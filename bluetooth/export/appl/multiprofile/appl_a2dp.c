/**
 *  \file appl_a2dp.c
 *
 *  Source file for A2DP Command Line Test Application
 */

/*
 *  Copyright (C) 2013. Mindtree Ltd.
 *  All rights reserved.
 */

/* ----------------------------------------- Header File Inclusion */
#include "appl_a2dp.h"
#include "appl_avrcp.h"
#include "appl_common.h"
#include "a2dp_pl.h"
#include "appl_utils.h"
#ifdef MULTI_PROFILE_FSM_SUPPORT
#include "BT_avrcp_al_api.h"
#include "BT_avrcp_api.h"
#include "profile_fsm_engine.h"
#include "profile_fsm_handlers.h"
#endif /* MULTI_PROFILE_FSM_SUPPORT */

#ifdef A2DP

#define AVDTP_A2DP_CHAINED_CONNECT

#define APPL_A2DP_MTU                       672

#define A2DP_APPL_MAX(a, b) ((a) > (b))? (a): (b)
#define A2DP_APPL_MIN(a, b) ((a) < (b))? (a): (b)

/* ----------------------------------------- Exported Global Variables */
UCHAR sep_type_selected;
HCI_CONNECTION_LIST appl_avrcp_acl_list [BT_MAX_REMOTE_DEVICES];
AVRCP_HANDLE appl_avrcp_handle [AVRCP_MAX_PROFILES];
/* A2DP Codec Instances */
A2DP_APPL_INSTANCE a2dp_appl_instance [A2DP_MAX_CODECS];
/* ----------------------------------------- Static Global Variables */
/* Source Identifier */

/* AVDTP Handle */
static AVDTP_HANDLE a2dp_appl_avdtp_handle;

/* Buffer for AVDTP Discover Response */
static UCHAR a2dp_appl_sep_info_buf [A2DP_MAX_DISCOVER_RESPONSE_LEN];

/* Pointer to start of Discover Response Info Element */
static UCHAR * a2dp_appl_sep_info_buf_start;

/* Actual response buffer length */
static UINT16 a2dp_appl_sep_info_buflen;

/* Buffer for AVDTP Get Capability Response */
static UCHAR a2dp_appl_sep_cap_buf [A2DP_GET_CAPABILITIES_RESPONSE_LEN];

/* A2DP Codec Information Element for SBC */
static UCHAR a2dp_appl_sbc_codec_ie[A2DP_SBC_CODEC_CAP_IE_LEN];

/* A2DP Service Record Handle */
static UINT32 a2dp_record_handle;

/* Peer bluetooth device address to connect to */
extern UCHAR appl_peer_bd_addr[BT_BD_ADDR_SIZE];

#ifdef AVDTP_HAVE_CONTENT_PROTECTION
UCHAR * cp_ie_buf = NULL;
UCHAR   cp_ie_buf_len = 0;
UCHAR   a2dp_cp_header [1];
UINT16  a2dp_cp_header_len;
#endif /* AVDTP_HAVE_CONTENT_PROTECTION */

#ifdef INCLUDE_A2DP_CODEC
#ifdef A2DP_SINK
#ifndef A2DP_BRIDGING
static JPL_PARAM jpl_param;
static UCHAR * appl_a2dp_jpl_pof;
static UINT16 appl_a2dp_jpl_poflen;
static void appl_a2dp_jpl_configure(UCHAR * codec_ie);
static API_RESULT jpl_callback_handle
       (
           /* IN */ UCHAR   event_type,
           /* IN */ UCHAR * event_data,
           /* IN */ UINT16  event_datalen
       );
static void a2dp_pl_snk_callback
       (
           /* IN */ const UCHAR *  p_data,
           /* IN */ UINT16   p_datalen
       );
#endif /*A2DP_BRIDGING*/
#endif /* A2DP_SINK */
#ifdef A2DP_SOURCE
#define APP_A2DP_SRC_WR_TH_INIT                 0x01
#define APP_A2DP_SRC_WR_TH_STOP                 0x02
#define APP_A2DP_SRC_WR_TH_PLAYING              0x03

#define A2DP_SRC_SBC_BLOCK_MAX                  512

/* A2DP Src PCM Queue Size, should be a power of 2 value */
#define A2DP_SRC_MAX_BUFFER_SIZE                4096

/* Write thread state */
static UINT8 a2dp_src_wr_th_state;

/* Buffers and Rd/Wr indices */
static INT32 a2dp_src_buffer_rd_ptr;
static INT32 a2dp_src_buffer_wr_ptr;
static INT32 a2dp_src_buffer_size;
static UCHAR a2dp_src_buffer[A2DP_SRC_MAX_BUFFER_SIZE];
static UCHAR pcm_to_send[A2DP_SRC_SBC_BLOCK_MAX];

/* Synchronization for thread */
BT_DEFINE_MUTEX (a2dp_src_th_mutex)
BT_DEFINE_COND (a2dp_src_th_cond)

/* SBC Encoder Input/Output Structure */
static SBC_ENCODER_IO_STRUCT a2dp_sbc_encoder_io;
#ifndef A2DP_BRIDGING
/* Size of PCM Data used for encoding one SBC frame */
static UINT16 appl_a2dp_pcm_datalen;
#endif /* A2DP_BRIDGING */
/* Buffer for converting UCHAR pcm stream to UINT16 pcm samples */
static UINT16 appl_a2dp_pcm_data_le [SBC_BLOCK_MAX >> 1];

/* Buffer used to hold encoded SBC data */
static UCHAR appl_a2dp_sbc_data[SBC_BLOCK_MAX];
#ifndef A2DP_BRIDGING
void appl_a2dp_src_prepare(void);
#endif /* A2DP_BRIDGING */
API_RESULT app_a2dp_src_enqueue
          (
              /* IN */  const UCHAR   * data,
              /* IN */  UINT16    datalen
          );
DECL_STATIC void *a2dp_src_write_task (void * args);

API_RESULT a2dp_encode_n_send
           (
               UINT8    a2dp_instance,
               UCHAR  * pcm_data,
               UINT16   pcm_datalen
           );
#ifndef A2DP_BRIDGING
static void a2dp_pl_src_callback
       (
           /* IN */ const UCHAR *  r_data,
           /* IN */ UINT16   r_datalen
       );
#endif /* A2DP_BRIDGING */
#endif /* A2DP_SOURCE */
#endif /* INCLUDE_A2DP_CODEC */

void a2dp_appl_handle_avdtp_discover_rsp (void);

/* Maximum Allowed Payload Length */
static UINT16 a2dp_max_allowed_payload_len;

static UCHAR a2dp_codec_instance;

void appl_a2dp_avrcp_disconnect(UCHAR * bd_addr);

API_RESULT a2dp_appl_avdtp_notify_cb
           (
               UCHAR             event_type,
               UINT16            event_result,
               AVDTP_HANDLE *    avdtp_handle,
               void *            event_data,
               UINT16            event_datalen
           );
API_RESULT a2dp_appl_notify_cb
           (
               UCHAR    codec_instance,
               UCHAR    event_type,
               UINT16   event_result,
               void  *  event_data,
               UINT16   event_datalen
           );

char a2dp_src_menu[] = "\n\
================A2DP SRC M E N U ================\n\
   0.  Exit.\n\
   1.  Refresh this Menu.\n\
   2.  A2DP Start.\n\
   3.  A2DP Suspend. \n\
   4.  Set Volume. \n\
\n\
Your Option ?\n";

char a2dp_snk_menu[] = "\n\
================A2DP SNK M E N U ================\n\
   0.  Exit.\n\
   1.  Refresh this Menu.\n\
   2.  PLAY. \n\
   3.  PAUSE. \n\
   4.  Set Volume. \n\
\n\
Your Option ?\n";
/* ----------------------------------------- Functions */
void main_a2dp_src_operations (void)
{
    int choice, menu_choice;
    UCHAR avrcp_index = AVRCP_MAX_PROFILES;
    //avrcp_index = appl_avrcp_get_connected_handle((UCHAR*)a2dp_appl_instance[a2dp_codec_instance].bd_addr);
    /* first remote sink bdaddr is taken for avrcp_index
     * TODO: if more sinks are connected need to take the info from user 
     */
    for (int index = 0; index < A2DP_MAX_CODECS; index++)
    {
        if (AVDTP_SEP_SOURCE == a2dp_appl_instance[index].role)
        {
            avrcp_index = appl_avrcp_get_connected_handle((UCHAR*)a2dp_appl_instance[index].bd_addr);
            printf("operations to be performed on \t    " BT_DEVICE_ADDR_ONLY_FRMT_SPECIFIER "\n",BT_DEVICE_ADDR_ONLY_PRINT_STR(a2dp_appl_instance[index].bd_addr));
            /* Matching instance found */
            break;
        }
    }
    if(avrcp_index == AVRCP_MAX_PROFILES)
    {
        printf("Invalid avrcp_index = %d\n",avrcp_index);
        return;
    }
    BT_LOOP_FOREVER()
    {
        printf("%s", a2dp_src_menu); fflush(stdin);
        scanf("%d", &choice);

        menu_choice = choice;

        switch (choice)
        {
        case 0:
            break; /* return; */

        case 1:
            break;

        case 2:
            {
                UCHAR indx;
                a2dp_appl_get_instance(&indx);
                appl_a2dp_stream_start(indx);
            }
            break;

        case 3:
            {
                UCHAR indx;
                a2dp_appl_get_instance(&indx);
                appl_a2dp_stream_suspend(indx);
            }
            break;

        case 4:
            if (AVRCP_MAX_PROFILES > avrcp_index)
            {
                appl_avrcp_ct_send_set_absolute_volume_cmd(avrcp_index);
            }
            else
            {
                printf("AVRCP index is not free for volume operations\n");
            }
            break;

        default:
            printf("Invalid Choice. Try Again\n");
            break;
        }
        if (0 == menu_choice)
        {
            /* return */
            break;
        }
    }/* BT_LOOP_FOREVER() */
    return;
}

void main_a2dp_snk_operations (void)
{
    int choice, menu_choice;
    UCHAR avrcp_index = AVRCP_MAX_PROFILES;
    //avrcp_index = appl_avrcp_get_connected_handle((UCHAR*)a2dp_appl_instance[a2dp_codec_instance].bd_addr);
    //printf ("[PROFILE_FSM_HANDLER]: avrcp_index  %02X \n", avrcp_index);
    /* first remote src bdaddr is taken for avrcp_index
     * TODO: if more srcs are connected need to take the info from user
     */
    for (int index = 0; index < A2DP_MAX_CODECS; index++)
    {
        if (AVDTP_SEP_SINK == a2dp_appl_instance[index].role)
        {
            avrcp_index = appl_avrcp_get_connected_handle((UCHAR*)a2dp_appl_instance[index].bd_addr);
            printf("operations to be performed on \t    " BT_DEVICE_ADDR_ONLY_FRMT_SPECIFIER "\n", BT_DEVICE_ADDR_ONLY_PRINT_STR(a2dp_appl_instance[index].bd_addr));
            /* Matching instance found */
            break;
        }
    }
    if(avrcp_index == AVRCP_MAX_PROFILES)
    {
        printf("Invalid avrcp_index = %d\n",avrcp_index);
        return;
    }
    BT_LOOP_FOREVER()
    {
        printf("%s", a2dp_snk_menu); fflush(stdin);
        scanf("%d", &choice);

        menu_choice = choice;

        switch (choice)
        {
        case 0:
            break; /* return; */

        case 1:
            break;

        case 2:
            appl_avrcp_ct_send_passthrough_cmd_variables(avrcp_index, 1U, AVRCP_OPERATION_ID_PLAY);
            break;

        case 3:
            appl_avrcp_ct_send_passthrough_cmd_variables(avrcp_index, 1U, AVRCP_OPERATION_ID_PAUSE);
            break;

        case 4:
            appl_avrcp_ct_send_set_absolute_volume_cmd(avrcp_index);
            break;

        default:
            printf("Invalid Choice. Try Again\n");
            break;
        }
        if (0 == menu_choice)
        {
            /* return */
            break;
        }
    }/* BT_LOOP_FOREVER() */
    return;
}

void a2dp_appl_init (void)
{
    API_RESULT retval;
    UINT8 choice;
#ifdef INCLUDE_A2DP_CODEC
#ifdef A2DP_SINK
#ifndef A2DP_BRIDGING
#ifdef JPL_USE_APP_MEMORY
    JPL_BUFFERS buffer;
#endif /* JPL_USE_APP_MEMORY */
#endif /* A2DP_BRIDGING */
#endif /* A2DP_SINK */
#endif /* INCLUDE_A2DP_CODEC */
    printf("Initializing A2DP ... ");
    retval = BT_a2dp_init();
    if (API_SUCCESS != retval)
    {
        printf("FAILED. Reason = 0x%04X\n", retval);
    }
    else
    {
        printf("OK\n");
    }

#ifdef A2DP_SOURCE
    a2dp_max_allowed_payload_len = 0;
#endif /* A2DP_SOURCE */

    for (choice = 0; choice < A2DP_MAX_CODECS; choice ++)
    {
    	a2dp_appl_free_instance((UCHAR)choice);
        a2dp_appl_connect_info_reset((UCHAR)choice);

    }

    /* Register AVDTO Async Event Indication Callback */
    BT_avdtp_callback_register (a2dp_appl_avdtp_notify_cb);

#ifdef INCLUDE_A2DP_CODEC
#ifdef A2DP_SINK
#ifndef A2DP_BRIDGING
    /* Initialize JPL */
    BT_jpl_init(jpl_callback_handle);
#ifdef JPL_USE_APP_MEMORY
    buffer.sbc = a2dp_alloc_buffer_pl(A2DP_SBC_BUFFER);
    buffer.pcm = a2dp_alloc_buffer_pl(A2DP_PCM_BUFFER);
    buffer.silence = a2dp_alloc_buffer_pl(A2DP_SILENCE_BUFFER);

    /* Register memory to JPL */
    (BT_IGNORE_RETURN_VALUE) BT_jpl_register_buffers(&buffer);
#endif /* JPL_USE_APP_MEMORY */
#endif /* A2DP_BRIDGING */
#endif /* A2DP_SINK */
#endif /* INCLUDE_A2DP_CODEC */
}


