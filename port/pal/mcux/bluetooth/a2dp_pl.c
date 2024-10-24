
/**
 *  \file a2dp_pl.c
 *
 *
 */

/*
 *  Copyright (C) 2013. Mindtree Limited.
 *  All rights reserved.
 */


/* --------------------------------------------- Header File Inclusion */
#include "a2dp_pl.h"

#ifdef A2DP_SOURCE

/* For A2DP Source Streaming */
#ifndef A2DP_PL_SOURCE_FS_MEDIA
#ifndef A2DP_PL_SOURCE_16KHz_SAMPLE
#include "a2dp_pl_media_48KHz.h"
#else /* A2DP_PL_SOURCE_16KHz_SAMPLE */
#include "a2dp_pl_media_16KHz.h"
#endif /* A2DP_PL_SOURCE_16KHz_SAMPLE */
#else /* A2DP_PL_SOURCE_FS_MEDIA */
#include "BT_fops.h"
#endif /* A2DP_PL_SOURCE_FS_MEDIA */
#endif /* A2DP_SOURCE */

/* --------------------------------------------- External Global Variables */

/* --------------------------------------------- Exported Global Variables */

/* --------------------------------------------- Static Global Variables */
#ifdef A2DP_SOURCE
UINT32 a2dp_src_sf;
UCHAR a2dp_src_bps;
UCHAR a2dp_src_nc;
UINT16 a2dp_src_size;
UINT16 a2dp_src_num_samples;
void (* a2dp_src_cb)(const UCHAR *data, UINT16 datalen);

UCHAR a2dp_src_playback;
BT_timer_handle a2dp_src_timer;
void a2dp_pl_start_playback_timer(void);

static int tone_index;
static INT32 a2dp_src_sent_ms;
static UINT32 a2dp_src_missed_count;

static BT_thread_mutex_type a2dp_src_media_mutex;
static BT_thread_cond_type a2dp_src_media_cond;

#ifdef A2DP_PL_SOURCE_FS_MEDIA
#ifdef AUDIO_PL_SOURCE_USE_DEFAULT_AUDIO_FILE
#ifdef MULTI_PROFILE_FSM_SUPPORT
UCHAR *A2DP_SRC_MEDIA = NULL;
#define A2DP_SRC_MEDIA_BASE_LEN 13
#define A2DP_SRC_MEDIA_NAME_LEN 40
#else //MULTI_PROFILE_FSM_SUPPORT
#define A2DP_SRC_MEDIA \
     BT_FOPS_PATH_JOIN(BT_FOPS_BASE,"data" BT_FOPS_PATH_SEP "a2dp" BT_FOPS_PATH_SEP "sample.wav")
#endif
#else /* AUDIO_PL_SOURCE_USE_DEFAULT_AUDIO_FILE */
#define A2DP_SRC_MEDIA \
     BT_FOPS_PATH_JOIN \
     ( \
         BT_FOPS_BASE, BT_FOPS_PATH_SEP "ga" \
     )
#endif /* AUDIO_PL_SOURCE_USE_DEFAULT_AUDIO_FILE */
static BT_fops_file_handle a2dp_src_media_fd;
#endif /* A2DP_PL_SOURCE_FS_MEDIA */

#define A2DP_SRC_PERIOD_MS    10U
#endif /* A2DP_SOURCE */

#ifdef A2DP_SINK
UINT32 a2dp_snk_sf;
UCHAR a2dp_snk_bps;
UCHAR a2dp_snk_nc;
UINT16 a2dp_snk_size;
void (* a2dp_snk_cb)(const UCHAR *data, UINT16 datlen);

/*Below change is made to fix DTCM buffer issue for LEAUDIO/A2DP,
 * Disable LE AUDIO flags to enable DTCM buffer for A2DP Sink*/
