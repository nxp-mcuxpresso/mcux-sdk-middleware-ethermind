
/**
 *  \file appl_hfp_unit_standalone.h
 *
 *  Header file for HFP Unit Command Line Test Application.
 */

/*
 *  Copyright (C) 2013. Mindtree Ltd.
 *  All rights reserved.
 */

#ifndef _H_APPL_HFP_UNIT_STANDALONE_
#define _H_APPL_HFP_UNIT_STANDALONE_


/* ----------------------------------------- Header File Inclusion */
/*#include "BT_hfp_unit_api.h"
#include "BT_hci_api.h"
#include "BT_sdp_api.h"

#include "appl_hci.h"
#include "db_gen.h"
*/
#include "appl_hfp_unit.h"

/* ----------------------------------------- Global Definitions */

/* ----------------------------------------- Macros */

#ifdef HFP_BRIDGING_STANDALONE
#define APPL_UNIT_SLC_CONNECTED    0x01U
#define APPL_UNIT_SLC_DISCONNECTED 0x00U
#endif /* HFP_BRIDGING_STANDALONE */

/* ----------------------------------------- Function Declarations */


API_RESULT appl_callback_registered_with_standalone_hfu
           (
               HFP_UNIT_HANDLE   handle,   /* Connection Instance */
               HFP_UNIT_EVENTS   event,    /* HFP Events          */
               API_RESULT        result,   /* Result of operation */
               void *            data,     /* Data for each event */
               UINT16            data_len  /* Length of Data      */
           );

void appl_hfu_standalone_sdp_cb
     (
         UCHAR    command,
         UCHAR  * data,
         UINT16   length,
         UINT16   status
     );

API_RESULT appl_hfp_standalone_extract_result
           (
               /* IN */  AT_PARSER_RESPONSE  * parser_response,
               /* IN */  UCHAR               * buffer,
               /* OUT */ APPL_PARSER_RESULT  * parse_result
           );

#ifndef HFP_UNIT_1_6
/* Start HFP Unit */
API_RESULT appl_start_hfu_standalone
           (
               UCHAR  * hfp_unit_local_supported_features,
               UINT16   data_length
           );
#else /* HFP_UNIT_1_6 */
/* Start HFP Unit */
API_RESULT appl_start_hfu_standalone
           (
               /* IN */  HFP_UNIT_APPL_CONFIG_PARAMS *p_hfp_unit_appl_conf_params
           );
#endif /* HFP_UNIT_1_6 */

void appl_hfp_unit_standalone_1_5_choice_hdlr( void );
void appl_hfp_unit_standalone_1_6_choice_hdlr( void );
void appl_hfpunit_standalone_change_esco_config(void);
void appl_hfpunit_standalone_create_eSCO_connection(void);
void appl_hfag_standalone_read_pl(UCHAR * rsp, UINT16 rsplen);
#ifdef HFP_BRIDGING_STANDALONE
void appl_hfp_standalone_handle_bridge_app_cmds(HFP_UNIT_EVENTS event, void *data, UINT16 data_len);
void appl_hfp_standalone_add_cmd_string(UCHAR* str, UCHAR* buffer, void* data, UINT16 data_len);
UINT32 appl_hfu_standalone_get_handle();
UINT8 appl_hfpunit_standalone_is_unit_connected();
#endif /* HFP_BRIDGING_STANDALONE */

#endif /* _H_APPL_HFP_UNIT_STANDALONE_ */

