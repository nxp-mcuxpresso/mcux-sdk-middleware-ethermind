
/**
 *  \file GA_features.h
 *
 *  \brief This file defines all the features of the GA module.
 */

/*
 *  Copyright (C) 2020. Mindtree Ltd.
 *  All rights reserved.
 */

#ifndef _H_GA_FEATURES_
#define _H_GA_FEATURES_

/* ----------------------------------------------------------------------- */
/* ============== GA Bearer Configuration Flags ========================== */
/* ----------------------------------------------------------------------- */
/*
 *  BRR_GATT_CLIENT
 *
 *  This flag enables the GATT client interfaces at the bearer
 *
 *  Dependency: BT_GAM
 */
#define BRR_GATT_CLIENT

/*
 *  BRR_GATT_SERVER
 *
 *  This flag enables the GATT server interfaces at the bearer
 *
 *  Dependency: BT_GAM
 */
#define BRR_GATT_SERVER

/*
 *  BRR_GAP_BROADCASTER
 *
 *  This flag enables the GAP broadcaster interfaces at the bearer
 *  for setup Extended, Periodic and BIG Advertisements
 *
 *  Dependency: BT_GAM
 */
#define BRR_GAP_BROADCASTER

#ifdef BRR_GAP_BROADCASTER
/*
 *  BRR_ENABLE_BROADCAST_TEST
 *
 *  This flag enables the GAP broadcaster test interfaces at the bearer
 *  for broadcasting in test mode
 *
 *  Dependency: BRR_GAP_BROADCASTER
 */
#define BRR_ENABLE_BROADCAST_TEST
#endif /* BRR_GAP_BROADCASTER */

/*
 *  BRR_GAP_OBSERVER
 *
 *  This flag enables the GAP observer interfaces at the bearer
 *  for scanning Extended, Periodic and BIG advertisements
 *
 *  Dependency: BT_GAM
 */
#define BRR_GAP_OBSERVER

/* ----------------------------------------------------------------------- */
/* ============== GA Profiles Flags ====================================== */
/* ----------------------------------------------------------------------- */
/*
 *  CAP_SIMULATE_RANDOM_DEVICE_LOCKING
 *
 *  This flag enables support random device locking of CAP CSIS Lock.
 *  Mainly used for testing with PTS without using multiple Testers.
 *
 *  Dependency: BT_GAM
 */
/* #define CAP_SIMULATE_RANDOM_DEVICE_LOCKING */

/*
 *  GA_BAP
 *
 *  This flag enables support for the Basic Audio Profile
 *
 *  Dependency: BT_GAM
 */
#define GA_BAP

/*
 *  GA_VCP
 *
 *  This flag enables support for the Volume Control Profile
 *
 *  Dependency: BT_GAM
 */
#define GA_VCP

/*
 *  GA_MICP
 *
 *  This flag enables support for the Microphone Control Profile
 *
 *  Dependency: BT_GAM
 */
#define GA_MICP

/*
 *  GA_CSIP
 *
 *  This flag enables support for the Coordinated Set Identification Profile
 *
 *  Dependency: BT_GAM
 */
#define GA_CSIP

/*
 *  GA_CCP
 *
 *  This flag enables support for the Call Control Profile
 *
 *  Dependency: BT_GAM
 */
#define GA_CCP

/*
 *  GA_MCP
 *
 *  This flag enables support for the Media Control Profile
 *
 *  Dependency: BT_GAM
 */
#define GA_MCP

/*
 *  GA_HAP
 *
 *  This flag enables support for the Hearing Access Profile
 *
 *  Dependency: BT_GAM
 */
#define GA_HAP

/*
 *  GA_TMAP
 *
 *  This flag enables support for the Telephony and Media Audio Profile
 *
 *  Dependency: BT_GAM
 */
#define GA_TMAP

/*
 *  GA_PBP
 *
 *  This flag enables support for the Public Broadcast Profile
 *
 *  Dependency: BT_GAM
 */
#define GA_PBP

/* ----------------------------------------------------------------------- */
/* ============== CAP Specific Flags ===================================== */
/* ----------------------------------------------------------------------- */

#ifdef GA_CSIP
/*
 *  CAP_CSIP_COORDINATOR
 *
 *  This flag enables support for the CAS CSIS Coordinator
 *
 *  Dependency: CSIP_COORDINATOR
 */
#define CAP_CSIP_COORDINATOR

