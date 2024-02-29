
/**
 *  \file obex_fsm_handlers.h
 *
 *  This file contains function handler declarations for OBEX 20601 FSM.
 *
 */

/*
 *  Copyright (C) 2011. MindTree Ltd.
 *  All rights reserved.
 */

#ifndef _H_PROFILE_FSM_HANDLERS_
#define _H_PROFILE_FSM_HANDLERS_
#include "BT_error.h"
#include "fsm_defines.h"
#include "profile_fsm_engine.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef UINT8 PROFILE_HANDLE;

API_RESULT se_profile_a2dp_connect_handler
           (
              void * hparams
           );
API_RESULT se_profile_error_handler
           (
               void *    hparams
           );
API_RESULT se_profile_a2dp_disconnect_handler
           (
               void *    hparams
           );
API_RESULT se_profile_a2dp_start_handler
           (
               void *    hparams
           );
API_RESULT se_profile_a2dp_suspend_handler
           (
               void *    hparams
           );
API_RESULT se_profile_a2dp_stop_handler
           (
               void *    hparams
           );
API_RESULT se_profile_hf_connect_handler
           (
               void *    hparams
           );
API_RESULT se_profile_hf_disconnect_handler
           (
               void *    hparams
           );
API_RESULT se_profile_hf_sco_connect_handler
           (
               void *    hparams
           );
API_RESULT se_profile_hf_sco_disconnect_handler
           (
               void *    hparams
           );
API_RESULT se_profile_avrcp_connect_handler
           (
              void * hparams
           );
API_RESULT se_profile_avrcp_disconnect_handler
           (
              void * hparams
           );
API_RESULT se_profile_avrcp_sdp_completed_handler
           (
               void *    hparams
           );
API_RESULT se_profile_avrcp_msg_ind_handler
           (
              void * hparams
		   );
API_RESULT se_profile_avrcp_msg_rsp_handler
           (
               void *    hparams
           );
#ifdef __cplusplus
};
#endif


#endif /* _H_PROFILE_FSM_HANDLERS_ */