#if defined(LE_AUDIO_SINK_SYNC_ENABLE) && (LE_AUDIO_SINK_SYNC_ENABLE > 0)
static UCHAR a2dp_sbc_buffer[JPL_SBC_FRAME_SIZE * JPL_SBC_NUM_FRAMES];
static UCHAR a2dp_pcm_buffer[JPL_PCM_BLOCK_SIZE * JPL_PCM_NUM_BLOCKS];
static UCHAR a2dp_silence_buffer[JPL_PCM_BLOCK_SIZE];
#else
static UCHAR a2dp_sbc_buffer[JPL_SBC_FRAME_SIZE * JPL_SBC_NUM_FRAMES];
AT_NONCACHEABLE_SECTION_INIT(UCHAR a2dp_pcm_buffer[JPL_PCM_BLOCK_SIZE * JPL_PCM_NUM_BLOCKS]);
AT_NONCACHEABLE_SECTION_INIT(UCHAR a2dp_silence_buffer[JPL_PCM_BLOCK_SIZE]);
#endif /*defined(LE_AUDIO_SINK_SYNC_ENABLE) && (LE_AUDIO_SINK_SYNC_ENABLE > 0)*/

#endif /* A2DP_SINK */

#if ((defined A2DP_PL_SOURCE_FS_MEDIA) && (!defined (AUDIO_PL_SOURCE_USE_DEFAULT_AUDIO_FILE)))
API_RESULT audio_src_prepare_file_name_pl(CHAR *file_name);
#endif /* ((defined A2DP_PL_SOURCE_FS_MEDIA) && (!defined (AUDIO_PL_SOURCE_USE_DEFAULT_AUDIO_FILE))) */

/* --------------------------------------------- Functions */
__attribute__((weak)) void a2dp_init_pl_ext (UCHAR role)
{
}

__attribute__((weak)) void a2dp_shutdown_pl_ext (void)
{
}

__attribute__((weak)) API_RESULT a2dp_setup_pl_ext
     (
         UCHAR ep,
         void (* ep_cb)(const UCHAR *data, UINT16 datalen),
         UINT16 sf,
         UCHAR bps,
         UCHAR nc,
         UINT16 size
     )
{
#ifdef A2DP_SOURCE
    if (A2DP_EP_SOURCE == ep)
    {
        a2dp_src_cb = ep_cb;
        a2dp_src_sf = sf;
        a2dp_src_bps = bps;
        a2dp_src_nc = nc;
        a2dp_src_size = size;
    }

    BT_IGNORE_UNUSED_PARAM(a2dp_src_bps);
    BT_IGNORE_UNUSED_PARAM(a2dp_src_nc);
    BT_IGNORE_UNUSED_PARAM(a2dp_src_size);
#endif /* A2DP_SOURCE */

#ifdef A2DP_SINK
    if (A2DP_EP_SINK == ep)
    {
        a2dp_snk_cb = ep_cb;
        a2dp_snk_sf = sf;
        a2dp_snk_bps = bps;
        a2dp_snk_nc = nc;
        a2dp_snk_size = size;
    }

    BT_IGNORE_UNUSED_PARAM(a2dp_snk_sf);
    BT_IGNORE_UNUSED_PARAM(a2dp_snk_bps);
    BT_IGNORE_UNUSED_PARAM(a2dp_snk_nc);
    BT_IGNORE_UNUSED_PARAM(a2dp_snk_size);
#endif /* A2DP_SINK */

    BT_IGNORE_UNUSED_PARAM(ep);

    return API_SUCCESS;
}

__attribute__((weak)) API_RESULT a2dp_start_pl_ext (UCHAR ep)
{
#ifdef A2DP_SOURCE
    if (A2DP_EP_SOURCE == ep)
    {
        /* Start Audio Source */
    }
#endif /* A2DP_SOURCE */

#ifdef A2DP_SINK
    if (A2DP_EP_SINK == ep)
    {
        /* Start Audio Player */
    }
#endif /* A2DP_SINK */
    return API_SUCCESS;
}

