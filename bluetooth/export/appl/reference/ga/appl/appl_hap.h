/**
 *  \file appl_hap.h
 *
 *  \brief This file defines the Hearing Access/Aid Profile:
 *  Application Data Structures and Methods.
 *  This application is used to identify a hearing aid and optionally to
 *  control hearing aid presets.
 *  A hearing aid preset represents a configuration of the hearing aid signal
 *  processing parameters tailored to a specific listening situation.
 *  This application implements both HAP Client and Server Role.
 *  It shows how to discover a Hearing Aid, its features and also perform
 *  control point procedures on them.
 *  It also indicates how the remote Hearing Aid handles the requests from the
 *  Client device and responds to the same.
 *
 *  Roles: HAP Client: Device that control the Hearing Aid Presets.
 *         HAP Server: Device that receives CP procedures from HAP Client.
 *  GATT Requirement: HAP Client: GATT Client
 *                    HAP Server: GATT Server
 */

/*
 *  Copyright (C) 2020. Mindtree Ltd.
 *  All rights reserved.
 */

#ifndef _H_APPL_HAP_
#define _H_APPL_HAP_


/* --------------------------------------------- Header File Inclusion */
#include "GA_hap_api.h"
#include "appl_ga_common.h"

/* --------------------------------------------- Macros */
#define APPL_HAP_MAX_SUPP_PRESET_RECORDS             10U
#define APPL_HAP_MAX_PRESET_RECORD_NAME              40U
#define APPL_HAP_PRESET_RECORD_INDEX_INVALID         0x00
#define APPL_HAP_PRESET_RECORD_IS_AVAILABLE_BIT_LOC  0x02

/* --------------------------------------------- Data types /Structures */

typedef struct _APPL_HAS_PRESET_RECORD_
{
    /* Preset Record - Index */
    UINT8 index;

    /* Preset Record - Properties */
    UINT8 properties;

    /* Preset Record - Name Length */
    UINT8 name_len;

    /* Preset Record - Name */
    UCHAR name[APPL_HAP_MAX_PRESET_RECORD_NAME];

    /* To Notify */
    UINT8 to_notify;

    /* Change_ID */
    UINT8 change_id;

}APPL_HAS_PRESET_RECORD;

typedef struct _APPL_HAS_CHAR_INFO_
{
    /**
     * Hearing Aid Features
     */
    HAP_FEATURES features;

    APPL_HAS_PRESET_RECORD preset_records[APPL_HAP_MAX_SUPP_PRESET_RECORDS];

    UINT8 num_of_preset_records;

    /**
     * Active Preset Index
     */
    UINT8 active_preset_index;
}APPL_HAS_CHAR_INFO;
/* --------------------------------------------- Global Definitions */

/* --------------------------------------------- APIs */

void main_hap_menu_operations(void);

GA_RESULT appl_hap_cb
          (
              /* IN */ GA_ENDPOINT * device,
              /* IN */ void        * ctx,
              /* IN */ HAP_EVT_ID    evt_id,
              /* IN */ UINT16        evt_status,
              /* IN */ HAP_EVT     * evt_data
          );

void appl_hap_parse_features(HAP_FEATURES features);

void appl_hap_fetch_preset_record_properties(UINT8 * prop);

void appl_hap_parse_ga_result(GA_RESULT status);

void appl_hap_parse_and_display_is_last(UCHAR is_last);

GA_RESULT appl_hap_notify_ha_preset_cp_generic_update
          (
              UINT8 isLast,
              UINT8 preset_record_index
          );

GA_RESULT appl_hap_notify_ha_preset_cp_record_deleted_avail_unavail
          (
              UINT8 change_id,
              UINT8 isLast,
              UINT8 preset_record_index
          );

void appl_hap_parse_and_display_preset_record_properties
     (
         UCHAR preset_record_properties
     );

#ifdef APPL_HAP_CLIENT
void appl_hap_handle_cp_write(void);

GA_RESULT appl_hap_ce_cb
          (
              /* IN */ GA_ENDPOINT * device,
              /* IN */ void        * ctx,
              /* IN */ HAP_EVT_ID    evt_id,
              /* IN */ UINT16        evt_status,
              /* IN */ HAP_EVT     * evt_data
          );

GA_RESULT appl_hap_parse_hap_cp
          (
              UINT8   handle,
              UCHAR * data,
              UINT16  len
          );

void appl_hap_parse_change_id(UINT8 changeId);

void appl_hap_parse_and_display_preset_record(UCHAR * data, UINT16 len);

void appl_hap_fetch_and_update_preset_record
     (
         UINT8   handle,
         UCHAR * data,
         UINT8   len
     );

void appl_hap_reset_rem_presets_db(void);

GA_RESULT appl_hap_fetch_preset_record_from_db
          (
              UINT8   hap_handle,
              UINT8   index,
              UINT8 * db_index
          );
#endif /* APPL_HAP_CLIENT */

#ifdef APPL_HAP_SERVER

void appl_hap_ha_initialize_records(void);

void appl_hap_ha_register_preset_records(void);

void appl_hap_ha_create_preset_records(void);

GA_RESULT appl_hap_se_cb
          (
              /* IN */ GA_ENDPOINT * device,
              /* IN */ void        * ctx,
              /* IN */ HAP_EVT_ID    evt_id,
              /* IN */ UINT16        evt_status,
              /* IN */ HAP_EVT     * evt_data
          );

GA_RESULT appl_hap_ha_preset_cp_handler
          (
              GA_ENDPOINT * device,
              HAP_EVT_ID    evt_id,
              HAP_EVT     * evt_data
          );

void appl_hap_ha_client_init_cp_send_ntf_timer_expiry_handler
     (
         void   * cntrl_point_rsp,
         UINT16   datalen
     );

void appl_hap_ha_server_init_cp_send_ntf_timer_expiry_handler
     (
         void   * cntrl_point_data,
         UINT16   datalen
     );

GA_RESULT appl_hap_send_preset_changed_ntf(void);

void appl_has_create_preset_records_array(UCHAR i, UCHAR* data, UCHAR* len);

void appl_has_pack_preset_record_data_for_ind_ntf
     (
         UINT8   opcode,
         UINT8   db_preset_record_index,
         UINT8   is_Last,
         UCHAR * data,
         UCHAR * len
     );

#endif /* APPL_HAP_SERVER */

#endif /* _H_APPL_HAP_ */

