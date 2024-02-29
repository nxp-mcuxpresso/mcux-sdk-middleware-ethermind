
/**
 *  \file appl_hfp_ag.c
 *
 *  This file contains the source code of HFP AG command line application.
 *  This application uses the standard I/O for user interface (MMI).
 */

/*
 *  Copyright (C) 2013. Mindtree Ltd.
 *  All rights reserved.
 */

#define HFP_AG_1_5_RSP

/* ------------------------------------------- Header File Inclusion */
#include "appl_hfp_ag.h"
#include "appl_hfp_ag_atrsp.h"
#include "appl_utils.h"

#include "appl_hci.h"
#include "hfp_ag_pl.h"
#ifdef HFP_BRIDGING
#include "BT_hfp_unit_api.h"
#include "appl_hfp_unit.h"

/************************************************/
/*disabling multi-profile feature for sco-bridge*/
#ifdef MULTI_PROFILE_FSM_SUPPORT
#define MULTI_PROFILE_FSM_SUPPORT_REENABLE
#undef MULTI_PROFILE_FSM_SUPPORT
#endif /*MULTI_PROFILE_FSM_SUPPORT*/
/************************************************/
#endif /* HFP_BRIDGING */

#ifdef HFP_AG

/* ------------------------------------------- External Global Variables */

/* ------------------------------------------- Exported Global Variables */

/* ------------------------------------------- Static Global Variables */
/* AG data*/
DECL_STATIC CHAR appl_hfag_phnum[16U];
DECL_STATIC CHAR appl_hfag_phnum_tag[16U];
DECL_STATIC CHAR appl_hfag_brsf[8U];
DECL_STATIC UCHAR appl_hfag_inband;
DECL_STATIC UCHAR appl_hfag_vgs;
DECL_STATIC UCHAR appl_hfag_vgm;
DECL_STATIC UCHAR appl_hfag_codec;
DECL_STATIC UCHAR appl_hfag_bind[2U];
DECL_STATIC UCHAR appl_hfag_codec_negotiate;
DECL_STATIC UCHAR appl_hfag_nrec;
DECL_STATIC UCHAR appl_hfag_dial;

DECL_STATIC UINT32 appl_hfu_brsf;

DECL_STATIC UCHAR appl_handle_ret = 1;

#ifdef HFP_BRIDGING
DECL_STATIC HFP_UNIT_HANDLE appl_hfp_bridge_unit_handle;
DECL_STATIC UCHAR appl_hfag_connection_state = APPL_HF_STATE_DISCONNECTED;
#define APPL_HFP_AG_PEER_SUPPORT_INDICATORS 0x100
#define APPL_HFP_AG_LOCAL_SUPPORT_INDICATORS 0x400
#define APPL_HFP_AG_PEER_SUPPORT_THREE_WAY_CALLING 0x2
#define APPL_HFP_AG_LOCAL_SUPPORT_THREE_WAY_CALLING 0x1

/* Peer bluetooth device address to connect to */
extern UCHAR appl_peer_bd_addr[BT_BD_ADDR_SIZE];
#endif /* HFP_BRIDGING */


/* Response lookup table */
DECL_STATIC CHAR * appl_rsp_table[] = {
    HFAG_OK_STR,
    HFAG_ERROR_STR,
    HFAG_BRSF_STR,
    HFAG_BCS_STR,
    HFAG_BINP_STR,
    HFAG_VGS_STR,
    HFAG_VGM_STR,
    HFAG_BSIR_STR,
    HFAG_BIND_TEST_STR,
    HFAG_BIND_READ_STR,
    HFAG_BVRA_STR
};

void appl_hfag_read_pl(UCHAR * rsp, UINT16 rsplen);
void appl_hfag_call_status_pl(UCHAR status);
UCHAR appl_hfag_get_inbandring_status(void);

#ifdef HFP_BRIDGING

static const char multiprofile_hfp_ag_menu[] = "\n\
-------- MULTIPROFILE HFP AG Menu ------- \n\
    0.  Exit \n\
    1.  Refresh menu \n\
    2.  Call operations \n\
    3.  Set Speaker Gain \n\
    4.  Set Microphone Gain \n\
    14. Establish Synchronous Connection with Unit \n\
    15. Release Synchronous Connection with Unit \n\
\n\
Your Option -> \0";
#else
static const char multiprofile_hfp_ag_menu[] = "\n\
-------- MULTIPROFILE HFP AG Menu ------- \n\
    0.  Exit \n\
    1.  Refresh menu \n\
    2.  Call operations \n\
    3.  Set Speaker Gain \n\
    4.  Set Microphone Gain \n\
\n\
Your Option -> \0";
#endif

static const char hfp_ag_menu[] = "\n\
-------- HFP AG Menu ------- \n\
    0.  Exit \n\
    1.  Refresh menu \n\n\
    2.  Initialize HF AG \n\
    3.  Start HF AG \n\
    4.  Connect to Hands-Free Unit \n\
    5.  Disconnect From Hands-Free Unit \n\
    6.  Register Supported Features in SDP \n\
    7.  Stop HF Audio Gateway \n\
\n\
    10. Register BD_ADDR of peer(HFU) \n\
    11. Get HF-Unit SDP record \n\
    12. Create ACL Connection\n\
    13. Release ACL Connection\n\
\n\
    14. Establish Synchronous Connection with Unit \n\
    15. Release Synchronous Connection with Unit \n\
    16. Select CVSD SCO parameter set \n\
    17. Select CVSD eSCO parameter set \n\
    18. Select mSBC eSCO parameter set \n\
    19. Set eSCO parameter\n\
\n\
    20. Send AG string data\n\
    21. Send result codes to HFU \n\
\n\
    41. MemDial/Redial Support\n\
    42. ECNR Support\n\
    43. Send AG Enable Voice Recognition\n\
    44. Send AG Disable Voice Recognition\n\
    45. Send AG Enhanced Voice Recognition Msg.\n\
\n\
    60. Set InBand Ring\n\
    61. Set Default Codec\n\
    62. Set Bluetooth Indicator\n\
    63. Set Speaker Gain\n\
    64. Set Microphone Gain\n\
\n\
    65. Establish Synchronous Connection with Unit for custom eSCO parameter\n\
\n\
   100. Network Simulator \n\
\n\
Your Option -> \0";

static HFP_AG_EVENT_NOTIFY_CB appl_cb_ptr;
static UCHAR hfu_bd_addr[BT_BD_ADDR_SIZE];
static UCHAR appl_hfp_ag_state;
static UCHAR hfp_ag_local_supported_features[6U];
static UINT16 hfp_ag_local_supported_features_ext;
static UINT8 hfp_ag_server_channel;

/* HFU server channel */
static UINT8 hfp_ag_peer_server_channel;

/* SDP Handle */
DECL_STATIC SDP_HANDLE sdp_handle;

/* For PTS testing */
CHAR     appl_hfp_ag_data[128U];
UINT16   appl_hfp_ag_datalen;

/* SCO-CVSD D0-D1 settings */
DECL_STATIC HCI_SCO_IN_PARAMS appl_hfag_sco_cvsd_params[] =
{
    /* D0 */
    {
        /* For Narrow Band Speech */
        LMP_ESCO_TX_BANDWIDTH_DEFAULT,
        LMP_ESCO_RX_BANDWIDTH_DEFAULT,
        LMP_MAX_LATENCY_DONT_CARE,
        LMP_VOICE_SETTING_DEFAULT,
        (LMP_ESCO_HV1 | LMP_ESCO_2_EV3 | LMP_ESCO_3_EV3 | LMP_ESCO_2_EV5 | LMP_ESCO_3_EV5),
        LMP_RETX_EFFORT_NONE
    },

    /* D1 */
    {
        /* For Narrow Band Speech */
        LMP_ESCO_TX_BANDWIDTH_DEFAULT,
        LMP_ESCO_RX_BANDWIDTH_DEFAULT,
        LMP_MAX_LATENCY_DONT_CARE,
        LMP_VOICE_SETTING_DEFAULT,
        (LMP_ESCO_HV3 | LMP_ESCO_2_EV3 | LMP_ESCO_3_EV3 | LMP_ESCO_2_EV5 | LMP_ESCO_3_EV5),
        LMP_RETX_EFFORT_NONE
    }
};

/* eSCO-CVSD S1-S4 settings */
DECL_STATIC HCI_SCO_IN_PARAMS appl_hfag_esco_cvsd_params[] =
{
    /* Default */
    {
        /* For Narrow Band Speech */
        LMP_ESCO_TX_BANDWIDTH_DEFAULT,
        LMP_ESCO_RX_BANDWIDTH_DEFAULT,
        LMP_MAX_LATENCY_DONT_CARE,
        LMP_VOICE_SETTING_DEFAULT,
        LMP_ESCO_PACKET_TYPE_DEFAULT,
        LMP_RETX_EFFORT_DONT_CARE
    },

    /* S1 */
    {
        /* For Narrow Band Speech */
        LMP_ESCO_TX_BANDWIDTH_DEFAULT,
        LMP_ESCO_RX_BANDWIDTH_DEFAULT,
        0x0007U,
        LMP_VOICE_SETTING_DEFAULT,
        (LMP_ESCO_EV3 | LMP_ESCO_2_EV3 | LMP_ESCO_3_EV3 | LMP_ESCO_2_EV5 | LMP_ESCO_3_EV5),
        LMP_RETX_EFFORT_POWER
    },

    /* S2 */
    {
        /* For Narrow Band Speech */
        LMP_ESCO_TX_BANDWIDTH_DEFAULT,
        LMP_ESCO_RX_BANDWIDTH_DEFAULT,
        0x0007U,
        LMP_VOICE_SETTING_DEFAULT,
        (LMP_ESCO_3_EV3 | LMP_ESCO_2_EV5 | LMP_ESCO_3_EV5),
        LMP_RETX_EFFORT_POWER
    },

    /* S3 */
    {
        /* For Narrow Band Speech */
        LMP_ESCO_TX_BANDWIDTH_DEFAULT,
        LMP_ESCO_RX_BANDWIDTH_DEFAULT,
        0x000AU,
        LMP_VOICE_SETTING_DEFAULT,
        (LMP_ESCO_3_EV3 | LMP_ESCO_2_EV5 | LMP_ESCO_3_EV5),
        LMP_RETX_EFFORT_POWER
    },

    /* S4 */
    {
        LMP_ESCO_TX_BANDWIDTH_DEFAULT,
        LMP_ESCO_RX_BANDWIDTH_DEFAULT,
        0x000CU,
        LMP_VOICE_SETTING_DEFAULT,
        (LMP_ESCO_3_EV3 | LMP_ESCO_2_EV5 | LMP_ESCO_3_EV5),
        LMP_RETX_EFFORT_QUALITY
    }
};