/*
 *  CAP_CSIP_MEMBER
 *
 *  This flag enables support for the CAS CSIS Member
 *
 *  Dependency: CSIP_MEMBER
 */
#define CAP_CSIP_MEMBER

/*
 *  CAP_ENABLE_CSIS_READ_APP_CB
 *
 *  This flag enables all Read/Write operations on the CAS CSIS server
 *  to be indicated to the application via callback. When not defined,
 *  the application callback for read operations on the CAS CSIS server
 *  are not indicated.
 *
 *  This flag is disabled by default.
 *
 *  Dependency: GA_CSIP
 */
/* #define CAP_ENABLE_CSIS_READ_APP_CB */
#endif /* GA_CSIP */

/* ----------------------------------------------------------------------- */
/* ============== BAP Specific Flags ===================================== */
/* ----------------------------------------------------------------------- */
#ifdef GA_BAP
/*
 *  BAP_PACS_CLIENT
 *
 *  This flag enables the Client role for BAP - PACS procedures
 *
 *  Dependency: GA_BAP
 */
#define BAP_PACS_CLIENT

/*
 *  BAP_PACS_SERVER
 *
 *  This flag enables the Server role of BAP - PACS procedures
 *
 *  Dependency: GA_BAP
 */
#define BAP_PACS_SERVER

#ifdef BAP_PACS_SERVER
/*
 *  BAP_PACS_DEREGISTER
 *
 *  This flag enables the interface to deregister the audio capabilities
 */
/* #define BAP_PACS_DEREGISTER */

/*
 *  BAP_AUTOREGISTER_MANDATORY_UNSPECIFIED_CONTEXT
 *
 *  This flag when defined, the API BAP_register_audio_contexts_and_locations()
 *  registers for the mandatory 'Unspecified' audio context irrespective of
 *  whether its support was given by the application or not.
 *
 *  When this flag is not defined, and if the 'Unspecified' context is not set
 *  by the application, the API will return an error.
 *
 *  Dependency: BAP_PACS_SERVER
 */
/* #define BAP_AUTOREGISTER_MANDATORY_UNSPECIFIED_CONTEXT */
#endif /* BAP_PACS_SERVER */

/*
 *  BAP_UCC
 *
 *  This flag enables the Unicast Client role of BAP
 *
 *  Dependency: GA_BAP and BAP_PACS_CLIENT
 */
#define BAP_UCC

/*
 *  BAP_UCS
 *
 *  This flag enables the Unicast Server role of BAP
 *
 *  Dependency: GA_BAP and BAP_PACS_SERVER
 */
#define BAP_UCS

#ifdef BAP_UCS
/*
 *  GA_CACHE_APPLIED_CONF
 *
 *  This flag enables BAP core to cache ASE state to Codec_Configured when
 *  Release Complete is notified, instead of IDLE state.
 *
 *  Dependency: BAP_UCS
 */
/* #define GA_CACHE_APPLIED_CONF */
#endif /* BAP_UCS */

#ifdef BAP_PACS_CLIENT
/*
 *  BAP_SUPPORT_CONFIG_SELECTION
 *
 *  This flag enables application interface to configure the
 *  notification selection of the characteristics in BAP services
 *
 *  Dependency: BAP_PACS_CLIENT or BAP_UCC
 */
/* #define BAP_SUPPORT_CONFIG_SELECTION */

/*
 *  BAP_SUPPORT_CONTEXT_MANAGE
 *
 *  This flag enables application interface to Retrieve and Save the
 *  context of BAP Services.
 *
 *  Dependency: BAP_PACS_CLIENT or BAP_UCC
 */
/* #define BAP_SUPPORT_CONTEXT_MANAGE */
#endif /* BAP_PACS_CLIENT */

/*
 *  BAP_BROADCAST
 *
 *  This flag enables the broadcast feature support in GA
 *
 *  Dependency: GA_BAP
 */
#define BAP_BROADCAST

#ifdef BAP_BROADCAST
/*
 *  BAP_BROADCAST_SOURCE
 *
 *  This flag enables the broadcast feature support in GA
 *
 *  Dependency: BAP_BROADCAST
 */
#define BAP_BROADCAST_SOURCE

/*
 *  BAP_BROADCAST_SINK
 *
 *  This flag enables the broadcast feature support in GA
 *
 *  Dependency: BAP_BROADCAST
 */
#define BAP_BROADCAST_SINK

