/**
 *  \file appl_ga_ucs.c
 *
 *  \brief This file is a generic application example that demonstrates the
 *  usage of BAP - Unicast Server exposed by BAP Client and BAP Server library.
 */

/*
 *  Copyright (C) 2020. Mindtree Ltd.
 *  All rights reserved.
 */

/* --------------------------------------------- Header File Inclusion */
#include "appl_ga_ucs.h"
#include "appl_hci.h"
#include "appl_ga_utils_audio_src.h"
#include "appl_ga_utils_audio_snk.h"

#ifdef BAP_UCS

/* --------------------------------------------- Global Definitions */

static const char ucs_menu_options[] = " \n\
================ GA Unicast Server MENU ================ \n\
    0. Exit. \n\
    1. Refresh this Menu. \n\
\n\
================ Service Management (ASCS) ~ Operations(BAP Procedures) ============ \n\
    2  Register ASE. \n\
    3. Update ASE QoS Capability \n\
    4. ASE Send Audio Context as Available. \n\
    5. ASE Send Auto Codec Configured. \n\
    6. ASE Send Auto Rx Start Ready for Local ASE Sink. \n\
    7. ASE Send Auto Update Metadata. \n\
    8. ASE Send Auto Disable. \n\
    9. ASE Send Auto Release. \n\
   10. ASE Send Release Complete. \n\
\n\
================ CIS Management ~ HCI ============ \n\
   15. ASE Disconnect CIS. \n\
\n\
================ ASE Management ~ Display ============ \n\
   20. Display Local ASEs Data for a Connected Device. \n\
   21. Display all Local ASEs Data. \n\
\n\
================ Device Management ~ Setting ============ \n\
   22. Display all Connected Devices. \n\
\n\
Your Option ?: ";

extern UINT8 uc_role;

/* Timer Handle for Automate Release Complete */
DECL_STATIC BT_timer_handle  appl_ga_ucs_trigger_release_complete_timer_handle;

/* --------------------------------------------- Data types /Structures */
ASCS_ASE_INFO  ascs;

typedef struct _APPL_GA_UCS_ASE_RELEASE_COMPLETE_INFO
{
    GA_ENDPOINT device;
    UINT8 ase_count;
    UINT8 ase_index[MAX_UC_ASE];
}APPL_GA_UCS_ASE_RELEASE_COMPLETE_INFO;
/* --------------------------------------------- Macros */
void appl_ga_ucs_update_transmitting_audio
     (
         UINT16 cis_handle,
         GA_LC3_CODEC_SPECIFIC_CONF cs_conf,
         UINT8 qos_conf_set_id,
         UINT8 bps,
         UINT8 status
     );

void appl_ga_ucs_update_receiving_audio
     (
         UINT16 cis_handle,
         GA_LC3_CODEC_SPECIFIC_CONF cs_conf,
         UINT8 bps,
         UINT8 status
     );

#define appl_ga_ucs_start_transmitting_audio(cis_handle, cs_conf, qos_conf_set_id, bps) \
        appl_ga_ucs_update_transmitting_audio(cis_handle, cs_conf, qos_conf_set_id, bps, GA_TRUE)

#define appl_ga_ucs_stop_transmitting_audio(cis_handle, cs_conf, qos_conf_set_id, bps) \
        appl_ga_ucs_update_transmitting_audio(cis_handle, cs_conf, qos_conf_set_id, bps, GA_FALSE)

#define appl_ga_ucs_start_receiving_audio(cis_handle, cs_conf, bps) \
        appl_ga_ucs_update_receiving_audio(cis_handle, cs_conf, bps, GA_TRUE)

#define appl_ga_ucs_stop_receiving_audio(cis_handle, cs_conf, bps) \
        appl_ga_ucs_update_receiving_audio(cis_handle, cs_conf, bps, GA_FALSE)


void appl_ga_ucs_handle_iso_data_path_event
     (
         UINT16 cis_conn_handle,
         UCHAR  state,
         UCHAR  status
     );

void appl_ga_ucs_handle_disconnection_event
     (
         UINT16  conn_status,
         UINT16  conn_handle
     );

void appl_ga_ucs_handle_cis_established_event
     (
         UINT16 cis_conn_handle,
         UINT16 cis_conn_status
     );
void appl_ga_ucs_handle_cis_request_event
     (
         UINT16 acl_handle,
         UINT16 cis_handle,
         UINT8 cig_id,
         UINT8 cis_id
     );

void appl_ga_ucs_trigger_release_complete_using_cis_handle
     (
         UINT16 cis_conn_handle
     );
void appl_ga_ucs_trigger_release_complete
     (
         GA_ENDPOINT * device,
         UINT8         ase_count,
         UINT8       * ase_index
     );

GA_RESULT appl_ga_ucs_init_unicast_server_info(void);
void appl_ga_ucs_init_conn_dev_index
     (
         UINT8 conn_dev_index,
         UINT8 ase_index
     );

#ifndef APPL_GA_USE_CONFIG_FILE_FOR_INPUT
GA_RESULT appl_ga_ucs_register_ascs_using_runtime_values
          (
              /* IN */  APPL_GA_ROLE   role,
              /* OUT */ ASE          * ase
          );
#else /* APPL_GA_USE_CONFIG_FILE_FOR_INPUT */
UINT8 appl_ga_ucs_ascs_get_ase_count_using_default_values(APPL_GA_ROLE role);
GA_RESULT appl_ga_ucs_register_ascs_using_default_values
          (
              /* IN */  APPL_GA_ROLE   role,
              /* OUT */ ASE          * ase
          );
#endif /* APPL_GA_USE_CONFIG_FILE_FOR_INPUT */
GA_RESULT appl_ga_ucs_get_common_params_for_auto_operations
          (
              GA_ENDPOINT * device,
              UINT8       * ase_count,
              UINT8       * ase_id
          );
void appl_ga_ucs_auto_codec_config(void);
void appl_ga_ucs_auto_rx_start_ready(void);
void appl_ga_ucs_auto_update_metadata(void);
void appl_ga_ucs_auto_disable(void);
void appl_ga_ucs_auto_release(void);
void appl_ga_ucs_release_complete(void);
void appl_ga_ucs_display_ase_data_for_a_conn_dev(void);
void appl_ga_ucs_display_all_ase_data(void);
void appl_ga_ucs_ase_disconnect_cis(void);

GA_RESULT appl_ga_fetch_conn_dev_index_ase_index_from_acl_conn_handle
          (
              UINT16   acl_conn_handle,
              UINT8  * conn_dev_index,
              UINT8  * ase_count,
              UINT8  * ase_index
          );

GA_RESULT appl_ga_ucs_get_ase_index_from_conn_dev_index
          (
              UINT8   conn_dev_index,
              UINT8 * ase_count,
              UINT8 * ase_index
          );

GA_RESULT appl_ga_ucs_get_ase_index_from_ase_id
          (
              UINT8   ase_id,
              UINT8 * ase_index
          );
GA_RESULT appl_ga_ucs_get_ase_index_from_cis_conn_handle
          (
              UINT16   cis_conn_handle,
              UINT8  * ase_count,
              UINT8  * ase_index
          );
GA_RESULT appl_ga_ucs_fetch_ase_index_from_acl_conn_handle_cig_id_cis_id
          (
              UINT16   acl_handle,
              UINT8    cig_id,
              UINT8    cis_id,
              UINT8  * ase_count,
              UINT8  * ase_index
          );

GA_RESULT appl_ga_ucs_remove_iso(UINT8 ase_index, UINT16 cis_conn_handle);
void appl_ga_ucs_terminate_cis(UINT16 cis_conn_handle);
GA_RESULT appl_ga_ucs_setup_iso(UINT8 ase_index);
void appl_ga_ucs_update_conn_dev_index
     (
         GA_ENDPOINT device,
         UINT8       ase_index
     );
void appl_ga_ucs_update_cis_conn_state
     (
         UINT8   ase_index,
         UINT8   conn,
         UINT16  cis_conn_status
     );

GA_RESULT appl_ga_ucs_is_cis_connect_accept_allowed
          (
              UINT8 * ase_index,
              UINT8   ase_count
          );
GA_RESULT appl_ga_ucs_is_cis_disconnect_allowed(UINT8 ase_index);

GA_RESULT appl_ga_ucs_accept_cis(UINT16 cis_conn_handle);
GA_RESULT appl_ga_ucs_reject_cis(UINT16 cis_conn_handle, UCHAR reason);

void appl_ga_ucs_pacs_display_common_event_info
     (
        GA_ENDPOINT * device,
        UINT16        ga_status
     );
void appl_ga_ucs_ascs_display_common_event_info
     (
        GA_ENDPOINT * device,
        UINT16        ga_status
     );

GA_RESULT appl_ga_ucs_validate_ase_cp
          (
              UINT8         ase_index,
              void        * data,
              UINT8         event
          );

GA_RESULT appl_ga_ucs_validate_ase_cp_codec_cfg_for_lc3
          (
              UINT8                        ase_index,
              GA_LC3_CODEC_SPECIFIC_CONF * csc
          );

GA_RESULT appl_ga_ucs_validate_ase_cp_qos_cfg_for_lc3
          (
              UINT8         ase_index,
              GA_QOS_CONF * csc
          );
GA_RESULT appl_ga_ucs_validate_ase_cp_metadata
          (
              UINT8         ase_index,
              GA_METADATA * metadata
          );
UINT8 appl_ga_ucs_is_metadata_unsupp_and_invalid
      (
          GA_METADATA * metadata,
          UINT8       * reason,
          UINT8       * response
      );
UINT8 appl_ga_ucs_is_metadata_rejected_and_unspecified
      (
          UINT8         ase_index,
          GA_METADATA * metadata,
          UINT8         metadata_type,
          UINT8       * reason,
          UINT8       * response
      );
GA_RESULT app_ga_ucs_bap_cig_cis_exists
          (
              UINT8 ase_index,
              UINT8 cig_id,
              UINT8 cis_id
          );
UINT8 app_ga_ucs_is_config_supp(UINT8 * reason);
UINT8 app_ga_ucs_bap_is_config_valid(UINT8 * reason);
UINT8 app_ga_ucs_bap_is_config_to_be_rejected(UINT8 * reason);

GA_RESULT appl_ga_ucs_is_release_complete_allowed(UINT8 ase_index);

UINT8 appl_ga_ucs_get_cig_cis_shared_bidirectional_ase_index
      (
          UINT8   ase_index,
          UINT8 * ase_index_using_same_cis
      );

GA_RESULT appl_ga_ucs_src_get_csc_conf_aca_from_pacs_sacc
          (
              GA_LC3_CODEC_SPECIFIC_CONF * csc
          );
GA_RESULT appl_ga_ucs_snk_get_csc_conf_aca_from_pacs_sacc
          (
              GA_LC3_CODEC_SPECIFIC_CONF * csc
          );

void appl_ga_ucs_trigger_release_complete_timer_handler
     (
         void  * data,
         UINT16  datalen
     );

/* --------------------------------------------- APIs */

GA_RESULT appl_ga_ucs_hci_cb_handler
          (
              UINT8   event_code,
              UINT8 * event_data,
              UINT8   event_datalen
          )
{
    UINT8      value_1;
    UINT16     value_2;
    UINT8      marker;
    UCHAR      status;
    UINT16     cis_conn_handle;
    UINT16     acl_conn_handle;
    UINT8      cig_id;
    UINT8      cis_id;

    /* Initialize */
    value_1 = 0U;
    value_2 = 0U;
    marker = 0U;
    status = 0U;
    cis_conn_handle = 0U;
    acl_conn_handle = 0U;
    cig_id = 0U;
    cis_id = 0U;

    APPL_DBG("[APPL][GA][UCS]: >> appl_ga_ucs_hci_cb_handler\n");

    /* Switch on the Event Code */
    switch (event_code)
    {
    case HCI_LE_META_EVENT:
        hci_unpack_1_byte_param(&value_1, &event_data[marker]);
        marker++;
        switch (value_1)
        {
        case HCI_LE_CIS_ESTABLISHED_SUBEVENT:
            hci_unpack_1_byte_param(&status, &event_data[marker]);
            marker++;
            hci_unpack_2_byte_param(&cis_conn_handle, &event_data[marker]);
            marker += 2U;
            appl_ga_ucs_handle_cis_established_event
            (
                cis_conn_handle,
                status
            );
            break;

        case HCI_LE_CIS_REQUEST_SUBEVENT:
            hci_unpack_2_byte_param(&acl_conn_handle, &event_data[marker]);
            marker += 2U;
            hci_unpack_2_byte_param(&cis_conn_handle, &event_data[marker]);
            marker += 2U;
            hci_unpack_1_byte_param(&cig_id, &event_data[marker]);
            marker++;
            hci_unpack_1_byte_param(&cis_id, &event_data[marker]);
            marker++;
            appl_ga_ucs_handle_cis_request_event
            (
                acl_conn_handle,
                cis_conn_handle,
                cig_id,
                cis_id
            );
            break;

        default:
            break;
        }
        break;

    case HCI_COMMAND_COMPLETE_EVENT:
        /* Number of Command Packets */
        hci_unpack_1_byte_param(&value_1, &event_data[marker]);
        marker++;

        /* Command Opcode */
        hci_unpack_2_byte_param(&value_2, &event_data[marker]);
        marker += 2U;

        /* Command Status */
        hci_unpack_1_byte_param(&status, &event_data[marker]);
        marker++;

        /* Command Return Parameters */
        if (event_datalen > 4U)
        {
            switch (value_2)
            {
            case HCI_LE_SET_HOST_FEATURE_OPCODE:
                break;

            case HCI_LE_SETUP_ISO_DATA_PATH_OPCODE:
                hci_unpack_2_byte_param(&cis_conn_handle, &event_data[marker]);
                marker += 2U;
                appl_ga_ucs_handle_iso_data_path_event
                (
                    cis_conn_handle,
                    AUDIO_ISO_DATA_SETUP,
                    status
                );
                break;

            case HCI_LE_REMOVE_ISO_DATA_PATH_OPCODE:
                hci_unpack_2_byte_param(&cis_conn_handle, &event_data[marker]);
                marker += 2U;
                appl_ga_ucs_handle_iso_data_path_event
                (
                    cis_conn_handle,
                    AUDIO_ISO_DATA_REMOVE,
                    status
                );
                appl_ga_ucs_terminate_cis(cis_conn_handle);
                /*
                 * Using menu option to trigger Release Complete,
                 * enable this to automate.
                 */
                appl_ga_ucs_trigger_release_complete_using_cis_handle(cis_conn_handle);
                break;

            default:
                break;
            }
        }
        break;

    case HCI_DISCONNECTION_COMPLETE_EVENT:
        /* Status */
        hci_unpack_1_byte_param(&status, &event_data[marker]);
        marker++;
        /* Connection Handle - CIS or ACL */
        hci_unpack_2_byte_param(&value_2, &event_data[marker]);
        marker += 2U;

        appl_ga_ucs_handle_disconnection_event(status, value_2);
        break;

    default:
        break;
    }

    APPL_DBG("[APPL][GA][UCS]: << appl_ga_ucs_hci_cb_handler\n");
    return GA_SUCCESS;
}

void appl_ga_ucs_handle_cis_request_event
     (
         UINT16 acl_handle,
         UINT16 cis_handle,
         UINT8  cig_id,
         UINT8  cis_id
     )
{
    UINT8 index;
    UINT8 ase_count;
    UINT8 ase_index[MAX_UC_ASE];

    /* Initialize */
    index = 0U;
    ase_count = 0U;

    APPL_DBG("[APPL][GA][UCS]: >> appl_ga_ucs_handle_cis_request_event\n");
    /* Fetch all ASEs connected to this Device whose CIG and CIS ID matches */
    if (GA_SUCCESS == appl_ga_ucs_fetch_ase_index_from_acl_conn_handle_cig_id_cis_id
                      (
                          acl_handle,
                          cig_id,
                          cis_id,
                          &ase_count,
                          ase_index
                      ))
    {
        if (GA_SUCCESS == appl_ga_ucs_is_cis_connect_accept_allowed
                          (
                              ase_index,
                              ase_count
                          ))
        {
            if (GA_SUCCESS == appl_ga_ucs_accept_cis(cis_handle))
            {
                for (index = 0U; index < ase_count; index++)
                {
                    /*
                     * There can be multiple ASEs having same CIG ID and CIS ID for this
                     * device.
                     * If it is Bidirectional ASE, we will get fetch 2 ASEs.
                     */
                    ascs.ase[ase_index[index]].cig_cis_info.cis_state = CIS_STATE_WAITING;
                    ascs.ase[ase_index[index]].cig_cis_info.handle = cis_handle;
                }
            }
            else
            {
                /* No change in the state */
                APPL_DBG("[APPL][GA][UCS]: FAILED to accept CIS request !\n");
            }
        }
        else
        {
            if (GA_SUCCESS == appl_ga_ucs_reject_cis
                              (
                                  cis_handle,
                                  UCS_CIS_REJECT_REMOTE_USER_TERMINATED
                              ))
            {
                /* No change in the state */
                APPL_DBG("[APPL][GA][UCS]: CIS Rejected\n");
            }
            else
            {
                /* No change in the state */
                APPL_DBG("[APPL][GA][UCS]: FAILED to reject CIS request !\n");
            }
        }
    }
    APPL_DBG("[APPL][GA][UCS]: << appl_ga_ucs_handle_cis_request_event\n");
    return;
}

void appl_ga_ucs_handle_cis_established_event
     (
         UINT16 cis_conn_handle,
         UINT16 cis_conn_status
     )
{
    GA_RESULT  retval;
    UINT8      index;
    UINT8      ase_count;
    UINT8      ase_index[MAX_UC_ASE] = { 0U };

    ase_count = 0U;

    APPL_DBG("[APPL][GA][UCS]: >> appl_ga_ucs_handle_cis_established_event\n");

    /* Fetch ase_index, from cis conn handle */
    retval = appl_ga_ucs_get_ase_index_from_cis_conn_handle
             (
                 cis_conn_handle,
                 &ase_count,
                 ase_index
             );

    if (GA_SUCCESS == retval)
    {
        /* Update CIS State for each ASE and Setup ISO */
        for (index = 0U; index < ase_count; index++)
        {
            /* Update CIS conn state */
            appl_ga_ucs_update_cis_conn_state
            (
                ase_index[index],
                GA_TRUE,
                cis_conn_status
            );

            /*
             * If ISO Data Path was previously setup and CIS was terminated/Loss,
             * and if CIS is re-established as part of Enable procedure,
             * If Rx Start Ready is received even before CIS is established,
             * trigger Audio Transmission here.
             */
            if (AUDIO_ISO_SETUP_COMPLETE == ascs.ase[ase_index[index]].iso_state)
            {
                if ((GA_ROLE_SOURCE == ascs.ase[ase_index[index]].role) &&
                    (GA_ASE_STATE_STREAMING == ascs.ase[ase_index[index]].state))
                {
                    /* We are Audio Source, Start Transmitting Audio */
                    appl_ga_ucs_start_transmitting_audio
                    (
                        ascs.ase[ase_index[index]].cig_cis_info.handle,
                        ascs.ase[ase_index[index]].cs_conf,
                        ascs.ase[ase_index[index]].qos_conf_set_id,
                        AUDIO_NUM_OF_BITS_PER_SAMPLE
                    );
                }
            }
            else
            {
                /*
                 * Need not check the cis_conn_status, since
                 * appl_ga_ucs_update_cis_conn_state would have updated the
                 * cis_conn_status, which will get validated inside this
                 * function to proceed or not.
                 */
                appl_ga_ucs_setup_iso
                (
                    ase_index[index]
                );
            }
        }
    }
    APPL_DBG("[APPL][GA][UCS]: << appl_ga_ucs_handle_cis_established_event\n");
    return;
}

