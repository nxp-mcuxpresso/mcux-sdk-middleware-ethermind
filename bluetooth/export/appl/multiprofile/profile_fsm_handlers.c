/**
 *  \file profile_fsm_handlers.c
 *
 *  This file implements the function handler for OBEX FSM
 */

/*
 *  Copyright (C) 2011. MindTree Ltd.
 *  All rights reserved.
 */

/* --------------------------------------------- Header File Inclusion */
#include "appl_a2dp.h"
#include "appl_avrcp.h"
#include "appl_avrcp_ct.h"
#include "BT_avdtp_api.h"
#include "BT_avrcp_api.h"
#ifdef MULTI_PROFILE_FSM_SUPPORT
#include "appl_common.h"
#include "profile_fsm_handlers.h"

//#define ENABLE_APPL_LOG

#ifndef ENABLE_APPL_LOG
#ifdef APPL_LOG
#undef APPL_LOG
#define APPL_LOG(...)
#endif /*APPL_LOG*/
#endif /*DISBALE_APPL_LOG*/

/* --------------------------------------------- External Global Variables */
extern A2DP_APPL_INSTANCE a2dp_appl_instance [A2DP_MAX_CODECS];
/* --------------------------------------------- Exported Global Variables */
extern PROFILE_SESSION multiprofile_inst[PROFILE_MAX_INSTANCES];
/* --------------------------------------------- Static Global Variables */
static UCHAR a2dp_idx_suspended;
/* a2dp streaming BD_ADDR */
static UCHAR bd_addr [BT_BD_ADDR_SIZE];
/* --------------------------------------------- Functions */

#ifndef A2DP_BRIDGING
API_RESULT se_profile_a2dp_connect_handler
           (
               void    * hparams
           )
{
    UINT32 state;
    PROFILE_SESSION * profile_session;
    API_RESULT retval;

    PROFILE_EVENT_INFO * param;
    param = (PROFILE_EVENT_INFO *)hparams;

    APPL_LOG (
    "[MULTI_PROFILE]: >>> se_profile_a2dp_connect_handler\n");

    state = 00U;
    retval = 0x00U;

    /* Get PROFILE session */
    profile_session = &multiprofile_inst[param->profile_fsm_handle];

    state = PROFILE_ACCESS_STATE(param->profile_fsm_handle);

    /* Initialize FSM state */
    state |=  SL_A2DP_CONNECTED;
    state &= ~(SL_A2DP_INITIALIZED);

    /* Is local event? */
    if (PROFILE_FSM_LOCAL_EVENT == param->event_info)
    {
        APPL_LOG (
        "[MULTI_PROFILE]: PROFILE_FSM_LOCAL_EVENT\n");
    }
    else if (PROFILE_FSM_REMOTE_EVENT == param->event_info)
    {
        APPL_LOG (
        "[MULTI_PROFILE]: PROFILE_FSM_REMOTE_EVENT\n");

    }
    else
    {
        /* MISRA C-2012 Rule 15.7 */
    }
    /* BD Address */
    BT_mem_copy
    (
        profile_session->bd_addr,
        (UCHAR*)param->data,
        BT_BD_ADDR_SIZE
    );
    APPL_LOG("\t    " BT_DEVICE_ADDR_ONLY_FRMT_SPECIFIER "\n",
    BT_DEVICE_ADDR_ONLY_PRINT_STR (profile_session->bd_addr));

    printf ("[fsm]ev_pro_a2dp_connect[%d,%d], current-state:%08x, updated-state: %08X\n", param->event_type, param->event_info, PROFILE_ACCESS_STATE(param->profile_fsm_handle),state);

    /* Update FSM State */
    PROFILE_SET_STATE (param->profile_fsm_handle, state);

    APPL_LOG (
    "[MULTI_PROFILE]: <<< se_profile_a2dp_connect_handler\n");

    return retval;
}
#else
API_RESULT se_profile_a2dp_connect_handler
           (
               void    * hparams
           )
{
    UINT32 state = 0, state_prev = 0;
    PROFILE_SESSION * profile_session;
    API_RESULT retval = 0;
    PROFILE_EVENT_INFO * param;
    param = (PROFILE_EVENT_INFO *)hparams;

    /* Get PROFILE session */
    profile_session = &multiprofile_inst[param->profile_fsm_handle];
    uint8_t current_a2dp_inst = a2dp_find_a2dp_instance (param->data);
    uint8_t other_a2dp_index = a2dp_find_connected_a2dp_instance (current_a2dp_inst);

	/*both a2dp role is now connected, a2dp-bridge connected*/
    state = PROFILE_ACCESS_STATE(param->profile_fsm_handle);
    state_prev = state;

    if (other_a2dp_index != PROFILE_INSTANCE_INVALID)
    {
    	/*avdtp config mismatched, update it from other a2dp end-point*/
        if ((param->event_info == PROFILE_FSM_REMOTE_EVENT) && memcmp(a2dp_appl_instance[other_a2dp_index].codec_ie_conf, a2dp_appl_instance[current_a2dp_inst].codec_ie_conf, AVDTP_MAX_CODEC_IE_LEN) != 0)
        {
            AVDTP_SEP_CONF sep_conf;
            UCHAR* codec_ie_conf = a2dp_appl_instance[other_a2dp_index].codec_ie_conf;

            /* Enable Codec Capabilities in SEP Configuration */
            AVDTP_SET_SEP_CONFIGURATION_CODEC_CAP
            (
                sep_conf,
                a2dp_appl_instance[other_a2dp_index].sep_cap.codec_cap.media_type,
                a2dp_appl_instance[other_a2dp_index].sep_cap.codec_cap.codec_type,
                a2dp_appl_instance[other_a2dp_index].sep_cap.codec_cap.codec_ie_len,
                codec_ie_conf
            )

			retval = BT_a2dp_reconfigure(
					a2dp_appl_instance[current_a2dp_inst].a2dp_instance,
					&sep_conf);

            if (API_SUCCESS != retval)
            {
                printf("BT_a2dp_reconfigure() failed with 0x%04X\n", retval);
            }
            else
            {
            	printf("OK. Wait for A2DP_RECONFIGURE_CNF\n");
                a2dp_appl_save_codec_ie_configuration
                (
                    a2dp_appl_instance[other_a2dp_index].role,
                    a2dp_appl_instance[other_a2dp_index].sep_cap.codec_cap.codec_type,
                    codec_ie_conf,
                    a2dp_appl_instance[other_a2dp_index].sep_cap.codec_cap.codec_ie_len
                );
            }
        }

        /* BD Address */
        BT_mem_copy
        (
            profile_session->bd_addr,
            (UCHAR*)param->data,
            BT_BD_ADDR_SIZE
        );

        /* Initialize FSM state */
        state |=  SL_A2DP_CONNECTED;
        state &= ~(SL_A2DP_INITIALIZED);
        PROFILE_SET_STATE (param->profile_fsm_handle, state);
    }
    printf ("[fsm]ev_pro_a2dp_connect[%d,%d], current-state:%08x, updated-state: %08X\n", param->event_type, param->event_info, state_prev,state);
    /* Set the current instance as connected */
    a2dp_appl_instance[current_a2dp_inst].a2dp_connection_state = APPL_A2DP_CONNECTED;

    /*start avrcp sdp-open*/
    appl_get_avrcp_sdp_record((UCHAR*)param->data);

    return retval;
}
#endif /*A2DP_BRIDGING*/