void a2dp_appl_start (UCHAR sep_type)
{
    UCHAR * codec_ie_cap;
    API_RESULT retval;
    UCHAR indx, a2dp_instance;
    UCHAR codec_type, codec_ie_len;
#ifdef MULTI_PROFILE_FSM_SUPPORT
    STATE_T    state;
    PROFILE_EVENT_INFO profile_info;
#endif /* MULTI_PROFILE_FSM_SUPPORT */
#ifdef A2DP_SOURCE
    BT_thread_type tid;
#endif /* A2DP_SOURCE */

    printf("Starting A2DP ...\n");

    /* Allocate an Instance */
    a2dp_appl_alloc_instance (&indx);
    if (indx >= A2DP_MAX_CODECS)
    {
        printf("*** No Free Codec Instance Available\n");
        return;
    }

    /* Set Codec Type - SBC */
    codec_type = AVDTP_CODEC_AUDIO_SBC;

    /* Get Codec IE */
    codec_ie_cap = a2dp_appl_instance[indx].codec_ie_cap;

    /* Initialize Codec IE */
    /* Set Support for SBC Sampling Freqn & Channel Modes */
    codec_ie_cap[0] = A2DP_SBC_SAMPLING_FREQUENCY_16000 |
                      A2DP_SBC_SAMPLING_FREQUENCY_32000 |
                      A2DP_SBC_SAMPLING_FREQUENCY_44100 |
                      A2DP_SBC_SAMPLING_FREQUENCY_48000 |
                      A2DP_SBC_CHANNEL_MONO |
                      A2DP_SBC_CHANNEL_DUAL |
                      A2DP_SBC_CHANNEL_STEREO |
                      A2DP_SBC_CHANNEL_JOINT_STEREO;

    /* Set Support for SBC Block Len, Subbands & Allocation Method */
    codec_ie_cap[1] = A2DP_SBC_BLOCK_LENGTH_4 |
                      A2DP_SBC_BLOCK_LENGTH_8 |
                      A2DP_SBC_BLOCK_LENGTH_12 |
                      A2DP_SBC_BLOCK_LENGTH_16 |
                      A2DP_SBC_SUBBANDS_4 |
                      A2DP_SBC_SUBBANDS_8 |
                      A2DP_SBC_ALLOCATION_METHOD_SNR |
                      A2DP_SBC_ALLOCATION_METHOD_LOUDNESS;

    /* Set Support for Minimum Bitpool */
    codec_ie_cap[2] = A2DP_SBC_BITPOOL_MIN;

    /* Set Support for Maximum Bitpool */
    codec_ie_cap[3] = A2DP_SBC_BITPOOL_MAX;

    /* Set Codec IE Length */
    codec_ie_len = A2DP_SBC_CODEC_CAP_IE_LEN;

    /*Update A2DP role */
    a2dp_appl_instance[indx].role = sep_type;

    /* Initialize Stream End Point Capability */
    AVDTP_SET_SEP_CAPABILITY
    (
        a2dp_appl_instance[indx].sep_cap,
        sep_type,
        AVDTP_MEDIA_AUDIO,
        codec_type,
        codec_ie_len,
        codec_ie_cap
    );

#ifdef AVDTP_HAVE_CONTENT_PROTECTION
    /* Initialize the Streaming End Point CP Capability */
    AVDTP_SET_SEP_CP_CAPABILITY
    (
        (a2dp_appl_instance[indx].sep_cap.cp_cap[0]),
        AVDTP_CONTENT_PROTECTION_TYPE_SCMS_T,
        cp_ie_buf,
        cp_ie_buf_len
    );
#endif /* AVDTP_HAVE_CONTENT_PROTECTION */

    /* Register to A2DP */
    printf("A2DP Register Codec ... ");
    retval = BT_a2dp_register_codec
             (
                 &a2dp_instance,
                 &a2dp_appl_instance[indx].sep_cap,
                 a2dp_appl_notify_cb
             );

    if (API_SUCCESS != retval)
    {
        printf("*** FAILED. Reason = 0x%04X\n", retval);

        /* Free Instance */
        a2dp_appl_free_instance (indx);
    }
    else
    {
        printf("OK\n");
#ifdef MULTI_PROFILE_FSM_SUPPORT
        profile_info.event_type         = 0U;
        profile_info.event_info         = 0U;
        profile_info.profile_fsm_handle = (UCHAR)get_multiprofile_handle();
        profile_info.data               = NULL;
        profile_info.datalen            = 0U;
        profile_access_state_handler(&profile_info, &state);
        state |= SL_A2DP_STARTED;
        profile_set_state_handler(&profile_info, state);
#endif /* MULTI_PROFILE_FSM_SUPPORT */
        /* Save A2DP Codec Instance */
        a2dp_appl_instance[indx].a2dp_instance = a2dp_instance;

        if (AVDTP_SEP_SINK == sep_type)
        {
            /* Get the A2DP Sink record handle */
            retval = BT_dbase_get_record_handle
                     (
                         DB_RECORD_A2DP_SINK,
                         0,
                         &a2dp_record_handle
                     );
        }
        else if (AVDTP_SEP_SOURCE == sep_type)
        {
            /* Get the A2DP Source record handle */
            retval = BT_dbase_get_record_handle
                     (
                         DB_RECORD_A2DP_SOURCE,
                         0,
                         &a2dp_record_handle
                     );

#ifdef INCLUDE_A2DP_CODEC
#ifdef A2DP_SOURCE
            BT_thread_mutex_init(&a2dp_src_th_mutex, NULL);
            BT_thread_cond_init(&a2dp_src_th_cond, NULL);

            /* Initialize the task variables and create the task */
            a2dp_src_wr_th_state = APP_A2DP_SRC_WR_TH_INIT;

            a2dp_src_buffer_size = A2DP_SRC_MAX_BUFFER_SIZE;
            a2dp_src_buffer_rd_ptr = 0;
            a2dp_src_buffer_wr_ptr = 0;

            if (0 != BT_thread_create(&tid, NULL, (void *)a2dp_src_write_task, NULL))
            {
                printf("Failed to create A2DP Src thread\n");
                return;
            }
#endif /* A2DP_SOURCE */
#endif /* INCLUDE_A2DP_CODEC */
        }

        if (API_SUCCESS == retval)
        {
            /* Activate Record Handle */
            BT_dbase_activate_record (a2dp_record_handle);
        }
    }

    /*
     * Optional to set the MTU. Default MTU as in BT_limits.h will be used
     * otherwise
     */
    retval = BT_a2dp_set_media_mtu
             (
                 a2dp_appl_instance[indx].a2dp_instance,
                 APPL_A2DP_MTU
             );

#ifdef AVDTP_HAVE_CONTENT_PROTECTION
    a2dp_cp_header [0] = AVDTP_SCMS_T_COPY_NOT_ALLOWED;
    a2dp_cp_header_len = 0x01;

    /* A2DP Set Media MTU */
    printf("A2DP Set CP Header ... ");
    retval = BT_a2dp_set_cp_header
             (
                 a2dp_appl_instance[indx].a2dp_instance,
                 a2dp_cp_header,
                 a2dp_cp_header_len
             );

    if (API_SUCCESS != retval)
    {
        printf("FAILED. Reason = 0x%04X\n", retval);
    }
    else
    {
        printf("OK\n");
    }
#endif /* AVDTP_HAVE_CONTENT_PROTECTION */
    a2dp_appl_show_instance();
    return;
}


void a2dp_appl_connect (UCHAR * bd_addr)
{
    API_RESULT retval;

    /* Initialize AVDTP Handle */
    AVDTP_INIT_HANDLE (a2dp_appl_avdtp_handle);

    /* Set AVDTP Handle Callback */
    AVDTP_SET_HANDLE_CALLBACK
    (
        a2dp_appl_avdtp_handle,
        a2dp_appl_avdtp_notify_cb
    );

    /* Set AVDTP Remote BD_ADDR */
    AVDTP_SET_HANDLE_BD_ADDR
    (
        a2dp_appl_avdtp_handle,
        bd_addr
    );

    /* AVDTP Connect */
    printf("AVDTP Connect ... ");
    retval = BT_avdtp_connect_req
             (
                 &a2dp_appl_avdtp_handle
             );

    if (API_SUCCESS != retval)
    {
        printf("FAILED. Reason = 0x%04X\n", retval);
    }
    else
    {
        printf("OK. Wait for AVDTP_CONNECT_CNF\n");
    }

    return;
}

void a2dp_appl_connect_info_reset (UCHAR inst)
{
    /* Check for valid inst */
    if (inst >= A2DP_MAX_CODECS)
    {
        printf("Invalid A2DP instance\n");
        /* return; */
    }
    else
    {
        /* Reset BD Address */
        BT_mem_set
        (
            a2dp_appl_instance[inst].bd_addr,
            0x00,
            BT_BD_ADDR_SIZE
        );

        /* Reset Codec Configuration */
        BT_mem_set
        (
            a2dp_appl_instance[inst].codec_ie_conf,
            0x00,
            sizeof (a2dp_appl_instance[inst].codec_ie_conf)
        );

        /* Reset Codec Configuration */
        BT_mem_set
        (
            a2dp_appl_instance[inst].codec_ie_cap,
            0x00,
            sizeof (a2dp_appl_instance[inst].codec_ie_cap)
        );

        a2dp_appl_instance[inst].stream_state = APPL_A2DP_STREAM_FALSE;
    }
#ifdef A2DP_BRIDGING
    a2dp_appl_instance[inst].a2dp_connection_state = APPL_A2DP_DISCONNECTED;
#endif //A2DP_BRIDGING
    return;
}