void appl_ga_ucs_handle_iso_data_path_event
     (
         UINT16 cis_conn_handle,
         UCHAR  state,
         UCHAR  status
     )
{
    UINT8      ase_index_list[MAX_UC_ASE] = { 0U };
    UINT8      ase_index;
    UINT8      ase_count;
    UINT8      index;

#ifndef APPL_GA_UCS_NO_AUTORXSTART_READY
    GA_ENDPOINT device;
    GA_RESULT retval;
#endif /* APPL_GA_UCS_NO_AUTORXSTART_READY */

    /* Initialize */
    ase_index = 0U;
    ase_count = 0U;
    index = 0U;

    APPL_DBG("[APPL][GA][UCS]: >> appl_ga_ucs_handle_iso_data_path_event\n");

    /* Fetch the ASE Index List based on the CIS Conn Handle */
    if (GA_SUCCESS == appl_ga_ucs_get_ase_index_from_cis_conn_handle
                      (
                          cis_conn_handle,
                          &ase_count,
                          ase_index_list
                      ))
    {
        for (index = 0U; index < ase_count; index++)
        {
            ase_index = ase_index_list[index];

            if ((AUDIO_ISO_DATA_SETUP == state)
                &&
                (AUDIO_ISO_UPDATE_IN_PROGRESS ==
                    ascs.ase[ase_index].iso_state))
            {
                if (GA_ROLE_SOURCE == ascs.ase[ase_index].role)
                {
                    if (GA_SUCCESS == appl_ga_utils_audio_src_update_entry
                                      (
                                          cis_conn_handle,
                                          AUDIO_ISO_DATA_SETUP,
                                          status,
                                          AUDIO_IGNORE_VALUE
                                      ))
                    {
                        APPL_TRC("[APPL][GA][UCS][%s]: ISO Data Path Setup Status: Complete\n", UC_GET_ROLE_STRING(ascs.ase[ase_index].role));
                        ascs.ase[ase_index].iso_state =
                            AUDIO_ISO_SETUP_COMPLETE;
                        /*
                         * Display ASE Streaming Info:
                         * Conn Device Index, ASE ID, ASE Role, ASE State,
                         * CIS Connection Handle, ASE Stream Symbol
                         */
                        GA_FORMAT_DISPLAY();
                        APPL_TRC("Local:\n");
                        /* TODO: Get the conn_dev_index from the device */
                        appl_ga_utils_bap_display_ase_data
                        (
                            ascs.ase[ase_index].conn_dev_index[0U],
                            ascs.ase[ase_index]
                        );
                        GA_FORMAT_DISPLAY();
                    }
                    else
                    {
                        APPL_ERR("[APPL][GA][UCS][%s]: ISO Data Path Setup Status: Update entry failed !\n", UC_GET_ROLE_STRING(ascs.ase[ase_index].role));
                    }
                }
                else
                {
                    if (GA_SUCCESS == appl_ga_utils_audio_snk_update_entry
                                      (
                                          cis_conn_handle,
                                          AUDIO_ISO_DATA_SETUP,
                                          status,
                                          AUDIO_IGNORE_VALUE
                                      ))
                    {
                        APPL_TRC("[APPL][GA][UCS][%s]: ISO Data Path Setup Status: Complete\n", UC_GET_ROLE_STRING(ascs.ase[ase_index].role));
                        /*
                         * Until ASE state of an ASE is moved to enabling,
                         * setup iso API will not get called and iso state of an ASE
                         * will not change.
                         */
                        ascs.ase[ase_index].iso_state =
                            AUDIO_ISO_SETUP_COMPLETE;
                        /*
                         * Display ASE Streaming Info:
                         * Conn Device Index, ASE ID, ASE Role, ASE State,
                         * CIS Connection Handle, ASE Stream Symbol
                         */
                        GA_FORMAT_DISPLAY();
                        APPL_TRC("Local:\n");
                        /* TODO: Get the conn_dev_index from the device */
                        appl_ga_utils_bap_display_ase_data
                        (
                            ascs.ase[ase_index].conn_dev_index[0U],
                            ascs.ase[ase_index]
                        );
                        GA_FORMAT_DISPLAY();

#ifndef APPL_GA_UCS_NO_AUTORXSTART_READY
                        /* TODO: Support for multiple device */
                        if (GA_SUCCESS == appl_ga_utils_get_conn_device
                                          (
                                              ascs.ase[ase_index].conn_dev_index[0U],
                                              &device
                                          ))
                        {
                            /*
                             * As per BAP Spec, Version: 1.0.1, Page: 94
                             * If the ASE is in the Enabling state, and if the device in the Audio Sink
                             * role for that ASE has not already set up its internal audio data path,
                             * the device in the Audio Sink role shall set up its internal audio data
                             * path as defined in Section 5.6.3.1 in preparation for reception of audio
                             * data. The device in the Audio Sink role shall then initiate the
                             * Receiver Start Ready operation as defined in Section 5.6.3.2.
                             */
                            if (AUDIO_ISO_SETUP_COMPLETE == ascs.ase[ase_index].iso_state)
                            {
                                ascs.ase_id_active_playback = ascs.ase[ase_index].id;

                                APPL_TRC("GA_notify_ase_receiver_start_ready\n");
                                retval = GA_notify_ase_receiver_start_ready
                                         (
                                             &device,
                                             1,
                                             &ascs.ase[ase_index].id
                                         );
                                APPL_TRC("Retval - ");
                                appl_ga_utils_display_ga_result(retval);

                                if (GA_SUCCESS == retval)
                                {
                                    /* Update the ASE State */
                                    ascs.ase[ase_index].state = GA_ASE_STATE_STREAMING;
                                    /* We are Audio Sink, Start Receiving Audio */
                                    appl_ga_ucs_start_receiving_audio
                                    (
                                        ascs.ase[ase_index].cig_cis_info.handle,
                                        ascs.ase[ase_index].cs_conf,
                                        AUDIO_NUM_OF_BITS_PER_SAMPLE
                                    );
                                }
                            }
                            else
                            {
                                /* Ideally this should never be hit */
                                APPL_ERR
                                (
                                    "Audio data path for ASE ID %d is not setup yet. Receiver Start Ready not allowed !\n",
                                    ascs.ase[ase_index].id
                                );
                            }
                        }
#endif /* APPL_GA_UCS_NO_AUTORXSTART_READY */
                    }
                    else
                    {
                        APPL_ERR("[APPL][GA][UCS][%s]: ISO Data Path Setup Status: Update entry failed !\n", UC_GET_ROLE_STRING(ascs.ase[ase_index].role));
                    }
                }
            }
            else if ((AUDIO_ISO_DATA_REMOVE == state)
                &&
                (AUDIO_ISO_UPDATE_IN_PROGRESS ==
                    ascs.ase[ase_index].iso_state))
            {
                if (GA_ROLE_SOURCE == ascs.ase[ase_index].role)
                {
                    if (GA_SUCCESS == appl_ga_utils_audio_src_update_entry
                                      (
                                          cis_conn_handle,
                                          AUDIO_ISO_DATA_REMOVE,
                                          status,
                                          AUDIO_IGNORE_VALUE
                                      ))
                    {
                        APPL_TRC("[APPL][GA][UCS][%s]: ISO Data Path Removal Status: Complete\n", UC_GET_ROLE_STRING(ascs.ase[ase_index].role));
                        ascs.ase[ase_index].iso_state = AUDIO_ISO_IDLE;
                    }
                    else
                    {
                        APPL_ERR("[APPL][GA][UCS][%s]: ISO Data Path Removal Status Update entry failed !\n", UC_GET_ROLE_STRING(ascs.ase[ase_index].role));
                    }
                }
                else
                {
                    if (GA_SUCCESS == appl_ga_utils_audio_snk_update_entry
                                      (
                                          cis_conn_handle,
                                          AUDIO_ISO_DATA_REMOVE,
                                          status,
                                          AUDIO_IGNORE_VALUE
                                      ))
                    {
                        APPL_TRC("[APPL][GA][UCS][%s]: ISO Data Path Removal Status: Complete\n", UC_GET_ROLE_STRING(ascs.ase[ase_index].role));
                        ascs.ase[ase_index].iso_state = AUDIO_ISO_IDLE;
                    }
                    else
                    {
                        APPL_ERR("[APPL][GA][UCS][%s]: ISO Data Path Removal Status Update entry failed !\n", UC_GET_ROLE_STRING(ascs.ase[ase_index].role));
                    }
                }
            }
        }
    }
    APPL_DBG("[APPL][GA][UCS]: << appl_ga_ucs_handle_iso_data_path_event\n");
    return;
}

void appl_ga_ucs_handle_disconnection_event
     (
         UINT16  conn_status,
         UINT16  conn_handle
     )
{
    UINT8        ase_count;
    UINT8        ase_index[MAX_UC_ASE];
    UINT8        ase_id[MAX_UC_ASE];
    UINT8        index;
    UINT8        conn_dev_index;
    GA_ENDPOINT  device;
    GA_RESULT    retval;

    ase_count = 0U;
    index = 0U;
    conn_dev_index = 0U;

    APPL_DBG("[APPL][GA][UCS]: >> appl_ga_ucs_handle_disconnection_event\n");

    if (GA_SUCCESS == conn_status)
    {
        /*
         * Validate if it's a cis_conn_handle.
         * For Valid cis_conn_handle, fetch all ase_index
         * with same cis_conn_handle.
         */
        if (GA_SUCCESS == appl_ga_ucs_get_ase_index_from_cis_conn_handle
                          (
                              conn_handle,
                              &ase_count,
                              ase_index
                          ))
        {
            /*
             * There can be more than 1 ASE that is connected to the same
             * Client device.
             */
            for (index = 0U; index < ase_count; index++)
            {
                /* Get the ASE ID from the ASE Index */
                ase_id[index] = ascs.ase[ase_index[index]].id;

                /* Update CIS conn state */
                appl_ga_ucs_update_cis_conn_state
                (
                    ase_index[index],
                    GA_FALSE,
                    conn_status
                );

                /*
                 * Since disconnection is already done, we need not do ISO
                 * Removal, So update the Audio PL and LC3 to stop, Also remove
                 * ISO entry.
                 */
                if (GA_ROLE_SOURCE == ascs.ase[ase_index[index]].role)
                {
                    appl_ga_ucs_stop_transmitting_audio
                    (
                        conn_handle,
                        ascs.ase[ase_index[index]].cs_conf,
                        ascs.ase[ase_index[index]].qos_conf_set_id,
                        AUDIO_NUM_OF_BITS_PER_SAMPLE
                    );

                    /*
                     * Ref: Core Spec, Version: 5.4, Page: 2163 (Disconnection Complete event)
                     * If Connection_Handle identifies a CIS on the Peripheral and
                     * Status is zero(Success), the handle and the associated data path of
                     * that CIS shall be deleted. If Connection_Handle identifies
                     * any other kind of connection and Status is zero(Success), the handle
                     * shall be deleted.
                     */
                    if (AUDIO_ISO_IDLE != ascs.ase[ase_index[index]].iso_state)
                    {
                        if (GA_SUCCESS == appl_ga_utils_audio_src_remove_entry
                                          (
                                              conn_handle
                                          ))
                        {
                            APPL_TRC("[APPL][GA][UCS][%s]: ISO Data Path Removal Status: Complete\n", UC_GET_ROLE_STRING(ascs.ase[ase_index[index]].role));
                            /* Update the ISO state */
                            ascs.ase[ase_index[index]].iso_state = AUDIO_ISO_IDLE;
                        }
                        else
                        {
                            APPL_ERR("[APPL][GA][UCS][%s]: ISO Data Path Removal Status: Remove entry failed !\n", UC_GET_ROLE_STRING(ascs.ase[ase_index[index]].role));
                        }
                    }
                }
                else
                {
                    if (ascs.ase_id_active_playback == ascs.ase[ase_index[index]].id)
                    {
                        /*
                         * We are Audio Sink, Stop receiving Audio only for the
                         * active playback ASE ID
                         */
                        appl_ga_ucs_stop_receiving_audio
                        (
                            conn_handle,
                            ascs.ase[ase_index[index]].cs_conf,
                            AUDIO_NUM_OF_BITS_PER_SAMPLE
                        );
                    }

                    /*
                     * Ref: Core Spec, Version: 5.4, Page: 2163 (Disconnection Complete event)
                     * If Connection_Handle identifies a CIS on the Peripheral and
                     * Status is zero(Success), the handle and the associated data path of
                     * that CIS shall be deleted. If Connection_Handle identifies
                     * any other kind of connection and Status is zero(Success), the handle
                     * shall be deleted.
                     */
                    if (AUDIO_ISO_IDLE != ascs.ase[ase_index[index]].iso_state)
                    {
                        if (GA_SUCCESS == appl_ga_utils_audio_snk_remove_entry
                                          (
                                              conn_handle
                                          ))
                        {
                            APPL_TRC("[APPL][GA][UCS][%s]: ISO Data Path Removal Status: Complete\n", UC_GET_ROLE_STRING(ascs.ase[ase_index[index]].role));
                            /* Update the ISO state */
                            ascs.ase[ase_index[index]].iso_state = AUDIO_ISO_IDLE;
                        }
                        else
                        {
                            APPL_ERR("[APPL][GA][UCS][%s]: ISO Data Path Removal Status: Remove entry failed !\n", UC_GET_ROLE_STRING(ascs.ase[ase_index[index]].role));
                        }
                    }
                }
            }
            /* Triggering Disable for a single device */
            /* TODO: Support for multiple device */
            if (GA_SUCCESS == appl_ga_utils_get_conn_device
                              (
                                  ascs.ase[ase_index[0U]].conn_dev_index[0U],
                                  &device
                              ))
            {
                if (GA_ASE_STATE_STREAMING == ascs.ase[ase_index[0U]].state)
                {
                    /*
                     * when the Unicast Server detects loss of a CIS for an ASE in the
                     * Streaming or the Disabling state, the Unicast Server transitions
                     * the ASE to the QoS Configured state
                     * BAP Spec, Version: 1.0.1, Page: 105, Section: 5.6.8
                     */
                    APPL_TRC("GA_notify_ase_suspend_on_CIS_loss\n");
                    retval = GA_notify_ase_suspend_on_CIS_loss
                             (
                                 &device,
                                 ase_count,
                                 &ase_id[0U]
                             );
                    APPL_TRC("Retval - ");
                    appl_ga_utils_display_ga_result(retval);
                }
                else if (GA_ASE_STATE_DISABLING == ascs.ase[ase_index[0U]].state)
                {
                    /*
                     * TODO: Add check later,
                     * This case is only for Local role as Source
                     */
                    appl_ga_utils_get_conn_device_in_use(NULL, &device, NULL);
                    /*
                     * when the Unicast Server detects loss of a CIS for an ASE in the
                     * Streaming or the Disabling state, the Unicast Server transitions
                     * the ASE to the QoS Configured state
                     * BAP Spec, Version: 1.0.1, Page: 105, Section: 5.6.8
                     */
                    APPL_TRC("GA_notify_ase_release_on_CIS_loss\n");
                    retval = GA_notify_ase_release_on_CIS_loss
                             (
                                 &device,
                                 ase_count,
                                 &ase_id[0U]
                             );
                    APPL_TRC("Retval - ");
                    appl_ga_utils_display_ga_result(retval);
                }
                else if (GA_ASE_STATE_RELEASING == ascs.ase[ase_index[0U]].state)
                {
                    appl_ga_ucs_trigger_release_complete_using_cis_handle(conn_handle);
                }
                else
                {
                    /* No action */
                }
            }
        }
        /*
         * It is not a CIS Handle.
         * Validate if it's a acl_conn_handle.
         * For Valid acl_conn_handle, fetch conn_dev_index and all ase_index
         * with same conn_dev_index.
         * More than one ASE can be connected to the same Client device.
         */
        else if (GA_SUCCESS == appl_ga_fetch_conn_dev_index_ase_index_from_acl_conn_handle
                               (
                                   conn_handle,
                                   &conn_dev_index,
                                   &ase_count,
                                   ase_index
                               ))
        {
            for (index = 0U; index < ase_count; index++)
            {
                /* Fetch device from conn_dev_index */
                appl_ga_utils_get_conn_device(conn_dev_index, &device);

                /* Get the ASE ID from the ASE Index */
                ase_id[index] = ascs.ase[ase_index[index]].id;

                /* Update conn_dev_index[] index for each ASE to Invalid */
                appl_ga_ucs_init_conn_dev_index
                (
                    conn_dev_index,
                    ase_index[index]
                );
            }

            /* For states where this should not be called like Releasing, this API will fail */
            APPL_TRC("GA_notify_ase_release\n");
            retval = GA_notify_ase_release
                     (
                         NULL,
                         ase_count,
                         &ase_id[0U]
                     );
            APPL_TRC("Retval - ");
            appl_ga_utils_display_ga_result(retval);

            /*
             * For states where this should not be called like state other than Releasing,
             * this API will fail.
             */
            /* Trigger Release Complete */
            APPL_TRC("GA_notify_release_complete\n");
            retval = GA_notify_release_complete
                     (
                         NULL,
                         ase_count,
                         &ase_id[0U]
                     );
            APPL_TRC("Retval - ");
            appl_ga_utils_display_ga_result(retval);

            /*
             * TODO: If we dont get CIS Disconnect and get ACL disconnect, Handle
             * appl_ga_ucs_stop_transmitting_audio or appl_ga_ucs_stop_receiving_audio
             * like above?
             */
        }
        else
        {
            APPL_DBG
            (
                "[APPL][GA][UCS]: No registered ASEs connected with "
                "this handle 0x%04x", conn_handle
            );
        }
    }
    APPL_DBG("[APPL][GA][UCS]: << appl_ga_ucs_handle_disconnection_event\n");
    return;
}