/* eSCO-mSBC T1-T2 settings */
DECL_STATIC HCI_SCO_IN_PARAMS appl_hfag_esco_msbc_params[] =
{
#ifdef HFP_BRIDGING
	{
		/* For Wide Band Speech */
		LMP_ESCO_TX_BANDWIDTH_DEFAULT,
		LMP_ESCO_RX_BANDWIDTH_DEFAULT,
		0x000D,
		APPL_WIDEBAND_VOICE_SETTING_DEFAULT,
		0x0380,
		0x02
	},
#else //HFP_BRIDGING
    /* Default */
    {
        /* For Narrow Band Speech */
        LMP_ESCO_TX_BANDWIDTH_DEFAULT,
        LMP_ESCO_RX_BANDWIDTH_DEFAULT,
        LMP_MAX_LATENCY_DONT_CARE,
        APPL_WIDEBAND_VOICE_SETTING_DEFAULT,
        LMP_ESCO_PACKET_TYPE_DEFAULT,
        LMP_RETX_EFFORT_DONT_CARE
    },
#endif //HFP_BRIDGING

    /* T1 */
    {
        /* For Narrow Band Speech */
        LMP_ESCO_TX_BANDWIDTH_DEFAULT,
        LMP_ESCO_RX_BANDWIDTH_DEFAULT,
        0x0008U,
        APPL_WIDEBAND_VOICE_SETTING_DEFAULT,
        (LMP_ESCO_EV3 | LMP_ESCO_2_EV3 | LMP_ESCO_3_EV3 | LMP_ESCO_2_EV5 | LMP_ESCO_3_EV5),
        LMP_RETX_EFFORT_QUALITY
    },

    /* T2 */
    {
        /* For Narrow Band Speech */
        LMP_ESCO_TX_BANDWIDTH_DEFAULT,
        LMP_ESCO_RX_BANDWIDTH_DEFAULT,
        0x000DU,
        APPL_WIDEBAND_VOICE_SETTING_DEFAULT,
        (LMP_ESCO_3_EV3 | LMP_ESCO_2_EV5 | LMP_ESCO_3_EV5),
        LMP_RETX_EFFORT_QUALITY
    }
};

/* HFP eSCO Channel Default parameters */
DECL_STATIC HCI_SCO_IN_PARAMS * appl_hfag_esco_params[] =
{
    /* Default Narrowband (CVSD) parameter */
    &appl_hfag_esco_cvsd_params[0U],

    /* Default Wideband (mSBC) parameter */
    &appl_hfag_esco_msbc_params[0U]
};

void appl_send_rsp(UCHAR rsp_code, void * value);

/* Send queue for HFP AG */
DECL_STATIC APPL_HFAG_SENDELT appl_hfag_send[APPL_HFAG_SEND_QUEUE_SIZE];
DECL_STATIC UCHAR appl_hfag_sendwr;
DECL_STATIC UCHAR appl_hfag_sendrd;

/* ------------------------------------------- Functions */
void main_hfp_ag_multiprofile_operations (void)
{
    int read_val;
    int choice, menu_choice;
    API_RESULT retval;
    UCHAR  str[5] = "";
    UINT16 length,i;

    /* Init */
    /* MISRA C-2012 Rule 9.1 */
    read_val = 0;

    BT_LOOP_FOREVER()
    {
        retval = API_SUCCESS;

        printf("%s",multiprofile_hfp_ag_menu);
        scanf ("%s", str);

        length = (UINT16)BT_str_len (str);
        for (i = 0; i < length; i++)
        {
            if (!((str[i]) >= '0' && (str[i]) <= '9'))
            {
                printf ("Invalid option\n");
                retval = API_FAILURE; break; /* return; */
            }
        }

        if (API_SUCCESS == retval)
        {
            choice = appl_str_to_num(str,length);
            printf("choice is %d\n",choice);
            menu_choice = choice;

            switch(choice)
            {
            case 0: /* exit */
                break; /* return; */

            case 1: /* Refresh */
                break;
            case 2:
                hfp_ag_access_pl();
            	break;
            case 3:
                if (0U == ((appl_hfu_brsf & 0x0010U)))
                {
                    printf("Peer does not support Volume Control\n");
                    break;
                }

                printf("Enter Speaker Gain (0-15): ");
                retval = appl_validate_params(&read_val,2U,0U,15U);
                if (API_SUCCESS == retval)
                {
                    appl_hfag_vgs = (UCHAR)read_val;
                    appl_send_rsp(HFAG_VGS, NULL);
                }
                break;

            case 4:
                if (0U == ((appl_hfu_brsf & 0x0010U)))
                {
                    printf("Peer does not support Volume Control\n");
                    break;
                }

                printf("Enter Speaker Gain (0-15): ");
                retval = appl_validate_params(&read_val,2U,0U,15U);
                if (API_SUCCESS == retval)
                {
                    appl_hfag_vgm = (UCHAR)read_val;
                    appl_send_rsp(HFAG_VGM, NULL);
                }
                break;
#ifdef HFP_BRIDGING
            case 14:
				if (0U != appl_hfag_codec_negotiate)
				{
					printf("sending BCS resp\n");
					appl_send_rsp(HFAG_BCS, NULL);
				}
				else
				{
					appl_hfag_open_voice_channel(appl_hfag_codec - 1U);
				}
				break;

			case 15: /* Release Synchronous Connection with AG */
				appl_hfag_close_voice_channel();
				break;
#endif
            } /* switch */
        }/* if (API_SUCCESS == retval) */
		if (0 == menu_choice)
		{
			/* return */
			break;
		}
    }/* BT_LOOP_FOREVER */
}
/* main function for HFP AG operations */
void hf_ag_appl_init(void)
{
    API_RESULT retval;
    appl_cb_ptr = hfp_ag_appl_callback;
    retval = BT_hfp_ag_init(appl_cb_ptr);
    appl_handle_retval_from_hfag(retval);

    BT_mem_set(appl_hfag_phnum, 0, sizeof(appl_hfag_phnum));
    BT_mem_set(appl_hfag_brsf, 0, sizeof(appl_hfag_brsf));
    appl_hfag_vgs = 15U;
    appl_hfag_vgm = 15U;
#ifdef HFP_BRIDGING
    printf("HFP Bridging setting to mSBC\n");
    appl_hfag_codec = (UCHAR)get_codec_selected();
#else
    appl_hfag_codec = 1U;
#endif
    appl_hfag_nrec = 1U;
    BT_str_print(appl_hfag_phnum_tag, "%s", "+918067064000");

#ifdef HFP_BRIDGING
	appl_hfag_connection_state = APPL_HF_STATE_DISCONNECTED;
#endif //HFP_BRIDGING

    /* Init the network simulator interface */
    hfp_ag_init_pl(appl_hfag_read_pl, appl_hfag_call_status_pl, appl_hfag_get_inbandring_status);

}

void hf_ag_appl_connect(UCHAR * hfu_bd_addr, UINT8 hfp_ag_peer_server_channel)
{
    API_RESULT retval;
    retval = 0U;
    retval = BT_hfp_ag_connect
	 (
		 hfp_ag_peer_server_channel,
		 hfu_bd_addr
	 );
    appl_handle_retval_from_hfag(retval);
}

