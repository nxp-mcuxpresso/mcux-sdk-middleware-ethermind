
/**
 *  \file appl_ga_features.h
 *
 *  \brief This file defines all the application features of the GA module.
 */

/*
 *  Copyright (C) 2020. Mindtree Ltd.
 *  All rights reserved.
 */

#ifndef _H_APPL_GA_FEATURES_
#define _H_APPL_GA_FEATURES_

/* --------------------------------------------- Header File Inclusion */

/* ----------------------------------------------------------------------- */
/* =============== APPL GA Feature Flags ================================= */
/* ----------------------------------------------------------------------- */
/* Have the legacy GA application support. Disable if APPL_INIT_AUTOMATE enabled */
#define APPL_GA_LEGACY_SUPPORT

/* Define to use default configurations for init and registration */
//#define APPL_GA_USE_CONFIG_FILE_FOR_INPUT


/* Define to display the missed Streaming data Sequence number for Source */
/* #define SRC_DISPLAY_MISSED_SEQ_NUM */

/* Define to display the missed Streaming data Sequence number for Sink */
/* #define SNK_DISPLAY_MISSED_SEQ_NUM */

/* For Unicast Client automated application through legacy GA app */
/* #define APPL_GA_SAMPLE_APP_UCC */

/* For Unicast Server automated application through legacy GA app */
/* #define APPL_GA_SAMPLE_APP_UCS */

/* Define to have an automated setup of Server Sink application for LE Audio */
/* #define APPL_INIT_AUTOMATE_SERVER_SINK */

/* Define to not automatically send RxStartReady upong ISO Data path setup */
/* #define APPL_GA_UCS_NO_AUTORXSTART_READY */

/* Define this Flag if all devices EA to be displayed */
/* #define APPL_DISPLAY_ALL_EA_DEVICE */


/*
 * Although the CC configured on ASE is 2, the Audio Input File used will be
 * for 1 CC, LC3 Encoder and Audio PL will work on 1CC setting.
 */
//#define APPL_GA_SRC_USE_CC1_CONFIG_FOR_CC2

#define AUDIO_SRC_ISO_SUPPORT
#define AUDIO_SNK_ISO_SUPPORT

#define AUDIO_SRC_PL_SUPPORT
#define AUDIO_SNK_PL_SUPPORT

#define AUDIO_SRC_LC3_SUPPORT
#define AUDIO_SNK_LC3_SUPPORT

/*
 * TODO: Validate AUDIO_SRC_LC3_CHANNELS_MAX/AUDIO_SNK_LC3_CHANNELS_MAX is less
 * than LC3_CHANNELS_MAX
 */
#define AUDIO_SRC_LC3_CHANNELS_MAX 2U
#define AUDIO_SNK_LC3_CHANNELS_MAX 2U

/* #define SRC_DUMP_AUDIO_PREENCODED */
/* #define SRC_DUMP_AUDIO_ENCODED */
/* #define SNK_DUMP_AUDIO_PREDECODED */
/* #define SNK_DUMP_AUDIO_DECODED */

/* #define APPL_SRC_TIMESTAMP_DUMP */
/* #define APPL_SNK_TIMESTAMP_DUMP */

#ifdef BT_GAM

#define APPL_UCC
#if ((defined APPL_UCC) && (!defined BAP_UCC))
#error "To support APPL_UCC, it's mandatory to support BAP_UCC"
#endif /* ((defined APPL_UCC) && (!defined BAP_UCC)) */

#define APPL_UCS
#if ((defined APPL_UCS) && (!defined BAP_UCS))
#error "To support APPL_UCS, it's mandatory to support BAP_UCS"
#endif /* ((defined APPL_UCS) && (!defined BAP_UCS)) */

#define APPL_BAP_BROADCAST_SOURCE
#if ((defined APPL_BAP_BROADCAST_SOURCE) && (!defined BAP_BROADCAST_SOURCE))
#error "To support APPL_BAP_BROADCAST_SOURCE, it's mandatory to support BAP_BROADCAST_SOURCE"
#endif /* ((defined APPL_BAP_BROADCAST_SOURCE) && (!defined BAP_BROADCAST_SOURCE)) */

