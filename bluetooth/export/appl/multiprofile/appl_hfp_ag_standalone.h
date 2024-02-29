
/**
 *  \file appl_hfp_ag_standalone.h
 *
 *  Internal header file of HFP AG application.
 *  This file contains the data structures, type definitions
 *  and function declarations that HFP AG application uses
 *  internally.
 */

/*
 *  Copyright (C) 2013. Mindtree Ltd.
 *  All rights reserved.
 */

#ifndef _H_APPL_HFP_AG_STANDALONE_
#define _H_APPL_HFP_AG_STANDALONE_


/* ---------------------------------------- Header File Inclusion */
#include "appl_hfp_ag.h"

API_RESULT hfp_ag_standalone_appl_callback
           (
               /* IN */ HFP_AG_EVENTS events,
               /* IN */ API_RESULT result,
               /* IN */ void * data,
               /* IN */ UINT16 data_length
           );


void appl_handle_retval_from_hfag_standalone ( /* IN */ UINT16 retval);
void appl_hfag_standalone_close_voice_channel(void);
void appl_hfag_standalone_open_voice_channel(UCHAR codec);
void appl_hfp_ag_standalone_send_data(void);
void appl_hfp_ag_standalone_send_disable_voice_recognition (void);
void appl_hfp_ag_standalone_send_enable_voice_recognition (void);
void appl_hfp_ag_standalone_send_enh_voice_recognition (void);
void appl_hfpag_standalone_change_esco_config(void);
void appl_start_hfp_ag_standalone (void);
void hfp_ag_standalone_register_supp_feat ( /* IN */ UCHAR supported_features);
void register_features_satandalone( /* IN */ UCHAR supported_features);
void appl_hfag_standalone_read_pl(UCHAR * rsp, UINT16 rsplen);

/* SDP Callback for HFP */
void appl_hfag_standalone_sdp_cb
     (
         UCHAR command,
         UCHAR * data,
         UINT16 length,
         UINT16 status
     );
#ifdef HFP_BRIDGING_STANDALONE
UINT8 appl_hfpag_standalone_is_ag_connected();
#endif
#endif /* _H_APPL_HFP_AG_STANDALONE_ */

