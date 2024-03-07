
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
#include "BT_status.h"
#include "audio_pl.h"
#include "leaudio_pl.h"
/* --------------------------------------------- External Global Variables */
/* --------------------------------------------- Exported Global functions */
/* --------------------------------------------- Static Global Variables */

bool is_sf_44k;

/* --------------------------------------------- internal functions prototypes */

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

#if defined(LE_AUDIO_SINK_SYNC_ENABLE) && (LE_AUDIO_SINK_SYNC_ENABLE > 0)
__attribute__((weak)) void le_audio_set_sync_info_pl_ext (UINT8 ep, UINT8 evt, void *sync_data)
{
}

#endif /*defined(LE_AUDIO_SINK_SYNC_ENABLE) && (LE_AUDIO_SINK_SYNC_ENABLE > 0)*/

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

int leaudio_get_sf(void)
{
	return is_sf_44k;
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
#ifdef NVRAM_WORKAROUND
    /* Disable storage update */
    BT_storage_disable_store();
#endif /* NVRAM_WORKAROUND */

    return leaudio_start_pl_ext(ep);
}

API_RESULT leaudio_stop_pl (UCHAR ep)
{
    API_RESULT retval;

    retval = leaudio_stop_pl_ext(ep);

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

#if defined(LE_AUDIO_SINK_SYNC_ENABLE) && (LE_AUDIO_SINK_SYNC_ENABLE > 0)
void le_audio_set_sync_info_pl (UINT8 ep, UINT8 evt, void *sync_data)
{
    le_audio_set_sync_info_pl_ext (ep, evt, sync_data);
}
#endif /*defined(LE_AUDIO_SINK_SYNC_ENABLE) && (LE_AUDIO_SINK_SYNC_ENABLE > 0)*/