void profile_notify_session(PROFILE_HANDLE handle, UINT16 status, API_RESULT retval)
{
    BT_IGNORE_UNUSED_PARAM(handle);
    BT_IGNORE_UNUSED_PARAM(retval);
    APPL_LOG (
    "[MULTI_PROFILE]: >>> profile_notify_session\n");
    APPL_LOG("status %d\n", status);
    APPL_LOG (
    "[MULTI_PROFILE]: <<< profile_notify_session\n");
}

API_RESULT se_profile_error_handler
           (
               void    * hparams
           )
{
    PROFILE_SESSION * profile_session;
    API_RESULT retval;
    PROFILE_HANDLE handle;

    PROFILE_EVENT_INFO * param;
    param = (PROFILE_EVENT_INFO *)hparams;

    APPL_LOG (
    "[MULTI_PROFILE]: >>> se_profile_error_handler\n");

    retval = PROFILE_INVALID_STATE;

    /* if (OBEX_FSM_LOCAL_EVENT != param->event_info) */
    if (NULL != param->data)
    {
        APPL_LOG (
        "[MULTI_PROFILE]: Profile Error Response on handle 0x%02X\n", param->profile_fsm_handle);

        /* Get profile session */
        handle = param->profile_fsm_handle;
        profile_session = &multiprofile_inst[handle];

        /* Get the error result */
        retval = *((API_RESULT *)param->data);

        /* Update FSM State to previous state */
        PROFILE_SET_STATE (param->profile_fsm_handle, profile_session->prev_state);

        printf ("[fsm]se_profile_error_handler[%d,%d],state: %08X\n", param->event_type, param->event_info,PROFILE_ACCESS_STATE(param->profile_fsm_handle));

        /* Inform the application about the occurrence of the error */
        profile_notify_session
        (
            handle,
            PROFILE_EVENT_OP_ERROR,
            retval
        );

        retval = API_SUCCESS;
    }

    APPL_LOG (
    "[MULTI_PROFILE]: <<< se_profile_error_handler\n");

    return retval;
}

#ifndef A2DP_BRIDGING
API_RESULT se_profile_a2dp_disconnect_handler
           (
               void *    hparams
           )
{
    UINT32 state;
    PROFILE_SESSION * profile_session;
    API_RESULT retval;
    PROFILE_EVENT_INFO* param;

    param = (PROFILE_EVENT_INFO *)hparams;

    state = 00U;
    retval = 0x00U;

    APPL_LOG (
    "[MULTI_PROFILE]: >>> se_profile_a2dp_disconnect_handler\n");

    /* Get PROFILE session */
    profile_session = &multiprofile_inst[param->profile_fsm_handle];
    state = PROFILE_ACCESS_STATE(param->profile_fsm_handle);

    /* Initialize FSM state */
    state |= SL_A2DP_STARTED ;
    state &= ~(SL_A2DP_CONNECTED);

    APPL_LOG (
     "[PROFILE_FSM_HANDLER]: state  %02X \n", state);

    /* Is local event? */
    if (PROFILE_FSM_LOCAL_EVENT == param->event_info)
    {
        APPL_LOG (
        "[MULTI_PROFILE]: se_profile_a2dp_disconnect_handler PROFILE_FSM_LOCAL_EVENT\n");
    }
    else if (PROFILE_FSM_REMOTE_EVENT == param->event_info)
    {
        APPL_LOG (
        "[MULTI_PROFILE]: se_profile_a2dp_disconnect_handler PROFILE_FSM_REMOTE_EVENT\n");
    }
    else
    {
        /* MISRA C-2012 Rule 15.7 */
    }
    /* BD Address */
    BT_mem_copy
    (
        profile_session->bd_addr,
        (UCHAR*)param->data,
        BT_BD_ADDR_SIZE
    );
    APPL_LOG("\t    " BT_DEVICE_ADDR_ONLY_FRMT_SPECIFIER "\n",
    BT_DEVICE_ADDR_ONLY_PRINT_STR (profile_session->bd_addr));

    printf ("[fsm]ev_pro_a2dp_disconnect[%d,%d], current-state:%08x, updated-state: %08X\n", param->event_type, param->event_info, PROFILE_ACCESS_STATE(param->profile_fsm_handle),state);

    /* Update FSM State */
    PROFILE_SET_STATE (param->profile_fsm_handle, state);

    APPL_LOG (
    "[MULTI_PROFILE]: <<< se_profile_a2dp_disconnect_handler\n");

    return retval;
}
#else
API_RESULT se_profile_a2dp_disconnect_handler
           (
               void *    hparams
           )
{
    UINT32 state = 0, state_prev = 0;
    PROFILE_SESSION * profile_session;
    API_RESULT retval = 0;
    PROFILE_EVENT_INFO * param;
    param = (PROFILE_EVENT_INFO *)hparams;

    /* Get PROFILE session */
    profile_session = &multiprofile_inst[param->profile_fsm_handle];
    uint8_t a2dp_inst_curr = a2dp_find_a2dp_instance (param->data);
    uint8_t other_a2dp_index = a2dp_find_connected_a2dp_instance (a2dp_inst_curr);
    state = PROFILE_ACCESS_STATE(param->profile_fsm_handle);
	state_prev = state;

    if ( (param->event_info == PROFILE_FSM_REMOTE_EVENT) &&
    		(other_a2dp_index != PROFILE_INSTANCE_INVALID) &&
			(a2dp_appl_instance[other_a2dp_index].stream_state == APPL_A2DP_STREAM_TRUE) )
    {
    	/*a2dp disconneted, check if other role still streaming, stop streaming if true*/
    	UCHAR avrcp_index = appl_avrcp_get_connected_handle(a2dp_appl_instance[other_a2dp_index].bd_addr);
    	appl_avrcp_ct_send_passthrough_cmd_variables (avrcp_index, 1U, AVRCP_OPERATION_ID_PAUSE);
    }

    /* BD Address */
    BT_mem_copy
    (
        profile_session->bd_addr,
        (UCHAR*)param->data,
        BT_BD_ADDR_SIZE
    );

    /*disconnect avrcp*/
    appl_a2dp_avrcp_disconnect(a2dp_appl_instance[a2dp_inst_curr].bd_addr);
    /*reset a2dp codec instance*/
    a2dp_appl_connect_info_reset(a2dp_inst_curr);

    state |= SL_A2DP_STARTED;
    state &= ~ (SL_A2DP_CONNECTED | SL_A2DP_STREAM_STARTED);
    PROFILE_SET_STATE (param->profile_fsm_handle, state);
    printf ("[fsm]ev_pro_a2dp_disconnect[%d,%d], current-state:%08x, updated-state: %08X\n", param->event_type, param->event_info, state_prev,state);

    return retval;
}
#endif /*A2DP_BRIDGING*/

