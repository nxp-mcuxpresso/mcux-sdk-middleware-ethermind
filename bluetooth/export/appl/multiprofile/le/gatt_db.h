/**
 *  \file gatt_db.h
 */

/*
 *  Copyright (C) 2013. Mindtree Ltd.
 *  All rights reserved.
 */

#ifndef _H_GATT_DB_
#define _H_GATT_DB_

/* ----------------------------------------- Header File Inclusion */
#if ((defined PXR) && (defined GATT_DB))
#include "gatt_db_pxr.h"
#endif

#if ((defined BT_HRS) && (defined GATT_DB))
#include "gatt_db_hrs.h"
#endif

#if ((defined VSE) && (defined GATT_DB))
#include "gatt_db_vse.h"
#endif

/* --------------------------------------------- Data Types/ Structures */

/* --------------------------------------------- Global Definitions */

/* --------------------------------------------- External Global Variables */
#ifdef GATT_DB_DYNAMIC
/* Service Instances */
extern UINT16 GATT_SER_GAP_INST;
extern UINT16 GATT_SER_GATT_INST;
extern UINT16 GATT_SER_BATTERY_INST;
extern UINT16 GATT_SER_DEV_INFO_INST;

/* Characteristic Instances */
extern UINT16 GATT_CHAR_BATTERY_LVL_INST;
#endif /* GATT_DB_DYNAMIC */

extern API_RESULT gatt_db_gatt_char_handler
           (
               GATT_DB_HANDLE    * handle,
               GATT_DB_PARAMS    * params
           );
/* --------------------------------------------- Macros */

/* --------------------------------------------- Functions */
#ifdef GATT_DB_DYNAMIC
API_RESULT appl_add_gaps(void);
API_RESULT appl_add_gatts(void);
API_RESULT appl_add_bas(void);
API_RESULT appl_add_dis(void);
API_RESULT appl_add_cccd
           (
               UINT16    service_handle,
               UINT16    char_handle
           );
API_RESULT appl_add_presentation_format
           (
               UINT16    service_handle,
               UINT16    char_handle,
               UCHAR   * presentation_format,
               UINT16    format_length
           );
#endif /* GATT_DB_DYNAMIC */

#endif /* _H_GATT_DB_ */
