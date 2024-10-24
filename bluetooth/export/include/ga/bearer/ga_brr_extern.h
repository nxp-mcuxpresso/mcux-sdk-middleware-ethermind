
/**
 *  \file ga_brr_extern.h
 *
 *  \brief This file defines the Generic Audio Beater Extern Defines.
 */

/*
*  Copyright (C) 2020. Mindtree Ltd.
*  All rights reserved.
*/

#ifndef _H_GA_BRR_EXTERN_
#define _H_GA_BRR_EXTERN_

#ifdef BT_GAM
/* --------------------------------------------- Header File Inclusion */

/* --------------------------------------------- Global Definitions */
/**
 * Common Bearer Callback to GA Core.
 */
extern GA_BRR_CB          ga_brr_cb;

/**
 * GA Bearer Profile/Service Contexts
 */
GA_BRR_DECLARE_GLOBAL_ARRAY(GA_BRR_CONTEXT, ga_brr_context, GA_BRR_CONFIG_LIMITS(GA_BRR_MAX_CONTEXTS));


/* --------------------------------------------- Data types /Structures */

/* --------------------------------------------- Macros */

/* --------------------------------------------- APIs */

#endif
#endif /* _H_GA_BRR_EXTERN_ */