#ifndef A2DP_BRIDGING
API_RESULT se_profile_a2dp_start_handler
           (
               void *    hparams
           )
{
    UINT32 state;
    PROFILE_SESSION * profile_session;
    API_RESULT retval;

    PROFILE_EVENT_INFO * param;
    param = (PROFILE_EVENT_INFO *)hparams;

    state = 00U;
    retval = 0x00U;

    APPL_LOG (
    "[MULTI_PROFILE]: >>> se_profile_a2dp_start_handler\n");

    /* Get PROFILE session */
    profile_session = &multiprofile_inst[param->profile_fsm_handle];
    state = PROFILE_ACCESS_STATE(param->profile_fsm_handle);

    /* Initialize FSM state */
    state |= SL_A2DP_STREAM_STARTED;
    state &= ~(SL_A2DP_CONNECTED);

    /* Is local event? */
    if (PROFILE_FSM_LOCAL_EVENT == param->event_info)
    {
        APPL_LOG (
        "[MULTI_PROFILE]: se_profile_a2dp_start_handler PROFILE_FSM_LOCAL_EVENT\n");
    }
    else if (PROFILE_FSM_REMOTE_EVENT == param->event_info)
    {
        APPL_LOG (
        "[MULTI_PROFILE]: se_profile_a2dp_start_handler PROFILE_FSM_REMOTE_EVENT\n");
    }
    else
    {
        /* MISRA C-2012 Rule 15.7 */
    }
    /* BD Address */
    BT_mem_copy
    (
        profile_session->bd_addr,
        (UCHAR*)param->data,
        BT_BD_ADDR_SIZE
    );
    APPL_LOG("\t    " BT_DEVICE_ADDR_ONLY_FRMT_SPECIFIER "\n",
    BT_DEVICE_ADDR_ONLY_PRINT_STR (profile_session->bd_addr));

    printf ("[fsm]ev_pro_a2dp_start[%d,%d], current-state:%08x, updated-state: %08X\n", param->event_type, param->event_info, PROFILE_ACCESS_STATE(param->profile_fsm_handle),state);

    /* Update FSM State */
    PROFILE_SET_STATE (param->profile_fsm_handle, state);

    APPL_LOG (
    "[MULTI_PROFILE]: <<< se_profile_a2dp_start_handler\n");
    return retval;
}
#else
API_RESULT se_profile_a2dp_start_handler
           (
               void *    hparams
           )
{
    UINT32 state = 0, state_prev = 0;
    PROFILE_SESSION * profile_session;
    API_RESULT retval = 0;
    PROFILE_EVENT_INFO * param;
    param = (PROFILE_EVENT_INFO *)hparams;

    /* Get PROFILE session */
    profile_session = &multiprofile_inst[param->profile_fsm_handle];
    uint8_t a2dp_index = a2dp_find_a2dp_instance (param->data);
    state = PROFILE_ACCESS_STATE(param->profile_fsm_handle);
	state_prev = state;

    if ((param->event_info == PROFILE_FSM_REMOTE_EVENT) && (state & SL_HF_SCO_CONNECTED) )
    {
        printf ("[multi-profile]: hfp-sco-bridge is connected, a2dp-stream can't be started\n");

        if ( (a2dp_index != PROFILE_INSTANCE_INVALID) && (AVDTP_SEP_SINK == a2dp_appl_instance[a2dp_index].role))
        {
        	/*pause send to this link*/
            uint8_t avrcp_index = appl_avrcp_get_connected_handle(param->data);
            appl_avrcp_ct_send_passthrough_cmd_variables(avrcp_index, 1U, AVRCP_OPERATION_ID_PAUSE);
        }
    }
    else
    {
    	if (a2dp_index != PROFILE_INSTANCE_INVALID)
    	{
    		uint8_t other_a2dp_ins_index = a2dp_find_connected_a2dp_instance (a2dp_index);
    		if ( (other_a2dp_ins_index != PROFILE_INSTANCE_INVALID) &&
    				(a2dp_appl_instance[other_a2dp_ins_index].stream_state != APPL_A2DP_STREAM_TRUE) )
    		{
	            printf("[multi-profile] starting a2dp for other endpoint for a2dp-bridge\n");
	            retval = BT_a2dp_start( a2dp_appl_instance[other_a2dp_ins_index].a2dp_instance);

	            if (API_SUCCESS != retval)
	            {
	            	printf("BT_a2dp_start, failed with 0x%04X\n", retval);
	            }
	            else
	            {
	                UINT16 acl_handle;
	                printf("OK. Wait for A2DP_START_CNF\n");
	                /* Unsniff the link if required */
	                (BT_IGNORE_RETURN_VALUE)BT_hci_get_acl_connection_handle(a2dp_appl_instance[other_a2dp_ins_index].bd_addr, &acl_handle);
	                (BT_IGNORE_RETURN_VALUE)BT_hci_exit_sniff_mode(acl_handle);
	            }
    		}
    		else if ( (other_a2dp_ins_index != PROFILE_INSTANCE_INVALID) &&
    				(a2dp_appl_instance[other_a2dp_ins_index].stream_state == APPL_A2DP_STREAM_TRUE) )
    		{
    			/*both a2dp endpoints are in streaming state, update fsm now*/
    		    /* Initialize FSM state */
    		    state_prev = state;
    		    state |= SL_A2DP_STREAM_STARTED;
    		    state &= ~(SL_A2DP_CONNECTED);
    		    PROFILE_SET_STATE (param->profile_fsm_handle, state);
    		}
    		else
    		{
    			/**/
    		}

            if (APPL_A2DP_STREAM_FALSE == a2dp_appl_instance[a2dp_index].stream_state)
            {
                a2dp_appl_instance[a2dp_index].stream_state = APPL_A2DP_STREAM_TRUE;
            }
    	}
    }

    /* BD Address */
    BT_mem_copy
    (
        profile_session->bd_addr,
        (UCHAR*)param->data,
        BT_BD_ADDR_SIZE
    );

    printf ("[fsm]ev_pro_a2dp_start[%d,%d], current-state:%08x, updated-state: %08X\n", param->event_type, param->event_info, state_prev,state);
    /* Update FSM State */

    return retval;
}
#endif /*A2DP_BRIDGING*/