#define APPL_BAP_BROADCAST_SINK
#if ((defined APPL_BAP_BROADCAST_SINK) && (!defined BAP_BROADCAST_SINK))
#error "To support APPL_BAP_BROADCAST_SINK, it's mandatory to support BAP_BROADCAST_SINK"
#endif /* ((defined APPL_BAP_BROADCAST_SINK) && (!defined BAP_BROADCAST_SINK)) */

#define APPL_BAP_BROADCAST_ASSISTANT
#if ((defined APPL_BAP_BROADCAST_ASSISTANT) && (!defined BAP_BROADCAST_ASSISTANT))
#error "To support APPL_BAP_BROADCAST_ASSISTANT, it's mandatory to support BAP_BROADCAST_ASSISTANT"
#endif /* ((defined APPL_BAP_BROADCAST_ASSISTANT) && (!defined BAP_BROADCAST_ASSISTANT)) */

#define APPL_BAP_BROADCAST_SCAN_DELEGATOR
#if ((defined APPL_BAP_BROADCAST_SCAN_DELEGATOR) && (!defined BAP_BROADCAST_SCAN_DELEGATOR))
#error "To support APPL_BAP_BROADCAST_SCAN_DELEGATOR, it's mandatory to support BAP_BROADCAST_SCAN_DELEGATOR"
#endif /* ((defined APPL_BAP_BROADCAST_SCAN_DELEGATOR) && (!defined BAP_BROADCAST_SCAN_DELEGATOR)) */

#define APPL_VCP_CONTROLLER
#if ((defined APPL_VCP_CONTROLLER) && (!defined VCP_CONTROLLER))
#error "To support APPL_VCP_CONTROLLER, it's mandatory to support VCP_CONTROLLER"
#endif /* ((defined APPL_VCP_CONTROLLER) && (!defined VCP_CONTROLLER)) */

#define APPL_VCP_RENDERER
#if ((defined APPL_VCP_RENDERER) && (!defined VCP_RENDERER))
#error "To support APPL_VCP_RENDERER, it's mandatory to support VCP_RENDERER"
#endif /* ((defined APPL_VCP_RENDERER) && (!defined VCP_RENDERER)) */

#define APPL_MICP_CONTROLLER
#if ((defined APPL_MICP_CONTROLLER) && (!defined MICP_CONTROLLER))
#error "To support APPL_MICP_CONTROLLER, it's mandatory to support MICP_CONTROLLER"
#endif /* ((defined APPL_MICP_CONTROLLER) && (!defined MICP_CONTROLLER)) */

#define APPL_MICP_DEVICE
#if ((defined APPL_MICP_DEVICE) && (!defined MICP_DEVICE))
#error "To support APPL_MICP_DEVICE, it's mandatory to support MICP_DEVICE"
#endif /* ((defined APPL_MICP_DEVICE) && (!defined MICP_DEVICE)) */

#define APPL_CSIP_SETMEMBER
#if ((defined APPL_CSIP_SETMEMBER) && (!defined CSIP_MEMBER))
#error "To support APPL_GA_CSIP, it's mandatory to support CSIP_MEMBER"
#endif /* ((defined APPL_CSIP_SETMEMBER) && (!defined CSIP_MEMBER)) */

#define APPL_CSIP_SETCOORDINATOR
#if ((defined APPL_CSIP_COORDINATOR) && (!defined CSIP_COORDINATOR))
#error "To support APPL_GA_CSIP, it's mandatory to support CSIP_COORDINATOR"
#endif /* ((defined APPL_CSIP_COORDINATOR) && (!defined CSIP_COORDINATOR)) */

/* CAS SetMember */
#define APPL_CAS_SETMEMBER

/* CAS SetCoordinator */
#define APPL_CAS_SETCOORDINATOR

/* #define APPL_CAP_ENABLE_CSIS_READ_APP_CB */
#if ((defined APPL_CAP_ENABLE_CSIS_READ_APP_CB) && (!defined CAP_ENABLE_CSIS_READ_APP_CB))
#error "To support APPL_CAP_ENABLE_CSIS_READ_APP_CB, it's mandatory to support CAP_ENABLE_CSIS_READ_APP_CB"
#endif /* ((defined APPL_CAP_ENABLE_CSIS_READ_APP_CB) && (!defined CAP_ENABLE_CSIS_READ_APP_CB)) */