void main_hfp_ag_operations (void)
{
    int read_val;
    int choice, menu_choice;
    API_RESULT retval;
    UCHAR supported_features;
    UINT16 hci_handle;
    UCHAR  str[5] = "";
    UINT16 length,i;

    /* Init */
    /* MISRA C-2012 Rule 9.1 */
    read_val = 0;

    BT_LOOP_FOREVER()
    {
        retval = API_SUCCESS;

        printf("%s",hfp_ag_menu);
        scanf ("%s", str);

        length = (UINT16)BT_str_len (str);
        for (i = 0; i < length; i++)
        {
            if (!((str[i]) >= '0' && (str[i]) <= '9'))
            {
                printf ("Invalid option\n");
                retval = API_FAILURE; break; /* return; */
            }
        }

        if (API_SUCCESS == retval)
        {
            choice = appl_str_to_num(str,length);
            printf("choice is %d\n",choice);
            menu_choice = choice;

            switch(choice)
            {
            case 0: /* exit */
                break; /* return; */

            case 1: /* Refresh */
                break;

            case 2: /* INIT HF AG */
            	hf_ag_appl_init();
                break;

            case 3: /* Start HF AG */
                appl_start_hfp_ag();
                break;

            case 4: /* Connect to HFU */
            	hf_ag_appl_connect
				(
					hfu_bd_addr,
					hfp_ag_peer_server_channel
                );
                break;

            case 5: /* Disconnect from HFU */
                retval = BT_hfp_ag_disconnect(hfu_bd_addr);
                appl_handle_retval_from_hfag(retval);
                break;

            case 6: /* Register Supported features */
                BT_mem_set(&supported_features, 0, sizeof(supported_features));
                printf("Select Supported Features \n");
                register_features(supported_features);
                break;

            case 7: /* Stop HF AG */
                retval = BT_hfp_ag_stop();
                appl_handle_retval_from_hfag(retval);
#ifdef HFP_BRIDGING
				//For multiprofile, this will not be called - To be handled
                appl_hfag_connection_state = APPL_HF_STATE_DISCONNECTED;
#endif //HFP_BRIDGING
                break;

            case 10: /* Register BD_ADDR of HFU */
                printf ("Enter HFP Unit Bluetooth Device Address: ");
                appl_get_bd_addr(hfu_bd_addr);
                appl_handle_retval_from_hfag(retval);
                break;

            case 11: /* Get HFU's SDP record */
                /* Set the SDP Handle */
                SDP_SET_HANDLE(sdp_handle,hfu_bd_addr,appl_hfag_sdp_cb);

                /* Call SDP open */
                retval = BT_sdp_open(&sdp_handle);

                printf("> API RETVAL BT_sdp_open : 0x%04X\n",retval);
                break;

            case 12:/*create ACL Connection*/
                retval =  BT_hci_create_connection
                          (
                              hfu_bd_addr,
                              LMP_ACL_DM1|LMP_ACL_DM3|LMP_ACL_DM5|
                              LMP_ACL_DH1|LMP_ACL_DH3|LMP_ACL_DH5,
                              0U, 0U, 0U,
                              1U
                          );

                if (API_SUCCESS == retval)
                {
                    printf("> HCI Create Connection Successful\n");
                }
                else
                {
                    printf("> - Error creating ACL , API RETVAL 0x%04X\n",
                        retval);
                }
                break;

            case 13:/*release ACL connection*/
                retval = BT_hci_get_acl_connection_handle
                         (
                             hfu_bd_addr,
                             &hci_handle
                         );

                if (API_SUCCESS == retval)
                {
                    printf("Disconnecting ACL Connection 0x%04X\n",
                    hci_handle);
                }
                else
                {
                    printf ("ACL Connection for HSP-AG not found\n");
                    printf("Enter ACL Handle\n");
                    scanf("%x",&choice);
                    hci_handle = (UINT16)choice;
                }

                retval = BT_hci_disconnect
                         (
                             hci_handle,
                             0x13U
                         );

                printf("> API RETVAL ACL disconnect : 0x%04X\n", retval);
                break;

            case 14:
                if (0U != appl_hfag_codec_negotiate)
                {
                    appl_send_rsp(HFAG_BCS, NULL);
                }
                else
                {
                    appl_hfag_open_voice_channel(appl_hfag_codec - 1U);
                }
                break;

            case 15: /* Release Synchronous Connection with AG */
                appl_hfag_close_voice_channel();
                break;

            case 16:
                printf("Select CVSD SCO parameter set (0-D0, 1-D1): ");
                scanf("%d", &choice);
                appl_hfag_esco_params[0U] = &appl_hfag_sco_cvsd_params[choice];
                appl_hfag_codec = 1U;
                /* Update the SCO channel paramters for Default CVSD Codec */
                (BT_IGNORE_RETURN_VALUE) appl_hci_set_esco_channel_parameters
                (
                    BT_TRUE,
                    appl_hfag_esco_params[0U]
                );

                break;

            case 17:
                printf("Select CVSD eSCO parameter set (0-Default, 1-S1, 2-S2, 3-S3, 4-S4): ");
                scanf("%d", &choice);
                appl_hfag_esco_params[0U] = &appl_hfag_esco_cvsd_params[choice];
                appl_hfag_codec = 1U;
                /* Update the eSCO channel paramters for Default CVSD Codec */
                (BT_IGNORE_RETURN_VALUE) appl_hci_set_esco_channel_parameters
                (
                    BT_TRUE,
                    appl_hfag_esco_params[0U]
                );
                break;

            case 18:
                printf("Select mSBC eSCO parameter set (0-Default, 1-T1, 2-T2): ");
                scanf("%d", &choice);
                appl_hfag_esco_params[1U] = &appl_hfag_esco_msbc_params[choice];
                appl_hfag_codec = 2U;
                /* Update the eSCO channel paramters for Default mSBC Codec */
                (BT_IGNORE_RETURN_VALUE) appl_hci_set_esco_channel_parameters
                (
                    BT_TRUE,
                    appl_hfag_esco_params[1U]
                );
                break;

            case 19:
                appl_hfpag_change_esco_config();
                break;

            case 20:
                appl_hfp_ag_send_data();
                break;

            case 21: /* Send result code */
                printf("%s", AT_cmd_menu);
                scanf("%d", &read_val);
                if (read_val > 2U)
                {
                    appl_hfag_read_pl
                    (
                        (UCHAR*)at_cmd_option[read_val],
                        (UCHAR)BT_str_len(at_cmd_option[read_val])
                    );
                }
                else
                {
                    printf(" User Choice is not allowed. Please \n");
                    printf(" enter a choice greater than 2 \n");
                }
                break;

            case 41:
                printf("Enter Memdial/Redial support (1-Yes, 0-No): ");
                scanf("%d", &choice);
                appl_hfag_dial = (UCHAR)choice;
                break;

            case 42:
                printf("Enter ECNR support (1-Yes, 0-No): ");
                retval = appl_validate_params(&read_val,1U,0U,1U);
                if (API_SUCCESS == retval)
                {
                    appl_hfag_nrec = (UCHAR)read_val;
                }
                break;

            case 43:
                appl_hfp_ag_send_enable_voice_recognition ();
                break;

            case 44:
                appl_hfp_ag_send_disable_voice_recognition ();
                break;

            case 45:
#ifdef HFP_AG_1_8
                appl_hfp_ag_send_enh_voice_recognition ();
#else
                printf ("Please enable HFP_AG_1_8 Flag \n");
#endif /* HFP_AG_1_8 */
                break;

            case 60:
                printf("Setup Inband ring (1/0): ");
                scanf("%d", &choice);
                if ((choice < 0) || (choice > 1))
                {
                    appl_handle_ret = 0;
                    printf("Invalid choice \n");
                    break;
                }

                appl_hfag_inband = (UCHAR)choice;
                appl_hfag_read_pl
                (
                    (UCHAR*)at_cmd_option[7U - choice],
                    (UCHAR)BT_str_len(at_cmd_option[7U - choice])
                );

                break;

            case 61:
                printf("Enter Default Codec (1 - CVSD, 2 - mSBC):");
                retval = appl_validate_params(&choice,1U,1U,2U);
                if (API_SUCCESS == retval)
                {
                    if (appl_hfag_codec != choice)
                    {
                        appl_hfag_codec = (UCHAR)choice;
                        appl_hfag_codec_negotiate = 1U;

                        /* Update the eSCO channel paramters for the Codec */
                        (BT_IGNORE_RETURN_VALUE) appl_hci_set_esco_channel_parameters
                        (
                            BT_TRUE,
                            appl_hfag_esco_params[choice - 1U]
                        );
                    }
                }
                break;

            case 62:
                printf("Bluetooth Indicators:\n");
                printf("1. Enhanced Safety\n");
                printf("2. Battery Level\n");
                printf("Enter option: ");
                retval = appl_validate_params(&choice,1U,1U,2U);
                choice--;
                if (API_SUCCESS == retval)
                {
                    printf("Enter Activation (1-Enable, 0-Disable): ");
                    retval = appl_validate_params(&read_val,1U,0U,1U);
                    if (API_SUCCESS == retval)
                    {
                        appl_hfag_bind[choice] = (UCHAR)read_val;
                        appl_send_rsp(HFAG_BIND_READ, &choice);
                    }
                }

                break;

            case 63:
                if (0U == ((appl_hfu_brsf & 0x0010U)))
                {
                    printf("Peer does not support Volume Control\n");
                    break;
                }

                printf("Enter Speaker Gain (0-15): ");
                retval = appl_validate_params(&read_val,2U,0U,15U);
                if (API_SUCCESS == retval)
                {
                    appl_hfag_vgs = (UCHAR)read_val;
                    appl_send_rsp(HFAG_VGS, NULL);
                }
                break;

            case 64:
                if (0U == ((appl_hfu_brsf & 0x0010U)))
                {
                    printf("Peer does not support Volume Control\n");
                    break;
                }

                printf("Enter Speaker Gain (0-15): ");
                retval = appl_validate_params(&read_val,2U,0U,15U);
                if (API_SUCCESS == retval)
                {
                    appl_hfag_vgm = (UCHAR)read_val;
                    appl_send_rsp(HFAG_VGM, NULL);
                }
                break;

            case 65:
                appl_hfpag_create_eSCO_connection();
                break;

            case 100:
                hfp_ag_access_pl();
                break;

            default:
                printf("Invalid Choice: %d\n", choice);
                appl_handle_ret = 0;
                break;
            }/* End Switch */

            if (0 == menu_choice)
            {
                /* return */
                break;
            }

            if (appl_handle_ret == 1)
            {
                appl_handle_retval_from_hfag (retval);
            }
            appl_handle_ret = 1;
        } /* if (API_SUCCESS == retval) */
    } /* End while */
}

void appl_send_rsp(UCHAR rsp_code, void * value)
{
    CHAR response[256U];
    UCHAR length;

    /* Initialize the response */
    BT_mem_set(response, 0, sizeof(response));

    /* Copy the base response and length from the response table */
    BT_str_n_copy(response, appl_rsp_table[rsp_code], (sizeof(response) - 1));
    length = (UCHAR)BT_str_len(appl_rsp_table[rsp_code]);

    switch (rsp_code)
    {
        case HFAG_OK:
            break;

        case HFAG_ERROR:
            break;

        case HFAG_BRSF:
            BT_str_print((&response[length]), "%s\r\n", appl_hfag_brsf);
            break;

        case HFAG_BCS:
            BT_str_print((&response[length]), "%d\r\n", appl_hfag_codec);
            break;

        case HFAG_BINP:
            BT_str_print((&response[length]), "%s\r\n", appl_hfag_phnum_tag);
            break;

        case HFAG_VGS:
            BT_str_print((&response[length]), "%d\r\n", appl_hfag_vgs);
            break;

        case HFAG_VGM:
            BT_str_print((&response[length]), "%d\r\n", appl_hfag_vgm);
            break;

        case HFAG_BSIR:
            BT_str_print((&response[length]), "%d\r\n", appl_hfag_inband);
            break;

        case HFAG_BIND_TEST:
            break;

        case HFAG_BIND_READ:
            BT_str_print((&response[length]), "%d, %d\r\n", (*(UCHAR *)value + 1U), appl_hfag_bind[*(UCHAR *)value]);
            break;

        default:
            printf("Invalid Response Code: 0x%02X\n", rsp_code);
            break;
    }

    /* Update length and send response to interface */
    length = (UCHAR)BT_str_len(response);
    appl_hfag_read_pl((UCHAR *)response, length);
}