#ifndef A2DP_BRIDGING
API_RESULT se_profile_a2dp_suspend_handler
           (
               void *    hparams
           )
{
    UINT32 state;
    PROFILE_SESSION * profile_session;
    API_RESULT retval;

    PROFILE_EVENT_INFO * param;
    param = (PROFILE_EVENT_INFO *)hparams;

    state = 00U;
    retval = 0x00U;

    APPL_LOG (
    "[MULTI_PROFILE]: >>> se_profile_a2dp_suspend_handler\n");

    /* Get PROFILE session */
    profile_session = &multiprofile_inst[param->profile_fsm_handle];
    state = PROFILE_ACCESS_STATE(param->profile_fsm_handle);

    /* Initialize FSM state */
    state |= SL_A2DP_CONNECTED;
    state &= ~(SL_A2DP_STREAM_STARTED);

    /* Is local event? */
    if (PROFILE_FSM_LOCAL_EVENT == param->event_info)
    {
        APPL_LOG (
        "[MULTI_PROFILE]: se_profile_a2dp_suspend_handler PROFILE_FSM_LOCAL_EVENT\n");
    }
    else if (PROFILE_FSM_REMOTE_EVENT == param->event_info)
    {
        APPL_LOG (
        "[MULTI_PROFILE]: se_profile_a2dp_suspend_handler PROFILE_FSM_REMOTE_EVENT\n");
    }
    else
    {
        /* MISRA C-2012 Rule 15.7 */
    }
    /* BD Address */
    BT_mem_copy
    (
        profile_session->bd_addr,
        (UCHAR*)param->data,
        BT_BD_ADDR_SIZE
    );
    APPL_LOG("\t    " BT_DEVICE_ADDR_ONLY_FRMT_SPECIFIER "\n",
    BT_DEVICE_ADDR_ONLY_PRINT_STR (profile_session->bd_addr));
    printf ("[fsm]ev_pro_a2dp_suspend[%d,%d], current-state:%08x, updated-state: %08X\n", param->event_type, param->event_info, PROFILE_ACCESS_STATE(param->profile_fsm_handle),state);

    /* Update FSM State */
    PROFILE_SET_STATE (param->profile_fsm_handle, state);

    APPL_LOG (
    "[MULTI_PROFILE]: <<< se_profile_a2dp_suspend_handler\n");
    return retval;
}
#else
API_RESULT se_profile_a2dp_suspend_handler
           (
               void *    hparams
           )
{
    UINT32 state = 0, state_prev = 0;
    PROFILE_SESSION * profile_session;
    API_RESULT retval = 0;
    PROFILE_EVENT_INFO * param;
    param = (PROFILE_EVENT_INFO *)hparams;

    /* Get PROFILE session */
    profile_session = &multiprofile_inst[param->profile_fsm_handle];
    state = PROFILE_ACCESS_STATE(param->profile_fsm_handle);
    uint8_t a2dp_index_curr = a2dp_find_a2dp_instance (param->data);
    uint8_t a2dp_index = a2dp_find_connected_a2dp_instance (a2dp_index_curr);

	state_prev = state;

    if ( (a2dp_index != PROFILE_INSTANCE_INVALID) && (a2dp_appl_instance[a2dp_index].stream_state != APPL_A2DP_STREAM_FALSE))
    {
    	/*pause send to other a2dp link*/
    	printf ("a2dp-suspend send to other link\n");
		retval = BT_a2dp_suspend(a2dp_appl_instance[a2dp_index].a2dp_instance);

		if (API_SUCCESS != retval) {
			printf("BT_a2dp_suspend, failed with 0x%04X\n", retval);
		} else {
			printf("OK. Wait for A2DP_SUSPEND_CNF\n");
		}
    }
    else if ( (a2dp_index != PROFILE_INSTANCE_INVALID) && (a2dp_appl_instance[a2dp_index].stream_state == APPL_A2DP_STREAM_FALSE))
    {
    	/*both links are suspended now, update fsm*/
        /* Initialize FSM state */
        state |= SL_A2DP_CONNECTED;
        state &= ~(SL_A2DP_STREAM_STARTED);
        PROFILE_SET_STATE (param->profile_fsm_handle, state);
    }
    else
    {
    	/**/
    }

    /* BD Address */
    BT_mem_copy
    (
        profile_session->bd_addr,
        (UCHAR*)param->data,
        BT_BD_ADDR_SIZE
    );

	if (APPL_A2DP_STREAM_TRUE == a2dp_appl_instance[a2dp_index_curr].stream_state)
    {
        a2dp_appl_instance[a2dp_index_curr].stream_state = APPL_A2DP_STREAM_FALSE;
    }

    printf ("[fsm]ev_pro_a2dp_suspend[%d,%d], current-state:%08x, updated-state: %08X\n", param->event_type, param->event_info, state_prev,state);
    /* Update FSM State */

    return retval;
}
#endif /*A2DP_BRIDGING*/

API_RESULT se_profile_a2dp_stop_handler
           (
               void *    hparams
           )
{
    UINT32 state;
    PROFILE_SESSION * profile_session;
    API_RESULT retval;

    PROFILE_EVENT_INFO * param;
    param = (PROFILE_EVENT_INFO *)hparams;

    APPL_LOG (
    "[MULTI_PROFILE]: >>> se_profile_a2dp_stop_handler\n");

    state = 00U;
    retval = 0x00U;

    /* Get PROFILE session */
    profile_session = &multiprofile_inst[param->profile_fsm_handle];
    state = PROFILE_ACCESS_STATE(param->profile_fsm_handle);

    /* Initialize FSM state */
    state |= SL_A2DP_CONNECTED;
    state &= ~(SL_A2DP_STREAM_STARTED);

    /* Is local event? */
    if (PROFILE_FSM_LOCAL_EVENT == param->event_info)
    {
        APPL_LOG (
        "[MULTI_PROFILE]: se_profile_a2dp_stop_handler PROFILE_FSM_LOCAL_EVENT\n");
    }
    else if (PROFILE_FSM_REMOTE_EVENT == param->event_info)
    {
        APPL_LOG (
        "[MULTI_PROFILE]: se_profile_a2dp_stop_handler PROFILE_FSM_REMOTE_EVENT\n");
    }
    else
    {
        /* MISRA C-2012 Rule 15.7 */
    }
    /* BD Address */
    BT_mem_copy
    (
        profile_session->bd_addr,
        (UCHAR*)param->data,
        BT_BD_ADDR_SIZE
    );
    APPL_LOG("\t    " BT_DEVICE_ADDR_ONLY_FRMT_SPECIFIER "\n",
    BT_DEVICE_ADDR_ONLY_PRINT_STR (profile_session->bd_addr));
    printf ("[fsm]ev_pro_a2dp_stop[%d,%d], current-state:%08x, updated-state: %08X\n", param->event_type, param->event_info, PROFILE_ACCESS_STATE(param->profile_fsm_handle),state);

    /* Update FSM State */
    PROFILE_SET_STATE (param->profile_fsm_handle, state);

    APPL_LOG (
    "[MULTI_PROFILE]: <<< se_profile_a2dp_stop_handler\n");
    return retval;
}