__attribute__((weak)) API_RESULT a2dp_stop_pl_ext (UCHAR ep)
{
#ifdef A2DP_SOURCE
    if (A2DP_EP_SOURCE == ep)
    {
        /* Stop Audio Source */
    }
#endif /* A2DP_SOURCE */

#ifdef A2DP_SINK
    if (A2DP_EP_SINK == ep)
    {
        /* Stop Audio Player */
    }
#endif /* A2DP_SINK */
    return API_SUCCESS;
}

__attribute__((weak)) void a2dp_write_pl_ext (UCHAR ep, UCHAR * m_data, UINT16 m_datalen)
{
#ifdef A2DP_SINK
    if (A2DP_EP_SINK != ep)
    {
        return;
    }

    /* Write to player */
#endif /* A2DP_SINK */
}

#ifdef A2DP_SOURCE
void a2dp_pl_produce_media(void)
{
    UCHAR * media;
    UINT16  medialen;
    UINT8 isMemAllocated = BT_FALSE;
#ifndef A2DP_PL_SOURCE_FS_MEDIA

    /* Music Audio is Stereo */
    medialen = (a2dp_src_num_samples << a2dp_src_nc);

    /* For mono or stereo configuration, skip alternative samples */
    if (1U == a2dp_src_nc)
    {
        UINT16 index;

        /* Allocate Memory */
        media = (UCHAR*)BT_alloc_mem(medialen);

        if (NULL == media)
        {
            A2DP_PL_ERR("Memory Allocation failed in Produce Media\n");
            return;
        }

        isMemAllocated = BT_TRUE;

        for (index = 0U; index < a2dp_src_num_samples; index++)
        {
            media[(2U * index)] = *((UCHAR*)beethoven + tone_index);
            media[(2U * index) + 1U] = *((UCHAR*)beethoven + tone_index + 1U);

            /* Update the tone index */
            tone_index += 4U;
            if (tone_index >= sizeof(beethoven))
            {
                tone_index = 0U;
            }
        }
    }
    else
    {
        if ((tone_index + (a2dp_src_num_samples << 2U)) > sizeof(beethoven))
        {
            media = (UCHAR*)BT_alloc_mem(medialen);
            if (NULL == media)
            {
                A2DP_PL_ERR("Memory Allocation failed in Produce Media\n");
                return;
            }

            isMemAllocated = BT_TRUE;

            memcpy(media, ((UCHAR*)beethoven + tone_index), sizeof(beethoven) - tone_index);
            memcpy(&media[sizeof(beethoven) - tone_index],
                   ((UCHAR*)beethoven),
                   ((a2dp_src_num_samples << 2U) - (sizeof(beethoven) - tone_index)));
            /* Update the tone index */
            tone_index = ((a2dp_src_num_samples << 2U) - (sizeof(beethoven) - tone_index));
        }
        else
        {
            media = ((UCHAR*)beethoven + tone_index);
            /* Update the tone index */
            tone_index += (a2dp_src_num_samples << 2U);
            if (tone_index >= sizeof(beethoven))
            {
                tone_index = 0U;
            }
        }
    }
#else /* A2DP_PL_SOURCE_FS_MEDIA */
    API_RESULT retval;
    UINT16 readlen;

    if (NULL == a2dp_src_media_fd)
    {
        A2DP_PL_ERR("Media not ready\n");
        return;
    }

    medialen = (a2dp_src_num_samples << a2dp_src_nc);
    media = BT_alloc_mem(medialen);

    if (NULL == media)
    {
        A2DP_PL_ERR("Memory Allocation failed in Produce Media\n");
        return;
    }

    isMemAllocated = BT_TRUE;

    retval = BT_fops_file_read(media, medialen, a2dp_src_media_fd, &readlen);
    if (API_SUCCESS != retval)
    {
        BT_fops_file_seek(a2dp_src_media_fd, 0U, BT_FOPS_SEEK_SET);
        retval = BT_fops_file_read(media, medialen, a2dp_src_media_fd, &readlen);
        if (API_SUCCESS != retval)
        {
            A2DP_PL_ERR("Media Read Failed\n");
            return;
        }
    }
    medialen = readlen;
#endif /* A2DP_PL_SOURCE_FS_MEDIA */

    /* Give data to callback */
    a2dp_src_cb(media, medialen);

    if (BT_TRUE == isMemAllocated)
    {
        BT_free_mem(media);
    }
}