/* This function is the callback registered with HFP AG profile */
API_RESULT hfp_ag_appl_callback
           (
               /* IN */ HFP_AG_EVENTS    hfp_ag_event,
               /* IN */ API_RESULT       result,
               /* IN */ void *           data,
               /* IN */ UINT16           data_length
           )
{
    UCHAR recvd_bd_addr[BT_BD_ADDR_SIZE];
    UINT16 i;
    UCHAR* recvd_data;
    UCHAR cmd[16U];
#ifdef MULTI_PROFILE_FSM_SUPPORT
    PROFILE_EVENT_INFO profile_info;
#endif /* MULTI_PROFILE_FSM_SUPPORT */

    switch(hfp_ag_event)
    {
        case HFP_AG_CONNECT_IND:
            printf("[Appl] HFP_AG_CONNECT_IND \n");
            BT_mem_copy(hfu_bd_addr, (UCHAR*)data,data_length);
            appl_hfp_ag_state = APPL_HF_STATE_CONNECTED;

            printf(BT_DEVICE_ADDR_ONLY_FRMT_SPECIFIER,
            BT_DEVICE_ADDR_ONLY_PRINT_STR (hfu_bd_addr));
#ifdef HFP_BRIDGING
			printf("\nselected esco param index = %d\n",(get_codec_selected()-1));
			/* Update the eSCO channel parameters for Selected Codec */
			(BT_IGNORE_RETURN_VALUE) appl_hci_set_esco_channel_parameters
						(
							BT_TRUE,
							appl_hfag_esco_params[(get_codec_selected()-1)]
						);
#else //HFP_BRIDGING
            /* Update the eSCO channel paramters for Default CVSD Codec */
            (BT_IGNORE_RETURN_VALUE) appl_hci_set_esco_channel_parameters
            (
                BT_TRUE,
                appl_hfag_esco_params[0U]
            );
#endif //HFP_BRIDGING

            appl_hfag_inband = BT_TRUE;
            appl_hfag_dial = BT_TRUE;
            hfp_ag_start_pl(hfp_ag_local_supported_features_ext);
#ifdef MULTI_PROFILE_FSM_SUPPORT
            profile_info.event_type         = ev_pro_hfp_connect;
            profile_info.event_info         = PROFILE_FSM_REMOTE_EVENT;
            profile_info.profile_fsm_handle = get_multiprofile_handle();
            profile_info.data               = (UCHAR*)hfu_bd_addr;
            profile_info.datalen            = BT_BD_ADDR_SIZE;
            profile_fsm_post_event(&profile_info);
#endif /* MULTI_PROFILE_FSM_SUPPORT */
            break;

        case HFP_AG_CONNECT_CNF:
            printf("[Appl] HFP_AG_CONNECT_CNF \n");
            if(API_SUCCESS == result)
            {
                appl_hfp_ag_state = APPL_HF_STATE_CONNECTED;
                BT_mem_copy(hfu_bd_addr, (UCHAR*)data,data_length);
                printf(BT_DEVICE_ADDR_ONLY_FRMT_SPECIFIER,
                BT_DEVICE_ADDR_ONLY_PRINT_STR (hfu_bd_addr));
#ifdef HFP_BRIDGING
			printf("\nselected esco param index = %d\n",(get_codec_selected()-1));
			/* Update the eSCO channel parameters for Selected Codec */
			(BT_IGNORE_RETURN_VALUE) appl_hci_set_esco_channel_parameters
						(
							BT_TRUE,
							appl_hfag_esco_params[(get_codec_selected()-1)]
						);
#else //HFP_BRIDGING
                /* Update the eSCO channel paramters for Default CVSD Codec */
                (BT_IGNORE_RETURN_VALUE) appl_hci_set_esco_channel_parameters
                (
                    BT_TRUE,
                    appl_hfag_esco_params[0U]
                );
#endif //HFP_BRIDGING

                appl_hfag_inband = BT_TRUE;
                appl_hfag_dial = BT_TRUE;
                hfp_ag_start_pl(hfp_ag_local_supported_features_ext);
#ifdef MULTI_PROFILE_FSM_SUPPORT
                profile_info.event_type         = ev_pro_hfp_connect;
                profile_info.event_info         = PROFILE_FSM_LOCAL_EVENT;
                profile_info.profile_fsm_handle = get_multiprofile_handle();
                profile_info.data               = (UCHAR*)hfu_bd_addr;
                profile_info.datalen            = BT_BD_ADDR_SIZE;
                profile_fsm_post_event(&profile_info);
#endif /* MULTI_PROFILE_FSM_SUPPORT */
            }
            appl_handle_retval_from_hfag(result);
            break;
        case HFP_AG_DISCONNECT_IND:
            BT_mem_copy(recvd_bd_addr, (UCHAR*)data,data_length);
            printf("[Appl] HFP_AG_DISCONNECT_IND \n");

            printf(BT_DEVICE_ADDR_ONLY_FRMT_SPECIFIER,
            BT_DEVICE_ADDR_ONLY_PRINT_STR (recvd_bd_addr));

            appl_hfp_ag_state = APPL_HF_STATE_DISCONNECTED;
#ifdef HFP_BRIDGING
            appl_hfag_connection_state = APPL_HF_STATE_DISCONNECTED;
#endif /* HFP_BRIDGING */
            hfp_ag_stop_pl();
#ifdef MULTI_PROFILE_FSM_SUPPORT
            profile_info.event_type         = ev_pro_hfp_disconnect;
            profile_info.event_info         = PROFILE_FSM_REMOTE_EVENT;
            profile_info.profile_fsm_handle = get_multiprofile_handle();
            profile_info.data               = (UCHAR*)recvd_bd_addr;
            profile_info.datalen            = BT_BD_ADDR_SIZE;
            profile_fsm_post_event(&profile_info);
#endif /* MULTI_PROFILE_FSM_SUPPORT */
            break;

        case HFP_AG_DISCONNECT_CNF:
            BT_mem_copy(recvd_bd_addr, (UCHAR*)data,data_length);
            printf("[Appl] HFP_AG_DISCONNECT_CNF \n");

            printf(BT_DEVICE_ADDR_ONLY_FRMT_SPECIFIER,
            BT_DEVICE_ADDR_ONLY_PRINT_STR (recvd_bd_addr));

            appl_hfp_ag_state = APPL_HF_STATE_DISCONNECTED;
#ifdef HFP_BRIDGING
            appl_hfag_connection_state = APPL_HF_STATE_DISCONNECTED;
#endif /* HFP_BRIDGING */
            hfp_ag_stop_pl();
#ifdef MULTI_PROFILE_FSM_SUPPORT
            profile_info.event_type         = ev_pro_hfp_disconnect;
            profile_info.event_info         = PROFILE_FSM_LOCAL_EVENT;
            profile_info.profile_fsm_handle = get_multiprofile_handle();
            profile_info.data               = (UCHAR*)recvd_bd_addr;
            profile_info.datalen            = BT_BD_ADDR_SIZE;
            profile_fsm_post_event(&profile_info);
#endif /* MULTI_PROFILE_FSM_SUPPORT */
            break;

        case HFP_AG_STOP_CNF:
            printf("[Appl] HFP_AG_STOP_CNF \n");
            break;

        case HFP_AG_SEND_DATA_CNF:
            if (API_SUCCESS != result)
            {
                printf("[Appl] HFP_AG_SEND_DATA_CNF \n");
                appl_handle_retval_from_hfag(result);
            }

            if (appl_hfag_send[appl_hfag_sendrd].buf == data)
            {
                API_RESULT retval;

                BT_free_mem(appl_hfag_send[appl_hfag_sendrd].buf);
                appl_hfag_send[appl_hfag_sendrd].buf = NULL;

                if (API_SUCCESS != result)
                {
                    break;
                }

                appl_hfag_sendrd++;
                appl_hfag_sendrd &= (APPL_HFAG_SEND_QUEUE_SIZE - 1U);

                if ((appl_hfag_sendrd != appl_hfag_sendwr) &&
                    (NULL != appl_hfag_send[appl_hfag_sendrd].buf))
                {
                    retval = BT_hfp_ag_send_data
                             (
                                 appl_hfag_send[appl_hfag_sendrd].buf,
                                 appl_hfag_send[appl_hfag_sendrd].len
                             );

                    if (API_SUCCESS != retval)
                    {
                        printf("BT_hfp_ag_send_data Failed - 0x%04X\n", retval);
                        BT_free_mem(appl_hfag_send[appl_hfag_sendrd].buf);
                    }
                }
            }
            else
            {
                printf("*** Spurious Send Data Cnf ***\n");
            }
            break;

        case HFP_AG_RECVD_DATA_IND:
            printf("[Appl] HFP_AG_RECVD_ATCMD \n");
            printf("[Appl] CMD LEN : %d \n",(UINT16) data_length);

            recvd_data = (UCHAR*)data;
            for(i=0U; i<data_length;i++)
            {
                printf("%c",recvd_data[i]);
            }
            printf("\n");

#ifndef HFP_AG_NO_AUTOMATED_SLC_RESPONSE
        {
            AT_PARSER_RESPONSE at_response;
            UINT16 start_index, buffer_size, length, retval;

            /* Call the AT parser to parse the AT command sent from unit */
            length = data_length;
            buffer_size = data_length;
            start_index = 0U;

            appl_dump_bytes (recvd_data, buffer_size);

            retval = BT_ag_at_parser
                     (
                         recvd_data,
                         start_index,
                         buffer_size,
                         &length,
                         &at_response
                     );

#ifdef HFP_BRIDGING 
            /* If Both AG and UNIT devices are connected to the Bridge App,
                send the data to AG device after recieving from UNIT */
            if ((appl_hfag_connection_state == APPL_HF_STATE_CONNECTED) && (appl_hfpunit_is_unit_connected() == BT_TRUE ) &&
                    (at_response.keyword_type != AT_BCS ) && (at_response.keyword_type != AT_BCC ))
            {
                appl_hfp_bridge_unit_handle = appl_hfu_get_handle();
                CONSOLE_OUT("\n ------->> Bridge App : Sending to remote AG \n");
                retval = BT_hfp_unit_send_string
                                    (
                                        appl_hfp_bridge_unit_handle,
                                        data,
                                        data_length
                                    );

                        CONSOLE_OUT("> API RETVAL - BT_hfp_BRIDGE_AG_send_string 0x%04X\n",
                        retval);
            }
            else 
#endif /* HFP_BRIDGING */
            {
                CONSOLE_OUT("\n ---->Normal HFP APP <----\n");
            /* Handle the AT commands */
            if (API_SUCCESS == retval)
            {
                switch (at_response.keyword_type)
                {
                    case AT_BRSF:
                        appl_hfu_brsf = appl_str_to_num
                                        (
                                            &at_response.global_at_str[at_response.param->start_of_value_index],
                                            at_response.param->value_length
                                        );

                        appl_send_rsp(HFAG_BRSF, NULL);
                        appl_send_rsp(HFAG_OK, NULL);
                        appl_hfag_codec_negotiate = 0U;
                        break;

                    case AT_NREC:
                        if (!appl_hfag_nrec)
                        {
                            appl_send_rsp(HFAG_ERROR, NULL);
                        }
                        else
                        {
                            switch (at_response.global_at_str[at_response.param->start_of_value_index])
                            {
                            case '1':
                                printf("NREC Enabled\n");
                                appl_send_rsp(HFAG_OK, NULL);
                                break;

                            case '0':
                                printf("NREC Disbled\n");
                                appl_send_rsp(HFAG_OK, NULL);
                                break;

                            default:
                                appl_send_rsp(HFAG_ERROR, NULL);
                                break;
                            }
                        }
                        break;

                    case AT_BVRA:
                        switch (at_response.global_at_str[at_response.param->start_of_value_index])
                        {
                        case '1':
                            printf("VR Enabled\n");
                            appl_send_rsp(HFAG_OK, NULL);
                            appl_hfag_open_voice_channel(appl_hfag_codec - 1U);
                            break;

                        case '0':
                            printf("VR Disbled\n");
                            appl_send_rsp(HFAG_OK, NULL);
                            appl_hfag_close_voice_channel();
                            break;

                        case '2':
                            printf("EVR Enabled\n");
                            appl_send_rsp(HFAG_OK, NULL);
                            break;

                        default:
                            appl_send_rsp(HFAG_ERROR, NULL);
                            break;
                        }
                        break;

                    case AT_VGS:
                        appl_hfag_vgs = (UCHAR)appl_str_to_num
                                               (
                                                   &at_response.global_at_str[at_response.param->start_of_value_index],
                                                   at_response.param->value_length
                                               );
                        printf("Speaker Gain Updated - %d\n", appl_hfag_vgs);
                        appl_send_rsp(HFAG_OK, NULL);
                        break;

                    case AT_VGM:
                        appl_hfag_vgm = (UCHAR)appl_str_to_num
                                               (
                                                   &at_response.global_at_str[at_response.param->start_of_value_index],
                                                   at_response.param->value_length
                                               );
                        printf("Microphone Gain Updated - %d\n", appl_hfag_vgm);
                        appl_send_rsp(HFAG_OK, NULL);
                        break;

                    case AT_BINP:
                        appl_send_rsp(HFAG_BINP, NULL);
                        appl_send_rsp(HFAG_OK, NULL);
                        break;

                    case AT_BCC:
                        appl_send_rsp(HFAG_OK, NULL);
                        appl_send_rsp(HFAG_BCS, NULL);
                        break;

                    case AT_BCS:
                        appl_send_rsp(HFAG_OK, NULL);

                        appl_hfag_codec_negotiate = 0U;

                        /* Trigger codec connection */
                        appl_hfag_open_voice_channel
                        ((at_response.global_at_str[at_response.param->start_of_value_index] - '0') - 1U);
                        break;

                    case AT_BAC:
                        appl_send_rsp(HFAG_OK, NULL);
                        appl_hfag_codec_negotiate = 1U;
#ifdef HFP_BRIDGING
                        appl_hfag_codec = get_codec_selected();
#else
                        appl_hfag_codec = 1U;
#endif
                        break;

                    case AT_BIND_TEST:
                        appl_send_rsp(HFAG_BIND_TEST, NULL);
                        appl_send_rsp(HFAG_OK, NULL);
                        break;

                    case AT_BIND_READ:
                        for (i = 0U; i < sizeof(appl_hfag_bind); i++)
                        {
                            appl_send_rsp(HFAG_BIND_READ, &i);
                        }
                        appl_send_rsp(HFAG_OK, NULL);
#ifdef HFP_BRIDGING
                       /* As per HFP v1.8 spec, if Ag has responded to AT+BIND and both 
                          AG and unit supports Indicators then we can consider the SLC done here.
                        */
                        if ((appl_hfag_connection_state == APPL_HF_STATE_DISCONNECTED) && (0U != (appl_hfu_brsf & APPL_HFP_AG_PEER_SUPPORT_INDICATORS )) &&
                              (0U != (hfp_ag_local_supported_features_ext & APPL_HFP_AG_LOCAL_SUPPORT_INDICATORS)))
                                {
                                    appl_hfag_connection_state = APPL_HF_STATE_CONNECTED;
                                }
#endif /* HFP_BRIDGING */
                        break;

                    case AT_BIND:
                        appl_send_rsp(HFAG_OK, NULL);
                        break;

                    case AT_BIEV:
                        if (2U < (at_response.global_at_str[at_response.param->start_of_value_index] - '0'))
                        {
                            appl_send_rsp(HFAG_ERROR, NULL);
                        }
                        else
                        {
                            appl_send_rsp(HFAG_OK, NULL);
                        }
                        break;

                    case ATD:
                        /* Hold the phone number */
                        BT_str_n_copy
                        (
                            appl_hfag_phnum,
                            &at_response.global_at_str[at_response.param->start_of_value_index],
                            (sizeof(appl_hfag_phnum) - 1)
                        );
                        hfp_ag_write_pl(recvd_data, buffer_size);
                        break;

                    case ATDM:    /* Fall Through */
                    case AT_BLDN:
                        if (0U == appl_hfag_dial)
                        {
                            appl_send_rsp(HFAG_ERROR, NULL);
                            break;
                        }

                        BT_mem_set(cmd, 0, sizeof(cmd));
                        BT_str_print((CHAR *)cmd, "ATD7654321;\r");
                        hfp_ag_write_pl(cmd, (UINT16)BT_str_len(cmd));
                        break;

                    default:
                        hfp_ag_write_pl(recvd_data, buffer_size);
                        break;
                }
#ifdef HFP_BRIDGING
                if(appl_hfag_connection_state == APPL_HF_STATE_DISCONNECTED)
                {
                /* As per HFP v1.8 spec, if either AG or unit doesn't support Indicator but it 
                   supports Three way calling and have responded to AT+CHLD command, then 
                   SLC can be considerd to be done here.
                */
                    if((at_response.keyword_type == AT_CHLD_TEST) && 
                       ((0U == (appl_hfu_brsf & APPL_HFP_AG_PEER_SUPPORT_INDICATORS)) || 
                           (0U == (hfp_ag_local_supported_features_ext & APPL_HFP_AG_LOCAL_SUPPORT_INDICATORS))) &&
                              ((0U != (appl_hfu_brsf & APPL_HFP_AG_PEER_SUPPORT_THREE_WAY_CALLING)) && 
                               (0U != (hfp_ag_local_supported_features_ext & APPL_HFP_AG_LOCAL_SUPPORT_THREE_WAY_CALLING))))
                                {
                                    appl_hfag_connection_state = APPL_HF_STATE_CONNECTED;
                                }
                /* As per HFP v1.8 spec, if either AG or unit doesn't support both Indicator and 
                   Three way calling  but it has responded to AT+CMER command, then 
                   SLC can be considerd to be done here.
                */
                    else if((at_response.keyword_type == AT_CMER) &&
                            ((0U == (appl_hfu_brsf & APPL_HFP_AG_PEER_SUPPORT_INDICATORS)) || 
                               (0U == (hfp_ag_local_supported_features_ext & APPL_HFP_AG_LOCAL_SUPPORT_INDICATORS)))&&
                                 ((0U == (appl_hfu_brsf & APPL_HFP_AG_PEER_SUPPORT_THREE_WAY_CALLING)) || 
                                 (0U == (hfp_ag_local_supported_features_ext & APPL_HFP_AG_LOCAL_SUPPORT_THREE_WAY_CALLING))))
                                    {
                                        appl_hfag_connection_state = APPL_HF_STATE_CONNECTED;
                                    }
                }
#endif /* HFP_BRIDGING */
            }
            else
            {
                appl_send_rsp(HFAG_ERROR, NULL);
            }
            }
        }
#endif /* !HFP_AG_NO_AUTOMATED_SLC_RESPONSE */
        break;

        default:
        printf("Invalid Event: 0x%02X\n", hfp_ag_event);
        break;
    }

    return API_SUCCESS;
}