/*
 *  BAP_BROADCAST_ASSISTANT
 *
 *  This flag enables the broadcast assistant feature support in GA
 *
 *  Dependency: BAP_BROADCAST
 */
#define BAP_BROADCAST_ASSISTANT

/*
 *  BAP_BROADCAST_SCAN_DELEGATOR
 *
 *  This flag enables the broadcast scan delegator feature support in GA.
 *  Mandatory if Broadcast Sink support is enabled.
 *
 *  Dependency: BAP_BROADCAST
 */
#define BAP_BROADCAST_SCAN_DELEGATOR

/*
 *  GA_BASS_CLIENT
 *
 *  This flag enables the BASS Client for Broadcast Assistant.
 *
 *  Dependency: BAP_BROADCAST
 */
#define GA_BASS_CLIENT

/*
 *  GA_BASS_SERVER
 *
 *  This flag enables the BASS Server for Scan delegator
 *  interfaces.
 *
 *  Dependency: BAP_BROADCAST
 */
#define GA_BASS_SERVER

#ifdef GA_BASS_CLIENT
/*
 *  BASS_SUPPORT_CONFIG_SELECTION
 *
 *  This flag enables application interface to configure the
 *  notification selection of the characteristics in BASS service
 *
 *  Dependency: GA_BASS_CLIENT
 */
/* #define BASS_SUPPORT_CONFIG_SELECTION */

/*
 *  BASS_SUPPORT_CONTEXT_MANAGE
 *
 *  This flag enables application interface to Retrieve and Save the
 *  context of BASS Service.
 *
 *  Dependency: GA_BASS_CLIENT
 */
/* #define BASS_SUPPORT_CONTEXT_MANAGE */
#endif /* GA_BASS_CLIENT */

#ifdef GA_BASS_SERVER
/*
 *  BASS_DB
 *
 *  This flag enables the DB for BASS Server.
 *
 *  Dependency: GA_BASS_SERVER
 */
#define BASS_DB
#endif /* GA_BASS_SERVER */

#ifdef BAP_BROADCAST_SOURCE
/*
 *  GA_SUPPORT_BC_ANNOUNCEMENT_END_IN_STREAMING
 *
 *  This flag enables the GA to support the possibility to end
 *  announcements during streaming. This would be non-compliant to the
 *  specification statemachine. Hence disabled by default.
 *
 *  Dependency: BAP_BROADCAST_SOURCE
 */
/* #define GA_SUPPORT_BC_ANNOUNCEMENT_END_IN_STREAMING */
#endif /* BAP_BROADCAST_SOURCE */
#endif /* BAP_BROADCAST */

/* Validate Dependencies in BAP */

#if ((!defined BAP_PACS_CLIENT) && (defined BAP_UCC))
#error "Mandatory to support BAP_PACS_CLIENT for BAP_UCC!"
#endif /* ((!defined BAP_PACS_CLIENT) && (defined BAP_UCC)) */

#if ((!defined BAP_PACS_SERVER) && (defined BAP_UCS))
#error "Mandatory to support BAP_PACS_SERVER for BAP_UCS!"
#endif /* ((!defined BAP_PACS_SERVER) && (defined BAP_UCS)) */

#if ((!defined BAP_PACS_SERVER) && (defined BAP_BROADCAST_SCAN_DELEGATOR))
#error "Mandatory to support BAP_PACS_SERVER for BAP_BROADCAST_SCAN_DELEGATOR"
#endif /* ((!defined BAP_PACS_SERVER) && (defined BAP_BROADCAST_SCAN_DELEGATOR)) */

#if ((!defined BAP_PACS_CLIENT) && (defined BAP_BROADCAST_ASSISTANT))
#error "Mandatory to support BAP_PACS_CLIENT for BAP_BROADCAST_ASSISTANT"
#endif /* ((!defined BAP_PACS_CLIENT) && (defined BAP_BROADCAST_ASSISTANT)) */

#if ((!defined GA_BASS_SERVER) && (defined BAP_BROADCAST_SCAN_DELEGATOR))
#error "Mandatory to support GA_BASS_SERVER for BAP_BROADCAST_SCAN_DELEGATOR"
#endif /* ((!defined GA_BASS_SERVER) && (defined BAP_BROADCAST_SCAN_DELEGATOR)) */

#if ((!defined GA_BASS_CLIENT) && (defined BAP_BROADCAST_ASSISTANT))
#error "Mandatory to support GA_BASS_CLIENT for BAP_BROADCAST_ASSISTANT"
#endif /* ((!defined GA_BASS_CLIENT) && (defined BAP_BROADCAST_ASSISTANT)) */

