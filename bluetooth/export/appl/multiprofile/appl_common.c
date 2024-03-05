
/**
 *  \file appl_common.c
 *
 *  Source file for Common Test Application
 */

/*
 *  Copyright (C) 2013. Mindtree Ltd.
 *  All rights reserved.
 */

/* ----------------------------------------- Header File Inclusion */
#include "appl_common.h"
/*#ifdef HCI_TX_RUN_TIME_SELECTION*/
#ifdef BT_USB
#include "hci_usb.h"
#endif /* BT_USB */

#ifdef BT_UART
#include "hci_uart.h"
#endif /* BT_UART */
/*#endif *//* HCI_TX_RUN_TIME_SELECTION */

#include "appl_a2dp.h"
#include "appl_le.h"
#include "appl_spp.h"
#include "fsm_defines.h"

/* For platform playback */
#include "sco_audio_pl.h"

/* SDP Attribute data size */
#define SDP_ATTRIB_DATALEN        1024

/* Application configuration for A2DP Role */
DECL_STATIC  UCHAR APPL_AVDTP_SEP = 0xFFU;
DECL_STATIC  UCHAR APPL_INITIATE_LINK = 0x00U;
DECL_STATIC  CHAR APPL_DEVICE_NAME[248] = "EtherMind";
DECL_STATIC  UINT32 APPL_DEVICE_CLASS = 0x26010C;

#ifdef HFP_BRIDGING
#define CVSD 1
#define MSBC 2
#define DEFAULT_SELECTED_CODEC MSBC
DECL_STATIC int appl_hf_codec = DEFAULT_SELECTED_CODEC;
#endif

#if defined(HFP_BRIDGING) && defined(A2DP_BRIDGING) && defined(AVRCP_BRIDGING)

static int appl_handle_multiprofile_menu_option(int choice);

char profile_main_options[] = "\n\
================MULTI PROFILE M A I N   M E N U ================\n\
   0.  Exit \n\
   1.  Refresh this Menu \n\
   2.  Set Snoop logging \n\
   3.  Select Codec	\n\
   4.  Scan Nearby Devices \n\
   5.  Connect Mobile \n\
   6.  Connect Headset/Speaker \n\
   7.  Create SCO connection with Unit \n\
   8.  Release SCO connection with Unit \n\
   9.  Disconnect \n\
   10. Bluetooth OFF \n\
   11. Get Track Details\n\
\n\
Your Option ?\n";
#else
char profile_main_options[] = "\n\
================MULTI PROFILE M A I N   M E N U ================\n\
   0.  Exit.\n\
   1.  Refresh this Menu.\n\
   2.  Select Role SNK(1) SRC(0).\n\
   3.  Connect. \n\
   4.  Disconnect \n\
   5.  A2DP Operations \n\
   6.  HF Operations. \n\
   7.  Set Snoop logging. \n\
   8.  Bluetooth OFF. \n\
   9.  A2DP Standalone Application. \n\
   10. HFP Bridging Application. \n\
\n\
Your Option ?\n";
#endif
#define appl_hci_get_command_name(x) "HCI_Command"

void appl_sdp_open (void);
#ifdef MULTI_PROFILE_FSM_SUPPORT
extern PROFILE_SESSION multiprofile_inst[PROFILE_MAX_INSTANCES];

/* ----------------------------------------- Exported Global Variables */
UCHAR profile_fsm_id;
/* ----------------------------------------- Static Global Variables */
PROFILE_HANDLE multiprofile_handle;
#endif /* MULTI_PROFILE_FSM_SUPPORT */

/* Peer bluetooth device address to connect to */
extern UCHAR appl_peer_bd_addr[BT_BD_ADDR_SIZE];

/* Peer device connection handle */
extern UINT16 appl_peer_acl_handle;

/* Initiator flag */
UCHAR appl_acl_initiated;

#ifdef SM_HAVE_MODE_2
DECL_STATIC UCHAR appl_sm_ui_authorization_request_reply = 0x1;
#endif /* SM_HAVE_MODE_2 */

DECL_STATIC UCHAR appl_sm_ui_connection_request_reply = 0x1;

#ifdef BT_SSP
DECL_STATIC UCHAR appl_sm_ui_user_conf_request_reply = 0x1;
DECL_STATIC UCHAR appl_sm_ui_user_conf_request_reply_bd_addr [BT_BD_ADDR_SIZE];
DECL_STATIC UCHAR appl_sm_ui_passkey_request_reply_bd_addr [BT_BD_ADDR_SIZE];
#endif /* BT_SSP */

/* SDP Application Handle */
static SDP_HANDLE appl_sdp_handle;

/* SDP Attribute Data */
static UCHAR appl_sdp_attrib_data[SDP_ATTRIB_DATALEN];

/* SDP Attribute Datalen */
static UINT16 appl_sdp_attrib_datalen;

#ifndef HCI_NO_ESCO_AUTO_ACCEPT
#ifdef BT_HCI_1_2
/*
 * If this flag is set as BT_TRUE,
 * application will set eSCO parameters
 */
DECL_STATIC UCHAR appl_hci_set_esco_connect_param;

/*
 *  To store eSCO Channel Parameters to be used while responding to
 *  eSCO Connection Request from Host Controller with Synchronous
 *  Connection Accept Command
 */
DECL_STATIC HCI_SCO_IN_PARAMS appl_esco_params;
#endif /* BT_HCI_1_2 */
#endif /* HCI_NO_ESCO_AUTO_ACCEPT */

/* Transport configuration identifier */
#ifdef HCI_TX_RUN_TIME_SELECTION
DECL_STATIC UCHAR appl_hci_transport[8];
#endif /* HCI_TX_RUN_TIME_SELECTION */

/* HCI UART configuration identifiers */
#ifdef BT_UART
DECL_STATIC CHAR appl_hci_uart_port[16];
DECL_STATIC UINT32 appl_hci_uart_baud;
#endif /* BT_UART */

#ifdef BT_VENDOR_SPECIFIC_INIT
void appl_vendor_init_complete(void);
DECL_STATIC int skip;

DECL_STATIC UCHAR *fw_array;
DECL_STATIC UINT32 fw_size;
DECL_STATIC UINT16 fw_baudrate_opcode;
#endif /* BT_VENDOR_SPECIFIC_INIT */

