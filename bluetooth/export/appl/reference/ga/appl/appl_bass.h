
/**
 *  \file appl_mcp_ce.h
 *
 *  \brief This file is a generic application example that demonstrates the
 *  usage of BASS - Client and Server role interfaces exposed by MCP Client
 *  and Server Library.
 */

/**
 *  Copyright (C) 2020. Mindtree Ltd.
 *  All rights reserved.
 */
#ifndef _H_APPL_BASS_
#define _H_APPL_BASS_
/* --------------------------------------------- Header File Inclusion */
#include "GA_bass_api.h"
#include "GA_common.h"

/* --------------------------------------------- Global Definitions */

/* --------------------------------------------- Data types /Structures */

/* --------------------------------------------- Macros */

/* As per BASS Spec, there is no maximum value defined */
#define APPL_BASS_MAX_NUM_OF_SUB_GROUPS         5U
/* As per BASS Spec, there is no maximum value defined */
#define APPL_BASS_MAX_NUM_OF_SOURCES            5U

/* --------------------------------------------- APIs */
GA_RESULT appl_bass_ce_cb
          (
              /* IN */ GA_ENDPOINT    * device,
              /* IN */ BASS_CE_EVT_ID   evt_id,
              /* IN */ UINT16           evt_status,
              /* IN */ BASS_EVT       * evt_data
          );

GA_RESULT appl_bass_ce_parse_and_handle_bc_rx_state(UINT8* rx_state_src_info_ptr, UINT16 len);

GA_RESULT appl_bass_se_cb
          (
              /* IN */ GA_ENDPOINT            * device,
              /* IN */ GA_BASS_SE_RSP_CONTEXT * ctx,
              /* IN */ BASS_SE_EVT_ID           evt_id,
              /* IN */ UINT16                   evt_status,
              /* IN */ BASS_EVT               * evt_data
          );

GA_RESULT appl_bass_se_parse_and_handle_bas_cp(UINT8* bas_cp, UINT16 len);

GA_RESULT appl_bass_se_is_src_add_allowed(UINT8* id);

UINT8 appl_bass_se_copy_add_src_to_bc_rx_state
      (
          GA_BASS_BAS_CP_ADD_SRC   add_src,
          GA_BASS_BC_RX_STATE    * br_rx_state
      );

void appl_bass_se_parse_and_display_add_source
     (
         GA_BASS_BAS_CP_ADD_SRC * add_src,
         UINT8                  * bas_cp,
         UINT32                 * bis_sync,
         UINT8                  * metadata_len,
         UINT8                  * metadata
     );

GA_RESULT appl_bass_se_parse_and_display_bc_rx_state
          (
              GA_BASS_BC_RX_STATE br_rx_state
          );

void main_bass_menu_operations(void);

#endif /* _H_APPL_BASS_ */
