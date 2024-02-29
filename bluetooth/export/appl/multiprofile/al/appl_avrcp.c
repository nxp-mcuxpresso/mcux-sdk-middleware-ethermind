
/**
 *  \file appl_avrcp.c
 *
 *  Source file for AVRCP command line applicaiton for both CT & TG roles.
 */

/*
 *  Copyright (C) 2013. Mindtree Ltd.
 *  All rights reserved.
 */

/* ----------------------------------------- Header File Inclusion */
#include "appl_a2dp.h"
#include "appl_avrcp.h"
#include "appl_avrcp_ct.h"
#include "appl_avrcp_tg.h"
#include "appl_common.h"
#include "appl_utils.h"

#ifdef AVRCP_BRIDGING
#include "appl_hfp_ag.h"
#include "appl_hfp_unit.h"
#endif

#if (defined AVRCP_CT || defined AVRCP_TG)
/* ----------------------------------------- External Global Variables */

/* ----------------------------------------- Exported Global Variables */

/* ----------------------------------------- Static Global Variables */

/* SDP Attribute data size */
#define SDP_ATTRIB_DATALEN        1024

/* Supported browsing feature bit set */
#define APPL_AVRCP_BROWSING_FEATURE_SUPPORT  0x40U

/* SDP Application Handle */
static SDP_HANDLE appl_sdp_handle;

/* SDP Attribute Data */
static UCHAR appl_sdp_attrib_data[SDP_ATTRIB_DATALEN];

/* SDP Attribute Datalen */
static UINT16 appl_sdp_attrib_datalen;

/* Flag to check browsing channel support */
static UINT8 appl_avrcp_browsing_support = BT_TRUE;


/* Main AVRCP Application Menu */
static const char avrcp_main_menu[] = " \n\
--------------- AVRCP Menu ---------------------- \n\n\
  0.  Exit. \n\
  1.  Refresh. \n\
 \n\
  2.  AVRCP Initialize. \n\
  3.  AVRCP Shutdown. \n\
 \n\
  4.  AVRCP Start Instance. \n\
  5.  AVRCP Stop Instance. \n\
 \n\
  6.  AVRCP Show Handle. \n\
 \n\
  7.  Register Peer BD Addrs. \n\
  8.  Get Registered Peer BD Addrs. \n\
  \n\
 10.  Create ACL Connection. \n\
 11.  Disconnect ACL connection.\n\
 \n\
 12.  AVRCP Control Channel Connect. \n\
 13.  AVRCP Control Channel Disconnect. \n\
 \n\
 14.  AVRCP Browsing Channel Connect.\n\
 15.  AVRCP Browsing Channel Disconnect.\n\
 \n\
 16.  AVRCP Controller Operations.\n\
 17.  AVRCP Target Operations.\n\
 \n\
Your Option -> ";

/* AVRCP Handles */
extern AVRCP_HANDLE appl_avrcp_handle [AVRCP_MAX_PROFILES];
static UCHAR first_time = 0x0U;

/* HCI ACL Connection List */
extern HCI_CONNECTION_LIST appl_avrcp_acl_list [BT_MAX_REMOTE_DEVICES];

/* AVRCP Peer BD Address */
UCHAR appl_avrcp_bd_addr[BT_BD_ADDR_SIZE];

/* Peer bluetooth device address to connect to */
extern UCHAR appl_peer_bd_addr[BT_BD_ADDR_SIZE];

#ifdef AVRCP_CT
extern AVRCP_AL_GET_FOLDER_ITEMS_PARAM get_folder_items_param;
#endif /* AVRCP_CT */
#ifdef AVRCP_BRIDGING
DECL_STATIC AVRCP_AL_CT_CMD_INFO *appl_event_recvd = NULL;
DECL_STATIC AVRCP_AL_VD_CMD_INFO  *appl_vendor_event_recvd = NULL;
DECL_STATIC AVRCP_AL_CT_RSP_INFO *appl_avrcp_recvd_cnf = NULL;
#endif /* AVRCP_BRIDGING */

/* ----------------------------------------- Functions */

void main_avrcp_operations (void)
{
    int choice, menu_choice, read_val;
    UINT16 connection_handle;
    API_RESULT retval;

    if (first_time == 0x0U)
    {
        first_time = 1U;
        appl_avrcp_init_handles();
    }

    BT_LOOP_FOREVER()
    {
        printf ("%s", avrcp_main_menu);
        scanf("%d", &choice);
        menu_choice = choice;

        switch(choice)
        {
        case 0:
            break; /* return; */

        case 1:
            break;

        case 2:
            /* Init */
            appl_avrcp_init ();
            break;

        case 3:
            /* Shutdown */
            appl_avrcp_shutdown ();
            break;

        case 4:
            /* Start */
            appl_avrcp_start ();
            break;

        case 5:
            /* Stop */
            appl_avrcp_stop ();
            break;

        case 6:
            appl_avrcp_show_handles();
            break;

        case 7:

            /* Register Peer BD address */
             printf("Enter Peer BD Address:");
             appl_get_bd_addr(appl_avrcp_bd_addr);

            /* BT_mem_copy(appl_avrcp_bd_addr, bd_addr, BT_BD_ADDR_SIZE);  */
            break;

        case 8:

            /* Get Registered BD_ADDR of Peer Device */
            printf("\nRegistered Peer BD "\
            BT_DEVICE_ADDR_ONLY_FRMT_SPECIFIER "\n",
            BT_DEVICE_ADDR_ONLY_PRINT_STR(appl_avrcp_bd_addr));
            break;

        case 10:
            /**
             * First Application should establish ACL Connection with
             * the peer Device
             */
            retval = BT_hci_create_connection
                     (
                         appl_avrcp_bd_addr,
                         LMP_ACL_DH5,
                         0x0U, 0x0U, 0x0U, 0x1U
                     );
            if (API_SUCCESS != retval)
            {
                printf("HCI Connect Attempt FAILED !! Error Code = 0x%04X\n",
                retval);
            }
            break;

        case 11:

            /* To disconnect read the ACL Connection Handle */
            printf("Enter Connection Handle (in Hex) = "); fflush(stdout);
            scanf("%x", &read_val);
            connection_handle = (UINT16)read_val;

            printf("\n");
            printf("Starting HCI Disconnection ... "); fflush(stdout);

            /* Mention Reason for Disconnect as User Initiated Disconnection */
            retval = BT_hci_disconnect ( connection_handle, 0x13U );
            if (API_SUCCESS != retval)
            {
                printf("HCI Disconnection FAILED !! Error Code = 0x%04X\n",
                retval);
            }
            break;

        case 12:
            /* Control Channel Connect */
            appl_avrcp_ctl_ch_connect_req ();
            break;

        case 13:
            /* Control Channel Disconnect */
            appl_avrcp_ctl_ch_disconnect_req ();
            break;

        case 14:
            /* Browsing Channel Connect */
            appl_avrcp_brow_ch_connect_req ();
            break;

        case 15:
            /* Browsing Channel Disconnect */
            appl_avrcp_brow_ch_disconnect_req ();
            break;

        case 16:
#ifdef AVRCP_CT
            /* AVRCP Controller operations */
            main_avrcp_ct_operations ();
#else
            printf ("AVRCP_CT flag is not defined\n");
#endif /* AVRCP_CT */
            break;

        case 17:
#ifdef AVRCP_TG
            /* AVRCP Target operations */
            main_avrcp_tg_operations ();
#else
            printf ("AVRCP_TG flag is not defined\n");
#endif /* AVRCP_TG */
            break;

        default:
            printf ("Invalid Choice\n");
            break;
        }

        if (0 == menu_choice)
        {
            /* return */
            break;
        }
    }

    return;
}