/* ----------------------------------------- Functions */
#ifdef INCLUDE_CONFIG
void appl_read_configuration(void)
{
    UCHAR config_str[248];
    int value;

#ifdef HCI_TX_RUN_TIME_SELECTION
    BT_mem_set(config_str, 0x00, sizeof(config_str));
    if (API_SUCCESS != BT_config_read
                       (
                           "EtherMind.conf",
                           "BT_TRANSPORT",
                           (CHAR *)config_str
                       ))
    {
        APPL_LOG("Failed to read BT_TRANSPORT from the Config\n");
    }
    else
    {
        sscanf((const char *)config_str, "%s", appl_hci_transport);
        APPL_LOG("Local HCI Transport\t\t: %s\n", appl_hci_transport);
    }

    if (0 == BT_str_cmp("UART", appl_hci_transport))
#endif /* HCI_TX_RUN_TIME_SELECTION */
#ifdef BT_UART
    {
        BT_mem_set(config_str, 0x00, sizeof(config_str));
        if (API_SUCCESS != BT_config_read
                           (
                               "EtherMind.conf",
                               "BT_UART_PORT",
                               (CHAR *)config_str
                           ))
        {
            APPL_LOG("Failed to read BT_UART_PORT from the Config\n");
        }
        else
        {
            sscanf((const char *)config_str, "%s", appl_hci_uart_port);
            APPL_LOG("HCI UART Port\t\t\t: %s\n", appl_hci_uart_port);
        }

        BT_mem_set(config_str, 0x00, sizeof(config_str));
        if (API_SUCCESS != BT_config_read
                           (
                               "EtherMind.conf",
                               "BT_UART_BAUDRATE",
                               (CHAR *)config_str
                           ))
        {
            APPL_LOG("Failed to read BT_UART_BAUDRATE from the Config\n");
        }
        else
        {
            sscanf((const char *)config_str, "%lu", &appl_hci_uart_baud);
            APPL_LOG("HCI UART Baudrate\t\t: %lu\n", appl_hci_uart_baud);
        }
    }
#endif /* BT_UART */

    BT_mem_set(config_str, 0x00, sizeof(config_str));
    if (API_SUCCESS != BT_config_read
                       (
                           "EtherMind.conf",
                           "BD_NAME",
                           (CHAR *)config_str
                       ))
    {
        APPL_LOG("Failed to read BD_NAME from the Config\n");
    }
    else
    {
        sscanf((const char *)config_str, "%s", APPL_DEVICE_NAME);
        APPL_LOG("Local Device Name\t\t: %s\n", APPL_DEVICE_NAME);
    }

    BT_mem_set(config_str, 0x00, sizeof(config_str));
    if (API_SUCCESS != BT_config_read
                       (
                           "EtherMind.conf",
                           "BD_CLASS",
                           (CHAR *)config_str
                       ))
    {
        APPL_LOG("Failed to read BD_CLASS from the Config\n");
    }
    else
    {
        sscanf((const char *)config_str, "%x", &APPL_DEVICE_CLASS);
        APPL_LOG("Local Device Class\t\t: 0x%06X\n", APPL_DEVICE_CLASS);
    }

    BT_mem_set(config_str, 0x00, sizeof(config_str));
    if (API_SUCCESS != BT_config_read
    (
        "EtherMind.conf",
        "A2DP_ROLE",
        (CHAR *)config_str
    ))
    {
        APPL_LOG("Failed to read A2DP_ROLE from the Config\n");
    }
    else
    {
        sscanf((const char *)config_str, "%X", &value);
        APPL_AVDTP_SEP = (UCHAR)value;

        APPL_LOG("A2DP Role Selected\t\t: %s\n",
            (AVDTP_SEP_SOURCE == APPL_AVDTP_SEP) ? "Source" : "Sink");
    }

    BT_mem_set(config_str, 0x00, sizeof(config_str));
    if (API_SUCCESS != BT_config_read
    (
        "EtherMind.conf",
        "CONN_INITIATE",
        (CHAR *)config_str
    ))
    {
        APPL_LOG("Failed to read CONN_INITIATE from the Config\n");
    }
    else
    {
        sscanf((const char *)config_str, "%X", &value);
        APPL_INITIATE_LINK = (UCHAR)value;

        APPL_LOG("Initiate Connection Enabled\t: %X\n", APPL_INITIATE_LINK);
    }

    BT_mem_set(config_str, 0x00, sizeof(config_str));
    if (API_SUCCESS != BT_config_read
                       (
                           "EtherMind.conf",
                           "BD_ADDRESS",
                           (CHAR *)config_str
                       ))
    {
        APPL_LOG("Failed to read BD_ADDRESS from the Config\n");
    }
    else
    {
        UCHAR  * str_temp_ptr = NULL;
        UCHAR  * str_ptr = NULL;
        INT32 index;

        APPL_LOG("Peer Device Address\t\t: %s\n", config_str);

        str_ptr = (UCHAR *)strtok((CHAR *)config_str, "-");
        str_temp_ptr = str_ptr;

        for (index = 5; index >= 0; --index)
        {
            sscanf((const char *)str_ptr, "%X", &value);
            appl_peer_bd_addr[index] = (UCHAR)value;

            if (0 == index)
            {
                break;
            }

            str_ptr = (UCHAR *)strtok(NULL, "-");

            if (NULL == str_ptr)
            {
                str_ptr = str_temp_ptr;
            }
            else
            {
                str_temp_ptr = str_ptr;
            }
        }
    }

#ifdef BT_VENDOR_SPECIFIC_INIT
    if (!skip)
    {
        BT_mem_set(config_str, 0x00, sizeof(config_str));
        if (API_SUCCESS != BT_config_read
                           (
                               "EtherMind.conf",
                               "VENDOR_FIRMWARE",
                               (CHAR *)config_str
                           ))
        {
            APPL_LOG("Failed to read FIRMWARE_FILE from the Config\n");
        }
        else
        {
            FILE *fp;

            fw_array = NULL;
            fw_size = 0;

            APPL_LOG("Loading Firmware from file\t: %s\n", config_str);

            fp = fopen(config_str, "rb");
            if (NULL != fp)
            {
                fseek(fp, 0L, SEEK_END);
                fw_size = ftell(fp);
                fseek(fp, 0L, SEEK_SET);

                fw_array = BT_alloc_mem(fw_size);

                if (NULL != fw_array)
                {
                    fread(fw_array, fw_size, 1, fp);
                }

                fclose(fp);
            }
        }
    }

    BT_mem_set(config_str, 0x00, sizeof(config_str));
    if (API_SUCCESS != BT_config_read
                       (
                           "EtherMind.conf",
                           "VENDOR_BAUDRATE_OPCODE",
                           (CHAR *)config_str
                       ))
    {
        APPL_LOG("Failed to read VENDOR_BAUDRATE_OPCODE from the Config\n");
        fw_baudrate_opcode = 0xFFFF;
    }
    else
    {
        sscanf((const char *)config_str, "%X", &fw_baudrate_opcode);

        APPL_LOG("Vendor Baudrate Opcode\t: %X\n", fw_baudrate_opcode);
    }
#endif /* BT_VENDOR_SPECIFIC_INIT */
}
#endif /* INCLUDE_CONFIG */

void appl_process_term_handler(void)
{
    printf("In Process Term Handler\n");

    printf("Turning off Bluetooth\n");

    /* Reset the Controller */
    BT_hci_reset();
    BT_sleep(1);

    /* Turn of Bluetooth stack */
    BT_bluetooth_off();
}

#ifdef MULTI_PROFILE_FSM_SUPPORT
UCHAR get_multiprofile_handle(void)
{
    return multiprofile_handle;
}

void appl_multiprofile_register(void)
{
    UCHAR count;
    printf("In Multiprofile Module Init\n");
    /* find a free Multiprofile session */
    for (count = 0U; count < PROFILE_MAX_INSTANCES; count++)
    {
        if (PROFILE_STATE_UNINITIALIZED == multiprofile_inst[count].state)
        {
            break;
        }
    }
    /* Initialize profile session */
    multiprofile_handle = count;
    /* Update FSM State */
    multiprofile_inst[multiprofile_handle].state = SL_A2DP_INITIALIZED;
}

void appl_profile_fsm_init(void)
{
    UCHAR count;
    printf("In Multiprofile FSM Module Init\n");
    /* Initialize profile session */
    for (count = 0U; count < PROFILE_MAX_INSTANCES; count++)
    {
        multiprofile_inst[count].dev_handle = 0xFFU;
        multiprofile_inst[count].prev_state = PROFILE_STATE_UNINITIALIZED;
        multiprofile_inst[count].state = PROFILE_STATE_UNINITIALIZED;
        memset (multiprofile_inst[count].bd_addr, 0U, BT_BD_ADDR_SIZE);
    }
}

void appl_profile_fsm_register(void)
{
    printf("In Multiprofile FSM Registration\n");
    /* Register with stack FSM */
    if(API_SUCCESS != fsm_register_module (&profile_fsm, &profile_fsm_id))
    {
    	printf("\n FSM registration failed\n");
    }
    return;
}
#endif /* MULTI_PROFILE_FSM_SUPPORT */

#ifndef EM_PLATFORM_MAIN
int main (int argc, char **argv)
#else /* EM_PLATFORM_MAIN */
#ifdef MULTI_PROFILE_FSM_SUPPORT
int appl_common_main (int argc, char **argv)
#else
int appl_main (int argc, char **argv)
#endif /* MULTI_PROFILE_FSM_SUPPORT */
#endif /* EM_PLATFORM_MAIN */