API_RESULT se_profile_hf_connect_handler
           (
               void *    hparams
           )
{
    UINT32 state;
    PROFILE_SESSION * profile_session;
    API_RESULT retval;

    PROFILE_EVENT_INFO * param;
    param = (PROFILE_EVENT_INFO *)hparams;

    APPL_LOG (
    "[MULTI_PROFILE]: >>> se_profile_hf_connect_handler\n");

    state = 00U;
    retval = 0x00U;

    /* Get PROFILE session */
    profile_session = &multiprofile_inst[param->profile_fsm_handle];
    state = PROFILE_ACCESS_STATE(param->profile_fsm_handle);

    /* Initialize FSM state */
    state |= SL_HF_CONNECTED;
    state &= ~(SL_HF_STARTED);

    /* Is local event? */
    if (PROFILE_FSM_LOCAL_EVENT == param->event_info)
    {
        APPL_LOG (
        "[MULTI_PROFILE]: se_profile_hf_connect_handler PROFILE_FSM_LOCAL_EVENT\n");
    }
    else if (PROFILE_FSM_REMOTE_EVENT == param->event_info)
    {
        APPL_LOG (
        "[MULTI_PROFILE]: se_profile_hf_connect_handler PROFILE_FSM_REMOTE_EVENT\n");
    }
    else
    {
        /* MISRA C-2012 Rule 15.7 */
    }
    /* BD Address */
    BT_mem_copy
    (
        profile_session->bd_addr,
        (UCHAR*)param->data,
        BT_BD_ADDR_SIZE
    );

    printf ("[fsm]ev_pro_hfp_connect[%d,%d], current-state:%08x, updated-state: %08X\n", param->event_type, param->event_info, PROFILE_ACCESS_STATE(param->profile_fsm_handle),state);
    /* Update FSM State */
    PROFILE_SET_STATE (param->profile_fsm_handle, state);

    APPL_LOG (
    "[MULTI_PROFILE]: <<< se_profile_hf_connect_handler\n");
    return retval;
}

API_RESULT se_profile_hf_disconnect_handler
           (
               void *    hparams
           )
{
    UINT32 state;
    PROFILE_SESSION * profile_session;
    API_RESULT retval;
    UINT8 sep_type;
    UCHAR avrcp_index;

    PROFILE_EVENT_INFO * param;
    param = (PROFILE_EVENT_INFO *)hparams;

    APPL_LOG (
    "[MULTI_PROFILE]: >>> se_profile_hf_disconnect_handler\n");

    sep_type = 0xFF;
    state = 00U;
    retval = 0x00U;
    avrcp_index = 0U;

    /* Get PROFILE session */
    profile_session = &multiprofile_inst[param->profile_fsm_handle];
    state = PROFILE_ACCESS_STATE(param->profile_fsm_handle);

    if (state & SL_A2DP_SUSPEND_ON_SCO)
    {
#ifdef A2DP_BRIDGING
    	a2dp_idx_suspended = a2dp_find_codec_sink_instance(&sep_type);
#else
        sep_type = appl_a2dp_get_sep_type();
#endif /*A2DP_BRIDGING*/
        if (AVDTP_SEP_SOURCE == sep_type)
        {
            retval = BT_a2dp_start
                     (
                         a2dp_appl_instance[a2dp_idx_suspended].a2dp_instance
                     );
        }
        else if (AVDTP_SEP_SINK == sep_type)
        {
            avrcp_index = appl_avrcp_get_connected_handle(bd_addr);
            appl_avrcp_ct_send_passthrough_cmd_variables (avrcp_index, 1U, AVRCP_OPERATION_ID_PLAY);
        }
        state |= (SL_HF_STARTED | SL_A2DP_STREAM_STARTED);
    }
    else
    {
        state |= SL_HF_STARTED;
    }
    state &= ~(SL_HF_CONNECTED);

    /* Is local event? */
    if (PROFILE_FSM_LOCAL_EVENT == param->event_info)
    {
        APPL_LOG (
        "[MULTI_PROFILE]: se_profile_hf_disconnect_handler PROFILE_FSM_LOCAL_EVENT\n");
    }
    else if (PROFILE_FSM_REMOTE_EVENT == param->event_info)
    {
        APPL_LOG (
        "[MULTI_PROFILE]: se_profile_hf_disconnect_handler PROFILE_FSM_REMOTE_EVENT\n");
    }
    else
    {
        /* MISRA C-2012 Rule 15.7 */
    }
    /* BD Address */
    BT_mem_copy
    (
        profile_session->bd_addr,
        (UCHAR*)param->data,
        BT_BD_ADDR_SIZE
    );

    printf ("[fsm]ev_pro_hfp_disconnect[%d,%d], current-state:%08x, updated-state: %08X\n", param->event_type, param->event_info, PROFILE_ACCESS_STATE(param->profile_fsm_handle),state);
    /* Update FSM State */
    PROFILE_SET_STATE (param->profile_fsm_handle, state);

    APPL_LOG (
    "[MULTI_PROFILE]: <<< se_profile_hf_disconnect_handler\n");
    return retval;
}