GA_RESULT appl_ga_ucs_cb_handler
          (
              GA_ENDPOINT * device,
              UINT8         ga_event,
              UINT16        ga_status,
              void        * ga_data,
              UINT16        ga_datalen
          )
{
    GA_RESULT      retval;
    GA_SEP_INFO  * info;
    GA_SEP_CONF  * sep;
    GA_QOS_CONF  * qos_conf;
    UINT8          ase_index;
    GA_METADATA  * meta;
    GA_LC3_CODEC_SPECIFIC_CONF csc;
    UINT32         locations;
    APPL_GA_UCS_ASE_RELEASE_COMPLETE_INFO ase_release_compl_info;

    /* Initialize */
    retval = GA_SUCCESS;

    /* MISRA C-2012 RULE 9.1 | Coverity UNINIT */
    GA_mem_set(&csc, 0, sizeof(GA_LC3_CODEC_SPECIFIC_CONF));
    GA_mem_set(&ase_release_compl_info, 0, sizeof(APPL_GA_UCS_ASE_RELEASE_COMPLETE_INFO));

    APPL_DBG("[APPL][GA][UCS]: >> appl_ga_ucs_cb_handler\n");

    if (NULL == device)
    {
        APPL_ERR("NULL Device Unexpected !\n");
        return GA_FAILURE;
    }

    GA_CB_ENTRY("Server");

    switch (ga_event)
    {
    case GA_SINK_SET_AUDIO_LOCATIONS_IND:
        appl_ga_ucs_pacs_display_common_event_info
        (
            device,
            ga_status
        );
        APPL_TRC
        (
            "[Event]       : GA_SINK_SET_AUDIO_LOCATIONS_IND (0x%02X)\n",
            ga_event
        );
        APPL_TRC("\n");
        appl_ga_utils_pacs_display_char_uuid(GA_CHAR_PACS_SINK_AUDIO_LOCATIONS);

        APPL_TRC("Data Length: 0x%02X\n", ga_datalen);
        APPL_TRC("Data:\n");
        if (sizeof(UINT32) == ga_datalen)
        {
            locations = *((UINT32*)ga_data);

            APPL_TRC("Len: 0x%02X,  Audio Locations: 0x%08X\n",
                ga_datalen, locations);
            appl_ga_utils_bap_display_audio_locations(locations);

            /* Update Local Record Info */
            appl_ga_utils_bap_fetch_update_local_pacs_audio_locations
            (
                GA_ROLE_SINK,
                locations
            );
        }
        break;

    case GA_SOURCE_SET_AUDIO_LOCATIONS_IND:
        appl_ga_ucs_pacs_display_common_event_info
        (
            device,
            ga_status
        );
        APPL_TRC
        (
            "[Event]       : GA_SOURCE_SET_AUDIO_LOCATIONS_IND (0x%02X)\n",
            ga_event
        );
        APPL_TRC("\n");
        appl_ga_utils_pacs_display_char_uuid(GA_CHAR_PACS_SOURCE_AUDIO_LOCATIONS);

        APPL_TRC("Data Length: 0x%02X\n", ga_datalen);
        APPL_TRC("Data:\n");
        if (sizeof(UINT32) == ga_datalen)
        {
            locations = *((UINT32*)ga_data);

            APPL_TRC("Len: 0x%02X,  Audio Locations: 0x%08X\n",
                ga_datalen, locations);
            appl_ga_utils_bap_display_audio_locations(locations);

            /* Update Local Record Info */
            appl_ga_utils_bap_fetch_update_local_pacs_audio_locations
            (
                GA_ROLE_SOURCE,
                locations
            );
        }
        break;

    case GA_SEP_CONFIGURE_IND:
        appl_ga_ucs_ascs_display_common_event_info
        (
            device,
            ga_status
        );
        APPL_TRC
        (
            "[Event]       : GA_SEP_CONFIGURE_IND (0x%02X)\n",
            ga_event
        );
        APPL_TRC("\n");
        appl_ga_utils_ascs_display_char_uuid(GA_CHAR_ASCS_ASE_CP);
        info = (GA_SEP_INFO*)ga_data;
        sep = (GA_SEP_CONF*)info->info;
        APPL_TRC("RECEIVED DATA\n");
        GA_FORMAT_DISPLAY();
        APPL_TRC("Data Length: 0x%02X\n", ga_datalen);
        APPL_TRC("Data:\n");

        APPL_TRC
        (
            "Len: 0x%02X,  ASE ID: 0x%02X\n",
            (UCHAR)sizeof(info->sep_id), info->sep_id
        );
        APPL_TRC
        (
            "Len: 0x%02X,  ",
            (UCHAR)sizeof(sep->role)
        );
        appl_ga_utils_bap_display_role(sep->role);
        APPL_TRC
        (
            "Len: 0x%02X,  Target_Latency: ",
            (UCHAR)sizeof(sep->target_latency)
        );
        appl_ga_utils_bap_display_target_latency(sep->target_latency);
        APPL_TRC
        (
            "Len: 0x%02X,  Target_PHY:",
            (UCHAR)sizeof(sep->target_phy)
        );
        appl_ga_utils_bap_display_target_phy(sep->target_phy);
        appl_ga_utils_bap_display_codec_id(sep->codec);
        APPL_TRC
        (
            "Len: 0x%02X,  Codec_Specific_Configuration_Length: %d\n",
            (UCHAR)sizeof(sep->role), sep->codec.ie_len
        );
        APPL_TRC
        (
            "Len: 0x%02X,  Codec_Specific_Configuration:\n",
            (UCHAR)sizeof(sep->codec.ie)
        );
        if (GA_AUDIO_CODING_LC3 == sep->codec.coding_format)
        {
            appl_ga_utils_bap_parse_and_display_codec_spec_conf_ltv
            (
                sep->codec.ie,
                sep->codec.ie_len,
                &csc
            );
            if (GA_ROLE_SOURCE == sep->role)
            {
                /*
                 * For ASE Role Source, UCC might not set
                 * Audio Channel Allocation value in csc conf during ASECP
                 * Config Codec operation.
                 * If ACA value is not set in csc conf, then get the value from
                 * Source PAC record.
                 */
                (GA_IGNORE_RETURN_VALUE)appl_ga_ucs_src_get_csc_conf_aca_from_pacs_sacc(&csc);
            }
            else if (GA_ROLE_SINK == sep->role)
            {
                /*
                 * For ASE Role Sink, UCC might not set
                 * Audio Channel Allocation value in csc conf during ASECP
                 * Config Codec operation.
                 * If ACA value is not set in csc conf, then get the value from
                 * Sink PAC record.
                 */
                (GA_IGNORE_RETURN_VALUE)appl_ga_ucs_snk_get_csc_conf_aca_from_pacs_sacc(&csc);
            }
        }
        else
        {
            /* TODO: Dump the Bytes as is since it is Vendor specific */
            appl_dump_bytes(sep->codec.ie, sep->codec.ie_len);
        }

        /* Fetch ASE Index from ASE ID */
        if (GA_FAILURE == appl_ga_ucs_get_ase_index_from_ase_id
                          (
                              info->sep_id,
                              &ase_index
                          ))
        {
            APPL_ERR("ASE ID not found !\n");
        }
        else
        {
            retval = appl_ga_ucs_validate_ase_cp
                     (
                         ase_index,
                         (void *)&csc,
                         GA_SEP_CONFIGURE_IND
                     );
            if (GA_SUCCESS == retval)
            {
                /* Update the ASE State */
                ascs.ase[ase_index].state = GA_ASE_STATE_CODEC_CONF;
                /* Update the conn_dev_index into array */
                appl_ga_ucs_update_conn_dev_index(*device, ase_index);
                /* Save the codec specific configuration setting for ASE */
                GA_mem_copy
                (
                    &ascs.ase[ase_index].cs_conf,
                    &csc,
                    sizeof(GA_LC3_CODEC_SPECIFIC_CONF)
                );
#ifdef APPL_GA_ALLOW_CODEC_CONF_CACHING
                GA_mem_copy
                (
                    ascs.ase[ase_index].codec,
                    &sep->codec,
                    sizeof(GA_CODEC_INFO)
                );
#endif /* APPL_GA_ALLOW_CODEC_CONF_CACHING */
            }
            else
            {
                APPL_TRC("Rejecting Config Codec !\n");
            }
        }
        break;

    case GA_SEP_SETUP_IND:
        appl_ga_ucs_ascs_display_common_event_info
        (
            device,
            ga_status
        );
        APPL_TRC
        (
            "[Event]       : GA_SEP_SETUP_IND (0x%02X)\n",
            ga_event
        );
        APPL_TRC("\n");
        appl_ga_utils_ascs_display_char_uuid(GA_CHAR_ASCS_ASE_CP);
        info = (GA_SEP_INFO*)ga_data;
        qos_conf = (GA_QOS_CONF*)info->info;
        APPL_TRC("RECEIVED DATA\n");
        GA_FORMAT_DISPLAY();
        APPL_TRC("Data Length: 0x%02X\n", ga_datalen);
        APPL_TRC("Data:\n");

        APPL_TRC
        (
            "Len: 0x%02X,  ASE ID: 0x%02X\n",
            (UCHAR)sizeof(info->sep_id), info->sep_id
        );
        APPL_TRC
        (
            "Len: 0x%02X,  CIG_ID - 0x%02X\n",
            (UCHAR)sizeof(qos_conf->channel.cig_id),
            qos_conf->channel.cig_id
        );
        APPL_TRC
        (
            "Len: 0x%02X,  CIS_ID - 0x%02X\n",
            (UCHAR)sizeof(qos_conf->channel.cis_id),
            qos_conf->channel.cis_id
        );
        APPL_TRC
        (
            "Len: 0x%02X,  SDU_Interval: %d(0x%08X)\n",
            (UCHAR)sizeof(qos_conf->sdu_interval),
            qos_conf->sdu_interval,
            qos_conf->sdu_interval
        );
        APPL_TRC
        (
            "Len: 0x%02X,  Framing: ",
            (UCHAR)sizeof(qos_conf->framing)
        );
        appl_ga_utils_bap_display_framing(qos_conf->framing);
        APPL_TRC
        (
            "Len: 0x%02X,  PHY:",
            (UCHAR)sizeof(qos_conf->phy)
        );
        appl_ga_utils_bap_display_pref_phy(qos_conf->phy);
        APPL_TRC
        (
            "Len: 0x%02X,  Max_SDU: %d(0x%04X)\n",
            (UCHAR)sizeof(qos_conf->max_sdu),
            qos_conf->max_sdu,
            qos_conf->max_sdu
        );
        APPL_TRC
        (
            "Len: 0x%02X,  Retransmission_Number: (%d)0x%02X\n",
            (UCHAR)sizeof(qos_conf->retxn),
            qos_conf->retxn,
            qos_conf->retxn
        );
        APPL_TRC
        (
            "Len: 0x%02X,  Max_Transport_Latency: %d(0x%04X)\n",
            (UCHAR)sizeof(qos_conf->max_transport_latency),
            qos_conf->max_transport_latency,
            qos_conf->max_transport_latency
        );
        APPL_TRC
        (
            "Len: 0x%02X,  Presentation_Delay: %d(0x%08X)\n",
            (UCHAR)sizeof(qos_conf->presentation_delay),
            qos_conf->presentation_delay,
            qos_conf->presentation_delay
        );

        /* Fetch ASE Index from ASE ID */
        if (GA_FAILURE == appl_ga_ucs_get_ase_index_from_ase_id
                          (
                              info->sep_id,
                              &ase_index
                          ))
        {
            APPL_ERR("ASE ID not found !\n");
        }
        else
        {
            retval = appl_ga_ucs_validate_ase_cp
                     (
                         ase_index,
                         (void *)qos_conf,
                         GA_SEP_SETUP_IND
                     );
            if (GA_SUCCESS == retval)
            {
                /* Update the QoS Parameters configured for this ASE */
                GA_mem_copy
                (
                    &ascs.ase[ase_index].qos_conf,
                    qos_conf,
                    sizeof(GA_QOS_CONF)
                );

                /*
                 * Fetch the Channel Count and based on that Divide by CC to get
                 * the value defined in BAP Spec which is per channel
                 */
                ascs.ase[ase_index].qos_conf.max_sdu /=
                    appl_ga_utils_fetch_sacc_from_aca(ascs.ase[ase_index].cs_conf.aca);

                /*
                 * TODO: Move above and below setting of max_sdu inside
                 * appl_ga_utils_fetch_qos_conf_set_id_from_qos_conf
                 */
                /* Update QOS Conf Set ID */
                ascs.ase[ase_index].qos_conf_set_id =
                    appl_ga_utils_fetch_qos_conf_set_id_from_qos_conf
                    (
                        ascs.ase[ase_index].qos_conf
                    );

                /*
                 * Fetch the Channel Count and based on that multiply by CC to get
                 * the total max_sdu value for CC
                 */
                ascs.ase[ase_index].qos_conf.max_sdu *=
                    appl_ga_utils_fetch_sacc_from_aca(ascs.ase[ase_index].cs_conf.aca);

                /* Update the ASE State */
                ascs.ase[ase_index].state = GA_ASE_STATE_QOS_CONF;
                ascs.ase[ase_index].cig_cis_info.cis_state = CIS_STATE_INITIALIZED;
            }
            else
            {
                APPL_TRC("Rejecting Config QOS !\n");
            }
        }
        break;

    case GA_SEP_START_IND:
        appl_ga_ucs_ascs_display_common_event_info
        (
            device,
            ga_status
        );
        APPL_TRC
        (
            "[Event]       : GA_SEP_START_IND (0x%02X)\n",
            ga_event
        );
        APPL_TRC("\n");
        appl_ga_utils_ascs_display_char_uuid(GA_CHAR_ASCS_ASE_CP);
        info = (GA_SEP_INFO*)ga_data;
        meta = (GA_METADATA*)info->info;
        APPL_TRC("RECEIVED DATA\n");
        GA_FORMAT_DISPLAY();
        APPL_TRC("Data Length: 0x%02X\n", ga_datalen);
        APPL_TRC("Data:\n");

        APPL_TRC
        (
            "Len: 0x%02X,  ASE ID: 0x%02X\n",
            (UCHAR)sizeof(info->sep_id), info->sep_id
        );
        APPL_TRC
        (
            "Len: 0x%02X,  Metadata_Length - 0x%02X\n",
            (UCHAR)sizeof(meta->length),
            meta->length
        );
        APPL_TRC("Len: 0x%02X,  Metadata -\n", meta->length);
        /*
         * Parse and display the Metadata_LTV
         */
        appl_ga_utils_bap_parse_and_display_metadata_ltv
        (
            meta->data,
            meta->length,
            NULL,
            NULL
        );
        /* Fetch ASE Index from ASE ID */
        if (GA_FAILURE == appl_ga_ucs_get_ase_index_from_ase_id
                          (
                              info->sep_id,
                              &ase_index
                          ))
        {
            APPL_ERR("ASE ID not found !\n");
        }
        else
        {
            retval = appl_ga_ucs_validate_ase_cp
                     (
                         ase_index,
                         (void *)meta,
                         GA_SEP_START_IND
                     );
            if (GA_SUCCESS == retval)
            {
                /* Update the ASE State */
                ascs.ase[ase_index].state = GA_ASE_STATE_ENABLING;
                /* State is in Enabling, Trigger ISO Setup Chain */
                appl_ga_ucs_setup_iso(ase_index);
            }
            else
            {
                APPL_TRC("Rejecting Enable !\n");
            }
        }
        break;

    case GA_SEP_RX_START_READY_IND:
        appl_ga_ucs_ascs_display_common_event_info
        (
            device,
            ga_status
        );
        APPL_TRC
        (
            "[Event]       : GA_SEP_RX_START_READY_IND (0x%02X)\n",
            ga_event
        );
        APPL_TRC("\n");
        appl_ga_utils_ascs_display_char_uuid(GA_CHAR_ASCS_ASE_CP);
        info = (GA_SEP_INFO*)ga_data;
        APPL_TRC("RECEIVED DATA\n");
        GA_FORMAT_DISPLAY();
        APPL_TRC("Data Length: 0x%02X\n", ga_datalen);
        APPL_TRC("Data:\n");

        APPL_TRC
        (
            "Len: 0x%02X,  ASE ID: 0x%02X\n",
            (UCHAR)sizeof(info->sep_id), info->sep_id
        );

        /* Fetch ASE Index from ASE ID */
        if (GA_FAILURE == appl_ga_ucs_get_ase_index_from_ase_id
                          (
                              info->sep_id,
                              &ase_index
                          ))
        {
            APPL_ERR("ASE ID not found !\n");
        }
        else
        {
            /* Update the ASE State */
            ascs.ase[ase_index].state = GA_ASE_STATE_STREAMING;
            if (GA_ROLE_SOURCE == ascs.ase[ase_index].role)
            {
                /* We are Audio Source, Start Transmitting Audio */
                appl_ga_ucs_start_transmitting_audio
                (
                    ascs.ase[ase_index].cig_cis_info.handle,
                    ascs.ase[ase_index].cs_conf,
                    ascs.ase[ase_index].qos_conf_set_id,
                    AUDIO_NUM_OF_BITS_PER_SAMPLE
                );
            }
            else
            {
                /*
                 * This shall never occur since Rx Start Ready is
                 * initiated on Sink ASE.
                 */
            }
        }
        break;

    case GA_SEP_RX_STOP_READY_IND:
        appl_ga_ucs_ascs_display_common_event_info
        (
            device,
            ga_status
        );
        APPL_TRC
        (
            "[Event]       : GA_SEP_RX_STOP_READY_IND (0x%02X)\n",
            ga_event
        );
        APPL_TRC("\n");
        appl_ga_utils_ascs_display_char_uuid(GA_CHAR_ASCS_ASE_CP);
        info = (GA_SEP_INFO*)ga_data;
        APPL_TRC("RECEIVED DATA\n");
        GA_FORMAT_DISPLAY();
        APPL_TRC("Data Length: 0x%02X\n", ga_datalen);
        APPL_TRC("Data:\n");

        APPL_TRC
        (
            "Len: 0x%02X,  ASE ID: 0x%02X\n",
            (UCHAR)sizeof(info->sep_id), info->sep_id
        );

        /* Fetch ASE Index from ASE ID */
        if (GA_FAILURE == appl_ga_ucs_get_ase_index_from_ase_id
                          (
                              info->sep_id,
                              &ase_index
                          ))
        {
            APPL_ERR("ASE ID not found !\n");
        }
        else
        {
            /* Update the ASE State */
            ascs.ase[ase_index].state = GA_ASE_STATE_QOS_CONF;
            if (GA_ROLE_SOURCE == ascs.ase[ase_index].role)
            {
                /* We are Audio Source, Stop transmitting Audio */
                appl_ga_ucs_stop_transmitting_audio
                (
                    ascs.ase[ase_index].cig_cis_info.handle,
                    ascs.ase[ase_index].cs_conf,
                    ascs.ase[ase_index].qos_conf_set_id,
                    AUDIO_NUM_OF_BITS_PER_SAMPLE
                );
            }
        }
        break;

    case GA_SEP_UPDATE_IND:
        appl_ga_ucs_ascs_display_common_event_info
        (
            device,
            ga_status
        );
        APPL_TRC
        (
            "[Event]       : GA_SEP_UPDATE_IND (0x%02X)\n",
            ga_event
        );
        APPL_TRC("\n");
        appl_ga_utils_ascs_display_char_uuid(GA_CHAR_ASCS_ASE_CP);
        info = (GA_SEP_INFO*)ga_data;
        meta = (GA_METADATA*)info->info;
        APPL_TRC("RECEIVED DATA\n");
        GA_FORMAT_DISPLAY();
        APPL_TRC("Data Length: 0x%02X\n", ga_datalen);
        APPL_TRC("Data:\n");
        APPL_TRC
        (
            "Len: 0x%02X,  ASE ID: 0x%02X\n",
            (UCHAR)sizeof(info->sep_id), info->sep_id
        );
        APPL_TRC
        (
            "Len: 0x%02X,  Metadata_Length - 0x%02X\n",
            (UCHAR)sizeof(meta->length),
            meta->length
        );
        APPL_TRC("Len: 0x%02X,  Metadata -\n", meta->length);
        /* Parse and display the Metadata_LTV. */
        appl_ga_utils_bap_parse_and_display_metadata_ltv
        (
            meta->data,
            meta->length,
            NULL,
            NULL
        );
        /* Fetch ASE Index from ASE ID */
        if (GA_FAILURE == appl_ga_ucs_get_ase_index_from_ase_id
                          (
                              info->sep_id,
                              &ase_index
                          ))
        {
            APPL_ERR("ASE ID not found !\n");
        }
        else
        {
            retval = appl_ga_ucs_validate_ase_cp
                     (
                         ase_index,
                         (void *)meta,
                         GA_SEP_UPDATE_IND
                     );
            if (GA_SUCCESS != retval)
            {
                APPL_TRC("Rejecting Update Metadata !\n");
            }
        }
        break;

    case GA_SEP_SUSPEND_IND:
        appl_ga_ucs_ascs_display_common_event_info
        (
            device,
            ga_status
        );
        APPL_TRC
        (
            "[Event]       : GA_SEP_SUSPEND_IND (0x%02X)\n",
            ga_event
        );
        APPL_TRC("\n");
        appl_ga_utils_ascs_display_char_uuid(GA_CHAR_ASCS_ASE_CP);
        info = (GA_SEP_INFO*)ga_data;
        APPL_TRC("RECEIVED DATA\n");
        GA_FORMAT_DISPLAY();
        APPL_TRC("Data Length: 0x%02X\n", ga_datalen);
        APPL_TRC("Data:\n");

        APPL_TRC
        (
            "Len: 0x%02X,  ASE ID: 0x%02X\n",
            (UCHAR)sizeof(info->sep_id), info->sep_id
        );

        /* Fetch ASE Index from ASE ID */
        if (GA_FAILURE == appl_ga_ucs_get_ase_index_from_ase_id
                          (
                              info->sep_id,
                              &ase_index
                          ))
        {
            APPL_ERR("ASE ID not found !\n");
        }
        else
        {
            if (GA_ROLE_SOURCE == ascs.ase[ase_index].role)
            {
                /* Update the ASE State */
                ascs.ase[ase_index].state = GA_ASE_STATE_DISABLING;
                /*
                 * Wait to receive Receiver Stop Ready Operation and handle
                 * the Stop in the GA_SEP_RX_STOP_READY_IND event.
                 *
                 * As per BAP Spec: BAP_v1.0.1: Page 99
                 * 5.6.5.1 Receiver Stop Ready
                 * The Unicast Client is ready to stop consuming audio data
                 * transmitted for that ASE by the Unicast Server.
                 * The Unicast Server in the Audio Source role should not
                 * stop transmitting audio data for a Source ASE in the
                 * Disabling state until the Unicast Server transitions the
                 * ASE to the QoS Configured state.
                 */
            }
            else
            {
                /* Update the ASE State */
                ascs.ase[ase_index].state = GA_ASE_STATE_QOS_CONF;
                if (ascs.ase_id_active_playback == ascs.ase[ase_index].id)
                {
                    /*
                     * We are Audio Sink, Stop receiving Audio only for the
                     * active playback ASE ID
                     */
                    appl_ga_ucs_stop_receiving_audio
                    (
                        ascs.ase[ase_index].cig_cis_info.handle,
                        ascs.ase[ase_index].cs_conf,
                        AUDIO_NUM_OF_BITS_PER_SAMPLE
                    );
                }
            }
        }
        break;

    case GA_SEP_RELEASE_IND:
        appl_ga_ucs_ascs_display_common_event_info
        (
            device,
            ga_status
        );
        APPL_TRC
        (
            "[Event]       : GA_SEP_RELEASE_IND (0x%02X)\n",
            ga_event
        );
        APPL_TRC("\n");
        appl_ga_utils_ascs_display_char_uuid(GA_CHAR_ASCS_ASE_CP);
        info = (GA_SEP_INFO*)ga_data;
        APPL_TRC("RECEIVED DATA\n");
        GA_FORMAT_DISPLAY();
        APPL_TRC("Data Length: 0x%02X\n", ga_datalen);
        APPL_TRC("Data:\n");

        APPL_TRC
        (
            "Len: 0x%02X,  ASE ID: 0x%02X\n",
            (UCHAR)sizeof(info->sep_id), info->sep_id
        );

        /* Fetch ASE Index from ASE ID */
        if (GA_FAILURE == appl_ga_ucs_get_ase_index_from_ase_id
                          (
                              info->sep_id,
                              &ase_index
                          ))
        {
            APPL_ERR("ASE ID not found !\n");
        }
        else
        {
            /* Update the ASE State */
            ascs.ase[ase_index].state = GA_ASE_STATE_RELEASING;

            /*
             * If the Unicast Client initiates the Release operation for
             * an ASE, the Unicast Client and Unicast Server should remove any
             * internal audio data paths that have been set up for the ASE
             * as defined in Section 5.6.6.1
             */
            /*
             * TODO: On receiving Release, Client will trigger CIS
             * Disconnection and as a peripheral device ISO data path
             * will be removed by controller on CIS disconnect. So, is it
             * required to trigger ISO data path removal here?
             */
            if (GA_FAILURE == appl_ga_ucs_remove_iso
                              (
                                  ase_index,
                                  ascs.ase[ase_index].cig_cis_info.handle
                              ))
            {
                /*
                 * Exception case: Previously, ASE state is GA_ASE_STATE_QOS_CONF,
                 * no ISO Data Path has been setup. In this case if Client triggers
                 * Release CP operation, then the API will return GA_FAILURE
                 * which is the expected behaviour(ISO is not setup).
                 */

                /*
                 * If there is no CIS established, Release is triggered
                 * from remote, Perform Release complete.
                 */
                if ((CIS_STATE_IDLE == ascs.ase[ase_index].cig_cis_info.cis_state) ||
                    (CIS_STATE_INITIALIZED == ascs.ase[ase_index].cig_cis_info.cis_state))
                {
                    GA_COPY_ENDPOINT
                    (
                        &ase_release_compl_info.device,
                        device
                    );
                    ase_release_compl_info.ase_count = 1U;
                    GA_mem_copy
                    (
                        ase_release_compl_info.ase_index,
                        &ase_index,
                        ase_release_compl_info.ase_count
                    );
                    /*
                     * As ASE State in core will get updated to Releasing after
                     *  the callback returns, trigger Release Complete post the timer.
                     */
                    if (BT_TIMER_HANDLE_INIT_VAL ==
                        appl_ga_ucs_trigger_release_complete_timer_handle)
                    {
                        BT_start_timer
                        (
                            &appl_ga_ucs_trigger_release_complete_timer_handle,
                            2U,
                            appl_ga_ucs_trigger_release_complete_timer_handler,
                            &ase_release_compl_info,
                            sizeof(APPL_GA_UCS_ASE_RELEASE_COMPLETE_INFO)
                        );
                    }
                }
            }
            if (GA_ROLE_SOURCE == ascs.ase[ase_index].role)
            {
                /* We are Audio Source, Stop transmitting Audio */
                appl_ga_ucs_stop_transmitting_audio
                (
                    ascs.ase[ase_index].cig_cis_info.handle,
                    ascs.ase[ase_index].cs_conf,
                    ascs.ase[ase_index].qos_conf_set_id,
                    AUDIO_NUM_OF_BITS_PER_SAMPLE
                );
            }
            else
            {
                if (ascs.ase_id_active_playback == ascs.ase[ase_index].id)
                {
                    /*
                     * We are Audio Sink, Stop receiving Audio only for the
                     * active playback ASE ID
                     */
                    appl_ga_ucs_stop_receiving_audio
                    (
                        ascs.ase[ase_index].cig_cis_info.handle,
                        ascs.ase[ase_index].cs_conf,
                        AUDIO_NUM_OF_BITS_PER_SAMPLE
                    );
                }
            }
        }
        break;

    default:
        break;
    }

    GA_CB_EXIT();

    APPL_DBG("[APPL][GA][UCS]: << appl_ga_ucs_cb_handler\n");
    return retval;
}

void appl_ga_ucs_pacs_display_common_event_info
     (
        GA_ENDPOINT * device,
        UINT16        ga_status
     )
{
    APPL_DBG("[APPL][GA][UCS]: >> appl_ga_ucs_pacs_display_common_event_info\n");

    APPL_TRC("[Profile]     : PACS (0x%04X)\n", GA_SERVICE_PACS);
    APPL_TRC("[SECTION]     : PACS SERVER EVENTS\n");
    APPL_TRC("[SUB-SECTION] : PACS SERVER-WRITE\n");
    APPL_TRC("[TYPE]        : WRITE REQUEST\n");
    appl_ga_utils_display_bdaddr_and_type(device);
    APPL_TRC("[Event Status]: ");
    appl_ga_utils_display_ga_result(ga_status);

    APPL_DBG("[APPL][GA][UCS]: << appl_ga_ucs_pacs_display_common_event_info\n");
    return;
}

void appl_ga_ucs_ascs_display_common_event_info
     (
        GA_ENDPOINT * device,
        UINT16        ga_status
     )
{
    APPL_DBG("[APPL][GA][UCS]: >> appl_ga_ucs_ascs_display_common_event_info\n");

    APPL_TRC("[Profile]     : ASCS (0x%04X)\n", GA_SERVICE_ASCS);
    APPL_TRC("[SECTION]     : ASCS SERVER EVENTS\n");
    APPL_TRC("[SUB-SECTION] : ASCS SERVER-WRITE\n");
    APPL_TRC("[TYPE]        : WRITE REQUEST\n");
    appl_ga_utils_display_bdaddr_and_type(device);
    APPL_TRC("[Event Status]: ");
    appl_ga_utils_display_ga_result(ga_status);

    APPL_DBG("[APPL][GA][UCS]: << appl_ga_ucs_ascs_display_common_event_info\n");
    return;
}

void appl_ga_ucs_init(void)
{
    UINT8  ase_index;
    UINT8 j;

    ase_index = 0U;
    j = 0U;

    APPL_DBG("[APPL][GA][UCS]: >> appl_ga_ucs_init\n");

    /*
     * TODO: Handle
     * Init for the first time. If caching is enabled, then it has to be
     * processed only once.
     */
    appl_ga_ucs_init_unicast_server_info();
    /* Initialize all fields to 0U */
    GA_mem_set
    (
        &ascs,
        0U,
        (sizeof(ASCS_ASE_INFO))
    );
    for (ase_index = 0U; ase_index < MAX_UC_ASE; ase_index++)
    {
        /*
         * Initialize the CIG, CIS, ISO, ASE state,
         * CIS ID and CIS conn_handle
         */
        ascs.ase[ase_index].qos_conf.channel.cig_id =
            INVALID_CIG_CIS_ID;
        ascs.ase[ase_index].qos_conf.channel.cis_id =
            INVALID_CIG_CIS_ID;
        ascs.ase[ase_index].cig_cis_info.cig_state =
            CIG_STATE_IDLE;
        ascs.ase[ase_index].cig_cis_info.cis_state =
            CIS_STATE_IDLE;
        ascs.ase[ase_index].cig_cis_info.handle =
            INVALID_CONN_HANDLE;
        ascs.ase[ase_index].iso_state =
            AUDIO_ISO_IDLE;
        ascs.ase[ase_index].state =
            GA_ASE_STATE_IDLE;
        /*
         * Initialize conn_dev_index. After mem_set all will set to 0.
         * Initialize then to INVALID_CONN_DEV_INDEX.
         */
        for (j = 0U; j < MAX_UCS_SIMULTANEOUS_ASE; j++)
        {
            ascs.ase[ase_index].conn_dev_index[j] = INVALID_CONN_DEV_INDEX;
        }
    }

    appl_ga_ucs_trigger_release_complete_timer_handle = BT_TIMER_HANDLE_INIT_VAL;

    APPL_DBG("[APPL][GA][UCS]: << appl_ga_ucs_init\n");
    return;
}

void appl_ga_ucs_init_conn_dev_index
     (
         UINT8 conn_dev_index,
         UINT8 ase_index
     )
{
    UINT8 index;

    /* Initialize */
    index = 0U;

    APPL_DBG("[APPL][GA][UCS]: >> appl_ga_ucs_init_conn_dev_index\n");

    for (index = 0U; index < MAX_UCS_SIMULTANEOUS_ASE; index++)
    {
        if (conn_dev_index == ascs.ase[ase_index].conn_dev_index[index])
        {
            ascs.ase[ase_index].conn_dev_index[index] = INVALID_CONN_DEV_INDEX;
            break;
        }
    }
    APPL_DBG("[APPL][GA][UCS]: << appl_ga_ucs_init_conn_dev_index\n");
    return;
}