API_RESULT a2dp_appl_notify_cb
           (
               UCHAR    codec_instance,
               UCHAR    event_type,
               UINT16   event_result,
               void  *  event_data,
               UINT16   event_datalen
           )
{
    UCHAR * codec_ie;
    UINT8 index;
#ifndef A2DP_BRIDGING
    UCHAR role;
#endif /* A2DP_BRIDGING */
#ifdef MULTI_PROFILE_FSM_SUPPORT
    PROFILE_EVENT_INFO profile_info;
    A2DP_DEVICE_INFO * a2dp_dev_info;
#endif /* MULTI_PROFILE_FSM_SUPPORT */
#ifndef A2DP_BRIDGING
    role = a2dp_appl_instance[codec_instance].role;
#endif /* A2DP_BRIDGING */
    for (index = 0; index < A2DP_MAX_CODECS; index ++)
    {
        if (codec_instance == a2dp_appl_instance[index].a2dp_instance)
        {
            a2dp_codec_instance = codec_instance;
            /* Matching instance found */
            break;
        }
    }

    if (A2DP_MAX_CODECS == index)
    {
        printf ("No Matching index found\n");
        return API_SUCCESS;
    }

    switch (event_type)
    {
    case A2DP_CONNECT_CNF:
        printf("\n");
        printf("Received A2DP_CONNECT_CNF\n");
        printf("\tCodec Instance = %d\n", codec_instance);
        printf("\tEvent Result   = 0x%04X\n", event_result);

        /* Open Audio Device for Recording */
        if (API_SUCCESS == event_result)
        {
#ifdef INCLUDE_A2DP_CODEC
#ifndef A2DP_BRIDGING
            /* Init the Pl */
            a2dp_init_pl(role);
#endif //A2DP_BRIDGING
#endif /* INCLUDE_A2DP_CODEC */
#ifdef MULTI_PROFILE_FSM_SUPPORT
            /* Set Connection Info */
            a2dp_dev_info = (A2DP_DEVICE_INFO *)event_data;

            if (BT_FALSE == BT_BD_ADDR_IS_NON_ZERO(a2dp_appl_instance[codec_instance].bd_addr))
            {
                /* Load the BD Address */
                BT_COPY_BD_ADDR
                (
                    a2dp_appl_instance[codec_instance].bd_addr,
                    (UCHAR*)a2dp_dev_info->bd_addr
                );
            }
            /* Codec Configuration */
            BT_mem_copy
            (
                a2dp_appl_instance[codec_instance].codec_ie_conf,
                a2dp_dev_info->codec_ie_conf,
                a2dp_dev_info->codec_ie_len
            );

            /* Set Application Stream State to FALSE */
            a2dp_appl_instance[codec_instance].stream_state = APPL_A2DP_STREAM_FALSE;

            profile_info.event_type         = ev_pro_a2dp_connect;
            profile_info.event_info         = PROFILE_FSM_LOCAL_EVENT;
            profile_info.profile_fsm_handle = get_multiprofile_handle();
            profile_info.data               = (UCHAR*)a2dp_dev_info->bd_addr;
            profile_info.datalen            = BT_BD_ADDR_SIZE;
            profile_fsm_post_event(&profile_info);
#endif /* MULTI_PROFILE_FSM_SUPPORT */
        }
        a2dp_appl_show_instance();
        break;

    case A2DP_CONNECT_IND:
        printf("\n");
        printf("Received A2DP_CONNECT_IND\n");
        printf("\tCodec Instance = %d\n", codec_instance);
        printf("\tEvent Result   = 0x%04X\n", event_result);

#ifdef INCLUDE_A2DP_CODEC
        /* Init the Pl */
#ifndef A2DP_BRIDGING
        a2dp_init_pl(role);
#endif /* A2DP_BRIDGING */
#endif /* INCLUDE_A2DP_CODEC */
#ifdef MULTI_PROFILE_FSM_SUPPORT
        /* Set Connection Info */
        a2dp_dev_info = (A2DP_DEVICE_INFO *)event_data;

        if (BT_FALSE == BT_BD_ADDR_IS_NON_ZERO(a2dp_appl_instance[codec_instance].bd_addr))
        {
            /* Load the BD Address */
            BT_COPY_BD_ADDR
            (
                a2dp_appl_instance[codec_instance].bd_addr,
                (UCHAR*)a2dp_dev_info->bd_addr
            );
        }
        /* Codec Configuration */
        BT_mem_copy
        (
            a2dp_appl_instance[codec_instance].codec_ie_conf,
            a2dp_dev_info->codec_ie_conf,
            a2dp_dev_info->codec_ie_len
        );

        /* Set Application Stream State to FALSE */
        a2dp_appl_instance[codec_instance].stream_state = APPL_A2DP_STREAM_FALSE;

#ifndef A2DP_BRIDGING
        profile_info.event_type         = ev_pro_a2dp_connect;
        profile_info.event_info         = PROFILE_FSM_REMOTE_EVENT;
        profile_info.profile_fsm_handle = get_multiprofile_handle();
        profile_info.data               = (UCHAR*)a2dp_dev_info->bd_addr;
        profile_info.datalen            = BT_BD_ADDR_SIZE;
        profile_fsm_post_event(&profile_info);
#endif /* A2DP_BRIDGING */
        /* Load the BD address */
        BT_COPY_BD_ADDR(appl_peer_bd_addr, a2dp_dev_info->bd_addr);

#endif /* MULTI_PROFILE_FSM_SUPPORT */
        a2dp_appl_show_instance();
        break;

    case A2DP_START_CNF:
        printf("\n");
        printf("Received A2DP_START_CNF\n");
        printf("\tCodec Instance = %d\n", codec_instance);
        printf("\tEvent Result   = 0x%04X\n", event_result);

        if (API_SUCCESS == event_result)
        {

#ifdef A2DP_SOURCE
            a2dp_max_allowed_payload_len = *(UINT16 *)event_data;

            /*
             * If a content protection scheme (eg. SCMT-T or DTCP etc.) is
             * configured for the media transport, subtract the correspoinding
             * 'Content protection header length' from
             * the 'Maximum Allowed Payload Length' to arrive at the exact
             * 'Maximum Payload Length' application can send in a single
             * media packet.
             */
        #ifdef AVDTP_HAVE_CONTENT_PROTECTION
            a2dp_max_allowed_payload_len -= a2dp_cp_header_len;
        #endif /* AVDTP_HAVE_CONTENT_PROTECTION */

            printf("\tMaximum Media Payload Allowed = %d\n",
                                        a2dp_max_allowed_payload_len);
#endif /* A2DP_SOURCE */

#ifdef INCLUDE_A2DP_CODEC
#ifndef A2DP_BRIDGING
            /* Start the Pl */
            a2dp_start_pl(role);
#endif //A2DP_BRIDGING

#ifdef A2DP_SINK
#ifndef A2DP_BRIDGING
            if (AVDTP_SEP_SINK == role)
            {
                /* Start JPL */
                BT_jpl_start(&jpl_param);
            }
#endif //A2DP_BRIDGING
#endif /* A2DP_SINK */
#endif /* INCLUDE_A2DP_CODEC */

#ifdef MULTI_PROFILE_FSM_SUPPORT
    		/*set a2dp-start when both a2dp links are in streaming state*/
            profile_info.event_type         = ev_pro_a2dp_start;
            profile_info.event_info         = PROFILE_FSM_LOCAL_EVENT;
            profile_info.profile_fsm_handle = get_multiprofile_handle();
            profile_info.data               = (UCHAR*)a2dp_appl_instance[codec_instance].bd_addr;
            profile_info.datalen            = BT_BD_ADDR_SIZE;
            profile_fsm_post_event(&profile_info);
#endif /* MULTI_PROFILE_FSM_SUPPORT */
        }

        break;

    case A2DP_START_IND:
        printf("\n");
        printf("Received A2DP_START_IND\n");
        printf("\tCodec Instance = %d\n", codec_instance);
        printf("\tEvent Result   = 0x%04X\n", event_result);
#ifdef A2DP_SOURCE
        a2dp_max_allowed_payload_len = *(UINT16 *)event_data;

        /*
         * If a content protection scheme (eg. SCMT-T or DTCP etc.) is
         * configured for the media transport, subtract the correspoinding
         * 'Content protection header length' from
         * the 'Maximum Allowed Payload Length' to arrive at the exact
         * 'Maximum Payload Length' application can send in a single
         * media packet.
         */
    #ifdef AVDTP_HAVE_CONTENT_PROTECTION
        a2dp_max_allowed_payload_len -= a2dp_cp_header_len;
    #endif /* AVDTP_HAVE_CONTENT_PROTECTION */

        printf("\tMaximum Media Payload Allowed = %d\n",
                                        a2dp_max_allowed_payload_len);
#endif /* A2DP_SOURCE */
#ifndef A2DP_BRIDGING
#ifdef INCLUDE_A2DP_CODEC
        /* Start the Pl */
        a2dp_start_pl(role);
#endif //A2DP_BRIDGING

#ifdef A2DP_SINK
#ifndef A2DP_BRIDGING
        if (AVDTP_SEP_SINK == role)
        {
            /* Start JPL */
            BT_jpl_start(&jpl_param);
        }
#endif /* A2DP_SINK */
#endif /* INCLUDE_A2DP_CODEC */
#endif //A2DP_BRIDGING

#ifdef MULTI_PROFILE_FSM_SUPPORT
		/*set a2dp-start when both a2dp links are in streaming state*/
		profile_info.event_type = ev_pro_a2dp_start;
		profile_info.event_info = PROFILE_FSM_REMOTE_EVENT;
		profile_info.profile_fsm_handle = get_multiprofile_handle();
		profile_info.data = (UCHAR*) a2dp_appl_instance[codec_instance].bd_addr;
		profile_info.datalen = BT_BD_ADDR_SIZE;
		profile_fsm_post_event(&profile_info);
#endif /* MULTI_PROFILE_FSM_SUPPORT */
        break;

    case A2DP_SUSPEND_CNF:
        printf("\n");
        printf("Received A2DP_SUSPEND_CNF\n");
        printf("\tCodec Instance = %d\n", codec_instance);
        printf("\tEvent Result   = 0x%04X\n", event_result);

        if (API_SUCCESS == event_result)
        {
#ifndef A2DP_BRIDGING
#ifdef INCLUDE_A2DP_CODEC
            /* Stop the Pl */
            a2dp_stop_pl(role);

#ifdef A2DP_SINK
            if (AVDTP_SEP_SINK == role)
            {
                /* Stop JPL */
                BT_jpl_stop();
            }
#endif /* A2DP_SINK */
#endif /* INCLUDE_A2DP_CODEC */
#endif //A2DP_BRIDGING

#ifdef MULTI_PROFILE_FSM_SUPPORT
			/*send suspend if both links are suspended..*/
            profile_info.event_type         = ev_pro_a2dp_suspend;
            profile_info.event_info         = PROFILE_FSM_LOCAL_EVENT;
            profile_info.profile_fsm_handle = get_multiprofile_handle();
            profile_info.data               = (UCHAR*)a2dp_appl_instance[codec_instance].bd_addr;
            profile_info.datalen            = BT_BD_ADDR_SIZE;
            profile_fsm_post_event(&profile_info);
#endif /* MULTI_PROFILE_FSM_SUPPORT */
        }

        break;

    case A2DP_SUSPEND_IND:
        printf("\n");
        printf("Received A2DP_SUSPEND_IND\n");
        printf("\tCodec Instance = %d\n", codec_instance);
        printf("\tEvent Result   = 0x%04X\n", event_result);

#ifndef A2DP_BRIDGING
#ifdef INCLUDE_A2DP_CODEC
        /* Stop the Pl */
        a2dp_stop_pl(role);

#ifdef A2DP_SINK
        if (AVDTP_SEP_SINK == role)
        {
            /* Stop JPL */
            BT_jpl_stop();
        }
#endif /* A2DP_SINK */
#endif /* INCLUDE_A2DP_CODEC */
#endif /*A2DP_BRIDGING*/

#ifdef MULTI_PROFILE_FSM_SUPPORT
		profile_info.event_type         = ev_pro_a2dp_suspend;
		profile_info.event_info         = PROFILE_FSM_REMOTE_EVENT;
		profile_info.profile_fsm_handle = get_multiprofile_handle();
		profile_info.data               = (UCHAR*)a2dp_appl_instance[codec_instance].bd_addr;
		profile_info.datalen            = BT_BD_ADDR_SIZE;
		profile_fsm_post_event(&profile_info);
#endif /* MULTI_PROFILE_FSM_SUPPORT */
        break;

    case A2DP_RECONFIGURE_CNF:
        printf("\n");
        printf("Received A2DP_RECONFIGURE_CNF\n");
        printf("\tCodec Instance = %d\n", codec_instance);
        printf("\tEvent Result   = 0x%04X\n", event_result);
#ifdef A2DP_BRIDGING
        if (API_SUCCESS == event_result)
        {
            /* Codec Configuration */
            BT_mem_copy
            (
                a2dp_appl_instance[codec_instance].codec_ie_conf,
                a2dp_appl_sbc_codec_ie,
                AVDTP_MAX_CODEC_IE_LEN
            );

            /* Print Codec Configuration */
            a2dp_appl_print_codec_ie_configuration
            (
                AVDTP_CODEC_AUDIO_SBC, //TODO: need to take dynamic values if more codec_types are supported
                a2dp_appl_instance[codec_instance].codec_ie_conf,
                AVDTP_MAX_CODEC_IE_LEN
            );
        }
#endif //A2DP_BRIDGING
        break;

    case A2DP_CONFIGURE_IND:
        printf("\n");
        printf("Received A2DP_CONFIGURE_IND\n");
        printf("\tCodec Instance = %d\n", codec_instance);
        printf("\tEvent Result   = 0x%04X\n", event_result);
        printf("\tEvent Data = %p, Data Length = %d\n",
        event_data, event_datalen);

        if (NULL != event_data)
        {
#ifdef  A2DP_1_3
            A2DP_DEVICE_INFO * a2dp_dev_info;

            a2dp_dev_info = (A2DP_DEVICE_INFO *)event_data;
            codec_ie = a2dp_dev_info->codec_ie_conf;
            event_datalen = a2dp_dev_info->codec_ie_len;
#else
            codec_ie = (UCHAR *)event_data;
#endif /* A2DP_1_3 */

            printf("\tSBC Codec IE = %02X %02X %02X %02X\n",
            codec_ie[0], codec_ie[1], codec_ie[2], codec_ie[3]);

            /* Decode Sampling Frequency */
            switch (codec_ie[0] & 0xF0)
            {
            case A2DP_SBC_SAMPLING_FREQUENCY_16000:
                printf("\t-> Sampling Frequency = 16000\n");
                break;

            case A2DP_SBC_SAMPLING_FREQUENCY_32000:
                printf("\t-> Sampling Frequency = 32000\n");
                break;

            case A2DP_SBC_SAMPLING_FREQUENCY_44100:
                printf("\t-> Sampling Frequency = 44100\n");
                break;

            case A2DP_SBC_SAMPLING_FREQUENCY_48000:
                printf("\t-> Sampling Frequency = 48000\n");
                break;

            default:
                printf("\t-> Sampling Frequency = ?????\n");
                break;
            }

            /* Decode Channel Mode */
            switch (codec_ie[0] & 0x0F)
            {
            case A2DP_SBC_CHANNEL_MONO:
                printf("\t-> Channel Mode = Mono (1)\n");
                break;

            case A2DP_SBC_CHANNEL_DUAL:
                printf("\t-> Channel Mode = Dual (2)\n");
                break;

            case A2DP_SBC_CHANNEL_STEREO:
                printf("\t-> Channel Mode = Stereo (2)\n");
                break;

            case A2DP_SBC_CHANNEL_JOINT_STEREO:
                printf("\t-> Channel Mode = Joint Stereo (2)\n");
                break;

            default:
                printf("\t-> Channel Mode = ?????\n");
                break;
            }

            /* Decode Block Length */
            switch (codec_ie[1] & 0xF0)
            {
            case A2DP_SBC_BLOCK_LENGTH_4:
                printf("\t-> Block Length = 4\n");
                break;

            case A2DP_SBC_BLOCK_LENGTH_8:
                printf("\t-> Block Length = 8\n");
                break;

            case A2DP_SBC_BLOCK_LENGTH_12:
                printf("\t-> Block Length = 12\n");
                break;

            case A2DP_SBC_BLOCK_LENGTH_16:
                printf("\t-> Block Length = 16\n");
                break;

            default:
                printf("\t-> Block Length = ?????\n");
                break;
            }

            /* Decode Subbands */
            switch (codec_ie[1] & 0x0C)
            {
            case A2DP_SBC_SUBBANDS_4:
                printf("\t-> Subbands = 4\n");
                break;

            case A2DP_SBC_SUBBANDS_8:
                printf("\t-> Subbands = 8\n");
                break;

            default:
                printf("\t-> Subbands = ?????\n");
                break;
            }

            /* Decode Allocation Method */
            switch (codec_ie[1] & 0x03)
            {
            case A2DP_SBC_ALLOCATION_METHOD_SNR:
                printf("\t-> Allocation Method = SNR\n");
                break;

            case A2DP_SBC_ALLOCATION_METHOD_LOUDNESS:
                printf("\t-> Allocation Method = Loudness\n");
                break;

            default:
                printf("\t-> Allocation Method = ?????\n");
                break;
            }

            printf("\t-> Bitpool = %d, %d\n", codec_ie[2], codec_ie[3]);

            /* Save SBC Codec IE */
            BT_mem_copy(a2dp_appl_sbc_codec_ie, codec_ie, A2DP_SBC_CODEC_CAP_IE_LEN);

#ifndef A2DP_BRIDGING
#ifdef INCLUDE_A2DP_CODEC
#if (defined A2DP_SOURCE && defined A2DP_SINK)
            if (AVDTP_SEP_SINK == role)
#endif /* (defined A2DP_SOURCE && defined A2DP_SINK) */
#ifdef A2DP_SINK
            {
                appl_a2dp_jpl_configure(codec_ie);
            }
#endif /* A2DP_SINK */
#if (defined A2DP_SOURCE && defined A2DP_SINK)
            else
#endif /* (defined A2DP_SOURCE && defined A2DP_SINK) */
#ifdef A2DP_SOURCE
            {
                appl_a2dp_src_prepare();
            }
#endif /* A2DP_SOURCE */
#endif /* INCLUDE_A2DP_CODEC */
#endif /* A2DP_BRIDGING */
        }
        else
        {
            printf("*** A2DP_CONFIGURE_IND: No Event Data/Data Length\n");
        }

        break;

    case A2DP_DISCONNECT_CNF:
        printf("\n");
        printf("Received A2DP_DISCONNECT_CNF\n");
        printf("\tCodec Instance = %d\n", codec_instance);
        printf("\tEvent Result   = 0x%04X\n", event_result);

#ifndef A2DP_BRIDGING
#ifdef INCLUDE_A2DP_CODEC
        if (API_SUCCESS == event_result)
        {
            /* Shutdown the Pl */
            a2dp_shutdown_pl();
        }
#endif /* INCLUDE_A2DP_CODEC */
#endif //A2DP_BRIDGING

#ifdef MULTI_PROFILE_FSM_SUPPORT
        profile_info.event_type         = ev_pro_a2dp_disconnect;
        profile_info.event_info         = PROFILE_FSM_LOCAL_EVENT;
        profile_info.profile_fsm_handle = get_multiprofile_handle();
        profile_info.data               = (UCHAR*)a2dp_appl_instance[codec_instance].bd_addr;
        profile_info.datalen            = BT_BD_ADDR_SIZE;
        profile_fsm_post_event(&profile_info);
#endif /* MULTI_PROFILE_FSM_SUPPORT */
        break;

    case A2DP_DISCONNECT_IND:
        printf("\n");
        printf("Received A2DP_DISCONNECT_IND\n");
        printf("\tCodec Instance = %d\n", codec_instance);
        printf("\tEvent Result   = 0x%04X\n", event_result);

#ifndef A2DP_BRIDGING
#ifdef INCLUDE_A2DP_CODEC
        /* Shutdown the Pl */
        a2dp_shutdown_pl();
#endif /* INCLUDE_A2DP_CODEC */
#endif

#ifdef MULTI_PROFILE_FSM_SUPPORT
        profile_info.event_type         = ev_pro_a2dp_disconnect;
        profile_info.event_info         = PROFILE_FSM_REMOTE_EVENT;
        profile_info.profile_fsm_handle = get_multiprofile_handle();
        profile_info.data               = (UCHAR*)a2dp_appl_instance[codec_instance].bd_addr;
        profile_info.datalen            = BT_BD_ADDR_SIZE;
        profile_fsm_post_event(&profile_info);
#endif /* MULTI_PROFILE_FSM_SUPPORT */
        break;

    case A2DP_MEDIA_FRAME_IND:
        /* printf (". "); */
        {
            API_RESULT retval;

            /* printf(". "); */
#ifdef A2DP_BRIDGING
            {
                UCHAR* data;
                UCHAR num_sbc_frames;
                UINT32 decoder_join;
                SBC_CODEC_PARAM codec_param;
                UINT16 appl_sbc_frame_len;
                UINT16 offset = 0;

                data = (UCHAR*)event_data;

                data = (void*)((UCHAR*)event_data + (12 + 1));

                /* Get the number of SBC frames */
                num_sbc_frames = (*(data - 1)) & 0xF;

                /* Calculate the frame length */
                sbc_decoder_extract_sbc_header
                (
                    &decoder_join,
                    &codec_param,
                    data
                );

                sbc_calculate_frame_length(&codec_param, &appl_sbc_frame_len);

                for (int i = 0U; i < A2DP_MAX_CODECS; i++)
                {
                    if ((APPL_A2DP_STREAM_TRUE == a2dp_appl_instance[i].stream_state) &&
                        (AVDTP_SEP_SOURCE == a2dp_appl_instance[i].role))
                    {
                        while (num_sbc_frames > 0)
                        {
                            /* Write to A2DP */
                            retval = BT_a2dp_media_write
                            (
                                a2dp_appl_instance[i].a2dp_instance,
                                &data[offset],
                                appl_sbc_frame_len
                            );
                            if (API_SUCCESS != retval)
                            {
                            	APPL_ERR("A2DP media write failed - 0x%04X\n", retval);
                            }
#ifndef A2DP_SUPPORT_MULTIPLE_MEDIA_FRAME_WRITE
                            offset += appl_sbc_frame_len;
                            num_sbc_frames--;
#endif /* A2DP_SUPPORT_MULTIPLE_MEDIA_FRAME_WRITE */
                        }
                        break;
                    }
                }
            }
#else //A2DP_BRIDGING
            UINT32 timestamp;
            UCHAR * data;
            UINT16 datalen;
            UINT16 seq_number;

            /* Remove the headers and get pointer to actual data */
            data = (void*)((UCHAR*)event_data + (12 + 1));
            datalen = (event_datalen - (12 + 1));

            timestamp = *((UCHAR*)data - 9);
            timestamp <<= 8;
            timestamp |= *((UCHAR*)data - 8);
            timestamp <<= 8;
            timestamp |= * ((UCHAR*) data - 7);
            timestamp <<= 8;
            timestamp |= * ((UCHAR*) data - 6);

            seq_number = * ((UCHAR*) data - 11);
            seq_number <<= 8;
            seq_number |= * ((UCHAR*) data - 10);

#ifdef INCLUDE_A2DP_CODEC
#ifdef A2DP_SINK
            /* Add SBC media frames to JPL */
            retval = BT_jpl_add_frames
                     (
                         seq_number,
                         timestamp,
                         (((UCHAR*) data) - 1),
                         (datalen + 1)
                     );
            if (API_SUCCESS != retval)
            {
            	APPL_ERR("JPL Add Frames Failed - 0x%04X\n", retval);
            }
#endif /* A2DP_SINK */
#endif /* INCLUDE_A2DP_CODEC */
#endif
        }

        break;

    default:
        return API_FAILURE;
    }

    return API_SUCCESS;
}