#if ((!defined BAP_BROADCAST_SINK) && (defined BAP_BROADCAST_SCAN_DELEGATOR))
#error "Mandatory to support BAP_BROADCAST_SINK for BAP_BROADCAST_SCAN_DELEGATOR"
#endif /* ((!defined BAP_BROADCAST_SINK) && (defined BAP_BROADCAST_SCAN_DELEGATOR)) */

#if ((!defined BAP_BROADCAST_SINK) && (defined BAP_BROADCAST_ASSISTANT))
#error "Mandatory to support BAP_BROADCAST_SINK for BAP_BROADCAST_ASSISTANT"
#endif /* ((!defined BAP_BROADCAST_SINK) && (defined BAP_BROADCAST_ASSISTANT)) */

#endif /* GA_BAP */

/* ----------------------------------------------------------------------- */
/* ============== VCP Specific Flags ===================================== */
/* ----------------------------------------------------------------------- */
#ifdef GA_VCP
/*
 *  VCP_CONTROLLER
 *
 *  This flag enables the Controller role of VCP
 *
 *  Dependency: GA_VCP
 */
#define VCP_CONTROLLER

/*
 *  VCP_RENDERER
 *
 *  This flag enables the Renderer role of VCP
 *
 *  Dependency: GA_VCP
 */
#define VCP_RENDERER

#ifdef VCP_CONTROLLER
/*
 *  VCP_SUPPORT_CONFIG_SELECTION
 *
 *  This flag enables application interface to configure the
 *  notification selection of the characteristics in VCP services
 *
 *  Dependency: VCP_CONTROLLER
 */
/* #define VCP_SUPPORT_CONFIG_SELECTION */

/*
 *  VCP_SUPPORT_CONTEXT_MANAGE
 *
 *  This flag enables application interface to Retrieve and Save the
 *  context of VCP Services.
 *
 *  Dependency: VCP_CONTROLLER
 */
/* #define VCP_SUPPORT_CONTEXT_MANAGE */
#endif /* VCP_CONTROLLER */
#endif /* GA_VCP */

/* ----------------------------------------------------------------------- */
/* ============== MICP Specific Flags ==================================== */
/* ----------------------------------------------------------------------- */
#ifdef GA_MICP
/*
 *  MICP_CONTROLLER
 *
 *  This flag enables the Controller role of MICP
 *
 *  Dependency: GA_MICP
 */
#define MICP_CONTROLLER

/*
 *  MICP_DEVICE
 *
 *  This flag enables the Device role of MICP
 *
 *  Dependency: GA_MICP
 */
#define MICP_DEVICE

#ifdef MICP_CONTROLLER
/*
 *  MICP_SUPPORT_CONFIG_SELECTION
 *
 *  This flag enables application interface to configure the
 *  notification selection of the characteristics in MICP services
 *
 *  Dependency: MICP_CONTROLLER
 */
/* #define MICP_SUPPORT_CONFIG_SELECTION */

/*
 *  MICP_SUPPORT_CONTEXT_MANAGE
 *
 *  This flag enables application interface to Retrieve and Save the
 *  context of MICP Services.
 *
 *  Dependency: MICP_CONTROLLER
 */
/* #define MICP_SUPPORT_CONTEXT_MANAGE */
#endif /* MICP_CONTROLLER */
#endif /* GA_MICP */

/* ----------------------------------------------------------------------- */
/* ============== CSIP Specific Flags ==================================== */
/* ----------------------------------------------------------------------- */
#ifdef GA_CSIP
/*
 *  CSIP_COORDINATOR
 *
 *  This flag enables the Set Coordinator role of CSIP
 *
 *  Dependency: GA_CSIP
 */
#define CSIP_COORDINATOR

/*
 *  CSIP_MEMBER
 *
 *  This flag enables the Set Member role of CSIP
 *
 *  Dependency: GA_CSIP
 */
#define CSIP_MEMBER

#ifdef CSIP_COORDINATOR
/*
 *  CSIP_SUPPORT_CONFIG_SELECTION
 *
 *  This flag enables application interface to configure the
 *  notification selection of the characteristics in CSIP services
 *
 *  Dependency: CSIP_COORDINATOR
 */
/* #define CSIP_SUPPORT_CONFIG_SELECTION */