GA_RESULT appl_ga_ucs_init_unicast_server_info(void)
{
    APPL_DBG("[APPL][GA][UCS]: >> appl_ga_ucs_init_unicast_server_info\n");

    APPL_DBG("[APPL][GA][UCS]: << appl_ga_ucs_init_unicast_server_info\n");

    /* If APPL_GA_ALLOW_CODEC_CONF_CACHING is enabled, Do not reset. */
    return GA_SUCCESS;
}

void main_ucs_operations(void)
{
    int choice;
    UINT8 menu_choice;

    menu_choice = 0U;

    APPL_DBG("[APPL][GA][UCS]: >> main_ucs_operations\n");

    GA_LOOP_FOREVER()
    {
        printf("\n");
        printf("%s", ucs_menu_options);
        CONSOLE_IN("%d", &choice);
        menu_choice = (UINT8)choice;

        switch(menu_choice)
        {
            case 0:
                break;

            case 1:
                break;

            case 2:
                appl_ga_ucs_register_ascs(APPL_GA_ROLE_NONE);
                break;

            case 3:
                break;

            case 4:
                break;

            case 5:
                appl_ga_ucs_auto_codec_config();
                break;

            case 6:
                appl_ga_ucs_auto_rx_start_ready();
                break;

            case 7:
                appl_ga_ucs_auto_update_metadata();
                break;

            case 8:
                appl_ga_ucs_auto_disable();
                break;

            case 9:
                appl_ga_ucs_auto_release();
                break;

            case 10:
                appl_ga_ucs_release_complete();
                break;

            case 15:
                appl_ga_ucs_ase_disconnect_cis();
                break;

            case 20:
                appl_ga_ucs_display_ase_data_for_a_conn_dev();
                break;

            case 21:
                appl_ga_ucs_display_all_ase_data();
                break;

            case 22:
                appl_ga_utils_display_all_conn_device();
                break;

            default:
                APPL_TRC("Invalid Choice\n");
        }
        if (0U == menu_choice)
        {
            /* return */
            break;
        }
    }

    APPL_DBG("[APPL][GA][UCS]: << main_ucs_operations\n");
    return;
}

GA_RESULT appl_ga_ucs_register_ascs(APPL_GA_ROLE role)
{
    GA_RESULT   retval;
    UINT8       index;
    UINT8       ase_count;

    /* Intitialize */
    retval = GA_FAILURE;
    ase_count = 0U;
    index = 0U;

    APPL_DBG("[APPL][GA][UCS]: >> appl_ga_ucs_register_ascs\n");

#ifndef APPL_GA_USE_CONFIG_FILE_FOR_INPUT
    if (APPL_GA_TMAP_ROLE_UMR == (APPL_GA_TMAP_ROLE_UMR & role))
    {
        /* TMAP Role: UMR 1 ASE Sink M */
        /* Fetch the Number of ASE */
    }
    else if (APPL_GA_TMAP_ROLE_CT == (APPL_GA_TMAP_ROLE_CT & role))
    {
        /*
         * TMAP Role: CT
         * A CT device that supports the BAP Audio Sink role shall include at least
         * one Sink Audio Stream Endpoint (ASE) characteristic as defined in ASCS.
         * A CT device that supports the BAP Audio Source role shall include at
         * least one Source ASE characteristic. A CT capable of bidirectional audio
         * shall include at least one Sink ASE characteristic and one Source ASE
         * characteristic.
         */
        /* Fetch the Number of ASE */
    }
    else if (APPL_GA_HAP_ROLE_HA == (APPL_GA_HAP_ROLE_HA & role))
    {
        /* Fetch the Number of ASE */
    }
    else
    {
        /* Fetch the Number of ASE */
    }
    /* Fetch the Number of ASE */
    ase_count = appl_ga_utils_bap_get_ase_count();
#else /* APPL_GA_USE_CONFIG_FILE_FOR_INPUT */
    ase_count = appl_ga_ucs_ascs_get_ase_count_using_default_values(role);
#endif /* APPL_GA_USE_CONFIG_FILE_FOR_INPUT */
    for (index = 0U; index < ase_count; index++)
    {
#ifdef APPL_GA_USE_CONFIG_FILE_FOR_INPUT
        retval = appl_ga_ucs_register_ascs_using_default_values
                 (
                     role,
                     &ascs.ase[ascs.ase_count]
                 );
#else /* APPL_GA_USE_CONFIG_FILE_FOR_INPUT */
        retval = appl_ga_ucs_register_ascs_using_runtime_values
                 (
                     role,
                     &ascs.ase[ascs.ase_count]
                 );
#endif
        if (GA_SUCCESS != retval)
        {
            APPL_DBG
            (
                "[APPL][GA][UCS]: Failed to register ASCS, 0x%04X !",
                retval
            );
            GA_mem_set(&ascs.ase[ascs.ase_count], 0x00, sizeof(ASE));
        }
        else
        {
            ascs.ase_count++;
        }
    }

    APPL_DBG("[APPL][GA][UCS]: << appl_ga_ucs_register_ascs\n");

    return retval;
}

#ifndef APPL_GA_USE_CONFIG_FILE_FOR_INPUT
GA_RESULT appl_ga_ucs_register_ascs_using_runtime_values
          (
              /* IN */  APPL_GA_ROLE   role,
              /* OUT */ ASE          * ase
          )
{
    GA_RESULT  retval;
    int        choice;
    UINT8      index;
    UINT8      ase_count;

    /* ASCS: Sink ASE/Source ASE */
    UINT8                       csc_set_id;
    GA_LC3_CODEC_SPECIFIC_CONF  csc = { 0 };

    /* Initialize */
    retval = GA_FAILURE;
    choice = 0;
    index = 0U;
    ase_count = 0U;
    csc_set_id = 0U;

    APPL_DBG("[APPL][GA][UCS]: >> appl_ga_ucs_register_ascs_using_runtime_values\n");

    if (APPL_GA_TMAP_ROLE_UMR == (APPL_GA_TMAP_ROLE_UMR & role))
    {
        ase->role = GA_ROLE_SINK;
    }
    else if (APPL_GA_TMAP_ROLE_CT == (APPL_GA_TMAP_ROLE_CT & role))
    {
        /* Input the Role for the ASE */
        ase->role = appl_ga_utils_bap_get_role();
    }
    else if (APPL_GA_HAP_ROLE_HA == (APPL_GA_HAP_ROLE_HA & role))
    {
        /* Input the Role for the ASE */
        ase->role = appl_ga_utils_bap_get_role();
    }
    else
    {
        /* Input the Role for the ASE */
        ase->role = appl_ga_utils_bap_get_role();
    }

    /* Display the PACS Records registered */
    appl_ga_utils_bap_display_local_pacs();

    CONSOLE_OUT("Do you want to use MAX values for QOS Capability?\n1. Yes\n2. No\n");
    CONSOLE_IN("%d", &choice);

    if (1U == (UINT8)choice)
    {
        /* Set QOS Capability to Max values */
        ase->qos_cap.pref_phy = GA_PREF_PHY_LE_2M_PHY;
        ase->qos_cap.pref_presentation_delay_min = GA_PRESENTATION_DELAY_NO_PREF;
        ase->qos_cap.pref_presentation_delay_max = GA_PRESENTATION_DELAY_NO_PREF;
        ase->qos_cap.pref_framing = GA_FRAMING_UNFRAMED;
        ase->qos_cap.pref_max_transport_latency = 100;
        ase->qos_cap.pref_retxn = 13;
        ase->qos_cap.supp_presentation_delay_min = 40000;
        ase->qos_cap.supp_presentation_delay_max = 40000;

        retval = GA_SUCCESS;
    }
    else if (2U == (UINT8)choice)
    {
        /* Fetch the Set ID based on the PACS Records registered */
        csc_set_id = appl_ga_utils_bap_uc_get_qos_cs_cap_set_id();

        /* Set the QoS Capability based on the Set ID */
        retval = appl_ga_utils_bap_uc_prepare_csc_and_qos_cap_based_on_set_id
                 (
                     csc_set_id, &csc, &ase->qos_cap, NULL
                 );
    }
    else
    {
        /* DO Nothing */
    }

    if (GA_SUCCESS == retval)
    {
        /*
         * Skip other fields, We are interested only in the QoS
         * Capability.
         * For now, we just add ASE preference in the QoS Capability.
         */
        APPL_TRC("GA_register_audio_sep: \n");
        retval = GA_register_audio_sep
                 (
                     ase->role,
                     NULL,
                     &ase->qos_cap,
                     &ase->id
                 );
        APPL_TRC("Retval - ");
        appl_ga_utils_display_ga_result(retval);
    }

    APPL_DBG("[APPL][GA][UCS]: << appl_ga_ucs_register_ascs_using_runtime_values\n");

    return retval;
}
#else /* APPL_GA_USE_CONFIG_FILE_FOR_INPUT */
UINT8 appl_ga_ucs_ascs_get_ase_count_using_default_values(APPL_GA_ROLE role)
{
    UINT8  ase_count;

    APPL_DBG("[APPL][GA][UCS]: >> appl_ga_ucs_ascs_get_ase_count_using_default_values\n");

    /* Set ASE count */
    if (APPL_GA_TMAP_ROLE_UMR == (APPL_GA_TMAP_ROLE_UMR & role))
    {
        /* TMAP Role: UMR 1 ASE Sink M, Using 2 for now can be 1 */
        ase_count = 2U;
    }
    else if (APPL_GA_TMAP_ROLE_CT == (APPL_GA_TMAP_ROLE_CT & role))
    {
        /*
         * TMAP Role: CT
         * A CT device that supports the BAP Audio Sink role shall include at least
         * one Sink Audio Stream Endpoint (ASE) characteristic as defined in ASCS.
         * A CT device that supports the BAP Audio Source role shall include at
         * least one Source ASE characteristic. A CT capable of bidirectional audio
         * shall include at least one Sink ASE characteristic and one Source ASE
         * characteristic.
         */
        ase_count = 2U;
    }
    else if (APPL_GA_HAP_ROLE_HA == (APPL_GA_HAP_ROLE_HA & role))
    {
        ase_count = 1U;
    }
    else
    {
        ase_count = 1U;
    }

    APPL_DBG("[APPL][GA][UCS]: << appl_ga_ucs_ascs_get_ase_count_using_default_values\n");

    return ase_count;
}

GA_RESULT appl_ga_ucs_register_ascs_using_default_values
          (
              /* IN */  APPL_GA_ROLE   role,
              /* OUT */ ASE          * ase
          )
{
    GA_RESULT  retval;

    /* ASCS: Sink ASE/Source ASE */
    UINT8                       csc_set_id;
    GA_LC3_CODEC_SPECIFIC_CONF  cs_conf = { 0 };

    /* Initialize */
    retval = GA_FAILURE;
    csc_set_id = 0U;

    APPL_DBG("[APPL][GA][UCS]: >> appl_ga_ucs_register_ascs_using_default_values\n");

    if (APPL_GA_TMAP_ROLE_UMR == (APPL_GA_TMAP_ROLE_UMR & role))
    {
        /* As per Spec, Sink is M */
        ase->role = GA_ROLE_SINK;
    }
    else if (APPL_GA_TMAP_ROLE_CT == (APPL_GA_TMAP_ROLE_CT & role))
    {
        /* Input the Role for the ASE, As per Spec shall support atleast Src/Sink */
        ase->role = appl_ga_utils_bap_get_role();
    }
    else if (APPL_GA_HAP_ROLE_HA == (APPL_GA_HAP_ROLE_HA & role))
    {
        /* Input the Role for the ASE, As per Spec shall support Sink, may support Source */
        ase->role = appl_ga_utils_bap_get_role();
    }
    else
    {
#if 0
        /* TBD: Updated in UPF-67 for Auto Source Endpoint. Check */
        ase->role = GA_ROLE_SOURCE;
#else /* 0 */
        /* Input the Role for the ASE */
        ase->role = appl_ga_utils_bap_get_role();
#endif /* 0 */
    }

    /* Display the PACS Records registered */
    appl_ga_utils_bap_display_local_pacs();

    if (APPL_GA_TMAP_ROLE_UMR ==
        (APPL_GA_TMAP_ROLE_UMR & role))
    {
        /* Set the Set ID based on the PACS Records registered */
        /*
         * TMAP_ROLE: UMR
         * Shall choose one of the below:
         *
         * 4:  16_2_1
         * 20: 16_2_2
         * 6:  24_2_1
         * 22: 24_2_2
         *
         * 11: 48_1_1
         * 27: 48_1_2
         * 12: 48_2_1
         * 28: 48_2_2
         * 13: 48_3_1
         * 29: 48_3_2
         * 14: 48_4_1
         * 30: 48_4_2
         * 15: 48_5_1
         * 31: 48_5_2
         * 16: 48_6_1
         * 32: 48_6_2
         *
         */

        /*
         * For now, 16_2_2 is selected,
         * Refer appl_ga_utils_bap_uc_get_qos_cs_cap_set_id()
         */
        csc_set_id = 12U;
    }
    if (APPL_GA_TMAP_ROLE_CT ==
        (APPL_GA_TMAP_ROLE_CT & role))
    {
        /* Set the Set ID based on the PACS Records registered */
        /*
         * TMAP_ROLE: CT
         * Shall choose one of the below:
         *
         * 3:  16_1_1
         * 4:  16_2_1
         * 19: 16_1_2
         * 20: 16_2_2
         * 7:  32_1_1
         * 8:  32_2_1
         * 23: 32_1_2
         * 24: 32_2_2
         *
         */

        /*
         * For now, 32_2_1 is selected,
         * Refer appl_ga_utils_bap_uc_get_qos_cs_cap_set_id()
         */
        csc_set_id = 8U;
    }
    if (APPL_GA_HAP_ROLE_HA ==
        (APPL_GA_HAP_ROLE_HA & role))
    {
        /* Set the Set ID based on the PACS Records registered */
        /*
         * HAP_ROLE: HA
         * Shall choose one of the below:
         *
         * 4:  16_2_1
         * 20: 16_2_2
         * 6:  24_2_1
         * 22: 24_2_2
         *
         */

        /*
         * For now, 16_2_2 is selected,
         * Refer appl_ga_utils_bap_uc_get_qos_cs_cap_set_id()
         */
        csc_set_id = 20U;
    }
    else
    {
        /*
         * For now, 48_2_2 is selected,
         * Refer appl_ga_utils_bap_uc_get_qos_cs_cap_set_id()
         */
        csc_set_id = 28U;
    }

    /* Set the QoS Capability based on the Set ID */
    if (GA_SUCCESS ==
        appl_ga_utils_bap_uc_prepare_csc_and_qos_cap_based_on_set_id
        (
            csc_set_id, &cs_conf, &ase->qos_cap, NULL
        ))
    {
        /*
         * Skip other fields, We are interested only in the QoS
         * Capability.
         * For now, we just add ASE preference in the QoS Capability.
         */
        APPL_TRC("GA_register_audio_sep: \n");
        retval = GA_register_audio_sep
                 (
                     ase->role,
                     NULL,
                     &ase->qos_cap,
                     &ase->id
                 );
        APPL_TRC("Retval - ");
        appl_ga_utils_display_ga_result(retval);
    }

    APPL_DBG("[APPL][GA][UCS]: << appl_ga_ucs_register_ascs_using_default_values\n");

    return retval;
}
#endif /* APPL_GA_USE_CONFIG_FILE_FOR_INPUT */

GA_RESULT appl_ga_ucs_get_common_params_for_auto_operations
          (
              GA_ENDPOINT * device,
              UINT8       * ase_count,
              UINT8       * ase_id
          )
{
    GA_RESULT  retval;
    UINT8      conn_dev_index;
    UINT8      index;

    conn_dev_index = 0U;
    index = 0U;
    retval = GA_SUCCESS;

    APPL_DBG("[APPL][GA][UCS]: >> appl_ga_ucs_get_common_params_for_auto_operations\n");

    if (NULL != device)
    {
        /* Fetch Conn Device Index */
        conn_dev_index = appl_ga_utils_bap_get_input_conn_dev_index();
    }

    /* Fetch ASE count */
    *ase_count = appl_ga_utils_bap_get_ase_count();

    for (index = 0U; index < *ase_count; index++)
    {
        /* Fetch ASE ID */
        ase_id[index] = appl_ga_utils_bap_get_ase_id();
    }

    if (NULL != device)
    {
        /* Fetch Device from conn_dev_index */
        retval = appl_ga_utils_get_conn_device(conn_dev_index, device);
    }

    APPL_DBG("[APPL][GA][UCS]: << appl_ga_ucs_get_common_params_for_auto_operations\n");

    return retval;
}

void appl_ga_ucs_auto_codec_config(void)
{
    GA_RESULT    retval;
    UINT8        index;
    UINT8        id;
    GA_ENDPOINT  device;
    UINT8        ase_index;

    /* Information of ASEs for Codec Configured Op */
    /* Total ASE count */
    UINT8                       ase_count;
    UINT8                       ase_id[MAX_UC_ASE];
    /* CS Configuration for the ASE */
    GA_LC3_CODEC_SPECIFIC_CONF  cs_conf[MAX_UC_ASE] = { 0 };
    GA_CODEC_INFO               codec_info[MAX_UC_ASE];

    /* Initialize */
    ase_count = 0U;
    index = 0U;

    APPL_DBG("[APPL][GA][UCS]: >> appl_ga_ucs_auto_codec_config\n");
    /* Fetch device, ase_count and ASE_IDs */
    if (GA_SUCCESS == appl_ga_ucs_get_common_params_for_auto_operations
                      (
                          &device,
                          &ase_count,
                          ase_id
                      ))
    {
        for (index = 0U; index < ase_count; index++)
        {
            /*
             * Codec Spec Conf set id should be same the set id selected
             * during ASCS register
             */
            id = appl_ga_utils_bap_get_cs_conf_id();

            /*
             * Prepare the CS Conf based on Set ID, Ignore the other
             * field.
             */
            if (GA_SUCCESS == appl_ga_utils_bap_uc_prepare_csc_and_qos_cap_based_on_set_id
                              (
                                  id,
                                  &cs_conf[index],
                                  NULL,
                                  NULL
                              ))
            {
                /*
                 * If one of the Set is chosen as defined in BAP Spec,
                 * the fields are mandated as below as per Spec.
                 */
                appl_ga_utils_bap_set_codec_id_for_lc3_defined_csc_set_id
                (
                    &codec_info[index]
                );

                /* Prepare the Codec Spec Configuration LTVs for LC3 */
                appl_ga_utils_bap_create_lc3_codec_spec_conf_ltv
                (
                    &cs_conf[index],
                    codec_info[index].ie,
                    &codec_info[index].ie_len
                );
            }
            else
            {
                /*
                 * Chosen a set not defined in BAP Spec, Shall be
                 * vendor specific
                 */
                appl_ga_utils_bap_get_codec_id_for_vendor_spec(&codec_info[index]);

                /* Fetch the Codec Spec Configuration LTVs for Vendor Specific */
                appl_ga_utils_bap_get_vendor_spec_codec_spec_conf_ltv
                (
                    codec_info[index].ie,
                    &codec_info[index].ie_len
                );
            }
        }

        APPL_TRC("GA_notify_ase_configure\n");
        retval = GA_notify_ase_configure
                 (
                     &device,
                     ase_count,
                     ase_id,
                     codec_info
                 );
        APPL_TRC("Retval - ");
        appl_ga_utils_display_ga_result(retval);

        if (GA_SUCCESS == retval)
        {
            for (index = 0U; index < ase_count; index++)
            {
                /* Fetch the ASE Index from ASE ID */
                if (GA_SUCCESS == appl_ga_ucs_get_ase_index_from_ase_id
                                  (
                                      ase_id[index],
                                      &ase_index
                                  ))
                {
                    /* Update the ASE State */
                    ascs.ase[ase_index].state = GA_ASE_STATE_CODEC_CONF;
                    /* Update the conn_dev_index for an ASE */
                    appl_ga_ucs_update_conn_dev_index(device, ase_index);
                    /* Save the codec specific configuration setting for ASE */
                    GA_mem_copy
                    (
                        &ascs.ase[ase_index].cs_conf,
                        &cs_conf[index],
                        sizeof(GA_LC3_CODEC_SPECIFIC_CONF)
                    );
#ifdef APPL_GA_ALLOW_CODEC_CONF_CACHING
                    /*
                     * Update the codec_info for an ASE if
                     * caching is supported
                     */
                    GA_mem_copy
                    (
                        ascs.ase[ase_index].codec,
                        &sep->codec,
                        sizeof(GA_CODEC_INFO)
                    );
#endif /* APPL_GA_ALLOW_CODEC_CONF_CACHING */
                }
            }
        }
    }

    APPL_DBG("[APPL][GA][UCS]: << appl_ga_ucs_auto_codec_config\n");
    return;
}

void appl_ga_ucs_auto_rx_start_ready(void)
{
    GA_RESULT    retval;
    GA_ENDPOINT  device;
    UINT8        ase_index;
    int          choice;
    UINT8        index;

    /* Information of ASEs for Receiver Start Ready Op */
    /* Total ASE count */
    UINT8  ase_count;
    UINT8  ase_id[MAX_UC_ASE];
    UINT8  ase_count_valid = 0;
    UINT8  ase_id_valid[MAX_UC_ASE];

    /* MISRA C-2012 RULE 9.1 | Coverity UNINIT */
    GA_mem_set(ase_id, 0, MAX_UC_ASE);
    GA_mem_set(ase_id_valid, 0, MAX_UC_ASE);

    APPL_DBG("[APPL][GA][UCS]: >> appl_ga_ucs_auto_rx_start_ready\n");
    /* Fetch device, ase_count and ASE_IDs */
    if (GA_SUCCESS == appl_ga_ucs_get_common_params_for_auto_operations
                      (
                          &device,
                          &ase_count,
                          ase_id
                      ))
    {
        for (index = 0U; index < ase_count; index++)
        {
            /* Fetch the ASE Index from ASE ID */
            if (GA_SUCCESS == appl_ga_ucs_get_ase_index_from_ase_id
                              (
                                  ase_id[index],
                                  &ase_index
                              ))
            {
                if (GA_ROLE_SINK == ascs.ase[ase_index].role)
                {
                    /*
                     * As per BAP Spec, Version: 1.0.1, Page: 94
                     * If the ASE is in the Enabling state, and if the device in the Audio Sink
                     * role for that ASE has not already set up its internal audio data path,
                     * the device in the Audio Sink role shall set up its internal audio data
                     * path as defined in Section 5.6.3.1 in preparation for reception of audio
                     * data. The device in the Audio Sink role shall then initiate the
                     * Receiver Start Ready operation as defined in Section 5.6.3.2.
                     */
                    if (AUDIO_ISO_SETUP_COMPLETE == ascs.ase[ase_index].iso_state)
                    {
                        ase_id_valid[ase_count_valid] = ase_id[index];
                        ase_count_valid++;
                    }
                    else
                    {
                        APPL_ERR
                        (
                            "Audio data path for ASE ID %d is not setup yet. Rx_start_ready not allowed !\n",
                            ase_id[index]
                        );
                    }
                }
                else
                {
                    ase_id_valid[ase_count_valid] = ase_id[index];
                    ase_count_valid++;
                }
            }
        }
        if (0U < ase_count)
        {
            CONSOLE_OUT("Enter ASE ID for active playback: ");
            CONSOLE_IN("%d", &choice);
            ascs.ase_id_active_playback = (UINT8)choice;
        }

        /* TODO: Add check to validate if CIS is established for this ASE */

        APPL_TRC("GA_notify_ase_receiver_start_ready\n");
        retval = GA_notify_ase_receiver_start_ready
                 (
                     &device,
                     ase_count_valid,
                     &ase_id_valid[0U]
                 );
        APPL_TRC("Retval - ");
        appl_ga_utils_display_ga_result(retval);

        if (GA_SUCCESS == retval)
        {
            if (0U < ase_count)
            {
                /* Fetch the ASE Index from ASE ID */
                if (GA_SUCCESS == appl_ga_ucs_get_ase_index_from_ase_id
                                  (
                                      ascs.ase_id_active_playback,
                                      &ase_index
                                  ))
                {
                    /* Update the ASE State */
                    ascs.ase[ase_index].state = GA_ASE_STATE_STREAMING;
                    if (GA_ROLE_SINK == ascs.ase[ase_index].role)
                    {
                        /* We are Audio Sink, Start Receiving Audio */
                        appl_ga_ucs_start_receiving_audio
                        (
                            ascs.ase[ase_index].cig_cis_info.handle,
                            ascs.ase[ase_index].cs_conf,
                            AUDIO_NUM_OF_BITS_PER_SAMPLE
                        );
                    }
                }
            }
        }
    }

    APPL_DBG("[APPL][GA][UCS]: << appl_ga_ucs_auto_rx_start_ready\n");
    return;
}