{
    BT_IGNORE_UNUSED_PARAM(argv);
    BT_IGNORE_UNUSED_PARAM(argc);
    API_RESULT retval;
    /*INT16 choice;*/
    int choice;
#if !(defined(HFP_BRIDGING) && defined(A2DP_BRIDGING) && defined(AVRCP_BRIDGING))
    UINT32 read_val = 0U;
    UINT16 peer_acl_handle;
    UINT16 handle;
#endif /*!(defined(HFP_BRIDGING) && defined(A2DP_BRIDGING) && defined(AVRCP_BRIDGING))*/
#ifdef BT_VENDOR_SPECIFIC_INIT
    int choice;
#endif /* BT_VENDOR_SPECIFIC_INIT */

    choice = 0U;

    /* Initialize OSAL */
    EM_os_init();
    EM_debug_init();
    EM_timer_init();
    timer_em_init();

    EM_process_term_notify(appl_process_term_handler);

#ifdef BT_VENDOR_SPECIFIC_INIT
    printf("Do Vendor Specific HCI Initialization? (Yes - 1/ No - 0): ");
    scanf("%d", &choice);
    skip = !choice;
#endif /* BT_VENDOR_SPECIFIC_INIT */

#ifdef INCLUDE_CONFIG
    /* Get the configuration */
    printf("Reading the configuration ...\n");
    appl_read_configuration();
    printf("\n");
#endif /* INCLUDE_CONFIG */

    /* Enable the transport based on configuration */
#ifdef HCI_TX_RUN_TIME_SELECTION
#ifdef BT_USB
    if (0 == BT_str_cmp("USB", appl_hci_transport))
    {
        hci_usb_enable();
    }
#endif /* BT_USB */
#ifdef BT_UART
    else if (0 == BT_str_cmp("UART", appl_hci_transport))
    {
        hci_uart_enable();
    }
#endif /* BT_UART */
#endif /* HCI_TX_RUN_TIME_SELECTION */

    /* Initialize the stack */
    printf("Initializing EtherMind ...\n");
    BT_ethermind_init();

#ifndef INCLUDE_SNOOP
    BT_snoop_logging_disable();
#endif /* INCLUDE_SNOOP */

    /* Register the transport based on configuration */
#ifdef HCI_TX_RUN_TIME_SELECTION
#ifdef BT_USB
    if (0 == BT_str_cmp("USB", appl_hci_transport))
    {
        BT_hci_register_tx_cb(hci_usb_send_data);
    }
#endif /* BT_USB */
#ifdef BT_UART
    else if (0 == BT_str_cmp("UART", appl_hci_transport))
    {
        BT_hci_register_tx_cb(hci_uart_send_data);
    }
#endif /* BT_UART */
#endif /* HCI_TX_RUN_TIME_SELECTION */

#ifdef BT_UART
#ifdef HCI_TX_RUN_TIME_SELECTION
    if (0 == BT_str_cmp("UART", appl_hci_transport))
#endif /* HCI_TX_RUN_TIME_SELECTION */
    {
        hci_uart_set_serial_settings(appl_hci_uart_port, appl_hci_uart_baud);
    }
#endif /* BT_UART */

#ifdef BT_VENDOR_SPECIFIC_INIT
    if (!skip)
    {
        if ((0 == fw_size) || (NULL == fw_array))
        {
            printf("Firmware file not found for Vendor specific Initialization...!\n");
            return -1;
        }

        app_vendor_specific_config(fw_array, fw_size, fw_baudrate_opcode);

#ifdef BT_SUPPORT_CONTROLLER_INIT_SKIP
        BT_hci_set_controller_init(BT_FALSE);
#endif /* BT_SUPPORT_CONTROLLER_INIT_SKIP */
    }
#endif /* BT_VENDOR_SPECIFIC_INIT */

    /* Do Bluetooth ON Initialization */
    printf("\nPerforming Bluetooth ON ...\n");
    retval = BT_bluetooth_on
             (
                 appl_hci_event_indication_callback,
                 appl_bluetooth_on_complete,
                 APPL_DEVICE_NAME
             );

    if (retval != API_SUCCESS)
    {
        printf("*** FAILED to Switch Bluetooth ON\n");
        return -1;
    }

    /* Initialize SPP */
    spp_appl_init();

    /* Initialize A2DP */
    a2dp_appl_init();

    /* Initialize AVRCP */
    appl_avrcp_init_handles();
    appl_avrcp_init ();

#ifdef MULTI_PROFILE_FSM_SUPPORT
    /* Initialize MultiProfile FSM module */
    appl_profile_fsm_init();

    /* Register MultiProfile with FSM Engine */
    appl_profile_fsm_register();

    /* Initialize Multiprofile Session */
    appl_multiprofile_register();
#endif /* MULTI_PROFILE_FSM_SUPPORT */
#ifdef INCLUDE_BLE
    appl_init();
#endif /* INCLUDE_BLE */

    appl_acl_initiated = BT_FALSE;

#ifdef BT_VENDOR_SPECIFIC_INIT
    if (!skip)
    {
        app_vendor_specific_init(appl_vendor_init_complete);
    }
#endif /* BT_VENDOR_SPECIFIC_INIT */


    /* Loop for the application lifetime */
    BT_LOOP_FOREVER()
    {
        printf("\n%s", profile_main_options);
        scanf("%d", &choice);
#if defined(HFP_BRIDGING) && defined(A2DP_BRIDGING) && defined(AVRCP_BRIDGING)
        appl_handle_multiprofile_menu_option(choice);
#else //defined(HFP_BRIDGING) && defined(A2DP_BRIDGING) && defined(AVRCP_BRIDGING)
        CHAR c;
        switch(choice)
        {
        case 0:
            /* Confirm on exiting */
            printf("Exit from Buetooth Main Software? (0/1):");
            scanf("%d", &choice);

            if (1 != choice)
            {
                break;
            }

            printf("\nExiting from Mindtree Bluetooth Main Software ... \n\n");

            return 0;

        case 1:
            printf("\nRefreshing ...\n\n");
            break;
        case 2:
            printf("\nSelect A2DP Role SNK(1) or SRC(0) ");
            scanf("%d", &read_val);
            //if (0xFF == APPL_AVDTP_SEP)
            {
                APPL_AVDTP_SEP = (UCHAR)read_val;

                if (AVDTP_SEP_SINK == APPL_AVDTP_SEP)
                {
                    printf("\nA2DP Role is SNK Initializing HFP Unit ...\n");
                    hfp_appl_init();
                }
                else if (AVDTP_SEP_SOURCE == APPL_AVDTP_SEP)
                {
                    printf("\nA2DP Role is SRC Initializing HF AG ...\n");
                    hf_ag_appl_init();
                }

                	a2dp_appl_start(APPL_AVDTP_SEP);

                if (AVDTP_SEP_SINK == APPL_AVDTP_SEP)
                {
                    printf("\nStarting HFP Unit ...\n");
                    hfp_appl_start();
                }
                else if (AVDTP_SEP_SOURCE == APPL_AVDTP_SEP)
                {
                    printf("\nStarting HF AG ...\n");
                    appl_start_hfp_ag();
                }
                printf("\nInitializing eSco Parameters...\n");
                appl_hci_eSco_init_params();

                printf("AVRCP is Starting...\n");
                appl_avrcp_start_handle((UCHAR)appl_avrcp_get_free_handle());
#ifdef MULTI_PROFILE_FSM_SUPPORT
                /* Update FSM State */
                PROFILE_SET_STATE (get_multiprofile_handle(), \
                	(multiprofile_inst[multiprofile_handle].state |= SL_HF_INITIALIZED));
#endif /* MULTI_PROFILE_FSM_SUPPORT */
            }
            /*else
            {
                printf("\nRole is already selected ...\n");
            }*/
            break;
        case 3:
            printf("Enter Profile (A2DP-1/SPP-2/HF-3)details\n");
            scanf("%d", &read_val);
            APPL_INITIATE_LINK = (UCHAR)read_val;

            printf("Enter Remote BD_ADDR = "); fflush(stdout);
            appl_get_bd_addr(appl_peer_bd_addr);
            retval = BT_hci_get_acl_connection_handle(&appl_peer_bd_addr, &handle);
            if(retval != API_SUCCESS)
            {
            printf("\nConnecting to ...\n");
            printf("\t    " BT_DEVICE_ADDR_ONLY_FRMT_SPECIFIER "\n",
            BT_DEVICE_ADDR_ONLY_PRINT_STR (appl_peer_bd_addr));
            retval = BT_sm_delete_device (appl_peer_bd_addr, 0x01);
            if (API_SUCCESS != retval)
            {
                printf("FAILED ! Reason = 0x%04X\n", retval);
                /*break;*/
            }
            appl_hci_connect(appl_peer_bd_addr);
            }
            else
            {
            	printf("\n ACL connection to this device is already established \n calling appl_sdp_open() to check"
            			" if HFP is supported on peer side \n");
            	appl_sdp_open();
            }
            break;
        case 4:
            printf("\nEnter acl_handle for disconnection...\n");
            scanf("%x", &choice);
            peer_acl_handle = (UINT16)choice;
            appl_hci_disconnect(peer_acl_handle);
            break;
        case 5:
            if (AVDTP_SEP_SINK == APPL_AVDTP_SEP)
            {
                printf("\nA2DP SNK Operations ...\n");
                main_a2dp_snk_operations();
            }
            else if (AVDTP_SEP_SOURCE == APPL_AVDTP_SEP)
            {
                printf("\nA2DP SRC Operations ...\n");
                main_a2dp_src_operations();
            }
            break;

        case 6:
            if (AVDTP_SEP_SOURCE == APPL_AVDTP_SEP)
            {
                main_hfp_ag_multiprofile_operations();
            }
            else if (AVDTP_SEP_SINK == APPL_AVDTP_SEP)
            {
                main_hfp_unit_multiprofile_operations();
            }
            break;

        case 7:
            printf("Set Snoop logging (0-Disable, 1-Enable): ");
            retval = appl_validate_params(&choice,1U,0U,1U);
            if (API_SUCCESS == retval)
            {
                BT_snoop_logging((UCHAR)choice);
            }
            break;

        case 8:
            printf("\nType x or X to Shut down ... \n\n");
            c = (UCHAR)getchar();
            if (('x' == c) || ('X' == c))
            {
                BT_hci_reset();

                printf("Shutting down...\n");

                BT_sleep(2);
                BT_bluetooth_off();
            }
            break;

        case 9:
            main_a2dp_operations();
            break;
        case 10:
            printf("\nChoose the operatios:\n 1. HF AG standalone\n 2. HF UNIT standalone\n");
            scanf("%d",&read_val);
            if (read_val == APPL_HFP_AG_OPERATION)
            {
                main_hfp_ag_standalone_operations();
            }
            else if(read_val == APPL_HFP_UNIT_OPERATION)
            {
                main_hfp_unit_standalone_operations();
            }
            else
            {
                printf("\n Invalid Choice\n");
            }
            break;
        default:
            printf("Invalid Choice. Try Again\n");
            break;
        }
#endif //defined(HFP_BRIDGING) && defined(A2DP_BRIDGING) && defined(AVRCP_BRIDGING)
        BT_usleep(1000);
    }
    return 0;
}