API_RESULT se_profile_hf_sco_connect_handler
           (
               void *    hparams
           )
{
    UINT32 state;
    PROFILE_SESSION * profile_session;
    API_RESULT retval;
    UCHAR avrcp_index, a2dp_index;
    UCHAR sep_type;

    PROFILE_EVENT_INFO * param;
    param = (PROFILE_EVENT_INFO *)hparams;

    state = 00U;
    retval = 0x00U;
    avrcp_index = 0U;
    a2dp_index = 0U;

    APPL_LOG (
    "[MULTI_PROFILE]: >>> se_profile_hf_sco_connect_handler\n");

    /* Get PROFILE session */
    profile_session = &multiprofile_inst[param->profile_fsm_handle];
    state = PROFILE_ACCESS_STATE(param->profile_fsm_handle);

    if (BT_TRUE == (API_RESULT)appl_a2dp_is_streaming(&a2dp_index, bd_addr))
    {
        APPL_LOG("\t    " BT_DEVICE_ADDR_ONLY_FRMT_SPECIFIER "\n",
        BT_DEVICE_ADDR_ONLY_PRINT_STR (bd_addr));
        a2dp_idx_suspended = a2dp_index;
        sep_type = a2dp_appl_instance[a2dp_idx_suspended].role;
        if (AVDTP_SEP_SOURCE == sep_type)
        {
            retval = BT_a2dp_suspend
                     (
                         a2dp_appl_instance[a2dp_idx_suspended].a2dp_instance
                     );
        }
        else if (AVDTP_SEP_SINK == sep_type)
        {
            avrcp_index = appl_avrcp_get_connected_handle((UCHAR*)bd_addr);
            appl_avrcp_ct_send_passthrough_cmd_variables(avrcp_index, 1U, AVRCP_OPERATION_ID_PAUSE);
        }

        /* Initialize FSM state */
        state |= (SL_HF_SCO_CONNECTED | SL_A2DP_SUSPEND_ON_SCO);
        state &= ~(SL_HF_CONNECTED);
    }
    else
    {
        /* Initialize FSM state */
        state |= SL_HF_SCO_CONNECTED;
        state &= ~(SL_HF_CONNECTED | SL_A2DP_SUSPEND_ON_SCO);
    }

    /* Is local event? */
    if (PROFILE_FSM_LOCAL_EVENT == param->event_info)
    {
        APPL_LOG (
        "[MULTI_PROFILE]: se_profile_hf_sco_connect_handler PROFILE_FSM_LOCAL_EVENT\n");
    }
    else if (PROFILE_FSM_REMOTE_EVENT == param->event_info)
    {
        APPL_LOG (
        "[MULTI_PROFILE]: se_profile_hf_disconnect_handler PROFILE_FSM_REMOTE_EVENT\n");
    }
    else
    {
        /* MISRA C-2012 Rule 15.7 */
    }
    /* BD Address */
    BT_mem_copy
    (
        profile_session->bd_addr,
        (UCHAR*)param->data,
        BT_BD_ADDR_SIZE
    );

    printf ("[fsm]ev_pro_hfp_sco_connect[%d,%d], current-state:%08x, updated-state: %08X\n", param->event_type, param->event_info, PROFILE_ACCESS_STATE(param->profile_fsm_handle),state);

    /* Update FSM State */
    PROFILE_SET_STATE (param->profile_fsm_handle, state);

    APPL_LOG (
    "[MULTI_PROFILE]: <<< se_profile_hf_sco_connect_handler\n");
    return retval;
}

API_RESULT se_profile_hf_sco_disconnect_handler
           (
               void *    hparams
           )
{
    UINT32 state;
    PROFILE_SESSION * profile_session;
    API_RESULT retval;
    UINT8 sep_type = 0xFF;
    UCHAR avrcp_index;

    PROFILE_EVENT_INFO * param;
    param = (PROFILE_EVENT_INFO *)hparams;

    state = 00U;
    retval = 0x00U;

    avrcp_index = 0U;
    APPL_LOG (
    "[MULTI_PROFILE]: >>> se_profile_hf_sco_disconnect_handler\n");

    /* Get PROFILE session */
    profile_session = &multiprofile_inst[param->profile_fsm_handle];
    profile_access_state_handler(param,  &state);

    if (state & SL_A2DP_SUSPEND_ON_SCO)
    {
#ifdef A2DP_BRIDGING
    	a2dp_idx_suspended = a2dp_find_codec_sink_instance(&sep_type);
#else
        sep_type = appl_a2dp_get_sep_type();
#endif /*A2DP_BRIDGING*/
        if (AVDTP_SEP_SOURCE == sep_type)
        {
            retval = BT_a2dp_start
                     (
                         a2dp_appl_instance[a2dp_idx_suspended].a2dp_instance
                     );
        }
        else if (AVDTP_SEP_SINK == sep_type)
        {
        	avrcp_index = appl_avrcp_get_connected_handle(bd_addr);
        	appl_avrcp_ct_send_passthrough_cmd_variables (avrcp_index, 1U, AVRCP_OPERATION_ID_PLAY);
        }
        state |= (SL_HF_CONNECTED | SL_A2DP_STREAM_STARTED);
    }
    else
    {
        state |= SL_HF_CONNECTED;
    }
    state &= ~(SL_HF_SCO_CONNECTED | SL_A2DP_SUSPEND_ON_SCO);

    /* Is local event? */
    if (PROFILE_FSM_LOCAL_EVENT == param->event_info)
    {
        APPL_LOG (
        "[MULTI_PROFILE]: se_profile_hf_sco_disconnect_handler PROFILE_FSM_LOCAL_EVENT\n");
    }
    else if (PROFILE_FSM_REMOTE_EVENT == param->event_info)
    {
        APPL_LOG (
        "[MULTI_PROFILE]: se_profile_hf_sco_disconnect_handler PROFILE_FSM_REMOTE_EVENT\n");
    }
    else
    {
        /* MISRA C-2012 Rule 15.7 */
    }
    /* BD Address */
    BT_mem_copy
    (
        profile_session->bd_addr,
        (UCHAR*)param->data,
        BT_BD_ADDR_SIZE
    );

    printf ("[fsm]ev_pro_hfp_sco_disconnect[%d,%d], current-state:%08x, updated-state: %08X\n", param->event_type, param->event_info, PROFILE_ACCESS_STATE(param->profile_fsm_handle),state);

    /* Update FSM State */
    PROFILE_SET_STATE (param->profile_fsm_handle, state);

    APPL_LOG (
    "[MULTI_PROFILE]: <<< se_profile_hf_sco_disconnect_handler\n");
    return retval;
}