API_RESULT a2dp_appl_avdtp_notify_cb
           (
               UCHAR             event_type,
               UINT16            event_result,
               AVDTP_HANDLE *    avdtp_handle,
               void *            event_data,
               UINT16            event_datalen
           )
{
    UCHAR * rsp_buf;
    UCHAR * codec_ie;
    API_RESULT retval;
    UINT16 count, codec_ie_len;
    AVDTP_SEP_CAP sep_cap;
    UCHAR * codec_ie_conf;
    AVDTP_SEP_CONF sep_conf;
    UCHAR    codec_instance = 0;

    switch (event_type)
    {
    case AVDTP_CONNECT_IND:
        printf("\n");
        printf("Received AVDTP_CONNECT_IND\n");
        printf("\tAVDTP Handle:\n");
        printf("\t    " BT_DEVICE_ADDR_ONLY_FRMT_SPECIFIER "\n",
        BT_DEVICE_ADDR_ONLY_PRINT_STR (avdtp_handle->bd_addr));
        printf("\tResult = 0x%04X\n", event_result);

        break;

    case AVDTP_CONNECT_CNF:
        printf("\n");
        printf("Received AVDTP_CONNECT_CNF\n");
        printf("\tAVDTP Handle:\n");
        printf("\t    " BT_DEVICE_ADDR_ONLY_FRMT_SPECIFIER "\n",
        BT_DEVICE_ADDR_ONLY_PRINT_STR (avdtp_handle->bd_addr));
        printf("\tResult = 0x%04X\n", event_result);

#ifdef AVDTP_A2DP_CHAINED_CONNECT
        if (API_SUCCESS == event_result)
        {
            retval = BT_avdtp_discover_req
                     (
                         &a2dp_appl_avdtp_handle,
                         a2dp_appl_sep_info_buf,
                         A2DP_MAX_DISCOVER_RESPONSE_LEN
                     );

            if (retval != API_SUCCESS)
            {
                printf("FAILED. Reason = 0x%04X\n", retval);
            }
            else
            {
                printf("OK. Wait for AVDTP_DISCOVER_CNF\n");
            }
        }
#endif /* AVDTP_A2DP_CHAINED_CONNECT */

        break;

    case AVDTP_DISCONNECT_IND:
        printf("\n");
        printf("Received AVDTP_DISCONNECT_IND\n");
        printf("\tAVDTP Handle:\n");
        printf("\t    " BT_DEVICE_ADDR_ONLY_FRMT_SPECIFIER "\n",
        BT_DEVICE_ADDR_ONLY_PRINT_STR (avdtp_handle->bd_addr));
        printf("\tResult = 0x%04X\n", event_result);

        /* Disconnect HCI */
        /*appl_hci_disconnect ();Re-visit*/
        a2dp_appl_show_instance();

        break;

    case AVDTP_DISCONNECT_CNF:
        printf("\n");
        printf("Received AVDTP_DISCONNECT_CNF\n");
        printf("\tAVDTP Handle:\n");
        printf("\t    " BT_DEVICE_ADDR_ONLY_FRMT_SPECIFIER "\n",
        BT_DEVICE_ADDR_ONLY_PRINT_STR (avdtp_handle->bd_addr));
        printf("\tResult = 0x%04X\n", event_result);

        /* Disconnect HCI */
        /*appl_hci_disconnect ();Re-visit*/
        a2dp_appl_show_instance();

        break;

    case AVDTP_DISCOVER_CNF:
        printf("\n");
        printf("Received AVDTP_DISCOVER_CNF\n");
        printf("\tAVDTP Handle:\n");
        printf("\t    " BT_DEVICE_ADDR_ONLY_FRMT_SPECIFIER "\n",
        BT_DEVICE_ADDR_ONLY_PRINT_STR (avdtp_handle->bd_addr));
        printf("\t    Remote SEID = 0x%02X\n", avdtp_handle->remote_seid);
        printf("\tResult = 0x%04X\n", event_result);

        if (event_result != API_SUCCESS)
        {
            printf("*** Discover RSP Error Code = 0x%04X\n",
            event_result);
            break;
        }

        printf("\tEvent Data = %p, Data Length = %d\n",
        event_data, event_datalen);

        /* Update Info Len and start of info element pointer */
        a2dp_appl_sep_info_buflen = event_datalen;
        a2dp_appl_sep_info_buf_start = a2dp_appl_sep_info_buf;

        a2dp_appl_handle_avdtp_discover_rsp ();

        break;

    case AVDTP_GET_CAPABILITIES_CNF:
        printf("\n");
        printf("Received AVDTP_GET_CAPABILITIES_CNF\n");
        printf("\tAVDTP Handle:\n");
        printf("\t    " BT_DEVICE_ADDR_ONLY_FRMT_SPECIFIER "\n",
        BT_DEVICE_ADDR_ONLY_PRINT_STR (avdtp_handle->bd_addr));
        printf("\t    Remote SEID = 0x%02X\n", avdtp_handle->remote_seid);
        printf("\tResult = 0x%04X\n", event_result);

        if (event_result != API_SUCCESS)
        {
            printf("*** Get Capabilities RSP Error Code = 0x%04X\n",
            event_result);

            /* Try to get capabilites of next Information element */
            a2dp_appl_handle_avdtp_discover_rsp ();

            break;
        }

        printf("\tEvent Data = %p, Data Length = %d\n",
        event_data, event_datalen);

        /* Decode SEP Capabilities - Codec Capabilities */
        rsp_buf = (UCHAR *) event_data;
        retval = BT_avdtp_decode_sep_capabilities
                 (
                     rsp_buf,
                     event_datalen,
                     &sep_cap
                 );

        if (retval != API_SUCCESS)
        {
            printf("*** FAILED to Decode SEP Capabilities = 0x%04X\n", retval);

            /* Try to get capabilites of next Information element */
            a2dp_appl_handle_avdtp_discover_rsp ();

            break;
        }

        printf("\tRemote SEP Capabilities:\n");

        /* Media Type */
        printf("\t    Media Type = 0x%02X -> ", sep_cap.codec_cap.media_type);
        switch (sep_cap.codec_cap.media_type)
        {
        case AVDTP_MEDIA_AUDIO:
            printf("Audio\n");
            break;

        case AVDTP_MEDIA_VIDEO:
            printf("Video\n");
            break;

        case AVDTP_MEDIA_MULTIMEDIA:
            printf("Multi\n");
            break;

        default:
            printf("????\n");
        }

        /* Codec Type */
        printf("\t    Codec Type = 0x%02X -> ", sep_cap.codec_cap.codec_type);
        switch (sep_cap.codec_cap.codec_type)
        {
        case AVDTP_CODEC_AUDIO_SBC:
            printf("SBC\n");
            break;

        case AVDTP_CODEC_AUDIO_MPEG_1_2:
            printf("MPG12\n");
            break;

        case AVDTP_CODEC_AUDIO_MPEG_2_4:
            printf("MPG24\n");
            break;

        case AVDTP_CODEC_AUDIO_ATRAC:
            printf("ATRAC\n");
            break;

        default:
            printf("????\n");
        }

        /* Codec IE */
        codec_ie = sep_cap.codec_cap.codec_ie;
        codec_ie_len = sep_cap.codec_cap.codec_ie_len;

        printf("\t    Codec IE   = ");
        for (count = 0; count < codec_ie_len; count ++)
        {
            printf("0x%02X ", codec_ie[count]);
        }
        printf("\n");

        /* Decode & Print various Codec IE elements, for SBC */
        if ((sep_cap.codec_cap.media_type == AVDTP_MEDIA_AUDIO) &&
            (sep_cap.codec_cap.codec_type == AVDTP_CODEC_AUDIO_SBC) &&
            (codec_ie_len == A2DP_SBC_CODEC_CAP_IE_LEN))
        {
            /* Decode Support for Sampling Frequency */
            printf("\t    -> SBC Sampling Frequency = ");
            if (codec_ie[0] & A2DP_SBC_SAMPLING_FREQUENCY_16000)
            {
                printf("16000 ");
            }
            if (codec_ie[0] & A2DP_SBC_SAMPLING_FREQUENCY_32000)
            {
                printf("32000 ");
            }
            if (codec_ie[0] & A2DP_SBC_SAMPLING_FREQUENCY_44100)
            {
                printf("44100 ");
            }
            if (codec_ie[0] & A2DP_SBC_SAMPLING_FREQUENCY_48000)
            {
                printf("48000");
            }
            printf("\n");

            /* Decode Support for Channel Mode */
            printf("\t    -> SBC Channel Modes = ");
            if (codec_ie[0] & A2DP_SBC_CHANNEL_MONO)
            {
                printf("Mono ");
            }
            if (codec_ie[0] & A2DP_SBC_CHANNEL_DUAL)
            {
                printf("Dual ");
            }
            if (codec_ie[0] & A2DP_SBC_CHANNEL_STEREO)
            {
                printf("Stereo ");
            }
            if (codec_ie[0] & A2DP_SBC_CHANNEL_JOINT_STEREO)
            {
                printf("Joint-Stereo");
            }
            printf("\n");

            /* Decode Support for Block Length */
            printf("\t    -> SBC Block Length = ");
            if (codec_ie[1] & A2DP_SBC_BLOCK_LENGTH_4)
            {
                printf("4 ");
            }
            if (codec_ie[1] & A2DP_SBC_BLOCK_LENGTH_8)
            {
                printf("8 ");
            }
            if (codec_ie[1] & A2DP_SBC_BLOCK_LENGTH_12)
            {
                printf("12 ");
            }
            if (codec_ie[1] & A2DP_SBC_BLOCK_LENGTH_16)
            {
                printf("16");
            }
            printf("\n");

            /* Decode Support for Subbands */
            printf("\t    -> SBC Subbands = ");
            if (codec_ie[1] & A2DP_SBC_SUBBANDS_4)
            {
                printf("4 ");
            }
            if (codec_ie[1] & A2DP_SBC_SUBBANDS_8)
            {
                printf("8");
            }
            printf("\n");

            /* Decode Support for Allocation Method */
            printf("\t    -> SBC Allocation Method = ");
            if (codec_ie[1] & A2DP_SBC_ALLOCATION_METHOD_SNR)
            {
                printf("SNR ");
            }
            if (codec_ie[1] & A2DP_SBC_ALLOCATION_METHOD_LOUDNESS)
            {
                printf("Loudness");
            }
            printf("\n");

            /* Decode Support for Min/Max Bitpools */
            printf("\t    -> SBC Bitpool Range = %d - %d\n",
            codec_ie[2], codec_ie[3]);

#ifdef AVDTP_A2DP_CHAINED_CONNECT
            for (count = 0U; count < A2DP_MAX_CODECS; count++)
            {
                if (BT_FALSE == BT_BD_ADDR_IS_NON_ZERO(a2dp_appl_instance[count].bd_addr))
                {
                    codec_instance = count;
                    printf("codec_instance = %d\n", codec_instance);
                    break;
                }
            }
            
            /* Load the BD Address */
            BT_COPY_BD_ADDR
            (
                a2dp_appl_instance[codec_instance].bd_addr,
                a2dp_appl_avdtp_handle.bd_addr
            );

            /* Initialize SEP Configuration Parameters */
            AVDTP_INIT_SEP_CONFIGURATION (sep_conf);

            /* Enable Media Transport Service in SEP Configuration */
            AVDTP_SET_SEP_CONFIGURATION_MEDIA (sep_conf);

            /* Get SEP Configuration Codec IE */
            codec_ie_conf = a2dp_appl_instance[codec_instance].codec_ie_conf;

            /*
             * Check if the peer supported capabilities has the configuration which the local device
             * wants to use
             *
             * Note that this is a sample implementation to compare a single set of configuration.
             * Application should maintain logic to get best configuration out of peer supported and
             * local supported configuration and set it for connection.
             */
            if (!((codec_ie[0] & A2DP_SBC_SAMPLING_FREQUENCY_44100) &&
                 (codec_ie[0] & A2DP_SBC_CHANNEL_JOINT_STEREO) &&
                 (codec_ie[1] & A2DP_SBC_BLOCK_LENGTH_16) &&
                 (codec_ie[1] & A2DP_SBC_SUBBANDS_8) &&
                 (codec_ie[1] & A2DP_SBC_ALLOCATION_METHOD_LOUDNESS)))
            {
                printf ("Local supported configuration not available at peer!\n");
                break;
            }

            /* Update codec configuration to connection */
#ifdef A2DP_BRIDGING
            codec_ie_conf[0] = A2DP_SBC_SAMPLING_FREQUENCY_44100 | A2DP_SBC_CHANNEL_JOINT_STEREO;
#else
            codec_ie_conf[0] = A2DP_SBC_SAMPLING_FREQUENCY_44100 | A2DP_SBC_CHANNEL_STEREO;
#endif
            codec_ie_conf[1] = A2DP_SBC_BLOCK_LENGTH_16 | A2DP_SBC_SUBBANDS_8 | A2DP_SBC_ALLOCATION_METHOD_LOUDNESS;
#ifdef A2DP_BRIDGING
			codec_ie_conf[2] = 2;
            codec_ie_conf[3] = 32;
#else
            codec_ie_conf[2] = A2DP_APPL_MAX(52, codec_ie[2]);
            codec_ie_conf[3] = A2DP_APPL_MIN(52, codec_ie[3]);
#endif
            printf("\t    Codec IE CONF   = ");
            for (count = 0; count < codec_ie_len; count ++)
            {
                printf("0x%02X ", codec_ie_conf[count]);
            }
            printf("\n");
#ifdef A2DP_BRIDGING
            for (int i = 0U; i < A2DP_MAX_CODECS; i++)
            {
                /*
                * Find if there are any connections for which codec is already set
                * If A2DP src and sink are not of the same config, audio will not be correctly heard
                */
                if ((i != codec_instance) &&
                    (a2dp_appl_instance[i].role != a2dp_appl_instance[codec_instance].role) &&
                    (a2dp_appl_instance[i].a2dp_connection_state == APPL_A2DP_CONNECTED) &&
                    (memcmp(a2dp_appl_instance[i].codec_ie_conf, a2dp_appl_instance[codec_instance].codec_ie_conf, AVDTP_MAX_CODEC_IE_LEN) != 0))
                {
                    /* Get SEP Configuration Codec IE */
                    codec_ie_conf = a2dp_appl_instance[i].codec_ie_conf;
                }
            }
#endif //A2DP_BRIDGING
            /* Enable Codec Capabilities in SEP Configuration */
            AVDTP_SET_SEP_CONFIGURATION_CODEC_CAP
            (
                sep_conf,
                a2dp_appl_instance[codec_instance].sep_cap.codec_cap.media_type,
                a2dp_appl_instance[codec_instance].sep_cap.codec_cap.codec_type,
                a2dp_appl_instance[codec_instance].sep_cap.codec_cap.codec_ie_len,
                codec_ie_conf
            )

#ifdef AVDTP_HAVE_CONTENT_PROTECTION
            if (sep_cap.cp_cap[0].cp_type & AVDTP_CONTENT_PROTECTION_TYPE_SCMS_T)
            {
                /* Enable CP capabilities in SEP Configuration */
                AVDTP_SET_SEP_CP_CAPABILITY
                (
                    (sep_conf.cp_cap[0]),
                    AVDTP_CONTENT_PROTECTION_TYPE_SCMS_T,
                    cp_ie_buf,
                    cp_ie_buf_len
                );
            }
            else
            {
                /* Enable CP capabilities in SEP Configuration */
                AVDTP_SET_SEP_CP_CAPABILITY
                (
                    (sep_conf.cp_cap[0]),
                    AVDTP_INVALID_CP_TYPE,
                    cp_ie_buf,
                    cp_ie_buf_len
                );
            }
#endif /* AVDTP_HAVE_CONTENT_PROTECTION */

            /* A2DP Connect */
            printf("A2DP Connect ... ");
            retval = BT_a2dp_connect
                     (
                         a2dp_appl_instance[codec_instance].a2dp_instance,
                         a2dp_appl_instance[codec_instance].bd_addr,
                         avdtp_handle->remote_seid,
                         &sep_conf
                     );

            if (retval != API_SUCCESS)
            {
                printf("FAILED. Reason = 0x%04X\n", retval);
            }
            else
            {
                printf("OK. Wait for A2DP_CONNECT_CNF\n");

                /* Save SBC Codec IE */
                BT_mem_copy(a2dp_appl_sbc_codec_ie, codec_ie_conf, A2DP_SBC_CODEC_CAP_IE_LEN);

#ifndef A2DP_BRIDGING
#ifdef INCLUDE_A2DP_CODEC
#if (defined A2DP_SOURCE && defined A2DP_SINK)
                if (AVDTP_SEP_SINK == a2dp_appl_instance[codec_instance].role)
#endif /* (defined A2DP_SOURCE && defined A2DP_SINK) */
#ifdef A2DP_SINK
                {
                    appl_a2dp_jpl_configure(codec_ie_conf);
                }
#endif /* A2DP_SINK */
#if (defined A2DP_SOURCE && defined A2DP_SINK)
                else
#endif /* (defined A2DP_SOURCE && defined A2DP_SINK) */
#ifdef A2DP_SOURCE
                {
                    appl_a2dp_src_prepare();
                }
#endif /* A2DP_SOURCE */
#endif /* INCLUDE_A2DP_CODEC */
#endif /* A2DP_BRIDGING */
            }
#endif /* AVDTP_A2DP_CHAINED_CONNECT */

        }
        else
        {
            /* Try to get capabilites of next information element */
            a2dp_appl_handle_avdtp_discover_rsp ();
        }

        break;

    default:
        printf("\n");
        printf("*** Received Unknown Event 0x%02X. Result = 0x%04X\n",
        event_type, event_result);
    }

    return API_SUCCESS;
}