/* Init AVRCP application handles */
void appl_avrcp_init_handles (void)
{
    UCHAR index;

    for (index = 0U; index < AVRCP_MAX_PROFILES; index ++)
    {
        AVRCP_INIT_HANDLE (appl_avrcp_handle[index]);
    }

    return;
}

void appl_avrcp_init (void)
{
    API_RESULT retval;

    printf("\n");
    printf("Initializing AVRCP ... "); fflush(stdout);

    retval = BT_avrcp_al_init();
    if (API_SUCCESS != retval)
    {
        printf("FAILED !! Error Code = 0x%04X\n", retval);
    }
    else
    {
        printf("OK\n");
    }

    /* CT Role init */
#ifdef AVRCP_CT
    appl_avrcp_ct_init();
#endif /* AVRCP_CT */

    /* TG Role init */
#ifdef AVRCP_TG
    appl_avrcp_tg_init ();
#endif /* AVRCP_TG */

    return;
}

void appl_avrcp_shutdown (void)
{
    API_RESULT retval;

    printf("\n");
    printf("Shutting down AVRCP ... "); fflush(stdout);

    retval = BT_avrcp_al_shutdown();
    if (API_SUCCESS != retval)
    {
        printf("FAILED !! Error Code = 0x%04X\n", retval);
    }
    else
    {
        printf("Successfully Done.\n");
    }

#ifdef AVRCP_CT
    /* CT Role Shutdown */
    appl_avrcp_ct_shutdown ();
#endif /* AVRCP_CT */

#ifdef AVRCP_TG
    /* TG Role Shutdown */
    appl_avrcp_tg_shutdown ();
#endif  /* AVRCP_TG */

    return;
}

void appl_avrcp_start_handle (UCHAR index)
{
    API_RESULT retval;

    printf("\n");
    printf("[APPL_AVRCP] Starting AVRCP Instance ... "); fflush(stdout);

    retval = BT_avrcp_al_start
             (
                 &appl_avrcp_handle[index],
                 appl_avrcp_ntf_cb
             );
    if (API_SUCCESS != retval)
    {
        printf("FAILED !! Error Code = 0x%04X\n", retval);
    }
    else
    {
        printf("Successfully Done.\n");
    }

#ifdef AVRCP_CT
    /* CT Role Start */
    appl_avrcp_ct_start (index);
#endif /* AVRCP_CT */

#ifdef AVRCP_TG
    /* TG Role Start */
     appl_avrcp_tg_start (index);
#endif /* AVRCP_TG */

    return;
}

void appl_avrcp_start (void)
{
    UCHAR index;

    API_RESULT retval;

    /* Choose Handle */
    appl_avrcp_choose_handle(&index);

    printf("\n");
    printf("Starting AVRCP Instance ... "); fflush(stdout);

    retval = BT_avrcp_al_start
             (
                 &appl_avrcp_handle[index],
                 appl_avrcp_ntf_cb
             );
    if (API_SUCCESS != retval)
    {
        printf("FAILED !! Error Code = 0x%04X\n", retval);
    }
    else
    {
        printf("Successfully Done.\n");
    }

#ifdef AVRCP_CT
    /* CT Role Start */
    appl_avrcp_ct_start (index);
#endif /* AVRCP_CT */

#ifdef AVRCP_TG
    /* TG Role Start */
     appl_avrcp_tg_start (index);
#endif /* AVRCP_TG */

    return;
}

void appl_avrcp_stop (void)
{
    UCHAR index;
    API_RESULT retval;

    /* Choose Handle */
    appl_avrcp_choose_handle(&index);

    printf("\n");
    printf("Stopping AVRCP Instance ... "); fflush(stdout);

    retval = BT_avrcp_al_stop (&appl_avrcp_handle[index]);
    if (API_SUCCESS != retval)
    {
        printf("FAILED !! Error Code = 0x%04X\n", retval);
    }
    else
    {
        printf("Successfully Done.\n");
    }

 #ifdef AVRCP_CT
    /* CT Role Stop */
    appl_avrcp_ct_stop (index);
#endif /* AVRCP_CT */

#ifdef AVRCP_TG
    /* TG Role Stop */
   appl_avrcp_tg_stop (index);
#endif /* AVRCP_TG */

     return;
}

void appl_avrcp_ctl_ch_connect_req (void)
{
    UCHAR index;
    UINT16 acl_indx;
    API_RESULT retval;

    /* Choose Handle */
    appl_avrcp_choose_handle(&index);

    /* Get Remote BD_ADDR */
    retval = appl_avrcp_choose_acl_connection (&acl_indx);
    if (API_SUCCESS == retval)
    {
        printf("\n");
        printf("Starting AVRCP Control Channel Connect ... "); fflush(stdout);

        retval = BT_avrcp_al_connect_req
                 (
                     &appl_avrcp_handle[index],
                     appl_avrcp_acl_list[acl_indx].bd_addr
                 );
        if (API_SUCCESS != retval)
        {
            printf("FAILED !! Error Code = 0x%04X\n", retval);
        }
        else
        {
            printf("Successfully Started.\n");
        }
    }

    return;
}

void appl_avrcp_ctl_ch_disconnect_req (void)
{
    UCHAR index;
    API_RESULT retval;

    /* Choose Handle */
    appl_avrcp_choose_handle(&index);

    printf("\n");
    printf("Starting AVRCP Control Channel Disconnect ... "); fflush(stdout);

    retval = BT_avrcp_al_disconnect_req (&appl_avrcp_handle[index]);
    if (API_SUCCESS != retval)
    {
        printf("FAILED !! Error Code = 0x%04X\n", retval);
    }
    else
    {
        printf("Successfully Started.\n");
    }

    return;
}

#ifdef AVRCP_1_4
void appl_avrcp_brow_ch_connect_req (void)
{
    UCHAR index;
    UINT16 acl_indx;
    API_RESULT retval;

    /* Choose Handle */
    appl_avrcp_choose_handle(&index);

    /* Get Remote BD_ADDR */
    retval = appl_avrcp_choose_acl_connection (&acl_indx);
    if (API_SUCCESS == retval)
    {
        printf("\n");
        printf("Starting AVRCP Browsing Channel Connect ... "); fflush(stdout);

        retval = BT_avrcp_al_channel_connect_req
                 (
                     &appl_avrcp_handle[index],
                     appl_avrcp_acl_list[acl_indx].bd_addr,
                     AVCTP_CHANNEL_TYPE_BROWSING
                 );
        if (API_SUCCESS != retval)
        {
            printf("FAILED !! Error Code = 0x%04X\n", retval);
        }
        else
        {
            printf("Successfully Started.\n");
        }
    }

    return;
}

void appl_avrcp_brow_ch_disconnect_req (void)
{
    UCHAR index;
    API_RESULT retval;

    /* Choose Handle */
    appl_avrcp_choose_handle(&index);

    printf("\n");
    printf("Starting AVRCP Browsing Channel Disconnect ... "); fflush(stdout);

    retval = BT_avrcp_al_channel_disconnect_req
             (
                 &appl_avrcp_handle[index],
                 AVCTP_CHANNEL_TYPE_BROWSING
             );
    if (API_SUCCESS != retval)
    {
        printf("FAILED !! Error Code = 0x%04X\n", retval);
    }
    else
    {
        printf("Successfully Started.\n");
    }

    return;
}

#endif /* AVRCP_1_4 */