#ifndef AVRCP_BRIDGING
API_RESULT se_profile_avrcp_connect_handler(void * hparams)
{
	UINT32 state;
	PROFILE_SESSION * profile_session;
	API_RESULT retval;
    UINT8 index;
	PROFILE_EVENT_INFO * param;
	param = (PROFILE_EVENT_INFO *)hparams;

	APPL_LOG (
	"[MULTI_PROFILE]: >>> se_profile_avrcp_connect_handler\n");

	state = 00U;
	retval = 0x00U;

	/* Get PROFILE session */
	profile_session = &multiprofile_inst[param->profile_fsm_handle];
    index = avrcp_find_avrcp_instance(param->data);
	printf("Control Channel Successfully Started with index %d\n", index);
	if (BT_TRUE == appl_avrcp_is_browsing_supported() )
	{
		printf("Starting AVRCP Browsing Channel Connect ... "); fflush(stdout);
		BT_avrcp_al_channel_connect_req
		(
			&appl_avrcp_handle[index],
			param->data,
			AVCTP_CHANNEL_TYPE_BROWSING
		);
	}
	state = PROFILE_ACCESS_STATE(param->profile_fsm_handle);

	/* Initialize FSM state */
	state |=  SL_AVRCP_CONNECTED;
	state &= ~(SL_AVRCP_STARTED);

	/* Is local event? */
	if (PROFILE_FSM_LOCAL_EVENT == param->event_info)
	{
		APPL_LOG (
		"[MULTI_PROFILE]: PROFILE_FSM_LOCAL_EVENT\n");
	}
	else if (PROFILE_FSM_REMOTE_EVENT == param->event_info)
	{
		APPL_LOG (
		"[MULTI_PROFILE]: PROFILE_FSM_REMOTE_EVENT\n");

	}
	else
	{
		/* MISRA C-2012 Rule 15.7 */
	}
	/* BD Address */
	BT_mem_copy
	(
		profile_session->bd_addr,
		(UCHAR*)param->data,
		BT_BD_ADDR_SIZE
	);
	APPL_LOG("\t    " BT_DEVICE_ADDR_ONLY_FRMT_SPECIFIER "\n",
	BT_DEVICE_ADDR_ONLY_PRINT_STR (profile_session->bd_addr));

	printf ("[fsm]ev_pro_avrcp_connect[%d,%d], current-state:%08x, updated-state: %08X\n", param->event_type, param->event_info, PROFILE_ACCESS_STATE(param->profile_fsm_handle),state);

	/* Update FSM State */
	PROFILE_SET_STATE (param->profile_fsm_handle, state);

	APPL_LOG (
	"[MULTI_PROFILE]: <<< se_profile_avrcp_connect_handler\n");

	return retval;
}
#else /* AVRCP_BRIDGING */
API_RESULT se_profile_avrcp_connect_handler
           (
               void    * hparams
           )
{
    UINT32 state = 0, state_prev = 0;
    API_RESULT retval = 0;
    UCHAR appl_avrcp_sep_flag;
    PROFILE_EVENT_INFO * param;
    param = (PROFILE_EVENT_INFO *)hparams;

    uint8_t current_avrcp_inst = avrcp_find_avrcp_instance (param->data);
    uint8_t sec_avrcp_index = avrcp_find_second_avrcp_instance (current_avrcp_inst);

    state = PROFILE_ACCESS_STATE(param->profile_fsm_handle);
    state_prev = state;

    if (current_avrcp_inst != PROFILE_INSTANCE_INVALID)
    {
		printf("\nControl Channel Successfully Started with index %d\n", current_avrcp_inst);
		/* start browsing channel connect */
		if (BT_TRUE == appl_avrcp_is_browsing_supported() )
		{
			printf("Starting AVRCP Browsing Channel Connect ... "); fflush(stdout);
			BT_avrcp_al_channel_connect_req
			(
				&appl_avrcp_handle[current_avrcp_inst],
				param->data,
				AVCTP_CHANNEL_TYPE_BROWSING
			);
		}
		appl_avrcp_sep_flag = appl_get_sep_to_register_notification();
	    /* register headset/speaker for notification */
	    if(appl_avrcp_sep_flag == AVDTP_SEP_SOURCE)
	    {
			retval = BT_avrcp_al_register_notification
					(
						&appl_avrcp_handle[current_avrcp_inst],
						0x0D,
						0
					);
			printf("\n Registered for the notification : %d\n",retval);
	    }
	    /* starting SDP for HFP only if the AVRCP connection is started locally, for ind - not calling here */
	    if(param->event_info != PROFILE_FSM_REMOTE_EVENT)
	    {
		   if(appl_avrcp_sep_flag == AVDTP_SEP_SOURCE)
		   {
				/*TODO: currently there is only one unit that can be connected, hence not checking the address*/
				if(BT_FALSE == appl_hfpag_is_ag_connected())
				{
					/* Initiate connection to unit if already not connected */
					appl_get_hfag_sdp_record(param->data);
				}
				else
				{
					printf("Unit already connected, not initiating connection again\n");
				}
		   }
		   else
		   {
				/*TODO: currently there is only one ag that can be connected, hence not checking the address*/
				if(BT_FALSE == appl_hfpunit_is_unit_connected())
				{
				   /* Initiate connection to AG if already not connected */
				   printf("Initiating Profile Connection to AG\n");
				   appl_get_hfunit_sdp_record(param->data);
				}
				else
				{
				   printf("AG already connected, not initiating connection again");
				}
		   }
	   }
	   /* Initialize FSM state */
	   if(PROFILE_INSTANCE_INVALID != sec_avrcp_index)
	   {
		   state |=  SL_AVRCP_CONNECTED;
		   state &= ~(SL_AVRCP_STARTED);
	   }
	   PROFILE_SET_STATE (param->profile_fsm_handle, state);
	   printf ("[fsm]ev_pro_avrcp_connect[%d,%d], current-state:%08x, updated-state: %08X\n", param->event_type, param->event_info, state_prev,state);
    }


    return retval;
}
#endif /*A2DP_BRIDGING*/