void appl_ga_ucs_auto_update_metadata(void)
{
    GA_RESULT        retval;
    UINT8            j;
    UINT8            ase_count;
    UINT8            index;
    UINT8            ase_id[MAX_UC_ASE];
    GA_CONTENT_INFO  content_info[MAX_UC_ASE];
    UINT8            ccid[MAX_UC_ASE];
    GA_ENDPOINT      device;

    /* Initialize */
    j = 0U;
    ase_count = 0U;
    index = 0U;

   /* MISRA C-2012 RULE 9.1 | Coverity UNINIT */
   GA_mem_set(ase_id, 0, MAX_UC_ASE);

    APPL_DBG("[APPL][GA][UCS]: >> appl_ga_ucs_auto_update_metadata\n");

    /* Fetch device, ase_count and ASE_IDs */
    if (GA_SUCCESS == appl_ga_ucs_get_common_params_for_auto_operations
                      (
                          &device,
                          &ase_count,
                          ase_id
                      ))
    {
        for (index = 0U; index < ase_count; index++)
        {
            /*
             * Unicast Client may write any LTV structures for the Metadata
             * parameter.
             */
            /*
             * While initiating the Update Metadata operation for an ASE, the
             * Unicast Client may include the Streaming_Audio_Contexts LTV
             * structure in the Metadata parameter for that ASE
             * Refer BAP Spec V_1.0 Page- 95
             */
            /* Fetch the streaming audio context value */
            content_info[index].contexts =
                appl_ga_utils_bap_fetch_streaming_audio_ctx();

            /*
             * Refer CAP Spec, Version: 1.0, Page: 20, Section: 4.2.2
             * An Acceptor that operates in the role of a BAP Unicast Server
             * shall not change a CCID_List value by initiating a BAP Update
             * Metadata operation, or by any other means except when accepting
             * a BAP Enable operation written by an Initiator, or when
             * accepting a BAP Update Metadata operation written by an
             * Initiator that includes a CCID_List value
             * (see Section 5.6.3 in BAP Spec).
             */
            /*
             * TODO: Check for Content Control service and reuse the CCID
             * values of those in the CCID_List.
             * Automate it.
             */
            content_info[index].num_ccid = appl_ga_utils_bap_get_ccid_count();

            for (j = 0U; j < content_info[index].num_ccid; j++)
            {
                ccid[j] = appl_ga_utils_bap_get_ccid();
            }
            content_info[index].ccid = ccid;
        }

        APPL_TRC("GA_notify_ase_update\n");
        retval = GA_notify_ase_update
                 (
                     &device,
                     ase_count,
                     &ase_id[0U],
                     &content_info[0U]
                 );
        APPL_TRC("Retval - ");
        appl_ga_utils_display_ga_result(retval);
    }

    APPL_DBG("[APPL][GA][UCS]: << appl_ga_ucs_auto_update_metadata\n");
    return;
}

void appl_ga_ucs_auto_disable(void)
{
    GA_RESULT    retval;
    GA_ENDPOINT  device;
    UINT8        ase_index;
    UINT8        index;

    /* Information of ASEs for Disable Op */
    /* Total ASE count */
    UINT8  ase_count;
    UINT8  ase_id[MAX_UC_ASE];

    /* MISRA C-2012 RULE 9.1 | Coverity UNINIT */
    GA_mem_set(ase_id, 0, MAX_UC_ASE);

    APPL_DBG("[APPL][GA][UCS]: >> appl_ga_ucs_auto_disable\n");

    /* Fetch device, ase_count and ASE_IDs */
    if (GA_SUCCESS == appl_ga_ucs_get_common_params_for_auto_operations
                      (
                          &device,
                          &ase_count,
                          ase_id
                      ))
    {
        APPL_TRC("GA_notify_ase_suspend\n");
        retval = GA_notify_ase_suspend
                 (
                     &device,
                     ase_count,
                     &ase_id[0U]
                 );
        APPL_TRC("Retval - ");
        appl_ga_utils_display_ga_result(retval);

        if (GA_SUCCESS == retval)
        {
            for (index = 0U; index < ase_count; index++)
            {
                /* Fetch the ASE Index from ASE ID */
                if (GA_SUCCESS == appl_ga_ucs_get_ase_index_from_ase_id
                                  (
                                      ase_id[index],
                                      &ase_index
                                  ))
                {
                    /* Update the ASE State */
                    if (GA_ROLE_SINK == ascs.ase[ase_index].role)
                    {
                        ascs.ase[ase_index].state = GA_ASE_STATE_QOS_CONF;
                        if (ascs.ase_id_active_playback == ascs.ase[ase_index].id)
                        {
                            /*
                             * We are Audio Sink, Stop receiving Audio only for the
                             * active playback ASE ID
                             */
                            appl_ga_ucs_stop_receiving_audio
                            (
                                ascs.ase[ase_index].cig_cis_info.handle,
                                ascs.ase[ase_index].cs_conf,
                                AUDIO_NUM_OF_BITS_PER_SAMPLE
                            );
                        }
                    }
                    else if (GA_ROLE_SOURCE == ascs.ase[ase_index].role)
                    {
                        ascs.ase[ase_index].state = GA_ASE_STATE_DISABLING;
                    }
                }
            }
        }
    }

    APPL_DBG("[APPL][GA][UCS]: << appl_ga_ucs_auto_disable\n");
    return;
}

void appl_ga_ucs_auto_release(void)
{
    GA_RESULT    retval;
    GA_ENDPOINT  device;

    /* Information of ASEs for Release Op */
    /* Total ASE count */
    UINT8  ase_count;
    UINT8  ase_id[MAX_UC_ASE];
    UINT8  ase_id_valid[MAX_UC_ASE];
    UINT8  index;
    UINT8  ase_index;
    UINT8  ase_index_valid[MAX_UC_ASE];
    UINT8  ase_count_valid;
    UINT8  ase_index_using_same_cis;
    int    choice;

    /* Initialize */
    index = 0U;
    ase_index = 0U;
    choice = 0U;
    retval = GA_FAILURE;
    ase_count_valid = 0U;
    ase_index_using_same_cis = 0U;
    GA_INIT_BRR_DEVICE(&device);

    /* MISRA C-2012 RULE 9.1 | Coverity UNINIT */
    GA_mem_set(ase_id, 0, MAX_UC_ASE);
    GA_mem_set(ase_id_valid, 0, MAX_UC_ASE);
    GA_mem_set(ase_index_valid, 0, MAX_UC_ASE);

    APPL_DBG("[APPL][GA][UCS]: >> appl_ga_ucs_auto_release\n");

    /*
     * TODO: Trigger this API automatically when LE ACL Link Loss is detected.
     */
    printf("Enter your choice\n");
    printf("1. LE ACL Link Loss\n");
    printf("2. No\n");
    CONSOLE_IN("%d", &choice);

    /* Auto Release called due to detection of LE ACL Link Loss */
    if (0x01U == (UINT8)choice)
    {
        /* Fetch device, ase_count and ASE_IDs */
        retval = appl_ga_ucs_get_common_params_for_auto_operations
                 (
                     NULL,
                     &ase_count,
                     ase_id
                 );
    }
    else
    {
        /* Fetch device, ase_count and ASE_IDs */
        retval = appl_ga_ucs_get_common_params_for_auto_operations
                 (
                     &device,
                     &ase_count,
                     ase_id
                 );
    }

    if (GA_SUCCESS == retval)
    {
        /* Validate the ASE IDs */
        for (index = 0U; index < ase_count; index++)
        {
            /* Get ASE Index from ASE Id */
            retval = appl_ga_ucs_get_ase_index_from_ase_id
                     (
                         ase_id[index],
                         &ase_index
                     );
            if (GA_SUCCESS == retval)
            {
                /*
                 * If Bidirectional, fetch the ASE Index which is using
                 * same CIG & CIS
                 */
                if (GA_TRUE == appl_ga_ucs_get_cig_cis_shared_bidirectional_ase_index
                               (
                                   ase_index, &ase_index_using_same_cis
                               ))
                {
                    /*
                     * If Bidirectional, then validate if given ASE is
                     * in Enabling/Streaming state
                     */
                    if (!(((GA_ASE_STATE_ENABLING == ascs.ase[ase_index].state)
                        ||
                        (GA_ASE_STATE_STREAMING == ascs.ase[ase_index].state))
                        &&
                        (CIS_STATE_CONNECTED ==
                            ascs.ase[ase_index].cig_cis_info.cis_state)))
                    {
                        if (!(((GA_ASE_STATE_ENABLING ==
                                ascs.ase[ase_index_using_same_cis].state)
                            ||
                            (GA_ASE_STATE_STREAMING ==
                                ascs.ase[ase_index_using_same_cis].state))
                            &&
                            (CIS_STATE_CONNECTED ==
                                ascs.ase[ase_index_using_same_cis].cig_cis_info.cis_state)))
                        {
                            ase_id_valid[ase_count_valid] = ase_id[index];
                            ase_index_valid[ase_count_valid] = ase_index;
                            ase_count_valid++;
                        }
                        else
                        {
                            APPL_ERR("Release Operation is not allowed ! Disable is allowed !\n");
                        }
                    }
                    else
                    {
                        /*
                         * For the given device, CIG and CIS is shared by more than 1 ASE,
                         * Also in Enabling/Streaming state.
                         */
                        APPL_DBG
                        (
                            "[APPL][GA][UCC]: ASE ID: 0x%02X and ASE ID: 0x%02X "
                            "with CIG ID: 0x%02X and CIS ID: 0x%02X is shared.\n"
                            "ASE State of ASE ID: 0x%02X is 0x%02X\n"
                            "ASE State of ASE ID: 0x%02X is 0x%02X\n",
                            ascs.ase[ase_index].id,
                            ascs.ase[ase_index_using_same_cis].id,
                            ascs.ase[ase_index].qos_conf.channel.cig_id,
                            ascs.ase[ase_index].qos_conf.channel.cis_id,
                            ascs.ase[ase_index].id,
                            ascs.ase[ase_index].state,
                            ascs.ase[ase_index_using_same_cis].id,
                            ascs.ase[ase_index_using_same_cis].state
                        );
                        APPL_ERR("Release Operation is not allowed ! Disable is allowed !\n");
                    }
                }
                else
                {
                    ase_id_valid[ase_count_valid] = ase_id[index];
                    ase_index_valid[ase_count_valid] = ase_index;
                    ase_count_valid++;
                }
            }
            else
            {
                APPL_ERR("ASE ID: 0x%02X not found !\n", ase_id[ase_index]);
            }
        }

        /* TODO: This API needs to be triggered only during LE ACL Link Loss? */

        APPL_TRC("GA_notify_ase_release\n");
        if (GA_IS_NON_ZERO_ENDPOINT_ADDR(device.bd_addr))
        {
            retval = GA_notify_ase_release
                     (
                         &device,
                         ase_count_valid,
                         &ase_id_valid[0U]
                     );
        }
        else
        {
            retval = GA_notify_ase_release
                     (
                         NULL,
                         ase_count_valid,
                         &ase_id_valid[0U]
                     );
        }
        APPL_TRC("Retval - ");
        appl_ga_utils_display_ga_result(retval);

        if (GA_SUCCESS == retval)
        {
            /*
             * The Unicast Client and Unicast Server should remove any
             * internal audio data paths that have been set up for the ASE that
             * is in the Releasing state, as defined in Section 5.6.6.1,
             * before terminating the CIS.
             */
            /*
             * The Unicast Server shall terminate a CIS established by
             * the Unicast Client for an ASE if the Unicast Server has
             * autonomously initiated the Release operation for that ASE by
             * following the Connected Isochronous Stream Terminate procedure
             * defined in Volume 3, Part C, Section 9.3.15 in Core Spec.
             */
            for (index = 0U; index < ase_count_valid; index++)
            {
                /* Update the ASE State */
                ascs.ase[ase_index_valid[index]].state = GA_ASE_STATE_RELEASING;
                ascs.ase[ase_index_valid[index]].is_release_initiated = GA_TRUE;

                /*
                 * TODO: On triggering autonomous Release, Server will trigger
                 * CIS Disconnection and as a peripheral device ISO data path
                 * will be removed by controller on CIS disconnect. So, is it
                 * required to trigger ISO data path removal here?
                 * If No, then needs to trigger CIS Disconnect here,
                 * which is currently called on receiving
                 * HCI_LE_REMOVE_ISO_DATA_PATH_OPCODE event in a chain.
                 */
                if (GA_FAILURE == appl_ga_ucs_remove_iso
                                  (
                                      ase_index_valid[index],
                                      ascs.ase[ase_index_valid[index]].cig_cis_info.handle
                                  ))
                {
                    /*
                     * Exception case: Previously, ASE state is GA_ASE_STATE_QOS_CONF,
                     * no ISO Data Path has been setup. In this case if Client triggers
                     * Release CP operation, then the API will return GA_FAILURE
                     * which is the expected behaviour(ISO is not setup).
                     */

                    /*
                     * If there is no CIS established, Release is triggered,
                     * Perform Release complete.
                     */
                    if ((CIS_STATE_IDLE == ascs.ase[ase_index_valid[index]].cig_cis_info.cis_state) ||
                        (CIS_STATE_INITIALIZED == ascs.ase[ase_index_valid[index]].cig_cis_info.cis_state))
                    {
                        appl_ga_ucs_trigger_release_complete
                        (
                            &device,
                            1U,
                            &ase_index_valid[index]
                        );
                    }
                    else
                    {
                        /*
                         * ISO data path is not setup, but CIS is established.
                         * Hence, trigger disconnect CIS.
                         */
                        appl_ga_ucs_terminate_cis
                        (
                            ascs.ase[ase_index_valid[index]].cig_cis_info.handle
                        );
                    }
                }
                else
                {
                    /* Do Nothing */
                }

                if (GA_ROLE_SOURCE == ascs.ase[ase_index_valid[index]].role)
                {
                    /* We are Audio Source, Stop transmitting Audio */
                    appl_ga_ucs_stop_transmitting_audio
                    (
                        ascs.ase[ase_index_valid[index]].cig_cis_info.handle,
                        ascs.ase[ase_index_valid[index]].cs_conf,
                        ascs.ase[ase_index_valid[index]].qos_conf_set_id,
                        AUDIO_NUM_OF_BITS_PER_SAMPLE
                    );
                }
                else
                {
                    if (ascs.ase_id_active_playback == ascs.ase[ase_index_valid[index]].id)
                    {
                        /*
                        * We are Audio Sink, Stop receiving Audio only for the
                        * active playback ASE ID
                        */
                        appl_ga_ucs_stop_receiving_audio
                        (
                            ascs.ase[ase_index_valid[index]].cig_cis_info.handle,
                            ascs.ase[ase_index_valid[index]].cs_conf,
                            AUDIO_NUM_OF_BITS_PER_SAMPLE
                        );
                    }
                }
            }
        }
    }

    APPL_DBG("[APPL][GA][UCS]: << appl_ga_ucs_auto_release\n");
    return;
}

void appl_ga_ucs_release_complete(void)
{
    GA_ENDPOINT  device;
    GA_RESULT retval;

    /* Information of ASEs for Release Complete Op */
    /* Total ASE count */
    UINT8  ase_count;
    UINT8  ase_count_valid;
    UINT8  index;
    UINT8  ase_id[MAX_UC_ASE] = { 0U };
    UINT8  ase_index[MAX_UC_ASE] = { 0U };
    int    choice;

    ase_count = 0U;
    ase_count_valid = 0U;
    index = 0U;
    choice = 0U;
    retval = GA_FAILURE;
    GA_INIT_BRR_DEVICE(&device);

    APPL_DBG("[APPL][GA][UCS]: >> appl_ga_ucs_trigger_release_complete_using_ase_id\n");
    /*
     * TODO: Trigger this API automatically when LE ACL Link Loss is detected.
     */
    printf("Enter your choice\n");
    printf("1. LE ACL Link Loss\n");
    printf("2. No\n");
    CONSOLE_IN("%d", &choice);

    /* Auto Release called due to detection of LE ACL Link Loss */
    if (0x01U == (UINT8)choice)
    {
        /* Fetch device, ase_count and ASE_IDs */
        retval = appl_ga_ucs_get_common_params_for_auto_operations
                 (
                     NULL,
                     &ase_count,
                     ase_id
                 );
    }
    else
    {
        /* Fetch device, ase_count and ASE_IDs */
        retval = appl_ga_ucs_get_common_params_for_auto_operations
                 (
                     &device,
                     &ase_count,
                     ase_id
                 );
    }

    if (GA_SUCCESS == retval)
    {
        for (index = 0U; index < ase_count; index++)
        {
            /* Fetch ase_index from ase_id */
            if (GA_SUCCESS == appl_ga_ucs_get_ase_index_from_ase_id
                              (
                                  ase_id[index],
                                  &ase_index[ase_count_valid]
                              ))
            {
                ase_count_valid++;
            }
        }

        /* TODO: This API needs to be triggered only during LE ACL Link Loss? */
        /* Trigger Release Complete */

        if (GA_IS_NON_ZERO_ENDPOINT_ADDR(device.bd_addr))
        {
            appl_ga_ucs_trigger_release_complete
            (
                &device,
                ase_count_valid,
                ase_index
            );
        }
        else
        {
            appl_ga_ucs_trigger_release_complete
            (
                NULL,
                ase_count_valid,
                ase_index
            );
        }
    }

    APPL_DBG("[APPL][GA][UCS]: << appl_ga_ucs_trigger_release_complete_using_ase_id\n");
    return;
}

void appl_ga_ucs_trigger_release_complete_using_cis_handle
     (
         UINT16 cis_conn_handle
     )
{
    UINT8        ase_index[MAX_UC_ASE] = { 0U };
    UINT8        ase_count;
    GA_ENDPOINT  device;

    /* Initialize */
    ase_count = 0U;

    APPL_DBG("[APPL][GA][UCS]: >> appl_ga_ucs_trigger_release_complete_using_cis_handle\n");

    /* Fetch the ASE Index List based on the CIS Conn Handle */
    if (GA_SUCCESS == appl_ga_ucs_get_ase_index_from_cis_conn_handle
                      (
                          cis_conn_handle,
                          &ase_count,
                          ase_index
                      ))
    {
        /* Triggering Release Complete for a single device */
        /* TODO: Support for multiple device */
        if (GA_SUCCESS == appl_ga_utils_get_conn_device
                          (
                              ascs.ase[ase_index[0U]].conn_dev_index[0U],
                              &device
                          ))
        {
            appl_ga_ucs_trigger_release_complete
            (
                &device,
                ase_count,
                ase_index
            );
        }
    }
    APPL_DBG("[APPL][GA][UCS]: << appl_ga_ucs_trigger_release_complete_using_cis_handle\n");
    return;
}

void appl_ga_ucs_trigger_release_complete
     (
         GA_ENDPOINT * device,
         UINT8         ase_count,
         UINT8       * ase_index
     )
{
    GA_RESULT  retval;
    UINT8      index;
    UINT8      ase_count_valid;
    UINT8      ase_id[MAX_UC_ASE] = { 0U };
    UINT8      ase_index_valid_array[MAX_UC_ASE] = { 0 };

    index = 0U;
    ase_count_valid = 0U;

    APPL_DBG("[APPL][GA][UCS]: >> appl_ga_ucs_trigger_release_complete\n");

    for (index = 0U; index < ase_count; index++)
    {
        if (GA_SUCCESS == appl_ga_ucs_is_release_complete_allowed
                          (
                              ase_index[index]
                          ))
        {
            ase_id[ase_count_valid] = ascs.ase[ase_index[index]].id;
            ase_index_valid_array[ase_count_valid] = ase_index[index];
            ase_count_valid++;
            /* Check if the release is initiated locally for this ASE */
            if (GA_TRUE == ascs.ase[ase_index[index]].is_release_initiated)
            {
                ascs.ase[ase_index[index]].is_release_initiated = GA_FALSE;
            }
        }
    }
    /* Trigger Release Complete */
    APPL_TRC("GA_notify_release_complete\n");
    retval = GA_notify_release_complete
             (
                 device,
                 ase_count_valid,
                 &ase_id[0U]
             );
    APPL_TRC("Retval - ");
    appl_ga_utils_display_ga_result(retval);

    for (index = 0U; index < ase_count_valid; index++)
    {
        if (GA_SUCCESS == retval)
        {
            /* Update the ASE State based on Caching */
            /* Update the Codec Cfg Params if Cache Supported */
#ifdef APPL_GA_ALLOW_CODEC_CONF_CACHING
            ascs.ase[ase_index_valid_array[index]].state =
                GA_ASE_STATE_CODEC_CONF;
#else /* APPL_GA_ALLOW_CODEC_CONF_CACHING */
            ascs.ase[ase_index_valid_array[index]].state = GA_ASE_STATE_IDLE;
#endif /* APPL_GA_ALLOW_CODEC_CONF_CACHING */
        }
    }

    APPL_DBG("[APPL][GA][UCS]: << appl_ga_ucs_trigger_release_complete\n");
    return;
}

void appl_ga_ucs_display_ase_data_for_a_conn_dev(void)
{
    UINT8  conn_dev_index;
    UINT8  index;
    UINT8  ase_index[MAX_UC_ASE] = { 0 };
    UINT8  ase_count;

    conn_dev_index = 0U;
    index = 0U;
    ase_count = 0U;

    APPL_DBG("[APPL][GA][UCS]: >> appl_ga_ucs_display_ase_data_for_a_conn_dev\n");

    /* Fetch Conn Device Index */
    conn_dev_index = appl_ga_utils_bap_get_input_conn_dev_index();

    if (GA_SUCCESS == appl_ga_ucs_get_ase_index_from_conn_dev_index
                      (
                          conn_dev_index,
                          &ase_count,
                          ase_index
                      ))
    {
        for (index = 0U; index < ase_count; index++)
        {
            APPL_TRC("ASE Data [%d]:\n", (index + 1U));
            /* Display ASE data */
            appl_ga_utils_bap_display_ase_data
            (
                conn_dev_index,
                ascs.ase[ase_index[index]]
            );
        }
    }
    else
    {
        APPL_DBG
        (
            "[APPL][GA][UCS]: ASCS data for this device is not present !\n"
        );
    }

    APPL_DBG("[APPL][GA][UCS]: << appl_ga_ucs_display_ase_data_for_a_conn_dev\n");
    return;
}