/* Application callback registered with AVRCP Abstraction Layer */
API_RESULT appl_avrcp_ntf_cb
           (
                AVRCP_HANDLE * avrcp_handle,
                UCHAR          event_type,
                UINT16         event_result,
                void  *        event_data,
                UINT16         event_datalen
           )
{
    UCHAR index;
#ifdef MULTI_PROFILE_FSM_SUPPORT
    PROFILE_EVENT_INFO profile_info;
#endif /* MULTI_PROFILE_FSM_SUPPORT */
    printf("\n");

    switch (event_type)
    {
    case AVRCP_CONNECT_IND:
        printf("Received AVRCP_CONNECT_IND.\n");
        printf("    Event Result   = 0x%04X\n", event_result);
        printf("    AVRCP Instance = %d (0x%02X)\n",
        avrcp_handle->profile_inst, avrcp_handle->profile_inst);
        printf("    Remote BD_ADDR = %02X:%02X:%02X:%02X:%02X:%02X\n",
        avrcp_handle->bd_addr[0U], avrcp_handle->bd_addr[1U],
        avrcp_handle->bd_addr[2U], avrcp_handle->bd_addr[3U],
        avrcp_handle->bd_addr[4U], avrcp_handle->bd_addr[5U]);

        /* Update AVRCP Handle */
        for (index = 0U; index < AVRCP_MAX_PROFILES; index ++)
        {
            if (avrcp_handle->profile_inst ==
                              appl_avrcp_handle[index].profile_inst)
            {
                AVRCP_SET_HANDLE_BD_ADDR
                (
                    appl_avrcp_handle[index],
                    avrcp_handle->bd_addr
                );
#ifdef MULTI_PROFILE_FSM_SUPPORT
                profile_info.event_type         = ev_pro_avrcp_connect;
				profile_info.event_info         = PROFILE_FSM_REMOTE_EVENT;
				profile_info.profile_fsm_handle = get_multiprofile_handle();
				profile_info.data               = (UCHAR*)avrcp_handle->bd_addr;
				profile_info.datalen            = BT_BD_ADDR_SIZE;
				profile_fsm_post_event(&profile_info);
#endif /* MULTI_PROFILE_FSM_SUPPORT */
            }
        }
        break;

    case AVRCP_CONNECT_CNF:
        printf("Received AVRCP_CONNECT_CNF.\n");
        printf("    Event Result   = 0x%04X\n", event_result);
        printf("    AVRCP Instance = %d (0x%02X)\n",
        avrcp_handle->profile_inst, avrcp_handle->profile_inst);
        printf("    Remote BD_ADDR = %02X:%02X:%02X:%02X:%02X:%02X\n",
        avrcp_handle->bd_addr[0U], avrcp_handle->bd_addr[1U],
        avrcp_handle->bd_addr[2U], avrcp_handle->bd_addr[3U],
        avrcp_handle->bd_addr[4U], avrcp_handle->bd_addr[5U]);

        if (API_SUCCESS != event_result)
        {
            /* Update AVRCP Handle */
            for (index = 0U; index < AVRCP_MAX_PROFILES; index++)
            {
                if (avrcp_handle->profile_inst ==
                    appl_avrcp_handle[index].profile_inst)
                {
                    AVRCP_RESET_HANDLE_BD_ADDR
                    (
                        appl_avrcp_handle[index]
                    );
                }
            }
        }
#ifdef MULTI_PROFILE_FSM_SUPPORT
        	profile_info.event_type         = ev_pro_avrcp_connect;
			profile_info.event_info         = PROFILE_FSM_LOCAL_EVENT;
			profile_info.profile_fsm_handle = get_multiprofile_handle();
			profile_info.data               = (UCHAR*)avrcp_handle->bd_addr;
			profile_info.datalen            = BT_BD_ADDR_SIZE;
			profile_fsm_post_event(&profile_info);
#endif /* MULTI_PROFILE_FSM_SUPPORT */
        break;

    case AVRCP_DISCONNECT_IND:
        printf("Received AVRCP_DISCONNECT_IND.\n");
        printf("    Event Result   = 0x%04X\n", event_result);
        printf("    AVRCP Instance = %d (0x%02X)\n",
        avrcp_handle->profile_inst, avrcp_handle->profile_inst);
        printf("    Remote BD_ADDR = %02X:%02X:%02X:%02X:%02X:%02X\n",
        avrcp_handle->bd_addr[0U], avrcp_handle->bd_addr[1U],
        avrcp_handle->bd_addr[2U], avrcp_handle->bd_addr[3U],
        avrcp_handle->bd_addr[4U], avrcp_handle->bd_addr[5U]);

        /* Update AVRCP Handle */
        for (index = 0U; index < AVRCP_MAX_PROFILES; index ++)
        {
            if (avrcp_handle->profile_inst ==
                              appl_avrcp_handle[index].profile_inst)
            {
                AVRCP_RESET_HANDLE_BD_ADDR
                (
                    appl_avrcp_handle[index]
                );
            }
        }
#ifdef MULTI_PROFILE_FSM_SUPPORT
        	profile_info.event_type         = ev_pro_avrcp_disconnect;
			profile_info.event_info         = PROFILE_FSM_REMOTE_EVENT;
			profile_info.profile_fsm_handle = get_multiprofile_handle();
			profile_info.data               = (UCHAR*)avrcp_handle->bd_addr;
			profile_info.datalen            = BT_BD_ADDR_SIZE;
			profile_fsm_post_event(&profile_info);
#endif /* MULTI_PROFILE_FSM_SUPPORT */
#ifdef AVRCP_BRIDGING
        set_ele_attr_command_called(BT_FALSE);
#endif //AVRCP_BRIDGING

        break;

    case AVRCP_DISCONNECT_CNF:
        printf("Received AVRCP_DISCONNECT_CNF.\n");
        printf("    Event Result   = 0x%04X\n", event_result);
        printf("    AVRCP Instance = %d (0x%02X)\n",
        avrcp_handle->profile_inst, avrcp_handle->profile_inst);
        printf("    Remote BD_ADDR = %02X:%02X:%02X:%02X:%02X:%02X\n",
        avrcp_handle->bd_addr[0U], avrcp_handle->bd_addr[1U],
        avrcp_handle->bd_addr[2U], avrcp_handle->bd_addr[3U],
        avrcp_handle->bd_addr[4U], avrcp_handle->bd_addr[5U]);

        /* Update AVRCP Handle */
        for (index = 0U; index < AVRCP_MAX_PROFILES; index ++)
        {
            if (avrcp_handle->profile_inst ==
                              appl_avrcp_handle[index].profile_inst)
            {
                AVRCP_RESET_HANDLE_BD_ADDR
                (
                    appl_avrcp_handle[index]
                );
            }
        }
#ifdef MULTI_PROFILE_FSM_SUPPORT
        	profile_info.event_type         = ev_pro_avrcp_disconnect;
			profile_info.event_info         = PROFILE_FSM_LOCAL_EVENT;
			profile_info.profile_fsm_handle = get_multiprofile_handle();
			profile_info.data               = (UCHAR*)avrcp_handle->bd_addr;
			profile_info.datalen            = BT_BD_ADDR_SIZE;
			profile_fsm_post_event(&profile_info);
#endif /* MULTI_PROFILE_FSM_SUPPORT */
#ifdef AVRCP_BRIDGING
        set_ele_attr_command_called(BT_FALSE);
#endif //AVRCP_BRIDGING
        break;

#ifdef AVRCP_1_4

    case AVRCP_BOW_CONNECT_IND:
        printf("Received AVRCP_BOW_CONNECT_IND.\n");
        printf("    Event Result   = 0x%04X\n", event_result);
        printf("    AVRCP Instance = %d (0x%02X)\n",
        avrcp_handle->profile_inst, avrcp_handle->profile_inst);

        break;

    case AVRCP_BOW_CONNECT_CNF:
        printf("Received AVRCP_BOW_CONNECT_CNF.\n");
        printf("    Event Result   = 0x%04X\n", event_result);
        printf("    AVRCP Instance = %d (0x%02X)\n",
        avrcp_handle->profile_inst, avrcp_handle->profile_inst);

#ifdef AVRCP_CT
        /**
         * Get Media Player list
         */
        get_folder_items_param.scope = AVRCP_SCOPE_MEDIA_PLAYER_LIST;
        get_folder_items_param.start_item = 0U;
        get_folder_items_param.end_item = 10U;
        get_folder_items_param.attr_count = 0xFFU;

        (BT_IGNORE_RETURN_VALUE) BT_avrcp_al_get_folder_items
        (
            avrcp_handle,
            &get_folder_items_param
        );
#endif /* AVRCP_CT */

        break;

    case AVRCP_BOW_DISCONNECT_IND:
        printf("Received AVRCP_BOW_DISCONNECT_IND.\n");
        printf("    Event Result   = 0x%04X\n", event_result);
        printf("    AVRCP Instance = %d (0x%02X)\n",
        avrcp_handle->profile_inst, avrcp_handle->profile_inst);

        break;

    case AVRCP_BOW_DISCONNECT_CNF:
        printf("Received AVRCP_BOW_DISCONNECT_CNF.\n");
        printf("    Event Result   = 0x%04X\n", event_result);
        printf("    AVRCP Instance = %d (0x%02X)\n",
        avrcp_handle->profile_inst, avrcp_handle->profile_inst);

        break;

#endif /* AVRCP_1_4 */

    case AVRCP_MESSAGE_SEND_CNF:
        printf("Received AVRCP_MESSAGE_SEND_CNF.\n");
        printf("    Event Result   = 0x%04X\n", event_result);
        printf("    AVRCP Instance = %d (0x%02X)\n",
        avrcp_handle->profile_inst, avrcp_handle->profile_inst);
        printf("    Remote BD_ADDR = %02X:%02X:%02X:%02X:%02X:%02X\n",
        avrcp_handle->bd_addr[0U], avrcp_handle->bd_addr[1U],
        avrcp_handle->bd_addr[2U], avrcp_handle->bd_addr[3U],
        avrcp_handle->bd_addr[4U], avrcp_handle->bd_addr[5U]);

        break;

        /* TG related events */
#ifdef AVRCP_TG
    case AVRCP_MESSAGE_IND:
        printf("Received AVRCP_MESSAGE_IND.\n");
        printf("    Event Result   = 0x%04X\n", event_result);
        printf("    AVRCP Instance = %d (0x%02X)\n",
        avrcp_handle->profile_inst, avrcp_handle->profile_inst);
        printf("    Remote BD_ADDR = %02X:%02X:%02X:%02X:%02X:%02X\n",
        avrcp_handle->bd_addr[0U], avrcp_handle->bd_addr[1U],
        avrcp_handle->bd_addr[2U], avrcp_handle->bd_addr[3U],
        avrcp_handle->bd_addr[4U], avrcp_handle->bd_addr[5U]);
#ifndef AVRCP_BRIDGING
        if ((event_data != NULL) && (event_datalen > 0U))
        {
            appl_avrcp_tg_handle_message_cmd
            (
                    avrcp_handle->profile_inst,
                    event_data,
                    event_datalen
            );
        }
#endif /* AVRCP_BRIDGING */
#ifdef MULTI_PROFILE_FSM_SUPPORT
            appl_event_recvd = (AVRCP_AL_CT_CMD_INFO*)event_data;
        	profile_info.event_type         = ev_pro_avrcp_message_ind;
			profile_info.event_info         = PROFILE_FSM_REMOTE_EVENT;
			profile_info.profile_fsm_handle = get_multiprofile_handle();
			profile_info.data               = (UCHAR*)avrcp_handle->bd_addr;
			profile_info.datalen            = BT_BD_ADDR_SIZE;
			profile_fsm_post_event(&profile_info);
#endif /* MULTI_PROFILE_FSM_SUPPORT */
        break;

#ifdef AVRCP_1_3

    case AVRCP_METADATA_CMD:
        printf("Received AVRCP_METADATA_CMD.\n");
        printf("    Event Result   = 0x%04X\n", event_result);
        printf("    AVRCP Instance = %d (0x%02X)\n",
        avrcp_handle->profile_inst, avrcp_handle->profile_inst);
        printf("    Remote BD_ADDR = %02X:%02X:%02X:%02X:%02X:%02X\n",
        avrcp_handle->bd_addr[0U], avrcp_handle->bd_addr[1U],
        avrcp_handle->bd_addr[2U], avrcp_handle->bd_addr[3U],
        avrcp_handle->bd_addr[4U], avrcp_handle->bd_addr[5U]);
#ifndef AVRCP_BRIDGING
        if ((event_data != NULL) && (event_datalen > 0U))
        {
            appl_avrcp_tg_handle_vendor_dependent_cmd
                (
                    avrcp_handle->profile_inst,
                    event_data,
                    event_datalen
                );
        }
#endif /* AVRCP_BRIDGING */
#ifdef MULTI_PROFILE_FSM_SUPPORT
            appl_vendor_event_recvd= (AVRCP_AL_VD_CMD_INFO*)event_data;
        	profile_info.event_type         = ev_pro_avrcp_message_ind;
			profile_info.event_info         = PROFILE_FSM_REMOTE_EVENT;
			profile_info.profile_fsm_handle = get_multiprofile_handle();
			profile_info.data               = (UCHAR*)avrcp_handle->bd_addr;
			profile_info.datalen            = BT_BD_ADDR_SIZE;
			profile_fsm_post_event(&profile_info);
#endif /* MULTI_PROFILE_FSM_SUPPORT */

        break;

#endif /* AVRCP_1_3 */

#ifdef AVRCP_1_4
    case AVRCP_BOW_MESSAGE_IND:

        printf("Received AVRCP Browsing PDU IND.\n");
        printf("    Event Result   = 0x%04X\n", event_result);
        printf("    AVRCP Instance = %d (0x%02X)\n",
        avrcp_handle->profile_inst, avrcp_handle->profile_inst);
        printf("    Remote BD_ADDR = %02X:%02X:%02X:%02X:%02X:%02X\n",
        avrcp_handle->bd_addr[0U], avrcp_handle->bd_addr[1U],
        avrcp_handle->bd_addr[2U], avrcp_handle->bd_addr[3U],
        avrcp_handle->bd_addr[4U], avrcp_handle->bd_addr[5U]);

        if ((event_data != NULL) && (event_datalen > 0U))
        {
            appl_avrcp_tg_handle_browsing_cmd (event_data, event_datalen);
        }

        break;

#endif /* AVRCP_1_4 */

#endif /* AVRCP_TG */

#ifdef AVRCP_CT
    case AVRCP_MESSAGE_CNF:
        printf("Received AVRCP_MESSAGE_CNF.\n");
        printf("    Event Result   = 0x%04X\n", event_result);
        printf("    AVRCP Instance = %d (0x%02X)\n",
        avrcp_handle->profile_inst, avrcp_handle->profile_inst);
        printf("    Remote BD_ADDR = %02X:%02X:%02X:%02X:%02X:%02X\n",
        avrcp_handle->bd_addr[0U], avrcp_handle->bd_addr[1U],
        avrcp_handle->bd_addr[2U], avrcp_handle->bd_addr[3U],
        avrcp_handle->bd_addr[4U], avrcp_handle->bd_addr[5U]);
#ifndef AVRCP_BRIDGING
        if ((event_result == API_SUCCESS) &&
            (event_data != NULL) && (event_datalen > 0U))
        {
            appl_avrcp_ct_handle_message_cnf (event_data, event_datalen);
        }
#endif /* AVRCP_BRIDGING */
#ifdef MULTI_PROFILE_FSM_SUPPORT
            appl_avrcp_recvd_cnf = (AVRCP_AL_CT_RSP_INFO*)event_data;
        	profile_info.event_type         = ev_pro_avrcp_message_cnf;
			profile_info.event_info         = PROFILE_FSM_REMOTE_EVENT;
			profile_info.profile_fsm_handle = get_multiprofile_handle();
			profile_info.data               = (UCHAR*)avrcp_handle->bd_addr;
			profile_info.datalen            = BT_BD_ADDR_SIZE;
			profile_fsm_post_event(&profile_info);
#endif /* MULTI_PROFILE_FSM_SUPPORT */
        break;

#ifdef AVRCP_1_3
    case AVRCP_METADATA_INTERIM_RSP:
    case AVRCP_METADATA_RSP:

        printf("Received %s.\n", ((AVRCP_METADATA_RSP == event_type)?
                "AVRCP_METADATA_RSP" : "AVRCP_METADATA_INTERIM_RSP"));
        printf("    Event Result   = 0x%04X\n", event_result);
        printf("    AVRCP Instance = %d (0x%02X)\n",
        avrcp_handle->profile_inst, avrcp_handle->profile_inst);
        printf("    Remote BD_ADDR = %02X:%02X:%02X:%02X:%02X:%02X\n",
        avrcp_handle->bd_addr[0U], avrcp_handle->bd_addr[1U],
        avrcp_handle->bd_addr[2U], avrcp_handle->bd_addr[3U],
        avrcp_handle->bd_addr[4U], avrcp_handle->bd_addr[5U]);
#ifndef AVRCP_BRIDGING
        if ((event_data != NULL) && (event_datalen > 0U))
        {
            appl_avrcp_ct_handle_vendor_dependent_cmd_rsp
                (
                    avrcp_handle->profile_inst,
                    event_data,
                    event_datalen
                );
        }
#endif /*ifndef AVRCP_BRIDGING */
#ifdef AVRCP_BRIDGING
        AVRCP_AL_VD_CMD_INFO * vd_cmd_info;
		vd_cmd_info     = (AVRCP_AL_VD_CMD_INFO *)event_data;
		if((vd_cmd_info->pdu_id == AVRCP_METADATA_PDU_ID_GET_ELEMENT_ATTRIBUTE) &&
				(is_ele_attr_command_called()))
		{
			printf("AVRCP_METADATA_PDU_ID_GET_ELEMENT_ATTRIBUTE:\n");
			appl_avrcp_ct_handle_vendor_dependent_cmd_rsp
							(
								avrcp_handle->profile_inst,
								event_data,
								event_datalen
							);
			set_ele_attr_command_called(BT_FALSE);
		}
		else
		{
#endif //AVRCP_BRIDGING
#ifdef MULTI_PROFILE_FSM_SUPPORT
            appl_vendor_event_recvd= (AVRCP_AL_VD_CMD_INFO*)event_data;
        	profile_info.event_type         = ev_pro_avrcp_message_cnf;
			profile_info.event_info         = PROFILE_FSM_REMOTE_EVENT;
			profile_info.profile_fsm_handle = get_multiprofile_handle();
			profile_info.data               = (UCHAR*)avrcp_handle->bd_addr;
			profile_info.datalen            = BT_BD_ADDR_SIZE;
			profile_fsm_post_event(&profile_info);
#endif /* MULTI_PROFILE_FSM_SUPPORT */
#ifdef AVRCP_BRIDGING
		}
#endif //AVRCP_BRIDGING
        break;

#endif /* AVRCP_1_3 */

#ifdef AVRCP_1_4
    case AVRCP_BOW_MESSAGE_RSP:
        printf("Received AVRCP_BOW_MESSAGE_RSP.\n");
        printf("    Event Result   = 0x%04X\n", event_result);
        printf("    AVRCP Instance = %d (0x%02X)\n",
        avrcp_handle->profile_inst, avrcp_handle->profile_inst);
        printf("    Remote BD_ADDR = %02X:%02X:%02X:%02X:%02X:%02X\n",
        avrcp_handle->bd_addr[0U], avrcp_handle->bd_addr[1U],
        avrcp_handle->bd_addr[2U], avrcp_handle->bd_addr[3U],
        avrcp_handle->bd_addr[4U], avrcp_handle->bd_addr[5U]);

        if ((event_data != NULL) && (event_datalen > 0U))
        {
            appl_avrcp_ct_handle_brow_cmd_rsp
                (
                    avrcp_handle->profile_inst,
                    event_data,
                    event_datalen
                );
        }

        break;

#endif /* AVRCP_1_4 */

#endif /* AVRCP_CT */

    default:
        printf("Received Unknown AVRCP Event = 0x%02X. Result = 0x%04X\n",
        event_type, event_result);
        break;
    }

    return API_SUCCESS;
}