void a2dp_pl_playback(void)
{
    INT32 now_ms, period_ms;

    /* Get the current time */
    now_ms = BT_get_time_ms();
    period_ms = A2DP_SRC_PERIOD_MS;

    /* Adjust the period */
    if (0U < a2dp_src_sent_ms)
    {
        period_ms = (now_ms > a2dp_src_sent_ms)?
            (now_ms - a2dp_src_sent_ms): A2DP_SRC_PERIOD_MS;
    }

    /* Get the number of samples */
    a2dp_src_num_samples = (UINT16)((period_ms * a2dp_src_sf) / 1000U);
    a2dp_src_missed_count += (period_ms * a2dp_src_sf) % 1000U;

    /* Raw adjust for the drift */
    while (a2dp_src_missed_count >= 1000U)
    {
        a2dp_src_num_samples++;
        a2dp_src_missed_count -= 1000U;
    }

    /* Update the sent timestamp */
    a2dp_src_sent_ms = now_ms;

    a2dp_pl_produce_media();
}

void a2dp_pl_playback_timeout_handler(void * args, UINT16 size)
{
    /* If stopped then return */
    if (BT_FALSE == a2dp_src_playback)
    {
        return;
    }

    /* Restart the timer */
    a2dp_src_timer = BT_TIMER_HANDLE_INIT_VAL;
    a2dp_pl_start_playback_timer();

    (BT_IGNORE_RETURN_VALUE) BT_thread_cond_signal(&a2dp_src_media_cond);
}

void a2dp_pl_start_playback_timer(void)
{
    (BT_IGNORE_RETURN_VALUE) BT_start_timer
    (
        &a2dp_src_timer,
        (BT_TIMEOUT_MILLISEC | A2DP_SRC_PERIOD_MS),
        a2dp_pl_playback_timeout_handler,
        NULL, 0U
    );
}

DECL_STATIC BT_THREAD_RETURN_TYPE a2dp_src_media_task (BT_THREAD_ARGS args)
{
    BT_LOOP_FOREVER()
    {
        (BT_IGNORE_RETURN_VALUE) BT_thread_mutex_lock(&a2dp_src_media_mutex);
        (BT_IGNORE_RETURN_VALUE) BT_thread_cond_wait(&a2dp_src_media_cond, &a2dp_src_media_mutex);
        (BT_IGNORE_RETURN_VALUE) BT_thread_mutex_unlock(&a2dp_src_media_mutex);

        if ((BT_TRUE != a2dp_src_playback) || (NULL == a2dp_src_cb))
        {
            continue;
        }

        a2dp_pl_playback();
    }
}
#endif /* A2DP_SOURCE */

API_RESULT a2dp_create_task_pl(BT_THREAD_START_ROUTINE routine)
{
#ifdef A2DP_SOURCE
    BT_thread_type tid;

    PL_TRC(
    "[A2DP] Creating Task ...\n");

    /* Create Write Task */
    if (0 != BT_thread_create(&tid,
        NULL,
        routine,
        NULL))
    {
        PL_ERR(
        "[A2DP] FATAL ERROR: FAILED to Create Task\n");

        return API_FAILURE;
    }
#endif /* A2DP_SOURCE */

    return API_SUCCESS;
}