void a2dp_appl_alloc_instance (UCHAR * indx)
{
    int count;

    *indx = A2DP_MAX_CODECS;
    for (count = 0; count < A2DP_MAX_CODECS; count ++)
    {
        if (0x0 == a2dp_appl_instance[count].allocated)
        {
            a2dp_appl_instance[count].allocated = 0x1;
            *indx = count;
            return;
        }
    }

    return;
}

void a2dp_appl_free_instance (UCHAR indx)
{
    a2dp_appl_instance[indx].allocated = 0x0;
    a2dp_appl_instance[indx].stream_state = APPL_A2DP_STREAM_FALSE;
    BT_mem_set(a2dp_appl_instance[indx].bd_addr, 0x0, BT_BD_ADDR_SIZE);
}

void a2dp_appl_handle_avdtp_discover_rsp (void)
{
    API_RESULT retval;
    AVDTP_SEP_INFO sep_info;
    UCHAR count;

    for (count = 0; count < a2dp_appl_sep_info_buflen; count += 2)
    {
        printf("Response Buf [0] = 0x%02X, [1] = 0x%02X\n",
        a2dp_appl_sep_info_buf_start[count + 0], a2dp_appl_sep_info_buf_start[count + 1]);

        retval = BT_avdtp_decode_sep_information
                 (
                     a2dp_appl_sep_info_buf_start,
                     (UINT16) a2dp_appl_sep_info_buflen,
                     &sep_info
                 );

        /* Set response buffer to next SEP info index */
        a2dp_appl_sep_info_buf_start += 2;
        a2dp_appl_sep_info_buflen -= 2;

        if (API_SUCCESS != retval)
        {
            printf("*** FAILED to Decode SEP Information (0x%04X)\n",
            retval);
        }
        else
        {
            printf("\tRemote SEP Information [%d]:\n", count);

            /* SEP In Use */
            printf("\t    In Use     = %s\n",
            ((0x1 == sep_info.in_use) ? "Yes" : "No"));

            /* SEP Type */
            printf("\t    SEP Type   = 0x%02X -> ", sep_info.sep_type);
            switch (sep_info.sep_type)
            {
            case AVDTP_SEP_SOURCE:
                printf("Source\n");
                break;

            case AVDTP_SEP_SINK:
                printf("Sink\n");
                break;

            default:
                printf("????\n");
            }

            /* ACP SEID */
            printf("\t    ACP SEID   = 0x%02X\n", sep_info.acp_seid);

            /* Media Type */
            printf("\t    Media Type = 0x%02X -> ", sep_info.media_type);
            switch (sep_info.media_type)
            {
            case AVDTP_MEDIA_AUDIO:
                printf("Audio\n");
                break;

            case AVDTP_MEDIA_VIDEO:
                printf("Video\n");
                break;

            case AVDTP_MEDIA_MULTIMEDIA:
                printf("Multi\n");
                break;

            default:
                printf("????\n");
            }

#ifdef AVDTP_A2DP_CHAINED_CONNECT
            if ((AVDTP_MEDIA_AUDIO == sep_info.media_type) &&
                (0x00 == sep_info.in_use))
            {
                /* Set AVDTP Handle Remote SEID */
                AVDTP_SET_HANDLE_REMOTE_SEID (a2dp_appl_avdtp_handle, sep_info.acp_seid);

                /* AVDTP Get Capabilities */
                printf("AVDTP Get Capabilities ... ");
                retval = BT_avdtp_get_capabilities_req
                         (
                             &a2dp_appl_avdtp_handle,
                             a2dp_appl_sep_cap_buf,
                             A2DP_GET_CAPABILITIES_RESPONSE_LEN
                         );

                if (API_SUCCESS != retval)
                {
                    printf("FAILED. Reason = 0x%04X\n", retval);
                }
                else
                {
                    printf("OK. Wait for AVDTP_GET_CAPABILITIES_CNF\n");
                    break;
                }
            }
#endif /* AVDTP_A2DP_CHAINED_CONNECT */

        }
    }
}

#ifdef INCLUDE_A2DP_CODEC
#ifdef A2DP_SOURCE
#ifndef A2DP_BRIDGING
void appl_a2dp_src_prepare (void)
{
    API_RESULT retval;
    UINT16 samples_per_sec;
    UCHAR number_of_channels;
    UCHAR * codec_ie;
    SBC_CODEC_PARAM * codec_param;

    /* Get SEP Configuration Codec IE */
    codec_ie = a2dp_appl_sbc_codec_ie;

    /* Get SBC Encoder Codec Parameters */
    codec_param = &a2dp_sbc_encoder_io.encoder_params;

    /* Decode Sampling Frequency */
    switch (codec_ie[0] & 0xF0)
    {
    case A2DP_SBC_SAMPLING_FREQUENCY_16000:
        samples_per_sec = 16000;
        codec_param->sampling_frequency = 0;

        break;

    case A2DP_SBC_SAMPLING_FREQUENCY_32000:
        samples_per_sec = 32000;
        codec_param->sampling_frequency = 1;

        break;

    case A2DP_SBC_SAMPLING_FREQUENCY_44100:
        samples_per_sec = 44100;
        codec_param->sampling_frequency = 2;

        break;

    case A2DP_SBC_SAMPLING_FREQUENCY_48000:
        samples_per_sec = 48000;
        codec_param->sampling_frequency = 3;

        break;

    default:
        printf("*** SBC Config: Sampling Frequency = Unknown (0x%02X)!!\n",
        (codec_ie[0] & 0xF0));

        return;
    }

    /* Decode Channel Mode */
    switch (codec_ie[0] & 0x0F)
    {
    case A2DP_SBC_CHANNEL_MONO:
        codec_param->channel_mode = SBC_CHANNEL_MONO;
        codec_param->nrof_channels = 1;

        break;

    case A2DP_SBC_CHANNEL_DUAL:
        codec_param->channel_mode = SBC_CHANNEL_DUAL;
        codec_param->nrof_channels = 2;

        break;

    case A2DP_SBC_CHANNEL_STEREO:
        codec_param->channel_mode = SBC_CHANNEL_STEREO;
        codec_param->nrof_channels = 2;

        break;

    case A2DP_SBC_CHANNEL_JOINT_STEREO:
        codec_param->channel_mode = SBC_CHANNEL_JOINT_STEREO;
        codec_param->nrof_channels = 2;

        break;

    default:
        printf("*** SBC Config: Channel Mode = Unknown (0x%02X)!!\n",
        (codec_ie[0] & 0x0F));

        return;
    }

    /* Set Number of Channels */
    number_of_channels = codec_param->nrof_channels;

    /* Decode Block Length */
    switch (codec_ie[1] & 0xF0)
    {
    case A2DP_SBC_BLOCK_LENGTH_4:
        codec_param->nrof_blocks = SBC_BLOCK_SIZE_4;

        break;

    case A2DP_SBC_BLOCK_LENGTH_8:
        codec_param->nrof_blocks = SBC_BLOCK_SIZE_8;

        break;

    case A2DP_SBC_BLOCK_LENGTH_12:
        codec_param->nrof_blocks = SBC_BLOCK_SIZE_12;

        break;

    case A2DP_SBC_BLOCK_LENGTH_16:
        codec_param->nrof_blocks = SBC_BLOCK_SIZE_16;

        break;

    default:
        printf("*** SBC Config: Block Length = Unknown (0x%02X)!!\n",
        (codec_ie[1] & 0xF0));

        return;
    }

    /* Decode Subbands */
    switch (codec_ie[1] & 0x0C)
    {
    case A2DP_SBC_SUBBANDS_4:
        codec_param->nrof_subbands = SBC_SUBBAND_4;

        break;

    case A2DP_SBC_SUBBANDS_8:
        codec_param->nrof_subbands = SBC_SUBBAND_8;

        break;

    default:
        printf("*** SBC Config: Subbands = Unknown (0x%02X)!!\n",
        (codec_ie[1] & 0x0C));

        return;
    }

    /* Decode Allocation Method */
    switch (codec_ie[1] & 0x03)
    {
    case A2DP_SBC_ALLOCATION_METHOD_SNR:
        codec_param->allocation_method = SBC_SNR;

        break;

    case A2DP_SBC_ALLOCATION_METHOD_LOUDNESS:
        codec_param->allocation_method = SBC_LOUDNESS;

        break;

    default:
        printf("*** SBC Config: Allocation Method = Unknown (0x%02X)!!\n",
        (codec_ie[1] & 0x03));

        return;
    }

    /* Set Bitpool */
    codec_param->bitpool = codec_ie[3];

    /* Initialize SBC Decoder */
    retval = sbc_encoder_init (&a2dp_sbc_encoder_io);
    if (API_SUCCESS != retval)
    {
        printf("*** Failed to Initialize SBC Encoder: 0x%04X\n",
        retval);

        return;
    }

    /* Calculate Number of Bytes to be encoded per SBC frame */
    appl_a2dp_pcm_datalen = 2 *
                           codec_param->nrof_subbands *
                           codec_param->nrof_blocks *
                           codec_param->nrof_channels;

    /* Setup the Pl */
    a2dp_setup_pl
    (
        A2DP_EP_SOURCE,
        a2dp_pl_src_callback,
        samples_per_sec,
        16,
        number_of_channels,
        appl_a2dp_pcm_datalen
    );

}