void appl_avrcp_choose_handle (UCHAR * retval)
{
    int read_val;

    BT_LOOP_FOREVER()
    {
        appl_avrcp_show_handles();

        printf("Choose Index = "); fflush(stdout);
        scanf("%d", &read_val);

        if ((read_val >= 0) && (read_val < AVRCP_MAX_PROFILES))
        {
            break;
        }
    }
    *retval = (UCHAR)read_val;

    return;
}

UCHAR appl_avrcp_get_connected_handle (UCHAR * bd_addr)
{
    UCHAR index;
    printf (
    "[MULTI_PROFILE]: >>> appl_avrcp_get_connected_handle\n");
    for (index = 0U; index < AVRCP_MAX_PROFILES; index ++)
    {
    	printf("appl_avrcp_handle BDADDR" BT_DEVICE_ADDR_ONLY_FRMT_SPECIFIER "\n",
        BT_DEVICE_ADDR_ONLY_PRINT_STR (appl_avrcp_handle[index].bd_addr));

    	printf("BDADDR" BT_DEVICE_ADDR_ONLY_FRMT_SPECIFIER "\n",
        BT_DEVICE_ADDR_ONLY_PRINT_STR (bd_addr));
        if (BT_TRUE == BT_COMPARE_ADDR(appl_avrcp_handle[index].bd_addr,bd_addr))
        {
            break;
        }
    }
    if (AVRCP_MAX_PROFILES == index)
    {
    	printf("No FREE Index\n");
    }
    printf (
    "[MULTI_PROFILE]: <<< appl_avrcp_get_connected_handle\n");
    return index;
}

