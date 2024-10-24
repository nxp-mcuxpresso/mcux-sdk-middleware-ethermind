
/**
*  \file appl_ga_smp_brr.h
*
*  File description
*/

/*
*  Copyright (C) 2013. Mindtree Ltd.
*  All rights reserved.
*/

#ifndef _H_GA_BRR_APPLSMP
#define _H_GA_BRR_APPLSMP

/* --------------------------------------------- Header File Inclusion */
#include "GA_common.h"
#include "GA_bearer_api.h"

/* --------------------------------------------- Global Definitions */

/* --------------------------------------------- Structures/Data Types */
/* --------------------------------------------- Macros */
/** LE Security Modes */
#define GA_SMP_LEGACY_MODE             0x01U
#define GA_SMP_LESC_MODE               0x02U
/* --------------------------------------------- Internal Functions */
GA_RESULT appl_ga_smp_brr_get_bd_handle
          (
              GA_ENDPOINT * addr,
              UCHAR       * dev_handle
          );

GA_RESULT appl_ga_smp_brr_authenticate
          (
              UCHAR security_mode,            
              GA_ENDPOINT* addr
          );

GA_RESULT appl_ga_smp_brr_create_resolvable_pvt_addr(UCHAR * sirk);

GA_RESULT appl_ga_smp_brr_verify_resolvable_pvt_addr
          (
              UCHAR * rsi,
              UCHAR * sirk
          );
void appl_ga_smp_brr_set_automatic_mode(UINT8 mode);

#endif /* _H_GA_BRR_APPLSMP */