/*
 *  CSIP_SUPPORT_CONTEXT_MANAGE
 *
 *  This flag enables application interface to Retrieve and Save the
 *  context of CSIP Services.
 *
 *  Dependency: CSIP_COORDINATOR
 */
/* #define CSIP_SUPPORT_CONTEXT_MANAGE */
#endif /* CSIP_COORDINATOR */

/*
 *  CSIP_CB_FOR_INVALID_PDU_PARAMETER
 *
 *  This flag enables CSIP to deliver callback to application
 *  even after identifying as incorrect PDU parameter and sending
 *  error response.
 *
 *  By default, this flag is disabled. No application callback would
 *  be indicated.
 *
 *  Dependency: GA_CSIP
 */
/* #define CSIP_CB_FOR_INVALID_PDU_PARAMETER */
#endif /* GA_CSIP */

/* Validate Dependencies in CAP */

#if ((!defined CSIP_COORDINATOR) && (defined CAP_CSIP_COORDINATOR))
#error "Mandatory to support CSIP_COORDINATOR for CAP_CSIP_COORDINATOR!"
#endif /* ((!defined CSIP_COORDINATOR) && (defined CAP_CSIP_COORDINATOR)) */

#if ((!defined CSIP_MEMBER) && (defined CAP_CSIP_MEMBER))
#error "Mandatory to support CSIP_MEMBER for CAP_CSIP_MEMBER!"
#endif /* ((!defined CSIP_MEMBER) && (defined CAP_CSIP_MEMBER)) */
/* ----------------------------------------------------------------------- */
/* ============== CCP Specific Flags ===================================== */
/* ----------------------------------------------------------------------- */
#ifdef GA_CCP
/*
 *  CCP_CLIENT
 *
 *  This flag enables the Client role of CCP
 *
 *  Dependency: GA_CCP
 */
#define CCP_CLIENT

/*
 *  CCP_SERVER
 *
 *  This flag enables the Server role of CCP
 *
 *  Dependency: GA_CCP
 */
#define CCP_SERVER

#ifdef CCP_CLIENT
/*
 *  CCP_SUPPORT_CONFIG_SELECTION
 *
 *  This flag enables application interface to configure the
 *  notification selection of the characteristics in CCP services
 *
 *  Dependency: CCP_CLIENT
 */
/* #define CCP_SUPPORT_CONFIG_SELECTION */

/*
 *  CCP_SUPPORT_CONTEXT_MANAGE
 *
 *  This flag enables application interface to Retrieve and Save the
 *  context of CCP Services.
 *
 *  Dependency: CCP_CLIENT
 */
/* #define CCP_SUPPORT_CONTEXT_MANAGE */
#endif /* CCP_CLIENT */
#endif /* GA_CCP */

/* ----------------------------------------------------------------------- */
/* ============== MCP Specific Flags ===================================== */
/* ----------------------------------------------------------------------- */
#ifdef GA_MCP
/*
 *  MCP_CLIENT
 *
 *  This flag enables the Client role of MCP
 *
 *  Dependency: GA_MCP
 */
#define MCP_CLIENT

/*
 *  MCP_SERVER
 *
 *  This flag enables the Server role of MCP
 *
 *  Dependency: GA_MCP
 */
#define MCP_SERVER

#ifdef MCP_CLIENT
/*
 *  MCP_SUPPORT_CONFIG_SELECTION
 *
 *  This flag enables application interface to configure the
 *  notification selection of the characteristics in MCP services
 *
 *  Dependency: MCP_CLIENT
 */
/* #define MCP_SUPPORT_CONFIG_SELECTION */

/*
 *  MCP_SUPPORT_CONTEXT_MANAGE
 *
 *  This flag enables application interface to Retrieve and Save the
 *  context of MCP Services.
 *
 *  Dependency: MCP_CLIENT
 */
/* #define MCP_SUPPORT_CONTEXT_MANAGE */
#endif /* MCP_CLIENT */

/*
 *  MCP_SUPPORT_OBJECT_TRANSFER
 *
 *  This flag enables the Object Transsfer handling support in MCP
 *
 *  Dependency: GA_MCP
 */
#define MCP_SUPPORT_OBJECT_TRANSFER

#ifdef MCP_SUPPORT_OBJECT_TRANSFER
/*
 *  OTP_CLIENT
 *
 *  This flag enables the Object Transfer Client support in GA
 *
 *  Dependency: MCP_SUPPORT_OBJECT_TRANSFER
 */