UCHAR appl_avrcp_get_free_handle (void)
{
    UCHAR index;
    for (index = 0U; index < AVRCP_MAX_PROFILES; index ++)
    {
        if ((appl_avrcp_handle[index].profile_inst == 0xFFU) && \
        		(BT_FALSE == BT_BD_ADDR_IS_NON_ZERO(appl_avrcp_handle[index].bd_addr)))
        {
            break;
        }
    }
    if (AVRCP_MAX_PROFILES == index)
    {
    	printf("No FREE Index\n");
    }
    return index;
}

void appl_avrcp_show_handles (void)
{
    UCHAR index;

    printf("\n");
    printf("Index  Remote BD_ADDR     Instance\n");
    printf("-----  -----------------  --------\n");
    for (index = 0U; index < AVRCP_MAX_PROFILES; index ++)
    {
        if (appl_avrcp_handle[index].profile_inst == 0xFFU)
        {
            printf("%3d    NOT ALLOCATED\n", index);
            continue;
        }

        printf("%3d    ", index);
        printf("%02X:%02X:%02X:%02X:%02X:%02X  ",
        appl_avrcp_handle[index].bd_addr[0U],
        appl_avrcp_handle[index].bd_addr[1U],
        appl_avrcp_handle[index].bd_addr[2U],
        appl_avrcp_handle[index].bd_addr[3U],
        appl_avrcp_handle[index].bd_addr[4U],
        appl_avrcp_handle[index].bd_addr[5U]);

        printf("  0x%02X\n", appl_avrcp_handle[index].profile_inst);
    }
    printf("\n");

    return;
}

