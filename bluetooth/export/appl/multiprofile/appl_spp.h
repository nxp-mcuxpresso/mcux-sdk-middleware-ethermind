
/**
 *  \file appl_spp.h
 *
 *  Header file for SPP Command Line Test Application.
 */

/*
 *  Copyright (C) 2013. Mindtree Ltd.
 *  All rights reserved.
 */

#ifndef _H_APPL_SPP_
#define _H_APPL_SPP_

/* ----------------------------------------- Header File Inclusion */
#include "BT_common.h"
#include "BT_spp_api.h"

#include "appl_common.h"
#include "db_gen.h"

/* ----------------------------------------- Global Definitions */


/* ----------------------------------------- Macros */


/* ----------------------------------------- Structures/ Data Types */


/* ----------------------------------------- Function Declarations */
void spp_appl_init (void);
void spp_appl_start (void);
void spp_appl_stop (void);
void spp_appl_connect (UCHAR * bd_addr, UCHAR server_channel);
void spp_appl_disconnect (void);
void spp_appl_send_data (UCHAR * data, UINT16 datalen);

/* SPP callback */
API_RESULT spp_application_callback
           (
               /* IN */  SPP_HANDLE       spp_handle,
               /* IN */  SPP_EVENTS       spp_event,
               /* IN */  API_RESULT       status,
               /* IN */  void           * data,
               /* IN */  UINT16           data_length
           );

#endif /* _H_APPL_SPP_ */