#ifndef AVRCP_BRIDGING
API_RESULT se_profile_avrcp_disconnect_handler
           (
               void *    hparams
           )
{
    UINT32 state;
    PROFILE_SESSION * profile_session;
    API_RESULT retval;
    PROFILE_EVENT_INFO* param;

    param = (PROFILE_EVENT_INFO *)hparams;

    state = 00U;
    retval = 0x00U;

    APPL_LOG (
    "[MULTI_PROFILE]: >>> se_profile_avrcp_disconnect_handler\n");

    /* Get PROFILE session */
    profile_session = &multiprofile_inst[param->profile_fsm_handle];
    state = PROFILE_ACCESS_STATE(param->profile_fsm_handle);

    /* Initialize FSM state */
    state |= SL_AVRCP_STARTED ;
    state &= ~(SL_AVRCP_CONNECTED);

    APPL_LOG (
     "[PROFILE_FSM_HANDLER]: state  %02X \n", state);

    /* Is local event? */
    if (PROFILE_FSM_LOCAL_EVENT == param->event_info)
    {
        APPL_LOG (
        "[MULTI_PROFILE]: se_profile_avrcpp_disconnect_handler PROFILE_FSM_LOCAL_EVENT\n");
    }
    else if (PROFILE_FSM_REMOTE_EVENT == param->event_info)
    {
        APPL_LOG (
        "[MULTI_PROFILE]: se_profile_avrcp_disconnect_handler PROFILE_FSM_REMOTE_EVENT\n");
    }
    else
    {
        /* MISRA C-2012 Rule 15.7 */
    }
    /* BD Address */
    BT_mem_copy
    (
        profile_session->bd_addr,
        (UCHAR*)param->data,
        BT_BD_ADDR_SIZE
    );
    APPL_LOG("\t    " BT_DEVICE_ADDR_ONLY_FRMT_SPECIFIER "\n",
    BT_DEVICE_ADDR_ONLY_PRINT_STR (profile_session->bd_addr));

    printf ("[fsm]ev_pro_avrcp_disconnect[%d,%d], current-state:%08x, updated-state: %08X\n", param->event_type, param->event_info, PROFILE_ACCESS_STATE(param->profile_fsm_handle),state);

    /* Update FSM State */
    PROFILE_SET_STATE (param->profile_fsm_handle, state);

    APPL_LOG (
    "[MULTI_PROFILE]: <<< se_profile_avrcp_disconnect_handler\n");

    return retval;
}
#else /* AVRCP_BRIDGING */
API_RESULT se_profile_avrcp_disconnect_handler
           (
               void *    hparams
           )
{
       UINT32 state = 0, state_prev = 0;
       API_RESULT retval = 0;
       PROFILE_EVENT_INFO * param;
       param = (PROFILE_EVENT_INFO *)hparams;

       uint8_t avrcp_inst_curr = avrcp_find_avrcp_instance (param->data);
       uint8_t sec_avrcp_index = avrcp_find_second_avrcp_instance (avrcp_inst_curr);
       state = PROFILE_ACCESS_STATE(param->profile_fsm_handle);
   	   state_prev = state;

       if ((param->event_info == PROFILE_FSM_LOCAL_EVENT) && (sec_avrcp_index == PROFILE_INSTANCE_INVALID))
       {
    	   state |= SL_AVRCP_STARTED;
    	   state &= ~ SL_AVRCP_CONNECTED;
       }
       PROFILE_SET_STATE (param->profile_fsm_handle, state);
       printf ("[fsm]ev_pro_avrcp_disconnect[%d,%d], current-state:%08x, updated-state: %08X\n", param->event_type, param->event_info, state_prev,state);

       return retval;
}
#endif /* AVCRP_BRIDGING */
#ifndef AVRCP_BRIDGING
API_RESULT se_profile_avrcp_sdp_completed_handler
           (
               void *    hparams
           )
{
	   UINT32 state = 0, state_prev = 0;
	   PROFILE_SESSION * profile_session;
	   API_RESULT retval = 0;
	   PROFILE_EVENT_INFO * param;
	   param = (PROFILE_EVENT_INFO *)hparams;

	   /* Get PROFILE session */
	   profile_session = &multiprofile_inst[param->profile_fsm_handle];
	   state = PROFILE_ACCESS_STATE(param->profile_fsm_handle);
	   state_prev = state;
	   printf ("[fsm]ev_pro_avrcp_sdp_completed[%d,%d], current-state:%08x, updated-state: %08X\n", param->event_type, param->event_info, state_prev,state);
        appl_a2dp_avrcp_connect(param->data);
	   return retval;
}
#else /* AVRCP_BRIDGING */
API_RESULT se_profile_avrcp_sdp_completed_handler
           (
               void *    hparams
           )
{
	   printf("\n SDP fsm handler called \n");
	   UINT32 state = 0, state_prev = 0;
	   API_RESULT retval = 0;
	   PROFILE_EVENT_INFO * param;
	   param = (PROFILE_EVENT_INFO *)hparams;

	   state = PROFILE_ACCESS_STATE(param->profile_fsm_handle);
	   state_prev = state;
	   printf ("[fsm]ev_pro_avrcp_sdp_completed[%d,%d], current-state:%08x, updated-state: %08X\n", param->event_type, param->event_info, state_prev,state);
	   appl_a2dp_avrcp_connect(param->data);
	   return retval;
}
#endif /* AVRCP_BRIDGING */

#ifndef AVRCP_BRIDGING
API_RESULT se_profile_avrcp_msg_ind_handler
           (
        	  void * hparams
		   )
{
	   printf("\n avrcp_msg_ind_handler() \n");
	   UINT32 state = 0, state_prev = 0;
	   PROFILE_SESSION * profile_session;
	   API_RESULT retval = 0;
	   PROFILE_EVENT_INFO * param;
	   param = (PROFILE_EVENT_INFO *)hparams;
	   /* Get PROFILE session */
	   profile_session = &multiprofile_inst[param->profile_fsm_handle];
	   state = PROFILE_ACCESS_STATE(param->profile_fsm_handle);
	   state_prev = state;
	   printf ("[fsm]ev_pro_avrcp_msg_ind[%d,%d], current-state:%08x, updated-state: %08X\n", param->event_type, param->event_info, state_prev,state);
       return retval;
}
#else /*AVRCP_BRIDGING */
API_RESULT se_profile_avrcp_msg_ind_handler
           (
        	  void * hparams
		   )
{
	   printf("\n avrcp_msg_ind_handler() \n");
	   UINT32 state = 0, state_prev = 0;
	   API_RESULT retval = 0;
	   PROFILE_EVENT_INFO * param;
	   param = (PROFILE_EVENT_INFO *)hparams;
	   uint8_t current_avrcp_inst = avrcp_find_avrcp_instance (param->data);
	   state = PROFILE_ACCESS_STATE(param->profile_fsm_handle);
	   state_prev = state;
	   printf ("[fsm]ev_pro_avrcp_msg_ind[%d,%d], current-state:%08x, updated-state: %08X\n", param->event_type, param->event_info, state_prev,state);
	   retval = appl_handle_avrcp_bridging_cmd_ind(current_avrcp_inst);
	   printf("\n retval = %d \n",retval);
	return retval;
}
#endif /* AVRCP_BRIDGING */

#ifndef AVRCP_BRIDGING
API_RESULT se_profile_avrcp_msg_rsp_handler
           (
        	   void * hparams
		   )
{
   printf("\n avrcp_msg_rsp_handler() \n");
   UINT32 state = 0, state_prev = 0;
   PROFILE_SESSION * profile_session;
   API_RESULT retval = 0;
   PROFILE_EVENT_INFO * param;
   param = (PROFILE_EVENT_INFO *)hparams;
   /* Get PROFILE session */
   profile_session = &multiprofile_inst[param->profile_fsm_handle];
   state = PROFILE_ACCESS_STATE(param->profile_fsm_handle);
   state_prev = state;
   printf ("[fsm]ev_pro_avrcp_msg_cnf[%d,%d], current-state:%08x, updated-state: %08X\n", param->event_type, param->event_info, state_prev,state);
   return;
}
#else /* AVRCP_BRIDGING */
API_RESULT se_profile_avrcp_msg_rsp_handler
           (
        	   void * hparams
		   )
{
	printf("\n avrcp_msg_rsp_handler() \n");
		   UINT32 state = 0, state_prev = 0;
		   API_RESULT retval = 0;
		   PROFILE_EVENT_INFO * param;
		   param = (PROFILE_EVENT_INFO *)hparams;
		   uint8_t current_avrcp_inst = avrcp_find_avrcp_instance (param->data);
		   state = PROFILE_ACCESS_STATE(param->profile_fsm_handle);
		   state_prev = state;
		   printf ("[fsm]ev_pro_avrcp_msg_cnf[%d,%d], current-state:%08x, updated-state: %08X\n", param->event_type, param->event_info, state_prev,state);
		   appl_handle_avrcp_bridging_cmd_rsp(current_avrcp_inst);

	   return retval;
}
#endif /* AVRCP_BRIDGING */
#endif /* MULTI_PROFILE_FSM_SUPPORT */