API_RESULT appl_avrcp_choose_acl_connection (UINT16 * indx)
{
    int choice;
    API_RESULT retval;
    UCHAR i, num_list;

    printf("Getting Connection Details from HCI ... "); fflush(stdout);
    retval = BT_hci_get_connection_details
             (
                 appl_avrcp_acl_list,
                 BT_MAX_REMOTE_DEVICES,
                 &num_list
             );
    if (API_SUCCESS != retval)
    {
         printf("FAILED !! Error Code = 0x%04X\n", retval);
    }
    else
    {
        printf("Succeeded.\n");

        if (0U == num_list)
        {
            retval = API_FAILURE; /* return API_FAILURE; */
        }

        if (API_FAILURE != retval)
        {
            printf("\n");
            printf("==========================================================\n");
            printf("Active ACL Connections\n");
            printf("----------------------------------------------------------\n");
            for (i = 0U; i < num_list; i++)
            {
                printf("  [%2d]  ", i);
                printf("BD_ADDR %02X:%02X:%02X:%02X:%02X:%02X  ",
                    appl_avrcp_acl_list[i].bd_addr[0U],
                    appl_avrcp_acl_list[i].bd_addr[1U],
                    appl_avrcp_acl_list[i].bd_addr[2U],
                    appl_avrcp_acl_list[i].bd_addr[3U],
                    appl_avrcp_acl_list[i].bd_addr[4U],
                    appl_avrcp_acl_list[i].bd_addr[5U]);
                printf("ACL Handle = 0x%04X\n",
                    appl_avrcp_acl_list[i].acl_handle);
            }
            printf("==========================================================\n");
            printf("\n");
        }
    }

    if (API_SUCCESS == retval)
    {
        printf("Choose ACL Connection Index = "); fflush(stdout);
        scanf("%d", &choice);
        if ((UINT16)choice >= BT_MAX_REMOTE_DEVICES)
        {
            retval = API_FAILURE; /* return API_FAILURE; */
        }
        else
        {
            *indx = (UINT16)choice;
        }
    }

    return retval;
}


void appl_avrcp_print_opcode (UCHAR opcode)
{
    switch (opcode)
    {
    case AVRCP_OPCODE_UNIT_INFO:
        printf("    Opcode = UNIT INFO\n");
        break;

    case AVRCP_OPCODE_SUBUNIT_INFO:
        printf("    Opcode = SUBUNIT INFO\n");
        break;

    case AVRCP_OPCODE_PASS_THROUGH:
        printf("    Opcode = PASS THROUGH\n");
        break;

    default:
        printf("    Opcode = ???? (0x%02X)\n", opcode);
        break;
    }

    return;
}

void appl_avrcp_print_response_type (UCHAR rsp_type)
{
    switch (rsp_type)
    {
    case AVRCP_RESPONSE_TYPE_NOT_IMPLEMENTED:
        printf("    Response Type = NOT IMPLEMENTED\n");
        break;

    case AVRCP_RESPONSE_TYPE_ACCEPTED:
        printf("    Response Type = ACCEPTED\n");
        break;

    case AVRCP_RESPONSE_TYPE_REJECTED:
        printf("    Response Type = REJECTED\n");
        break;

    case AVRCP_RESPONSE_TYPE_INTERIM:
        printf("    Response Type = INTERIM\n");
        break;

    case AVRCP_RESPONSE_TYPE_STABLE:
        printf("    Response Type = STABLE\n");
        break;

    default:
        printf("    Response Type = ???? (0x%02X)\n", rsp_type);
        break;
    }

    return;
}