void a2dp_init_default_src_pl (void)
{
#ifdef A2DP_SOURCE
    static UCHAR task_init = 0x00U;

    BT_thread_type tid;
    BT_thread_attr_type task_attr;

    /* Initialize the Write Task Attributes */
    task_attr.thread_name       = (DECL_CONST CHAR  *)"EtherMind PCM Task";
    task_attr.thread_stack_size = BT_TASK_STACK_DEPTH;
    task_attr.thread_priority   = BT_TASK_PRIORITY;

    if (0x00U != task_init)
    {
        return;
    }

    /* MISRA C-2012 Rule 17.7 | Coverity CHECKED_RETURN */
    (void) BT_thread_mutex_init (&a2dp_src_media_mutex, NULL);
    (BT_IGNORE_RETURN_VALUE) BT_thread_cond_init (&a2dp_src_media_cond, NULL);

    task_init = 0x01U;

    if (0 != BT_thread_create(&tid, &task_attr, a2dp_src_media_task, NULL))
    {
        A2DP_PL_ERR("Failed to create A2DP Media Task\n");
        return;
    }
#endif /* A2DP_SOURCE */
}

void a2dp_init_pl (UCHAR role)
{
#ifdef A2DP_SOURCE
#ifdef MULTI_PROFILE_FSM_SUPPORT
#ifdef A2DP_PL_SOURCE_FS_MEDIA
	if (NULL == A2DP_SRC_MEDIA)
	{
		A2DP_SRC_MEDIA =  (UCHAR *)BT_alloc_mem(A2DP_SRC_MEDIA_NAME_LEN);
	    BT_mem_set(A2DP_SRC_MEDIA, 0x00, A2DP_SRC_MEDIA_NAME_LEN);
	    BT_str_copy(A2DP_SRC_MEDIA, "1:/data/a2dp/sample.wav");
		//A2DP_SRC_MEDIA = BT_FOPS_PATH_JOIN(BT_FOPS_BASE,"data" BT_FOPS_PATH_SEP "a2dp" BT_FOPS_PATH_SEP "sample.wav");
		printf("a2dp_init_pl() A2DP_SRC_MEDIA %s\n", A2DP_SRC_MEDIA);
	}
#endif /* A2DP_PL_SOURCE_FS_MEDIA */
#endif /* MULTI_PROFILE_FSM_SUPPORT */
#endif /* A2DP_SOURCE */

#ifdef A2DP_SINK
#endif /* A2DP_SINK */
    a2dp_init_pl_ext(role);
}

void a2dp_shutdown_pl (void)
{
#ifdef A2DP_SOURCE
#ifdef MULTI_PROFILE_FSM_SUPPORT
#ifdef A2DP_PL_SOURCE_FS_MEDIA
	if (NULL != A2DP_SRC_MEDIA)
	{
		BT_free_mem(A2DP_SRC_MEDIA);
		A2DP_SRC_MEDIA = NULL;
	}
#endif /* A2DP_PL_SOURCE_FS_MEDIA */
#endif /* MULTI_PROFILE_FSM_SUPPORT */
#endif /* A2DP_SOURCE */

#ifdef A2DP_SINK
#endif /* A2DP_SINK */
    a2dp_shutdown_pl_ext();
}

UCHAR * a2dp_alloc_buffer_pl(UCHAR type)
{
#ifdef A2DP_SINK
    UCHAR * ptr;

    switch (type)
    {
    case A2DP_SBC_BUFFER:
        ptr = a2dp_sbc_buffer;
        break;

    case A2DP_PCM_BUFFER:
        ptr = a2dp_pcm_buffer;
        break;

    case A2DP_SILENCE_BUFFER:
        ptr = a2dp_silence_buffer;
        break;

    default:
        ptr = NULL;
    }

    return ptr;
#else /* A2DP_SINK */

    return NULL;
#endif /* A2DP_SINK */
}

