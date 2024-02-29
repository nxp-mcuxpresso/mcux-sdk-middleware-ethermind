
/**
 *  \file profile_fsm_table.c
 *
 *  This file contains PROFILE FSM - state/event transitions.
 */

/*
 *  Copyright (C) 2011. MindTree Ltd.
 *  All rights reserved.
 */

/* --------------------------------------------- Header File Inclusion */
#include "fsm_defines.h"
#include "profile_fsm_engine.h"
#include "profile_fsm_handlers.h"
#ifdef MULTI_PROFILE_FSM_SUPPORT
const /* DECL_CONST_QUALIFIER */ STATE_EVENT_TABLE profile_state_event_table[] =
{
    {
        /*0*/ ev_pro_a2dp_connect,
        1U,
        0U
    },
    {
        /*1*/ ev_pro_a2dp_disconnect,
        3U,
        2U
    },
    {
        /*2*/ ev_pro_a2dp_start,
        5U,
        4U
    },
    {
        /*3*/ ev_pro_a2dp_suspend,
        7U,
        6U
    },
    {
        /*4*/ ev_pro_a2dp_stop,
        9U,
        8U
    },
    {
        /*5*/ ev_pro_hfp_connect,
        11U,
        10U
    },
    {
        /*6*/ ev_pro_hfp_disconnect,
        13U,
        12U
    },
    {
        /*7*/ ev_pro_hfp_sco_connect,
        15U,
        14U
    },
    {
        /*8*/ ev_pro_hfp_sco_disconnect,
        17U,
        16U
    },
    {
        /*9*/ ev_pro_avrcp_sdp_done,
        18U,
        18U
    },
	{
	    /* 10 */ ev_pro_avrcp_connect,
        19U,
        19U
	},
	{
        /* 11 */ ev_pro_avrcp_disconnect,
         20U,
         20U
	},
    {
		/* 12 */ ev_pro_avrcp_message_ind,
		 21U,
		 21U
	},
	{
		/* 13 */ ev_pro_avrcp_message_cnf,
         22U,
		 22U
	},
    {
         /*14*/ ev_pro_error_rsp,
         24U,
         23U
    }
};

const /* DECL_CONST_QUALIFIER */ EVENT_HANDLER_TABLE profile_event_handler_table[] =
{
    {
        /*0*/ SL_A2DP_STARTED,
        (SE_HNDLR_T )se_profile_a2dp_connect_handler
    },
    {
        /*1*/ SL_A2DP_INITIALIZED | SL_A2DP_CONNECTED | SL_A2DP_STREAM_STARTED,
        (SE_HNDLR_T )se_profile_error_handler
    },
    {
        /*2*/ SL_A2DP_INITIALIZED | SL_A2DP_CONNECTED | SL_A2DP_STREAM_STARTED,
        (SE_HNDLR_T ) se_profile_a2dp_disconnect_handler
    },
    {
        /*3*/ SL_A2DP_INITIALIZED | SL_A2DP_STARTED,
        (SE_HNDLR_T )se_profile_error_handler
    },
    {
        /*4*/ SL_A2DP_CONNECTED | SL_A2DP_SUSPEND_ON_SCO,
        (SE_HNDLR_T ) se_profile_a2dp_start_handler
    },
    {
        /*5*/ SL_A2DP_INITIALIZED | SL_A2DP_STARTED | SL_A2DP_STREAM_STARTED |
         SL_HF_SCO_CONNECTED,
        (SE_HNDLR_T )se_profile_error_handler
    },
    {
        /*6*/ SL_A2DP_STREAM_STARTED | SL_HF_SCO_CONNECTED,
        (SE_HNDLR_T ) se_profile_a2dp_suspend_handler
    },
    {
        /*7*/ SL_A2DP_INITIALIZED | SL_A2DP_CONNECTED | SL_A2DP_STARTED,
        (SE_HNDLR_T )se_profile_error_handler
    },
    {
        /*8*/ SL_A2DP_STREAM_STARTED,
        (SE_HNDLR_T ) se_profile_a2dp_stop_handler
    },
    {
        /*9*/ SL_A2DP_INITIALIZED | SL_A2DP_CONNECTED | SL_A2DP_STARTED ,
        (SE_HNDLR_T )se_profile_error_handler
    },
    {
        /*10*/ SL_HF_STARTED,
        (SE_HNDLR_T )se_profile_hf_connect_handler
    },
    {
        /*11*/ SL_HF_INITIALIZED | SL_HF_CONNECTED | SL_HF_SCO_CONNECTED,
        (SE_HNDLR_T )se_profile_error_handler
    },
    {
        /*12*/ SL_HF_CONNECTED | SL_HF_SCO_CONNECTED,
        (SE_HNDLR_T )se_profile_hf_disconnect_handler
    },
    {
        /*13*/ SL_HF_INITIALIZED | SL_HF_STARTED,
        (SE_HNDLR_T )se_profile_error_handler
    },
    {
        /*14*/ SL_HF_CONNECTED,
        (SE_HNDLR_T )se_profile_hf_sco_connect_handler
    },
    {
        /*15*/ SL_HF_INITIALIZED | SL_HF_STARTED | SL_HF_SCO_CONNECTED,
        (SE_HNDLR_T )se_profile_error_handler
    },
    {
        /*16*/ SL_A2DP_SUSPEND_ON_SCO | SL_HF_SCO_CONNECTED,
        (SE_HNDLR_T )se_profile_hf_sco_disconnect_handler
    },
    {
        /*17*/ SL_HF_INITIALIZED | SL_HF_STARTED,
        (SE_HNDLR_T )se_profile_error_handler
    },
	{
        /* 18 */SL_AVRCP_STARTED | SL_AVRCP_CONNECTED,
        (SE_HNDLR_T)se_profile_avrcp_sdp_completed_handler
	},
	{
		/* 19 */SL_AVRCP_STARTED,
		(SE_HNDLR_T)se_profile_avrcp_connect_handler
	},
	{
		/* 20 */ SL_AVRCP_CONNECTED,
		(SE_HNDLR_T)se_profile_avrcp_disconnect_handler
	},
	{
		/* 21 */ SL_AVRCP_CONNECTED,
		(SE_HNDLR_T)se_profile_avrcp_msg_ind_handler
	},
	{
		/* 22 */ SL_AVRCP_CONNECTED,
		(SE_HNDLR_T)se_profile_avrcp_msg_rsp_handler
    }
};
#endif /* MULTI_PROFILE_FSM_SUPPORT */