static int appl_handle_multiprofile_menu_option(int choice)
{
	API_RESULT retval = API_SUCCESS;
    UINT16 peer_acl_handle;
    UINT16 handle;
    CHAR c;
	switch(choice)
	{
	case 0:
		/* Confirm on exiting */
		printf("Exit from Buetooth Main Software? (0/1):");
		scanf("%d", &choice);

		if (1 != choice)
		{
			break;
		}

		printf("\nExiting from Mindtree Bluetooth Main Software ... \n\n");

		return 0;
	case 1:
		printf("\nRefreshing ...\n\n");
		break;
	case 2:
		printf("Set Snoop logging (0-Disable, 1-Enable): ");
		retval = appl_validate_params(&choice,1U,0U,1U);
		if (API_SUCCESS == retval)
		{
			BT_snoop_logging((UCHAR)choice);
		}
		break;
	case 3:
		printf("Enter the codec for HF init(1 - CVSD, 2 - mSBC)\n");
		scanf("%d",&appl_hf_codec);
		break;
	case 4:
		appl_reset_hci_inquiry_result();
		appl_hci_inquiry();
		break;
	case 5:
	{
		APPL_AVDTP_SEP = AVDTP_SEP_SINK;

		printf("\nA2DP Role is SNK Initializing HFP Unit ...\n");
		hfp_appl_init();

		/*Donot create/start a new sep if a free sep already exists*/
		if(0xFF == a2dp_find_free_sep_instance(APPL_AVDTP_SEP))
		{
			printf("There are no free sep instances for this role, starting a new one\n");
			a2dp_appl_start(APPL_AVDTP_SEP);
		}
		else
		{
			printf("a2dp is already started in this role\n");
		}

		printf("\nStarting HFP Unit ...\n");
		hfp_appl_start();

		printf("\nInitializing eSco Parameters...\n");
		appl_hci_eSco_init_params();
		printf("AVRCP is Starting...\n");
		appl_avrcp_start_handle((UCHAR)appl_avrcp_get_free_handle());
#ifdef MULTI_PROFILE_FSM_SUPPORT
		/* Update FSM State */
		PROFILE_SET_STATE (get_multiprofile_handle(), \
		        (multiprofile_inst[multiprofile_handle].state |= SL_AVRCP_STARTED));
#endif /* MULTI_PROFILE_FSM_SUPPORT */

#ifdef MULTI_PROFILE_FSM_SUPPORT
		/* TODO: Need to update the FSM for each instance of sink and src */
		/* Update FSM State */
		PROFILE_SET_STATE (get_multiprofile_handle(), \
				        (multiprofile_inst[multiprofile_handle].state |= SL_HF_INITIALIZED));
#endif /* MULTI_PROFILE_FSM_SUPPORT */
#ifdef CONNECT_BDADDR
		printf("Enter Remote BD_ADDR = "); fflush(stdout);
		appl_get_bd_addr(appl_peer_bd_addr);
#else
		INQUIRY_RESULT *inq_res;
		UINT32 index, dev_cnt = 0;
		inq_res = appl_get_hci_inquiry_result();
		dev_cnt = appl_print_discovered_devices();
		printf("Enter Device Index to connect from above list, if device is not present please enter 99 = "); fflush(stdout);
		scanf("%d", &index);
        if(index < dev_cnt)
        {
		BT_COPY_BD_ADDR(appl_peer_bd_addr, inq_res[index].bd_addr);
        }
        else
        {
			printf("Retry scanning the device\n"); fflush(stdout);
			retval = API_FAILURE;
        }
#endif
		if (retval == API_SUCCESS)
		{
		     retval = BT_hci_get_acl_connection_handle(appl_peer_bd_addr, &handle);
			if (retval != API_SUCCESS)
			{
				printf("\nConnecting to ...\n");
				printf("\t    " BT_DEVICE_ADDR_ONLY_FRMT_SPECIFIER "\n",
						BT_DEVICE_ADDR_ONLY_PRINT_STR (appl_peer_bd_addr));
				retval = BT_sm_delete_device(appl_peer_bd_addr, SM_ANY_LIST);
				if (API_SUCCESS != retval)
				{
					printf("FAILED ! Reason = 0x%04X\n", retval);
					/*break;*/
				}
#ifdef CONNECT_BDADDR
			appl_hci_connect(appl_peer_bd_addr);
#else
			appl_hci_connect_index(index);
#endif
			}
			else
			{
				printf("\n ACL connection to this device is already established \n calling appl_sdp_open() to check"
								" if HFP is supported on peer side \n");
				appl_sdp_open();
			}
		}
	}
	break;
	case 6:
	{
		APPL_AVDTP_SEP = AVDTP_SEP_SOURCE;

		printf("\nA2DP Role is SRC Initializing HF AG ...\n");
		hf_ag_appl_init();

		/*Donot create/start a new sep if a free sep already exists*/
		if(0xFF == a2dp_find_free_sep_instance(APPL_AVDTP_SEP))
		{
			printf("There are no free sep instances for this role, starting a new one\n");
			a2dp_appl_start(APPL_AVDTP_SEP);
		}
		else
		{
			printf("a2dp is already started in this role\n");
		}

		printf("\nStarting HF AG ...\n");
		appl_start_hfp_ag();

		printf("\nInitializing eSco Parameters...\n");
		appl_hci_eSco_init_params();

		printf("AVRCP is Starting...\n");
		appl_avrcp_start_handle((UCHAR)appl_avrcp_get_free_handle());
#ifdef MULTI_PROFILE_FSM_SUPPORT
		/* Update FSM State */
		PROFILE_SET_STATE (get_multiprofile_handle(), \
					(multiprofile_inst[multiprofile_handle].state |= SL_AVRCP_STARTED));
#endif /* MULTI_PROFILE_FSM_SUPPORT */
#ifdef MULTI_PROFILE_FSM_SUPPORT
		/* TODO: Need to update the FSM for each instance of sink and src */
		/* Update FSM State */
		PROFILE_SET_STATE (get_multiprofile_handle(), \
					(multiprofile_inst[multiprofile_handle].state |= SL_HF_INITIALIZED));
#endif /* MULTI_PROFILE_FSM_SUPPORT */

#ifdef CONNECT_BDADDR
		printf("Enter Remote BD_ADDR = "); fflush(stdout);
		appl_get_bd_addr(appl_peer_bd_addr);
#else
		INQUIRY_RESULT *inq_res;
		UINT32 index, dev_cnt = 0;
		inq_res = appl_get_hci_inquiry_result();
		printf("ins_res = %p\n",inq_res);
		dev_cnt = appl_print_discovered_devices();
		printf("Enter Device Index to connect from above list, if device is not present please enter 99 = "); fflush(stdout);
		scanf("%d", &index);
		if(index < dev_cnt)
		{
			BT_COPY_BD_ADDR(appl_peer_bd_addr, inq_res[index].bd_addr);
		}
		else
		{
			printf("Retry scanning the device\n"); fflush(stdout);
			retval = API_FAILURE;
		}
#endif
		if (retval == API_SUCCESS)
		{
		retval = BT_hci_get_acl_connection_handle(appl_peer_bd_addr, &handle);
			if (retval != API_SUCCESS)
			{
				printf("\nConnecting to ...\n");
				printf("\t    " BT_DEVICE_ADDR_ONLY_FRMT_SPECIFIER "\n",
						BT_DEVICE_ADDR_ONLY_PRINT_STR (appl_peer_bd_addr));
				retval = BT_sm_delete_device(appl_peer_bd_addr, SM_ANY_LIST);
				if (API_SUCCESS != retval)
				{
					printf("FAILED ! Reason = 0x%04X\n", retval);
					/*break;*/
				}
#ifdef CONNECT_BDADDR
			appl_hci_connect(appl_peer_bd_addr);
#else
			appl_hci_connect_index(index);
#endif
			}
			else
			{
				printf("\n ACL connection to this device is already established \n calling appl_sdp_open() to check"
								" if HFP is supported on peer side \n");
				appl_sdp_open();
			}
		}
	}
	break;
	case 7:
		appl_hfag_create_sco_connection();
		break;
	case 8:
		appl_hfag_close_voice_channel();
		break;
	case 9:
		printf("\nEnter acl_handle for disconnection...\n");
		scanf("%x", &choice);
		peer_acl_handle = (UINT16)choice;
		appl_hci_disconnect(peer_acl_handle);
		break;
	case 10:
		printf("\nType x or X to Shut down ... \n\n");
		c = (UCHAR)getchar();
		if (('x' == c) || ('X' == c))
		{
			BT_hci_reset();

			printf("Shutting down...\n");

			BT_sleep(2);
			BT_bluetooth_off();
		}
		break;
	case 11:
	{
		UCHAR index;
		index = a2dp_find_avrcp_target_instance();
		appl_avrcp_ct_send_get_element_attibutes_cmd(index);
	}
	break;
	default:
		printf("Invalid Choice. Try Again\n");
		break;
	}
	return 0;
}
#ifdef AVRCP_BRIDGING
UCHAR appl_get_sep_to_register_notification(void)
{
	return APPL_AVDTP_SEP;
}
#endif /* AVRCP_BRIDGING */