static void a2dp_pl_src_callback
       (
           const UCHAR *    r_data,
           UINT16     r_datalen
       )
{
    app_a2dp_src_enqueue (r_data, r_datalen);
}

API_RESULT app_a2dp_src_enqueue
           (
               /* IN */ const UCHAR   * data,
               /* IN */  UINT16    datalen
           )
{
    INT32  n_free;
    UINT32 count;

    /*
     *  Get amount of free buffer space.
     */
    if (a2dp_src_buffer_wr_ptr >= a2dp_src_buffer_rd_ptr)
    {
        /*
         *    ----------DDDDDDDDDDDDDDD--------------X
         *    ^         ^              ^             ^
         *    |         |              |             |
         *    0       rd_ptr         wr_ptr         max
         *
         *  Free Space => '-----------'
         */
        n_free = (a2dp_src_buffer_size - a2dp_src_buffer_wr_ptr)
                + a2dp_src_buffer_rd_ptr;
    }
    else
    {
        /*
         *    DDDDDDDDDD---------------DDDDDDDDDDDDDDX
         *    ^         ^              ^             ^
         *    |         |              |             |
         *    0       wr_ptr         rd_ptr         max
         *
         *  Free Space => '-----------'
         */
        n_free = a2dp_src_buffer_rd_ptr - a2dp_src_buffer_wr_ptr;
    }

    /*
     *  Do we have enough space to accomodate new data ?
     *  Buffer Empty Condition: when rd_ptr == wr_ptr
     *  Buffer Full  Condition: when diff(rd_ptr, wr_ptr) == 1
     */
    if ((n_free < 1) || (n_free < datalen))
    {
        /* Overflow ! */
        /*APPL_ERR (bt_debug_fd, "+"); */
        return API_FAILURE;
    }

    /* Store new data into Buffer */
    for (count = 0; count < datalen; count++)
    {
        a2dp_src_buffer[a2dp_src_buffer_wr_ptr] = data[count];
        a2dp_src_buffer_wr_ptr++;

        if(a2dp_src_buffer_wr_ptr == a2dp_src_buffer_size)
        {
            a2dp_src_buffer_wr_ptr = 0;
        }
    }

    if (APP_A2DP_SRC_WR_TH_INIT == a2dp_src_wr_th_state)
    {
        /* Signal the waiting thread */
        BT_thread_mutex_lock (&a2dp_src_th_mutex);
        a2dp_src_wr_th_state = APP_A2DP_SRC_WR_TH_PLAYING;
        BT_thread_cond_signal (&a2dp_src_th_cond);
        BT_thread_mutex_unlock (&a2dp_src_th_mutex);
    }

    return API_SUCCESS;
}
#endif /* A2DP_BRIDGING */
DECL_STATIC void *a2dp_src_write_task (void * args)
{
    INT32  rd_ptr, index, remaining;
    UINT16 bytes_to_send, buf_index, encode_len;

    BT_LOOP_FOREVER()
    {
        if (APP_A2DP_SRC_WR_TH_INIT == a2dp_src_wr_th_state)
        {
            /* Wait for data in buffer */
            BT_thread_mutex_lock (&a2dp_src_th_mutex);
            BT_thread_cond_wait (&a2dp_src_th_cond, &a2dp_src_th_mutex);
            BT_thread_mutex_unlock (&a2dp_src_th_mutex);
        }
        else if (APP_A2DP_SRC_WR_TH_STOP == a2dp_src_wr_th_state)
        {
            /* Exit from task */
            return NULL;
        }

        if (a2dp_src_buffer_wr_ptr >= a2dp_src_buffer_rd_ptr)
        {
            /*
             *    ----------DDDDDDDDDDDDDDD--------------X
             *    ^         ^              ^             ^
             *    |         |              |             |
             *    0       rd_ptr         wr_ptr         max
             *
             *  Free Space => '-----------'
             */
            remaining = a2dp_src_buffer_wr_ptr - a2dp_src_buffer_rd_ptr;
        }
        else
        {
            /*
             *    DDDDDDDDDD---------------DDDDDDDDDDDDDDX
             *    ^         ^              ^             ^
             *    |         |              |             |
             *    0       wr_ptr         rd_ptr         max
             *
             *  Free Space => '-----------'
             */
            remaining = a2dp_src_buffer_size -
                    (a2dp_src_buffer_rd_ptr - a2dp_src_buffer_wr_ptr);
        }

        /* Do we really have anything to read ? */
        if (remaining < A2DP_SRC_SBC_BLOCK_MAX)
        {
            /* Wait for data in buffer */
            BT_thread_mutex_lock (&a2dp_src_th_mutex);
            a2dp_src_wr_th_state = APP_A2DP_SRC_WR_TH_INIT;
            BT_thread_cond_wait (&a2dp_src_th_cond, &a2dp_src_th_mutex);
            BT_thread_mutex_unlock (&a2dp_src_th_mutex);

            /* APPL_INF (bt_debug_fd, "remaining < 1\n"); */
            BT_usleep(1000);
            continue;
        }

        rd_ptr = a2dp_src_buffer_rd_ptr;

        bytes_to_send = (remaining > A2DP_SRC_SBC_BLOCK_MAX) ?
            A2DP_SRC_SBC_BLOCK_MAX : remaining;

        for (index = 0; index < bytes_to_send; index++)
        {
            pcm_to_send[index] = a2dp_src_buffer[rd_ptr];

            rd_ptr = rd_ptr + 1;
            if (rd_ptr == a2dp_src_buffer_size)
            {
                rd_ptr = 0;
            }
        }

        /* Update the read pointer */
        a2dp_src_buffer_rd_ptr = rd_ptr;

        buf_index = 0;

        while (buf_index < bytes_to_send)
        {
            if ((bytes_to_send - buf_index) <= A2DP_SRC_SBC_BLOCK_MAX)
            {
                encode_len = bytes_to_send - buf_index;
            }
            else
            {
                encode_len = A2DP_SRC_SBC_BLOCK_MAX;
            }
            
            a2dp_encode_n_send
            (
                a2dp_appl_instance[0].a2dp_instance,
                pcm_to_send + buf_index,
                encode_len
            );

            buf_index += encode_len;
        }

       /* BT_usleep(1000); */
    }
}

API_RESULT a2dp_encode_n_send
           (
               UINT8    a2dp_instance,
               UCHAR  * pcm_data,
               UINT16   pcm_datalen
           )
{
    API_RESULT        retval;
    UINT16            count;
    UINT16            sbc_datalen;

    /* Convert UCHAR LE16 PCM Data to UINT16 LE16 */
    for (count = 0; count < (pcm_datalen >> 1); count ++)
    {
        appl_a2dp_pcm_data_le[count] =
        (UINT16) ((pcm_data[2 * count + 1] << 8) | (pcm_data[2 * count]));
    }

    /* Initialize amount of buffer passed for SBC stream */
    sbc_datalen = A2DP_SRC_SBC_BLOCK_MAX;

    /* Prepare for SBC Encoder */
    a2dp_sbc_encoder_io.encoder_input_buflen = count;
    a2dp_sbc_encoder_io.encoder_input_buffer = appl_a2dp_pcm_data_le;

    a2dp_sbc_encoder_io.encoder_output_buffer = appl_a2dp_sbc_data;
    a2dp_sbc_encoder_io.encoder_output_buflen = sbc_datalen;

    /* Do SBC Encoding */
    retval = sbc_encoder
             (
                 &a2dp_sbc_encoder_io
             );

    if (API_SUCCESS != retval)
    {
        printf ("SBC Encoder failed - 0x%04X\n", retval);
        return retval;
    }

    /* Update SBC Frame Size */
    sbc_datalen = a2dp_sbc_encoder_io.encoder_output_buflen;

    /* printf ("~ "); */

    for (int i = 0U; i < A2DP_MAX_CODECS; i++)
    {
        if ((APPL_A2DP_STREAM_TRUE == a2dp_appl_instance[i].stream_state) &&
            (AVDTP_SEP_SOURCE == a2dp_appl_instance[i].role))
        {
            /* Write to A2DP */
            retval = BT_a2dp_media_write
            (
                a2dp_appl_instance[i].a2dp_instance,
                appl_a2dp_sbc_data,
                sbc_datalen
            );
        }
    }
    if (API_SUCCESS != retval)
    {
        /*printf ("A2DP media write failed - 0x%04X\n", retval); Re-visit*/
    }

    return retval;
}
#endif /* A2DP_SOURCE */

#ifdef A2DP_SINK
#ifndef A2DP_BRIDGING
static void appl_a2dp_jpl_configure(UCHAR* codec_ie)
{
    SBC_CODEC_PARAM * codec_param;
    UINT16 wav_sf;

    codec_param = &jpl_param.sbc_param;

    /* Get the sampling Frequency */
    switch (codec_ie[0] & 0xF0)
    {
    case A2DP_SBC_SAMPLING_FREQUENCY_16000:
        codec_param->sampling_frequency = 0;
        wav_sf = 16000;
        break;

    case A2DP_SBC_SAMPLING_FREQUENCY_32000:
        codec_param->sampling_frequency = 1;
        wav_sf = 32000;
        break;

    case A2DP_SBC_SAMPLING_FREQUENCY_44100:
        codec_param->sampling_frequency = 2;
        wav_sf = 44100;
        break;

    case A2DP_SBC_SAMPLING_FREQUENCY_48000:
        codec_param->sampling_frequency = 3;
        wav_sf = 48000;
        break;

    default:
        /* This should not be reached */
        printf("[APPL] Invalid sampling frequency\r\n");
        return;
    }

    /* Get the Channel Mode */
    switch (codec_ie[0] & 0x0F)
    {
    case A2DP_SBC_CHANNEL_MONO:
        codec_param->channel_mode = SBC_CHANNEL_MONO;
        codec_param->nrof_channels = 1;
        break;

    case A2DP_SBC_CHANNEL_DUAL:
        codec_param->channel_mode = SBC_CHANNEL_DUAL;
        codec_param->nrof_channels = 2;
        break;

    case A2DP_SBC_CHANNEL_STEREO:
        codec_param->channel_mode = SBC_CHANNEL_STEREO;
        codec_param->nrof_channels = 2;
        break;

    case A2DP_SBC_CHANNEL_JOINT_STEREO:
        codec_param->channel_mode = SBC_CHANNEL_JOINT_STEREO;
        codec_param->nrof_channels = 2;
        break;

    default:
        /* This should not be reached */
        printf("[APPL] Invalid Channel mode\r\n");
        return;
    }

    /* Get the Block Length */
    switch (codec_ie[1] & 0xF0)
    {
    case A2DP_SBC_BLOCK_LENGTH_4:
        codec_param->nrof_blocks = SBC_BLOCK_SIZE_4;
        break;

    case A2DP_SBC_BLOCK_LENGTH_8:
        codec_param->nrof_blocks = SBC_BLOCK_SIZE_8;
        break;

    case A2DP_SBC_BLOCK_LENGTH_12:
        codec_param->nrof_blocks = SBC_BLOCK_SIZE_12;
        break;

    case A2DP_SBC_BLOCK_LENGTH_16:
        codec_param->nrof_blocks = SBC_BLOCK_SIZE_16;
        break;

    default:
        /* This should not be reached */
        printf("[APPL] Invalid Block Length\r\n");
        return;
    }

    /* Get the Subbands */
    switch (codec_ie[1] & 0x0C)
    {
    case A2DP_SBC_SUBBANDS_4:
        codec_param->nrof_subbands = SBC_SUBBAND_4;
        break;

    case A2DP_SBC_SUBBANDS_8:
        codec_param->nrof_subbands = SBC_SUBBAND_8;
        break;

    default:
        /* This should not be reached */
        printf("[APPL] Invalid Subband\r\n");
        return;
    }

    /* Get the Allocation Method */
    switch (codec_ie[1] & 0x03)
    {
    case A2DP_SBC_ALLOCATION_METHOD_SNR:
        codec_param->allocation_method = SBC_SNR;
        break;

    case A2DP_SBC_ALLOCATION_METHOD_LOUDNESS:
        codec_param->allocation_method = SBC_LOUDNESS;
        break;

    default:
        /* This should not be reached */
        printf("[APPL] Invalid Allocation method\r\n");
        return;
    }

    /* Set Bitpool */
    codec_param->bitpool = codec_ie[3];

    jpl_param.pcm_num_frames =
        ((3 * (SBC_MAX_BLOCK_SIZE * SBC_MAX_SUBBAND)) /
        (codec_param->nrof_blocks * codec_param->nrof_subbands));

    jpl_param.pod_frames =
        ((18 * (SBC_MAX_BLOCK_SIZE * SBC_MAX_SUBBAND)) /
        (codec_param->nrof_blocks * codec_param->nrof_subbands));

    printf("[APPL] A2DP Sink Configured\r\n");

    /* Setup the pl */
    a2dp_setup_pl(A2DP_EP_SINK, a2dp_pl_snk_callback, wav_sf, 16, codec_param->nrof_channels, 1536);

    return;
}