void appl_avrcp_print_operation_id (UCHAR operation_id)
{
    switch (operation_id)
    {
    case AVRCP_OPERATION_ID_SELECT:
        printf("    Operation ID = SELECT\n");
        break;

    case AVRCP_OPERATION_ID_UP:
        printf("    Operation ID = UP\n");
        break;

    case AVRCP_OPERATION_ID_DOWN:
        printf("    Operation ID = DOWN\n");
        break;

    case AVRCP_OPERATION_ID_LEFT:
        printf("    Operation ID = LEFT\n");
        break;

    case AVRCP_OPERATION_ID_RIGHT:
        printf("    Operation ID = RIGHT\n");
        break;

    case AVRCP_OPERATION_ID_RIGHT_UP:
        printf("    Operation ID = RIGHT UP\n");
        break;

    case AVRCP_OPERATION_ID_RIGHT_DOWN:
        printf("    Operation ID = RIGHT DOWN\n");
        break;

    case AVRCP_OPERATION_ID_LEFT_UP:
        printf("    Operation ID = LEFT UP\n");
        break;

    case AVRCP_OPERATION_ID_LEFT_DOWN:
        printf("    Operation ID = LEFT DOWN\n");
        break;

    case AVRCP_OPERATION_ID_ROOT_MENU:
        printf("    Operation ID = ROOT MENU\n");
        break;

    case AVRCP_OPERATION_ID_SETUP_MENU:
        printf("    Operation ID = SETUP MENU\n");
        break;

    case AVRCP_OPERATION_ID_CONTENTS_MENU:
        printf("    Operation ID = CONTENTS MENU\n");
        break;

    case AVRCP_OPERATION_ID_FAVORITE_MENU:
        printf("    Operation ID = FAVORITE MENU\n");
        break;

    case AVRCP_OPERATION_ID_EXIT:
        printf("    Operation ID = EXIT\n");
        break;

    case AVRCP_OPERATION_ID_0:
        printf("    Operation ID = 0\n");
        break;

    case AVRCP_OPERATION_ID_1:
        printf("    Operation ID = 1\n");
        break;

    case AVRCP_OPERATION_ID_2:
        printf("    Operation ID = 2\n");
        break;

    case AVRCP_OPERATION_ID_3:
        printf("    Operation ID = 3\n");
        break;

    case AVRCP_OPERATION_ID_4:
        printf("    Operation ID = 4\n");
        break;

    case AVRCP_OPERATION_ID_5:
        printf("    Operation ID = 5\n");
        break;

    case AVRCP_OPERATION_ID_6:
        printf("    Operation ID = 6\n");
        break;

    case AVRCP_OPERATION_ID_7:
        printf("    Operation ID = 7\n");
        break;

    case AVRCP_OPERATION_ID_8:
        printf("    Operation ID = 8\n");
        break;

    case AVRCP_OPERATION_ID_9:
        printf("    Operation ID = 9\n");
        break;

    case AVRCP_OPERATION_ID_DOT:
        printf("    Operation ID = DOT\n");
        break;

    case AVRCP_OPERATION_ID_ENTER:
        printf("    Operation ID = ENTER\n");
        break;

    case AVRCP_OPERATION_ID_CLEAR:
        printf("    Operation ID = CLEAR\n");
        break;

    case AVRCP_OPERATION_ID_CHANNEL_UP:
        printf("    Operation ID = CHANNEL UP\n");
        break;

    case AVRCP_OPERATION_ID_CHANNEL_DOWN:
        printf("    Operation ID = CHANNEL DOWN\n");
        break;

    case AVRCP_OPERATION_ID_PREVIOUS_CHANNEL:
        printf("    Operation ID = PREVIOUS CHANNEL\n");
        break;

    case AVRCP_OPERATION_ID_SOUND_SELECT:
        printf("    Operation ID = SOUND SELECT\n");
        break;

    case AVRCP_OPERATION_ID_INPUT_SELECT:
        printf("    Operation ID = INPUT SELECT\n");
        break;

    case AVRCP_OPERATION_ID_DISPLAY_INFORMATION:
        printf("    Operation ID = DISPLAY INFORMATION\n");
        break;

    case AVRCP_OPERATION_ID_HELP:
        printf("    Operation ID = HELP\n");
        break;

    case AVRCP_OPERATION_ID_PAGE_UP:
        printf("    Operation ID = PAGE UP\n");
        break;

    case AVRCP_OPERATION_ID_PAGE_DOWN:
        printf("    Operation ID = PAGE DOWN\n");
        break;

    case AVRCP_OPERATION_ID_POWER:
        printf("    Operation ID = POWER\n");
        break;

    case AVRCP_OPERATION_ID_VOLUME_UP:
        printf("    Operation ID = VOLUME UP\n");
        break;

    case AVRCP_OPERATION_ID_VOLUME_DOWN:
        printf("    Operation ID = VOLUME DOWN\n");
        break;

    case AVRCP_OPERATION_ID_MUTE:
        printf("    Operation ID = MUTE\n");
        break;

    case AVRCP_OPERATION_ID_PLAY:
        printf("    Operation ID = PLAY\n");
        break;

    case AVRCP_OPERATION_ID_STOP:
        printf("    Operation ID = STOP\n");
        break;

    case AVRCP_OPERATION_ID_PAUSE:
        printf("    Operation ID = PAUSE\n");
        break;

    case AVRCP_OPERATION_ID_RECORD:
        printf("    Operation ID = RECORD\n");
        break;

    case AVRCP_OPERATION_ID_REWIND:
        printf("    Operation ID = REWIND\n");
        break;

    case AVRCP_OPERATION_ID_FAST_FORWARD:
        printf("    Operation ID = FAST FORWARD\n");
        break;

    case AVRCP_OPERATION_ID_EJECT:
        printf("    Operation ID = EJECT\n");
        break;

    case AVRCP_OPERATION_ID_FORWARD:
        printf("    Operation ID = FORWARD\n");
        break;

    case AVRCP_OPERATION_ID_BACKWARD:
        printf("    Operation ID = BACKWARD\n");
        break;

    case AVRCP_OPERATION_ID_ANGLE:
        printf("    Operation ID = ANGLE\n");
        break;

    case AVRCP_OPERATION_ID_SUBPICTURE:
        printf("    Operation ID = SUBPICTURE\n");
        break;

    case AVRCP_OPERATION_ID_F1:
        printf("    Operation ID = F1\n");
        break;

    case AVRCP_OPERATION_ID_F2:
        printf("    Operation ID = F2\n");
        break;

    case AVRCP_OPERATION_ID_F3:
        printf("    Operation ID = F3\n");
        break;

    case AVRCP_OPERATION_ID_F4:
        printf("    Operation ID = F4\n");
        break;

    case AVRCP_OPERATION_ID_F5:
        printf("    Operation ID = F5\n");
        break;

    case AVRCP_OPERATION_ID_VENDOR_UNIQUE:
        printf("    Operation ID = VENDOR UNIQUE\n");
        break;

    default:
        printf("    Operation ID = ???? (0x%02X)\n", operation_id);
        break;
    }

    return;
}

void appl_get_avrcp_sdp_record (UCHAR * bd_addr)
{
    printf("appl_get_avrcp_sdp_record: SDP Open....\n");
    /* Set the SDP handle */
    SDP_SET_HANDLE(appl_sdp_handle, bd_addr, appl_avrcp_sdp_callback);
    BT_sdp_open(&appl_sdp_handle);
   
    return;
}

void appl_avrcp_sdp_callback
(
    UCHAR command,
    UCHAR * data,
    UINT16 length,
    UINT16 status
)
{
    S_UUID  uuid;
    UINT16 num_uuids;
    UINT16  attrib_id[6];
    UINT16 num_attribute_ids;
    API_RESULT retval = API_FAILURE;
    UCHAR * sdp_query_result;
    UCHAR num_list;
#ifdef MULTI_PROFILE_FSM_SUPPORT
    PROFILE_EVENT_INFO profile_info;
#endif /* MULTI_PROFILE_FSM_SUPPORT */
    if (API_SUCCESS != status)
    {
        printf("> ** FAILED performing SDP Operation: %02X\n", command);
        printf("> Return Value : 0x%04X\n", status);
    }

     switch(command)
    {
    case SDP_Open : /* SDP open callback */
      {
          /* Set AVCTP related UUID variables */
            uuid.uuid_type = UUID_16;
            uuid.uuid_union.uuid_16 = AVCTP_UUID;
           
          /* Number of UUIDs to be queried in one record */
            num_uuids = 0x01;

            /* Attribute IDs in ascending order */
            attrib_id[0] = SERVICE_CLASS_ID_LIST;
            attrib_id[1] = PROTOCOL_DESC_LIST;
            attrib_id[2] = SUPPORTED_FEATURES_ATTR_ID;

            num_attribute_ids = 3;

            appl_sdp_attrib_datalen = SDP_ATTRIB_DATALEN;

            /* Do Service Search Request */
            retval = BT_sdp_servicesearchattributerequest
                 (
                     &appl_sdp_handle,
                     &uuid,
                     num_uuids,
                     attrib_id,
                     num_attribute_ids,
                     NULL,
                     0x00,
                     appl_sdp_attrib_data,
                     &appl_sdp_attrib_datalen
                 );

          if (API_SUCCESS != retval)
            {
                printf("> ** "\
                       "BT_sdp_servicesearchattributerequest Failed %d\n",retval);

                /* Close SDP */
                BT_sdp_close(&appl_sdp_handle);
            }
      }
        break;

    /* Service Search Attribute callback */
    case SDP_ServiceSearchAttributeResponse:
	{
        UINT16 avrcp_peer_supp_feat;
        UINT16 peer_supp_features_len = sizeof(UINT16);
        printf("AVRCP,SDP Response received \n");
        sdp_query_result = data;
        retval = BT_sdp_get_attr_value
                 (
                     SUPPORTED_FEATURES_ATTR_ID,
                     sdp_query_result,
                     (UCHAR *)&avrcp_peer_supp_feat,
                     &peer_supp_features_len
                 );
        if(API_SUCCESS != retval)
        {
            printf("SDP FAILED to find AVRCP Supported Features\n");
        }
        else
        {
            printf ("avrcp sdp Successs\n");

            printf ("Peer AVRCP Supported Features 0x%04X\n", avrcp_peer_supp_feat);
        }

        if (APPL_AVRCP_BROWSING_FEATURE_SUPPORT & avrcp_peer_supp_feat)
         {
            appl_avrcp_browsing_support = BT_TRUE;
         }
        else 
         {
            appl_avrcp_browsing_support = BT_FALSE;
         }

        int ret = BT_sdp_close(&appl_sdp_handle);
        printf("avrcp BT_sdp_close() call, %x\n", ret);

       /* get conection details to start AVRCP connection */	 
        retval = BT_hci_get_connection_details
         (
             appl_avrcp_acl_list,
             BT_MAX_REMOTE_DEVICES,
             &num_list
         );
 
         if (API_SUCCESS != retval)
         {
             printf("FAILED !! Error Code = 0x%04X\n", retval);
         }
	}
         break;

    case SDP_Close: /* SDP Close callback */
    {
        printf("avrcp sdp closed\n");
#ifdef MULTI_PROFILE_FSM_SUPPORT
        	profile_info.event_type         = ev_pro_avrcp_sdp_done;
			profile_info.event_info         = PROFILE_FSM_LOCAL_EVENT;
			profile_info.profile_fsm_handle = get_multiprofile_handle();
			profile_info.data               = appl_peer_bd_addr;
			profile_info.datalen            = BT_BD_ADDR_SIZE;
			profile_fsm_post_event(&profile_info);
#endif /* MULTI_PROFILE_FSM_SUPPORT */
        //TODO: Check SDP AVRCP Service and then call below API.
        break;
    }

    case SDP_ErrorResponse:

        printf("> ** AVRCP ERROR occoured in SDP Query\n");

        BT_sdp_close(&appl_sdp_handle);

        break;

    default: /* Invalid: Nothing to do */
        break;
    }
}