#ifdef BT_VENDOR_SPECIFIC_INIT
void appl_vendor_init_complete(void)
{
    API_RESULT retval;

    BT_bluetooth_off();

#ifdef BT_SUPPORT_CONTROLLER_INIT_SKIP
    BT_hci_set_controller_init(BT_TRUE);
    skip = 1;
#endif /* BT_SUPPORT_CONTROLLER_INIT_SKIP */

    BT_hci_set_init_command_mask(0x000001);

    /* Do Bluetooth ON Initialization */
    printf("Vendor Initialization Complete !!!\n");
    printf("\nPerforming Bluetooth ON ...\n");

    retval = BT_bluetooth_on
             (
                 appl_hci_event_indication_callback,
                 appl_bluetooth_on_complete,
                 APPL_DEVICE_NAME
             );

    if (retval != API_SUCCESS)
    {
        printf("*** FAILED to Switch Bluetooth ON\n");
    }

    return;
}
#endif /* BT_VENDOR_SPECIFIC_INIT */

API_RESULT appl_bluetooth_on_complete ( void )
{
    UCHAR bd_addr[BT_BD_ADDR_SIZE];
    /*API_RESULT retval;*/

    printf("\nBluetooth ON Initialization Completed.\n");

    /* Get the local BD Address */
    BT_hci_get_local_bd_addr(bd_addr);
    printf("Local Device Addr: %02X:%02X:%02X:%02X:%02X:%02X\n",
        bd_addr[5], bd_addr[4], bd_addr[3], bd_addr[2], bd_addr[1], bd_addr[0]);

    printf("\n");

    /* Register with BR/EDR Security Module */
    BT_sm_register_user_interface (appl_sm_ui_notify_cb);
#if defined(HFP_BRIDGING)
    /* Set controller default link policy to enable sniff and disable role-switch */
    BT_hci_write_default_link_policy_settings (0x04);
#else
	/* Set controller default link policy to enable sniff and role-switch */
    BT_hci_write_default_link_policy_settings (0x05);
#endif /*HFP_BRIDGING*/

    /* Set the Class of Device */
    BT_hci_write_class_of_device (APPL_DEVICE_CLASS);

    /* Set default pincode for Security */
    BT_sm_default_pin_code((UCHAR*)"0000", 4U);

    /* Write BR/EDR secure connections support */
    BT_hci_write_secure_connections_host_support(0x01U);

#if defined(HFP_BRIDGING) && defined(A2DP_BRIDGING) && defined(AVRCP_BRIDGING)
    /* To avoid auto-reconnect from remote device, changed scan enable value to 0x01.
     * which means, the device will be discoverable to the remote but won't accept connections.
     * With this our criteria to always be master for SCO bridging will be fullfilled.
     */
    BT_hci_write_scan_enable(0x01U);
    /*
     * Inquiry mode 0x02U returns Inquiry Result with RSSI format or
     * Extended Inquiry Result format
     */
    BT_hci_write_inquiry_mode(0x02U);
#else
    /* Make self discoverable and connectable over BR/EDR */
    BT_hci_write_scan_enable(0x03U);
#endif /* (A2DP_BRIDGING && AVRCP_BRIDGING && HFP_BRIDGING) */

    /* Start SPP */
    spp_appl_start();
#if 0
    /* Start A2DP */
    a2dp_appl_start(APPL_AVDTP_SEP);
#endif

#ifdef INCLUDE_BLE
    appl_init_complete();
#endif /* INCLUDE_BLE */

    if (0x00!= APPL_INITIATE_LINK)
    {
        appl_hci_connect(appl_peer_bd_addr);
    }

    return API_SUCCESS;
}


/* ----------------------------------------- HCI */
void appl_hci_connect(UCHAR * bd_addr)
{
    API_RESULT retval;

    retval = BT_hci_create_connection
    (
        bd_addr,
        LMP_ACL_DH5,
        0x0,
        0x0,
        0x0,
#ifdef HFP_BRIDGING
		0x0
#else
        0x1
#endif
    );

    if (retval != API_SUCCESS)
    {
        printf("FAILED !! Error Code = 0x%04x\n", retval);
    }
    else
    {
        printf("Successfully started.\n");
        printf("Please wait for Connect Complete.\n");

        appl_acl_initiated = BT_TRUE;
        BT_COPY_BD_ADDR(appl_peer_bd_addr, bd_addr);
    }
}

void appl_hci_connect_index(UINT8 index)
{
    API_RESULT retval;
    INQUIRY_RESULT* inq_res;

    inq_res = appl_get_hci_inquiry_result();

    retval = BT_hci_create_connection
    (
        inq_res[index].bd_addr,
        LMP_ACL_DH5,
        0x0,
        0x0,
        0x0,
#ifdef HFP_BRIDGING
		0x0
#else
        0x1
#endif
    );

    if (retval != API_SUCCESS)
    {
        printf("FAILED !! Error Code = 0x%04x\n", retval);
    }
    else
    {
        printf("Successfully started.\n");
        printf("Please wait for Connect Complete.\n");

        appl_acl_initiated = BT_TRUE;
        BT_COPY_BD_ADDR(appl_peer_bd_addr, inq_res[index].bd_addr);
    }
}
void appl_hci_disconnect (UINT16 acl_handle)
{
    /*BT_hci_disconnect (appl_peer_acl_handle, 0x13);*/
    printf("acl_handle 0x%x\n",acl_handle);
    BT_hci_disconnect (acl_handle, 0x13);
}