/* Function to handle API return values from HFP AG */
void appl_handle_retval_from_hfag ( /* IN */ UINT16 retval)
{
    switch(retval)
    {
    case API_SUCCESS:
        /*printf("[Appl] API_SUCCESS\n");*/
        break;
    case HFP_AG_ERR_NULL_PARAMETER:
        printf("[Appl] HFP_AG_ERR_NULL_PARAMETER\n");
        break;
    case HFP_AG_MUTEX_INIT_FAILED:
        printf("[Appl] HFP_AG_MUTEX_INIT_FAILED \n");
        break;
    case HFP_AG_ERR_INVALID_PARAMETER:
        printf("[Appl] HFP_AG_ERR_INVALID_PARAMETER\n");
        break;
    case HFP_AG_ERR_INVALID_STATE:
        printf("[Appl] HFP_AG_ERR_INVALID_STATE\n");
        break;
    case HFP_AG_ERR_STOP_PENDING:
        printf("[Appl] HFP_AG_ERR_STOP_PENDING\n");
        break;
    case HFP_AG_MUTEX_LOCK_FAILED:
        printf("[Appl] HFP_AG_MUTEX_LOCK_FAILED\n");
        break;
    case HFP_AG_MUTEX_UNLOCK_FAILED:
        printf("[Appl] HFP_AG_MUTEX_UNLOCK_FAILED\n");
        break;

    default:
        printf("[Appl] Result: 0x%04X\n", retval);
        break;
    } /* End Switch */

    return;
}


