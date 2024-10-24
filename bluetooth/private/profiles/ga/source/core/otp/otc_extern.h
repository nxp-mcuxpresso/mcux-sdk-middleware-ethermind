/**
 *  \file otc_extern.h
 *
 *  \brief This file defines the Media Control Profile Client extern usage.
 */

 /*
  *  Copyright (C) 2020. Mindtree Ltd.
  *  All rights reserved.
  */


#ifndef _H_OTC_EXTERN_
#define _H_OTC_EXTERN_

/* --------------------------------------------- Header File Inclusion */

#ifdef OTP_CLIENT

/* --------------------------------------------- Global Definitions */
/* Number of simultaneous OTC Sessions using different Channel Identifiers */
extern OTC_SESSION otc_sess[MAX_NUM_OF_CONCURRENT_OTC_SESSIONS];

/* OTC Callback registered by applications */
extern OTP_CE_CB_CTX otc_cb_ctx[MAX_NUM_OF_CONCURRENT_CB_CTX];

/* OTC Profile ID registered with the GA Bearer */
extern GA_BRR_PRF_HANDLE otc_ga_brr_prf_hdl;

/* Characteristic configuration handle */
extern UINT16 otc_config_hndl;

/* Characteristic UUID table for OTS */
extern DECL_CONST GA_CHAR_UUID otp_ots_uuid[OTP_CHAR_ID_COUNT];

extern UINT32 otp_ots_config;

/* --------------------------------------------- Data types /Structures */


/* --------------------------------------------- Macros */

/* --------------------------------------------- APIs */

#endif /* OTP_CLIENT */

#endif /* _H_OTC_EXTERN_ */