/**
 *  appl_hci_set_esco_channel_parameters
 *  This function registers the eSCO Connection Parameters.
 *
 *  \param  sco_params (IN):
 *  Pointer to the eSCO Connection Parameters to be saved,
 *  to use while accepting next eSCO Connection request.
 *
 *  \param set_sco_param (IN):
 *  Flag indicates eSCO Parameter to be set or not.
 *
 *  @return
 *          API_SUCCESS : callback function is registered successfully
 *          Error Codes : reason for the failure
 */
#ifndef HCI_NO_ESCO_AUTO_ACCEPT
#ifdef BT_HCI_1_2
API_RESULT appl_hci_set_esco_channel_parameters
           (
               /* IN */ UCHAR               set_sco_param,
               /* IN */ HCI_SCO_IN_PARAMS * sco_params
           )
{
    UCHAR enable;
    API_RESULT retval;

    /* Init */
    retval = API_SUCCESS;

    /* Null Check for eSCO parameters */
    if ((BT_TRUE == set_sco_param) && (NULL == sco_params))
    {
        printf("Unable to set NULL as eSCO parameters\n");
        retval = API_FAILURE; /* return API_FAILURE; */
    }
    else
    {
        /* Lock HCI */
        APPL_HCI_MUTEX_LOCK();

        /* Set flag */
        appl_hci_set_esco_connect_param = set_sco_param;

        if (BT_TRUE == appl_hci_set_esco_connect_param)
        {
            appl_esco_params = *(sco_params);
        }

        /* Update the audio config */
        enable =
        (LMP_VOICE_AIR_CODING_TRANSPARENT ==
        (appl_esco_params.voice_setting & LMP_VOICE_AIR_CODING_TRANSPARENT))? BT_TRUE: BT_FALSE;
        sco_audio_set_wideband_pl(enable);

        BT_hci_set_esco_channel_parameters (&appl_esco_params);

        /* Unlock HCI */
        APPL_HCI_MUTEX_UNLOCK();
    }

    return retval;
}
#endif /* BT_HCI_1_2 */
#endif /* HCI_NO_ESCO_AUTO_ACCEPT */
//To revisit, is moved to appl_common.c
void appl_hci_get_esco_channel_parameters(HCI_SCO_IN_PARAMS * esco_param)
{
    BT_mem_copy (esco_param, &appl_esco_params, sizeof(HCI_SCO_IN_PARAMS));
}
/* ----------------------------------------- Security Manager */
API_RESULT appl_sm_ui_notify_cb
           (
               UCHAR      event_type,
               UCHAR *    bd_addr,
               UCHAR *    event_data
           )
{
#ifdef BT_SSP
    UINT32 numeric_val;
#endif /* BT_SSP */

    API_RESULT retval;
    UCHAR reason, flag, pin_len;
    UCHAR pin_code [BT_PIN_CODE_SIZE];
    UCHAR link_key [BT_LINK_KEY_SIZE];

    printf("\n");
    printf("Received SM Service UI Notification. Event Type 0x%02X\n",
    event_type);

    retval = API_SUCCESS;

    switch (event_type)
    {
    case SM_ACL_CONNECT_REQUEST_NTF:
        printf("Received UI Connection Request from SM\n");
        printf(BT_DEVICE_ADDR_ONLY_FRMT_SPECIFIER " \n",
        BT_DEVICE_ADDR_ONLY_PRINT_STR (bd_addr));

        reason = (0x1 == appl_sm_ui_connection_request_reply) ? 0x0 : 0x13;

        printf("Replying to UI Connection Request ... ");
        retval = BT_sm_connection_request_reply
                 (bd_addr, appl_sm_ui_connection_request_reply, reason);

        if (retval != API_SUCCESS)
        {
            printf("FAILED ! Reason = 0x%04X\n", retval);
            break;
        }
        else
        {
            printf("OK\n");
        }

        break;

    case SM_PIN_CODE_REQUEST_NTF:
        printf("Received UI PIN Code Request from SM\n");
        printf( BT_DEVICE_ADDR_ONLY_FRMT_SPECIFIER " \n",
        BT_DEVICE_ADDR_ONLY_PRINT_STR (bd_addr));

        /* Get PIN Code from SM */
        pin_len = BT_PIN_CODE_SIZE;
        retval = BT_sm_get_pin (pin_code, &pin_len);
        if (API_SUCCESS == retval)
        {
            printf("Replying to UI PIN Code Request (+Ve) ... ");
            retval = BT_sm_pin_code_request_reply (bd_addr, pin_code, pin_len);
        }
        else
        {
            printf("Replying to UI PIN Code Request (-Ve) ... ");
            retval = BT_sm_pin_code_request_reply (bd_addr, NULL, 0);
        }

        if (retval != API_SUCCESS)
        {
            printf("FAILED ! Reason = 0x%04X\n", retval);
            break;
        }
        else
        {
            printf("OK\n");
        }

        break;

    case SM_LINK_KEY_REQUEST_NTF:
        printf("Received UI Link Key Request from SM\n");
        printf( BT_DEVICE_ADDR_ONLY_FRMT_SPECIFIER " \n",
        BT_DEVICE_ADDR_ONLY_PRINT_STR (bd_addr));

       /* Get Link Key from Device Database */
        retval = BT_sm_get_device_link_key (bd_addr, link_key);
        flag = (API_SUCCESS == retval) ? 0x1 : 0x0;

        printf("Replying to UI Link Key Request (%s) ... ",
        (API_SUCCESS == retval) ? "+Ve" : "-Ve");
        retval = BT_sm_link_key_request_reply (bd_addr, link_key, flag);

        if (retval != API_SUCCESS)
        {
            printf("FAILED ! Reason = 0x%04X\n", retval);
            break;
        }
        else
        {
            printf("OK\n");
        }

        break;

#ifdef BT_SSP
    case SM_USER_CONF_REQUEST_NTF:
        printf("Received UI User Conf Request from SM\n");
        printf(BT_DEVICE_ADDR_ONLY_FRMT_SPECIFIER " \n",
        BT_DEVICE_ADDR_ONLY_PRINT_STR (bd_addr));

        /* Get Numeric Value */
        numeric_val   = event_data[3];
        numeric_val <<= 8;
        numeric_val  |= event_data[2];
        numeric_val <<= 8;
        numeric_val  |= event_data[1];
        numeric_val <<= 8;
        numeric_val  |= event_data[0];
        printf("Numeric Value = %06d (0x%08X)\n",
               (unsigned int) numeric_val, (unsigned int) numeric_val);

        switch (appl_sm_ui_user_conf_request_reply)
        {
        case 0x0:
            /* Save BD_ADDR for Menu use */
            BT_COPY_BD_ADDR
            (
                appl_sm_ui_user_conf_request_reply_bd_addr,
                bd_addr
            );

            printf("Please Reply to User Conf Request using Menu Options\n");
            break;

        case 0x1:
            printf("Replying to UI User Conf Request ... ");
            retval = BT_sm_user_conf_request_reply (bd_addr, 0x01);
            if (retval != API_SUCCESS)
            {
                printf("FAILED ! Reason = 0x%04X\n", retval);
                break;
            }
            else
            {
                printf("OK\n");
            }

            break;

        case 0x2:
        default:
            printf("Replying to UI User Conf Request (-Ve) ... ");
            retval = BT_sm_user_conf_request_reply (bd_addr, 0x00);
            if (retval != API_SUCCESS)
            {
                printf("FAILED ! Reason = 0x%04X\n", retval);
                break;
            }
            else
            {
                printf("OK\n");
            }

            break;
        }

        break;

    case SM_USER_PASSKEY_REQUEST_NTF:
        printf("Received UI User Passkey Request from SM\n");
        printf(BT_DEVICE_ADDR_ONLY_FRMT_SPECIFIER " \n",
        BT_DEVICE_ADDR_ONLY_PRINT_STR (bd_addr));

        /* Save BD_ADDR for Menu use */
        BT_COPY_BD_ADDR
        (
            appl_sm_ui_passkey_request_reply_bd_addr,
            bd_addr
        );

        printf("Please Reply to User Passkey Request using Menu Options\n");
        break;

    case SM_USER_PASSKEY_NTF:
        printf("Received UI User Passkey Notification from SM\n");
        printf(BT_DEVICE_ADDR_ONLY_FRMT_SPECIFIER " \n",
        BT_DEVICE_ADDR_ONLY_PRINT_STR (bd_addr));

        /* Get Numeric Value */
        numeric_val   = event_data[3];
        numeric_val <<= 8;
        numeric_val  |= event_data[2];
        numeric_val <<= 8;
        numeric_val  |= event_data[1];
        numeric_val <<= 8;
        numeric_val  |= event_data[0];
        printf("Numeric Value = %u (0x%08X)\n",
        (unsigned int) numeric_val, (unsigned int) numeric_val);

        break;
#if 0
#ifdef BT_SSP_OOB
    case SM_REMOTE_OOB_DATA_REQUEST_NTF:
        break;
#endif /* BT_SSP_OOB */

    case SM_SIMPLE_PAIRING_COMPLETE_NTF:
        printf("Received UI Simple Pairing Complete from SM\n");
        printf(BT_DEVICE_ADDR_ONLY_FRMT_SPECIFIER " \n",
        BT_DEVICE_ADDR_ONLY_PRINT_STR (bd_addr));
        printf("Status = 0x%02X\n", *event_data);

        break;
#endif /* BT_SSP */
#endif
    default:
        printf("*** Unknown/Undefined Event Type 0x%02X\n", event_type);
        break;
    }

    return retval;
}