/* Function to process user choice for supported features */
void register_features( /* IN */ UCHAR supported_features)
{
    int choice;
    int feature_choice;

    do
    {
        printf("\n");
        printf("    0. exit without register\n");
        printf("    1. Three Way Call Support\n");
        printf("    2. EC and/or NR function\n");
        printf("    3. Voice Recognition function\n");
        printf("    4. InBand-Ring Tone Capability\n");
        printf("    5. Attach a phone number to voice tag\n");
        printf("    6. Network Call-Reject Ability\n");
        printf("    7. Enable all supported features\n");
        printf("    8. Register with SDP\n");

        printf("\n  Your choice :");

        scanf("%d",&choice);

        switch(choice)
        {
        case 0:
           break;

        case 1:
           printf("    Enter 1-Yes 0-No :");
           scanf("%d", &feature_choice);
           if(0 != feature_choice)
           {
               supported_features |= SET_AG_CCWA;
           }
           else
           {
               supported_features &= RESET_AG_CCWA;
           }
           break;

        case 2:
            printf("    Enter 1-Yes 0-No :");
            scanf("%d", &feature_choice);
            if(0 != feature_choice)
            {
                supported_features |= SET_AG_ECNR;
            }
            else
            {
                supported_features &= RESET_AG_ECNR;
            }
            break;

        case 3:
            printf("    Enter 1-Yes 0-No :");
            scanf("%d", &feature_choice);
            if(0 != feature_choice)
            {
                supported_features |= SET_AG_BVRA;
            }
            else
            {
                supported_features &= RESET_AG_BVRA;
            }
            break;

        case 4:
            printf("    Enter 1-Yes 0-No :");
            scanf("%d", &feature_choice);
            if(0 != feature_choice)
            {
                supported_features |= SET_AG_BSIR;
            }
            else
            {
                supported_features &= RESET_AG_BSIR;
            }
            break;

        case 5:
            printf("    Enter 1-Yes 0-No :");
            scanf("%d", &feature_choice);
            if(0 != feature_choice)
            {
               supported_features |= SET_AG_BINP;
            }
            else
            {
                supported_features &= RESET_AG_BINP;
            }
            break;

        case 6:
            printf("    Enter 1-Ability to reject a call \n");
            printf("    Enter 0-No ability to reject a call \n");
            scanf("%d", &feature_choice);
            break;

        case 7:
            /* Enable all features here */
            supported_features |= SET_ALL_FEATURES;
            printf(" Enabled all supported features \n");

            break;

        case 8:
            hfp_ag_register_supp_feat(supported_features);
            break;

        default:
            printf("Invalid Choice \n");
            break;
         }
    } while(choice != 0U && choice != 8U);

    return;
}


/* Function to register Supported features with local SDP Database */
void hfp_ag_register_supp_feat ( /* IN */ UCHAR supported_features)
{
    UCHAR  attr_value[] = {0x09U, 0x00U, 0x00U};
    UINT32 hfp_ag_record_handle;
    UINT16 hfp_ag_supp_features;

    /* Get HF AG SDP record handle */
    if (API_SUCCESS == BT_dbase_get_record_handle(DB_RECORD_HFAG, 1U, &hfp_ag_record_handle))
    {
        hfp_ag_supp_features = supported_features;

        attr_value[1U] = (UCHAR)(hfp_ag_supp_features >> 8U);
        attr_value[2U] = (UCHAR)(hfp_ag_supp_features);

        if(API_SUCCESS != BT_dbase_update_attr_value
                          (
                              hfp_ag_record_handle,
                              HFP_AG_SUPP_FEATURES_ATTR_ID,
                              attr_value,
                              0x03U
                          ))
        {
            printf("HFP AG SUPP_FEAT_REG_FAILED \n");
        }
    }

    return;
}


/* Function to activate HFP AG SDP record and Start HFAG */
void appl_start_hfp_ag (void)
{
    API_RESULT api_retval;
    UINT32 hfp_ag_record_handle;
#ifdef MULTI_PROFILE_FSM_SUPPORT
    STATE_T    state;
    PROFILE_EVENT_INFO profile_info;
#endif /* MULTI_PROFILE_FSM_SUPPORT */
    /* local varibale to extract the supported features */
    UCHAR  attr_value[] = {0x09U, 0x00U, 0x00U};
    UINT16 str_len, hfp_ag_feature, i;
    UCHAR  hfp_ag_str[6U];

#ifdef MULTI_PROFILE_FSM_SUPPORT
    state = 00U;
#endif /* MULTI_PROFILE_FSM_SUPPORT */
#if 0
    printf("HF supported feature bitmap\n");
    printf("\tBit\tFeature\n");
    printf("\t---\t-------\n");
    printf("\t 0  \t3-way calling\n");
    printf("\t 1  \tEC and/or NR function\n");
    printf("\t 2  \tVoice recognition function\n");
    printf("\t 3  \tIn-band ringtone capability\n");
    printf("\t 4  \tAttach a number to a voice tag\n");
    printf("\t 5  \tAbility to reject a call\n");
    printf("\t 6  \tEnhanced call status\n");
    printf("\t 7  \tEnhanced call control\n");
    printf("\t 8  \tExtended Error result codes\n");

#ifdef HFP_UNIT_1_6
    printf("\t 9  \tCodec Negotiation\n");
#endif /* HFP_UNIT_1_6 */

#ifdef HFP_UNIT_1_7
    printf("\t 10  \tHF Indicators\n");
    printf("\t 11  \teSCO S4 Settings Supported\n");
#endif /* HFP_UNIT_1_7 */

#ifdef HFP_UNIT_1_8
    printf("\t 12 \tEnhanced Voice Recognition Status\n");
    printf("\t 13 \tVoice Recognition Text\n");
#endif /* HFP_UNIT_1_8 */

    printf("Enter Local HFP_AG Supported Features(as Decimal value)\n:");
    scanf("%s", hfp_ag_local_supported_features);
#endif
    BT_mem_set(hfp_ag_str, 0x00, sizeof(hfp_ag_str));
    /*BT_str_n_copy(hfp_ag_str ,hfp_ag_local_supported_features, (sizeof(hfp_ag_str) - 1));*/
#ifdef HFP_BRIDGING
    if(get_codec_selected() == 2/*mSBC*/)
    {
    BT_str_n_copy(hfp_ag_local_supported_features ,"16383", 6);
    BT_str_n_copy(hfp_ag_str ,"16383", 6);
    }
    else if(get_codec_selected() == 1/*CVSD*/)
    {
    	BT_str_n_copy(hfp_ag_local_supported_features ,"15871", 6);
    	BT_str_n_copy(hfp_ag_str ,"15871", 6);
    }
#else
    BT_str_n_copy(hfp_ag_local_supported_features ,"16383", 6);
    BT_str_n_copy(hfp_ag_str ,"16383", 6);
#endif
    str_len = (UINT16)BT_str_len(hfp_ag_str);

    hfp_ag_feature  = (UINT16)appl_str_to_num(hfp_ag_local_supported_features, str_len);
    /* Init */
    api_retval = API_SUCCESS;

    for (i = 0; i < str_len; i++)
    {
        if ((!((hfp_ag_str[i]) >= '0' && (hfp_ag_str[i]) <= '9')) || ( (hfp_ag_feature < HFP_AG_MIN_SUPP_FEATURE_RANGE) || (hfp_ag_feature > HFP_AG_MAX_SUPP_FEATURE_RANGE) ) )
        {
            api_retval =  HFP_AG_ERR_INVALID_PARAMETER;
            appl_handle_ret = 0;
            appl_handle_retval_from_hfag(api_retval);
            break; /* return; */
        }
    }

    if (API_SUCCESS == api_retval)
    {
        appl_handle_ret = 1;

        hfp_ag_local_supported_features[HFP_UNIT_MAX_SUPP_FEATURE_LEN - 1U] = '\0';
        BT_str_n_copy(appl_hfag_brsf, hfp_ag_local_supported_features, HFP_UNIT_MAX_SUPP_FEATURE_LEN);

        /* Local Supported Features in Numeric Format */
        hfp_ag_local_supported_features_ext = (UINT16)appl_str_to_num
                                                      (
                                                          hfp_ag_local_supported_features,
                                                          (UINT16)BT_str_n_len(hfp_ag_local_supported_features, HFP_UNIT_MAX_SUPP_FEATURE_LEN)
                                                      );

        attr_value[1U] = hfp_ag_local_supported_features[0U];
        attr_value[2U] = hfp_ag_local_supported_features[1U];

        /* Get HFP_UNIT SDP record handle */
        (BT_IGNORE_RETURN_VALUE) BT_dbase_get_record_handle
        (
            DB_RECORD_HFAG,
            0U,
            &hfp_ag_record_handle
        );

        api_retval = BT_dbase_update_attr_value
                     (
                         hfp_ag_record_handle,
                         0x0311U,
                         attr_value,
                         0x03U
                     );

        api_retval = BT_dbase_get_server_channel
                     (
                         hfp_ag_record_handle,
                         PROTOCOL_DESC_LIST,
                         &hfp_ag_server_channel
                     );
        printf("[Appl] HFP AG Server Channel %02x\n",hfp_ag_server_channel);
        api_retval = BT_hfp_ag_start(hfp_ag_server_channel);

        if(API_SUCCESS == api_retval)
        {
            appl_hfp_ag_state = APPL_HF_STATE_DISCONNECTED;

            (BT_IGNORE_RETURN_VALUE) BT_dbase_activate_record(hfp_ag_record_handle);

            printf("\n[Appl] HFP AG Profile Started Successfully\n");
#ifdef MULTI_PROFILE_FSM_SUPPORT
            profile_info.event_type         = 0U;
            profile_info.event_info         = 0U;
            profile_info.profile_fsm_handle = get_multiprofile_handle();
            profile_info.data               = NULL;
            profile_info.datalen            = 0U;
            profile_access_state_handler(&profile_info, &state);
            state |= SL_HF_STARTED;
            profile_set_state_handler(&profile_info, state);
#endif /* MULTI_PROFILE_FSM_SUPPORT */
        }
        else
        {
            appl_handle_retval_from_hfag(api_retval);
        }
    }

    return;
}