static API_RESULT jpl_callback_handle
       (
           /* IN */ UCHAR   event_type,
           /* IN */ UCHAR * event_data,
           /* IN */ UINT16  event_datalen
       )
{
    /* printf("~ "); */

    appl_a2dp_jpl_pof = event_data;
    appl_a2dp_jpl_poflen = event_datalen;
    a2dp_write_pl(A2DP_EP_SINK, event_data, event_datalen);
}

static void a2dp_pl_snk_callback
       (
           /* IN */const UCHAR *  p_data,
           /* IN */ UINT16   p_datalen
       )
{
    /* printf("* "); */

    BT_jpl_remove_frames(appl_a2dp_jpl_pof, appl_a2dp_jpl_poflen);
}
#endif /* A2DP_BRIDGING */
#endif /* A2DP_SINK */
#endif /* INCLUDE_A2DP_CODEC */

#ifdef MULTI_PROFILE_FSM_SUPPORT
UCHAR appl_a2dp_get_sep_type(void)
{
    return sep_type_selected;
}

API_RESULT appl_a2dp_is_streaming(UCHAR *idx, UCHAR *bd_addr)
{
    UCHAR i, j;
    API_RESULT retval;

    retval = BT_FALSE;
    for (i = 0U; i < A2DP_MAX_CODECS; i++)
    {
        if (APPL_A2DP_STREAM_TRUE == a2dp_appl_instance[i].stream_state)
        {
#ifdef A2DP_BRIDGING
        	if (AVDTP_SEP_SINK == a2dp_appl_instance[i].role)
#endif /*A2DP_BRIDGING*/
        	{
                retval = BT_TRUE;
                for(j = 0; j < BT_BD_ADDR_SIZE; j++)
                {
                    bd_addr[j] = a2dp_appl_instance[i].bd_addr[j];
                }
                break;
        	}
        }
    }
    *idx = i;
    return retval;
}

#endif /* MULTI_PROFILE_FSM_SUPPORT */

void appl_a2dp_stream_start (UCHAR index)
{
    API_RESULT retval;
    UINT16 acl_handle;

    /* Choose an Instance */
#if 0
    for (index = 0; index < A2DP_MAX_CODECS; index ++)
    {
        if (a2dp_codec_instance == a2dp_appl_instance[index].a2dp_instance)
        {
            /* Matching instance found */
            break;
        }
    }
#endif

    if (index >= A2DP_MAX_CODECS)
    {
        printf("Instance is out of Range\n");
        /* return; */
    }
    else
    {
        if (0x00U == a2dp_appl_instance[index].allocated)
        {
            printf("Instance is not registered\n");
            /* return; */
        }
        else
        {
            /* A2DP Start */
            printf("A2DP Start ... "); fflush (stdout);
            retval = BT_a2dp_start
                     (
                         a2dp_appl_instance[index].a2dp_instance
                     );

            if (API_SUCCESS != retval)
            {
                printf("FAILED. Reason = 0x%04X\n", retval);
            }
            else
            {
                printf("OK. Wait for A2DP_START_CNF\n");

                /* Unsniff the link if required */
                (BT_IGNORE_RETURN_VALUE) BT_hci_get_acl_connection_handle(a2dp_appl_instance[index].bd_addr, &acl_handle);
                (BT_IGNORE_RETURN_VALUE) BT_hci_exit_sniff_mode(acl_handle);
            }
        }
    }

    return;
}


void appl_a2dp_stream_suspend (UCHAR index)
{
    API_RESULT retval;

    /* Choose an Instance */
#if 0
    for (index = 0; index < A2DP_MAX_CODECS; index ++)
    {
        if (a2dp_codec_instance == a2dp_appl_instance[index].a2dp_instance)
        {
            /* Matching instance found */
            break;
        }
    }
#endif
    if (index >= A2DP_MAX_CODECS)
    {
        printf("Instance is out of Range\n");
        /* return; */
    }

    else
    {
        if (0x00U == a2dp_appl_instance[index].allocated)
        {
            printf("Instance is not registered\n");
            /* return; */
        }
        else
        {
            /* A2DP Suspend */
            printf("A2DP Suspend ... "); fflush (stdout);
            retval = BT_a2dp_suspend
                     (
                         a2dp_appl_instance[index].a2dp_instance
                     );

            if (API_SUCCESS != retval)
            {
                printf("FAILED. Reason = 0x%04X\n", retval);
            }
            else
            {
                printf("OK. Wait for A2DP_SUSPEND_CNF\n");
            }
        }
    }

    return;
}

void a2dp_appl_show_instance(void)
{
    UINT32 indx;

    printf("\n");
    printf("       SEP     Media  Codec    Remote\n");
    printf("Index  Type    Type   Type     BD_ADDR                   State\n");
    printf("-----  ------  -----  -----    -------------------       -----\n");

    for (indx = 0U; indx < A2DP_MAX_CODECS; indx++)
    {
        if (0x0U == a2dp_appl_instance[indx].allocated)
        {
            printf("%3d    ", indx);
            printf("--      ");
            printf("--     ");
            printf("--       ");
            printf("--:--:--:--:--:--  ");
            printf("      NOT ALLOCATED\n");
            continue;
        }

        /* Index */
        printf("%3d    ", indx);

        /* SEP Type */
        switch (a2dp_appl_instance[indx].sep_cap.sep_type)
        {
        case AVDTP_SEP_SOURCE:
            printf("Source  ");
            break;

        case AVDTP_SEP_SINK:
            printf("Sink    ");
            break;

        default:
            printf("????    ");
            break;
        }

        /* Media Type */
        switch (a2dp_appl_instance[indx].sep_cap.codec_cap.media_type)
        {
        case AVDTP_MEDIA_AUDIO:
            printf("Audio  ");
            break;

        case AVDTP_MEDIA_VIDEO:
            printf("Video  ");
            break;

        case AVDTP_MEDIA_MULTIMEDIA:
            printf("Multi  ");
            break;

        default:
            printf("????    ");
            break;
        }

        /* Codec Type */
        switch (a2dp_appl_instance[indx].sep_cap.codec_cap.codec_type)
        {
        case AVDTP_CODEC_AUDIO_SBC:
            printf("SBC      ");
            break;

        case AVDTP_CODEC_AUDIO_MPEG_1_2:
            printf("MPG12    ");
            break;

        case AVDTP_CODEC_AUDIO_MPEG_2_4:
            printf("MPG24    ");
            break;

        case AVDTP_CODEC_AUDIO_ATRAC:
            printf("ATRAC    ");
            break;

        case AVDTP_CODEC_AUDIO_VENDOR_SPECIFIC:
            printf("VENDOR   ");
            break;

        default:
            printf("????    ");
            break;
        }


        /* Remote BD_ADDR */
        printf(BT_DEVICE_ADDR_ONLY_FRMT_SPECIFIER "  ",
            BT_DEVICE_ADDR_ONLY_PRINT_STR(a2dp_appl_instance[indx].bd_addr));

        /* State */
        printf("\n");
    }

    printf("\n");
}

void a2dp_appl_get_instance(UCHAR* indx)
{
    int choice;

    /* Show Instances */
    a2dp_appl_show_instance();
    BT_LOOP_FOREVER()
    {
        printf("Choose A2DP Instance = "); fflush(stdout); fflush(stdin);
        scanf("%d", &choice);
        if ((choice >= 0) || (choice < A2DP_MAX_CODECS))
        {
            break;
        }
    }

    *indx = (UCHAR)choice;
    return;
}