#ifdef SM_HAVE_MODE_2
API_RESULT appl_sm_service_cb
           (
               UCHAR      event_type,
               UCHAR *    bd_addr,
               UCHAR *    event_data
           )
{
    BT_IGNORE_UNUSED_PARAM(event_data);
    API_RESULT retval;
    
    printf("\n");
    printf("Received SM Service UI Notification. Event Type 0x%02X\n",
    event_type);

    retval = API_SUCCESS;

    switch (event_type)
    {
    case SM_AUTHORIZATION_REQUEST_NTF:
        printf("Received UI Authorization Request from SM\n");
        printf(BT_DEVICE_ADDR_ONLY_FRMT_SPECIFIER " \n",
        BT_DEVICE_ADDR_ONLY_PRINT_STR (bd_addr));

        printf("Replying to UI Authorization Request ... ");
        retval = BT_sm_authorization_request_reply
                 (bd_addr, appl_sm_ui_authorization_request_reply);

        if (retval != API_SUCCESS)
        {
            printf("FAILED ! Reason = 0x%04X\n", retval);
            break;
        }
        else
        {
            printf("OK\n");
        }

        break;

#ifndef BT_SSP
    case SM_AUTHORIZATION_REQUEST_NTF_MODE_1_3:
        printf("Received UI Authorization Request (Mode 1/3) from SM\n");
        printf(BT_DEVICE_ADDR_ONLY_FRMT_SPECIFIER " \n",
        BT_DEVICE_ADDR_ONLY_PRINT_STR (bd_addr));

        printf("Replying to UI Authorization Request ... ");
        retval = BT_sm_authorization_request_reply_mode_1_3
                 (bd_addr, appl_sm_ui_authorization_request_reply);

        if (retval != API_SUCCESS)
        {
            printf("FAILED ! Reason = 0x%04X\n", retval);
            break;
        }
        else
        {
            printf("OK\n");
        }

        break;
#endif  /* BT_SSP */

    default:
        printf("*** Unknown/Undefined Event Type 0x%02X\n", event_type);
        break;
    }

    return retval;
}
#endif /* SM_HAVE_MODE_2 */

/* ----------------------------------------- SDP */
void appl_sdp_open (void)
{
    /* Set the SDP handle */
    SDP_SET_HANDLE(appl_sdp_handle, appl_peer_bd_addr, appl_sdp_callback);

    /* Open channel for SDP */
    printf("appl_sdp_open: SDP Open....\n");
    BT_sdp_open(&appl_sdp_handle);

    return;
}