void appl_ga_ucs_display_all_ase_data(void)
{
    UINT8  index;

    index = 0U;

    APPL_DBG("[APPL][GA][UCS]: >> appl_ga_ucs_display_all_ase_data\n");

    for (index = 0U; index < ascs.ase_count; index++)
    {
        APPL_TRC("ASE Data [%d]:\n", (index + 1U));
        /* Display ASE data */
        appl_ga_utils_bap_display_local_ase_db(ascs.ase[index]);
    }

    APPL_DBG("[APPL][GA][UCS]: << appl_ga_ucs_display_all_ase_data\n");
    return;
}

void appl_ga_ucs_ase_disconnect_cis(void)
{
    UINT8   ase_id;
    UINT8   ase_index;
    UINT16  cis_handle;
    UCHAR   reason;
    int     input;

    /* Initialize */
    ase_id = 0U;
    ase_index = 0U;
    cis_handle = INVALID_CONN_HANDLE;
    reason = 0U;
    input = 0;

    APPL_DBG("[APPL][GA][UCS]: >> appl_ga_ucs_ase_disconnect_cis\n");

    ase_id = appl_ga_utils_bap_get_ase_id();

    /* Fetch ase_index from ase_id and ascs_index */
    if (GA_SUCCESS == appl_ga_ucs_get_ase_index_from_ase_id(ase_id, &ase_index))
    {
        /* Check if disconnection is allowed or not */
        if (GA_SUCCESS == appl_ga_ucs_is_cis_disconnect_allowed
                          (
                              ase_index
                          ))
        {
            /* Check if CIS state is valid */
            if (CIS_STATE_CONNECTED ==
                ascs.ase[ase_index].cig_cis_info.cis_state)
            {
                /* Update cis_handle to be disconnected */
                cis_handle =
                    ascs.ase[ase_index].cig_cis_info.handle;
            }

            if (INVALID_CONN_HANDLE != cis_handle)
            {
                /* Disconnect CIS */
                printf("Enter reason for disconnection: ");
                CONSOLE_IN("%d", &input);
                reason = (UCHAR)input;
                if (GA_SUCCESS == appl_ga_utils_disconnect
                                  (
                                      cis_handle,
                                      reason
                                  ))
                {
                    APPL_TRC("CIS Disconnection successful\n");
                }
            }
        }
    }
    else
    {
        APPL_ERR("Invalid ASE ID !\n");
    }

    APPL_DBG("[APPL][GA][UCS]: << appl_ga_ucs_ase_disconnect_cis\n");
    return;
}

GA_RESULT appl_ga_fetch_conn_dev_index_ase_index_from_acl_conn_handle
          (
              UINT16   acl_conn_handle,
              UINT8  * conn_dev_index,
              UINT8  * ase_count,
              UINT8  * ase_index
          )
{
    GA_RESULT  retval;

    retval = GA_FAILURE;

    APPL_DBG("[APPL][GA][UCS]: >> appl_ga_fetch_conn_dev_index_ase_index_from_acl_conn_handle\n");

    /* Fetch conn_dev_index from acl_conn_handle */
    if (GA_SUCCESS == appl_ga_utils_get_dev_index_from_handle
                      (
                          acl_conn_handle,
                          conn_dev_index
                      ))
    {
        /* Fetch ascs_index from conn_dev_index */
        retval = appl_ga_ucs_get_ase_index_from_conn_dev_index
                 (
                     *conn_dev_index,
                     ase_count,
                     ase_index
                 );
    }

    APPL_DBG("[APPL][GA][UCS]: << appl_ga_fetch_conn_dev_index_ase_index_from_acl_conn_handle\n");
    return retval;
}

GA_RESULT appl_ga_ucs_get_ase_index_from_conn_dev_index
          (
              UINT8   conn_dev_index,
              UINT8 * ase_count,
              UINT8 * ase_index
          )
{
    GA_RESULT  retval;
    UINT8      index;
    UINT8      j;

    retval = GA_FAILURE;
    index = 0U;
    j = 0U;

    APPL_DBG("[APPL][GA][UCS]: >> appl_ga_ucs_get_ase_index_from_conn_dev_index\n");

    for (index = 0U; index < ascs.ase_count; index++)
    {
        for (j = 0U; j < MAX_UCS_SIMULTANEOUS_ASE; j++)
        {
            if (conn_dev_index == ascs.ase[index].conn_dev_index[j])
            {
                ase_index[*ase_count] = index;
                (*ase_count)++;
                retval = GA_SUCCESS;
                break;
            }
        }
    }

    APPL_DBG("[APPL][GA][UCS]: << appl_ga_ucs_get_ase_index_from_conn_dev_index\n");
    return retval;
}

GA_RESULT appl_ga_ucs_get_ase_index_from_cis_conn_handle
          (
              UINT16   cis_conn_handle,
              UINT8  * ase_count,
              UINT8  * ase_index
          )
{
    GA_RESULT  retval;
    UINT8      index;

    retval = GA_FAILURE;
    index = 0U;

    APPL_DBG("[APPL][GA][UCS]: >>  appl_ga_ucs_get_ase_index_from_cis_conn_handle\n");

    if ((NULL == ase_index) || (NULL == ase_count))
    {
        return GA_FAILURE;
    }

    for (index = 0U; index < ascs.ase_count; index++)
    {
        if (cis_conn_handle == ascs.ase[index].cig_cis_info.handle)
        {
            ase_index[(*ase_count)] = index;
            (*ase_count)++;
            retval = GA_SUCCESS;
        }
    }

    APPL_DBG("[APPL][GA][UCS]: << appl_ga_ucs_get_ase_index_from_cis_conn_handle\n");

    return retval;
}

GA_RESULT appl_ga_ucs_fetch_ase_index_from_acl_conn_handle_cig_id_cis_id
          (
              UINT16   acl_handle,
              UINT8    cig_id,
              UINT8    cis_id,
              UINT8  * ase_count,
              UINT8  * ase_index
          )
{
    GA_RESULT  retval;
    UINT8      ase_index_for_same_dev[MAX_UC_ASE] = { 0 };
    UINT8      ase_count_for_same_dev;
    UINT8      conn_dev_index;
    UINT8      index;

    /* Initialize */
    retval = GA_FAILURE;
    ase_count_for_same_dev = 0U;
    conn_dev_index = 0U;
    index = 0U;

    APPL_DBG("[APPL][GA][UCS]: >> appl_ga_ucs_fetch_ase_index_from_acl_conn_handle_cig_id_cis_id\n");
    /*
     * Fetch conn_dev_index and all ase_index for
     * same device from acl_handle
     */
    if (GA_SUCCESS == appl_ga_fetch_conn_dev_index_ase_index_from_acl_conn_handle
                      (
                          acl_handle,
                          &conn_dev_index,
                          &ase_count_for_same_dev,
                          ase_index_for_same_dev
                      ))
    {
        /* Check for ASEs of same device with same CIG_ID and CIS_ID */
        for (index = 0U; index < ase_count_for_same_dev; index++)
        {
            if ((cig_id == ascs.ase[ase_index_for_same_dev[index]].qos_conf.channel.cig_id) &&
                (cis_id == ascs.ase[ase_index_for_same_dev[index]].qos_conf.channel.cis_id))
            {
                ase_index[*ase_count] = ase_index_for_same_dev[index];
                *ase_count += 1U;
                retval = GA_SUCCESS;
            }
        }
    }

    APPL_DBG("[APPL][GA][UCS]: << appl_ga_ucs_fetch_ase_index_from_acl_conn_handle_cig_id_cis_id\n");
    return retval;
}

void appl_ga_ucs_update_conn_dev_index
     (
         GA_ENDPOINT device,
         UINT8       ase_index
     )
{
    UINT8  conn_dev_index;
    UINT8  index;
    UINT8  empty_conn_dev_index;
    UINT8  is_conn_dev_index_present;

    /* Initialize */
    conn_dev_index = 0U;
    is_conn_dev_index_present = GA_FALSE;
    empty_conn_dev_index = INVALID_CONN_DEV_INDEX;
    index = 0U;

    APPL_DBG("[APPL][GA][UCS]: >> appl_ga_ucs_update_conn_dev_index\n");

    /* Fetch conn_dev_index from device */
    if (GA_SUCCESS == appl_ga_utils_get_conn_device_index
                      (
                          device,
                          &conn_dev_index
                      ))
    {
        /* Check if conn_dev_index already present or not */
        for (index = 0U; index < MAX_UCS_SIMULTANEOUS_ASE; index++)
        {
            /* Compare conn_dev_index */
            if (conn_dev_index == ascs.ase[ase_index].conn_dev_index[index])
            {
                is_conn_dev_index_present = GA_TRUE;
                break;
            }
            /* Check for empty conn_dev_index */
            if ((INVALID_CONN_DEV_INDEX == ascs.ase[ase_index].conn_dev_index[index]) &&
                (INVALID_CONN_DEV_INDEX == empty_conn_dev_index))
            {
                empty_conn_dev_index = index;
            }
        }

        /*
         * If conn_dev_index is not present then add the conn_dev_index
         * into an empty array element
         */
        if (GA_FALSE == is_conn_dev_index_present)
        {
            ascs.ase[ase_index].conn_dev_index[empty_conn_dev_index] =
                conn_dev_index;
        }
    }

    APPL_DBG("[APPL][GA][UCS]: << appl_ga_ucs_update_conn_dev_index\n");
    return;
}

GA_RESULT appl_ga_ucs_get_ase_index_from_ase_id
          (
              UINT8   ase_id,
              UINT8 * ase_index
          )
{
    GA_RESULT  retval;
    UINT8      index;

    retval = GA_FAILURE;
    index = 0U;

    APPL_DBG("[APPL][GA][UCS]: >> appl_ga_ucs_get_ase_index_from_ase_id\n");

    /* Fetch ASE index based on ASE ID */
    for (index = 0U; index < MAX_UC_ASE; index++)
    {
        /* Compare ASE ID */
        if (ase_id == ascs.ase[index].id)
        {
            *ase_index = index;
            retval = GA_SUCCESS;
            break;
        }
    }

    APPL_DBG("[APPL][GA][UCS]: << appl_ga_ucs_get_ase_index_from_ase_id\n");

    return retval;
}

void appl_ga_ucs_terminate_cis(UINT16 cis_conn_handle)
{
    UINT8  ase_index[MAX_UC_ASE] = { 0 };
    UINT8  ase_count;
    UINT8  index;

    /* Initialize */
    ase_count = 0U;
    index = 0U;

    APPL_DBG("[APPL][GA][UCS]: >> appl_ga_ucs_terminate_cis\n");

    /* Fetch the ASE Index List based on the CIS Conn Handle */
    if (GA_SUCCESS == appl_ga_ucs_get_ase_index_from_cis_conn_handle
                      (
                          cis_conn_handle,
                          &ase_count,
                          ase_index
                      ))
    {
        for (index = 0U; index < ase_count; index++)
        {
            if (GA_SUCCESS == appl_ga_ucs_is_cis_disconnect_allowed
                              (
                                  ase_index[index]
                              ))
            {
                /* Disconnect CIS */
                if (GA_SUCCESS == appl_ga_utils_disconnect
                                  (
                                      cis_conn_handle,
                                      0x13U
                                  ))
                {
                    APPL_TRC("CIS Disconnection successful\n");
                }
                break;
            }
        }
    }
    APPL_DBG("[APPL][GA][UCS]: << appl_ga_ucs_terminate_cis\n");
    return;
}

GA_RESULT appl_ga_ucs_remove_iso(UINT8 ase_index, UINT16 cis_conn_handle)
{
    GA_RESULT  retval;

    /* Initialize */
    retval = GA_FAILURE;

    APPL_DBG("[APPL][GA][UCS]: >> appl_ga_ucs_remove_iso\n");

    if ((GA_ASE_STATE_RELEASING == ascs.ase[ase_index].state) &&
        (AUDIO_ISO_SETUP_COMPLETE == ascs.ase[ase_index].iso_state))
    {
        if (GA_ROLE_SOURCE == ascs.ase[ase_index].role)
        {
            retval = appl_ga_utils_audio_src_le_remove_iso_data_path
                     (
                         cis_conn_handle
                     );
            if (GA_SUCCESS == retval)
            {
                APPL_TRC("[APPL][GA][UCS][%s]: ISO Data Path Removal Status: Complete\n", UC_GET_ROLE_STRING(ascs.ase[ase_index].role));
            }
            else if (GA_CONTINUE == retval)
            {
                APPL_TRC("[APPL][GA][UCC][%s]: ISO Data Path Removal Status: In-progress\n", UC_GET_ROLE_STRING(ascs.ase[ase_index].role));
            }
            else
            {
                APPL_ERR("[APPL][GA][UCS][%s]: ISO Data Path Removal Status: Failed !\n", UC_GET_ROLE_STRING(ascs.ase[ase_index].role));
            }
        }
        else if (GA_ROLE_SINK == ascs.ase[ase_index].role)
        {
            retval = appl_ga_utils_audio_snk_le_remove_iso_data_path
                     (
                         cis_conn_handle
                     );
            if (GA_SUCCESS == retval)
            {
                APPL_TRC("[APPL][GA][UCS][%s]: ISO Data Path Removal Status: Complete\n", UC_GET_ROLE_STRING(ascs.ase[ase_index].role));
            }
            else if (GA_CONTINUE == retval)
            {
                APPL_TRC("[APPL][GA][UCC][%s]: ISO Data Path Removal Status: In-progress\n", UC_GET_ROLE_STRING(ascs.ase[ase_index].role));
            }
            else
            {
                APPL_ERR("[APPL][GA][UCS][%s]: ISO Data Path Removal Status: Failed !\n", UC_GET_ROLE_STRING(ascs.ase[ase_index].role));
            }
        }
        else
        {
            /* Should not reach here */
        }

        /* Validate the retval from remove_iso and update the state */
        if (GA_SUCCESS == retval)
        {
            ascs.ase[ase_index].iso_state = AUDIO_ISO_IDLE;
        }
        else if (GA_CONTINUE == retval)
        {
            ascs.ase[ase_index].iso_state = AUDIO_ISO_UPDATE_IN_PROGRESS;
        }
        else
        {
            /* State mismatch */
        }
    }

    APPL_DBG("[APPL][GA][UCS]: << appl_ga_ucs_remove_iso\n");

    return retval;
}

void appl_ga_ucs_update_cis_conn_state
     (
         UINT8   ase_index,
         UINT8   conn,
         UINT16  cis_conn_status
     )
{
    APPL_DBG("[APPL][GA][UCS]: >> appl_ga_ucs_update_cis_conn_state\n");

    if (conn)
    {
        if (GA_SUCCESS == cis_conn_status)
        {
            if (CIS_STATE_WAITING ==
                ascs.ase[ase_index].cig_cis_info.cis_state)
            {
                ascs.ase[ase_index].cig_cis_info.cis_state =
                    CIS_STATE_CONNECTED;
            }
        }
        else
        {
            if (CIS_STATE_WAITING ==
                ascs.ase[ase_index].cig_cis_info.cis_state)
            {
                ascs.ase[ase_index].cig_cis_info.cis_state =
                    CIS_STATE_INITIALIZED;
            }
        }
    }
    else
    {
        if (GA_SUCCESS == cis_conn_status)
        {
            if (CIS_STATE_CONNECTED ==
                ascs.ase[ase_index].cig_cis_info.cis_state)
            {
                ascs.ase[ase_index].cig_cis_info.cis_state =
                    CIS_STATE_INITIALIZED;
            }
        }
        else
        {
            /* This case will never hit */
        }
    }
    APPL_DBG("[APPL][GA][UCS]: << appl_ga_ucs_update_cis_conn_state\n");
    return;
}

GA_RESULT appl_ga_ucs_setup_iso(UINT8 ase_index)
{
    GA_RESULT  retval;

    /* Initialize */
    retval = GA_FAILURE;

    APPL_DBG("[APPL][GA][UCS]: >> appl_ga_ucs_setup_iso\n");

    /*
     * As per BAP Spec, Version: 1.0.1, Page: 94
     * If the ASE is in the Enabling state, and if the device in the Audio Sink
     * role for that ASE has not already set up its internal audio data path,
     * the device in the Audio Sink role shall set up its internal audio data
     * path as defined in Section 5.6.3.1 in preparation for reception of audio
     * data. The device in the Audio Sink role shall then initiate the
     * Receiver Start Ready operation as defined in Section 5.6.3.2.
     */
    /*
     * As per BAP Spec, Version: 1.0.1, Page: 94
     * If the ASE is in the Enabling state, and if the device in the Audio
     * Source role for that ASE has not already set up its internal audio data
     * path, the device in the Audio Source role may set up its internal audio
     * data path as defined in Section 5.6.3.1, or may wait until completion of
     * the Receiver Start Ready operation for that ASE as defined in
     * Section 5.6.3.2 before setting up its internal audio data path.
     */
    if (((GA_ASE_STATE_ENABLING == ascs.ase[ase_index].state) ||
         ((GA_ASE_STATE_STREAMING == ascs.ase[ase_index].state) &&
          (GA_ROLE_SOURCE == ascs.ase[ase_index].role)))
        &&
        (CIS_STATE_CONNECTED == ascs.ase[ase_index].cig_cis_info.cis_state) &&
        (AUDIO_ISO_IDLE == ascs.ase[ase_index].iso_state))
    {
        if (GA_ROLE_SOURCE == ascs.ase[ase_index].role)
        {
            if (GA_SUCCESS == appl_ga_utils_audio_src_set_entry
                              (
                                  ascs.ase[ase_index].cig_cis_info.handle,
                                  ascs.ase[ase_index].cs_conf,
                                  GA_TRUE
                              ))
            {
                retval = appl_ga_utils_audio_src_le_setup_iso_data_path
                         (
                             ascs.ase[ase_index].cig_cis_info.handle,
                             &ascs.ase[ase_index].stream_symbol
                         );

                if (GA_SUCCESS == retval)
                {
                    APPL_TRC("[APPL][GA][UCS][%s]: ISO Data Path Setup Status: Already Complete\n", UC_GET_ROLE_STRING(ascs.ase[ase_index].role));
                    /* ISO Data Path is already set - If multiple ASEs has same CIS */
                    ascs.ase[ase_index].iso_state = AUDIO_ISO_SETUP_COMPLETE;
                    /*
                     * Display ASE Streaming Info:
                     * Conn Device Index, ASE ID, ASE Role, ASE State,
                     * CIS Connection Handle, ASE Stream Symbol
                     */
                    GA_FORMAT_DISPLAY();
                    APPL_TRC("Local:\n");
                    /* TODO: Get the conn_dev_index from the device */
                    appl_ga_utils_bap_display_ase_data
                    (
                        ascs.ase[ase_index].conn_dev_index[0U],
                        ascs.ase[ase_index]
                    );
                    GA_FORMAT_DISPLAY();
                }
                else if (GA_CONTINUE == retval)
                {
                    APPL_TRC("[APPL][GA][UCS][%s]: ISO Data Path Setup Status: In-progress\n", UC_GET_ROLE_STRING(ascs.ase[ase_index].role));
                    /* ISO Data Path is Ongoing */
                    ascs.ase[ase_index].iso_state = AUDIO_ISO_UPDATE_IN_PROGRESS;
                }
                else
                {
                    APPL_ERR("[APPL][GA][UCS][%s]: ISO Data Path Setup Status: Failed !\n", UC_GET_ROLE_STRING(ascs.ase[ase_index].role));
                }
            }
            else
            {
                APPL_ERR("[APPL][GA][UCS][%s]: ISO Data Path Setup Status: Set entry failed !\n", UC_GET_ROLE_STRING(ascs.ase[ase_index].role));
            }
        }
        else
        {
            if (GA_SUCCESS == appl_ga_utils_audio_snk_set_entry
                              (
                                  ascs.ase[ase_index].cig_cis_info.handle,
                                  ascs.ase[ase_index].cs_conf
                              ))
            {
                retval = appl_ga_utils_audio_snk_le_setup_iso_data_path
                         (
                             ascs.ase[ase_index].cig_cis_info.handle,
                             &ascs.ase[ase_index].stream_symbol
                         );

                if (GA_SUCCESS == retval)
                {
                    APPL_TRC("[APPL][GA][UCS][%s]: ISO Data Path Setup Status: Already Complete\n", UC_GET_ROLE_STRING(ascs.ase[ase_index].role));
                    /* ISO Data Path is already set - If multiple ASEs has same CIS */
                    ascs.ase[ase_index].iso_state = AUDIO_ISO_SETUP_COMPLETE;
                    /*
                     * Display ASE Streaming Info:
                     * Conn Device Index, ASE ID, ASE Role, ASE State,
                     * CIS Connection Handle, ASE Stream Symbol
                     */
                    GA_FORMAT_DISPLAY();
                    APPL_TRC("Local:\n");
                    /* TODO: Get the conn_dev_index from the device */
                    appl_ga_utils_bap_display_ase_data
                    (
                        ascs.ase[ase_index].conn_dev_index[0U],
                        ascs.ase[ase_index]
                    );
                    GA_FORMAT_DISPLAY();
                }
                else if (GA_CONTINUE == retval)
                {
                    APPL_TRC("[APPL][GA][UCS][%s]: ISO Data Path Setup Status: In-progress\n", UC_GET_ROLE_STRING(ascs.ase[ase_index].role));
                    /* ISO Data Path is Ongoing */
                    ascs.ase[ase_index].iso_state = AUDIO_ISO_UPDATE_IN_PROGRESS;
                }
                else
                {
                    APPL_ERR("[APPL][GA][UCS][%s]: ISO Data Path Setup Status: Failed !\n", UC_GET_ROLE_STRING(ascs.ase[ase_index].role));
                }
            }
            else
            {
                APPL_ERR("[APPL][GA][UCS][%s]: ISO Data Path Setup Status: Set entry failed !\n", UC_GET_ROLE_STRING(ascs.ase[ase_index].role));
            }
        }
    }
    APPL_DBG("[APPL][GA][UCS]: << appl_ga_ucs_setup_iso\n");
    return retval;
}

GA_RESULT appl_ga_ucs_is_cis_connect_accept_allowed
          (
              UINT8 * ase_index,
              UINT8   ase_count
          )
{
    GA_RESULT retval;
    UINT8 i;

    /* Initialize */
    retval = GA_SUCCESS;

    APPL_DBG("[APPL][GA][UCS]: >> appl_ga_ucs_is_cis_connect_accept_allowed\n");
    for (i = 0U; i < ase_count; i++)
    {
        if (((GA_ASE_STATE_QOS_CONF == ascs.ase[ase_index[i]].state)
            ||
            (GA_ASE_STATE_ENABLING == ascs.ase[ase_index[i]].state))
            &&
            (CIS_STATE_INITIALIZED == ascs.ase[ase_index[i]].cig_cis_info.cis_state))
        {
            /* Do nothing and proceed */
        }
        else
        {
            APPL_DBG("CIS Connect Accept Not Allowed, ASE State: (0x%02X) CIS State: (0x%02X) !",
            ascs.ase[ase_index[i]].state,
            ascs.ase[ase_index[i]].cig_cis_info.cis_state);
            retval = GA_FAILURE;
            break;
        }
    }
    APPL_DBG("[APPL][GA][UCS]: << appl_ga_ucs_is_cis_connect_accept_allowed\n");
    return retval;
}