/* SDP Callback for HFP */
void appl_hfag_sdp_cb
     (
         UCHAR command,
         UCHAR * data,
         UINT16 length,
         UINT16 status
     )
{
    S_UUID  uuid;
    UINT16 num_uuids;
    UINT16  attrib_id[2U];
    UINT16 num_attribute_ids = 2U ;
    UCHAR *attribute_data = NULL;
    API_RESULT retval = API_SUCCESS;

    UINT16 len_attrib_data;

    /* Length of supported features */
    /* UINT16 support_len = 2; */

    BT_IGNORE_UNUSED_PARAM(length);

    /* Set AG related UUID variables */
    uuid.uuid_type = UUID_16;
    uuid.uuid_union.uuid_16 = HFP_HFU_HANDS_FREE_UUID;
    num_uuids = 0x01U;

#ifdef HFP_BRIDGE
    attrib_id[0U] = SERVICE_CLASS_ID_LIST;
    attrib_id[1U] = PROTOCOL_DESC_LIST;
#else
    attrib_id[0U] = PROTOCOL_DESC_LIST;
    attrib_id[1U] = SUPPORTED_FEATURES_ATTR_ID;
#endif

    /* It can come only while creating connection. verify */
    if (API_SUCCESS != status)
    {
        printf("> ** FAILED performing SDP Operation: %02X\n", command);
        printf("> Return Value : 0x%04X\n", status);

        /* Implies that SDP open wa successful but service search failed */
        if(command == SDP_ServiceSearchAttributeResponse)
        {
            (BT_IGNORE_RETURN_VALUE) BT_sdp_close(&sdp_handle);
            retval = API_FAILURE; /*  return; */
        }
    }

    if (API_SUCCESS == retval)
    {
        switch(command)
        {
        case SDP_Open : /* SDP open callback */
        {
            attribute_data = BT_alloc_mem (100U);

            if(NULL == attribute_data)
            {
                printf("> ** FAILED to Allocate memory for SDP Query\n");

                /* Close SDP */
                (BT_IGNORE_RETURN_VALUE) BT_sdp_close(&sdp_handle);
                /* return; */
            }
            else
            {
                len_attrib_data = 100U;

                /* Do Service Search Request */
                retval = BT_sdp_servicesearchattributerequest
                         (
                             &sdp_handle,
                             &uuid,
                             num_uuids,
                             attrib_id,
                             num_attribute_ids,
                             NULL,
                             0x00U,
                             attribute_data,
                             &len_attrib_data
                         );

                if (API_SUCCESS != retval)
                {
                    printf("> ** "\
                           "BT_sdp_servicesearchattributerequest Failed\n");

                    BT_free_mem (attribute_data);

                    printf("> Closing SDP Connection\n");

                    /* Close SDP */
                    (BT_IGNORE_RETURN_VALUE) BT_sdp_close(&sdp_handle);

                    /* return; */
                }
            }
            /* SDP operation to continue */

            break;
        }

        case SDP_Close: /* SDP Close callback */
        {
               break;
        }

        /* Service Search Attribute callback */
        case SDP_ServiceSearchAttributeResponse:
            /* From the response extract the server channel */
            retval = BT_sdp_get_channel_number
                     (
                         data,
                         &hfp_ag_peer_server_channel
                     );

            printf("> Remote SERVER CHANNEL 0x%02X\n",\
            hfp_ag_peer_server_channel);

            if(API_SUCCESS != retval)
            {
                BT_free_mem(data);

                printf("> ** FAILED to get Remote SERVER CHANNEL\n");

                (BT_IGNORE_RETURN_VALUE) BT_sdp_close(&sdp_handle);
                /* return; */
            }
            else
            {
#if 0
                /* From the response extract the remote supported features */
                if( BT_sdp_get_attr_value
                    (
                        attrib_id[1],
                        data,
                        (UCHAR *)&hfp_unit_peer_supported_features[0],
                        &support_len
                    ) != API_SUCCESS )
                {
                    printf("> ** FAILED to extract the remote supported"\
                    "features\n");
                    sdp_close_due2error = 2;

                }
                else
                {
                    printf("> AG Supported features %X\n", \
                    hfp_unit_peer_supported_features[0]);

                }
#endif /* 0 */
#ifdef HFP_BRIDGING
                hf_ag_appl_connect
				(
					appl_peer_bd_addr,
					hfp_ag_peer_server_channel
				);
#endif
                /* Free allocated memory for attribute data */
                BT_free_mem(data);

                /* Close SDP */
                (BT_IGNORE_RETURN_VALUE) BT_sdp_close(&sdp_handle);
            }

            break;


        case SDP_ErrorResponse:

            printf("> ** ERROR occoured in SDP Query\n");

            /* Free allocated memory for attribute data */
            BT_free_mem(data);

            (BT_IGNORE_RETURN_VALUE) BT_sdp_close(&sdp_handle);

            break;

        default: /* Invalid: Nothing to do */
            printf("Invalid Command: 0x%02X\n", command);
            break;

        }/* switch */
    }

    return;
}

void appl_hfp_ag_send_data(void)
{
    CHAR     ag_rsp_data[64U];

    BT_mem_set(appl_hfp_ag_data, 0, sizeof(appl_hfp_ag_data));
    BT_mem_set(ag_rsp_data, 0, sizeof(ag_rsp_data));

    printf ("Enter AT cmd/rsp string\n");
    scanf("%s", ag_rsp_data);

    BT_str_n_copy (appl_hfp_ag_data, HFP_CR_LF, BT_str_len(HFP_CR_LF));
    BT_str_n_cat (appl_hfp_ag_data, ag_rsp_data, (sizeof(appl_hfp_ag_data) - BT_str_len(appl_hfp_ag_data)));
    BT_str_n_cat (appl_hfp_ag_data, HFP_CR_LF, (sizeof(appl_hfp_ag_data) - BT_str_len(appl_hfp_ag_data)));

    appl_hfp_ag_datalen = (UCHAR )BT_str_len(appl_hfp_ag_data);

    printf ("== HFP AG data ==\n");

#if 0
    printf ("HFP AG datalen:%d\n", appl_hfp_ag_datalen);
    printf ("== HFP AG data(in CHAR frmt) ==\n");
    for (i = 0; i < appl_hfp_ag_datalen; i++)
    {
        printf ("%c", appl_hfp_ag_data[i]);
    }
    printf ("\n=================\n");

    printf ("== HFP AG data(in HEX frmt) ==\n");
    for (i = 0; i < appl_hfp_ag_datalen; i++)
    {
        printf ("%02X", appl_hfp_ag_data[i]);
    }
    printf ("\n=================\n");

#else
    appl_dump_bytes ((UCHAR *)appl_hfp_ag_data, appl_hfp_ag_datalen);
#endif /* 0 */

    /**
     * Yes, Send data received from HFP Unit RFCOMM Transport to
     * remote HFP Unit through HFP AG
     */
    appl_hfag_read_pl
    (
        (UCHAR *)appl_hfp_ag_data,
        appl_hfp_ag_datalen
    );

    return;
}

void appl_hfp_ag_send_enable_voice_recognition (void)
{
    if (0U == (appl_hfu_brsf & 0x0008U))
    {
        printf("HFU does not support VR feature\n");
        /* return; */
    }
    else
    {
        appl_hfag_read_pl
        (
            (UCHAR *)HFP_AG_ENABLE_VOICE_REG,
            (UCHAR)BT_str_len(HFP_AG_ENABLE_VOICE_REG)
        );

        appl_hfag_open_voice_channel(appl_hfag_codec - 1U);
    }

    return;
}

void appl_hfp_ag_send_disable_voice_recognition (void)
{
    if (0U == (appl_hfu_brsf & 0x0008U))
    {
        printf("HFU does not support VR feature\n");
        /* return; */
    }
    else
    {
        appl_hfag_read_pl
        (
            (UCHAR *)HFP_AG_DISABLE_VOICE_REG,
            (UCHAR)BT_str_len(HFP_AG_DISABLE_VOICE_REG)
        );

        appl_hfag_close_voice_channel();
    }

    return;
}

#ifdef HFP_AG_1_8
void appl_hfp_ag_send_enh_voice_recognition (void)
{
    CHAR response[128U];
    int choice;
    CHAR *text[] = { "Hi", "Hello", "Hello?", "Hello!" };
    CHAR *str;

    if (0U == (appl_hfu_brsf & 0x0400U))
    {
        printf("HFU does not support EVR feature\n");
        /* return; */
    }
    else
    {
        BT_mem_set(response, 0, sizeof(response));

        printf("VRECStates:\n");
        printf("Bit 0: Ready to Accept Audio Input\n");
        printf("Bit 1: Sending Audio to HF\n");
        printf("Bit 2: Processing Audio Input\n");
        printf("Enter the VRECState: ");
        scanf("%d", &choice);

        BT_str_print(response, "%s%d,", HFP_AG_ENH_VR_MSG, choice);

        if (0U != (appl_hfu_brsf & 0x0800U))
        {
            printf("Text ID (2 octet Max):\n");
            scanf("%d", &choice);
            BT_str_print((&response[BT_str_len(response)]), "%04X,", choice);

            printf("Enter Text Type (0: HF IP, 1: AG OP 2: AG OP Question, 3: AG OP Error): ");
            scanf("%d", &choice);
            BT_str_print((&response[BT_str_len(response)]), "%d,", choice);
            str = text[choice];
            printf("Enter Text Operation (1: New, 2: Replace, 3: Append): ");
            scanf("%d", &choice);
            BT_str_print((&response[BT_str_len(response)]), "%d,", choice);

            BT_str_print((&response[BT_str_len(response)]), "\"%s\"\r\n", str);
        }

        appl_hfag_read_pl
        (
            (UCHAR *)response,
            (UCHAR)BT_str_len(response)
        );
    }

    return;
}
#endif /* HFP_AG_1_8 */