#define APPL_CCP_CLIENT
#if ((defined APPL_CCP_CLIENT) && (!defined CCP_CLIENT))
#error "To support APPL_CCP_CLIENT, it's mandatory to support CCP_CLIENT"
#endif /* ((defined APPL_CCP_CLIENT) && (!defined CCP_CLIENT)) */

#define APPL_CCP_SERVER
#if ((defined APPL_CCP_SERVER) && (!defined CCP_SERVER))
#error "To support APPL_CCP_SERVER, it's mandatory to support CCP_SERVER"
#endif /* ((defined APPL_CCP_SERVER) && (!defined CCP_SERVER)) */

#define APPL_MCP_CLIENT
#if ((defined APPL_MCP_CLIENT) && (!defined MCP_CLIENT))
#error "To support APPL_MCP_CLIENT, it's mandatory to support MCP_CLIENT"
#endif /* ((defined APPL_MCP_CLIENT) && (!defined MCP_CLIENT)) */

#define APPL_MCP_SERVER
#if ((defined APPL_MCP_SERVER) && (!defined MCP_SERVER))
#error "To support APPL_MCP_SERVER, it's mandatory to support MCP_SERVER"
#endif /* ((defined APPL_MCP_SERVER) && (!defined MCP_SERVER)) */

#define APPL_TMAP_CLIENT
#if ((defined APPL_TMAP_CLIENT) && (!defined TMAP_CLIENT))
#error "To support APPL_TMAP_CLIENT, it's mandatory to support TMAP_CLIENT"
#endif /* ((defined APPL_TMAP_CLIENT) && (!defined TMAP_CLIENT)) */

#define APPL_TMAP_SERVER
#if ((defined APPL_TMAP_SERVER) && (!defined TMAP_SERVER))
#error "To support APPL_TMAP_SERVER, it's mandatory to support TMAP_SERVER"
#endif /* ((defined APPL_TMAP_SERVER) && (!defined TMAP_SERVER)) */

#define APPL_HAP_CLIENT
#if ((defined APPL_HAP_CLIENT) && (!defined HAP_CLIENT))
#error "To support APPL_HAP_CLIENT, it's mandatory to support HAP_CLIENT"
#endif /* ((defined APPL_HAP_CLIENT) && (!defined HAP_CLIENT)) */

#define APPL_HAP_SERVER
#if ((defined APPL_HAP_SERVER) && (!defined HAP_SERVER))
#error "To support APPL_HAP_SERVER, it's mandatory to support HAP_SERVER"
#endif /* ((defined APPL_HAP_SERVER) && (!defined HAP_SERVER)) */

#define APPL_GA_PBP
#if ((defined APPL_GA_PBP) && (!defined GA_PBP))
#error "To support APPL_GA_PBP, it's mandatory to support GA_PBP"
#endif /* ((defined APPL_GA_PBP) && (!defined GA_PBP)) */
#endif /* BT_GAM */

#if 0
#if ((defined AUDIO_SRC_LC3_SUPPORT) && (AUDIO_SRC_LC3_CHANNELS_MAX > LC3_CHANNELS_MAX))
#error "EtherMind LC3 does not support AUDIO_SRC_LC3_CHANNELS_MAX"
#endif /* ((defined INCLUDE_ETHERMIND_LC3) && (AUDIO_SRC_LC3_CHANNELS_MAX > LC3_CHANNELS_MAX) */

#if ((defined AUDIO_SNK_LC3_SUPPORT) && (AUDIO_SNK_LC3_CHANNELS_MAX > LC3_CHANNELS_MAX))
#error "EtherMind LC3 does not support AUDIO_SNK_LC3_CHANNELS_MAX"
#endif /* ((defined INCLUDE_ETHERMIND_LC3) && (AUDIO_SRC_LC3_CHANNELS_MAX > LC3_CHANNELS_MAX) */
#endif /* 0 */
#endif /* _H_APPL_GA_FEATURES_ */