GA_RESULT appl_ga_ucs_is_cis_disconnect_allowed(UINT8 ase_index)
{
    /*
     * Sequence: Client triggered Release
     * 1. Client triggers Release, ASE State is Releasing.
     * 2. Remove ISO Data Path.
     * 3. Receive the Remove ISO Data Path Complete Event.
     * 4. Trigger CIS Disconnect.
     * 5. Receive CIS Disconnect Complete Event.
     * 6. Receive Release Complete.
     *
     * Sequence: Server triggered Release
     * 1. Server triggers Release, ASE State is Releasing.
     * 2. Remove ISO Data Path.
     * 3. Receive the Remove ISO Data Path Complete Event.
     * 4. Receive CIS Disconnect Complete Event.
     * 6. Send Release Complete.
     */

    UINT8  ase_index_using_same_cis;

    /* Initialize */
    ase_index_using_same_cis = 0U;

    APPL_DBG("[APPL][GA][UCS]: >> appl_ga_ucs_is_cis_disconnect_allowed\n");
    if ((GA_TRUE == ascs.ase[ase_index].is_release_initiated)
        &&
        (GA_ASE_STATE_RELEASING == ascs.ase[ase_index].state)
        &&
        (CIS_STATE_CONNECTED == ascs.ase[ase_index].cig_cis_info.cis_state))
    {
        /*
         * If Bidirectional, fetch the ASE Index which is using
         * same CIG & CIS
         */
        if (GA_TRUE == appl_ga_ucs_get_cig_cis_shared_bidirectional_ase_index
                       (
                           ase_index, &ase_index_using_same_cis
                       ))
        {
            /*
             * Validate if ISO data path is removed for shared ASE
             * and CIS is still connected
             */
            if ((AUDIO_ISO_IDLE == ascs.ase[ase_index_using_same_cis].iso_state)
                &&
                (CIS_STATE_CONNECTED ==
                    ascs.ase[ase_index_using_same_cis].cig_cis_info.cis_state))
            {
                return GA_SUCCESS;
            }
            else
            {
                APPL_DBG
                (
                    "ISO Data path is not removed yet for shared ASE ID: 0x%02X\n",
                    ascs.ase[ase_index_using_same_cis].id
                );
            }
        }
        else
        {
            return GA_SUCCESS;
        }
    }

    APPL_DBG("CIS Disconnect Not Allowed, ASE State: (0x%02X) CIS State: (0x%02X) !",
        ascs.ase[ase_index].state,
        ascs.ase[ase_index].cig_cis_info.cis_state);

    APPL_DBG("[APPL][GA][UCS]: << appl_ga_ucs_is_cis_disconnect_allowed\n");
    return GA_FAILURE;
}

GA_RESULT appl_ga_ucs_accept_cis(UINT16 cis_conn_handle)
{
    GA_RESULT  retval;

    APPL_DBG("[APPL][GA][UCS]: >> appl_ga_ucs_accept_cis\n");
    retval = BT_hci_le_accept_cis_request(cis_conn_handle);

    APPL_DBG("[APPL][GA][UCS]: << appl_ga_ucs_accept_cis\n");
    return retval;
}

GA_RESULT appl_ga_ucs_reject_cis(UINT16 cis_conn_handle, UCHAR reason)
{
    GA_RESULT  retval;

    APPL_DBG("[APPL][GA][UCS]: >> appl_ga_ucs_reject_cis\n");
    retval = BT_hci_le_reject_cis_request(cis_conn_handle, reason);

    APPL_DBG("[APPL][GA][UCS]: << appl_ga_ucs_reject_cis\n");
    return retval;
}

GA_RESULT appl_ga_ucs_validate_ase_cp
          (
              UINT8         ase_index,
              void        * data,
              UINT8         event
          )
{
    GA_RESULT retval;

    /* Initialize */
    retval = GA_SUCCESS;

    APPL_DBG("[APPL][GA][UCS]: >> appl_ga_ucs_validate_ase_cp\n");

    /* If the event is GA_SEP_CONFIGURE_IND, Validate the params */
    if (GA_SEP_CONFIGURE_IND == event)
    {
        /* TODO: Add check if it is only for LC3 */
        retval = appl_ga_ucs_validate_ase_cp_codec_cfg_for_lc3
                 (
                     ase_index,
                     (GA_LC3_CODEC_SPECIFIC_CONF *)data
                 );
    }
    /* If the event is GA_SEP_SETUP_IND, Validate the params */
    else if (GA_SEP_SETUP_IND == event)
    {
        retval = appl_ga_ucs_validate_ase_cp_qos_cfg_for_lc3
                 (
                     ase_index,
                     (GA_QOS_CONF *)data
                 );
    }
    /*
     * If the event is GA_SEP_START_IND or GA_SEP_UPDATE_IND,
     * Validate the params
     */
    else if ((GA_SEP_START_IND == event) || (GA_SEP_UPDATE_IND == event))
    {
        if (GA_SEP_START_IND == event)
        {
            /*
             * Validate below:
             * Src:
             * If LC3 is already configured and streaming,
             * Validate the Stream Configurations, Channel Count and
             * Audio Channel Allocation to be the same set or a subset of the
             * existing set.
             * If yes, Allow else do not.
             * Snk:
             * If LC3 is already configured and streaming,
             * Do not allow.
             */

            if ((GA_ROLE_SOURCE == ascs.ase[ase_index].role) &&
                GA_SUCCESS != appl_ga_utils_audio_src_audio_lc3_enc_allowed
                              (
                                  ascs.ase[ase_index].cs_conf
                              ))
            {
                /* Do not accept */
                APPL_ERR("LC3 Encoder not allowed 0x%02X !\n", ascs.ase[ase_index].id);
                retval = GA_SEP_RSP_INSUFFICIENT_RESOURCES;
            }
            else if ((GA_ROLE_SINK == ascs.ase[ase_index].role) &&
                (GA_SUCCESS != appl_ga_utils_audio_snk_audio_lc3_dec_allowed
                               (
                                   ascs.ase[ase_index].cs_conf
                               )))
            {
                /* Do not accept */
                APPL_ERR("LC3 Decoder not allowed  0x%02X !\n", ascs.ase[ase_index].id);
                retval = GA_SEP_RSP_INSUFFICIENT_RESOURCES;
            }
        }

        if (GA_SUCCESS == retval)
        {
            retval = appl_ga_ucs_validate_ase_cp_metadata
                     (
                         ase_index,
                         (GA_METADATA*)data
                     );
        }
    }

    APPL_DBG("[APPL][GA][UCS]: << appl_ga_ucs_validate_ase_cp\n");
    return retval;
}

GA_RESULT appl_ga_ucs_validate_ase_cp_codec_cfg_for_lc3
          (
              UINT8                        ase_index,
              GA_LC3_CODEC_SPECIFIC_CONF * csc
          )
{
    UINT8     index, i;
    UINT8     cap_count;

    UINT8     reason;
    GA_RESULT retval;
    PACS_CAP_INFO pacs;

    /* Initialize */
    retval = GA_FAILURE;
    reason = GA_SEP_RSP_RSN_NONE;

    APPL_DBG("[APPL][GA][UCS]: >> appl_ga_ucs_validate_ase_cp_codec_cfg_for_lc3\n");

    /*
     * The server has not exposed the requested configuration in any PAC
     * record as defined. Reason: 0x06 = Unsupported Audio Capabilities.
     * Refer ASCS_v1.0, Page 27.
     */

    /* Fetch the Local PACS Record */
    appl_ga_utils_bap_fetch_local_pacs(&pacs);

    /* Validate if this is the same SET ID requested during Config Codec */
    if (GA_ROLE_SOURCE == ascs.ase[ase_index].role)
    {
        cap_count = pacs.pacs_src_cap_count;
        for (index = 0U; index < cap_count; index++)
        {
            for (i = 0U; i < pacs.pacs_src_cap[index].cap_count_per_instance; i++)
            {
                /* Validate if the CS Conf exists in our Local Cap */
                if (GA_AUDIO_CODING_LC3 == pacs.pacs_src_cap[index].cap[i].codec.coding_format)
                {
                    /* TODO: Make the below check as Macro */
                    /* Validate all fields, SF, FD */
                    if (((1U << (csc->sf - 1U)) ==
                        (pacs.pacs_src_cap[index].lc3_cs_cap[i].supported_sf & (1U << (csc->sf - 1U))))
                        &&
                        ((1U << csc->fd) ==
                            (pacs.pacs_src_cap[index].lc3_cs_cap[i].supported_fd & (1U << csc->fd))))
                    {
                        /* TODO: Validate other fields too */
                        retval = GA_SUCCESS;
                        break;
                    }
                }
            }
        }
    }
    else if (GA_ROLE_SINK == ascs.ase[ase_index].role)
    {
        cap_count = pacs.pacs_snk_cap_count;
        for (index = 0U; index < cap_count; index++)
        {
            for (i = 0U; i < pacs.pacs_snk_cap[index].cap_count_per_instance; i++)
            {
                /* Validate if the CS Conf exists in our Local Cap */
                if (GA_AUDIO_CODING_LC3 == pacs.pacs_snk_cap[index].cap[i].codec.coding_format)
                {
                    /* Validate all fields, SF, FD */
                    if (((1U << (csc->sf - 1U)) ==
                        (pacs.pacs_snk_cap[index].lc3_cs_cap[i].supported_sf & (1U << (csc->sf - 1U))))
                        &&
                        ((1U << csc->fd) ==
                            (pacs.pacs_snk_cap[index].lc3_cs_cap[i].supported_fd & (1U << csc->fd))))
                    {
                        /* TODO: Validate other fields too */
                        retval = GA_SUCCESS;
                        break;
                    }
                }
            }
        }
    }

    if (GA_SUCCESS != retval)
    {
        /* Reset first before reusing */
        retval = GA_SUCCESS;
        /* Codec Specific Conf */
        reason = GA_SEP_RSP_RSN_CODEC_SPECIFIC_CONFIG;
        retval = reason;
        retval = (retval << 8U);
        retval |= GA_SEP_RSP_UNSUPP_CONFIG_PARAM_VAL;
    }

    APPL_DBG("[APPL][GA][UCS]: << appl_ga_ucs_validate_ase_cp_codec_cfg_for_lc3\n");
    return retval;
}

GA_RESULT appl_ga_ucs_validate_ase_cp_qos_cfg_for_lc3
          (
              UINT8         ase_index,
              GA_QOS_CONF * qos_conf
          )
{
    UINT8     reason;
    UINT8     response;
    GA_RESULT retval;

    /* Initialize */
    retval = GA_SUCCESS;
    reason = GA_SEP_RSP_RSN_NONE;
    response = GA_SEP_RSP_SUCCESS;

    APPL_DBG("[APPL][GA][UCS]: >> appl_ga_ucs_validate_ase_cp_qos_cfg_for_lc3\n");

    /*
     * Validate the CIG_ID and CIS_ID parameter.
     * If a client requests a Config QoS operation for an ASE that would result
     * in more than one Sink ASE having identical CIG_ID and CIS_ID parameter
     * values for that client, or that would result in more than one Source ASE
     * having identical CIG_ID and CIS_ID parameter values for that client
     * Refer ASCS_v1.0, Page 31.
     */
    /* Validate if the same combination already exists */
    if (GA_SUCCESS == app_ga_ucs_bap_cig_cis_exists
                      (
                          ase_index,
                          qos_conf->channel.cig_id,
                          qos_conf->channel.cis_id
                      ))
    {
        response = GA_SEP_RSP_INVALID_CONFIG_PARAM_VAL;
        reason = GA_SEP_RSP_RSN_INVALID_ASE_CIS_MAPPING;
    }

    /*
     * If a client initiated an ASE Control operation with parameter value[0],
     * parameter value[1], and parameter value[2], and if parameter value[1]
     * and parameter value[2] were in error, then the server would use the
     * Response_Code and Reason values applicable to parameter value[1].
     * Refer ASCS_v1.0, Page 26.
     */

    /* Validate if the config is not supported */
    if (GA_TRUE != app_ga_ucs_is_config_supp(&reason))
    {
        response = GA_SEP_RSP_UNSUPP_CONFIG_PARAM_VAL;
    }

    /* Validate if the config is invalid */
    if (GA_TRUE != app_ga_ucs_bap_is_config_valid(&reason))
    {
        response = GA_SEP_RSP_REJECTED_CONFIG_PARAM_VAL;
    }

    /* Validate if the config is to be rejected */
    if (GA_FALSE == app_ga_ucs_bap_is_config_to_be_rejected(&reason))
    {
        response = GA_SEP_RSP_INVALID_CONFIG_PARAM_VAL;
    }

    if (GA_SEP_RSP_RSN_NONE != reason)
    {
        /* Reset first before reusing */
        retval = GA_SUCCESS;
        retval = reason;
        retval = (retval << 8U);
        retval |= response;
    }

    APPL_DBG("[APPL][GA][UCS]: << appl_ga_ucs_validate_ase_cp_qos_cfg_for_lc3\n");
    return retval;
}

UINT8 app_ga_ucs_is_config_supp(UINT8 * reason)
{
    GA_IGNORE_UNUSED_PARAM(reason);

    APPL_DBG("[APPL][GA][UCS]: >> app_ga_ucs_is_config_supp\n");

    APPL_DBG("[APPL][GA][UCS]: << app_ga_ucs_is_config_supp\n");
    return GA_TRUE;
}

UINT8 app_ga_ucs_bap_is_config_valid(UINT8 * reason)
{
    GA_IGNORE_UNUSED_PARAM(reason);

    APPL_DBG("[APPL][GA][UCS]: >> app_ga_ucs_bap_is_config_valid\n");

    APPL_DBG("[APPL][GA][UCS]: << app_ga_ucs_bap_is_config_valid\n");
    return GA_TRUE;
}

UINT8 app_ga_ucs_bap_is_config_to_be_rejected(UINT8 * reason)
{
    GA_IGNORE_UNUSED_PARAM(reason);

    APPL_DBG("[APPL][GA][UCS]: >> app_ga_ucs_bap_is_config_to_be_rejected\n");

    APPL_DBG("[APPL][GA][UCS]: >> app_ga_ucs_bap_is_config_to_be_rejected\n");
    return GA_FALSE;
}

GA_RESULT app_ga_ucs_bap_cig_cis_exists
          (
              UINT8 ase_index,
              UINT8 cig_id,
              UINT8 cis_id
          )
{
    GA_RESULT  retval;
    UINT8      index;

    /* Initialize */
    retval = GA_FAILURE;
    index = 0U;

    APPL_DBG("[APPL][GA][UCS]: >> app_ga_ucs_bap_cig_cis_exists\n");
    /*
     * Validate the CIG_ID and CIS_ID parameter.
     * If a client requests a Config QoS operation for an ASE that would result
     * in more than one Sink ASE having identical CIG_ID and CIS_ID parameter
     * values for that client, or that would result in more than one Source ASE
     * having identical CIG_ID and CIS_ID parameter values for that client
     * Refer ASCS_v1.0, Page 31.
     */
    for (index = 0U; index < ascs.ase_count; index++)
    {
        if ((cig_id == ascs.ase[index].qos_conf.channel.cig_id) &&
            (cis_id == ascs.ase[index].qos_conf.channel.cis_id) &&
            (ascs.ase[ase_index].role == ascs.ase[index].role) &&
            (ase_index != index))
        {
            retval = GA_SUCCESS;
            break;
        }
    }

    APPL_DBG("[APPL][GA][UCS]: << app_ga_ucs_bap_cig_cis_exists\n");
    return retval;
}

GA_RESULT appl_ga_ucs_validate_ase_cp_metadata
          (
              UINT8         ase_index,
              GA_METADATA * metadata
          )
{
    UINT8          reason;
    UINT8          response;
    GA_RESULT      retval;

    retval = GA_SUCCESS;
    response = GA_SEP_RSP_SUCCESS;
    reason = GA_SEP_RSP_RSN_NONE;

    if (0U == metadata->length)
    {
        response = GA_SEP_RSP_INSUFFICIENT_RESOURCES;
        reason = 0x00U;
    }
    /* Validate for Reason: Unsopprted/Invalid Metadata */
    if ((GA_SEP_RSP_SUCCESS == response) &&
        (GA_TRUE == appl_ga_ucs_is_metadata_unsupp_and_invalid
                    (
                        metadata,
                        &reason,
                        &response
                    )))
    {
        /* Do Nothing as response and reason are already updated */
    }
    /* Validate for Reason: Rejected Metadata/Unspecified Error */
    if ((GA_SEP_RSP_SUCCESS == response) &&
        (GA_TRUE == appl_ga_ucs_is_metadata_rejected_and_unspecified
                    (
                        ase_index,
                        metadata,
                        GA_LTV_METADATA_STREAMING_AC_TYPE,
                        &reason,
                        &response
                    )))
    {
        /* Do Nothing as response and reason are already updated */
    }

    if (GA_SEP_RSP_RSN_NONE != reason)
    {
        /* Reset first before reusing */
        retval = GA_SUCCESS;
        retval = reason;
        retval = (retval << 8U);
        retval |= response;
    }

    return retval;
}

UINT8 appl_ga_ucs_is_metadata_unsupp_and_invalid
      (
          GA_METADATA * metadata,
          UINT8       * reason,
          UINT8       * response
      )
{
    UINT8 retval;
    UINT8 marker;
    UINT8 len;
    UINT8 type;

    /* Initialize */
    retval = GA_FALSE;
    marker = 0U;
    len = 0U;
    type = 0U;

    APPL_DBG("[APPL][GA][UCS]: >> appl_ga_ucs_is_metadata_unsupp_and_invalid\n");

    if ((0U != metadata->length) && (NULL != metadata))
    {
        while (marker < metadata->length)
        {
            /* Extract the Length: LTV - Type(1B) + Value(nB) */
            len = metadata->data[marker];
            marker++;

            /* Extract the Type */
            type = metadata->data[marker];
            marker++;

            if (GA_LTV_METADATA_PREF_AC_TYPE == type)
            {
                if ((GA_LTV_METADATA_PREF_AC_LEN - 1U) == len)
                {
                    marker += (GA_LTV_METADATA_PREF_AC_LEN - 1U);
                }
                else
                {
                    *response = GA_SEP_RSP_INVALID_METADATA;
                    *reason = GA_LTV_METADATA_PREF_AC_TYPE;
                    retval = GA_TRUE;
                    break;
                }
            }
            else if (GA_LTV_METADATA_STREAMING_AC_TYPE == type)
            {
                if (GA_LTV_METADATA_STREAMING_AC_LEN == len)
                {
                    marker += (GA_LTV_METADATA_STREAMING_AC_LEN - 1U);
                }
                else
                {
                    *response = GA_SEP_RSP_INVALID_METADATA;
                    *reason = GA_LTV_METADATA_STREAMING_AC_TYPE;
                    retval = GA_TRUE;
                    break;
                }
            }
            else if (GA_LTV_METADATA_PGM_INFO_TYPE == type)
            {
                /*
                 * Validate by checking if the (Total Length - Parsed Length)
                 * is atleast minimum of the Length expected for this Metadata
                 * Type.
                 */
                if ((metadata->length - marker) < (len - 1U))
                {
                    *response = GA_SEP_RSP_INVALID_METADATA;
                    *reason = GA_LTV_METADATA_PGM_INFO_TYPE;
                    retval = GA_TRUE;
                    break;
                }
                marker += (len - 1U);
            }
            else if (GA_LTV_METADATA_LANGUAGE_TYPE == type)
            {
                if (GA_LTV_METADATA_LANGUAGE_LEN == len)
                {
                    marker += (GA_LTV_METADATA_LANGUAGE_LEN - 1U);
                }
                else
                {
                    *response = GA_SEP_RSP_INVALID_METADATA;
                    *reason = GA_LTV_METADATA_LANGUAGE_TYPE;
                    retval = GA_TRUE;
                    break;
                }
            }
            else if (GA_LTV_METADATA_CCID_LIST_TYPE == type)
            {
                /*
                 * Validate by checking if the (Total Length - Parsed Length)
                 * is atleast minimum of the Length expected for this Metadata
                 * Type.
                 */
                if ((metadata->length - marker) < (len - 1U))
                {
                    *response = GA_SEP_RSP_INVALID_METADATA;
                    *reason = GA_LTV_METADATA_CCID_LIST_TYPE;
                    retval = GA_TRUE;
                    break;
                }
                marker += (len - 1U);
            }
            else if (GA_LTV_METADATA_PARENTAL_RATING_TYPE == type)
            {
                if (GA_LTV_METADATA_PARENTAL_RATING_LEN == len)
                {
                    marker += (GA_LTV_METADATA_PARENTAL_RATING_LEN - 1U);
                }
                else
                {
                    *response = GA_SEP_RSP_INVALID_METADATA;
                    *reason = GA_LTV_METADATA_PARENTAL_RATING_TYPE;
                    retval = GA_TRUE;
                    break;
                }
            }
            else if (GA_LTV_METADATA_PROGRAM_INFO_URL_TYPE == type)
            {
                /*
                 * Validate by checking if the (Total Length - Parsed Length)
                 * is atleast minimum of the Length expected for this Metadata
                 * Type.
                 */
                if ((metadata->length - marker) < (len - 1U))
                {
                    *response = GA_SEP_RSP_INVALID_METADATA;
                    *reason = GA_LTV_METADATA_PROGRAM_INFO_URL_TYPE;
                    retval = GA_TRUE;
                    break;
                }
                marker += (len - 1U);
            }
            else if (GA_LTV_METADATA_EM_TYPE == type)
            {
                /*
                 * Validate by checking if the (Total Length - Parsed Length)
                 * is atleast minimum of the Length expected for this Metadata
                 * Type.
                 */
                if ((metadata->length - marker) < (len - 1U))
                {
                    *response = GA_SEP_RSP_INVALID_METADATA;
                    *reason = GA_LTV_METADATA_EM_TYPE;
                    retval = GA_TRUE;
                    break;
                }
                marker += (len - 1U);
            }
            else if (GA_LTV_METADATA_VS_TYPE == type)
            {
                /*
                 * Validate by checking if the (Total Length - Parsed Length)
                 * is atleast minimum of the Length expected for this Metadata
                 * Type.
                 */
                if ((metadata->length - marker) < (len - 1U))
                {
                    *response = GA_SEP_RSP_INVALID_METADATA;
                    *reason = GA_LTV_METADATA_VS_TYPE;
                    retval = GA_TRUE;
                    break;
                }
                marker += (len - 1U);
            }
            else
            {
                *response = GA_SEP_RSP_UNSUPP_METADATA;
                *reason = type;
                retval = GA_TRUE;
                break;
            }
        }
    }

    APPL_DBG("[APPL][GA][UCS]: << appl_ga_ucs_is_metadata_unsupp_and_invalid\n");

    return retval;
}

