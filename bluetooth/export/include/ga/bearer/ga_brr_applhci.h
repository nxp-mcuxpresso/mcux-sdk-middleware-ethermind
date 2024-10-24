
/**
*  \file ga_brr_applhci.h
*
*  File description
*/

/*
*  Copyright (C) 2013. Mindtree Ltd.
*  All rights reserved.
*/

#ifndef _H_GA_BRR_APPLHCI
#define _H_GA_BRR_APPLHCI

/* --------------------------------------------- Header File Inclusion */
#include "GA_common.h"
#include "GA_bearer_api.h"

/* --------------------------------------------- Global Definitions */

/* --------------------------------------------- Structures/Data Types */
typedef struct _GA_HCI_ISO_HEADER
{
    /* CIS/BIS connection handle */
    UINT16 conn_handle;

    /* Packet Broadcast Flag */
    UINT8  pb_flag;

    /* Timestamp presence flag */
    UINT8  ts_flag;

    /* ISO Dataload length */
    UINT16 dataload_len;

    /* Timestamp value */
    UINT32 ts;

    /* Sequence Number value */
    UINT16 seqnum;

    /* ISO SDU Length */
    UINT16 sdulen;

    /* ISO packet status */
    UINT8  ps_flag;
} GA_HCI_ISO_HEADER;
/* --------------------------------------------- Macros */

/* --------------------------------------------- Internal Functions */
typedef GA_RESULT (*APPL_HCI_CB) 
                   (
                       UINT8 event_code,
                       UINT8* event_data,
                       UINT8 event_datalen
                   );

GA_RESULT appl_ga_hci_brr_write_scan_enable(UCHAR enable);

GA_RESULT appl_ga_hci_brr_le_set_host_feature
          (
              UCHAR  bit_number,
              UCHAR  bit_value
          );

GA_RESULT appl_ga_hci_brr_get_local_bd_addr
          (
              UCHAR * bd_addr
          );

GA_RESULT appl_ga_hci_brr_le_set_random_address
          (
              UCHAR * bd_addr
          );

GA_RESULT appl_ga_hci_brr_le_set_adv_set_random_address
          (
              UCHAR   advertising_handle,
              UCHAR * random_address
          );

GA_RESULT appl_ga_hci_brr_le_set_adv_params
          (
               UINT16   advertising_interval_min,
               UINT16   advertising_interval_max,
               UCHAR    advertising_type,
               UCHAR    own_addr_type,
               UCHAR    peer_addr_type,
               UCHAR *  peer_addr,
               UCHAR    advertising_channel_map,
               UCHAR    advertising_filter_policy
          );

GA_RESULT appl_ga_hci_brr_le_set_adv_data
          (
              UCHAR   advertising_data_len,
              UCHAR * advertising_data
          );

GA_RESULT appl_ga_hci_brr_le_set_adv_enable
          (
              UCHAR advertising_enable
          );

GA_RESULT appl_ga_hci_brr_le_set_ext_adv_params
           (
              UCHAR   adv_handle,
              UINT16  adv_event_properties,
              UINT32  primary_advertising_interval_min,
              UINT32  primary_advertising_interval_max,
              UCHAR   primary_advertising_channel_map,
              UCHAR   own_address_type,
              UCHAR   peer_address_type,
              UCHAR * peer_address,
              UCHAR   advertising_filter_policy,
              INT8    advertising_tx_power,
              UCHAR   primary_advertising_phy,
              UCHAR   secondary_adv_max_skip,
              UCHAR   secondary_advertising_phy,
              UCHAR   advertising_set_id,
              UCHAR   scan_req_nfy_enable
          );

#ifdef GA_SUPPORT_5_4
GA_RESULT appl_ga_hci_brr_le_set_ext_adv_params_v2
          (
              UCHAR  adv_handle,
              UINT16 adv_event_properties,
              UINT32 primary_advertising_interval_min,
              UINT32 primary_advertising_interval_max,
              UCHAR  primary_advertising_channel_map,
              UCHAR  own_address_type,
              UCHAR  peer_address_type,
              UCHAR * peer_address,
              UCHAR  advertising_filter_policy,
              INT8   advertising_tx_power,
              UCHAR  primary_advertising_phy,
              UCHAR  secondary_adv_max_skip,
              UCHAR  secondary_advertising_phy,
              UCHAR  advertising_set_id,
              UCHAR  scan_req_nfy_enable,
              UCHAR  primary_advertising_phy_options,
              UCHAR  secondary_advertising_phy_options
          );