void appl_hfpag_change_esco_config(void)
{
#ifdef BR_EDR_HCI
    int read_val;

    HCI_SCO_IN_PARAMS esco_params;
    UINT16  max_latency;
    UINT16  packet_type;
    UCHAR   rtx_effort;

    /*packet type input*/
    printf("packet type (in Hex) = "); fflush(stdout);
    scanf("%x", &read_val);
    packet_type = (UINT16)read_val;

    /*latency input*/
    printf("latency (in Hex) = "); fflush(stdout);
    scanf("%x", &read_val);
    max_latency = (UINT16)read_val;

    /*retransmission effort*/
    printf("retransmission effort (in Hex) = "); fflush(stdout);
    scanf("%x", &read_val);
    rtx_effort = (UCHAR)read_val;

    appl_hci_get_esco_channel_parameters(&esco_params);
    esco_params.packet_type = packet_type;
    esco_params.max_latency = max_latency;
    esco_params.rtx_effort = rtx_effort;

    /* Update the eSCO channel paramters for Default mSBC Codec */
    appl_hci_set_esco_channel_parameters
    (
        BT_TRUE,
        &esco_params
    );

#else
    printf("Feature flag BR_EDR_HCI is not defined\n");
#endif /* BR_EDR_HCI */
}

/*command to create eSCO connection with custom eSCO parameter set using command 19*/
void appl_hfpag_create_eSCO_connection(void)
{
    API_RESULT retval;
    UINT16 hci_handle;
    HCI_SCO_IN_PARAMS esco_params;
    /*
    * Establish Synchronous Connection with selected setting
    * with UNIT
    */
    retval = BT_hci_get_acl_connection_handle
             (
                 hfu_bd_addr,
                 &hci_handle
             );

    if (API_SUCCESS == retval)
    {
        appl_hci_get_esco_channel_parameters(&esco_params);

        printf("> API RETVAL BT_hci_setup_synchronous_connection\n");

        retval = BT_hci_setup_synchronous_connection
                 (
                     hci_handle,
                     &esco_params
                 );
    }

    if (API_SUCCESS != retval)
    {
        printf("FAILED !! Error Code = 0x%04x\n", retval);
    }
}

void appl_hfag_open_voice_channel(UCHAR codec)
{
    API_RESULT retval;
    UINT16 hci_handle;
    HCI_SCO_IN_PARAMS hfp_ag_esco_param;
    printf("codec = %d\n", codec);
    printf(BT_DEVICE_ADDR_ONLY_FRMT_SPECIFIER "  ",
                BT_DEVICE_ADDR_ONLY_PRINT_STR(hfu_bd_addr));
    /**
     * Establish Synchronous Connection with selected setting
     * with AG
     */
    retval = BT_hci_get_acl_connection_handle
             (
                 hfu_bd_addr,
                 &hci_handle
             );

    if (API_SUCCESS == retval)
    {
        /* get default eSCO parameter set */
        appl_hci_get_esco_channel_parameters(&hfp_ag_esco_param);

        hfp_ag_esco_param.voice_setting = appl_hfag_esco_params[codec]->voice_setting;

        /* Update the eSCO channel paramters for Codec */
        (BT_IGNORE_RETURN_VALUE) appl_hci_set_esco_channel_parameters
        (
            BT_TRUE,
            &hfp_ag_esco_param
        );

        printf("> API RETVAL BT_hci_setup_synchronous_connection, voice setting = %d\n", hfp_ag_esco_param.voice_setting);

        retval = BT_hci_setup_synchronous_connection
                 (
                     hci_handle,
                     &hfp_ag_esco_param
                 );
    }

    if (API_SUCCESS != retval)
    {
        printf("FAILED !! Error Code = 0x%04x\n", retval);
    }
}

void appl_hfag_close_voice_channel(void)
{
    API_RESULT retval;
    UINT16 hci_sco_handles[HCI_MAX_SCO_CHANNELS];
    UCHAR num_of_sco_handles;

    /* MISRA C-2012 Rule 9.1 | Coverity UNINIT */
    BT_mem_set(hci_sco_handles, 0, sizeof(UINT16)*HCI_MAX_SCO_CHANNELS);

    retval = BT_hci_get_sco_connection_handle
                (
                    hfu_bd_addr,
                    hci_sco_handles,
                    &num_of_sco_handles
                );

    /* If SCO/eSCO connection present, disconect the first one */
    if (API_SUCCESS == retval)
    {
        printf("Disconnecting SCO/eSCO Connection 0x%04X\n",
        hci_sco_handles[0U]);

        retval = BT_hci_disconnect
                 (
                     hci_sco_handles[0U],
                     0x13U
                 );
    }
    else
    {
        printf ("SCO Connection for HFP-Unit not found\n");
    }
}


void appl_hfag_read_pl(UCHAR * rsp, UINT16 rsplen)
{
    API_RESULT retval;
    UCHAR * buf;

    if (APPL_HF_STATE_CONNECTED != appl_hfp_ag_state)
    {
        printf("Invalid State for read operation\n");
        /* return; */
    }
    else
    {
        /* Allocate memory */
        buf = BT_alloc_mem(rsplen);
        if (NULL == buf)
        {
            printf("Failed to allocate buffer\n");
            /* return; */
        }
        else
        {
            /* Copy the data */
            BT_mem_copy(buf, rsp, rsplen);

            /* Add it to the queue */
            appl_hfag_send[appl_hfag_sendwr].buf = buf;
            appl_hfag_send[appl_hfag_sendwr].len = rsplen;

            retval = API_SUCCESS;

            /* Is Tx ongoing? */
            if (appl_hfag_sendwr == appl_hfag_sendrd)
            {
                retval = BT_hfp_ag_send_data
                         (
                             buf,
                             rsplen
                         );

                if (API_SUCCESS != retval)
                {
                    printf("BT_hfp_ag_send_data Failed - 0x%04X\n", retval);
                    BT_free_mem(buf);
                }
            }

            if (API_SUCCESS == retval)
            {
                appl_hfag_sendwr++;
                appl_hfag_sendwr &= (APPL_HFAG_SEND_QUEUE_SIZE - 1U);
            }
        }
    }
}

void appl_hfag_callend_timeout_handler(void * args, UINT16 size)
{
    BT_IGNORE_UNUSED_PARAM(args);
    BT_IGNORE_UNUSED_PARAM(size);

    appl_hfag_close_voice_channel();
}

void appl_hfag_call_status_pl(UCHAR status)
{
    BT_timer_handle tmr_handle;
#ifdef MULTI_PROFILE_FSM_SUPPORT
    STATE_T    state;
    PROFILE_EVENT_INFO profile_info;

    profile_info.event_type         = 0U;
    profile_info.event_info         = 0U;
    profile_info.profile_fsm_handle = get_multiprofile_handle();
    profile_info.data               = NULL;
    profile_info.datalen            = 0U;
    profile_access_state_handler(&profile_info, &state);

    if ((0x03U & status) && (state & SL_HF_CONNECTED))
    {
        PROFILE_EVENT_INFO profile_info;
        profile_info.event_type         = ev_pro_hfp_sco_connect;
        profile_info.event_info         = PROFILE_FSM_LOCAL_EVENT;
        profile_info.profile_fsm_handle = get_multiprofile_handle();
        profile_info.data               = (UCHAR*)hfu_bd_addr;
        profile_info.datalen            = BT_BD_ADDR_SIZE;
        profile_fsm_post_event(&profile_info);
    }
#endif /* MULTI_PROFILE_FSM_SUPPORT */
    switch (status)
    {
    case 0x00U: /* Call End */
        (BT_IGNORE_RETURN_VALUE) BT_start_timer(&tmr_handle, 1U, appl_hfag_callend_timeout_handler, NULL, 0U);
        break;

    case 0x01U: /* Call Active */
        if (!appl_hfag_inband)
        {
            if (0U != appl_hfag_codec_negotiate)
            {
                appl_send_rsp(HFAG_BCS, NULL);
            }
            else
            {
                appl_hfag_open_voice_channel(appl_hfag_codec - 1U);
            }
        }
        break;

    case 0x02U: /* Call Incoming */
    case 0x03U: /* Call Outgoing */
        if (0U != appl_hfag_inband)
        {
            if (0U != appl_hfag_codec_negotiate)
            {
                appl_send_rsp(HFAG_BCS, NULL);
            }
            else
            {
                appl_hfag_open_voice_channel(appl_hfag_codec - 1U);
            }
        }
        break;
#if 0
    case 0x03U: /* Call Outgoing */
        if (0U != appl_hfag_codec_negotiate)
        {
            appl_send_rsp(HFAG_BCS, NULL);
        }
        else
        {
            appl_hfag_open_voice_channel(appl_hfag_codec - 1U);
        }
        break;
#endif
    default:
        printf("Invalid Status: 0x%02X\n", status);
        break;
    }
}

UCHAR appl_hfag_get_inbandring_status(void)
{
    return appl_hfag_inband;
}

#ifdef HFP_BRIDGING
UINT8 appl_hfpag_is_ag_connected()
 {
    if (appl_hfp_ag_state == BT_TRUE)
	    return BT_TRUE;
	else
	   return BT_FALSE;
 }
void appl_hfag_create_sco_connection()
{
	if (0U != appl_hfag_codec_negotiate)
	{
		printf("sending BCS resp\n");
		appl_send_rsp(HFAG_BCS, NULL);
	}
	else
	{
		appl_hfag_open_voice_channel(appl_hfag_codec - 1U);
	}
}

void appl_get_hfag_sdp_record (UCHAR * bd_addr)
{
    printf("appl_get_hfag_sdp_record: SDP Open....\n");
    /* Set the SDP handle */
    SDP_SET_HANDLE(sdp_handle, bd_addr, appl_hfag_sdp_cb);
    API_RESULT ret = BT_sdp_open(&sdp_handle);
    printf("appl_get_hfunit_sdp_record: SDP Open ret %x\n", ret);

    return;
 }
#endif /* HFP_BRIDGING */

#ifdef HFP_BRIDGING
/***************************************/
/*Re-enabling global multi-profile macro for other files*/
#ifdef MULTI_PROFILE_FSM_SUPPORT_REENABLE
#define MULTI_PROFILE_FSM_SUPPORT
#undef MULTI_PROFILE_FSM_SUPPORT_REENABLE
#endif /*MULTI_PROFILE_FSM_SUPPORT_REENABLE*/
/****************************************/
#endif /*HFP_BRIDGING*/

#endif /* HFP_AG */
