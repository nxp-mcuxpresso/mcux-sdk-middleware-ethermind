
/**
 *  \file leaudio_pl.c
 *
 *
 */

/*
 *  Copyright (C) 2013. Mindtree Limited.
 *  All rights reserved.
 */


/* --------------------------------------------- Header File Inclusion */
#include "BT_fops.h"
#include "audio_pl.h"

/* --------------------------------------------- External Global Variables */

/* --------------------------------------------- Exported Global Variables */

/* --------------------------------------------- Static Global Variables */
UINT32 leaudio_src_sf;
UCHAR leaudio_src_bps;
UCHAR leaudio_src_nc;
UINT16 leaudio_src_size;
UINT16 leaudio_src_num_samples;
void (* leaudio_src_cb)(const UCHAR *data, UINT16 datalen);

UCHAR leaudio_src_playback;
BT_timer_handle leaudio_src_timer;
void leaudio_pl_start_playback_timer(void);

static INT32 leaudio_src_sent_ms;
static UINT32 leaudio_src_missed_count;

static BT_thread_mutex_type leaudio_src_media_mutex;
static BT_thread_cond_type leaudio_src_media_cond;

#define LEAUDIO_SRC_MEDIA \
     BT_FOPS_PATH_JOIN \
     ( \
         BT_FOPS_BASE, BT_FOPS_PATH_SEP "ga" \
     )
static BT_fops_file_handle leaudio_src_media_fd;

#define LEAUDIO_SRC_PERIOD_MS    10U

UINT32 leaudio_snk_sf;
UCHAR leaudio_snk_bps;
UCHAR leaudio_snk_nc;
UINT16 leaudio_snk_size;
void (* leaudio_snk_cb)(const UCHAR *data, UINT16 datlen);

//AT_NONCACHEABLE_SECTION_INIT(UCHAR leaudio_sbc_buffer[JPL_SBC_FRAME_SIZE * JPL_SBC_NUM_FRAMES]);
//AT_NONCACHEABLE_SECTION_INIT(UCHAR leaudio_pcm_buffer[JPL_PCM_BLOCK_SIZE * JPL_PCM_NUM_BLOCKS]);
//AT_NONCACHEABLE_SECTION_INIT(UCHAR leaudio_silence_buffer[JPL_PCM_BLOCK_SIZE]);

#ifdef BT_GAM
extern UINT8 isroleCT;
extern UINT8 isroleCG;
#endif

API_RESULT audio_src_prepare_file_name_pl(UCHAR *file_name);

/* --------------------------------------------- Functions */


__attribute__((weak)) void leaudio_init_pl_ext (UCHAR role)
{
}

__attribute__((weak)) void leaudio_shutdown_pl_ext (void)
{
}

__attribute__((weak)) API_RESULT leaudio_setup_pl_ext
     (
         UCHAR ep,
         void (* ep_cb)(const UCHAR *data, UINT16 datalen),
         UINT16 sf,
         UCHAR bps,
         UCHAR nc,
         UINT16 size
     )
{
    return API_SUCCESS;
}

__attribute__((weak)) API_RESULT leaudio_start_pl_ext (UCHAR ep)
{
    return API_SUCCESS;
}

__attribute__((weak)) API_RESULT leaudio_stop_pl_ext (UCHAR ep)
{
    return API_SUCCESS;
}

__attribute__((weak)) void leaudio_write_pl_ext (UCHAR ep, UCHAR * m_data, UINT16 m_datalen)
{
}

void leaudio_pl_produce_media(void)
{
    UCHAR * media;
    UINT16  medialen;
    API_RESULT retval;
    UINT16 readlen;

    if (NULL == leaudio_src_media_fd)
    {
        PL_ERR("Media not ready\n");
        return;
    }

    medialen = (leaudio_src_num_samples << leaudio_src_nc);
    media = BT_alloc_mem(medialen);

    if (NULL == media)
    {
    	PL_ERR("Memory Allocation failed in Produce Media\n");
        return;
    }

    retval = BT_fops_file_read(media, medialen, leaudio_src_media_fd, &readlen);
    if (API_SUCCESS != retval)
    {
        BT_fops_file_seek(leaudio_src_media_fd, 0U, BT_FOPS_SEEK_SET);
        retval = BT_fops_file_read(media, medialen, leaudio_src_media_fd, &readlen);
        if (API_SUCCESS != retval)
        {
        	PL_ERR("Media Read Failed\n");
            return;
        }
    }
    medialen = readlen;

    /* Give data to callback */
    leaudio_src_cb(media, medialen);

    BT_free_mem(media);
  }