#endif /* GA_SUPPORT_5_4 */

GA_RESULT appl_ga_hci_brr_le_set_ext_adv_data
          (
              UCHAR   advertising_handle,
              UCHAR   operation,
              UCHAR   frag_pref,
              UCHAR   advertising_data_length,
              UCHAR * advertising_data
          );

GA_RESULT appl_ga_hci_brr_le_set_ext_adv_enable
          (
              UCHAR    enable,
              UCHAR    number_of_sets,
              UCHAR  * advertising_handle,
              UINT16 * duration,
              UCHAR  * max_extd_adv_evts
          );

GA_RESULT appl_ga_hci_brr_le_set_scan_params
          (
               UCHAR    le_scan_type,
               UINT16   le_scan_interval,
               UINT16   le_scan_window,
               UCHAR    own_addr_type,
               UCHAR    scan_filter_policy
          );

GA_RESULT appl_ga_hci_brr_le_set_scan_enable
          (
               UCHAR    le_scan_enable,
               UCHAR    filter_dups
          );

GA_RESULT appl_ga_hci_brr_le_set_ext_scan_params
          (
              UCHAR    own_address_type,
              UCHAR    scanning_filter_policy,
              UCHAR    scanning_phy,
              UCHAR  * scan_type,
              UINT16 * scan_interval,
              UINT16 * scan_window
          );

GA_RESULT appl_ga_hci_brr_le_set_ext_scan_enable
          (
              UCHAR   enable,
              UCHAR   filter_duplicates,
              UINT16  duration,
              UINT16  period
          );

GA_RESULT appl_ga_hci_brr_le_create_connection
          (
              UINT16   le_scan_interval,
              UINT16   le_scan_window,
              UCHAR    initiator_filter_policy,
              UCHAR    peer_address_type,
              UCHAR *  peer_address,
              UCHAR    own_address_type,
              UINT16   conn_interval_min,
              UINT16   conn_interval_max,
              UINT16   conn_latency,
              UINT16   supervision_timeout,
              UINT16   maximum_ce_length,
              UINT16   minimum_ce_length
          );

GA_RESULT appl_ga_hci_brr_le_ext_create_connection
          (
               UCHAR    initiator_filter_policy,
               UCHAR    own_address_type,
               UCHAR    peer_address_type,
               UCHAR  * peer_address,
               UCHAR    initiating_phys,
               UINT16 * scan_interval,
               UINT16 * scan_window,
               UINT16 * conn_interval_min,
               UINT16 * conn_interval_max,
               UINT16 * conn_latency,
               UINT16 * supervision_timeout,
               UINT16 * minimum_ce_length,
               UINT16 * maximum_ce_length
          );

#ifdef GA_SUPPORT_5_4
GA_RESULT appl_ga_hci_brr_le_ext_create_connection_v2
          (
              UCHAR    adv_handle,
              UCHAR    subevent,
              UCHAR    initiator_filter_policy,
              UCHAR    own_address_type,
              UCHAR    peer_address_type,
              UCHAR  * peer_address,
              UCHAR    initiating_phys,
              UINT16 * scan_interval,
              UINT16 * scan_window,
              UINT16 * conn_interval_min,
              UINT16 * conn_interval_max,
              UINT16 * max_latency,
              UINT16 * supervision_timeout,
              UINT16 * minimum_ce_length,
              UINT16 * maximum_ce_length
          );
#endif /* GA_SUPPORT_5_4 */

GA_RESULT appl_ga_hci_brr_create_connection_cancel(void);

GA_RESULT appl_ga_hci_brr_disconnect
          (
              UINT16  connection_handle,
              UCHAR   reason
          );

GA_RESULT appl_ga_hci_brr_le_start_encryption
          (
              UINT16   conn_handle,
              UCHAR  * random_number,
              UINT16   encrypted_diversifier,
              UCHAR  * long_term_key
          );

GA_RESULT appl_ga_hci_brr_le_long_term_key_requested_reply
           (
               UINT16   connection_handle,
               UCHAR *  long_term_key
           );