void a2dp_appl_print_codec_ie_configuration
(
    /* IN */  UCHAR   codec_type,
    /* IN */  UCHAR* codec_ie,
    /* IN */  UINT16  codec_ie_len
)
{
    if (NULL == codec_ie)
    {
        printf("NULL Codec IE\n");

        /* return; */
    }
    else
    {
        if (AVDTP_CODEC_AUDIO_SBC == codec_type)
        {
            printf("Code Type: SBC\n");

            if (A2DP_SBC_CODEC_CAP_IE_LEN == codec_ie_len)
            {
                printf("\tSBC Codec IE = 0x%02X 0x%02X 0x%02X 0x%02X\n",
                    codec_ie[0U], codec_ie[1U], codec_ie[2U], codec_ie[3U]);

                /* Decode Sampling Frequency */
                switch (codec_ie[0U] & 0xF0U)
                {
                case A2DP_SBC_SAMPLING_FREQUENCY_16000:
                    printf("\t-> Sampling Frequency = 16000\n");
                    break;

                case A2DP_SBC_SAMPLING_FREQUENCY_32000:
                    printf("\t-> Sampling Frequency = 32000\n");
                    break;

                case A2DP_SBC_SAMPLING_FREQUENCY_44100:
                    printf("\t-> Sampling Frequency = 44100\n");
                    break;

                case A2DP_SBC_SAMPLING_FREQUENCY_48000:
                    printf("\t-> Sampling Frequency = 48000\n");
                    break;

                default:
                    printf("\t-> Sampling Frequency = ?????\n");
                    break;
                }

                /* Decode Channel Mode */
                switch (codec_ie[0U] & 0x0FU)
                {
                case A2DP_SBC_CHANNEL_MONO:
                    printf("\t-> Channel Mode = Mono (1)\n");
                    break;

                case A2DP_SBC_CHANNEL_DUAL:
                    printf("\t-> Channel Mode = Dual (2)\n");
                    break;

                case A2DP_SBC_CHANNEL_STEREO:
                    printf("\t-> Channel Mode = Stereo (2)\n");
                    break;

                case A2DP_SBC_CHANNEL_JOINT_STEREO:
                    printf("\t-> Channel Mode = Joint Stereo (2)\n");
                    break;

                default:
                    printf("\t-> Channel Mode = ?????\n");
                    break;
                }

                /* Decode Block Length */
                switch (codec_ie[1U] & 0xF0U)
                {
                case A2DP_SBC_BLOCK_LENGTH_4:
                    printf("\t-> Block Length = 4\n");
                    break;

                case A2DP_SBC_BLOCK_LENGTH_8:
                    printf("\t-> Block Length = 8\n");
                    break;

                case A2DP_SBC_BLOCK_LENGTH_12:
                    printf("\t-> Block Length = 12\n");
                    break;

                case A2DP_SBC_BLOCK_LENGTH_16:
                    printf("\t-> Block Length = 16\n");
                    break;

                default:
                    printf("\t-> Block Length = ?????\n");
                    break;
                }

                /* Decode Subbands */
                switch (codec_ie[1U] & 0x0CU)
                {
                case A2DP_SBC_SUBBANDS_4:
                    printf("\t-> Subbands = 4\n");
                    break;

                case A2DP_SBC_SUBBANDS_8:
                    printf("\t-> Subbands = 8\n");
                    break;

                default:
                    printf("\t-> Subbands = ?????\n");
                    break;
                }

                /* Decode Allocation Method */
                switch (codec_ie[1U] & 0x03U)
                {
                case A2DP_SBC_ALLOCATION_METHOD_SNR:
                    printf("\t-> Allocation Method = SNR\n");
                    break;

                case A2DP_SBC_ALLOCATION_METHOD_LOUDNESS:
                    printf("\t-> Allocation Method = Loudness\n");
                    break;

                default:
                    printf("\t-> Allocation Method = ?????\n");
                    break;
                }

                printf("\t-> Bitpool = %d, %d\n", codec_ie[2U], codec_ie[3U]);
            }
            else
            {
                printf("*** A2DP_CONFIGURE_IND: No Event Data/Data Length\n");
            }
        }
#ifdef A2DP_MPEG_1_2
        else if (AVDTP_CODEC_AUDIO_MPEG_1_2 == codec_type)
        {
            UINT16 bit_rate_index;

            printf("Code Type: MPEG-1,2\n");

            if (A2DP_MPEG_1_2_CODEC_CAP_IE_LEN == codec_ie_len)
            {
                printf("\tMPEG-1,2 Codec IE = 0x%02X 0x%02X 0x%02X 0x%02X\n",
                    codec_ie[0U], codec_ie[1U], codec_ie[2U], codec_ie[3U]);

                /* Decode MPEG Layer */
                printf("\t    -> Layer = ");
                switch (codec_ie[0U] & 0xE0U)
                {
                case A2DP_MPEG_1_2_LAYER_I:
                    printf("I");
                    break;

                case A2DP_MPEG_1_2_LAYER_II:
                    printf("II");
                    break;

                case A2DP_MPEG_1_2_LAYER_III:
                    printf("III");
                    break;

                default:
                    printf("?????");
                    break;
                }
                printf("\n");

                /* Decode CRC */
                printf("\t    -> CRC = ");
                if (codec_ie[0U] & 0x10U)
                {
                    printf("ON");
                }
                else
                {
                    printf("OFF");
                }
                printf("\n");

                /* Decode Channel Mode */
                printf("\t    -> Channel Mode = ");
                switch (codec_ie[0U] & 0x0FU)
                {
                case A2DP_MPEG_1_2_CHANNEL_MONO:
                    printf("MONO");
                    break;
                case A2DP_MPEG_1_2_CHANNEL_STEREO:
                    printf("STEREO");
                    break;
                case A2DP_MPEG_1_2_CHANNEL_DUAL:
                    printf("DUAL");
                    break;
                case A2DP_MPEG_1_2_CHANNEL_JOINT_STEREO:
                    printf("JOINT_STEREO");
                    break;
                default:
                    printf("?????");
                    break;
                }
                printf("\n");

                /* Decode Media Payload Format */
                printf("\t    -> MPF = ");
                if (codec_ie[1U] & 0x40U)
                {
                    printf("MPF-2");
                }
                else
                {
                    printf("MPF-1");
                }
                printf("\n");

                /* Decode Sampling Frequency */
                printf("\t    -> Sampling Frequency = ");
                switch (codec_ie[1U] & 0x3FU)
                {
                case A2DP_MPEG_1_2_SAMPLING_FREQUENCY_16000:
                    printf("16000");
                    break;

                case A2DP_MPEG_1_2_SAMPLING_FREQUENCY_22050:
                    printf("22050");
                    break;

                case A2DP_MPEG_1_2_SAMPLING_FREQUENCY_24000:
                    printf("24000");
                    break;

                case A2DP_MPEG_1_2_SAMPLING_FREQUENCY_32000:
                    printf("32000");
                    break;

                case A2DP_MPEG_1_2_SAMPLING_FREQUENCY_44100:
                    printf("44100");
                    break;

                case A2DP_MPEG_1_2_SAMPLING_FREQUENCY_48000:
                    printf("48000");
                    break;

                default:
                    printf("?????");
                    break;
                }
                printf("\n");

                /* Decode Variable Bit Rate */
                printf("\t    -> VBR = ");
                if (codec_ie[2U] & 0x80U)
                {
                    printf("ON");
                }
                else
                {
                    printf("OFF");
                }
                printf("\n");

                /* Decode Bit Rate Index */
                bit_rate_index = codec_ie[2U] & 0x7FU;
                bit_rate_index = (bit_rate_index << 8U) | codec_ie[3U];

                printf("\t    -> Bit Rate Index = ");
                switch (bit_rate_index)
                {
                case A2DP_MPEG_1_2_BITRATE_INDEX_0:
                    printf("0");
                    break;
                case A2DP_MPEG_1_2_BITRATE_INDEX_1:
                    printf("1");
                    break;
                case A2DP_MPEG_1_2_BITRATE_INDEX_2:
                    printf("2");
                    break;
                case A2DP_MPEG_1_2_BITRATE_INDEX_3:
                    printf("3");
                    break;
                case A2DP_MPEG_1_2_BITRATE_INDEX_4:
                    printf("4");
                    break;
                case A2DP_MPEG_1_2_BITRATE_INDEX_5:
                    printf("5");
                    break;
                case A2DP_MPEG_1_2_BITRATE_INDEX_6:
                    printf("6");
                    break;
                case A2DP_MPEG_1_2_BITRATE_INDEX_7:
                    printf("7");
                    break;
                case A2DP_MPEG_1_2_BITRATE_INDEX_8:
                    printf("8");
                    break;
                case A2DP_MPEG_1_2_BITRATE_INDEX_9:
                    printf("9");
                    break;
                case A2DP_MPEG_1_2_BITRATE_INDEX_10:
                    printf("10");
                    break;
                case A2DP_MPEG_1_2_BITRATE_INDEX_11:
                    printf("11");
                    break;
                case A2DP_MPEG_1_2_BITRATE_INDEX_12:
                    printf("12");
                    break;
                case A2DP_MPEG_1_2_BITRATE_INDEX_13:
                    printf("13");
                    break;
                case A2DP_MPEG_1_2_BITRATE_INDEX_14:
                    printf("14");
                    break;
                default:
                    printf("?????");
                    break;
                }
                printf("\n");
            }
            else
            {
                printf("*** A2DP_CONFIGURE_IND: No Event Data/Data Length\n");
            }
        }
#endif /* A2DP_MPEG_1_2 */

#ifdef A2DP_MPEG_2_4
        else if (AVDTP_CODEC_AUDIO_MPEG_2_4 == codec_type)
        {
            UINT16 sampling_rate;
            UINT32 bit_rate;

            printf("Code Type: MPEG-2,4\n");

            if (A2DP_MPEG_2_4_CODEC_CAP_IE_LEN == codec_ie_len)
            {
                printf("\tMPEG-2,4 Codec IE = 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X\n",
                    codec_ie[0U], codec_ie[1U], codec_ie[2U], codec_ie[3U],
                    codec_ie[4U], codec_ie[5U]);

                /* Decode MPEG Object Type */
                printf("\t    -> Object Type = ");
                switch (codec_ie[0U] & 0xF0U)
                {
                case A2DP_MPEG_2_4_OBJ_TYPE_MPEG2_AAC_LC:
                    printf("MPEG-2 AAC LC");
                    break;

                case A2DP_MPEG_2_4_OBJ_TYPE_MPEG4_AAC_LC:
                    printf("MPEG-4 AAC LC");
                    break;

                case A2DP_MPEG_2_4_OBJ_TYPE_MPEG4_AAC_LTP:
                    printf("MPEG-4 AAC LTP");
                    break;

                case A2DP_MPEG_2_4_OBJ_TYPE_MPEG4_AAC_SCALABLE:
                    printf("MPEG-4 AAC SCALABLE");
                    break;

                default:
                    printf("?????");
                    break;
                }
                printf("\n");

                sampling_rate = (UINT16)codec_ie[1U];
                sampling_rate = ((sampling_rate << 8U) | (codec_ie[2U] & 0xF0U));

                /* Decode Sampling Frequency */
                printf("\t    -> Sampling Frequency = ");
                switch (sampling_rate)
                {
                case A2DP_MPEG_2_4_SAMPLING_FREQUENCY_8000:
                    printf("8000");
                    break;
                case A2DP_MPEG_2_4_SAMPLING_FREQUENCY_11025:
                    printf("11025");
                    break;

                case A2DP_MPEG_2_4_SAMPLING_FREQUENCY_12000:
                    printf("12000");
                    break;

                case A2DP_MPEG_2_4_SAMPLING_FREQUENCY_16000:
                    printf("16000");
                    break;

                case A2DP_MPEG_2_4_SAMPLING_FREQUENCY_22050:
                    printf("22050");
                    break;

                case A2DP_MPEG_2_4_SAMPLING_FREQUENCY_24000:
                    printf("24000");
                    break;

                case A2DP_MPEG_2_4_SAMPLING_FREQUENCY_32000:
                    printf("32000");
                    break;

                case A2DP_MPEG_2_4_SAMPLING_FREQUENCY_44100:
                    printf("44100");
                    break;

                case A2DP_MPEG_2_4_SAMPLING_FREQUENCY_48000:
                    printf("48000");
                    break;

                case A2DP_MPEG_2_4_SAMPLING_FREQUENCY_64000:
                    printf("64000");
                    break;

                case A2DP_MPEG_2_4_SAMPLING_FREQUENCY_88200:
                    printf("88200");
                    break;

                case A2DP_MPEG_2_4_SAMPLING_FREQUENCY_96000:
                    printf("96000");
                    break;

                default:
                    printf("?????");
                    break;
                }

                printf("\n");

                /* Decode Channels */
                printf("\t    -> Channels = ");
                switch (codec_ie[2U] & 0x0CU)
                {
                case A2DP_MPEG_2_4_CHANNELS_1:
                    printf("1");
                    break;
                case A2DP_MPEG_2_4_CHANNELS_2:
                    printf("2");
                    break;
                default:
                    printf("?????");
                    break;
                }
                printf("\n");

                /* Decode Variable Bit Rate */
                printf("\t    -> VBR = ");
                if (codec_ie[3U] & 0x80U)
                {
                    printf("ON");
                }
                else
                {
                    printf("OFF");
                }

                printf("\n");

                /* Decode Bit Rate */
                bit_rate = 0U;
                bit_rate = codec_ie[3U] & 0x7FU;
                bit_rate = (bit_rate << 8U) | codec_ie[4U];
                bit_rate = (bit_rate << 8U) | codec_ie[5U];

                printf("\t    -> Bit Rate = ");
                if (bit_rate)
                {
                    printf("%d", bit_rate);
                }
                else
                {
                    printf("?????");
                }
                printf("\n");
            }
            else
            {
                printf("*** A2DP_CONFIGURE_IND: No Event Data/Data Length\n");
            }
        }
#endif /* A2DP_MPEG_2_4 */
#ifdef A2DP_VENDOR_CODEC
        else if (AVDTP_CODEC_AUDIO_VENDOR_SPECIFIC == codec_type)
        {
            UINT32 vendor_id;
            UINT16 vendor_codec_id, rem_ie_len;
            UCHAR  i;

            printf("Code Type: Vendor Specific\n");

            /* Length should be greater than 6 */
            if (codec_ie_len > 6U)
            {
                BT_UNPACK_LE_4_BYTE(&vendor_id, &codec_ie[0U]);
                printf("\t    -> Vendor ID: 0x%08X\n", vendor_id);

                BT_UNPACK_LE_2_BYTE(&vendor_codec_id, &codec_ie[4U]);
                printf("\t    -> Vendor Codec ID: 0x%04X\n", vendor_codec_id);

                rem_ie_len = (codec_ie_len - 6U);

                printf("\t    -> Vendor Codec Value(in Hex): ");
                if (0x00U != rem_ie_len)
                {
                    for (i = 0U; i < rem_ie_len; i++)
                    {
                        printf("0x%02X\n", codec_ie[6U + i]);
                    }
                    printf("\n");
                }
                else
                {
                    printf("???\n");
                }

                /**
                 * Since Vendor Specific Codec is NOT part of A2DP specification,
                 * application has to take core Codec Config parameter validation.
                 * If it doesn't match as per requirement, application has to take
                 * appropriate action, like initiate disconnection etc.
                 */
                printf("Note:Application has " \
                    "to take care of the validation of Codec config parameters\n\n");
            }
            else
            {
                printf("*** A2DP_CONFIGURE_IND: No Event Data/Data Length\n");
            }
        }
#endif /* A2DP_VENDOR_CODEC */
    }

    return;
}
void a2dp_appl_save_codec_ie_configuration
(
    /* IN */  UCHAR   role,
    /* IN */  UCHAR   codec_type,
    /* IN */  UCHAR* codec_ie,
    /* IN */  UINT16   codec_ie_len
)
{
    UCHAR* codec_ie_storage;
    API_RESULT retval;

    /* Init */
    retval = API_SUCCESS;
    codec_ie_storage = NULL;

    if ((NULL == codec_ie) ||
        (0x00U == codec_ie_len))
    {
        printf("Invalid parameters to save Codec IE Info.\n");
        retval = API_FAILURE;  /* return; */
    }

    if (API_SUCCESS == retval)
    {
        if (AVDTP_CODEC_AUDIO_SBC == codec_type)
        {
            /* Save SBC Codec IE */
            codec_ie_storage = a2dp_appl_sbc_codec_ie;
        }
#ifdef A2DP_MPEG_1_2
        else if (AVDTP_CODEC_AUDIO_MPEG_1_2 == codec_type)
        {
            /* Save MPEG-1,2 Codec IE */
            codec_ie_storage = appl_a2dp_mpeg12_codec_ie;
        }
#endif /* A2DP_MPEG_1_2 */
#ifdef A2DP_MPEG_2_4
        else if (AVDTP_CODEC_AUDIO_MPEG_2_4 == codec_type)
        {
            /* Save MPEG-2,4 Codec IE */
            codec_ie_storage = appl_a2dp_mpeg24_codec_ie;
        }
#endif /* A2DP_MPEG_2_4 */
#ifdef A2DP_VENDOR_CODEC
        else if (AVDTP_CODEC_AUDIO_VENDOR_SPECIFIC == codec_type)
        {
            /* Save Vendor Specific Codec IE */
            codec_ie_storage = appl_a2dp_vendor_codec_ie;
        }
#endif /* A2DP_VENDOR_CODEC */
        else
        {
            /* No matching codec found */
            retval = API_FAILURE;  /* return; */
        }
    }

    if (API_SUCCESS == retval)
    {
        /* Save Codec IE */
        BT_mem_copy
        (
            codec_ie_storage,
            codec_ie,
            codec_ie_len
        );

        /* jpl configuration and src prep is not needed for a2dp bridging app */
#ifndef A2DP_BRIDGING
//currently this function is used only during A2DP_BRIDGING, hence commenting as it is unneccessary
#if 0 
        /* Check if codec is SBC */
        if (AVDTP_CODEC_AUDIO_SBC == codec_type)
        {
            if (AVDTP_SEP_SINK == role)
            {
#ifdef A2DP_SINK
                appl_a2dp_jpl_configure(codec_ie);
#else
                printf("A2DP_SINK Flag is not defined\n");
#endif /* A2DP_SINK */
            }
#ifdef A2DP_SOURCE
            else
            {
                a2dp_appl_src_prepare();
            }
#endif /* A2DP_SOURCE */
        }
#endif
#endif //A2DP_BRIDGING
    }
    return;
}

#ifdef A2DP_BRIDGING
uint8_t a2dp_find_codec_sink_instance (uint8_t *sep_type)
{
	uint8_t a2dp_sink_instance = 0xFF;

	for (int i = 0U; i < A2DP_MAX_CODECS; i++)
	{
		if ( (a2dp_appl_instance[i].role == AVDTP_SEP_SINK) &&
				(a2dp_appl_instance[i].a2dp_connection_state == APPL_A2DP_CONNECTED) )
			{
				a2dp_sink_instance = i;
				*sep_type = AVDTP_SEP_SINK;
				break;
			}
	}

	return a2dp_sink_instance;
}

UINT8 a2dp_find_free_sep_instance (UCHAR sep_type)
{
	UINT8 a2dp_instance = 0xFF;

	for (int i = 0U; i < A2DP_MAX_CODECS; i++)
	{
		if ((a2dp_appl_instance[i].role == sep_type) &&
			(BT_FALSE == BT_BD_ADDR_IS_NON_ZERO(a2dp_appl_instance[i].bd_addr)) &&
			(a2dp_appl_instance[i].allocated))
			{
				a2dp_instance = i;
				break;
			}
	}

	return a2dp_instance;
}
uint8_t a2dp_find_connected_a2dp_instance (uint8_t current_instance)
{
	uint8_t connected_a2dp_instance = 0xFFU;

	if (current_instance != 0xFFU)
	{
		for (int i = 0U; i < A2DP_MAX_CODECS; i++)
		{
			if ((i != current_instance) &&
				(a2dp_appl_instance[i].role != a2dp_appl_instance[current_instance].role) &&
				(a2dp_appl_instance[i].a2dp_connection_state == APPL_A2DP_CONNECTED))
			{
				connected_a2dp_instance = i;
				break;
			}
		}
	}
	printf ("a2dp_find_connected_a2dp_instance, curr: %d, other: %d\n",current_instance, connected_a2dp_instance);
	return connected_a2dp_instance;
}

uint8_t a2dp_find_a2dp_instance (UCHAR *bd_addr)
{
	uint8_t current_a2dp_instance = 0xFFU;
	for (int i = 0U; i < A2DP_MAX_CODECS; i++)
	{
        if (BT_TRUE == BT_BD_ADDR_IS_NON_ZERO(a2dp_appl_instance[i].bd_addr) &&
        		(BT_COMPARE_ADDR(bd_addr, a2dp_appl_instance[i].bd_addr) == BT_TRUE))
        {
        	current_a2dp_instance = i;
        	break;
        }
	}
	return current_a2dp_instance;
}
UCHAR a2dp_find_avrcp_target_instance ()
{
	UCHAR avrcp_index = AVRCP_MAX_PROFILES;

	for (int index = 0; index < A2DP_MAX_CODECS; index++)
	{
		if (AVDTP_SEP_SINK == a2dp_appl_instance[index].role)
		{
			avrcp_index = appl_avrcp_get_connected_handle((UCHAR*)a2dp_appl_instance[index].bd_addr);
			printf("FOUND CONNECTED TARGET \t    " BT_DEVICE_ADDR_ONLY_FRMT_SPECIFIER "\n",BT_DEVICE_ADDR_ONLY_PRINT_STR(a2dp_appl_instance[index].bd_addr));
			/* Matching instance found */
			break;
		}
	}
	return avrcp_index;
}
#endif /*A2DP_BRIDGING*/

#endif /* A2DP */