void leaudio_pl_playback(void)
{
    INT32 now_ms, period_ms;

    /* Get the current time */
    now_ms = BT_get_time_ms();
    period_ms = LEAUDIO_SRC_PERIOD_MS;

    /* Adjust the period */
    if (0U < leaudio_src_sent_ms)
    {
        period_ms = (now_ms > leaudio_src_sent_ms)?
            (now_ms - leaudio_src_sent_ms): LEAUDIO_SRC_PERIOD_MS;
    }

    /* Get the number of samples */
    leaudio_src_num_samples = (UINT16)((period_ms * leaudio_src_sf) / 1000U);
    leaudio_src_missed_count += (period_ms * leaudio_src_sf) % 1000U;

    /* Raw adjust for the drift */
    while (leaudio_src_missed_count >= 1000U)
    {
        leaudio_src_num_samples++;
        leaudio_src_missed_count -= 1000U;
    }

    /* Update the sent timestamp */
    leaudio_src_sent_ms = now_ms;

    leaudio_pl_produce_media();
}

void leaudio_pl_playback_timeout_handler(void * args, UINT16 size)
{
    /* If stopped then return */
    if (BT_FALSE == leaudio_src_playback)
    {
        return;
    }

    /* Restart the timer */
    leaudio_src_timer = BT_TIMER_HANDLE_INIT_VAL;
    leaudio_pl_start_playback_timer();

    (BT_IGNORE_RETURN_VALUE) BT_thread_cond_signal(&leaudio_src_media_cond);
}

void leaudio_pl_start_playback_timer(void)
{
    (BT_IGNORE_RETURN_VALUE) BT_start_timer
    (
        &leaudio_src_timer,
        (BT_TIMEOUT_MILLISEC | LEAUDIO_SRC_PERIOD_MS),
        leaudio_pl_playback_timeout_handler,
        NULL, 0U
    );
}

DECL_STATIC BT_THREAD_RETURN_TYPE leaudio_src_media_task (BT_THREAD_ARGS args)
{
    BT_LOOP_FOREVER()
    {
        (BT_IGNORE_RETURN_VALUE) BT_thread_mutex_lock(&leaudio_src_media_mutex);
        (BT_IGNORE_RETURN_VALUE) BT_thread_cond_wait(&leaudio_src_media_cond, &leaudio_src_media_mutex);
        (BT_IGNORE_RETURN_VALUE) BT_thread_mutex_unlock(&leaudio_src_media_mutex);

        if ((BT_TRUE != leaudio_src_playback) || (NULL == leaudio_src_cb))
        {
            continue;
        }

        leaudio_pl_playback();
    }
}

API_RESULT leaudio_create_task_pl(BT_THREAD_START_ROUTINE routine)
{
    BT_thread_type tid;

    PL_TRC(
    "[leaudio] Creating Task ...\n");

    /* Create Write Task */
    if (0 != BT_thread_create(&tid,
        NULL,
        routine,
        NULL))
    {
        PL_ERR(
        "[leaudio] FATAL ERROR: FAILED to Create Task\n");

        return API_FAILURE;
    }

    return API_SUCCESS;
}

void leaudio_init_default_src_pl (void)
{
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
    (void) BT_thread_mutex_init (&leaudio_src_media_mutex, NULL);
    (BT_IGNORE_RETURN_VALUE) BT_thread_cond_init (&leaudio_src_media_cond, NULL);

    task_init = 0x01U;

    if (0 != BT_thread_create(&tid, &task_attr, leaudio_src_media_task, NULL))
    {
        PL_ERR("Failed to create leaudio Media Task\n");
        return;
    }
}

void leaudio_init_pl (UCHAR role)
{
    leaudio_init_pl_ext(role);
}

void leaudio_shutdown_pl (void)
{
    leaudio_shutdown_pl_ext();
}