GA_RESULT appl_ga_hci_brr_le_read_remote_used_features
          (
              UINT16 connection_handle
          );

GA_RESULT appl_ga_hci_brr_le_set_cig_params
          (
              UCHAR  cig_id,
              UINT32 sdu_interval_m_to_s,
              UINT32 sdu_interval_s_to_m,
              UCHAR  sca,
              UCHAR  packing,
              UCHAR  framing,
              UINT16 max_transport_latency_m_to_s,
              UINT16 max_transport_latency_s_to_m,
              UCHAR  cis_count,
              UCHAR * cis_id,
              UINT16 * max_sdu_m_to_s,
              UINT16 * max_sdu_s_to_m,
              UCHAR * phy_m_to_s,
              UCHAR * phy_s_to_m,
              UCHAR * rtn_m_to_s,
              UCHAR * rtn_s_to_m
          );

GA_RESULT appl_ga_hci_brr_le_set_cig_params_test
          (
              UCHAR  cig_id,
              UINT32 sdu_interval_m_to_s,
              UINT32 sdu_interval_s_to_m,
              UCHAR  ft_m_to_s,
              UCHAR  ft_s_to_m,
              UINT16 iso_interval,
              UCHAR  sca,
              UCHAR  packing,
              UCHAR  framing,
              UCHAR  cis_count,
              UCHAR * cis_id,
              UCHAR * nse,
              UINT16 * max_sdu_m_to_s,
              UINT16 * max_sdu_s_to_m,
              UINT16 * max_pdu_m_to_s,
              UINT16 * max_pdu_s_to_m,
              UCHAR * phy_m_to_s,
              UCHAR * phy_s_to_m,
              UCHAR * bn_m_to_s,
              UCHAR * bn_s_to_m
          );

GA_RESULT appl_ga_hci_brr_le_remove_cig
          (
              UCHAR  cig_id
          );

GA_RESULT appl_ga_hci_brr_le_create_cis
          (
              UCHAR    cis_count,
              UINT16 * cis_connection_handle,
              UINT16 * acl_connection_handle
          );

GA_RESULT appl_ga_hci_brr_le_accept_cis_req
          (
              UINT16 connection_handle
          );

GA_RESULT appl_ga_hci_brr_le_reject_cis_req
          (
              UINT16 connection_handle,
              UCHAR  reason
          );

GA_RESULT appl_ga_hci_brr_le_set_pa_sync_transfer_params
          (
              UINT16 connection_handle,
              UCHAR  mode,
              UINT16 skip,
              UINT16 sync_timeout,
              UCHAR  cte_type
          );

GA_RESULT appl_ga_hci_brr_le_pa_sync_transfer
          (
              UINT16 connection_handle,
              UINT16 service_data,
              UINT16 sync_handle
          );

GA_RESULT appl_ga_hci_brr_le_pa_set_info_transfer
          (
              UINT16 connection_handle,
              UINT16 service_data,
              UCHAR  advertising_handle
          );

GA_RESULT appl_ga_hci_brr_le_setup_iso_data_path
          (
              UINT16 connection_handle,
              UCHAR  data_path_direction,
              UCHAR  data_path_id,
              UCHAR * codec_id,
              UINT32 controller_delay,
              UCHAR  codec_configuration_length,
              UCHAR * codec_configuration
          );

GA_RESULT appl_ga_hci_brr_le_remove_iso_data_path
          (
              UINT16 connection_handle,
              UCHAR  data_path_direction
          );

GA_RESULT appl_ga_hci_brr_register_iso_data_handler
          (
              GA_RESULT (* callback_ptr) (UCHAR *header, UCHAR *data, UINT16 datalen)
          );

GA_RESULT appl_ga_hci_brr_iso_write
          (
              UINT16     connection_handle,
              UCHAR      ts_flag,
              UINT32     ts,
              UINT16     seq_num,
              UCHAR *    sdu,
              UINT16     sdu_len
          );

GA_RESULT appl_ga_hci_brr_register_callback(APPL_HCI_CB cb);

GA_RESULT appl_ga_hci_brr_unregister_callback(APPL_HCI_CB cb);

void appl_ga_hci_brr_extract_iso_header(UCHAR* header, GA_HCI_ISO_HEADER * iso_header);

#endif /* _H_GA_BRR_APPLHCI */

