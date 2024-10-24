/**
 *  \file micp_extern.h
 *
 *  \brief This file defines the Volume Control Profile Interfaces
 */

/*
 *  Copyright (C) 2020. Mindtree Ltd.
 *  All rights reserved.
 */


#ifndef _H_MICP_EXTERN_
#define _H_MICP_EXTERN_

/* --------------------------------------------- Header File Inclusion */
#include "micp.h"

/* --------------------------------------------- Global Definitions */
#ifdef MICP_CONTROLLER
/** MICP MICS Contexts */
GA_DECLARE_GLOBAL_ARRAY(MICP_CONTEXT, micp_context, GA_CONFIG_LIMITS(MICP_MAX_MICS_CONTEXTS));

/** MICP AICS Contexts */
GA_DECLARE_GLOBAL_ARRAY(MICP_AICS_CONTEXT, micp_aics_context, GA_CONFIG_LIMITS(MICP_MAX_AICS_CONTEXTS));

extern GA_BRR_PRF_HANDLE micp_brr_id;
#endif /* MICP_CONTROLLER */

/* Global MICP Mutex Variable */
#ifdef MICP_CONTROLLER
GA_DEFINE_MUTEX_TYPE(extern, micc_mutex);
#endif /* MICP_CONTROLLER */
#ifdef MICP_DEVICE
GA_DEFINE_MUTEX_TYPE(extern, mics_mutex);
#endif /* MICP_DEVICE */

#ifdef MICP_CONTROLLER
/* Characteristic UUID table for AICS */
extern DECL_CONST GA_CHAR_UUID micp_mics_uuid[MICS_CHAR_ID_COUNT];

/* Characterisitc configuration enable mask */
extern UINT32 micp_mics_config;

/* Characteristic UUID table for AICS */
extern DECL_CONST GA_CHAR_UUID micp_aics_uuid[AICS_CHAR_ID_COUNT];

/* Characterisitc configuration enable mask */
extern UINT32 micp_aics_config;
#endif /* MICP_CONTROLLER */

#ifdef MICP_DEVICE
/* MICS as Server */
extern MICS_CONTEXT    mics_entity;

/* AICS as Server */
GA_DECLARE_GLOBAL_ARRAY(MICS_AICS_CONTEXT, mics_aics_entity, GA_CONFIG_LIMITS(MICP_MAX_AICS_ENTITIES));
#endif /* MICP_DEVICE */

/* --------------------------------------------- Data types /Structures */

/* --------------------------------------------- Macros */

/* --------------------------------------------- APIs */

#endif /* _H_MICP_EXTERN_ */