/* AVRCP connect functions moved from A2DP files to here */
void appl_a2dp_avrcp_connect(UCHAR * bd_addr)
{
    UCHAR i, avrcp_idx, num_list;
    API_RESULT retval = 0x00;;

    for (i = 0U; i < AVRCP_MAX_PROFILES; i ++)
    {
        if ((appl_avrcp_handle[i].profile_inst != 0xFFU) && \
                (BT_FALSE == BT_BD_ADDR_IS_NON_ZERO(appl_avrcp_handle[i].bd_addr)))
        {
            break;
        }
    }
    avrcp_idx = i;

    printf ("avrcp_idx %d\n", avrcp_idx);

    if (AVRCP_MAX_PROFILES > avrcp_idx)
    {
        retval = BT_hci_get_connection_details
                 (
                     appl_avrcp_acl_list,
                     BT_MAX_REMOTE_DEVICES,
                     &num_list
                 );
        for (i = 0U; i < num_list; i++)
        {
            if (BT_TRUE == BT_COMPARE_ADDR(appl_avrcp_acl_list[i].bd_addr,bd_addr))
            {
                break;
            }
        }
        printf("Starting AVRCP Control Channel Connect ... "); fflush(stdout);

        retval = BT_avrcp_al_connect_req
                 (
                     &appl_avrcp_handle[avrcp_idx],
                     appl_avrcp_acl_list[i].bd_addr
                 );
        if (API_SUCCESS != retval)
        {
            printf("FAILED !! Error Code = 0x%04X\n", retval);
        }
    }

#if defined(HFP_BRIDGING) && defined(A2DP_BRIDGING) && defined(AVRCP_BRIDGING)
    if ((avrcp_idx >= AVRCP_MAX_PROFILES) || (retval == AVCTP_CONNECTION_ALREADY_EXISTS))
    {
        UCHAR appl_avrcp_sep_flag = appl_get_sep_to_register_notification();
		if (appl_avrcp_sep_flag == AVDTP_SEP_SOURCE)
		{
			/*TODO: currently there is only one unit that can be connected, hence not checking the address*/
			if (BT_FALSE == appl_hfpag_is_ag_connected())
			{
				/* Initiate connection to unit if already not connected */
				appl_get_hfag_sdp_record(bd_addr);
			}
			else
			{
				printf("Unit already connected, not initiating connection again\n");
			}
		}
		else
		{
			/*TODO: currently there is only one ag that can be connected, hence not checking the address*/
			if (BT_FALSE == appl_hfpunit_is_unit_connected())
			{
				/* Initiate connection to AG if already not connected */
				printf("Initiating Profile Connection to AG\n");
				appl_get_hfunit_sdp_record(bd_addr);
			}
			else
			{
				printf("AG already connected, not initiating connection again\n");
			}
		}
    }
#endif
    return;
}

/* Function AVRCP disconnect moved from A2DP to here */
void appl_a2dp_avrcp_disconnect(UCHAR * bd_addr)
{
    UCHAR i;
    API_RESULT retval;

    for (i = 0U; i < AVRCP_MAX_PROFILES; i++)
    {
        if (BT_TRUE == BT_COMPARE_ADDR(appl_avrcp_handle[i].bd_addr,bd_addr))
        {
            break;
        }
    }
    retval = BT_avrcp_al_channel_disconnect_req
            (
                &appl_avrcp_handle[i],
                AVCTP_CHANNEL_TYPE_BROWSING
            );

    if (API_SUCCESS != retval)
    {
        printf("FAILED !! Error Code = 0x%04X\n", retval);
    }
    else
    {
        printf("Successfully Disconnected.\n");
        retval = BT_avrcp_al_disconnect_req (&appl_avrcp_handle[i]);
    }
}

/* API to find avrcp  instance */
uint8_t avrcp_find_avrcp_instance (UCHAR *bd_addr)
{
	uint8_t current_avrcp_instance = 0xFFU;
	for (int index = 0U; index < AVRCP_MAX_PROFILES; index++)
	{
       if (BT_TRUE == BT_BD_ADDR_IS_NON_ZERO(appl_avrcp_handle[index].bd_addr) &&
        		(BT_COMPARE_ADDR(bd_addr, appl_avrcp_handle[index].bd_addr) == BT_TRUE))
        {
        	current_avrcp_instance = index;
        	break;
        }
	}
	return current_avrcp_instance;
}

/* API to find second running instance of AVRCP */
uint8_t avrcp_find_second_avrcp_instance (uint8_t current_instance)
{
	uint8_t connected_avrcp_instance = PROFILE_INSTANCE_INVALID;

	if (current_instance != PROFILE_INSTANCE_INVALID)
	{
		for (int i = 0U; i < AVRCP_MAX_PROFILES; i++)
		{
			if ((i != current_instance) &&
					(BT_TRUE == BT_BD_ADDR_IS_NON_ZERO(appl_avrcp_handle[i].bd_addr)))
			{
				connected_avrcp_instance = i;
				break;
			}
		}
	}
	printf ("avrcp_find_second_avrcp_instance, curr: %d, other: %d\n",current_instance, connected_avrcp_instance);
	return connected_avrcp_instance;
}

/* Function to get the status if browsing is supported or not */
UINT8 appl_avrcp_is_browsing_supported()
{
	return appl_avrcp_browsing_support;
}

AVRCP_AL_CT_CMD_INFO* appl_avrcp_get_cmd_info(void)
{
	return appl_event_recvd;
}

AVRCP_AL_VD_CMD_INFO* appl_avrcp_get_vendor_cmd_info(void)
{
	return appl_vendor_event_recvd;
}

AVRCP_AL_CT_RSP_INFO* appl_avrcp_get_rsp_info(void)
{
	return appl_avrcp_recvd_cnf;
}

void appl_reset_cmd_infos(void)
{
	appl_event_recvd = NULL;
	appl_vendor_event_recvd = NULL;
	appl_avrcp_recvd_cnf = NULL;
}
#endif /* #if (defined AVRCP_CT || defined AVRCP_TG) */