UCHAR * leaudio_alloc_buffer_pl(UCHAR type)
{
    UCHAR * ptr;

    switch (type)
    {
#if 0
		case leaudio_SBC_BUFFER:
			ptr = leaudio_sbc_buffer;
			break;

		case leaudio_PCM_BUFFER:
			ptr = leaudio_pcm_buffer;
			break;

		case leaudio_SILENCE_BUFFER:
			ptr = leaudio_silence_buffer;
			break;
#endif
		default:
			ptr = NULL;
    }

    return ptr;
}

API_RESULT leaudio_setup_pl
           (
               UCHAR ep,
               void (* ep_cb)(const UCHAR *data, UINT16 datalen),
               UINT16 sf,
               UCHAR bps,
               UCHAR nc,
               UINT16 size
           )
{
    return leaudio_setup_pl_ext(ep, ep_cb, sf, bps, nc, size);
}

API_RESULT leaudio_start_pl (UCHAR ep)
{
    UCHAR audio_file_name[100] = { 0 };

#ifdef NVRAM_WORKAROUND
    /* Disable storage update */
    BT_storage_disable_store();
#endif /* NVRAM_WORKAROUND */

    if (AUDIO_EP_SOURCE == ep)
    {
#ifdef BT_GAM
    	if( (isroleCG == 0) && ((isroleCT == 0)) )
#endif
    	{
			UCHAR wav_header[44U];
			API_RESULT retval;
			UINT16 headerlen;

			leaudio_src_media_fd = NULL;

            /* Prepare the Audio File based on the Codec Configuration */
            retval = audio_src_prepare_file_name_pl(audio_file_name);
            if (API_SUCCESS == retval)
            {
                retval = BT_fops_file_open(audio_file_name, (UCHAR *)"rb", &leaudio_src_media_fd);
            }

            if (API_SUCCESS != retval)
            {
            	PL_ERR("Failed to open media for playback\n");
            	return retval;
            }

            /* Skip the initial 44 bytes of Wav header */
            BT_fops_file_read(wav_header, sizeof(wav_header), leaudio_src_media_fd, &headerlen);

            /* Reset indices */
			leaudio_src_sent_ms = 0U;
			leaudio_src_num_samples = 0U;
			leaudio_src_missed_count = 0U;
    	}
    }

    return leaudio_start_pl_ext(ep);
}

API_RESULT leaudio_stop_pl (UCHAR ep)
{
    API_RESULT retval;

    retval = leaudio_stop_pl_ext(ep);

    if (AUDIO_EP_SOURCE == ep)
    {
/* added this define for other legacy LE profiles are enabled */
#ifdef BT_GAM
        if( (isroleCG == 0) && ((isroleCT == 0)) )
#endif
        {
            /* MISRA C-2012 Rule 17.7 | Coverity CHECKED_RETURN */
            (void)BT_fops_file_close(leaudio_src_media_fd);
            leaudio_src_media_fd = NULL;
    	}
    }

    if (AUDIO_EP_SINK == ep)
    {
        /* Stop Audio Player */
    }

#ifdef NVRAM_WORKAROUND
    /* Sync the storage */
    BT_storage_sync_db(STORAGE_TYPE_PERSISTENT);
#endif /* NVRAM_WORKAROUND */

    return retval;
}

void leaudio_write_pl (UCHAR ep, UCHAR * m_data, UINT16 m_datalen)
{
    if (AUDIO_EP_SINK != ep)
    {
        return;
    }

    /* Write to player */
    leaudio_write_pl_ext(ep, m_data, m_datalen);
}

API_RESULT audio_src_prepare_file_name_pl(UCHAR *file_name)
{
    API_RESULT retval;

    retval = API_FAILURE;

    if (NULL != file_name)
    {
        /* Copy audio files path in audio file name */
        BT_str_copy(file_name, LEAUDIO_SRC_MEDIA);
        BT_str_cat(file_name, BT_FOPS_PATH_SEP);
        BT_str_cat(file_name, "all_");
        retval = API_SUCCESS;

        /* Append sampling freq in audio file name */
        switch (leaudio_src_sf)
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
            switch (leaudio_src_nc)
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
            switch (leaudio_src_bps)
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