#define OTP_CLIENT

/*
 *  OTP_SERVER
 *
 *  This flag enables the Object Transsfer Server support in GA
 *
 *  Dependency: MCP_SUPPORT_OBJECT_TRANSFER
 */
#define OTP_SERVER
#endif /* MCP_SUPPORT_OBJECT_TRANSFER */
#endif /* GA_MCP */

/* ----------------------------------------------------------------------- */
/* ============== HAP Specific Flags ===================================== */
/* ----------------------------------------------------------------------- */
#ifdef GA_HAP
/*
 *  HAP_CLIENT
 *
 *  This flag enables the Client role of HAP
 *
 *  Dependency: GA_HAP
 */
#define HAP_CLIENT

#ifdef HAP_CLIENT
/*
 *  HAP_SUPPORT_CONFIG_SELECTION
 *
 *  This flag enables application interface to configure the
 *  notification selection of the characteristics in HAP services
 *
 *  Dependency: HAP_CLIENT
 */
/* #define HAP_SUPPORT_CONFIG_SELECTION */

/*
 *  HAP_SUPPORT_CONTEXT_MANAGE
 *
 *  This flag enables application interface to Retrieve and Save the
 *  context of HAP Services.
 *
 *  Dependency: HAP_CLIENT
 */
/* #define HAP_SUPPORT_CONTEXT_MANAGE */
#endif /* HAP_CLIENT */

/*
 *  HAP_SERVER
 *
 *  This flag enables the Server role of HAP
 *
 *  Dependency: GA_HAP
 */
#define HAP_SERVER
#endif /* GA_HAP */

/* ----------------------------------------------------------------------- */
/* ============== TMAP Specific Flags ===================================== */
/* ----------------------------------------------------------------------- */
#ifdef GA_TMAP
/*
 *  TMAP_CLIENT
 *
 *  This flag enables the Client role of TMAP
 *
 *  Dependency: GA_TMAP
 */
#define TMAP_CLIENT

#ifdef TMAP_CLIENT
/*
 *  TMAP_SUPPORT_CONTEXT_MANAGE
 *
 *  This flag enables application interface to Retrieve and Save the
 *  context of TMAP Services.
 *
 *  Dependency: TMAP_CLIENT
 */
/* #define TMAP_SUPPORT_CONTEXT_MANAGE */
#endif /* TMAP_CLIENT */

/*
 *  TMAP_SERVER
 *
 *  This flag enables the Server role of TMAP
 *
 *  Dependency: GA_TMAP
 */
#define TMAP_SERVER
#endif /* GA_TMAP */

/* ----------------------------------------------------------------------- */
/* ============== Common GA SDK Flags ==================================== */
/* ----------------------------------------------------------------------- */
/*
 *  GA_HAVE_DYNAMIC_CONFIG
 *
 *  This flag enables the dynamic configuration of GA at runtime
 *
 *  Dependency: None
 */
#define GA_HAVE_DYNAMIC_CONFIG

/* ----------------------------------------------------------------------- */
/* ==== Debug Specification Flags ======================================== */
/* ----------------------------------------------------------------------- */

/**
 *  Flag to control debug logging at run time.
 *  Debug level can be set using GA_set_debug_level() API.
 *  In addition there are interfaces to enable/disable module specific flag at run time.
 */
#define GA_ENABLE_DISABLE_RUNTIME_DEBUG

/* Profile Modules */

#define  BRR_NO_DEBUG
/* #define  BRR_DEBUG */

#define  BAP_NO_DEBUG
/* #define  BAP_DEBUG */

#define  BASS_NO_DEBUG
/* #define  BASS_DEBUG */

#define  CAP_NO_DEBUG
/* #define  CAP_DEBUG */

#define  CSIP_NO_DEBUG
/* #define  CSIP_DEBUG */

#define  MICP_NO_DEBUG
/* #define  MICP_DEBUG */

#define  VCP_NO_DEBUG
/* #define  VCP_DEBUG */

#define  MCP_NO_DEBUG
/* #define  MCP_DEBUG */

#define OTP_NP_DEBUG
/* #define  OTP_DEBUG */

#define  CCP_NO_DEBUG
/* #define  CCP_DEBUG */

#define  HAP_NO_DEBUG
/* #define  HAP_DEBUG */

#define  TMAP_NO_DEBUG
/* #define  TMAP_DEBUG */

#endif /* _H_GA_FEATURES_ */