UINT8 appl_ga_ucs_is_metadata_rejected_and_unspecified
      (
          UINT8         ase_index,
          GA_METADATA * metadata,
          UINT8         metadata_type,
          UINT8       * reason,
          UINT8       * response
      )
{
    UINT8   retval;
    UINT8   marker;
    UINT8   len;
    UINT8   type;
    UINT16  streaming_audio_ctx;
    PACS_CAP_INFO  local_pacs_info;

    /* Initialize */
    retval = GA_FALSE;
    marker = 0U;
    len = 0U;
    type = 0U;
    streaming_audio_ctx = 0U;

    APPL_DBG("[APPL][GA][UCS]: >> appl_ga_ucs_is_metadata_rejected_and_unspecified\n");

    if ((0U != metadata->length) && (NULL != metadata))
    {
        while (marker < metadata->length)
        {
            /* Extract the Length */
            len = metadata->data[marker];
            marker++;

            /* Extract the Type */
            type = metadata->data[marker];
            marker++;

            if (GA_LTV_METADATA_PREF_AC_TYPE == type)
            {
                if (GA_LTV_METADATA_PREF_AC_TYPE == metadata_type)
                {
                    /* Do Nothing */
                }
                else
                {
                    marker += (GA_LTV_METADATA_PREF_AC_LEN - 1U);
                }
            }
            else if (GA_LTV_METADATA_STREAMING_AC_TYPE == type)
            {
                if (GA_LTV_METADATA_STREAMING_AC_TYPE == metadata_type)
                {
                    appl_ga_utils_bap_fetch_local_pacs(&local_pacs_info);
                    /*
                     * If an Acceptor is not available for the requested set of Context
                     * Type values, then it shall return a response code of
                     * "Rejected Metadata" and set the Reason to the value of the Type
                     * identifier of Streaming_Audio_Contexts Metadata LTV structure.
                     * Refer CAP_v1.0 spec (Page 35 for Update Metadata)
                     * Refer CAP_v1.0 spec (Page 34 for Enable)
                     */
                    GA_UNPACK_LE_2_BYTE(&streaming_audio_ctx, &metadata->data[marker]);
                    if (GA_ROLE_SINK == ascs.ase[ase_index].role)
                    {
                        if (GA_CONTEXT_TYPE_UNSPECIFIED == streaming_audio_ctx)
                        {
                            /* No action, Allow this */
                        }
                        else if ((streaming_audio_ctx !=
                            (local_pacs_info.record.avail_sink_contexts & streaming_audio_ctx)) ||
                            (GA_CONTEXT_TYPE_PROHIBITED == streaming_audio_ctx))
                        {
                            *response = GA_SEP_RSP_REJECTED_METADATA;
                            *reason = GA_LTV_METADATA_STREAMING_AC_TYPE;
                            retval = GA_TRUE;
                            break;
                        }
                    }
                    else if (GA_ROLE_SOURCE == ascs.ase[ase_index].role)
                    {
                        if (GA_CONTEXT_TYPE_UNSPECIFIED == streaming_audio_ctx)
                        {
                            /* No action, Allow this */
                        }
                        else if ((streaming_audio_ctx !=
                            (local_pacs_info.record.avail_src_contexts & streaming_audio_ctx)) ||
                            (GA_CONTEXT_TYPE_PROHIBITED == streaming_audio_ctx))
                        {
                            *response = GA_SEP_RSP_REJECTED_METADATA;
                            *reason = GA_LTV_METADATA_STREAMING_AC_TYPE;
                            retval = GA_TRUE;
                            break;
                        }
                    }
                    else
                    {
                        /* Should not reach here */
                        /* TODO: Check */
                        *response = GA_SEP_RSP_UNSPECIFIED_ERROR;
                        *reason = 0x00U;
                        retval = GA_TRUE;
                        break;
                    }
                    marker += (GA_LTV_METADATA_STREAMING_AC_LEN - 1U);
                }
                else
                {
                    marker += (GA_LTV_METADATA_STREAMING_AC_LEN - 1U);
                }
            }
            else if (GA_LTV_METADATA_PGM_INFO_TYPE == type)
            {
                if (GA_LTV_METADATA_PGM_INFO_TYPE == metadata_type)
                {
                    /* Do Nothing */
                }
                else
                {
                    marker += (len - 1U);
                }
            }
            else if (GA_LTV_METADATA_LANGUAGE_TYPE == type)
            {
                if (GA_LTV_METADATA_LANGUAGE_TYPE == metadata_type)
                {
                    /* Do Nothing */
                }
                else
                {
                    marker += (GA_LTV_METADATA_LANGUAGE_LEN - 1U);
                }
            }
            else if (GA_LTV_METADATA_CCID_LIST_TYPE == type)
            {
                if (GA_LTV_METADATA_CCID_LIST_TYPE == metadata_type)
                {
                    /* Do Nothing */
                }
                else
                {
                    marker += (len - 1U);
                }
            }
            else if (GA_LTV_METADATA_PARENTAL_RATING_TYPE == type)
            {
                if (GA_LTV_METADATA_PARENTAL_RATING_TYPE == metadata_type)
                {
                    /* Do Nothing */
                }
                else
                {
                    marker += (GA_LTV_METADATA_PARENTAL_RATING_LEN - 1U);
                }
            }
            else if (GA_LTV_METADATA_PROGRAM_INFO_URL_TYPE == type)
            {
                if (GA_LTV_METADATA_PROGRAM_INFO_URL_TYPE == metadata_type)
                {
                    /* Do Nothing */
                }
                else
                {
                    marker += (len - 1U);
                }
            }
            else if (GA_LTV_METADATA_EM_TYPE == type)
            {
                if (GA_LTV_METADATA_EM_TYPE == metadata_type)
                {
                    /* Do Nothing */
                }
                else
                {
                    marker += (len - 1U);
                }
            }
            else if (GA_LTV_METADATA_VS_TYPE == type)
            {
                if (GA_LTV_METADATA_VS_TYPE == metadata_type)
                {
                    /* Do Nothing */
                }
                else
                {
                    marker += (len - 1U);
                }
            }
            else
            {
                /*
                 * TODO: Already handled in
                 * appl_ga_ucs_is_metadata_unsupp_and_invalid(),
                 * Check if we can remove?
                 */
                *response = GA_SEP_RSP_UNSUPP_METADATA;
                *reason = type;
                retval = GA_TRUE;
                break;
            }
        }
    }

    APPL_DBG("[APPL][GA][UCS]: << appl_ga_ucs_is_metadata_rejected_and_unspecified\n");

    return retval;
}

GA_RESULT appl_ga_ucs_is_release_complete_allowed(UINT8 ase_index)
{
    GA_RESULT  retval;

    /* Initialize */
    retval = GA_FAILURE;

    APPL_DBG("[APPL][GA][UCS]: >> appl_ga_ucs_is_release_complete_allowed\n");
    if ((GA_TRUE == ascs.ase[ase_index].is_release_initiated)
        &&
        (GA_ASE_STATE_RELEASING == ascs.ase[ase_index].state))
    {
        if ((AUDIO_ISO_IDLE == ascs.ase[ase_index].iso_state) &&
            ((CIS_STATE_IDLE == ascs.ase[ase_index].cig_cis_info.cis_state) ||
             (CIS_STATE_INITIALIZED == ascs.ase[ase_index].cig_cis_info.cis_state)))
        {
            /*
             * Trigger Release Complete when Server has initiated Auto Release.
             *
             * 1. Trigger Auto Release.
             * 2. Trigger ISO Remove.
             * 3. On receiving ISO Remove Complete event, Trigger Terminate CIS .
             * 4. On receiving CIS Disconnect Complete event, Trigger Release Complete.
             */
            return GA_SUCCESS;
        }
    }
    else if ((GA_FALSE == ascs.ase[ase_index].is_release_initiated)
             &&
              (GA_ASE_STATE_RELEASING == ascs.ase[ase_index].state))
    {
        if (AUDIO_ISO_IDLE == ascs.ase[ase_index].iso_state)
        {
            /*
             * Trigger Release Complete when Client has initiated Release.
             *
             * 1. On receiving GA_SEP_RELEASE_IND, Trigger ISO Remove.
             * 2. On receiving ISO Remove Complete event, Trigger Release Complete.
             */
            return GA_SUCCESS;
        }
    }

    APPL_DBG("Release Complete Not Allowed, ASE State: (0x%02X) ISO State: (0x%02X) !",
        ascs.ase[ase_index].state,
        ascs.ase[ase_index].iso_state);

    APPL_DBG("[APPL][GA][UCS]: << appl_ga_ucs_is_release_complete_allowed\n");
    return retval;
}

GA_RESULT appl_ga_ucs_src_get_csc_conf_aca_from_pacs_sacc
          (
              GA_LC3_CODEC_SPECIFIC_CONF * csc
          )
{
    GA_RESULT      retval;
    PACS_CAP_INFO  pacs;
    UINT8          cap_count_index;
    UINT8          cap_count_per_instance_index;

    retval = GA_SUCCESS;
    /* TODO: Fetch the capability index and Record index */
    cap_count_index = 0U;
    cap_count_per_instance_index = 0U;

    if (NULL == csc)
    {
        return GA_FAILURE;
    }

    /* Fetch the Local PACS Record */
    appl_ga_utils_bap_fetch_local_pacs(&pacs);

    if (GA_AUDIO_LOCATION_NOT_ALLOWED == csc->aca)
    {
        /*
         * For ASE Role Source, UCC might not set
         * Audio Channel Allocation value in csc conf during ASECP
         * Config Codec operation. Check for supported Channel
         * Count (sacc) in PAC record and set ACA based on that.
         */
        if (pacs.pacs_src_cap[cap_count_index].lc3_cs_cap[cap_count_per_instance_index].supported_acc ==
            (pacs.pacs_src_cap[cap_count_index].lc3_cs_cap[cap_count_per_instance_index].supported_acc & (1U << 0U)))
        {
            /* It means SACC = 1. Set ACA to FL. */
            /*
             * TODO: It can be any other value based on
             * Source Audio Location in PAC record.
             */
            csc->aca = GA_AUDIO_LOCATION_FL;
        }
        else if (pacs.pacs_src_cap[cap_count_index].lc3_cs_cap[cap_count_per_instance_index].supported_acc ==
                 (pacs.pacs_src_cap[cap_count_index].lc3_cs_cap[cap_count_per_instance_index].supported_acc & (1U << 1U)))
        {
            /* It means SACC = 2. Set ACA to FL|FR. */
            /*
             * TODO: It can be any other value based on
             * Source Audio Location in PAC record.
             */
            csc->aca = GA_AUDIO_LOCATION_FL | GA_AUDIO_LOCATION_FR;
        }
        else
        {
            retval = GA_FAILURE;
        }
    }

    return retval;
}

GA_RESULT appl_ga_ucs_snk_get_csc_conf_aca_from_pacs_sacc
          (
              GA_LC3_CODEC_SPECIFIC_CONF * csc
          )
{
    GA_RESULT      retval;
    PACS_CAP_INFO  pacs;
    UINT8          cap_count_index;
    UINT8          cap_count_per_instance_index;

    retval = GA_SUCCESS;
    /* TODO: Fetch the capability index and Record index */
    cap_count_index = 0U;
    cap_count_per_instance_index = 0U;

    if (NULL == csc)
    {
        return GA_FAILURE;
    }

    /* Fetch the Local PACS Record */
    appl_ga_utils_bap_fetch_local_pacs(&pacs);

    if (GA_AUDIO_LOCATION_NOT_ALLOWED == csc->aca)
    {
        /*
         * For ASE Role Sink, UCC might not set
         * Audio Channel Allocation value in csc conf during ASECP
         * Config Codec operation. Check for supported Channel
         * Count (sacc) in PAC record and set ACA based on that.
         */
        if (pacs.pacs_snk_cap[cap_count_index].lc3_cs_cap[cap_count_per_instance_index].supported_acc ==
            (pacs.pacs_snk_cap[cap_count_index].lc3_cs_cap[cap_count_per_instance_index].supported_acc & (1U << 0U)))
        {
            /* It means SACC = 1. Set ACA to FL. */
            /*
             * TODO: It can be any other value based on
             * Sink Audio Location in PAC record.
             */
            csc->aca = GA_AUDIO_LOCATION_FL;
        }
        else if (pacs.pacs_snk_cap[cap_count_index].lc3_cs_cap[cap_count_per_instance_index].supported_acc ==
                 (pacs.pacs_snk_cap[cap_count_index].lc3_cs_cap[cap_count_per_instance_index].supported_acc & (1U << 1U)))
        {
            /* It means SACC = 2. Set ACA to FL|FR. */
            /*
             * TODO: It can be any other value based on
             * Sink Audio Location in PAC record.
             */
            csc->aca = GA_AUDIO_LOCATION_FL | GA_AUDIO_LOCATION_FR;
        }
        else
        {
            retval = GA_FAILURE;
        }
    }

    return retval;
}

UINT8 appl_ga_ucs_get_cig_cis_shared_bidirectional_ase_index
      (
          UINT8   ase_index,
          UINT8 * ase_index_using_same_cis
      )
{
    UINT8 index;

    index = 0U;

    APPL_DBG("[APPL][GA][UCC]: >> appl_ga_ucs_get_cig_cis_shared_bidirectional_ase_index\n");

    for (index = 0U; index < MAX_UC_ASE; index++)
    {
        /* Skip the ase_index given and compare with the other ASEs */
        if ((ase_index != index)
            &&
            (ascs.ase[ase_index].qos_conf.channel.cig_id ==
                ascs.ase[index].qos_conf.channel.cig_id)
            &&
            (ascs.ase[ase_index].qos_conf.channel.cis_id ==
                ascs.ase[index].qos_conf.channel.cis_id))
        {
            /*
             * For the given device, CIG and CIS is shared by more than 1 ASE.
             * Bidirectional CIS.
             */
            *ase_index_using_same_cis = index;
            return GA_TRUE;
        }
    }

    APPL_DBG("[APPL][GA][UCC]: << appl_ga_ucs_get_cig_cis_shared_bidirectional_ase_index\n");
    return GA_FALSE;
}

void appl_ga_ucs_update_transmitting_audio
     (
         UINT16 cis_handle,
         GA_LC3_CODEC_SPECIFIC_CONF cs_conf,
         UINT8 qos_conf_set_id,
         UINT8 bps,
         UINT8 status
     )
{
    GA_IGNORE_UNUSED_PARAM(cs_conf);
#ifdef AUDIO_SRC_ISO_SUPPORT
    if (GA_SUCCESS == appl_ga_utils_audio_src_update_entry
                      (
                          cis_handle,
                          AUDIO_IGNORE_VALUE,
                          AUDIO_IGNORE_VALUE,
                          status
                      ))
    {
#ifdef AUDIO_SRC_LC3_SUPPORT
        if (GA_TRUE == status)
        {
            if (GA_SUCCESS == appl_ga_utils_audio_src_create_lc3_encoder
                              (
                                  cs_conf,
                                  qos_conf_set_id,
                                  bps
                              ))
            {
                APPL_TRC("[APPL][GA][UCS][SRC]: LC3 Encoder Setup Status: Created\n");
            }
            else
            {
                APPL_ERR("[APPL][GA][UCS][SRC]: LC3 Encoder Setup Status: Could not create !\n");
            }
        }
        else if (GA_FALSE == status)
        {
            if (GA_TRUE == appl_ga_utils_audio_src_is_lc3_encoder_running())
            {
                if (GA_SUCCESS == appl_ga_utils_audio_src_delete_lc3_encoder())
                {
                    APPL_TRC("[APPL][GA][UCS][SRC]: LC3 Encoder Setup Status: Deleted\n");
                }
                else
                {
                    APPL_ERR("[APPL][GA][UCS][SRC]: LC3 Encoder Setup Status: Could not delete !\n");
                }
            }
            else
            {
                APPL_TRC("[APPL][GA][UCS][SRC]: LC3 Encoder Setup Status: Already Deleted\n");
            }
        }
#else /* AUDIO_SRC_LC3_SUPPORT */
        APPL_ERR("AUDIO_SRC_LC3_SUPPORT is not enabled !\n");
#endif /* AUDIO_SRC_LC3_SUPPORT */
#ifdef AUDIO_SRC_PL_SUPPORT
        if (GA_TRUE == status)
        {
            if (GA_SUCCESS == appl_ga_utils_audio_src_setup_generator_pl
                              (
                                  cs_conf,
                                  bps,
                                  AUDIO_SRC_PL_BUFFER_SIZE
                              ))
            {
                APPL_TRC("[APPL][GA][UCS][SRC]: Audio PL Generator Setup Status: Success\n");
            }
            else
            {
                APPL_ERR("[APPL][GA][UCS][SRC]: Audio PL Generator Setup Status: Failed !\n");
            }
            if (GA_SUCCESS == appl_ga_utils_audio_src_start_generator_pl())
            {
                APPL_TRC("[APPL][GA][UCS][SRC]: Audio PL Generator Start Process Status: Success\n");
            }
            else
            {
                APPL_ERR("[APPL][GA][UCS][SRC]: Audio PL Generator Start Process Status: Failed !\n");
            }
        }
        else if (GA_FALSE == status)
        {
            if (GA_TRUE == appl_ga_utils_audio_src_is_generator_pl_running())
            {
                if (GA_SUCCESS == appl_ga_utils_audio_src_stop_generator_pl())
                {
                    APPL_TRC("[APPL][GA][UCS][SRC]: Audio PL Generator Stop Process Status: Success\n");
                }
                else
                {
                    APPL_ERR("[APPL][GA][UCS][SRC]: Audio PL Generator Stop Process Status: Failed !\n");
                }
            }
            else
            {
                APPL_TRC("[APPL][GA][UCS][SRC]: Audio PL Generator Status: Already Stopped\n");
            }
        }
#else /* AUDIO_SRC_PL_SUPPORT */
        APPL_ERR("AUDIO_SRC_PL_SUPPORT is not enabled !\n");
#endif /* AUDIO_SRC_PL_SUPPORT */
    }
    else
    {
        APPL_ERR("[APPL][GA][UCS][SRC]: ISO Data Path Setup Status: Update entry failed !\n");
    }
#else /* AUDIO_SRC_ISO_SUPPORT */
APPL_ERR("AUDIO_SRC_ISO_SUPPORT is not enabled !\n");
#endif /* AUDIO_SRC_ISO_SUPPORT */

    return;
}

void appl_ga_ucs_update_receiving_audio
     (
         UINT16 cis_handle,
         GA_LC3_CODEC_SPECIFIC_CONF cs_conf,
         UINT8 bps,
         UINT8 status
     )
{
#ifdef AUDIO_SNK_ISO_SUPPORT
    if (GA_SUCCESS == appl_ga_utils_audio_snk_update_entry
                      (
                          cis_handle,
                          AUDIO_IGNORE_VALUE,
                          AUDIO_IGNORE_VALUE,
                          status
                      ))
    {
#ifdef AUDIO_SNK_LC3_SUPPORT
        if (GA_TRUE == status)
        {
            if (GA_SUCCESS == appl_ga_utils_audio_snk_create_lc3_decoder
                              (
                                  cs_conf,
                                  bps
                              ))
            {
                APPL_TRC("[APPL][GA][UCS][SNK]: LC3 Decoder Setup Status: Created\n");
            }
            else
            {
                APPL_ERR("[APPL][GA][UCS][SNK]: LC3 Decoder Setup Status: Could not create !\n");
            }
        }
        else if (GA_FALSE == status)
        {
            if (GA_TRUE == appl_ga_utils_audio_snk_is_lc3_decoder_running())
            {
                if (GA_SUCCESS == appl_ga_utils_audio_snk_delete_lc3_decoder())
                {
                    APPL_TRC("[APPL][GA][UCS][SNK]: LC3 Decoder Setup Status: Deleted\n");
                }
                else
                {
                    APPL_ERR("[APPL][GA][UCS][SNK]: LC3 Decoder Setup Status: Could not delete !\n");
                }
            }
            else
            {
                APPL_TRC("[APPL][GA][UCS][SNK]: LC3 Decoder Setup Status: Already Deleted\n");
            }
        }
#else /* AUDIO_SNK_LC3_SUPPORT */
        APPL_ERR("AUDIO_SNK_LC3_SUPPORT is not enabled !\n");
#endif /* AUDIO_SNK_LC3_SUPPORT */
#ifdef AUDIO_SNK_PL_SUPPORT
        if (GA_TRUE == status)
        {
            if (GA_SUCCESS == appl_ga_utils_audio_snk_setup_playback_pl
                              (
                                  cs_conf,
                                  bps,
                                  AUDIO_SNK_PL_BUFFER_SIZE
                              ))
            {
                APPL_TRC("[APPL][GA][UCS][SNK]: Audio PL Playback Setup Status: Success\n");
            }
            else
            {
                APPL_ERR("[APPL][GA][UCS][SNK]: Audio PL Playback Setup Status: Failed !\n");
            }
            if (GA_SUCCESS == appl_ga_utils_audio_snk_start_playback_pl())
            {
                APPL_TRC("[APPL][GA][UCS][SNK]: Audio PL Playback Start Process Status: Success\n");
            }
            else
            {
                APPL_ERR("[APPL][GA][UCS][SNK]: Audio PL Playback Start Process Status: Failed !\n");
            }
        }
        else if (GA_FALSE == status)
        {
            if (GA_TRUE == appl_ga_utils_audio_snk_is_playback_pl_running())
            {
                if (GA_SUCCESS == appl_ga_utils_audio_snk_stop_playback_pl())
                {
                    APPL_TRC("[APPL][GA][UCS][SNK]: Audio PL Playback Stop Process Status: Success\n");
                }
                else
                {
                    APPL_ERR("[APPL][GA][UCS][SNK]: Audio PL Playback Stop Process Status: Failed !\n");
                }
            }
            else
            {
                APPL_TRC("[APPL][GA][UCS][SNK]: Audio PL Playback Status: Already Stopped\n");
            }
        }
#else /* AUDIO_SNK_PL_SUPPORT */
        APPL_ERR("AUDIO_SNK_PL_SUPPORT is not enabled !\n");
#endif /* AUDIO_SNK_PL_SUPPORT */
    }
    else
    {
        APPL_ERR("[APPL][GA][UCS][SNK]: ISO Data Path Setup Status: Update entry failed !\n");
    }
#else /* AUDIO_SNK_ISO_SUPPORT */
APPL_ERR("AUDIO_SNK_ISO_SUPPORT is not enabled !\n");
#endif /* AUDIO_SNK_ISO_SUPPORT */

    return;
}

void appl_ga_ucs_trigger_release_complete_timer_handler
     (
         void  * data,
         UINT16  datalen
     )
{
    APPL_GA_UCS_ASE_RELEASE_COMPLETE_INFO * ase_release_compl_info;

    /* Reset the timer handle to NULL */
    appl_ga_ucs_trigger_release_complete_timer_handle = BT_TIMER_HANDLE_INIT_VAL;

    if ((NULL != data) && (0U != datalen))
    {
        ase_release_compl_info = (APPL_GA_UCS_ASE_RELEASE_COMPLETE_INFO *)data;

        appl_ga_ucs_trigger_release_complete
        (
            &ase_release_compl_info->device,
            ase_release_compl_info->ase_count,
            ase_release_compl_info->ase_index
        );
    }

    return;
}

#endif /* BAP_UCS */