void appl_sdp_callback
     (
         UCHAR command,
         UCHAR * data,
         UINT16 length,
         UINT16 status
     )
{
    BT_IGNORE_UNUSED_PARAM(length);
    S_UUID  uuid;
    UINT16 num_uuids;
    UINT16  attrib_id[6];
    UINT16 num_attribute_ids;
    /*UCHAR *attribute_data = NULL;*/
    API_RESULT retval = API_FAILURE;
    S_UUID id_list[3];
    UINT16 id_list_length;
    UINT16 service_class_uuid;
    UINT128_ID uuid_128;
    UINT32     uuid_32;
    UCHAR sc_uuid_match_found;
#if !defined(HFP_BRIDGING) && defined(A2DP_BRIDGING) && defined(AVRCP_BRIDGING)
    UCHAR remote_server_channel;
#endif
    num_uuids = 0U; 
    num_attribute_ids = 0U;
    service_class_uuid = 0U;
    /* It can come only while creating connection. verify */
    if (API_SUCCESS != status)
    {
        printf("> ** FAILED performing SDP Operation: %02X\n", command);
        printf("> Return Value : 0x%04X\n", status);
    }

    switch(command)
    {
    case SDP_Open : /* SDP open callback */
    {
#if defined(HFP_BRIDGING) && defined(A2DP_BRIDGING) && defined(AVRCP_BRIDGING)
    	/* Set A2DP related UUID variables */
		uuid.uuid_type = UUID_16;

		if (AVDTP_SEP_SINK == APPL_AVDTP_SEP)
		{
			uuid.uuid_union.uuid_16 = A2DP_SOURCE_UUID;
		}
		else
    {
			uuid.uuid_union.uuid_16 = A2DP_SINK_UUID;
		}

		num_uuids = 0x01;

		/* In ascending order */
		attrib_id[0] = SERVICE_CLASS_ID_LIST;
		attrib_id[1] = PROTOCOL_DESC_LIST;
		attrib_id[2] = SUPPORTED_FEATURES_ATTR_ID;

		num_attribute_ids = 3;

		appl_sdp_attrib_datalen = SDP_ATTRIB_DATALEN;
#else
        if (APPL_INITIATE_LINK == APPL_SPP)
        {
            /* Set SPP related UUID variables */
            uuid.uuid_type = UUID_16;
            uuid.uuid_union.uuid_16 = SERIALPORT_UUID;

            num_uuids = 0x01;

            /* In ascending order */
            attrib_id[0] = SERVICE_CLASS_ID_LIST;
            attrib_id[1] = PROTOCOL_DESC_LIST;

            num_attribute_ids = 2;
        }
        else if (APPL_INITIATE_LINK == APPL_A2DP)
        {
            /* Set A2DP related UUID variables */
            uuid.uuid_type = UUID_16;

            if (AVDTP_SEP_SINK == APPL_AVDTP_SEP)
            {
                uuid.uuid_union.uuid_16 = A2DP_SOURCE_UUID;
            }
            else
            {
                uuid.uuid_union.uuid_16 = A2DP_SINK_UUID;
            }

            num_uuids = 0x01;

            /* In ascending order */
            attrib_id[0] = SERVICE_CLASS_ID_LIST;
            attrib_id[1] = PROTOCOL_DESC_LIST;
            attrib_id[2] = SUPPORTED_FEATURES_ATTR_ID;

            num_attribute_ids = 3;
        }
        else if (APPL_INITIATE_LINK == APPL_HF)
        {
            uuid.uuid_type = UUID_16;
            if (AVDTP_SEP_SINK == APPL_AVDTP_SEP)
            {
                uuid.uuid_union.uuid_16 = HFP_AG_AUDIO_GATEWAY_UUID;
            }
            else
            {
                uuid.uuid_union.uuid_16 = HFP_HFU_HANDS_FREE_UUID;
            }
            num_uuids = 0x01U;
            attrib_id[0U] = SERVICE_CLASS_ID_LIST;
            attrib_id[1U] = PROTOCOL_DESC_LIST;
            num_attribute_ids = 2;
        }

        appl_sdp_attrib_datalen = SDP_ATTRIB_DATALEN;
#endif

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
                   "BT_sdp_servicesearchattributerequest Failed\n");

            /* Close SDP */
            BT_sdp_close(&appl_sdp_handle);
        }

        break;
    }

    case SDP_Close: /* SDP Close callback */
    {
        break;
    }

    /* Service Search Attribute callback */
    case SDP_ServiceSearchAttributeResponse:
        if (API_SUCCESS == status)
        {
            sc_uuid_match_found = BT_FALSE;

            /* Profiles intended should have corresponding UUID in Service Class ID List */
            id_list_length = 3;
            retval = BT_sdp_get_ServiceClassIDList
                     (
                         data,
                         id_list,
                         &id_list_length
                     );
#if defined(HFP_BRIDGING) && defined(A2DP_BRIDGING) && defined(AVRCP_BRIDGING)
            if ((API_SUCCESS == retval) && (0 < id_list_length))
            {
            	/* First initiate A2DP connection */
            	/* Check UUID format */
				if (AVDTP_SEP_SINK == APPL_AVDTP_SEP)
				{
					service_class_uuid = A2DP_SOURCE_UUID;
				}
				else
				{
					service_class_uuid = A2DP_SINK_UUID;
				}
				switch (id_list[0].uuid_type)
				{
				case UUID_16:
					if (service_class_uuid == id_list[0].uuid_union.uuid_16)
					{
						sc_uuid_match_found = BT_TRUE;
					}
					break;

				case UUID_32:
					BT_uuid_16_to_32
					(
						service_class_uuid,
						&uuid_32
					);

					if (uuid_32 == id_list[0].uuid_union.uuid_32)
					{
						sc_uuid_match_found = BT_TRUE;
					}
					break;

				case UUID_128:
					BT_uuid_16_to_32
					(
						service_class_uuid,
						&uuid_32
					);

					BT_uuid_32_to_128
					(
						uuid_32,
						&uuid_128
					);

					if (0 == BT_mem_cmp(uuid_128.byte, id_list[0].uuid_union.uuid_128.byte, sizeof(uuid_128)))
					{
						sc_uuid_match_found = BT_TRUE;
					}
					break;
				}
				/* Service Found, Start A2DP Profile connection */
				if (BT_TRUE == sc_uuid_match_found)
				{
					printf("A2DP Service found. Connecting ...\n");
					a2dp_appl_connect(appl_peer_bd_addr);
				}
            }

#else
            if ((API_SUCCESS == retval) && (0 < id_list_length))
            {
                if (APPL_INITIATE_LINK == APPL_SPP)
                {
                    service_class_uuid = SERIALPORT_UUID;
                }
                else if (APPL_INITIATE_LINK == APPL_A2DP)
                {
                    /* Check UUID format */
                    if (AVDTP_SEP_SINK == APPL_AVDTP_SEP)
                    {
                        service_class_uuid = A2DP_SOURCE_UUID;
                    }
                    else
                    {
                        service_class_uuid = A2DP_SINK_UUID;
                    }
                }
                else if (APPL_INITIATE_LINK == APPL_HF)
                {
                    /* Check UUID format */
                    if (AVDTP_SEP_SINK == APPL_AVDTP_SEP)
                    {
                        service_class_uuid = HFP_AG_AUDIO_GATEWAY_UUID;
                    }
                    else
                    {
                        service_class_uuid = HFP_HFU_HANDS_FREE_UUID;
                    }
                }
                switch (id_list[0].uuid_type)
                {
                case UUID_16:
                    if (service_class_uuid == id_list[0].uuid_union.uuid_16)
                    {
                        sc_uuid_match_found = BT_TRUE;
                    }
                    break;

                case UUID_32:
                    BT_uuid_16_to_32
                    (
                        service_class_uuid,
                        &uuid_32
                    );

                    if (uuid_32 == id_list[0].uuid_union.uuid_32)
                    {
                        sc_uuid_match_found = BT_TRUE;
                    }
                    break;

                case UUID_128:
                    BT_uuid_16_to_32
                    (
                        service_class_uuid,
                        &uuid_32
                    );

                    BT_uuid_32_to_128
                    (
                        uuid_32,
                        &uuid_128
                    );

                    if (0 == BT_mem_cmp(uuid_128.byte, id_list[0].uuid_union.uuid_128.byte, sizeof(uuid_128)))
                    {
                        sc_uuid_match_found = BT_TRUE;
                    }
                    break;
                }
            }

            /* Service Found, Start Profile connection */
            if (BT_TRUE == sc_uuid_match_found)
            {
                if ((APPL_INITIATE_LINK == APPL_SPP) || (APPL_INITIATE_LINK == APPL_HF))
                {
                    /* Get the SPP server channel to connect */
                    printf("Get the remote server channel ...\n");
                    retval = BT_sdp_get_channel_number
                             (
                                 data,
                                 &remote_server_channel
                             );

                    if (API_SUCCESS != retval)
                    {
                        printf("Failed - 0x%04X", retval);
                    }
                    else
                    {
                        printf("Service found. Server Channel 0x%02X. Connecting ...\n",
                            remote_server_channel);

                        if (APPL_INITIATE_LINK == APPL_SPP)
                        {
                            spp_appl_connect(appl_peer_bd_addr, remote_server_channel);
                        }
                        else if (APPL_INITIATE_LINK == APPL_HF)
                        {
                            if (AVDTP_SEP_SINK == APPL_AVDTP_SEP)
                            {
                                hfp_unit_appl_connect(appl_peer_bd_addr, remote_server_channel);
                            }
                            else if (AVDTP_SEP_SOURCE == APPL_AVDTP_SEP)
                            {
                                hf_ag_appl_connect(appl_peer_bd_addr, remote_server_channel);
                            }
                        }
                    }
                }
                else if (APPL_INITIATE_LINK == APPL_A2DP)
                {
                    /* No other information required for connection */
                    printf("A2DP Service found. Connecting ...\n");
                    a2dp_appl_connect(appl_peer_bd_addr);
                }

            }
            else
            {
                printf ("Required Service not found or unexpected format\n");
            }
#endif
        }

        /* Close SDP */
        BT_sdp_close(&appl_sdp_handle);

        break;


    case SDP_ErrorResponse:

        printf("> ** ERROR occoured in SDP Query\n");

        BT_sdp_close(&appl_sdp_handle);

        break;

    default: /* Invalid: Nothing to do */
        break;

    }

    return;
}

#ifdef BT_LE
/*
 * Update Service Handle Range in SDP record
 * and activate SDP record.
 */
API_RESULT appl_update_gatt_service_range_in_sdp_record
            (
                /* IN */ UCHAR  service_type,
                /* IN */ UINT16 start_handle,
                /* IN */ UINT16 end_handle
            )
{
    UINT32 record_handle;
    API_RESULT retval;

    /* local variable to extract the supported features */
    UCHAR protocol_desc_list[] = {
                                     0x35, 0x13, 0x35, 0x06, 0x19,

                                     /* UUID L2CAP */
                                     0x01, 0x00, 0x09,

                                     /* PSM = ATT */
                                     0x00, 0x1F, 0x35, 0x09, 0x19,

                                     /* UUID ATT */
                                     0x00, 0x07, 0x09,

                                     /* Start Handle */
                                     0x00, 0x00, 0x09,

                                     /* End Handle */
                                     0x00, 0x00
                                 };

    /* Get Record Handle from SDP Database */
    retval = BT_dbase_get_record_handle (service_type, 0, &record_handle);

    if (API_SUCCESS == retval)
    {
        /* Update Start Handle */
        BT_PACK_BE_2_BYTE_VAL(&protocol_desc_list[16], start_handle);

        /* Update End Handle */
        BT_PACK_BE_2_BYTE_VAL(&protocol_desc_list[19], end_handle);

        retval = BT_dbase_update_attr_value
                 (
                     record_handle,
                     PROTOCOL_DESC_LIST,
                     protocol_desc_list,
                     sizeof (protocol_desc_list)
                 );

        if (API_SUCCESS == retval)
        {
            retval = BT_dbase_activate_record(record_handle);
        }
    }
    return retval;
}

#ifdef HFP_BRIDGING
int get_codec_selected()
{
	return appl_hf_codec;
}
#endif
#endif /* BT_LE */
