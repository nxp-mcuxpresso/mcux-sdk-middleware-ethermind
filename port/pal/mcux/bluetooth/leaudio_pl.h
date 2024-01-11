
/**
 *  \file leaudio_pl.h
 *
 *
 */

/*
 *  Copyright (C) 2013. Mindtree Limited.
 *  All rights reserved.
 */

#ifndef _H_LEAUDIO_PL_
#define _H_LEAUDIO_PL_

/* --------------------------------------------- Header File Inclusion */
#include "BT_common.h"


/* --------------------------------------------- API Declarations */
API_RESULT leaudio_create_task_pl(BT_THREAD_START_ROUTINE routine);
void leaudio_init_pl (UCHAR role);
void leaudio_shutdown_pl (void);
UCHAR * leaudio_alloc_buffer_pl(UCHAR type);
API_RESULT leaudio_setup_pl
           (
               UCHAR ep,
               void (* ep_cb)(const UCHAR *data, UINT16 datalen),
               UINT16 sf,
               UCHAR bps,
               UCHAR nc,
               UINT16 size
           );
API_RESULT leaudio_start_pl (UCHAR ep);
API_RESULT leaudio_stop_pl (UCHAR ep);
void leaudio_write_pl (UCHAR ep, UCHAR * m_data, UINT16 m_datalen);

void leaudio_init_pl_ext (UCHAR role);
void leaudio_shutdown_pl_ext (void);
API_RESULT leaudio_setup_pl_ext
           (
               UCHAR ep,
               void (* ep_cb)(const UCHAR *data, UINT16 datalen),
               UINT16 sf,
               UCHAR bps,
               UCHAR nc,
               UINT16 size
           );
API_RESULT  leaudio_start_pl_ext (UCHAR ep);
API_RESULT   leaudio_stop_pl_ext (UCHAR ep);
void leaudio_write_pl_ext (UCHAR ep, UCHAR * m_data, UINT16 m_datalen);
void le_audio_pl_iso_tx_delay (void);

#endif /* _H_LEAUDIO_PL_*/