API_RESULT a2dp_setup_pl
           (
               UCHAR ep,
               void (* ep_cb)(const UCHAR *data, UINT16 datalen),
               UINT16 sf,
               UCHAR bps,
               UCHAR nc,
               UINT16 size
           )
{
    return a2dp_setup_pl_ext(ep, ep_cb, sf, bps, nc, size);
}

API_RESULT a2dp_start_pl (UCHAR ep)
{
#ifndef AUDIO_PL_SOURCE_USE_DEFAULT_AUDIO_FILE
    //UCHAR audio_file_name[100] = { 0 };
#endif /* AUDIO_PL_SOURCE_USE_DEFAULT_AUDIO_FILE */

#ifdef NVRAM_WORKAROUND
    /* Disable storage update */
    BT_storage_disable_store();
#endif /* NVRAM_WORKAROUND */

#ifdef A2DP_SOURCE
    if (A2DP_EP_SOURCE == ep)
    {
#ifdef A2DP_PL_SOURCE_FS_MEDIA
        UCHAR wav_header[44U];
        API_RESULT retval;
        UINT16 headerlen;

        a2dp_src_media_fd = NULL;
#ifdef AUDIO_PL_SOURCE_USE_DEFAULT_AUDIO_FILE
        retval = BT_fops_file_open(A2DP_SRC_MEDIA, "rb", &a2dp_src_media_fd);
#else /* AUDIO_PL_SOURCE_USE_DEFAULT_AUDIO_FILE */
        /* Prepare the Audio File based on the Codec Configuration */
        retval = audio_src_prepare_file_name_pl(&audio_file_name);
        if (API_SUCCESS == retval)
        {
            retval = BT_fops_file_open(audio_file_name, "rb", &a2dp_src_media_fd);
        }
#endif /* AUDIO_PL_SOURCE_USE_DEFAULT_AUDIO_FILE */

        if (API_SUCCESS != retval)
        {
            A2DP_PL_ERR("Failed to open media for playback\n");
            return retval;
        }

        /* Skip the initial 44 bytes of Wav header */
        BT_fops_file_read(wav_header, sizeof(wav_header), a2dp_src_media_fd, &headerlen);
#endif /* A2DP_PL_SOURCE_FS_MEDIA */

        /* Reset indices */
        tone_index = 0U;
        a2dp_src_sent_ms = 0U;
        a2dp_src_num_samples = 0U;
        a2dp_src_missed_count = 0U;

        /* Start Audio Source */
    }
#endif /* A2DP_SOURCE */

#ifdef A2DP_SINK
    if (A2DP_EP_SINK == ep)
    {
        /* Start Audio Player */
    }
#endif /* A2DP_SINK */
    return a2dp_start_pl_ext(ep);
}

API_RESULT a2dp_stop_pl (UCHAR ep)
{
    API_RESULT retval;

    retval = a2dp_stop_pl_ext(ep);

#ifdef A2DP_SOURCE
    if (A2DP_EP_SOURCE == ep)
    {
#ifdef A2DP_PL_SOURCE_FS_MEDIA
        /* MISRA C-2012 Rule 17.7 | Coverity CHECKED_RETURN */
        (void)BT_fops_file_close(a2dp_src_media_fd);
        a2dp_src_media_fd = NULL;
#endif /* A2DP_PL_SOURCE_FS_MEDIA */
    }
#endif /* A2DP_SOURCE */

#ifdef A2DP_SINK
    if (A2DP_EP_SINK == ep)
    {
        /* Stop Audio Player */
    }
#endif /* A2DP_SINK */

#ifdef NVRAM_WORKAROUND
    /* Sync the storage */
    BT_storage_sync_db(STORAGE_TYPE_PERSISTENT);
#endif /* NVRAM_WORKAROUND */

    return retval;
}

void a2dp_write_pl (UCHAR ep, UCHAR * m_data, UINT16 m_datalen)
{
#ifdef A2DP_SINK
    if (A2DP_EP_SINK != ep)
    {
        return;
    }

    /* Write to player */
#endif /* A2DP_SINK */
    a2dp_write_pl_ext(ep, m_data, m_datalen);
}

#if ((defined A2DP_PL_SOURCE_FS_MEDIA) && (!defined (AUDIO_PL_SOURCE_USE_DEFAULT_AUDIO_FILE)))
API_RESULT audio_src_prepare_file_name_pl(CHAR *file_name)
{
    API_RESULT retval;

    retval = API_FAILURE;

    if (NULL != file_name)
    {
        /* Copy audio files path in audio file name */
        BT_str_copy(file_name, A2DP_SRC_MEDIA);
        BT_str_cat(file_name, BT_FOPS_PATH_SEP);
        BT_str_cat(file_name, "all_");
        retval = API_SUCCESS;

        /* Append sampling freq in audio file name */
        switch (a2dp_src_sf)
        {
        case 8000:
            BT_str_cat(file_name, "8000hz_");
            break;

        case 16000:
            BT_str_cat(file_name, "16000hz_");
            break;

        case 24000:
            BT_str_cat(file_name, "24000hz_");
            break;

        case 32000:
            BT_str_cat(file_name, "32000hz_");
            break;

        case 44100:
            BT_str_cat(file_name, "44100hz_");
            break;

        case 48000:
            BT_str_cat(file_name, "48000hz_");
            break;

        default:
            retval = API_FAILURE;
            break;
        }

        if (API_SUCCESS == retval)
        {
            switch (a2dp_src_nc)
            {
            case 1:
                BT_str_cat(file_name, "1ch_");
                break;
            /*
             * For CC 2 also currently we are using 1 channel file and
             * duplicating the data above
             */

            default:
                BT_str_cat(file_name, "1ch_");
                break;
            }
        }

        if (API_SUCCESS == retval)
        {
            switch (a2dp_src_bps)
            {
            case 16:
                BT_str_cat(file_name, "16b");
                break;

            case 24:
                BT_str_cat(file_name, "24b");
                break;

            case 32:
                BT_str_cat(file_name, "32b");
                break;

            default:
                retval = API_FAILURE;
                break;
            }
        }
    }

    if (API_SUCCESS == retval)
    {
        /*
         * Append file extension "wav" in audio file name with
         * NULL(\0) at the end.
         */
        BT_str_cat(file_name, ".wav\0");
    }

    return retval;
}
#endif /* ((defined A2DP_PL_SOURCE_FS_MEDIA) && (!defined (AUDIO_PL_SOURCE_USE_DEFAULT_AUDIO_FILE))) */
#ifdef MULTI_PROFILE_FSM_SUPPORT
#ifdef A2DP_PL_SOURCE_FS_MEDIA
void audio_set_media_file_name_pl(UCHAR* media_file_name)
{
	UCHAR i;
	if (NULL != A2DP_SRC_MEDIA)
	{
		UCHAR *temp;
		temp = A2DP_SRC_MEDIA;
		printf("A2DP_SRC_MEDIA %s\n", A2DP_SRC_MEDIA);
		for (i = 0; i < A2DP_SRC_MEDIA_NAME_LEN; i++ )
		{
			printf("%c ", temp[i]);
		}
		printf("\n");
	    BT_str_copy((A2DP_SRC_MEDIA + A2DP_SRC_MEDIA_BASE_LEN), media_file_name);
		A2DP_SRC_MEDIA[A2DP_SRC_MEDIA_BASE_LEN + BT_str_len(media_file_name)] = '\0';
		printf("A2DP_SRC_MEDIA %s\n", A2DP_SRC_MEDIA);
	}
}
#endif /* A2DP_PL_SOURCE_FS_MEDIA */
void a2dp_audio_set_speaker_volume_pl(UCHAR value)
{
    (void)a2dp_audio_set_speaker_volume(value);
}
#endif /* MULTI_PROFILE_FSM_SUPPORT */
