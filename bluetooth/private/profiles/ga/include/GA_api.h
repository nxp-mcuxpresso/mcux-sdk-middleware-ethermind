
/**
 *  \file GA_api.h
 *
 *  \brief This file defines the Generic Audio Core Application Interface - includes
 *  Data Structures and Methods.
 */

/*
 *  Copyright (C) 2020. Mindtree Ltd.
 *  All rights reserved.
 */

#ifndef _H_GA_API_
#define _H_GA_API_

/**
 * \addtogroup bt_ga GA
 * \{
 */

/* --------------------------------------------- Header File Inclusion */
#include "GA_common.h"
#include "GA_bearer_api.h"

#include "bap.h"
#include "vcp.h"
#include "micp.h"
#include "csip.h"

/* --------------------------------------------- Global Definitions */
/**
 * \defgroup bt_ga_profiles Profiles
 * \{
 * \brief This section describes the interfaces & APIs offered by the EtherMind
 * Generic Audio (GA) Profile module to the Application.
 */

/** \} */

/**
 * \defgroup bt_ga_core Core
 * \{
 * \brief This section describes the interfaces & APIs offered by the EtherMind
 * Generic Audio (GA) Core module to the Application and other upper
 * layers of the stack.
 */

/**
 * \defgroup ga_cap_module CAP
 * \{
 * \brief This section describes the interfaces & APIs offered by the EtherMind
 * GA CAP module to the Application.
 */

/**
 * \defgroup ga_common_module Common
 * \{
 * \brief This section describes the interfaces & APIs offered by EtherMind
 * module, which are common through all profile modules to the Application. \n
 */

/**
 * \defgroup ga_common_defines Defines
 * \{
 * \brief This section describes the various Defines in EtherMind
 * GA Layer which are common for all modules.
 */

/**
 * \defgroup ga_common_error_code_def Error Code Definitions
 * \{
 * \brief This sections describes all the Error ID for GA Layer and
 * Common Error Codes exposed and used by the EtherMind GA Layer.
 */

/**
 * \defgroup ga_common_error_group Error Grouping
 * \{
 * \brief This sections describes various Error Code Groupings exposed by the
 * EtherMind GA Layer.
 */

/** \} */

/**
 * \defgroup ga_common_error_code Error Codes
 * \{
 * \brief This section lists the Common Error Codes that are provided as part
 * of return of functionalities.
 */

/** \} */

/** \} */

/**
 * \defgroup ga_common_constants Constants
 * \{
 * \brief This section describes the various Constants in EtherMind
 * GA Layer which are common for all modules.
 */

/** \} */

/**
 * \defgroup ga_common_structures Structures
 * \{
 * \brief This section lists the various data structures and typedefs for use
 * by all modules.
 */

/** \} */

/**
 * \defgroup ga_common_macros Utility Macros
 * \{
 * \brief This section describes Initialization and other Utility Macros
 * offered by GA.
 */

/** \} */
/** \} */

/**
 * \defgroup ga_common_api_defs API Definitions
 * \{
 * \brief This section describes the Generic Audio APIs.
 * This section describes the Common APIs.
 */

/** \} */

/**
 * \defgroup ga_common_cb Application Callback
 * \{
 * \brief This Section Describes the module Common Notification Callback
 * interface offered to the application.
 */

/** \} */

/** \} */

/**
 * \defgroup ga_cas_module Common Audio Service (CAS)
 * \{
 * \brief This section describes the interfaces & APIs offered by the EtherMind
 * Common Audio Service(CAS) module to the Application. \n
 * Common Audio Service shall be instantiated as a Primary Service and may be
 * included by other services. \n
 * If the device implementing CAS is a member of a Coordinated Set, the CAS
 * instance shall include the CSIS instance that identifies the Coordinated Set
 * as an included service.
 */

/** \} */

/**
 * \defgroup ga_csip_module Coordinated Set Identification Profile (CSIP)
 * \{
 * \brief This section describes the interfaces & APIs offered by the EtherMind
 * Coordinated Set Identification Profile(CSIP) module to the CAP
 * layers of the stack. \n
 * Coordinated Set Identification Service shall be instantiated as a Primary
 * Service.
 */

/** \} */

/**
 * \defgroup ga_micp_module Microphone Control Profile (MICP)
 * \{
 * \brief This section describes the interfaces & APIs offered by the EtherMind
 * Microphone Control Profile (MICP) module to the CAP layer of the stack. \n
 * Microphone Control Profile Service shall be instantiated as Primary
 * Service. \n
 * The Audio Input Control Service shall only be instantiated as an
 * included service. \n
 * Microphone Control Profile includes Audio Input Control Service.
 */

/** \} */

/**
 * \defgroup ga_vcp_module Volume Control Profile (VCP)
 * \{
 * \brief This section describes the interfaces & APIs offered by the EtherMind
 * Volume Control Profile (VCP) module to the CAP layer of the stack. \n
 * Volume Control Service is a Primary Service. \n
 * Volume Offset Control Service shall only be instantiated as an included
 * service. \n
 * Audio Input Control Service shall only be instantiated as an included
 * service. \n
 * Volume Control Service includes Volume Offset Control Service and
 * Audio Input Control Service.
 */

/** \} */

/**
 * \defgroup ga_bap_module Basic Audio Profile (BAP)
 * \{
 * \brief This section describes the interfaces & APIs offered by the EtherMind
 * Basic Audio Profile (BAP) Unicast and Broadcast module to the
 * CAP layer of the stack.
 * BAP roles used for unicast audio: Unicast Server and
 * Unicast Client. \n
 * BAP roles used for broadcast audio: Broadcast Source,
 * Broadcast Sink, Broadcast Assistant (BA), and Scan Delegator (SD).
 */

/**
 * \defgroup ga_bap_uc_module Unicast (UC)
 * \{
 * \brief This section describes the interfaces & APIs offered by the EtherMind
 * Basic Audio Profile (BAP) Unicast module to the CAP layer of the stack. \n
 * Published Audio Capabilities Service (PACS) is a Primary Service. \n
 * Audio Stream Control Service (ASCS) is a Primary Service.
 */

/**
 * \defgroup ga_bap_uc_defines Defines
 * \{
 * \brief This section describes the BAP Unicast Defines
 * (PACS and ASCS).
 */

/** \} */

/**
 * \defgroup ga_bap_uc_api_defs API Definitions
 * \{
 * \brief This section describes the BAP Unicast API Definitions
 * (PACS and ASCS).
 */

/** \} */

/**
 * \defgroup ga_bap_uc_api_sequences API Sequences
 * \{
 * \brief This section describes the BAP Unicast API Sequences(PACS and ASCS).
 */

/** \} */

/** \} */

/**
 * \defgroup ga_bap_bc_module Broadcast (BC)
 * \{
 * \brief This section describes the interfaces & APIs offered by the EtherMind
 * Basic Audio Profile (BAP) Broadcast module to the CAP layer of the stack. \n
 * Broadcast Audio Scan Service (BASS) is a Primary Service used by Broadcast.
 */

/**
 * \defgroup ga_bap_bc_defines Defines
 * \{
 * \brief This section describes the BAP Broadcast Defines.
 */

/** \} */

/**
 * \defgroup ga_bap_bc_api_defs API Definitions
 * \{
 * \brief This section describes the BAP Broadcast API Definitions.
 */

/** \} */

/**
 * \defgroup ga_bap_bc_cb Application Callback
 * \{
 * \brief This section describes the BAP Broadcast Application Callback.
 */

/** \} */

/**
 * \defgroup ga_bap_bc_api_sequences API Sequences
 * \{
 * \brief This section describes the BAP Broadcast API Sequences
 * (Broadcast Source, Broadcast Sink, Broadcast Assistant, Scan Delegator).
 */

/** \} */

/** \} */

/**
 * \defgroup ga_bap_common_module Common
 * \{
 * \brief This section describes the interfaces & APIs offered by the EtherMind
 * Basic Audio Profile (BAP) Common module to the CAP layer of the stack.
 */

/**
 * \defgroup ga_bap_common_defines Defines
 * \{
 * \brief This section describes the common BAP Unicast and Broadcast Defines.
 */

/**
 * \defgroup ga_bap_common_error_code Error Codes
 * \{
 * \brief This section lists the Error Codes that are provided as part of
 * return of functionalities of BAP \ref ga_bap_uc_api_defs and
 * \ref ga_bap_bc_api_defs.
 */

/** \} */

/**
 * \defgroup ga_bap_common_constants Constants
 * \{
 * \brief This section describes the common BAP Unicast and Broadcast
 * Constants.
 */

/** \} */

/**
 * \defgroup ga_bap_common_structures Structures
 * \{
 * \brief This section lists the various data structures and typedefs for use
 * by Unicast and Broadcast.
 */

/** \} */

/** \} */

/** \} */
/** \} */

/**
 * \addtogroup ga_cas_module
 * \{
 */

/**
 * \defgroup ga_cas_defines Defines
 * \{
 * \brief This section describes the various Defines in EtherMind
 * GA CAP Layer.
 */

/**
 * \defgroup ga_cas_error_code Error Codes
 * \{
 * \brief This section lists the Error Codes that are provided as part of
 * return of functionalities of CAP \ref ga_cas_api_defs.
 */

/** \} */

/**
 * \defgroup ga_cas_constants Constants
 * \{
 * \brief This section describes the various Constants in EtherMind
 * GA CAP Layer.
 */

/**
 * \name Core Modules
 * \{
 * \brief Identify BAP, VCP, MICP, CSIP
 */

/** GA Module - BAP */
#define GA_MODULE_BAP       0x00U
/** GA Module - VCP */
#define GA_MODULE_VCP       0x01U
/** GA Module - MICP */
#define GA_MODULE_MICP      0x02U
/** GA Module - CSIP */
#define GA_MODULE_CSIP      0x03U

/** \} */

/**
 * \name CAP Roles
 * \{
 * \brief Bitmasks Type : Initiator, Acceptor, Commander
 */

/** CAP Role - Initiator */
#define CAP_ROLE_INITIATOR   0x01U
/** CAP Role - Acceptor */
#define CAP_ROLE_ACCEPTOR    0x02U
/** CAP Role - Commander */
#define CAP_ROLE_COMMANDER   0x04U

/** \} */

/**
 * \name CAP Announcement Type
 * \{
 * \brief Type : Size(Octets): 1
 */

/** CAP Announcement Type - General */
#define CAS_GENERAL_ANNOUNCEMENT   0x00U
/** CAP Announcement Type - Targeted */
#define CAS_TARGETED_ANNOUNCEMENT  0x01U

/** \} */

/**
 * \name CAP Set Operations
 * \{
 * \brief Type : Size(Octets): 1
 */

/** CAP Set Operation: Invalid */
#define CAP_SETOP_INVALID           0x00U
/** CAP Set Operation: Lock Release */
#define CAP_SETOP_LOCKRELEASE       0x01U
/** CAP Set Operation: Lock Request */
#define CAP_SETOP_LOCKREQUEST       0x02U
/** CAP Set Operation: Ordered Access */
#define CAP_SETOP_ORDEREDACCESS     0x03U

/** \} */

/** \} */

/** \} */
/** \} */

/**
 * \addtogroup ga_bap_module
 * \{
 */

/**
 * \addtogroup ga_bap_uc_module
 * \{
 */

/**
 * \addtogroup ga_bap_uc_defines
 * \{
 */

/**
 * \defgroup ga_bap_uc_common_def UC - Common
 * \{
 * \brief This section describes the various Common Defines in EtherMind
 * GA BAP Layer for UC Client and Server.
 */

/**
 * \defgroup ga_bap_uc_common_constants Constants
 * \{
 * \brief This section describes the various Common Constants in EtherMind
 * GA BAP Layer for UC Client and Server.
 */

/**
 * \name Audio Role
 * \{
 * \brief Type : Size(Octets): 1
 */

/** GA Audio Role - Sink */
#define GA_ROLE_SINK                BAP_ROLE_SINK
/** GA Audio Role - Source */
#define GA_ROLE_SOURCE              BAP_ROLE_SOURCE

/** \} */
/** \} */
/** \} */

/**
 * \defgroup ga_bap_uc_client_server_ascs_def UC Client & Server - ASCS
 * \{
 * \brief This section describes the various Defines in EtherMind
 * GA BAP Layer for UC Client and Server - ASCS.
 */

/**
 * \defgroup ga_bap_uc_client_server_ascs_constants Constants
 * \{
 * \brief This section describes the various Constants in EtherMind
 * GA BAP Layer for UC Client and Server - ASCS.
 */

/**
 * \name BAP Announcement Type
 * \{
 * \brief Type : Size(Octets): 1
 */

/** BAP Announcement Type - General */
#define BAP_ASCS_GENERAL_ANNOUNCEMENT   0x00U
/** BAP Announcement Type - Targeted */
#define BAP_ASCS_TARGETED_ANNOUNCEMENT  0x01U

/** \} */
/** \} */
/** \} */

/**
 * \defgroup ga_bap_uc_client_server_pacs_def UC Client & Server - PACS
 * \{
 * \brief This section describes the various Defines in EtherMind
 * GA BAP Layer for UC Client and Server - PACS.
 */

/**
 * \defgroup ga_bap_uc_client_server_pacs_constants Constants
 * \{
 * \brief This section describes the various Constants in EtherMind
 * GA BAP Layer for UC Client and Server - PACS.
 */

/**
 * \name Capabilities Type
 * \{
 * \brief Type : Size(Octets): 1
 */

/** GA Capabilities Type - Codecs */
#define GA_CAP_TYPE_CODECS          0x01U
/** GA Capabilities Type - Locations */
#define GA_CAP_TYPE_LOCATIONS       0x02U
/** GA Capabilities Type - Supported Contexts */
#define GA_CAP_TYPE_SUPP_CONTEXTS   0x03U
/** GA Capabilities Type - Available Contexts */
#define GA_CAP_TYPE_AVAIL_CONTEXTS  0x04U

/** \} */
/** \} */
/** \} */

/** \} */
/** \} */

/**
 * \addtogroup ga_bap_bc_module
 * \{
 */

/**
 * \addtogroup ga_bap_bc_defines
 * \{
 */

/**
 * \defgroup ga_bap_bc_source_sink_common_def BC Source & Sink - Common
 * \{
 * \brief This section describes the various Common Defines in EtherMind
 * GA BAP Layer for BC Source and Sink.
 */

/**
 * \defgroup ga_bap_bc_source_sink_common_constants Constants
 * \{
 * \brief This section describes the various Common Constants in EtherMind
 * GA BAP Layer for BC Source and Sink.
 */

/**
 * \name Broadcast ID Size
 * \{
 */

/** Broadcast_ID Length */
#define GA_BC_ID_LEN                BAP_BC_ID_LEN

/** \} */
/** \} */
/** \} */

/** \} */
/** \} */

/**
 * \addtogroup ga_bap_uc_module
 * \{
 */

/**
 * \addtogroup ga_bap_uc_defines
 * \{
 */

/**
 * \defgroup ga_bap_uc_server_ascs_def UC Server - ASCS
 * \{
 * \brief This section describes the various Defines in EtherMind
 * GA BAP Layer for Unicast Server - ASCS.
 */

/**
 * \defgroup ga_bap_uc_server_ascs_constants Constants
 * \{
 * \brief This section describes the various Constants in EtherMind
 * GA BAP Layer for Unicast Server - ASCS.
 */

/**
 * \name Suspend/Release Reason Type
 * \{
 * \brief Type : Size(Octets): 1
 */
/** ASE Suspend/Release reason used during Autonomous Proc(Server) */
#define GA_ASE_SUSPEND_RELEASE_REASON_NONE     0x00

/** ASE Suspend/Release reason used during Autonomous Proc(Server) - CIS Loss */
#define GA_ASE_SUSPEND_RELEASE_REASON_CIS_LOSS 0x01

/** \} */
/** \} */
/** \} */

/**
 * \defgroup ga_bap_uc_client_pacs_def UC Client - PACS
 * \{
 * \brief This section describes the various Defines in EtherMind
 * GA BAP Layer for Unicast Client - PACS.
 */

/**
 * \defgroup ga_bap_uc_client_pacs_evt_defs Events
 * \{
 * \brief This section describes the Generic Audio Events for
 * Unicast Client - PACS.
 */

/**
 * \brief This event is notified once the discovery and configuration for
 * notification is done on the peer for PACS Service. The roles discovered on
 * the remote is notified in the callback \ref GA_PROFILE_CB registered during
 * \ref GA_uc_client_init().
 * The data is of type \ref ga_bap_uc_common_constants and the length is 1B.
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \note If both Source and Sink PAC records are discovered on remote, the
 *       data will include both roles ORred in a single event.
 *
 * \sa ga_bap_uc_common_constants
 */
#define GA_SETUP_CNF                0x01U

/**
 * \brief This event is notified once the configuration for
 * notification is disabled on the peer for PACS and ASCS Service.
 * The context of the remote device is cleared. \n
 * Once complete, event is notified in the callback \ref GA_PROFILE_CB
 * registered during \ref GA_uc_client_init().
 * The data is NULL and the length is 0B.
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \note If both PACS records and ASCS is discovered on the remote device,
 *       the configuration disable and the context clear happens for both. \n
 *       If ASCS is not done, then only PACS is cleared.
 */
#define GA_RELEASE_CNF              0x02U

/**
 * \brief This event is notified once the Capabilities of the peer for the
 * requested role is determined. The parameters shall be as below and is
 * notified via the callback \ref GA_PROFILE_CB registered during
 * \ref GA_uc_client_init().
 *
 * PACS - Read request on the PACS char as per role requested is done in a
 * chained manner to determine number of PACS records, record details,
 * Audio Locations, Available and Supported Contexts. The event is notified
 * multiple times indicating the capability type with status as
 * \ref GA_CONTINUE and finally with \ref GA_SUCCESS.
 *
 * The data is of type \ref GA_CAP_ENDPOINT. \n
 * Based on the role and the type defined in \ref GA_CAP_ENDPOINT, the data
 * parameters shall vary. \n
 * Capability Type: \ref ga_bap_uc_client_server_pacs_constants \n
 *    - \ref GA_CAP_TYPE_CODECS :
 *         - data: Pointer to data with First byte indicating Number of PACS
 *                 Records, followed by \ref GA_CODEC_INFO followed by
 *                 \ref GA_METADATA.
 *                 Refer \ref ga_bap_common_constants
 *         - datalen: Length of above.
 *         .
 *    - \ref GA_CAP_TYPE_LOCATIONS :
 *         - data: Pointer to \ref UINT32, \n
 *                 Represents Supported Context values as bitmask.
 *                 Refer \ref ga_common_constants
 *         - datalen: \ref sizeof ( \ref UINT32 )
 *         .
 *    - \ref GA_CAP_TYPE_SUPP_CONTEXTS :
 *         - data: Pointer to \ref UINT16, \n
 *                 Represents Supported Context values as bitmask.
 *                 Refer \ref ga_bap_common_constants
 *         - datalen: \ref sizeof ( \ref UINT16 )
 *         .
 *    - \ref GA_CAP_TYPE_AVAIL_CONTEXTS :
 *         - data: Pointer to \ref UINT16, \n
 *                 Represents Available Context values as bitmask.
 *                 Refer \ref ga_bap_common_constants
 *         - datalen: \ref sizeof ( \ref UINT16 )
 *         .
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_GET_CAPABILITIES_CNF     0x03U

/** \} */
/** \} */

/**
 * \defgroup ga_bap_uc_client_ascs_def UC Client - ASCS
 * \{
 * \brief This section describes the various Defines in EtherMind
 * GA BAP Layer for Unicast Client - ASCS.
 */

/**
 * \defgroup ga_bap_uc_client_ascs_evt_defs Events
 * \{
 * \brief This section describes the Generic Audio Events for
 * Unicast Client - ASCS.
 */

/**
 * \brief This event is notified once the discovery of ASCS Service, Char, Desc
 * and configuration of notification is complete along with reading of the
 * ASE Sink and ASE Source Char on the peer. \n
 * A Callback is made to \ref GA_PROFILE_CB registered during
 * \ref GA_uc_client_init().
 *
 * The event is notified multiple times indicating the ASEs present on the
 * peer device with role and its ASE along with the status as
 * \ref GA_CONTINUE and finally with \ref GA_SUCCESS.
 *
 * The data is of type \ref GA_ASE_INFO. \n
 * The data inside \ref GA_ASE_INFO shall be \ref GA_ASE_INFO_IN_IDLE.
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \sa ga_bap_uc_client_server_ascs_constants
 */
#define GA_SEP_DISCOVER_CNF         0x04U

/**
 * \brief This event is notified once the response for Config Codec operation
 * is received form the peer. In this event, the server exposed preferred QoS
 * parameters are notified in this format \ref GA_ASE_INFO_IN_CODEC_CONF. \n
 * A Callback is made to \ref GA_PROFILE_CB registered during
 * \ref GA_uc_client_init().
 *
 * The data is of type \ref GA_ASE_INFO. \n
 * The data inside \ref GA_ASE_INFO shall be \ref GA_ASE_INFO_IN_CODEC_CONF.
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \sa ga_bap_uc_client_server_ascs_constants
 * \sa ga_bap_uc_client_ascs_constants
 * \sa ga_bap_common_constants
 */
#define GA_SEP_CONFIGURE_CNF        0x05U

/**
 * \brief This event is notified once the response for QoS Config operation is
 * received form the peer. In this event, the server provides the accepted QoS
 * parameters which is notified in this format \ref GA_ASE_INFO_IN_QOS_CONF. \n
 * A Callback is made to \ref GA_PROFILE_CB registered during
 * \ref GA_uc_client_init().
 *
 * The data is of type \ref GA_ASE_INFO. \n
 * The data inside \ref GA_ASE_INFO shall be \ref GA_ASE_INFO_IN_QOS_CONF.
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \sa ga_bap_uc_client_server_ascs_constants
 * \sa ga_bap_common_constants
 */
#define GA_SEP_SETUP_CNF            0x06U

/**
 * \brief This event is notified once the response for Enable operation is
 * received form the peer. In this event, the server provides the Metadata
 * parameters which is notified in this format
 * \ref GA_ASE_INFO_IN_ENABLING_STREAMING_DISABLING. \n
 * A Callback is made to \ref GA_PROFILE_CB registered during\
 * \ref GA_uc_client_init().
 *
 * The data is of type \ref GA_ASE_INFO. \n
 * The data inside \ref GA_ASE_INFO shall be
 * \ref GA_ASE_INFO_IN_ENABLING_STREAMING_DISABLING.
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \sa ga_bap_uc_client_server_ascs_constants
 * \sa ga_bap_common_constants
 */
#define GA_SEP_START_CNF            0x07U

/**
 * \brief This event is notified once the response for Disable operation is
 * received form the peer. In this event, the server provides the Metadata
 * parameters which is notified in this format
 * \ref GA_ASE_INFO_IN_ENABLING_STREAMING_DISABLING. \n
 * A Callback is made to \ref GA_PROFILE_CB registered during
 * \ref GA_uc_client_init().
 *
 * The data is of type \ref GA_ASE_INFO. \n
 * The data inside \ref GA_ASE_INFO shall be
 * \ref GA_ASE_INFO_IN_ENABLING_STREAMING_DISABLING.
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \sa ga_bap_uc_client_server_ascs_constants
 * \sa ga_bap_common_constants
 */
#define GA_SEP_SUSPEND_CNF          0x08U

/**
 * \brief This event is notified once the response for Update Metadata
 * operation is received form the peer. In this event, the server provides the
 * Metadata parameters which is notified in this format
 * \ref GA_ASE_INFO_IN_ENABLING_STREAMING_DISABLING. \n
 * A Callback is made to \ref GA_PROFILE_CB registered during
 * \ref GA_uc_client_init().
 *
 * The data is of type \ref GA_ASE_INFO. \n
 * The data inside \ref GA_ASE_INFO shall be
 * \ref GA_ASE_INFO_IN_ENABLING_STREAMING_DISABLING.
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \sa ga_bap_uc_client_server_ascs_constants
 * \sa ga_bap_common_constants
 */
#define GA_SEP_UPDATE_CNF           0x09U

/**
 * \brief This event is notified once the response for Release operation is
 * received form the peer. \n
 * A Callback is made to \ref GA_PROFILE_CB registered during
 * \ref GA_uc_client_init().
 *
 * The data is of type \ref GA_ASE_INFO. \n
 * The data inside \ref GA_ASE_INFO shall be NULL.
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \sa ga_bap_uc_client_server_ascs_constants
 */
#define GA_SEP_RELEASE_CNF          0x0AU

/**
 * \brief This event is notified once the response for Receiver Start Ready
 * operation is received form the peer. In this event, the server provides the
 * Metadata parameters which is notified in this format
 * \ref GA_ASE_INFO_IN_ENABLING_STREAMING_DISABLING. \n
 * A Callback is made to \ref GA_PROFILE_CB registered during
 * \ref GA_uc_client_init().
 *
 * The data is of type \ref GA_ASE_INFO. \n
 * The data inside \ref GA_ASE_INFO shall be
 * \ref GA_ASE_INFO_IN_ENABLING_STREAMING_DISABLING.
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \note This event is generated post calling \ref GA_sep_receiver_start_ready,
 *       when Local Client ASE is a Sink.
 *
 * \sa ga_bap_uc_client_server_ascs_constants
 * \sa ga_bap_common_constants
 */
#define GA_SEP_RX_START_READY_CNF   0x0BU

/**
 * \brief This event is notified once the response for Receiver Start Ready
 * operation is received form the peer. In this event, the server provides the
 * Metadata parameters which is notified in this format
 * \ref GA_ASE_INFO_IN_ENABLING_STREAMING_DISABLING. \n
 * A Callback is made to \ref GA_PROFILE_CB registered during
 * \ref GA_uc_client_init().
 *
 * The data is of type \ref GA_ASE_INFO. \n
 * The data inside \ref GA_ASE_INFO shall be
 * \ref GA_ASE_INFO_IN_ENABLING_STREAMING_DISABLING.
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \note This event is generated post calling \ref GA_sep_receiver_stop_ready,
 *       when Local Client ASE is a Sink.
 *
 * \sa ga_bap_uc_client_server_ascs_constants
 * \sa ga_bap_common_constants
 */
#define GA_SEP_RX_STOP_READY_CNF    0x0CU

/** \} */
/** \} */

/**
 * \addtogroup ga_bap_uc_server_ascs_def
 * \{
 */

/**
 * \defgroup ga_bap_uc_server_ascs_evt_defs Events
 * \{
 * \brief This section describes the Generic Audio Events for
 * Unicast Server - ASCS.
 */

/**
 * \brief This event is notified once the Codec Config opcode
 * is received form the peer. In this event, the client provides the Codec
 * conf parameters which is notified in this format
 * \ref GA_SEP_CONF. \n
 * Internally this event is generated once the ASE CP for Config Codec is
 * received, The Application shall set the response along with the
 * reason for the respective ASE CP. Post this the ASE Sink or ASE Source
 * Notification is done by the Stack. \n
 * A Callback is made with the parameters as below and is notified via
 * \ref GA_PROFILE_CB registered during \ref GA_uc_server_init().
 *
 * The data is of type \ref GA_SEP_INFO. \n
 * The info inside \ref GA_SEP_INFO shall be \ref GA_SEP_CONF.
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \sa ga_bap_uc_common_constants
 * \sa ga_bap_uc_server_ascs_constants
 * \sa ga_bap_common_constants
 */
#define GA_SEP_CONFIGURE_IND        0x11U

/**
 * \brief This event is notified once the Codec QoS opcode
 * is received form the peer. In this event, the client provides the Codec
 * conf parameters which is notified in this format
 * \ref GA_QOS_CONF. \n
 * Internally this event is generated once the ASE CP for Config QoS is
 * received, The Application shall set the response along with the
 * reason for the respective ASE CP. Post this the ASE Sink or ASE Source
 * Notification is done by the Stack. \n
 * A Callback is made with the parameters as below and is notified via
 * \ref GA_PROFILE_CB registered during \ref GA_uc_server_init().
 *
 * The data is of type \ref GA_SEP_INFO. \n
 * The info inside \ref GA_SEP_INFO shall be \ref GA_QOS_CONF.
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \sa ga_bap_common_constants
 */
#define GA_SEP_SETUP_IND            0x12U

/**
 * \brief This event is notified once the Enable opcode
 * is received form the peer. In this event, the client provides the
 * Metadata parameters which is notified in this format
 * \ref GA_METADATA. \n
 * Internally this event is generated once the ASE CP for Enable is
 * received, The Application shall set the response along with the
 * reason for the respective ASE CP. Post this the ASE Sink or ASE Source
 * Notification is done by the Stack. \n
 * A Callback is made with the parameters as below and is notified via
 * \ref GA_PROFILE_CB registered during \ref GA_uc_server_init().
 *
 * The data is of type \ref GA_SEP_INFO. \n
 * The info inside \ref GA_SEP_INFO shall be \ref GA_METADATA.
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \sa ga_bap_common_constants
 */
#define GA_SEP_START_IND            0x13U

/**
 * \brief This event is notified once the Disable opcode
 * is received form the peer. \n
 * Internally this event is generated once the ASE CP for Disable is
 * received, The Application shall set the response along with the
 * reason for the respective ASE CP. Post this the ASE Sink or ASE Source
 * Notification is done by the Stack. \n
 * A Callback is made with the parameters as below and is notified via
 * \ref GA_PROFILE_CB registered during \ref GA_uc_server_init().
 *
 * The data is of type \ref GA_SEP_INFO. \n
 * The info inside \ref GA_SEP_INFO shall be NULL.
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_SEP_SUSPEND_IND          0x14U

/**
 * \brief This event is notified once the Update opcode
 * is received form the peer. In this event, the client provides the
 * Metadata parameters which is notified in this format
 * \ref GA_METADATA. \n
 * Internally this event is generated once the ASE CP for Update is
 * received, The Application shall set the response along with the
 * reason for the respective ASE CP. Post this the ASE Sink or ASE Source
 * Notification is done by the Stack. \n
 * A Callback is made with the parameters as below and is notified via
 * \ref GA_PROFILE_CB registered during \ref GA_uc_server_init().
 *
 * The data is of type \ref GA_SEP_INFO. \n
 * The info inside \ref GA_SEP_INFO shall be \ref GA_METADATA.
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \sa ga_bap_common_constants
 */
#define GA_SEP_UPDATE_IND           0x15U

/**
 * \brief This event is notified once the Release opcode
 * is received form the peer. \n
 * Internally this event is generated once the ASE CP for Release is
 * received, The Application shall set the response along with the
 * reason for the respective ASE CP. Post this the ASE Sink or ASE Source
 * Notification is done by the Stack. \n
 * A Callback is made with the parameters as below and is notified via
 * \ref GA_PROFILE_CB registered during \ref GA_uc_server_init().
 *
 * The data is of type \ref GA_SEP_INFO. \n
 * The info inside \ref GA_SEP_INFO shall be NULL.
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_SEP_RELEASE_IND          0x16U

/**
 * \brief This event is notified once the Receiver Start Ready opcode
 * is received form the peer Sink ASE. \n
 * Internally this event is generated once the ASE CP for Release is
 * received, The Application shall set the response along with the
 * reason for the respective ASE CP. Post this the ASE Sink or ASE Source
 * Notification is done by the Stack. \n
 * A Callback is made with the parameters as below and is notified via
 * \ref GA_PROFILE_CB registered during \ref GA_uc_server_init().
 *
 * The data is of type \ref GA_SEP_INFO. \n
 * The info inside \ref GA_SEP_INFO shall be NULL.
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_SEP_RX_START_READY_IND   0x17U

/**
 * \brief This event is notified once the Receiver Stop Ready opcode
 * is received form the peer Sink ASE. \n
 * Internally this event is generated once the ASE CP for Release is
 * received, The Application shall set the response along with the
 * reason for the respective ASE CP. Post this the ASE Sink or ASE Source
 * Notification is done by the Stack. \n
 * A Callback is made with the parameters as below and is notified via
 * \ref GA_PROFILE_CB registered during \ref GA_uc_server_init().
 *
 * The data is of type \ref GA_SEP_INFO. \n
 * The info inside \ref GA_SEP_INFO shall be NULL.
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_SEP_RX_STOP_READY_IND    0x18U

/** \} */
/** \} */

/**
 * \addtogroup ga_bap_uc_client_ascs_def
 * \{
 */

/**
 * \addtogroup ga_bap_uc_client_ascs_evt_defs
 * \{
 */

/**
 * \brief This event is notified when there is a Autonomous Config Codec
 * Operation initiated by the Server. \n
 * In this event, the server exposed preferred QoS parameters are notified in
 * this format \ref GA_ASE_INFO_IN_CODEC_CONF. Also, this event shall get
 * generated when Released Operation is performed by the Server, also when the
 * Server has Caching Support. \n
 * A Callback is made with the parameters as below and is notified via
 * \ref GA_PROFILE_CB registered during \ref GA_uc_client_init().
 *
 * The data is of type \ref GA_ASE_INFO. \n
 * The info inside \ref GA_ASE_INFO shall be \ref GA_ASE_INFO_IN_CODEC_CONF.
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \sa ga_bap_uc_client_server_ascs_constants
 * \sa ga_bap_uc_client_ascs_constants
 * \sa ga_bap_common_constants
 */
#define GA_SEP_CONFIGURE_NTF        0x19U

/**
 * \brief This event is notified when there is a Autonomous Disable Operation
 * initiated by the Server on a Sink ASE(Server Local Role). \n
 * In this event, the server provides the accepted QoS parameters which
 * is notified in this format \ref GA_ASE_INFO_IN_QOS_CONF for this active
 * ASE establishment. \n
 * A Callback is made with the parameters as below and is notified via
 * \ref GA_PROFILE_CB registered during \ref GA_uc_client_init().
 *
 * The data is of type \ref GA_ASE_INFO. \n
 * The info inside \ref GA_ASE_INFO shall be \ref GA_ASE_INFO_IN_QOS_CONF.
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \sa ga_bap_uc_client_server_ascs_constants
 * \sa ga_bap_common_constants
 */
#define GA_SEP_SETUP_NTF            0x20U

/**
 * \brief This event is notified when there is a Autonomous Disable Operation
 * initiated by the Server on a Source ASE(Server Local Role). \n
 * In this event, the server provides the the Metadata
 * parameters which is notified in this format
 * \ref GA_ASE_INFO_IN_ENABLING_STREAMING_DISABLING. \n
 * A Callback is made with the parameters as below and is notified via
 * \ref GA_PROFILE_CB registered during \ref GA_uc_client_init().
 *
 * The data is of type \ref GA_ASE_INFO. \n
 * The info inside \ref GA_ASE_INFO shall be
 * \ref GA_ASE_INFO_IN_ENABLING_STREAMING_DISABLING.
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \sa ga_bap_uc_client_server_ascs_constants
 * \sa ga_bap_common_constants
 */
#define GA_SEP_SUSPEND_NTF          0x21U

/**
 * \brief This event is notified when there is a Autonomous Update Metadata
 * Operation initiated by the Server. \n
 * In this event, the server provides the the Metadata
 * parameters which is notified in this format
 * \ref GA_ASE_INFO_IN_ENABLING_STREAMING_DISABLING. \n
 * A Callback is made with the parameters as below and is notified via
 * \ref GA_PROFILE_CB registered during \ref GA_uc_client_init().
 *
 * The data is of type \ref GA_ASE_INFO. \n
 * The info inside \ref GA_ASE_INFO shall be
 * \ref GA_ASE_INFO_IN_ENABLING_STREAMING_DISABLING.
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \sa ga_bap_uc_client_server_ascs_constants
 * \sa ga_bap_common_constants
 */
#define GA_SEP_UPDATE_NTF           0x22U

/**
 * \brief This event is notified when there is a Autonomous Release Operation
 * initiated by the Server. \n
 * A Callback is made with the parameters as below and is notified via
 * \ref GA_PROFILE_CB registered during \ref GA_uc_client_init().
 *
 * The data is of type \ref GA_ASE_INFO. \n
 * The info inside \ref GA_ASE_INFO shall be NULL.
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \sa ga_bap_uc_client_server_ascs_constants
 */
#define GA_SEP_RELEASE_NTF          0x23U

/**
 * \brief This event is notified when there is a Autonomous
 * Receiver Start Ready Operation initiated by the Server for a Sink ASE
 * (Server Local Role). \n
 * A Callback is made with the parameters as below and is notified via
 * \ref GA_PROFILE_CB registered during \ref GA_uc_client_init().
 *
 * The data is of type \ref GA_ASE_INFO. \n
 * The data inside \ref GA_ASE_INFO shall be NULL.
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \sa ga_bap_uc_client_server_ascs_constants
 * \sa ga_bap_common_constants
 */
#define GA_SEP_RX_START_READY_NTF   0x24U

/**
 * \brief This event is notified when there is a Released Operation initiated
 * by the Server. This is generated when the Server moves from Releasing,
 * also when the Server has No Caching Support. \n
 * A Callback is made with the parameters as below and is notified via
 * \ref GA_PROFILE_CB registered during \ref GA_uc_client_init().
 *
 * The data is of type \ref GA_ASE_INFO.
 * The info inside \ref GA_ASE_INFO shall be NULL.
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \sa ga_bap_uc_client_server_ascs_constants
 */
#define GA_SEP_IDLE_NTF             0x25U

/** \} */
/** \} */

/**
 * \addtogroup ga_bap_uc_client_pacs_def
 * \{
 */

/**
 * \addtogroup ga_bap_uc_client_pacs_evt_defs
 * \{
 */

/* TODO: Comment */
#define GA_CAPABILITIES_CHANGE_NTF  0x26U

/** \} */
/** \} */

/**
 * \defgroup ga_bap_uc_server_pacs_def UC Server - PACS
 * \{
 * \brief This section describes the various Defines in EtherMind
 * GA BAP Layer for Unicast Server - PACS.
 */

/**
 * \defgroup ga_bap_uc_server_pacs_evt_defs Events
 * \{
 * \brief This section describes the Generic Audio Events for
 * Unicast Server - PACS.
 */

/**
 * \brief This event is notified when the Client has triggered a write on the
 * Sink Audio Locations. \n
 * Internally this event is generated once the basic validation of the param is
 * complete and is accepted. \n
 * A Callback is made with the parameters as below and is notified via
 * \ref GA_PROFILE_CB registered during \ref GA_uc_server_init().
 *
 * The data is of type \ref UINT32.
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \sa ga_common_constants
 */
#define GA_SINK_SET_AUDIO_LOCATIONS_IND        0x27U

/**
 * \brief This event is notified when the Client has triggered a write on the
 * Source Audio Locations. \n
 * Internally this event is generated once the basic validation of the param is
 * complete and is accepted. \n
 * A Callback is made with the parameters as below and is notified via
 * \ref GA_PROFILE_CB registered during \ref GA_uc_server_init().
 *
 * The data is of type \ref UINT32.
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \sa ga_common_constants
 */
#define GA_SOURCE_SET_AUDIO_LOCATIONS_IND      0x28U

/** \} */
/** \} */

/**
 * \addtogroup ga_bap_uc_client_pacs_def
 * \{
 */

/**
 * \addtogroup ga_bap_uc_client_pacs_evt_defs
 * \{
 */

/**
 * \brief This event is notified when a write response is received for Sink
 * Audio Location characteristic from peer device with the following values as
 * parameters in the \ref GA_PROFILE_CB registered during
 * \ref GA_uc_client_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_SINK_SET_AUDIO_LOCATIONS_CNF
 * \param [in] ga_status \ref GA_SUCCESS : Write Response received \n
 * \param [in] ga_data NULL \n
 * \param [in] ga_datalen 0
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \sa ga_common_constants
 */
#define GA_SINK_SET_AUDIO_LOCATIONS_CNF        0x29U

/**
 * \brief This event is notified when a write response is received for Source
 * Audio Location characteristic from peer device with the following values as
 * parameters in the \ref GA_PROFILE_CB registered during
 * \ref GA_uc_client_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_SOURCE_SET_AUDIO_LOCATIONS_CNF
 * \param [in] ga_status \ref GA_SUCCESS : Write Response received \n
 * \param [in] ga_data NULL \n
 * \param [in] ga_datalen 0
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \sa ga_common_constants
 */
#define GA_SOURCE_SET_AUDIO_LOCATIONS_CNF      0x30U

/** \} */
/** \} */

/** \} */
/** \} */

/**
 * \addtogroup ga_bap_bc_module
 * \{
 */

/**
 * \addtogroup ga_bap_bc_defines
 * \{
 */

/**
 * \defgroup ga_bap_bc_source_def BC Source
 * \{
 * \brief This section describes the various Defines in EtherMind
 * GA BAP Layer for Broadcast Source.
 */

/**
 * \defgroup ga_bap_bc_source_evt_defs Events
 * \{
 * \brief This section describes the Generic Audio Events for
 * Broadcast Source.
 */

/**
 * \brief This event is notified when the EA for Broadcast Audio Announcement
 * and PA for Basic Audio Announcement is enabled successfully/failed. \n
 * A Callback is made with the parameters as below and is notified via
 * \ref GA_PROFILE_CB registered during \ref GA_bc_source_init().
 *
 * The data is NULL and length is 0U.
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_BC_SETUP_ANNOUNCEMENT_CNF        BAP_BC_SETUP_ANNOUNCEMENT_CNF

/**
 * \brief This event is notified when the EA for Broadcast Audio Announcement
 * and PA for Basic Audio Announcement is disabled successfully/failed. \n
 * A Callback is made with the parameters as below and is notified via
 * \ref GA_PROFILE_CB registered during \ref GA_bc_source_init().
 *
 * The data is NULL and length is 0U.
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_BC_END_ANNOUNCEMENT_CNF          BAP_BC_END_ANNOUNCEMENT_CNF

/**
 * \brief This event is notified when the Streaming has started
 * successfully/failed. \n
 * A Callback is made with the parameters as below and is notified via
 * \ref GA_PROFILE_CB registered during \ref GA_bc_source_init().
 *
 * The data is of type \ref BAP_BC_START_PARAMS.
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_BC_START_CNF                     BAP_BC_START_CNF

/**
 * \brief This event is notified when the Streaming has stopped
 * successfully/failed. \n
 * A Callback is made with the parameters as below and is notified via
 * \ref GA_PROFILE_CB registered during \ref GA_bc_source_init().
 *
 * The data is of type \ref BAP_BC_SUSPEND_PARAMS.
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_BC_SUSPEND_CNF                   BAP_BC_SUSPEND_CNF

/**
 * \brief This event is notified when the Streaming has stopped without the
 * user triggering a Suspend. This can be caused if the controller
 * terminates the BIG. \n
 * A Callback is made with the parameters as below and is notified via
 * \ref GA_PROFILE_CB registered during \ref GA_bc_source_init().
 *
 * The data is of type \ref BAP_BC_SUSPEND_PARAMS.
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_BC_SUSPEND_IND                   BAP_BC_SUSPEND_IND

/** \} */
/** \} */

/**
 * \defgroup ga_bap_bc_sink_def BC Sink
 * \{
 * \brief This section describes the various Defines in EtherMind
 * GA BAP Layer for Broadcast Sink.
 */

/**
 * \defgroup ga_bap_bc_sink_evt_defs Events
 * \{
 * \brief This section describes the Generic Audio Events for
 * Broadcast Sink.
 */

/**
 * \brief This event is notified when the device started succesfully/failed
 * the scan for Broadcast Audio Annoucements on EA from other devices. \n
 * A Callback is made with the parameters as below and is notified via
 * \ref GA_PROFILE_CB registered during \ref GA_bc_sink_init().
 *
 * The data is NULL and length is 0U.
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_BC_SCAN_ANNOUNCEMENT_CNF         BAP_BC_SCAN_ANNOUNCEMENT_CNF

/**
 * \brief This event is notified when the device stopped succesfully/failed
 * the scan for Broadcast Audio Annoucements on EA from other devices. \n
 * A Callback is made with the parameters as below and is notified via
 * \ref GA_PROFILE_CB registered during \ref GA_bc_sink_init().
 *
 * The data is NULL and length is 0U.
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_BC_SCAN_END_CNF                  BAP_BC_SCAN_END_CNF

/**
 * \brief This event is notified when the device creates/fail to create Sync
 * to the Broadcast Source identified during
 * Broadcast Audio Announcement Scan EA. \n
 * A Callback is made with the parameters as below and is notified via
 * \ref GA_PROFILE_CB registered during \ref GA_bc_sink_init().
 *
 * The data is of type \ref BAP_BC_ASSOCIATE_PARAMS.
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \sa GA_broadcast_decode_event_params() to fetch the event decoded params.
 */
#define GA_BC_ASSOCIATE_CNF                 BAP_BC_ASSOCIATE_CNF

/**
 * \brief This event is notified when the device stops/fails to stop Sync to
 * the Broadcast Source identified during Broadcast Audio Annoucement Scan EA. \n
 * A Callback is made with the parameters as below and is notified via
 * \ref GA_PROFILE_CB registered during \ref GA_bc_sink_init().
 *
 * The data is of type \ref BAP_BC_DISSOCIATE_PARAMS.
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \sa GA_broadcast_decode_event_params() to fetch the event decoded params.
 */
#define GA_BC_DISSOCIATE_CNF                BAP_BC_DISSOCIATE_CNF

/**
 * \brief This event is notified when the device lost Periodic Advertising Sync
 * to the Broadcast Source identified during
 * Broadcast Audio Annoucement Scan EA. \n
 * A Callback is made with the parameters as below and is notified via
 * \ref GA_PROFILE_CB registered during \ref GA_bc_sink_init().
 *
 * The data is of type \ref BAP_BC_DISSOCIATE_PARAMS.
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \sa GA_broadcast_decode_event_params() to fetch the event decoded params.
 */
#define GA_BC_DISSOCIATE_IND                BAP_BC_DISSOCIATE_IND

/**
 * \brief This event is notified when the device creates/fails to create the
 * Broadcast Sync to the Broadcast Source identified during
 * Broadcast Audio Annoucement Scan EA. \n
 * Once the Sync to Basic Audio Annoucement PA is complete, and when the
 * the BIG Create Sync is created/failed to create this event is generated. \n
 * A Callback is made with the parameters as below and is notified via
 * \ref GA_PROFILE_CB registered during \ref GA_bc_sink_init().
 *
 * The data is of type \ref BAP_BC_ENABLE_PARAMS.
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \sa GA_broadcast_decode_event_params() to fetch the event decoded params.
 */
#define GA_BC_ENABLE_CNF                    BAP_BC_ENABLE_CNF

/**
 * \brief This event is notified when the device terminate/fails to terminate
 * the Broadcast Sync to the Broadcast Source identified during Broadcast Audio
 * Annoucement Scan EA. \n
 * Once the Sync to Basic Audio Annoucement PA is complete, and when the
 * BIG Create Sync is created and when a successful/failed terminate of the
 * Broadcast Sync happens, this event is generated. \n
 * A Callback is made with the parameters as below and is notified via
 * \ref GA_PROFILE_CB registered during \ref GA_bc_sink_init().
 *
 * The data is of type \ref BAP_BC_DISABLE_PARAMS.
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \sa GA_broadcast_decode_event_params() to fetch the event decoded params.
 */
#define GA_BC_DISABLE_CNF                   BAP_BC_DISABLE_CNF

/**
 * \brief This event is notified when the device lost the Broadcast Sync to the
 * Broadcast Source identified during Broadcast Audio Annoucement Scan EA. \n
 * Once the Sync to Basic Audio Annoucement PA is complete, and when the
 * BIG Create Sync is created and when a Loss to Broadcast Sync happens,
 * this event is generated. \n
 * A Callback is made with the parameters as below and is notified via
 * \ref GA_PROFILE_CB registered during \ref GA_bc_sink_init().
 *
 * The data is of type \ref BAP_BC_DISABLE_PARAMS.
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \sa GA_broadcast_decode_event_params() to fetch the event decoded params.
 */
#define GA_BC_DISABLE_IND                   BAP_BC_DISABLE_IND

/**
 * \brief This event is notified when the device is receiving Broadcast Audio
 * Announcement EA from remote devices. \n
 * A Callback is made with the parameters as below and is notified via
 * \ref GA_PROFILE_CB registered during \ref GA_bc_sink_init().
 *
 * The data is of type \ref BAP_BC_SOURCE_ANNOUNCEMENT_PARAMS.
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \sa GA_broadcast_decode_event_params() to fetch the event decoded params.
 */
#define GA_BC_SOURCE_ANNOUNCEMENT_IND       BAP_BC_SOURCE_ANNOUNCEMENT_IND

/**
 * \brief This event is notified when the device is receiving Basic Audio
 * Announcement PA from remote device. \n
 * A Callback is made with the parameters as below and is notified via
 * \ref GA_PROFILE_CB registered during \ref GA_bc_sink_init().
 *
 * The data is of type \ref BAP_BC_SOURCE_CONFIG_PARAMS.
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \sa GA_broadcast_decode_event_params() to fetch the event decoded params.
 */
#define GA_BC_SOURCE_CONFIG_IND             BAP_BC_SOURCE_CONFIG_IND

/**
 * \brief This event is notified when the device is receiving BigInfo Event
 * that gets generated post creating successful Broadcast Sync. \n
 * A Callback is made with the parameters as below and is notified via
 * \ref GA_PROFILE_CB registered during \ref GA_bc_sink_init().
 *
 * The data is of type \ref BAP_BC_SOURCE_STREAM_PARAMS.
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \sa GA_broadcast_decode_event_params() to fetch the event decoded params.
 */
#define GA_BC_SOURCE_STREAM_IND             BAP_BC_SOURCE_STREAM_IND

/** \} */
/** \} */

/** \} */
/** \} */

/** \} */

/**
 * \addtogroup ga_cas_module
 * \{
 */

/**
 * \addtogroup ga_cas_defines
 * \{
 */

/**
 * \defgroup ga_cas_api_evt_defs Events
 * \{
 * \brief This section describes the Common Audio Service Events.
 */

/**
 * \defgroup ga_cas_client_evt_defs Client
 * \{
 * \brief This section describes the Common Audio Service Events for Client.
 */

/**
 * \name CAS Client Events - Setup
 * \{
 * \brief This section describes the Common Audio Service Setup
 * Events for Client.
 */

/**
 * \brief This event is notified as result of a CAP discovery procedure
 * that is initiated by the application to discover CAS and its included
 * services if any. The event passes the parameters as below to
 * the application callback as in \ref GA_PROFILE_CB registered with
 * \ref GA_register_callback().
 *
 * \param [in] ga_ep Endpoint Address
 * \param [in] ga_event \ref GA_CAP_DISCOVER_CNF
 * \param [in] ga_status If ga_status is \ref GA_CONTINUE : CAS is found\n
 *                          - If CAS included CSIS is found: \ref GA_CONTINUE. \n
 *                             - Operation complete: \ref GA_SUCCESS. \n
 *                             .
 *                          - Else,
 *                             - If CAS included CSIS is not found:
 *                               \ref GA_FAILURE. \n
 *                             .
 *                          .
 *                       If ga_status is \ref GA_FAILURE : CAS service is not
 *                       found.\n
 * \param [in] ga_data If status is \ref GA_CONTINUE \n
 *                        - ga_data: \ref GA_BRR_SVC_INFO.
 *                        .
 *                      Else \n
 *                        - ga_data: NULL.
 *                        .
 * \param [in] ga_datalen If status is \ref GA_CONTINUE \n
 *                           - ga_datalen: \ref sizeof ( \ref GA_BRR_SVC_INFO)
 *                           .
 *                        Else \n
 *                           - ga_datalen: 0
 *                           .
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_CAP_DISCOVER_CNF         0x30U

/**
 * \brief This event is notified when the application does a CAP Setup member
 * operation to configure the notification of the CSIS member instance on the
 * peer. CSIS characteristics are read. The event passes the parameters as
 * below to the application callback as in \ref GA_PROFILE_CB registered with
 * \ref GA_register_callback().
 *
 * \param [in] ga_ep Endpoint Address
 * \param [in] ga_event \ref GA_CAP_SETUP_MEMBER_CNF
 * \param [in] ga_status \ref GA_SUCCESS or any Error Code
 * \param [in] ga_data If status is \ref GA_SUCCESS \n
 *                        - ga_data: Pointer to object of type \ref GA_SET_MEMBER.
 *                                   Value of SIRK is valid, however values of
 *                                   other chars is valid only if corresponding
 *                                   read is successful. \n
 *                        .
 *                     Else \n
 *                        - ga_data: NULL. \n
 *                        .
 * \param [in] ga_datalen If status is \ref GA_SUCCESS \n
 *                           - ga_datalen: \ref sizeof ( \ref GA_SET_MEMBER) \n
 *                           .
 *                        Else \n
 *                           - ga_datalen: 0 \n
 *                           .
 * \return \ref GA_SUCCESS (always)
 */
#define GA_CAP_SETUP_MEMBER_CNF     0x31U

/** \} */

/**
 * \name CAS Client Events - Release
 * \{
 * \brief This section describes the Common Audio Service Release
 * Events for Client.
 */

/**
 * \brief This event is notified when the application does a CAP Release member
 * operation to release the CSIS member instance of the
 * peer CAS service. The event passes the parameters as below to
 * the application callback as in \ref GA_PROFILE_CB registered with
 * \ref GA_register_callback().
 *
 * \param [in] ga_ep Endpoint Address
 * \param [in] ga_event \ref GA_CAP_RELEASE_MEMBER_CNF
 * \param [in] ga_status \ref GA_SUCCESS or any Error Code
 * \param [in] ga_data If status is \ref GA_SUCCESS or \ref GA_FAILURE \n
 *                        - ga_data: Pointer to object of type \ref CSIP_EVENT_INFO \n
 *                           - context: To be ignored by the application \n
 *                           - data: NULL \n
 *                           - datalen: 0 \n
 *                           - handle: GA context for the peer endpoint. \n
 *                           .
 *                        .
 * \param [in] ga_datalen If status is \ref GA_SUCCESS or \ref GA_FAILURE \n
 *                           - ga_datalen: \ref sizeof ( \ref CSIP_EVENT_INFO) \n
 *                           .
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_CAP_RELEASE_MEMBER_CNF   0x32U

/** \} */

/**
 * \name CAS Client Events - Write
 * \{
 * \brief This section describes the Common Audio Service Write
 * Events for Client.
 */

/**
 * \brief This event is notified when the application does a CAP lock member
 * operation to lock the CSIS member instance on the peer. The event passes the
 * parameters as below to the application callback as in \ref GA_PROFILE_CB
 * registered with \ref GA_register_callback().
 *
 * \param [in] ga_ep Endpoint Address
 * \param [in] ga_event \ref GA_CAP_LOCK_MEMBER_CNF
 * \param [in] ga_status \ref GA_SUCCESS or any Error Code
 * \param [in] ga_data If status is \ref GA_SUCCESS or \ref GA_FAILURE \n
 *                        - ga_data: Pointer to object of type \ref CSIP_EVENT_INFO \n
 *                           - context: To be ignored by the application \n
 *                           - data: NULL \n
 *                           - datalen: 0 \n
 *                           - handle: GA context for the peer endpoint. \n
 *                           .
 *                        .
 * \param [in] ga_datalen If status is \ref GA_SUCCESS or \ref GA_FAILURE \n
 *                           - ga_datalen: \ref sizeof ( \ref CSIP_EVENT_INFO) \n
 *                           .
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_CAP_LOCK_MEMBER_CNF      0x33U

/**
 * \brief This event is notified on completion of a Lock request procedure
 * initiated by the application for all the Set Members. The event passes the
 * parameters as below to the application callback as in \ref GA_PROFILE_CB
 * registered with \ref GA_register_callback().
 *
 * \param [in] ga_ep Endpoint Address
 * \param [in] ga_event \ref GA_CAP_SET_LOCKREQUEST_CNF
 * \param [in] ga_status \ref GA_SUCCESS or Error Code
 * \param [in] ga_data NULL
 * \param [in] ga_datalen 0
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_CAP_SET_LOCKREQUEST_CNF  0x35U

/**
 * \brief This event is notified on completion of a Lock release procedure
 * initiated by the application. The event passes the parameters as below to
 * the application callback as in \ref GA_PROFILE_CB registered with
 * \ref GA_register_callback().
 *
 * \param [in] ga_ep Endpoint Address
 * \param [in] ga_event \ref GA_CAP_SET_LOCKRELEASE_CNF
 * \param [in] ga_status \ref GA_SUCCESS or Error Code
 * \param [in] ga_data NULL
 * \param [in] ga_datalen 0
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_CAP_SET_LOCKRELEASE_CNF  0x36U

/** \} */
/** \} */

/**
 * \defgroup ga_cas_server_evt_defs Server
 * \{
 * \brief This section describes the Common Audio Service Events for Server.
 */

/**
 * \name CAS Server Events - Write
 * \{
 * \brief This section describes the Common Audio Service Write
 * Events for Server.
 */

/**
 * \brief This event is notified when a peer Set Coordinator Sets the Lock
 * on the local CAS CSIS member. \n
 * The event passes the parameters as below to
 * the application callback as in \ref GA_PROFILE_CB registered with
 * \ref GA_register_callback().
 *
 * \param [in] ga_ep Endpoint Address
 * \param [in] ga_event \ref GA_CAP_LOCK_MEMBER_IND
 * \param [in] ga_status \ref GA_SUCCESS
 * \param [in] ga_data If status is \ref GA_SUCCESS \n
 *                        - ga_data: Pointer to object of type \ref CSIP_EVENT_INFO \n
 *                           - context: To be ignored by the application \n
 *                           - data: Pointer to object of type \ref UINT8 depicting
 *                                    value of Lock \n
 *                                    \ref ga_csip_set_member_lock \n
 *                           - datalen: \ref sizeof ( \ref UINT8 ) \n
 *                           - handle: CSIS Member Handle for CAP.\n
 *                           .
 *                        .
 *                     Else \n
 *                        - ga_data: NULL \n
 *                        .
 * \param [in] ga_datalen If status is \ref GA_SUCCESS \n
 *                           - ga_datalen: \ref sizeof ( \ref CSIP_EVENT_INFO) \n
 *                           .
 *                        Else \n
 *                           - ga_datalen: 0 \n
 *                           .
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \note This is only informational to the application. The application
 * need not send any response.
 */
#define GA_CAP_LOCK_MEMBER_IND      0x34U

/** \} */
/** \} */
/** \} */
/** \} */
/** \} */

/**
 * \addtogroup ga_vcp_module
 * \{
 */

/**
 * \defgroup ga_vcp_defines Defines
 * \{
 * \brief This section describes the various Defines in EtherMind
 * GA VCP Layer.
 */

/**
 * \defgroup ga_vcp_error_code Error Codes
 * \{
 * \brief This section lists the Error Codes that are provided as part of
 * return of functionalities of VCP \ref ga_vcp_api_defs.
 */

/** \} */

/**
 * \defgroup ga_vcp_constants Constants
 * \{
 * \brief This section describes the various Constants in EtherMind
 * GA VCP Layer.
 */

/** \} */

/**
 * \defgroup ga_vcp_api_evt_defs Events
 * \{
 * \brief This section describes the Volume Control Events.
 */

/**
 * \defgroup ga_vcp_volcntrl_evt_defs Volume Controller
 * \{
 * \brief This section describes the Volume Control Profile
 * Events for Volume Controller.
 */

/**
 * \name VCP Controller Events - Setup
 * \{
 * \brief This section describes the Volume Control Profile Setup
 * Events for Volume Controller.
 */

/**
 * \brief This event indicates the setup of a VCS Session.
 * Callback is triggered once discovery of service, char and descriptors,
 * configuration for Notifications is complete. \n
 * A Callback is made with the parameters as below and is notified via
 * \ref GA_PROFILE_CB registered during \ref GA_vc_client_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_VC_SETUP_CNF
 * \param [in] ga_status \ref GA_SUCCESS : Setup Complete \n
 *                       \ref GA_FAILURE : Others \n
 * \param [in] ga_data If status is \ref GA_SUCCESS or
 *                     \ref GA_FAILURE, \n
 *                        - ga_data: NULL \n
 *                        .
 * \param [in] ga_datalen If status is \ref GA_SUCCESS or
 *                        \ref GA_FAILURE, \n
 *                           - ga_datalen: 0 \n
 *                           .
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_VC_SETUP_CNF                                 0xA9U

/**
 * \brief This event is notified on discovery of secondary/included services
 * VOCS and AICS with peer device with the following values as parameters in
 * the \ref GA_PROFILE_CB registered during \ref GA_vc_client_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_VC_GET_CAPABILITIES_CNF
 * \param [in] ga_status \ref GA_CONTINUE : Service Handle range of discovered
 *                       VOCS(if any) and again for AICS(if any) \n
 *                       \ref GA_SUCCESS : Service Discovery Complete \n
 *                       \ref GA_FAILURE : Others \n
 * \param [in] ga_data If status is \ref GA_CONTINUE \n
 *                        - ga_data: Pointer to object of type
 *                          \ref GA_BRR_SVC_INFO \n
 *                        .
 * \param [in] ga_datalen If status is \ref GA_CONTINUE \n
 *                           - ga_datalen: \ref sizeof ( \ref GA_BRR_SVC_INFO ) \n
 *                           .
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_VC_GET_CAPABILITIES_CNF                      0xAAU

/**
 * \brief This event indicates the setup of an VOCS/AICS Session as requested
 * during call to \ref GA_vc_set_capability(). \n
 * The Char and Desc Discovery is performed post which the Configuration of
 * Notification of Char is done. \n
 * A Callback is made with the parameters as below and is notified via
 * \ref GA_PROFILE_CB registered during \ref GA_vc_client_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_VC_SET_CAPABILITY_CNF
 * \param [in] ga_status \ref GA_SUCCESS : Setup Complete \n
 *                       \ref GA_FAILURE : Others \n
 * \param [in] ga_data If status is \ref GA_SUCCESS or \ref GA_FAILURE, \n
 *                        - ga_data: NULL \n
 *                        .
 * \param [in] ga_datalen If status is \ref GA_SUCCESS or \ref GA_FAILURE, \n
 *                           - ga_datalen: 0 \n
 *                           .
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_VC_SET_CAPABILITY_CNF                        0xABU

/** \} */

/**
 * \name VCP Controller Events - Release
 * \{
 * \brief This section describes the Volume Control Profile Release
 * Events for Volume Controller.
 */

/**
 * \brief This event is notified when a VCS Service context is released.
 * Configuration of Notifications for char are disabled and followed by release
 * of VCS context. \n
 * A Callback is made with the parameters as below and is notified via
 * \ref GA_PROFILE_CB registered during \ref GA_vc_client_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_VC_RELEASE_CNF
 * \param [in] ga_status \ref GA_SUCCESS : Release Complete \n
 *                       \ref GA_FAILURE : Others \n
 * \param [in] ga_data If status is \ref GA_SUCCESS or \ref GA_FAILURE, \n
 *                        - ga_data: NULL \n
 *                        .
 * \param [in] ga_datalen If status is \ref GA_SUCCESS or \ref GA_FAILURE, \n
 *                           - ga_datalen: 0 \n
 *                           .
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_VC_RELEASE_CNF                               0xAC

/**
 * \brief This event is notified after VOCS/AICS Service context is released as
 * requested by \ref GA_vc_release_capability(). \n
 * Configuration of Notifications for char are disabled followed by release
 * of VOCS/AICS context. \n
 * A Callback is made with the parameters as below and is notified via
 * \ref GA_PROFILE_CB registered during \ref GA_vc_client_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_VC_RELEASE_CAPABILITY_CNF
 * \param [in] ga_status \ref GA_SUCCESS : Release Complete \n
 *                       \ref GA_FAILURE : Others \n
 * \param [in] ga_data If status is \ref GA_SUCCESS or \ref GA_FAILURE, \n
 *                        - ga_data: NULL \n
 *                        .
 * \param [in] ga_datalen If status is \ref GA_SUCCESS or \ref GA_FAILURE, \n
 *                           - ga_datalen: 0 \n
 *                           .
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_VC_RELEASE_CAPABILITY_CNF                    0xAD

/** \} */

/**
 * \name VCP Controller Events - Read
 * \{
 * \brief This section describes the Volume Control Profile Read
 * Events for Volume Controller.
 */

/**
 * \brief This event is notified when a read response is received for Volume
 * State characteristic from peer device with the following values as
 * parameters in the \ref GA_PROFILE_CB registered during
 * \ref GA_vc_client_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_VC_GET_VOLUME_STATE_CNF
 * \param [in] ga_status \ref GA_SUCCESS : Read Response received \n
 * \param [in] ga_data Pointer to \ref UCHAR with params as below: \n
 *                     Includes Param \n
 *                        - Volume_Setting ( \ref UINT8 )
 *                          \ref ga_vcp_vcs_vs_vol_setting \n
 *                        - Mute ( \ref UINT8 )
 *                          \ref ga_vcp_vcs_vs_mute \n
 *                        - Change_Counter ( \ref UINT8 )
 *                          \ref ga_vcp_vcs_vs_chng_cntr \n
 *                        .
 * \param [in] ga_datalen 3
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \sa ga_vcp_vcs_vs_char_val
 */
#define GA_VC_GET_VOLUME_STATE_CNF                      VCS_EVENT_GET_VOLUME_STATE_CNF

/**
 * \brief This event is notified when a read response is received for
 * Volume Flags characteristic from peer device with the following values as
 * parameters in the \ref GA_PROFILE_CB registered during
 * \ref GA_vc_client_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_VC_GET_VOLUME_FLAGS_CNF
 * \param [in] ga_status \ref GA_SUCCESS : Read Response received \n
 * \param [in] ga_data Pointer to \ref UCHAR with params as below: \n
 *                     Includes Param \n
 *                        - Volume_Setting_Persisted ( \ref UINT8 )
 *                          \ref ga_vcp_vcs_vol_setting_persisted \n
 *                        .
 * \param [in] ga_datalen 1
 *
 * \return \ref GA_SUCCESS (always)
 * \sa ga_vcp_vcs_vol_setting_persisted
 */
#define GA_VC_GET_VOLUME_FLAGS_CNF                      VCS_EVENT_GET_VOLUME_FLAGS_CNF

/**
 * This event is notified when a read response is received for Volume Offset
 * State characteristic from peer device with the following values as
 * parameters in the \ref GA_PROFILE_CB registered during
 * \ref GA_vc_client_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_VC_VOCS_GET_OFFSET_STATE_CNF
 * \param [in] ga_status \ref GA_SUCCESS : Read Response received \n
 * \param [in] ga_data Pointer to \ref UCHAR with params as below: \n
 *                     Includes Param \n
 *                        - Volume_Offset ( \ref INT16 ) \n
 *                        - Change_Counter ( \ref UINT8 ) \n
 *                        .
 * \param [in] ga_datalen 3
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \sa ga_vcp_vocs_cp_vo
 * \sa ga_vcp_vocs_cp_cc
 */
#define GA_VC_VOCS_GET_OFFSET_STATE_CNF                 VOCS_EVENT_GET_OFFSET_STATE_CNF

/**
 * \brief This event is notified when a read response is received for Audio
 * Location characteristic from peer device with the following values as
 * parameters in the \ref GA_PROFILE_CB registered during
 * \ref GA_vc_client_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_VC_VOCS_GET_AUDIO_LOCATION_CNF
 * \param [in] ga_status \ref GA_SUCCESS : Read Response received \n
 * \param [in] ga_data Pointer to \ref UCHAR with params as below: \n
 *                     Includes Param \n
 *                        - Audio Location ( \ref UINT32 ) \n
 *                        .
 * \param [in] ga_datalen 4
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \sa ga_common_constants
 */
#define GA_VC_VOCS_GET_AUDIO_LOCATION_CNF               VOCS_EVENT_GET_AUDIO_LOCATION_CNF

/**
 * \brief This event is notified when a read response is received for Audio
 * Output Description characteristic from peer device with the following values
 * as parameters in the \ref GA_PROFILE_CB registered during
 * \ref GA_vc_client_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_VC_VOCS_GET_AUDIO_OUT_DESC_CNF
 * \param [in] ga_status \ref GA_SUCCESS : Read Response received \n
 * \param [in] ga_data Pointer to UCHAR, Can be a UTF-8 String of 0 or more
 *                     characters \n
 * \param [in] ga_datalen 0 or Length of UTF-8 String.
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_VC_VOCS_GET_AUDIO_OUT_DESC_CNF               VOCS_EVENT_GET_AUDIO_OUT_DESC_CNF

/**
 * \brief This event is notified when a read response is received for Audio
 * Input State characteristic from peer device with the following values as
 * parameters in the \ref GA_PROFILE_CB registered during
 * \ref GA_vc_client_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_VC_AICS_GET_INPUT_STATE_CNF
 * \param [in] ga_status \ref GA_SUCCESS : Read Response received \n
 * \param [in] ga_data Pointer to \ref UCHAR with params as below: \n
 *                     Includes Param \n
 *                        - Gain_Setting ( \ref INT8 ) \n
 *                        - Mute ( \ref UINT8 )
 *                          \ref ga_vcp_aics_mute_field_values \n
 *                        - Gain_Mode ( \ref UINT8 )
 *                          \ref ga_vcp_aics_gain_mode_field_values \n
 *                        - Change_Counter ( \ref UINT8 ) \n
 *                        .
 * \param [in] ga_datalen 4
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \sa ga_vcp_aics_mute_field_values
 * \sa ga_vcp_aics_gain_mode_field_values
 */
#define GA_VC_AICS_GET_INPUT_STATE_CNF                  AICS_EVENT_GET_INPUT_STATE_CNF

/**
 * \brief This event is notified when a read response is received for Gain
 * Setting Properties characteristic from peer device with the following values
 * as parameters in the \ref GA_PROFILE_CB registered during
 * \ref GA_vc_client_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_VC_AICS_GET_GAIN_SETTING_PROPRTY_CNF
 * \param [in] ga_status \ref GA_SUCCESS : Read Response received \n
 * \param [in] ga_data Pointer to \ref UCHAR with params as below: \n
 *                     Includes Param \n
 *                        - Gain_Setting_Units ( \ref UINT8 ) \n
 *                        - Gain_Setting_Minimum ( \ref INT8 ) \n
 *                        - Gain_Setting_Maximum ( \ref INT8 ) \n
 *                        .
 * \param [in] ga_datalen 3
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \sa ga_vcp_aics_gain_setting
 */
#define GA_VC_AICS_GET_GAIN_SETTING_PROPRTY_CNF         AICS_EVENT_GET_GAIN_SETTING_PROPRTY_CNF

/**
 * \brief This event is notified when a read response is received for Audio
 * Input Type characteristic from peer device with the following values as
 * parameters in the \ref GA_PROFILE_CB registered during
 * \ref GA_vc_client_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_VC_AICS_GET_INPUT_TYPE_CNF
 * \param [in] ga_status \ref GA_SUCCESS : Read Response received \n
 * \param [in] ga_data Pointer to \ref UCHAR. Refer \ref ga_common_constants
 * \param [in] ga_datalen 1
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \sa ga_common_constants
 */
#define GA_VC_AICS_GET_INPUT_TYPE_CNF                   AICS_EVENT_GET_INPUT_TYPE_CNF

/**
 * \brief This event is notified when a read response is received for Audio
 * Input Status characteristic from peer device with the following values as
 * parameters in the \ref GA_PROFILE_CB registered during
 * \ref GA_vc_client_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_VC_AICS_GET_INPUT_STATUS_CNF
 * \param [in] ga_status \ref GA_SUCCESS : Read Response received \n
 * \param [in] ga_data Pointer of type \ref UCHAR.
 *                     Refer \ref ga_vcp_aics_input_status
 * \param [in] ga_datalen 1
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \sa ga_vcp_aics_input_status
 */
#define GA_VC_AICS_GET_INPUT_STATUS_CNF                 AICS_EVENT_GET_INPUT_STATUS_CNF

/**
 * \brief This event is notified when a read response is received for Audio
 * Input Description characteristic from peer device with the following values
 * as parameters in the \ref GA_PROFILE_CB registered during
 * \ref GA_vc_client_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_VC_AICS_GET_AUDIO_INPUT_DESC_CNF
 * \param [in] ga_status \ref GA_SUCCESS : Read Response received \n
 * \param [in] ga_data Pointer to UCHAR, Can be a UTF-8 String of 0 or more
 *                     characters \n
 * \param [in] ga_datalen 0 or Length of UTF-8 String.
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_VC_AICS_GET_AUDIO_INPUT_DESC_CNF             AICS_EVENT_GET_AUDIO_INPUT_DESC_CNF

/** \} */

/**
 * \name VCP Controller Events - Write
 * \{
 * \brief This section describes the Volume Control Profile Write
 * Events for Volume Controller.
 */

/**
 * \brief This event is notified when a write response is received for Volume
 * Control Point characteristic from peer device with the following values as
 * parameters in the \ref GA_PROFILE_CB registered during
 * \ref GA_vc_client_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_VC_CP_WT_CNF
 * \param [in] ga_status \ref GA_SUCCESS : Write Response received \n
 * \param [in] ga_data NULL \n
 * \param [in] ga_datalen 0
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_VC_CP_WT_CNF                                 VCS_EVENT_CP_WT_CNF

/**
 * \brief This event is notified when a write response is received for Volume
 * Offset Control Point characteristic from peer device with the following
 * values as parameters in the \ref GA_PROFILE_CB registered during
 * \ref GA_vc_client_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_VC_VOCS_CP_WT_CNF
 * \param [in] ga_status \ref GA_SUCCESS : Write Response received \n
 * \param [in] ga_data NULL \n
 * \param [in] ga_datalen 0
 *
 * \return\ref GA_SUCCESS (always)
 *
 * \sa ga_vcp_vocs_cp_opc
 */
#define GA_VC_VOCS_CP_WT_CNF                            VOCS_EVENT_CP_WT_CNF

/**
 * \brief This event is notified when a write response is received for Audio
 * Input Control Point characteristic from peer device with the following
 * values as parameters in the \ref GA_PROFILE_CB registered during
 * \ref GA_vc_client_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_VC_AICS_CP_WT_CNF
 * \param [in] ga_status \ref GA_SUCCESS : Write Response received \n
 * \param [in] ga_data NULL \n
 * \param [in] ga_datalen 0
 *
 * \return\ref GA_SUCCESS (always)
 *
 * \sa ga_vcp_aics_cp_req_opc
 */
#define GA_VC_AICS_CP_WT_CNF                            AICS_EVENT_CP_WT_CNF

/** \} */

/**
 * \name VCP Controller Events - Notification
 * \{
 * \brief This section describes the Volume Control Profile
 * Notification Events for Volume Controller.
 */

/**
 * \brief This event is notified when a notification is received for Volume
 * State characteristic from peer device with the following values as
 * parameters in the \ref GA_PROFILE_CB registered during
 * \ref GA_vc_client_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_VC_VOLUME_STATE_NTF
 * \param [in] ga_status \ref GA_SUCCESS Notification received
 * \param [in] ga_data Pointer to \ref UCHAR with params as below: \n
 *                     Includes Param \n
 *                        - Volume_Setting ( \ref UINT8 )
 *                          \ref ga_vcp_vcs_vs_vol_setting \n
 *                        - Mute ( \ref UINT8 )
 *                          \ref ga_vcp_vcs_vs_mute \n
 *                        - Change_Counter ( \ref UINT8 )
 *                          \ref ga_vcp_vcs_vs_chng_cntr \n
 *                        .
 * \param [in] ga_datalen 3
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \sa ga_vcp_vcs_vs_char_val
 */
#define GA_VC_VOLUME_STATE_NTF                          VCS_EVENT_VOLUME_STATE_NTF

/**
 * \brief This event is notified when a notification is received for Volume
 * Flags characteristic from peer device with the following values as
 * parameters in the \ref GA_PROFILE_CB registered during
 * \ref GA_vc_client_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_VC_VOLUME_FLAGS_NTF
 * \param [in] ga_status \ref GA_SUCCESS Notification received
 * \param [in] ga_data Pointer to \ref UCHAR with params as below: \n
 *                     Includes Param \n
 *                        - Volume_Setting_Persisted ( \ref UINT8 )
 *                          \ref ga_vcp_vcs_vol_setting_persisted \n
 *                        .
 * \param [in] ga_datalen 1
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \sa ga_vcp_vcs_vol_setting_persisted
 */
#define GA_VC_VOLUME_FLAGS_NTF                          VCS_EVENT_VOLUME_FLAGS_NTF

/**
 * \brief This event is notified when a notification is received for Offset State
 * characteristic from peer device with the following values as
 * parameters in the \ref GA_PROFILE_CB registered during
 * \ref GA_vc_client_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_VC_VOCS_OFFSET_STATE_NTF
 * \param [in] ga_status \ref GA_SUCCESS Notification received
 * \param [in] ga_data Pointer to \ref UCHAR with params as below: \n
 *                     Includes Param \n
 *                        - Volume_Offset ( \ref INT16 ) \n
 *                        - Change_Counter ( \ref UINT8 ) \n
 *                        .
 * \param [in] ga_datalen 3
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_VC_VOCS_OFFSET_STATE_NTF                     VOCS_EVENT_OFFSET_STATE_NTF

/**
 * \brief This event is notified when a notification is received for Audio
 * Location characteristic from peer device with the following values as
 * parameters in the \ref GA_PROFILE_CB registered during
 * \ref GA_vc_client_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_VC_VOCS_AUDIO_LOCATION_NTF
 * \param [in] ga_status \ref GA_SUCCESS Notification received
 * \param [in] ga_data Pointer to \ref UCHAR with params as below: \n
 *                     Includes Param \n
 *                         - Audio Location ( \ref UINT32 ) \n
 *                         .
 * \param [in] ga_datalen 4
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \sa ga_common_constants
 */
#define GA_VC_VOCS_AUDIO_LOCATION_NTF                   VOCS_EVENT_AUDIO_LOCATION_NTF

/**
 * \brief This event is notified when a notification is received for Audio
 * Output Description characteristic from peer device with the following values as
 * parameters in the \ref GA_PROFILE_CB registered during
 * \ref GA_vc_client_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_VC_VOCS_AUDIO_OUT_DESC_NTF
 * \param [in] ga_status \ref GA_SUCCESS Notification received
 * \param [in] ga_data Pointer to \ref UCHAR, Can be a UTF-8 String of 0 or
 *                     more characters \n
 * \param [in] ga_datalen 0 or Length of UTF-8 String.
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_VC_VOCS_AUDIO_OUT_DESC_NTF                   VOCS_EVENT_AUDIO_OUT_DESC_NTF

/**
 * \brief This event is notified when a notification is received for Audio
 * Input State characteristic from peer device with the following values as
 * parameters in the \ref GA_PROFILE_CB registered during
 * \ref GA_vc_client_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_VC_AICS_INPUT_STATE_NTF
 * \param [in] ga_status \ref GA_SUCCESS Notification received
 * \param [in] ga_data Pointer to \ref UCHAR with params as below: \n
 *                     Includes Param \n
 *                        - Gain_Setting ( \ref INT8 ) \n
 *                        - Mute ( \ref UINT8 )
 *                          \ref ga_vcp_aics_mute_field_values \n
 *                        - Gain_Mode ( \ref UINT8 )
 *                          \ref ga_vcp_aics_gain_mode_field_values \n
 *                        - Change_Counter ( \ref UINT8 ) \n
 *                        .
 * \param [in] ga_datalen 4
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_VC_AICS_INPUT_STATE_NTF                      AICS_EVENT_CP_INPUT_STATE_NTF

/**
 * \brief This event is notified when a notification is received for Audio
 * Input Status characteristic from peer device with the following values as
 * parameters in the \ref GA_PROFILE_CB registered during
 * \ref GA_vc_client_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_VC_AICS_INPUT_STATUS_NTF
 * \param [in] ga_status \ref GA_SUCCESS Notification received
 * \param [in] ga_data Pointer of type \ref UCHAR.
 *                     Refer \ref ga_vcp_aics_input_status
 * \param [in] ga_datalen 1
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_VC_AICS_INPUT_STATUS_NTF                     AICS_EVENT_CP_INPUT_STATUS_NTF

/**
 * \brief This event is notified when a notification is received for Audio
 * Input Description characteristic from peer device with the following values
 * as parameters in the \ref GA_PROFILE_CB registered during
 * \ref GA_vc_client_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_VC_AICS_AUDIO_INPUT_DESC_NTF
 * \param [in] ga_status \ref GA_SUCCESS Notification received
 * \param [in] ga_data Pointer to \ref UCHAR, Can be a UTF-8 String of 0 or
 *                     more characters \n
 * \param [in] ga_datalen 0 or Length of UTF-8 String.
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_VC_AICS_AUDIO_INPUT_DESC_NTF                 AICS_EVENT_AUDIO_INPUT_DESC_NTF

/** \} */

/** \} */

/**
 * \defgroup ga_vcp_vol_renderer_evt_defs Volume Renderer
 * \{
 * \brief This section describes the Volume Control Profile Events
 * for Volume Renderer.
 */

/**
 * \name VCP Renderer Events - Read
 * \{
 * \brief This section describes the Volume Control Profile Read
 * Events for Volume Renderer.
 */

/**
 * \brief This event is notified when a read request is received for
 * characteristic from peer device with the following values as
 * parameters in the \ref GA_PROFILE_CB registered during
 * \ref GA_vc_server_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_VC_RD_IND
 * \param [in] ga_status \ref GA_SUCCESS : Read Request received \n
 * \param [in] ga_data Pointer to Object of type \ref VCP_EVENT_INFO \n
 *                        - context: Use this while calling
 *                                   \ref GA_vc_send_rsp() to send response. \n
 *                        - data: NULL
 *                        - datalen: 0
 *                        .
 * \param [in] ga_datalen \ref sizeof ( \ref VCP_EVENT_INFO).
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \note \ref GA_vc_send_rsp() has to be called to send the read response.
 *       Refer to \ref GA_BRR_UUID inside \ref GA_BRR_CHR_CONTEXT in
 *       \ref VCP_EVENT_INFO.
 *
 * \sa ga_common_constants
 */
#define GA_VC_RD_IND                                    VCS_EVENT_RD_IND

/**
 * \brief This event is notified when a read request is received for
 * characteristic from peer device with the following values as
 * parameters in the \ref GA_PROFILE_CB registered during
 * \ref GA_vc_server_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_VC_VOCS_RD_IND
 * \param [in] ga_status \ref GA_SUCCESS : Read Request received \n
 * \param [in] ga_data Pointer to Object of type \ref VCP_EVENT_INFO \n
 *                        - context: Use this while calling
 *                                   \ref GA_vc_send_rsp() to send response.
 *                        - data: NULL
 *                        - datalen: 0
 *                        .
 * \param [in] ga_datalen \ref sizeof ( \ref VCP_EVENT_INFO).
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \note \ref GA_vc_send_rsp() has to be called to send the read response.
 *       Refer to \ref GA_BRR_UUID inside \ref GA_BRR_CHR_CONTEXT in
 *       \ref VCP_EVENT_INFO.
 *
 * \sa ga_common_constants
 */
#define GA_VC_VOCS_RD_IND                               VOCS_EVENT_RD_IND

/**
 * \brief This event is notified when a read request is received for
 * characteristic from peer device with the following values as
 * parameters in the \ref GA_PROFILE_CB registered during
 * \ref GA_vc_server_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_VC_AICS_RD_IND
 * \param [in] ga_status \ref GA_SUCCESS : Read Request received \n
 * \param [in] ga_data Pointer to Object of type \ref VCP_EVENT_INFO \n
 *                        - context: Use this while calling
 *                                   \ref GA_vc_send_rsp() to send response.
 *                        - data: NULL
 *                        - datalen: 0
 *                        .
 * \param [in] ga_datalen \ref sizeof ( \ref VCP_EVENT_INFO).
 *
 * \return \ref GA_SUCCESS (always)
 * \note \ref GA_vc_send_rsp() has to be called to send the read response.
 */
#define GA_VC_AICS_RD_IND                               AICS_EVENT_RD_IND

/** \} */

/**
 * \name VCP Renderer Events - Write
 * \{
 * \brief This section describes the Volume Control Profile Write
 * Events for Volume Renderer.
 */

/**
 * \brief This event is notified when a write request is received for Volume
 * Control Point characteristic from peer device with the following values as
 * parameters in the \ref GA_PROFILE_CB registered during
 * \ref GA_vc_server_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_VC_CP_WT_IND
 * \param [in] ga_status \ref GA_SUCCESS : Write Request received \n
 * \param [in] ga_data Pointer to Object of type \ref VCP_EVENT_INFO \n
 *                        - context: Use this while calling
 *                                   \ref GA_vc_send_rsp() to send response.
 *                        - data: Pointer to UCHAR, that includes Opcode
 *                                followed by Parameters.
 *                        - datalen: Data length of the Parameter.
 *                        .
 * \param [in] ga_datalen \ref sizeof ( \ref VCP_EVENT_INFO).
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \note \ref GA_vc_send_rsp() has to be called to send the write response.
 */
#define GA_VC_CP_WT_IND                                 VCS_EVENT_CP_WT_IND

/**
 * \brief This event is notified when a write request is received for Audio
 * Location characteristic from peer device with the following values as
 * parameters in the \ref GA_PROFILE_CB registered during
 * \ref GA_vc_server_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_VC_VOCS_SET_AUDIO_LOCATION_IND
 * \param [in] ga_status \ref GA_SUCCESS : Write Request received \n
 * \param [in] ga_data Pointer to \ref UCHAR with params as below: \n
 *                     Includes Param \n
 *                        - Audio Location ( \ref UINT32 ) \n
 *                        .
 * \param [in] ga_datalen 4
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \note Since it is WriteWithoutResponse request,
 *       There is no response expected for this event. \n
 *       The Audio Location characteristic value is a bitmask that shall be
 *       set to a value that reflects the location of an audio output that
 *       is associated with the instance of VOCS.
 *
 * \sa ga_common_constants
 */
#define GA_VC_VOCS_SET_AUDIO_LOCATION_IND               VOCS_EVENT_SET_AUDIO_LOCATION_IND

/**
 * \brief This event is notified when a write request is received for Audio
 * Output Description characteristic from peer device with the following values
 * as parameters in the \ref GA_PROFILE_CB registered during
 * \ref GA_vc_server_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_VC_VOCS_SET_AUDIO_OUT_DESC_IND
 * \param [in] ga_status \ref GA_SUCCESS : Write Request received \n
 * \param [in] ga_data Pointer to \ref UCHAR, Can be a UTF-8 String of 0 or
 *                     more characters \n
 * \param [in] ga_datalen 0 or Length of UTF-8 String.
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \note Since it is WriteWithoutResponse request,
 *       there is no response expected for this event.
 */
#define GA_VC_VOCS_SET_AUDIO_OUT_DESC_IND               VOCS_EVENT_SET_AUDIO_OUT_DESC_IND

/**
 * \brief This event is notified when a write request is received for Audio
 * Input Control Point characteristic from peer device with the following
 * values as parameters in the \ref GA_PROFILE_CB registered during
 * \ref GA_vc_server_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_VC_VOCS_CP_WT_IND
 * \param [in] ga_status \ref GA_SUCCESS : Write Request received \n
 * \param [in] ga_data Pointer to Object of type \ref VCP_EVENT_INFO \n
 *                        - context: Use this while calling
 *                                   \ref GA_vc_send_rsp() to send response.
 *                        - data: Pointer to \ref UCHAR, that includes Opcode
 *                                followed by Parameters (Change_Counter (1B),
 *                                Volume_Offset (2B)).
 *                        - datalen: Data length of the Parameter.
 *                        .
 * \param [in] ga_datalen \ref sizeof ( \ref VCP_EVENT_INFO).
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \note \ref GA_vc_send_rsp() has to be called to send the write response.
 */
#define GA_VC_VOCS_CP_WT_IND                            VOCS_EVENT_CP_WT_IND

/**
 * \brief This event is notified when a write without response request is
 * received for Audio Input Description characteristic from peer device with
 * the following values as parameters in the \ref GA_PROFILE_CB registered
 * during \ref GA_vc_server_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_VC_AICS_SET_AUDIO_INPUT_DESC_IND
 * \param [in] ga_status \ref GA_SUCCESS : Write Without Response Request
 *                       received \n
 * \param [in] ga_data Pointer to \ref UCHAR, Can be a UTF-8 String of 0 or
 *                     more characters \n
 * \param [in] ga_datalen 0 or Length of UTF-8 String.
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \note There is no response expected for this event.
 */
#define GA_VC_AICS_SET_AUDIO_INPUT_DESC_IND             AICS_EVENT_SET_AUDIO_INPUT_DESC_IND

/**
 * \brief This event is notified when a write request is received for Audio
 * Input Control Point characteristic from peer device with the following
 * values as parameters in the \ref GA_PROFILE_CB registered during
 * \ref GA_vc_server_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_VC_AICS_CP_WT_IND
 * \param [in] ga_status \ref GA_SUCCESS : Write Request received \n
 * \param [in] ga_data Pointer to Object of type \ref VCP_EVENT_INFO \n
 *                        - context: Use this while calling
 *                                   \ref GA_vc_send_rsp() to send response.
 *                        - data: Pointer to \ref UCHAR, that includes Opcode
 *                                followed by Parameters.
 *                        - datalen: Data length of the Parameter.
 *                        .
 * \param [in] ga_datalen \ref sizeof ( \ref VCP_EVENT_INFO).
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \note \ref GA_vc_send_rsp() has to be called to send the write response.
 */
#define GA_VC_AICS_CP_WT_IND                            AICS_EVENT_CP_WT_IND

/** \} */
/** \} */
/** \} */
/** \} */
/** \} */

/**
 * \addtogroup ga_micp_module
 * \{
 */

/**
 * \defgroup ga_micp_defines Defines
 * \{
 * \brief This section describes the various Defines in EtherMind
 * GA MICP Layer.
 */

/**
 * \defgroup ga_micp_error_code Error Codes
 * \{
 * \brief This section lists the Error Codes that are provided as part of
 * return of functionalities of MICP \ref ga_micp_api_defs.
 */

/** \} */

/**
 * \defgroup ga_micp_constants Constants
 * \{
 * \brief This section describes the various Constants in EtherMind
 * GA MICP Layer.
 */

/** \} */

/**
 * \defgroup ga_micp_api_evt_defs Events
 * \{
 * \brief This section describes the Microphone Control Events.
 */

/**
 * \defgroup ga_micp_cont_evt_defs Microphone Controller
 * \{
 * \brief This section describes the Microphone Control Profile Events for
 * Microphone Controller.
 */

/**
 * \name MICP Controller Events - Setup
 * \{
 * \brief This section describes the Microphone Control Profile Setup Events
 * for Microphone Controller.
 */

/**
 * \brief This event indicates the setup of a MICS Session. \n
 * Callback is triggered once discovery of service, char and descriptors,
 * configuration for Notifications is complete. \n
 * A Callback is made with the parameters as below and is notified via
 * \ref GA_PROFILE_CB registered during \ref GA_mc_client_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_MC_SETUP_CNF
 * \param [in] ga_status \ref GA_SUCCESS : Setup Complete \n
 *                       \ref GA_FAILURE : Others \n
 * \param [in] ga_data Pointer to Object of type \ref MICP_EVENT_INFO \n
 *                     If status is \ref GA_SUCCESS or \ref GA_FAILURE, \n
 *                        - srv_inst: MICP Handle for the Device \n
 *                        - data: NULL \n
 *                        - datalen: 0 \n
 *                        .
 * \param [in] ga_datalen \ref sizeof ( \ref MICP_EVENT_INFO ) \n
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_MC_SETUP_CNF                                 MC_SETUP_MICS_CNF

/**
 * \brief This event is notified on discovery of secondary service AICS with
 * peer device with the following values as parameters in the
 * \ref GA_PROFILE_CB registered during \ref GA_mc_client_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_MC_GET_CAPABILITIES_CNF
 * \param [in] ga_status \ref GA_CONTINUE : Service Handle range of discovered
 *                       AICS \n
 *                       \ref GA_SUCCESS : Service Discovery Complete \n
 *                       \ref GA_FAILURE : Others \n
 * \param [in] ga_data Pointer to Object of type \ref MICP_EVENT_INFO \n
 *                     If status is \ref GA_CONTINUE \n
 *                        - srv_inst: MICP Handle for the Device \n
 *                        - data: Pointer to object of type
 *                                \ref GA_BRR_SVC_INFO \n
 *                        - datalen: \ref sizeof ( \ref GA_BRR_SVC_INFO ) \n
 *                        .
 *                     Else \n
 *                        - srv_inst: MICP Handle for the Device \n
 *                        - data: NULL \n
 *                        - datalen: 0 \n
 *                        .
 * \param [in] ga_datalen \ref sizeof ( \ref MICP_EVENT_INFO ) \n
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_MC_GET_CAPABILITIES_CNF                      MC_DISCOVER_MICS_OPTIONAL_SRVC_CNF

/**
 * \brief This event indicates the setup of an AICS Session. \n
 * Callback is triggered once discovery of service, char and descriptors,
 * configuration for Notifications is complete. \n
 * A Callback is made with the parameters as below and is notified via
 * \ref GA_PROFILE_CB registered during \ref GA_mc_client_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_MC_SET_CAPABILITIES_CNF
 * \param [in] ga_status \ref GA_SUCCESS : Setup Complete \n
 *                       \ref GA_FAILURE : Others \n
 * \param [in] ga_data Pointer to Object of type \ref MICP_EVENT_INFO \n
 *                     If status is \ref GA_SUCCESS or \ref GA_FAILURE, \n
 *                        - srv_inst: MICP Handle for the Device \n
 *                        - data: NULL \n
 *                        - datalen: 0 \n
 *                        .
 * \param [in] ga_datalen \ref sizeof ( \ref MICP_EVENT_INFO ) \n
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_MC_SET_CAPABILITIES_CNF                      MC_SETUP_AICS_CNF

/** \} */

/**
 * \name MICP Controller Events - Read
 * \{
 * \brief This section describes the Microphone Control Profile Read Events
 * for Microphone Controller.
 */

/**
 * \brief This event is notified when a read response is received for Mute
 * characteristic from peer device with the following values as parameters in
 * the \ref GA_PROFILE_CB registered during \ref GA_mc_client_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_MC_GET_MUTE_CNF
 * \param [in] ga_status \ref GA_SUCCESS : Read Response received \n
 * \param [in] ga_data Pointer to \ref UCHAR - Mute
 *                     \ref ga_micp_mics_mute_char_values
 * \param [in] ga_datalen \ref sizeof ( \ref UINT8 )
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \sa ga_micp_mics_mute_char_values
 */
#define GA_MC_GET_MUTE_CNF                              MC_EVENT_GET_MUTE_CNF

/**
 * \brief This event is notified when a read response is received for Audio Input
 * State characteristic from peer device with the following values as
 * parameters in the \ref GA_PROFILE_CB registered during
 * \ref GA_mc_client_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_MC_AICS_GET_INPUT_STATE_CNF
 * \param [in] ga_status \ref GA_SUCCESS : Read Response received \n
 * \param [in] ga_data Pointer to \ref UCHAR with params as below: \n
 *                     Includes Param \n
 *                        - Gain_Setting ( \ref INT8 ) \n
 *                        - Mute ( \ref UINT8 )
 *                          \ref ga_micp_aics_mute_field_values \n
 *                        - Gain_Mode ( \ref UINT8 )
 *                          \ref ga_micp_aics_gain_mode_field_values \n
 *                        - Change_Counter ( \ref UINT8 ) \n
 *                        .
 * \param [in] ga_datalen 4
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \sa ga_micp_aics_mute_field_values
 * \sa ga_micp_aics_gain_mode_field_values
 */
#define GA_MC_AICS_GET_INPUT_STATE_CNF                  MC_AICS_EVENT_GET_INPUT_STATE_CNF

/**
 * \brief This event is notified when a read response is received for Gain
 * Setting Properties characteristic from peer device with the following values
 * as parameters in the \ref GA_PROFILE_CB registered during
 * \ref GA_mc_client_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_MC_AICS_GET_GAIN_SETTING_PROPRTY_CNF
 * \param [in] ga_status \ref GA_SUCCESS : Read Response received \n
 * \param [in] ga_data Pointer to \ref UCHAR with params as below: \n
 *                     Includes Param \n
 *                        - Gain_Setting_Units ( \ref UINT8 ) \n
 *                        - Gain_Setting_Minimum ( \ref INT8 ) \n
 *                        - Gain_Setting_Maximum ( \ref INT8 ) \n
 *                        .
 * \param [in] ga_datalen 3
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \sa ga_micp_aics_gain_setting
 */
#define GA_MC_AICS_GET_GAIN_SETTING_PROPRTY_CNF         MC_AICS_EVENT_GET_GAIN_SETTING_PROPRTY_CNF

/**
 * \brief This event is notified when a read response is received for Audio
 * Input Type characteristic from peer device with the following values as
 * parameters in the \ref GA_PROFILE_CB registered during
 * \ref GA_mc_client_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_MC_AICS_GET_INPUT_TYPE_CNF
 * \param [in] ga_status \ref GA_SUCCESS : Read Response received \n
 * \param [in] ga_data Pointer to \ref UCHAR.
 *                     Refer \ref ga_common_constants
 * \param [in] ga_datalen 1
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \sa ga_common_constants
 */
#define GA_MC_AICS_GET_INPUT_TYPE_CNF                   MC_AICS_EVENT_GET_INPUT_TYPE_CNF

/**
 * \brief This event is notified when a read response is received for Audio
 * Input Status characteristic from peer device with the following values as
 * parameters in the \ref GA_PROFILE_CB registered during
 * \ref GA_mc_client_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_MC_AICS_GET_INPUT_STATUS_CNF
 * \param [in] ga_status \ref GA_SUCCESS : Read Response received \n
 * \param [in] ga_data Pointer of type \ref UCHAR.
 *                     Refer \ref ga_micp_aics_input_status
 * \param [in] ga_datalen 1
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \sa ga_micp_aics_input_status
 */
#define GA_MC_AICS_GET_INPUT_STATUS_CNF                 MC_AICS_EVENT_GET_INPUT_STATUS_CNF

/**
 * \brief This event is notified when a read response is received for Audio
 * Input Description characteristic from peer device with the following values
 * as parameters in the \ref GA_PROFILE_CB registered during
 * \ref GA_mc_client_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_MC_AICS_GET_AUDIO_INPUT_DESC_CNF
 * \param [in] ga_status \ref GA_SUCCESS : Read Response received \n
 * \param [in] ga_data Pointer to \ref UCHAR, Can be a UTF-8 String of 0 or
 *                     more characters \n
 * \param [in] ga_datalen 0 or Length of UTF-8 String.
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_MC_AICS_GET_AUDIO_INPUT_DESC_CNF             MC_AICS_EVENT_GET_AUDIO_INPUT_DESC_CNF

/** \} */

/**
 * \name MICP Controller Events - Write
 * \{
 * \brief This section describes the Microphone Control Profile Write Events
 * for Microphone Controller.
 */

/**
 * \brief This event is notified when a write response is received for Mute
 * characteristic from peer device with the following values as parameters in
 * the \ref GA_PROFILE_CB registered during \ref GA_mc_client_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_MC_SET_MUTE_CNF
 * \param [in] ga_status \ref GA_SUCCESS : Write Response received \n
 * \param [in] ga_data NULL \n
 * \param [in] ga_datalen 0
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \sa ga_micp_mics_mute_char_values
 */
#define GA_MC_SET_MUTE_CNF                              MC_EVENT_SET_MUTE_CNF

/**
 * \brief This event is notified when a write response is received for Audio
 * Input Control Point characteristic from peer device with the following
 * values as parameters in the \ref GA_PROFILE_CB registered during
 * \ref GA_mc_client_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_MC_AICS_CP_WT_CNF
 * \param [in] ga_status \ref GA_SUCCESS : Write Response received \n
 * \param [in] ga_data NULL \n
 * \param [in] ga_datalen 0
 *
 * \return\ref GA_SUCCESS (always)
 *
 * \sa ga_micp_aics_cp_req_opc
 */
#define GA_MC_AICS_CP_WT_CNF                            MC_AICS_EVENT_CP_WT_CNF

/** \} */

/**
 * \name MICP Controller Events - Notification
 * \{
 * \brief This section describes the Microphone Control Profile Notification
 * Events for Microphone Controller.
 */

/**
 * \brief This event is notified when a notification is received for Mute
 * characteristic from peer device with the following values as
 * parameters in the \ref GA_PROFILE_CB registered during
 * \ref GA_mc_client_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_MC_MUTE_NTF
 * \param [in] ga_status \ref GA_SUCCESS Notification received
 * \param [in] ga_data Pointer to \ref UCHAR - Mute
 *                     \ref ga_micp_mics_mute_char_values
 * \param [in] ga_datalen \ref sizeof ( \ref UINT8 )
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \sa ga_micp_mics_mute_char_values
 */
#define GA_MC_MUTE_NTF                                  MC_EVENT_MUTE_NTF

/**
 * \brief This event is notified when a notification is received for Audio
 * Input State characteristic from peer device with the following values as
 * parameters in the \ref GA_PROFILE_CB registered during
 * \ref GA_mc_client_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_MC_AICS_INPUT_STATE_NTF
 * \param [in] ga_status \ref GA_SUCCESS Notification received
 * \param [in] ga_data Pointer to \ref UCHAR with params as below: \n
 *                     Includes Param \n
 *                         - Gain_Setting ( \ref INT8 ) \n
 *                         - Mute ( \ref UINT8 )
 *                           \ref ga_micp_aics_mute_field_values \n
 *                         - Gain_Mode ( \ref UINT8 )
 *                           \ref ga_micp_aics_gain_mode_field_values \n
 *                         - Change_Counter ( \ref UINT8 ) \n
 *                         .
 * \param [in] ga_datalen 4
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_MC_AICS_INPUT_STATE_NTF                      MC_AICS_EVENT_CP_INPUT_STATE_NTF

/**
 * \brief This event is notified when a notification is received for Audio
 * Input Status characteristic from peer device with the following values as
 * parameters in the \ref GA_PROFILE_CB registered during
 * \ref GA_mc_client_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_MC_AICS_INPUT_STATUS_NTF
 * \param [in] ga_status \ref GA_SUCCESS Notification received
 * \param [in] ga_data Pointer of type \ref UCHAR.
 *                     Refer \ref ga_micp_aics_input_status
 * \param [in] ga_datalen 1
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_MC_AICS_INPUT_STATUS_NTF                     MC_AICS_EVENT_CP_INPUT_STATUS_NTF

/**
 * \brief This event is notified when a notification is received for Audio
 * Input Description characteristic from peer device with the following values
 * as parameters in the \ref GA_PROFILE_CB registered during
 * \ref GA_mc_client_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_MC_AICS_AUDIO_INPUT_DESC_NTF
 * \param [in] ga_status \ref GA_SUCCESS Notification received
 * \param [in] ga_data Pointer to UCHAR, Can be a UTF-8 String of 0 or more
 *                     characters \n
 * \param [in] ga_datalen 0 or Length of UTF-8 String.
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_MC_AICS_AUDIO_INPUT_DESC_NTF                 MC_AICS_EVENT_AUDIO_INPUT_DESC_NTF

/** \} */

/**
 * \name MICP Controller Events - Release
 * \{
 * \brief This section describes the Microphone Control Profile Release Events
 * for Microphone Controller.
 */

/**
 * \brief This event is notified when a MICS Service context is released.
 * Configuration of Notifications for char are disabled followed by release
 * of MICS context. \n
 * A Callback is made with the parameters as below and is notified via
 * \ref GA_PROFILE_CB registered during \ref GA_mc_client_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_MC_RELEASE_CNF
 * \param [in] ga_status \ref GA_SUCCESS : Setup Complete \n
 *                       \ref GA_FAILURE : Others \n
 * \param [in] ga_data If status is \ref GA_SUCCESS or \ref GA_FAILURE, \n
 *                        - ga_data: NULL \n
 *                        .
 * \param [in] ga_datalen If status is \ref GA_SUCCESS or \ref GA_FAILURE, \n
 *                          - ga_datalen: 0 \n
 *                          .
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_MC_RELEASE_CNF                               MC_RELEASE_MICS_CNF

/**
 * \brief This event is notified after AICS Service context is released.
 * Configuration of Notifications for char are disabled followed by release
 * of AICS context. \n
 * A Callback is made with the parameters as below and is notified via
 * \ref GA_PROFILE_CB registered during \ref GA_mc_client_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_MC_RELEASE_CAPABILITY_CNF
 * \param [in] ga_status \ref GA_SUCCESS : Release Complete \n
 *                       \ref GA_FAILURE : Others \n
 * \param [in] ga_data If status is \ref GA_SUCCESS or \ref GA_FAILURE, \n
 *                        - ga_data: NULL \n
 *                        .
 * \param [in] ga_datalen If status is \ref GA_SUCCESS or \ref GA_FAILURE, \n
 *                           - ga_datalen: 0 \n
 *                           .
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_MC_RELEASE_CAPABILITY_CNF                    MC_RELEASE_AICS_CNF

/** \} */

/** \} */

/**
 * \defgroup ga_micp_dev_evt_defs Microphone Device
 * \{
 * \brief This section describes the Microphone Control Profile Events
 * for Microphone Device.
 */

/**
 * \name MICP Device Events - Read
 * \{
 * \brief This section describes the Microphone Control Profile Read Events
 * for Microphone Device.
 */

/**
 * \brief This event is notified when a read request is received for Mute
 * characteristic from peer device with the following values as
 * parameters in the \ref GA_PROFILE_CB registered during
 * \ref GA_mc_server_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_MC_RD_IND
 * \param [in] ga_status \ref GA_SUCCESS : Read Request received \n
 * \param [in] ga_data Pointer to Object of type \ref MICP_EVENT_INFO \n
 *                        - context: Use this while calling
 *                                   \ref GA_mc_send_rsp() to send response.
 *                        - data: NULL
 *                        - datalen: 0
 *                        .
 * \param [in] ga_datalen \ref sizeof ( \ref MICP_EVENT_INFO)
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \note \ref GA_mc_send_rsp() has to be called to send the read response. \n
 *       Allowed values for Mute characteristics are defined in \ref
 *       ga_micp_mics_mute_char_values.
 */
#define GA_MC_RD_IND                                    MC_EVENT_GET_MUTE_IND

/**
 * \brief This event is notified when a read request is received for
 * characteristic from peer device with the following values as
 * parameters in the \ref GA_PROFILE_CB registered during
 * \ref GA_mc_server_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_MC_AICS_RD_IND
 * \param [in] ga_status \ref GA_SUCCESS : Read Request received \n
 * \param [in] ga_data Pointer to Object of type \ref MICP_EVENT_INFO \n
 *                        - context: Use this while calling
 *                                   \ref GA_mc_send_rsp() to send response.
 *                        - data: NULL
 *                        - datalen: 0
 *                        .
 * \param [in] ga_datalen \ref sizeof ( \ref MICP_EVENT_INFO).
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \note \ref GA_mc_send_rsp() has to be called to send the read response.
 */
#define GA_MC_AICS_RD_IND                               MC_AICS_EVENT_RD_IND

/** \} */

/**
 * \name MICP Device Events - Write
 * \{
 * \brief This section describes the Microphone Control Profile Write Events
 * for Microphone Device.
 */

/**
 * \brief This event is notified when a write request is received for Mute
 * characteristic from peer device with the following values as
 * parameters in the \ref GA_PROFILE_CB registered during
 * \ref GA_mc_server_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_MC_SET_MUTE_IND
 * \param [in] ga_status \ref GA_SUCCESS : Write Request received \n
 * \param [in] ga_data Pointer to Object of type \ref MICP_EVENT_INFO \n
 *                        - context: Use this while calling
 *                                   \ref GA_mc_send_rsp() to send response.
 *                        - data: \ref UINT8 depicting value of Mute
 *                                \ref ga_micp_mics_mute_char_values
 *                        - datalen: \ref sizeof ( \ref UINT8 )
 *                        .
 * \param [in] ga_datalen \ref sizeof ( \ref MICP_EVENT_INFO)
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \note \ref GA_mc_send_rsp() has to be called to send the write response.
 */
#define GA_MC_SET_MUTE_IND                              MC_EVENT_SET_MUTE_IND

/**
 * \brief This event is notified when a write without response request is
 * received for Audio Input Description characteristic from peer device with
 * the following values as parameters in the \ref GA_PROFILE_CB registered
 * during \ref GA_mc_server_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_MC_AICS_SET_AUDIO_INPUT_DESC_IND
 * \param [in] ga_status \ref GA_SUCCESS : Write Without Response Request
 *                       received \n
 * \param [in] ga_data Pointer to \ref UCHAR, Can be a UTF-8 String of 0 or
 *                     more characters. \n
 * \param [in] ga_datalen 0 or Length of UTF-8 String.
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \note Since it is WriteWithoutResponse request
 *       there is no response expected for this event.
 */
#define GA_MC_AICS_SET_AUDIO_INPUT_DESC_IND             MC_AICS_EVENT_SET_AUDIO_INPUT_DESC_IND

/**
 * \brief This event is notified when a write request is received for Audio
 * Input Control Point characteristic from peer device with the following
 * values as parameters in the \ref GA_PROFILE_CB registered during
 * \ref GA_mc_server_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_MC_AICS_CP_WT_IND
 * \param [in] ga_status \ref GA_SUCCESS : Write Request received \n
 * \param [in] ga_data Pointer to Object of type \ref MICP_EVENT_INFO \n
 *                        - context: Use this while calling
 *                                   \ref GA_mc_send_rsp() to send response.
 *                        - data: Pointer to \ref UCHAR, that includes Opcode
 *                                followed by Parameters.
 *                        - datalen: Data length of the Parameter.
 *                        .
 * \param [in] ga_datalen \ref sizeof ( \ref MICP_EVENT_INFO).
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \note \ref GA_mc_send_rsp() has to be called to send the write response.
 */
#define GA_MC_AICS_CP_WT_IND                            MC_AICS_EVENT_CP_WT_IND

/** \} */

/** \} */

/**
 * \brief This is an event to indicate random event. This event shall never be
 * generated.
 *
 * \param [in] ga_ep NULL
 * \param [in] ga_event \ref GA_EVENT_INVALID
 * \param [in] ga_status \ref NULL \n
 * \param [in] ga_data NULL \n
 * \param [in] ga_datalen 0 \n
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_EVENT_INVALID                                MC_EVENT_INVALID

/** \} */
/** \} */
/** \} */

/**
 * \addtogroup ga_csip_module
 * \{
 */

/**
 * \defgroup ga_csip_defines Defines
 * \{
 * \brief This section describes the various Defines in EtherMind
 * GA CSIP Layer.
 */

/**
 * \defgroup ga_csip_api_evt_defs Events
 * \{
 * \brief This section describes the Coordinated Set Identification Events.
 */

/**
 * \defgroup ga_csip_setco_evt_defs SetCoordinator
 * \{
 * \brief This section describes the Coordinated Set Identification Profile
 * Events for SetCoordinator.
 */

/**
 * \brief This event is notified as result of RSI verification
 * procedure initiated by the application. The event passes the
 * parameters as below to the application callback as in
 * \ref GA_PROFILE_CB registered during \ref GA_cs_client_init().
 *
 * \param [in] ga_ep NULL
 * \param [in] ga_event \ref GA_CS_RSI_VERIFY_COMPLETE
 * \param [in] ga_status \ref GA_SUCCESS or Error Code.
 * \param [in] ga_data Pointer to the RSI given for verification.
 * \param [in] ga_datalen 6
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_CS_RSI_VERIFY_COMPLETE                      CSIP_RSI_VERIFY_COMPLETE

/**
 * \name CSIP SetCoordinator Events - Setup
 * \{
 * \brief This section describes the Coordinated Set Identification Profile
 * Setup Events for SetCoordinator.
 */

/**
 * \brief This event is notified on discovery of CSIS service with the
 * following values as parameters in the \ref GA_PROFILE_CB
 * registered during \ref GA_cs_client_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_CS_DISCOVER_CNF \n
 * \param [in] ga_status \ref GA_SUCCESS : Service found \n
 *                       \ref GA_FAILURE : Service not found \n
 * \param [in] ga_data If status is \ref GA_SUCCESS \n
 *                        - ga_data: Pointer to object of type \ref CSIP_EVENT_INFO \n
 *                           - context: To be ignored by the application \n
 *                           - data: Pointer to object of type
 *                                   \ref GA_BRR_SVC_INFO \n
 *                                   Parameter depicts the Service Handle -
 *                                   Start and End. \n
 *                           - datalen: \ref sizeof ( \ref GA_BRR_SVC_INFO) \n
 *                           - handle: CSIS context Handle for the Device. \n
 *                           .
 *                        .
 *                     Else \n
 *                        - ga_data: NULL \n
 *                        .
 * \param [in] ga_datalen If status is \ref GA_SUCCESS \n
 *                           - ga_datalen: \ref sizeof ( \ref CSIP_EVENT_INFO) \n
 *                           .
 *                        Else \n
 *                           - ga_datalen: 0 \n
 *                           .
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_CS_DISCOVER_CNF                              CSIP_DISCOVER_CNF

/**
 * \brief This event is notified on successful setup of CSIP context with the
 * peer device with following values as parameters in the \ref GA_PROFILE_CB
 * registered during \ref GA_cs_client_init().
 * Char and Descriptor discovery is followed by Configuration of Notification
 * of any char if applicable.
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_CS_SETUP_CNF \n
 * \param [in] ga_status \ref GA_CONTINUE : Setup Ongoing \n
 *                       \ref GA_SUCCESS : Setup Done \n
 *                       \ref GA_FAILURE : Setup Failed \n
 * \param [in] ga_data If status is \ref GA_SUCCESS \n
 *                        - ga_data: Pointer to object of type \ref CSIP_EVENT_INFO \n
 *                           - context: To be ignored by the application \n
 *                           - data: NULL \n
 *                           - datalen: 0 \n
 *                           - handle: CSIS context Handle for the Device. \n
 *                           .
 *                        .
 *                     Else \n
 *                        - ga_data: NULL \n
 *                        .
 * \param [in] ga_datalen If status is \ref GA_SUCCESS \n
 *                           - ga_datalen: \ref sizeof ( \ref CSIP_EVENT_INFO) \n
 *                           .
 *                        Else \n
 *                           - ga_datalen: 0 \n
 *                           .
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_CS_SETUP_CNF                                 CSIP_SETUP_CNF

/** \} */

/**
 * \name CSIP SetCoordinator Events - Read
 * \{
 * \brief This section describes the Coordinated Set Identification Profile
 * Read Events for SetCoordinator.
 */

/**
 * \brief This event is notified when a read response is received for Set
 * Identity Resolving Key characteristic from peer device with the following
 * values as parameters in the \ref GA_PROFILE_CB registered during
 * \ref GA_cs_client_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_CS_SIRK_GET_CNF
 * \param [in] ga_status \ref GA_SUCCESS : Read Response received \n
 * \param [in] ga_data If status is \ref GA_SUCCESS \n
 *                        - ga_data: Pointer to object of type \ref CSIP_EVENT_INFO \n
 *                           - context: To be ignored by the application \n
 *                           - data: Pointer to object of type \ref CSIP_SIRK \n
 *                           - datalen: \ref sizeof ( \ref CSIP_SIRK) \n
 *                           - handle: CSIS context Handle for the Device. \n
 *                           .
 *                        .
 *                     Else \n
 *                        - ga_data: NULL \n
 *                        .
 * \param [in] ga_datalen If status is \ref GA_SUCCESS \n
 *                           - ga_datalen: \ref sizeof ( \ref CSIP_EVENT_INFO) \n
 *                           .
 *                        Else \n
 *                           - ga_datalen: 0 \n
 *                           .
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_CS_SIRK_GET_CNF                              CSIP_SIRK_GET_CNF

/**
 * \brief This event is notified when a read response is received for
 * Coordinated Set Size characteristic from peer device with the following
 * values as parameters in the \ref GA_PROFILE_CB registered during
 * \ref GA_cs_client_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_CS_SETSIZE_GET_CNF
 * \param [in] ga_status \ref GA_SUCCESS : Read Response received \n
 * \param [in] ga_data If status is \ref GA_SUCCESS \n
 *                        - ga_data: Pointer to object of type \ref CSIP_EVENT_INFO \n
 *                           - context: To be ignored by the application \n
 *                           - data: Pointer to object of type \ref UINT8 (Size) \n
 *                           - datalen: \ref sizeof ( \ref UINT8 ) \n
 *                           - handle: CSIS context Handle for the Device. \n
 *                           .
 *                        .
 *                     Else \n
 *                        - ga_data: NULL \n
 *                        .
 * \param [in] ga_datalen If status is \ref GA_SUCCESS \n
 *                           - ga_datalen: \ref sizeof ( \ref CSIP_EVENT_INFO) \n
 *                           .
 *                        Else \n
 *                           - ga_datalen: 0 \n
 *                           .
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_CS_SETSIZE_GET_CNF                           CSIP_SETSIZE_GET_CNF

/**
 * \brief This event is notified when a read response is received for Set
 * Member Lock characteristic from peer device with the following values as
 * parameters in the \ref GA_PROFILE_CB registered during
 * \ref GA_cs_client_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_CS_SETMEMBER_LOCK_GET_CNF
 * \param [in] ga_status \ref GA_SUCCESS : Read Response received \n
 * \param [in] ga_data If status is \ref GA_SUCCESS \n
 *                        - ga_data: Pointer to object of type \ref CSIP_EVENT_INFO \n
 *                           - context: To be ignored by the application \n
 *                           - data: Pointer to object of type \ref UINT8 (Lock)\n
 *                           - datalen: \ref sizeof ( \ref UINT8 ) \n
 *                           - handle: CSIS context Handle for the Device. \n
 *                           .
 *                        .
 *                     Else \n
 *                        - ga_data: NULL \n
 *                        .
 * \param [in] ga_datalen If status is \ref GA_SUCCESS \n
 *                           - ga_datalen: \ref sizeof ( \ref CSIP_EVENT_INFO) \n
 *                           .
 *                        Else \n
 *                           - ga_datalen: 0 \n
 *                           .
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_CS_SETMEMBER_LOCK_GET_CNF                    CSIP_SETMEMBER_LOCK_GET_CNF

/**
 * \brief This event is notified when a read response is received for
 * Set Member Rank characteristic from peer device with the following values as
 * parameters in the \ref GA_PROFILE_CB registered during
 * \ref GA_cs_client_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_CS_SETMEMBER_RANK_GET_CNF
 * \param [in] ga_status \ref GA_SUCCESS : Read Response received \n
 * \param [in] ga_data If status is \ref GA_SUCCESS \n
 *                        - ga_data: Pointer to object of type \ref CSIP_EVENT_INFO \n
 *                           - context: To be ignored by the application \n
 *                           - data: Pointer to object of type \ref UINT8 (Rank)\n
 *                           - datalen: \ref sizeof ( \ref UINT8 ) \n
 *                           - handle: CSIS context Handle for the Device. \n
 *                           .
 *                        .
 *                     Else \n
 *                        - ga_data: NULL \n
 *                        .
 * \param [in] ga_datalen If status is \ref GA_SUCCESS \n
 *                           - ga_datalen: \ref sizeof ( \ref CSIP_EVENT_INFO) \n
 *                           .
 *                        Else \n
 *                           - ga_datalen: 0 \n
 *                           .
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_CS_SETMEMBER_RANK_GET_CNF                    CSIP_SETMEMBER_RANK_GET_CNF

/** \} */

/**
 * \name CSIP SetCoordinator Events - Write
 * \{
 * \brief This section describes the Coordinated Set Identification Profile
 * Write Events for SetCoordinator.
 */

/**
 * \brief This event is notified when a write response is received for Set
 * Member Lock characteristic from peer device with the following values as
 * parameters in the \ref GA_PROFILE_CB registered during
 * \ref GA_cs_client_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_CS_SETMEMBER_LOCK_SET_CNF
 * \param [in] ga_status \ref GA_SUCCESS : Write Response received \n
 * \param [in] ga_data If status is \ref GA_SUCCESS \n
 *                        - ga_data: Pointer to object of type \ref CSIP_EVENT_INFO \n
 *                           - context: To be ignored by the application \n
 *                           - data: NULL \n
 *                           - datalen: 0 \n
 *                           - handle: CSIS context Handle for the Device. \n
 *                           .
 *                        .
 *                     Else \n
 *                        - ga_data: NULL \n
 *                        .
 * \param [in] ga_datalen If status is \ref GA_SUCCESS \n
 *                           - ga_datalen: \ref sizeof ( \ref CSIP_EVENT_INFO) \n
 *                           .
 *                        Else \n
 *                           - ga_datalen: 0 \n
 *                           .
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_CS_SETMEMBER_LOCK_SET_CNF                    CSIP_SETMEMBER_LOCK_SET_CNF

/** \} */

/**
 * \name CSIP SetCoordinator Events - Notification
 * \{
 * \brief This section describes the Coordinated Set Identification Profile
 * Notification Events for SetCoordinator.
 */

/**
 * \brief This event is notified when a notification is received for Set
 * Identity Resolving Key characteristic from peer device with the following
 * values as parameters in the \ref GA_PROFILE_CB registered during
 * \ref GA_cs_client_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_CS_SIRK_NTF \n
 * \param [in] ga_status \ref GA_SUCCESS : Notification received \n
 * \param [in] ga_data If status is \ref GA_SUCCESS \n
 *                        - ga_data: Pointer to object of type \ref CSIP_EVENT_INFO \n
 *                           - context: To be ignored by the application \n
 *                           - data: Pointer to object of type \ref CSIP_SIRK \n
 *                           - datalen: \ref sizeof ( \ref CSIP_SIRK) \n
 *                           - handle: CSIS context Handle for the Device. \n
 *                           .
 *                        .
 *                     Else \n
 *                        - ga_data: NULL \n
 *                        .
 * \param [in] ga_datalen If status is \ref GA_SUCCESS \n
 *                           - ga_datalen: \ref sizeof ( \ref CSIP_EVENT_INFO) \n
 *                           .
 *                        Else \n
 *                           - ga_datalen: 0 \n
 *                           .
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_CS_SIRK_NTF                                CSIP_SIRK_NTF

/**
 * \brief This event is notified when a notification is received for
 * Coordinated Set Size characteristic from peer device with the following
 * values as parameters in the \ref GA_PROFILE_CB registered during
 * \ref GA_cs_client_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_CS_SETSIZE_NTF \n
 * \param [in] ga_status \ref GA_SUCCESS : Notification received \n
 * \param [in] ga_data If status is \ref GA_SUCCESS \n
 *                        - ga_data: Pointer to object of type \ref CSIP_EVENT_INFO \n
 *                           - context: To be ignored by the application \n
 *                           - data: Pointer to object of type \ref UINT8 \n
 *                           - datalen: \ref sizeof ( \ref UINT8) \n
 *                           - handle: CSIS context Handle for the Device. \n
 *                           .
 *                        .
 *                     Else \n
 *                        - ga_data: NULL \n
 *                        .
 * \param [in] ga_datalen If status is \ref GA_SUCCESS \n
 *                           - ga_datalen: \ref sizeof ( \ref CSIP_EVENT_INFO) \n
 *                           .
 *                        Else \n
 *                           - ga_datalen: 0 \n
 *                           .
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_CS_SETSIZE_NTF                             CSIP_SET_SIZE_NTF

/**
 * \brief This event is notified when a notification is received for
 * Coordinated Set Member Lock characteristic from peer device with the
 * following values as parameters in the \ref GA_PROFILE_CB registered during
 * \ref GA_cs_client_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_CS_SETMEMBER_LOCK_STATUS_NTF \n
 * \param [in] ga_status \ref GA_SUCCESS : Notification received \n
 * \param [in] ga_data If status is \ref GA_SUCCESS \n
 *                        - ga_data: Pointer to object of type \ref CSIP_EVENT_INFO \n
 *                           - context: To be ignored by the application \n
 *                           - data: Pointer to object of type \ref UINT8 \n
 *                           - datalen: \ref sizeof ( \ref UINT8) \n
 *                           - handle: CSIS context Handle for the Device. \n
 *                           .
 *                        .
 *                     Else \n
 *                        - ga_data: NULL \n
 *                        .
 * \param [in] ga_datalen If status is \ref GA_SUCCESS \n
 *                           - ga_datalen: \ref sizeof ( \ref CSIP_EVENT_INFO) \n
 *                           .
 *                        Else \n
 *                           - ga_datalen: 0 \n
 *                           .
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_CS_SETMEMBER_LOCK_STATUS_NTF               CSIP_SETMEMBER_LOCK_STATUS_NTF

/** \} */

/**
 * \name CSIP SetCoordinator Events - Release
 * \{
 * \brief This section describes the Coordinated Set Identification Profile
 * Release Events for SetCoordinator.
 */

/**
 * \brief The event is notified when CSIS context is released with the
 * \ref GA_PROFILE_CB registered during \ref GA_cs_client_init().
 * When the event is notified, notification is disabled and context will be
 * cleared.
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_CS_RELEASE_CNF \n
 * \param [in] ga_status \ref GA_SUCCESS : Release completed \n
 *                       \ref GA_FAILURE : Release Failed \n
 * \param [in] ga_data If status is \ref GA_SUCCESS \n
 *                        - ga_data: Pointer to object of type \ref CSIP_EVENT_INFO \n
 *                           - context: To be ignored by the application \n
 *                           - data: NULL \n
 *                           - datalen: 0 \n
 *                           - handle: CSIS context Handle for the Device. \n
 *                           .
 *                        .
 *                     Else \n
 *                        - ga_data: NULL \n
 *                        .
 * \param [in] ga_datalen If status is \ref GA_SUCCESS \n
 *                           - ga_datalen: \ref sizeof ( \ref CSIP_EVENT_INFO) \n
 *                           .
 *                        Else \n
 *                           - ga_datalen: 0 \n
 *                           .
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_CS_RELEASE_CNF                               CSIP_RELEASE_CNF

/** \} */

/** \} */

/**
 * \defgroup ga_csip_setmem_evt_defs SetMember
 * \{
 * \brief This section describes the Coordinated Set Identification Profile
 * Events for SetMember.
 */

/**
 * \brief This event is notified as result of RSI generation
 * procedure initiated by the application. The event passes the
 * parameters as below to the application callback as in
 * \ref GA_PROFILE_CB registered during \ref GA_cs_server_init().
 *
 * \param [in] ga_ep NULL
 * \param [in] ga_event \ref GA_CS_RSI_CREATE_COMPLETE
 * \param [in] ga_status \ref GA_SUCCESS
 * \param [in] ga_data Pointer to the RSI Created
 * \param [in] ga_datalen 6
 *
 * \return \ref GA_SUCCESS (always)
 */
#define GA_CS_RSI_CREATE_COMPLETE                      CSIP_RSI_CREATE_COMPLETE

/**
 * \name CSIP SetMember Events - Read
 * \{
 * \brief This section describes the Coordinated Set Identification Profile
 * Read Events for SetMember.
 */

/**
 * \brief This event is notified when a read request is received for Set
 * Identity Resolving Key characteristic from peer device with the following
 * parameters as below to the application callback as in
 * \ref GA_PROFILE_CB registered during \ref GA_cs_server_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_CS_SIRK_GET_IND \n
 * \param [in] ga_status \ref GA_SUCCESS : Read Request received \n
 * \param [in] ga_data If status is \ref GA_SUCCESS \n
 *                        - ga_data: Pointer to object of type \ref CSIP_EVENT_INFO \n
 *                           - context: Use this while calling
 *                                      \ref GA_cs_send_response() to send
 *                                      response. \n
 *                           - data: NULL \n
 *                           - datalen: 0 \n
 *                           - handle: CSIS Member Handle for the Device. \n
 *                           .
 *                        .
 *                     Else \n
 *                        - ga_data: NULL \n
 *                        .
 * \param [in] ga_datalen If status is \ref GA_SUCCESS \n
 *                           - ga_datalen: \ref sizeof ( \ref CSIP_EVENT_INFO) \n
 *                           .
 *                        Else \n
 *                           - ga_datalen: 0 \n
 *                           .
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \note \ref GA_cs_send_response() has to be called to send the read response
 *       if the event is notified for CSIS. \n
 *       If the event is notified for CAS_CSIS, then this is only informational
 *       to the application. The application need not send any response.
 *       For CAS_CSIS, this event will be notified to application only if
 *       \ref CAP_ENABLE_CSIS_READ_APP_CB flag is enabled.
 */
#define GA_CS_SIRK_GET_IND                              CSIP_SIRK_GET_IND

/**
 * \brief This event is notified when a read request is received for
 * Coordinated Set Size characteristic from peer device with the following
 * parameters as below to the application callback as in
 * \ref GA_PROFILE_CB registered during \ref GA_cs_server_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_CS_SETSIZE_GET_IND \n
 * \param [in] ga_status \ref GA_SUCCESS : Read Request received \n
 * \param [in] ga_data If status is \ref GA_SUCCESS \n
 *                        - ga_data: Pointer to object of type \ref CSIP_EVENT_INFO \n
 *                           - context: Use this while calling
 *                                      \ref GA_cs_send_response() to send
 *                                      response. \n
 *                           - data: NULL \n
 *                           - datalen: 0 \n
 *                           - handle: CSIS Member Handle for the Device. \n
 *                           .
 *                        .
 *                     Else \n
 *                        - ga_data: NULL \n
 *                        .
 * \param [in] ga_datalen If status is \ref GA_SUCCESS \n
 *                           - ga_datalen: \ref sizeof ( \ref CSIP_EVENT_INFO) \n
 *                           .
 *                        Else \n
 *                           - ga_datalen: 0 \n
 *                           .
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \note \ref GA_cs_send_response() has to be called to send the read response
 *       if the event is notified for CSIS. \n
 *       Allowed values for the Coordinated Set Size characteristic are
 *       integers in the range 0x01 to 0xFF. Value 0x00 is Prohibited. \n
 *       If the event is notified for CAS_CSIS, then this is only informational
 *       to the application. The application need not send any response.
 *       For CAS_CSIS, this event will be notified to application only if
 *       \ref CAP_ENABLE_CSIS_READ_APP_CB flag is enabled.
 */
#define GA_CS_SETSIZE_GET_IND                           CSIP_SETSIZE_GET_IND

/**
 * \brief This event is notified when a read request is received for
 * Coordinated Set Member Lock characteristic from peer device with the
 * parameters as below to the application callback as in
 * \ref GA_PROFILE_CB registered during \ref GA_cs_server_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_CS_SETMEMBER_LOCK_GET_IND \n
 * \param [in] ga_status \ref GA_SUCCESS : Read Request received \n
 * \param [in] ga_data If status is \ref GA_SUCCESS \n
 *                        - ga_data: Pointer to object of type \ref CSIP_EVENT_INFO \n
 *                           - context: Use this while calling
 *                                      \ref GA_cs_send_response() to send
 *                                      response. \n
 *                           - data: NULL \n
 *                           - datalen: 0 \n
 *                           - handle: CSIS Member Handle for the Device. \n
 *                           .
 *                        .
 *                     Else \n
 *                        - ga_data: NULL \n
 *                        .
 * \param [in] ga_datalen If status is \ref GA_SUCCESS \n
 *                           - ga_datalen: \ref sizeof ( \ref CSIP_EVENT_INFO) \n
 *                           .
 *                        Else \n
 *                           - ga_datalen: 0 \n
 *                           .
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \note \ref GA_cs_send_response() has to be called to send the read response
 *       if the event is notified for CSIS. \n
 *       Allowed values for the Coordinated Set Member Lock characteristic are
 *       defined as \ref ga_csip_set_member_lock. \n
 *       If the event is notified for CAS_CSIS, then this is only informational
 *       to the application. The application need not send any response.
 *       For CAS_CSIS, this event will be notified to application only if
 *       \ref CAP_ENABLE_CSIS_READ_APP_CB flag is enabled.
 */
#define GA_CS_SETMEMBER_LOCK_GET_IND                    CSIP_SETMEMBER_LOCK_GET_IND

/**
 * \brief This event is notified when a read request is received for
 * Coordinated Set Member Rank characteristic from peer device with the
 * parameters as below to the application callback as in
 * \ref GA_PROFILE_CB registered during \ref GA_cs_server_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_CS_SETMEMBER_RANK_GET_IND \n
 * \param [in] ga_status \ref GA_SUCCESS : Read Request received \n
 * \param [in] ga_data If status is \ref GA_SUCCESS \n
 *                        - ga_data: Pointer to object of type \ref CSIP_EVENT_INFO \n
 *                           - context: Use this while calling
 *                                      \ref GA_cs_send_response() to send
 *                                      response. \n
 *                           - data: NULL \n
 *                           - datalen: 0 \n
 *                           - handle: CSIS Member Handle for the Device. \n
 *                           .
 *                        .
 *                     Else \n
 *                        - ga_data: NULL \n
 *                        .
 * \param [in] ga_datalen If status is \ref GA_SUCCESS \n
 *                           - ga_datalen: \ref sizeof ( \ref CSIP_EVENT_INFO) \n
 *                           .
 *                        Else \n
 *                           - ga_datalen: 0 \n
 *                           .
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \note \ref GA_cs_send_response() has to be called to send the read response
 *       if the event is notified for CSIS. \n
 *       Allowed values for the Set Member Rank characteristics are positive
 *       integer numbers starting from 0x01. \n
 *       If the event is notified for CAS_CSIS, then this is only informational
 *       to the application. The application need not send any response.
 *       For CAS_CSIS, this event will be notified to application only if
 *       \ref CAP_ENABLE_CSIS_READ_APP_CB flag is enabled.
 */
#define GA_CS_SETMEMBER_RANK_GET_IND                    CSIP_SETMEMBER_RANK_GET_IND

/** \} */

/**
 * \name CSIP SetMember Events - Write
 * \{
 * \brief This section describes the Coordinated Set Identification Profile
 * Write Events for SetMember.
 */

/**
 * \brief This event is notified when a write request is received for
 * Set Member Lock characteristic from peer device with the following values as
 * parameters as below to the application callback as in
 * \ref GA_PROFILE_CB registered during \ref GA_cs_server_init().
 *
 * \param [in] ga_ep Pointer to peer device handle \ref
 * \param [in] ga_event \ref GA_CS_SETMEMBER_LOCK_SET_IND \n
 * \param [in] ga_status \ref GA_SUCCESS : Write Request received \n
 * \param [in] ga_data If status is \ref GA_SUCCESS \n
 *                        - ga_data: Pointer to object of type \ref CSIP_EVENT_INFO \n
 *                           - context: Use this while calling
 *                                      \ref GA_cs_send_response() to send
 *                                      response. \n
 *                           - data: Pointer to object of type \ref UINT8
 *                                   depicting value of Lock
 *                                   \ref ga_csip_set_member_lock. \n
 *                           - datale: \ref sizeof ( \ref UINT8 )
 *                           - handle: CSIS Member Handle for the Device. \n.
 *                           .
 *                        .
 *                     Else \n
 *                        - ga_data: NULL \n
 *                        .
 * \param [in] ga_datalen If status is \ref GA_SUCCESS \n
 *                           - ga_datalen: \ref sizeof ( \ref CSIP_EVENT_INFO) \n
 *                           .
 *                        Else \n
 *                           - ga_datalen: 0 \n
 *                           .
 *
 * \return \ref GA_SUCCESS (always)
 *
 * \note \ref GA_cs_send_response() has to be called to send the
 *       write response.
 */
#define GA_CS_SETMEMBER_LOCK_SET_IND                    CSIP_SETMEMBER_LOCK_SET_IND

/** \} */

/** \} */

/**
 * This is an event to indicate unknown event. This event shall never be
 * generated.
 *
 * \param [in] ga_ep NULL
 * \param [in] ga_event \ref CSIP_EVENT_INVALID
 * \param [in] ga_status \ref NULL \n
 * \param [in] ga_data NULL \n
 * \param [in] ga_datalen  0 \n
 *
 * \return \ref GA_SUCCESS (always)
 */
#define CSIP_EVENT_INVALID                              0xFFU

/** \} */
/** \} */
/** \} */

/**
 * \addtogroup ga_bap_module
 * \{
 */

/**
 * \addtogroup ga_bap_bc_module
 * \{
 */

/**
 * \addtogroup ga_bap_bc_defines
 * \{
 */

/**
 * \addtogroup ga_bap_bc_source_sink_common_def
 * \{
 */

/**
 * \addtogroup ga_bap_bc_source_sink_common_constants
 * \{
 */

/**
 * \name Broadcast Encryption Code Size
 * \{
 * \brief This section defines the Broadcast Code Encryption Size.
 * As defined in BAP Specification.
 */

/** Size of Broadcast code for encryption */
#define GA_BROADCAST_CODE_SIZE                      BAP_BC_CODE_SIZE

/** \} */
/** \} */
/** \} */

/**
 * \addtogroup ga_bap_bc_source_def
 * \{
 */

/**
 * \defgroup ga_bap_bc_source_constants Constants
 * \{
 * \brief This section describes the various Constants in EtherMind
 * GA BAP Layer for BC Source.
 */

/**
 * \name Broadcast Profile Types
 * \{
 * \brief This section defines the different Broadcast profile types
 * based on the adopted Broadcast profile specifiations
 */

/** No Broadcast Profile */
#define GA_BCAST_SIG_PROFILE_NONE                   0U

/** Public Broadcast Profile */
#define GA_BCAST_SIG_PROFILE_PUBLIC_BROADCAST       1U

/** \} */
/** \} */
/** \} */

/** \} */
/** \} */

/**
 * \addtogroup ga_bap_uc_module
 * \{
 */

/**
 * \addtogroup ga_bap_uc_defines
 * \{
 */

/**
 * \addtogroup ga_bap_uc_client_server_ascs_def
 * \{
 */

/**
 * \addtogroup ga_bap_uc_client_server_ascs_constants
 * \{
 */

/**
 * \name ASE CP Response Codes
 * \{
 * \brief This section lists the response codes for use
 * by the module. As defined in ASCS Specification.
 */

/**
 * ASE CP Response codes: The server has successfully completed the
 * client-initiated ASE Control operation.
 */
#define GA_SEP_RSP_SUCCESS                      0x00
/**
 * ASE CP Response codes: The server does not support the client-initiated
 * ASE Control operation defined by the opcode written by the client.
 */
#define GA_SEP_RSP_UNSUPP_OPCODE                0x01U
/**
 * ASE CP Response codes: The server has detected an invalid length operation
 * written by the client.
 */
#define GA_SEP_RSP_INVALID_LENGTH               0x02U
/**
 * ASE CP Response codes: The server has detected that an ASE_ID written by
 * the client does not match an ASE_ID in an exposed ASE characteristic value
 * for that client.
 */
#define GA_SEP_RSP_INVALID_ASEID                0x03U
/**
 * ASE CP Response codes: The server has detected that the client-initiated
 * ASE Control operation would cause an invalid ASE state machine transition.
 */
#define GA_SEP_RSP_INVALID_ASE_SM_TRANSITION    0x04U
/**
 * ASE CP Response codes: The server has detected that the client-initiated
 * ASE Control operation is not valid for the ASE direction.
 */
#define GA_SEP_RSP_INVALID_ASE_DIRECTION        0x05U
/**
 * ASE CP Response codes: The server has detected that the audio capabilities
 * requested during a Config Codec operation are not supported
 * (i.e., the server has not exposed the requested configuration in any PAC
 * record).
 */
#define GA_SEP_RSP_UNSUPP_AUDIO_CAPABILITIES    0x06U
/**
 * ASE CP Response codes: The server has detected that it does not support one
 * or more configuration parameter values written by the client. Shall not be
 * used when the Reason value is 0x04(Framing).
 * Refer \ref ga_bap_uc_client_server_ascs_constants for reason codes.
 */
#define GA_SEP_RSP_UNSUPP_CONFIG_PARAM_VAL      0x07U
/**
 * ASE CP Response codes: The server has rejected one or more configuration
 * parameter values written by the client.
 * Refer \ref ga_bap_uc_client_server_ascs_constants for reason codes.
 */
#define GA_SEP_RSP_REJECTED_CONFIG_PARAM_VAL    0x08U
/**
 * ASE CP Response codes: The server has detected one or more invalid
 * configuration parameter values written by the client.
 * Refer \ref ga_bap_uc_client_server_ascs_constants for reason codes.
 */
#define GA_SEP_RSP_INVALID_CONFIG_PARAM_VAL     0x09U
/**
 * ASE CP Response codes: The server has detected an unsupported Metadata
 * Type written by the client.
 */
#define GA_SEP_RSP_UNSUPP_METADATA              0x0AU
/**
 * ASE CP Response codes: The server has rejected a Metadata Type written
 * by the client.
 */
#define GA_SEP_RSP_REJECTED_METADATA            0x0BU
/**
 * ASE CP Response codes: This Response_Code is used to inform the client
 * that the Metadata Value is incorrectly formatted.
 */
#define GA_SEP_RSP_INVALID_METADATA             0x0CU
/**
 * ASE CP Response codes: The server is unable to successfully complete the
 * client-initiated ASE Control operation because of insufficient resources.
 */
#define GA_SEP_RSP_INSUFFICIENT_RESOURCES       0x0DU
/**
 * ASE CP Response codes: The server has encountered an unspecified error.
 */
#define GA_SEP_RSP_UNSPECIFIED_ERROR            0x0EU

/** \} */

/**
 * \name ASE CP Response Reason Codes
 * \{
 * \brief This section lists the reason codes for use
 * by the module. As defined in ASCS Specification.
 * ASE CP Reason codes: Used for only below ASE CP Response Codes.
 * \ref GA_SEP_RSP_UNSUPP_CONFIG_PARAM_VAL
 * \ref GA_SEP_RSP_REJECTED_CONFIG_PARAM_VAL
 * \ref GA_SEP_RSP_INVALID_CONFIG_PARAM_VAL
 */

/** ASE CP Response Reason codes: None */
#define GA_SEP_RSP_RSN_NONE                         0x00U
/** ASE CP Response Reason codes: Codec_ID */
#define GA_SEP_RSP_RSN_CODEC_ID                     0x01U
/** ASE CP Response Reason codes: Codec_Specific_Configuration */
#define GA_SEP_RSP_RSN_CODEC_SPECIFIC_CONFIG        0x02U
/** ASE CP Response Reason codes: SDU_Interval */
#define GA_SEP_RSP_RSN_SDU_INTERVAL                 0x03U
/** ASE CP Response Reason codes: Framing */
#define GA_SEP_RSP_RSN_FRAMING                      0x04U
/** ASE CP Response Reason codes: PHY */
#define GA_SEP_RSP_RSN_PHY                          0x05U
/** ASE CP Response Reason codes: Maximum_SDU_Size */
#define GA_SEP_RSP_RSN_MAX_SDU_SIZE                 0x06U
/** ASE CP Response Reason codes: Retransmission_Number */
#define GA_SEP_RSP_RSN_RETRANSMISSION_NUMBER        0x07U
/** ASE CP Response Reason codes: Max_Transport_Latency */
#define GA_SEP_RSP_RSN_MAX_TRANSPORT_LATENCY        0x08U
/** ASE CP Response Reason codes: Presentation_Delay */
#define GA_SEP_RSP_RSN_PRESENTATION_DELAY           0x09U
/** ASE CP Response Reason codes: Invalid_ASE_CIS_Mapping */
#define GA_SEP_RSP_RSN_INVALID_ASE_CIS_MAPPING      0x0AU

/** \} */

/**
 * \name ASE State
 * \{
 * \brief This section lists the ASE STates for use
 * by the module. As defined in ASCS Specification.
 * Represented as \ref GA_ASE_STATE
 */

/**
 * ASE State: Idle \n
 * The ASE has no codec configuration or QoS configuration applied
 */
#define GA_ASE_STATE_IDLE                           SEP_STATE_IDLE

/**
 * ASE State: Codec Configured \n
 * The ASE has a codec configuration applied. The codec configuration may
 * have been autonomously applied by the server or it may have been requested
 * by the client. The server is exposing its preferred QoS parameters;
 * however, the ASE has no QoS configuration applied yet.
 */
#define GA_ASE_STATE_CODEC_CONF                     SEP_STATE_CODEC_CONFIGURED

/**
 * ASE State: QoS Configured  \n
 * The ASE has a codec configuration and a QoS configuration applied.
 * The applied QoS configuration at the host level may be different from the
 * actual configuration applied to a CIS by the client controller.
 * A CIS can exist, but the ASE has not been coupled to the CIS.
 */
#define GA_ASE_STATE_QOS_CONF                       SEP_STATE_QOS_CONFIGURED

/**
 * ASE State: Enabling \n
 * The ASE has a codec configuration and a QoS configuration applied and
 * any Metadata applied by the client or server is associated with the ASE.
 * A CIS can exist, but the ASE has not been coupled to the CIS.
 * There is a risk of some lost audio data packets in this state if either
 * server or client begin transmitting audio data before the ASE is
 * in the Streaming state.
 */
#define GA_ASE_STATE_ENABLING                       SEP_STATE_ENABLING

/**
 * ASE State: Streaming \n
 * The ASE has a codec configuration and a QoS configuration applied,
 * and any Metadata applied by the client or server is associated
 * with the ASE. The ASE is coupled to a CIS. The device acting as Audio Sink
 * has initiated a Receiver Start Ready operation that has successfully
 * completed and the ASE is ready to receive or transmit audio data.
 */
#define GA_ASE_STATE_STREAMING                      SEP_STATE_STREAMING

/**
 * ASE State: Disabling \n
 * Applies only to Source ASE. The ASE has a codec configuration and a QoS
 * configuration applied. Any CIS established to transport audio data for
 * the ASE might remain established or might be disconnected however the ASE
 * is being decoupled from the CIS. Any Metadata previously applied remains
 * associated with the ASE in this state. The ASE remains ready to transmit
 * audio data until the device acting as Audio Sink has initiated a
 * Receiver Stop Ready operation that has successfully completed.
 */
#define GA_ASE_STATE_DISABLING                      SEP_STATE_DISABLING

/**
 * ASE State: Releasing \n
 * Any CIS established to transport audio data for the ASE is being
 * disconnected or has been disconnected. Any previously applied codec
 * configuration may be cached by the server, or the server may cache a codec
 * configuration of the server's choosing, or the codec configuration
 * may be removed. Any previously applied QoS configuration is no longer
 * valid. Any Metadata previously applied is no longer associated with the ASE.
 */
#define GA_ASE_STATE_RELEASING                      SEP_STATE_RELEASING

/** \} */

/** \} */
/** \} */
/** \} */
/** \} */
/** \} */

/**
 * \addtogroup ga_csip_module
 * \{
 */

/**
 * \addtogroup ga_csip_defines
 * \{
 */

/**
 * \defgroup ga_csip_constants Constants
 * \{
 * \brief This section describes the various Constants in EtherMind
 * GA CSIP Layer.
 */

/** \} */

/**
 * \defgroup ga_csip_error_code Error Codes
 * \{
 * \brief This sections describes the Error Codes exposed and used
 * by the EtherMind GA CSIP Layer.
 */

/**
 * \name CSIP - Application Error Codes
 * \{
 * \brief This section lists Application error codes,
 * As defined in CSIS Specification.
 */

/** The lock cannot be granted because the server is already locked. */
#define GA_CSIS_ERR_LOCK_DENIED                     CSIS_ERR_LOCK_DENIED

/**
 * The lock cannot be released because another
 * client has locked the Coordinated Set.
 */
#define GA_CSIS_ERR_LOCK_RELEASE_NOT_ALLOWED        CSIS_ERR_LOCK_RELEASE_NOT_ALLOWED

/**
 * The client attempts to write an RFU value to the
 * Set Member Lock characteristic value.
 */
#define GA_CSIS_ERR_INVALID_LOCK_VALUE              CSIS_ERR_INVALID_LOCK_VALUE

/**
 * The server only supports exposing the Set Identity Resolving
 * Key (SIRK) via an out-of-band (OOB) procedure.
 */
#define GA_CSIS_ERR_OOB_SIRK_ONLY                   CSIS_ERR_OOB_SIRK_ONLY

/** The client that made the request is the current owner of the lock. */
#define GA_CSIS_ERR_LOCK_ALREADY_GRANTED            CSIS_ERR_LOCK_ALREADY_GRANTED

/** \} */
/** \} */
/** \} */
/** \} */

/* --------------------------------------------- Data types /Structures */

/**
 * \addtogroup ga_vcp_module
 * \{
 */

/**
 * \addtogroup ga_vcp_defines
 * \{
 */

/**
 * \defgroup ga_vcp_structures Structures
 * \{
 * \brief This section lists the various data structures and typedefs for use
 * by the module.
 */

/** GA Volume Control Profile Context Reference for an Endpoint */
typedef UINT8 GA_VC_CONTEXT;

/** GA Volume Control Profile Renderer Reference for an Endpoint */
typedef UINT8 GA_VR_HANDLE;

/** \} */
/** \} */
/** \} */

/**
 * \addtogroup ga_micp_module
 * \{
 */

/**
 * \addtogroup ga_micp_defines
 * \{
 */

/**
 * \defgroup ga_micp_structures Structures
 * \{
 * \brief This section lists the various data structures and typedefs for use
 * by the module.
 */

/** GA Microphone Control Profile Context Reference for an Endpoint */
typedef UINT8 GA_MC_CONTEXT;

/** GA Microphone Control Device Reference for an Endpoint */
typedef UINT8 GA_MD_HANDLE;

/** \} */
/** \} */
/** \} */

/**
 * \addtogroup ga_csip_module
 * \{
 */

/**
 * \addtogroup ga_csip_defines
 * \{
 */

/**
 * \defgroup ga_csip_structures Structures
 * \{
 * \brief This section lists the various data structures and typedefs for use
 * by the module.
 */

/**
 * GA Coordinated Set Identification Profile Context Reference for an
 * Endpoint
 */
typedef UINT8 GA_CS_CONTEXT;

/** GA Coordinated Set Member Reference for an Endpoint */
typedef UINT8 GA_CM_HANDLE;

/** \} */
/** \} */
/** \} */

/**
 * \addtogroup ga_bap_module
 * \{
 */

/**
 * \addtogroup ga_bap_uc_module
 * \{
 */

/**
 * \addtogroup ga_bap_uc_defines
 * \{
 */

/**
 * \addtogroup ga_bap_uc_client_server_ascs_def
 * \{
 */

/**
 * \defgroup ga_bap_uc_client_server_ascs_structures Structures
 * \{
 * \brief This section lists the various data structures and typedefs for use
 * by UC Client and Server ASCS.
 */

/** GA ASE States */
typedef UINT8 GA_ASE_STATE;

/** GA Channel Reference */
typedef BAP_CHANNEL GA_CHANNEL;

/** GA Content Information */
typedef struct _GA_CONTENT_INFO
{
    /** Contexts for the content */
    UINT16 contexts;

    /** List of CCIDs */
    UINT8 * ccid; /* SZ:^3 */

    /** Number of CCIDs */
    UINT8 num_ccid;

} GA_CONTENT_INFO;

/** Stream End point Configuration */
typedef struct _GA_SEP_CONF
{
    /** Role */
    UINT8 role;

    /** Target Latency */
    UINT8 target_latency;

    /** Target Phy */
    UINT8 target_phy;

    /** Codec Capability */
    GA_CODEC_INFO codec;

} GA_SEP_CONF;

/** \} */
/** \} */
/** \} */
/** \} */
/** \} */

/**
 * \addtogroup ga_common_module
 * \{
 */

/**
 * \addtogroup ga_common_defines
 * \{
 */

/**
 * \addtogroup ga_common_structures
 * \{
 */

/** GA Context Reference for an Endpoint */
typedef UINT8 GA_CONTEXT;

/** \} */
/** \} */
/** \} */

/**
 * \addtogroup ga_bap_module
 * \{
 */

/**
 * \addtogroup ga_bap_common_module
 * \{
 */

/**
 * \addtogroup ga_bap_common_defines
 * \{
 */

/**
 * \addtogroup ga_bap_common_structures
 * \{
 */

/** GA LC3 Codec Specific Capability */
typedef struct _GA_LC3_CODEC_SPECIFIC_CAP
{
    /**
     * Supported Sampling Frequencies,
     * Refer \ref ga_ltv_val
     */
    UINT16 supported_sf;

    /**
     * Supported Frame Durations,
     * Refer \ref ga_ltv_val
     */
    UINT8 supported_fd;

    /**
     * Supported Audio Channel Counts,
     * Refer \ref ga_ltv_val
     */
    UINT8 supported_acc;

    /**
     * Supported Octets per Codec Frame,
     * Refer \ref ga_ltv_val
     */
    UINT32 supported_opcf;

    /**
     * Supported Max Codec Frames Per SDU,
     * Refer \ref ga_ltv_val
     */
    UINT8 supported_mcfpSDU;

} GA_LC3_CODEC_SPECIFIC_CAP;

/** GA LC3 Codec Configuration */
typedef struct _GA_LC3_CODEC_SPECIFIC_CONF
{
    /** Sampling Frequency, Refer \ref ga_ltv_val */
    UINT8 sf;

    /** Frame Duration, Refer \ref ga_ltv_val */
    UINT8 fd;

    /** Audio Channel Allocation, Refer \ref ga_ltv_val */
    UINT32 aca;

    /** Octets per Codec Frame, Refer \ref  ga_ltv_val */
    UINT16 opcf;

    /**
     * Codec Frame Blocks Per SDU,
     * Refer \ref  ga_ltv_val
     */
    UINT8 mcfpSDU;

} GA_LC3_CODEC_SPECIFIC_CONF;

/** GA Codec Configuration */
typedef struct _GA_CODEC_CONFIG
{
    /** Codec ID */
    UINT8 id;

    /** Codec Configuration */
    void * conf;

} GA_CODEC_CONFIG;

/** GA QOS Configuration */
typedef BAP_ASE_QOS_CONF GA_QOS_CONF;

/** \} */
/** \} */
/** \} */

/**
 * \addtogroup ga_bap_uc_module
 * \{
 */

/**
 * \addtogroup ga_bap_uc_defines
 * \{
 */

/**
 * \addtogroup ga_bap_uc_client_server_pacs_def
 * \{
 */

/**
 * \defgroup ga_bap_uc_client_server_pacs_structures Structures
 * \{
 * \brief This section lists the various data structures and typedefs for use
 * by UC Client and Server PACS.
 */

/** GA Supported Audio Capability */
typedef struct _GA_AUDIO_CAP
{
    /** Codec Information */
    GA_CODEC_INFO codec;

    /** Preferred Context Types for the capability */
    UINT16 pref_audio_contexts;

} GA_AUDIO_CAP;

/** GA PACS Audio Record */
typedef struct _GA_PACS_AUDIO_RECORD
{
    /**
     * Sink Audio Locations, Refer \ref ga_common_constants
     */
    UINT32 sink_audio_locations;

    /**
     * Source Audio Locations, Refer \ref ga_common_constants
     */
    UINT32 src_audio_locations;

    /**
     * Available Audio Contexts for the capability,
     * Refer \ref ga_bap_common_constants
     */
    UINT16 avail_sink_contexts;

    /**
     * Available Audio Contexts for the capability,
     * Refer \ref ga_bap_common_constants
     */
    UINT16 avail_src_contexts;

    /**
     * Supported Audio Contexts for the capability,
     * Refer \ref ga_bap_common_constants
     */
    UINT16 supp_sink_contexts;

    /**
     * Supported Audio Contexts for the capability,
     * Refer \ref ga_bap_common_constants
     */
    UINT16 supp_src_contexts;

} GA_PACS_AUDIO_RECORD;

/** \} */
/** \} */
/** \} */
/** \} */

/**
 * \addtogroup ga_bap_uc_module
 * \{
 */

/**
 * \addtogroup ga_bap_uc_defines
 * \{
 */

/**
 * \addtogroup ga_bap_uc_common_def
 * \{
 */

/**
 * \defgroup ga_bap_uc_common_structures Structures
 * \{
 * \brief This section lists the various data structures and typedefs for use
 * by UC Client and Server.
 */

/** GA QOS Capability */
typedef struct _GA_QOS_CAP
{
    /** Framing Preference */
    UINT8 pref_framing;

    /** PHY Preference */
    UINT8 pref_phy;

    /** Retransmission Number Preference */
    UINT8 pref_retxn;

    /** Max Transport Latency Preference */
    UINT16 pref_max_transport_latency;

    /** Presentation Delay supported - Minimum */
    UINT32 supp_presentation_delay_min;
    /** Presentation Delay supported - Maximum */
    UINT32 supp_presentation_delay_max;

    /** Presentation Delay preferred - Minimum */
    UINT32 pref_presentation_delay_min;
    /** Presentation Delay preferred - Maximum */
    UINT32 pref_presentation_delay_max;

} GA_QOS_CAP;

/** \} */
/** \} */

/**
 * \addtogroup ga_bap_uc_client_pacs_def
 * \{
 */

/**
 * \defgroup ga_bap_uc_client_pacs_structures Structures
 * \{
 * \brief This section lists the various data structures and typedefs for use
 * by UC Client - PACS.
 */

/** GA Endpoint Capability */
typedef struct _GA_CAP_ENDPOINT
{
    /**
     * Capability data:
     * If \ref GA_CAP_TYPE_CODECS
     *     data: Pointer to data with First byte indicating Number of PACS Records,
     *           followed by \ref GA_CODEC_INFO followed by \ref GA_METADATA.
     *           Refer \ref ga_bap_common_constants
     *     data[0] -> No of PAC Records followed by params as above.
     *
     * If \ref GA_CAP_TYPE_LOCATIONS,
     *     data: Pointer to \ref UINT32, Represents Audio Location values as
     *           bitmask.
     *           Refer \ref ga_common_constants
     *
     * If \ref GA_CAP_TYPE_SUPP_CONTEXTS
     *     data: Pointer to \ref UINT16, Represents Supported Context values
     *           as bitmask.
     *           Refer \ref ga_bap_common_constants
     *
     * If \ref GA_CAP_TYPE_AVAIL_CONTEXTS,
     *     data: Pointer to \ref UINT16, Represents Supported Context values
     *           as bitmask.
     *           Refer \ref ga_bap_common_constants
     */
    UCHAR * data; /* SZ:^2 */

    /**
     * Capability data length:
     * If \ref GA_CAP_TYPE_CODECS
     *     datalen: Length of the data above.
     *
     * If \ref GA_CAP_TYPE_LOCATIONS,
     *     datalen: \ref sizeof ( \ref UINT32 )
     *
     * If \ref GA_CAP_TYPE_SUPP_CONTEXTS,
     *     datalen: \ref sizeof ( \ref UINT16 )
     *
     * If \ref GA_CAP_TYPE_AVAIL_CONTEXTS,
     *     datalen: \ref sizeof ( \ref UINT16 )
     */
    UINT16 datalen;

    /** Peer role under consideration, Refer \ref ga_bap_uc_common_constants */
    UINT8 role;

    /** Capability type, Refer \ref ga_bap_uc_client_server_pacs_constants */
    UINT8 type;

    /** Capability Record ID, Valid only for type \ref GA_CAP_TYPE_CODECS */
    UINT8 record_id;

} GA_CAP_ENDPOINT;

/** \} */
/** \} */

/**
 * \addtogroup ga_bap_uc_client_ascs_def
 * \{
 */

/**
 * \defgroup ga_bap_uc_client_ascs_structures Structures
 * \{
 * \brief This section lists the various data structures and typedefs for use
 * by UC Client - ASCS.
 */

/** ASE Information */
typedef struct _GA_ASE_INFO
{
    /** ASE Info data */
    UCHAR * data; /* SZ:^2 */

    /** ASE Infor datalen */
    UINT16 datalen;

    /** ASE Index */
    UINT8 sep_id;

    /** ASE Role of the Remote */
    UINT8 ase_role;

} GA_ASE_INFO;

/** ASE Format referenced in \ref GA_SEP_DISCOVER_CNF */
typedef struct _GA_ASE_INFO_IN_IDLE
{
    /** ASE ID */
    UINT8 ase_id;

    /** ASE State, Ref \ref GA_ASE_STATE */
    UINT8 ase_state;
} GA_ASE_INFO_IN_IDLE;

/** ASE Format referenced in \ref GA_SEP_CONFIGURE_CNF */
typedef struct _GA_ASE_INFO_IN_CODEC_CONF
{
    /** ASE ID */
    UINT8 ase_id;

    /** ASE State, Ref \ref GA_ASE_STATE */
    UINT8 ase_state;

    /** QoS Codec Capabilities of the peer ASE */
    GA_QOS_CAP qos_cap;

    /** Codec Info of the peer ASE */
    GA_CODEC_INFO codec_info;
} GA_ASE_INFO_IN_CODEC_CONF;

/** ASE Format referenced in \ref GA_SEP_SETUP_CNF */
typedef struct _GA_ASE_INFO_IN_QOS_CONF
{
    /** ASE ID */
    UINT8 ase_id;

    /** ASE State, Ref \ref GA_ASE_STATE */
    UINT8 ase_state;

    /** QoS Configuration post config with the peer ASE */
    GA_QOS_CONF qos_cfg;
} GA_ASE_INFO_IN_QOS_CONF;

/**
 * ASE Format referenced in \ref GA_SEP_START_CNF, \ref GA_SEP_SUSPEND_CNF,
 * \ref GA_SEP_UPDATE_CNF
 */
typedef struct _GA_ASE_INFO_IN_ENABLING_STREAMING_DISABLING
{
    /** ASE ID */
    UINT8 ase_id;

    /** ASE State, Ref \ref GA_ASE_STATE */
    UINT8 ase_state;

    /** Channel Information */
    GA_CHANNEL channel;

    /** Metadata Total Length */
    UINT8 metadata_length;

    /** LTV Formatted Metadata */
    UINT8* metadata; /* SZ:^4 */

} GA_ASE_INFO_IN_ENABLING_STREAMING_DISABLING;

/** GA Stream Context information */
typedef struct _GA_STREAM_CONTEXT
{
    /** Stream endpoint ID */
    UINT8 sep_id;

    /** ASE ID */
    UINT8 ase_id;

    /** ASE state */
    UINT8 ase_state;

} GA_STREAM_CONTEXT;

/** \} */
/** \} */

/**
 * \addtogroup ga_bap_uc_server_ascs_def
 * \{
 */

/**
 * \defgroup ga_bap_uc_server_ascs_structures Structures
 * \{
 * \brief This section lists the various data structures and typedefs for use
 * by UC Server - ASCS.
 */

/** SEP Callback Information */
typedef struct _GA_SEP_INFO
{
    /** Event specific information */
    void * info;

    /** SEP Id */
    UINT8 sep_id;

} GA_SEP_INFO;

/** \} */
/** \} */
/** \} */
/** \} */
/** \} */

/**
 * \addtogroup ga_cas_module
 * \{
 */

/**
 * \addtogroup ga_cas_defines
 * \{
 */

/**
 * \defgroup ga_cas_structures Structures
 * \{
 * \brief This section lists the various data structures and typedefs for use
 * by CAS.
 */

/** GA Set Member parameters */
typedef struct _GA_SET_MEMBER
{
    /** Set SIRK, 1 octet type + 16 octet value */
    UCHAR sirk[1U + CSIP_SIRK_LEN];

    /** Set Size */
    UINT8 size;

    /** Set Member Rank */
    UINT8 rank;

    /** Set Member Lock */
    UINT8 lock;

} GA_SET_MEMBER;

/** \} */
/** \} */
/** \} */

/**
 * \addtogroup ga_common_module
 * \{
 */

/**
 * \addtogroup ga_common_cb
 * \{
 */

/**
 * \brief GA Profile Callback
 *
 * \param [in] ga_ep      Peer Device Info
 * \param [in] ga_event   Event type
 * \param [in] ga_status  Event status
 * \param [in] ga_data    Event Data
 * \param [in] ga_datalen Event Data Length
 */
typedef GA_RESULT (* GA_PROFILE_CB)
                  (
                      /* IN */ GA_ENDPOINT* ga_ep,
                      /* IN */ UINT8 ga_event,
                      /* IN */ UINT16 ga_status,
                      /* IN:^5 */ void * ga_data,
                      /* IN: */ UINT16 ga_datalen
                  );

/** \} */
/** \} */

/* --------------------------------------------- Macros */

/* --------------------------------------------- APIs */

/**
 * \addtogroup ga_bap_module
 * \{
 */

/**
 * \addtogroup ga_bap_uc_module
 * \{
 */

/**
 * \addtogroup ga_bap_uc_api_sequences
 * \{
 */

/**
 * \defgroup ga_bap_uc_ase_state_machine ASE State Machine
 * \{
 * \brief This section describes the BAP Unicast ASE state machine. \n
 * As defined in ASCS Specification.
 *
 * \page ase_src_state_machine ASE Source State Machine
 * \image html ASE_Source_State_Machine.png
 *
 * \page ase_snk_state_machine ASE Sink State Machine
 * \image html ASE_Sink_State_Machine.png
 */

/** \} */

/**
 * \defgroup ga_bap_uc_api_seq API Sequences
 * \{
 * \brief This section describes the BAP Unicast API Sequences.
 * MSC depicting the flow of APIs and Events.
 *
 * \page unidirectional_cis Unidirectional CIS
 * \mscfile BAP_Unidirectional_CIS.signalling
 *
 * \page bidirectional_cis Bidirectional CIS
 * \mscfile BAP_Bidirectional_CIS.signalling
 */

/** \} */
/** \} */
/** \} */

/**
 * \addtogroup ga_bap_bc_module
 * \{
 */

/**
 * \addtogroup ga_bap_bc_api_sequences
 * \{
 */

/**
 * \defgroup ga_bap_bc_api_seq API Sequences
 * \{
 * \brief This section describes the BAP Broadcast API Sequences.
 * MSC depicting the flow of APIs and Events.
 *
 * \page bass_collc_src_with_past BASS Collocated Source(PAST Available)
 * \mscfile BASS_Collocated_PAST_Available.signalling
 *
 * \page bass_collc_src_without_past BASS Collocated Source(PAST Not Available)
 * \mscfile BASS_Collocated_PAST_Not_Available.signalling
 *
 * \page bass_non_collc_src_with_past BASS Non-Collocated Source(PAST Available)
 * \mscfile BASS_NonCollocated_PAST_Available.signalling
 *
 * \page bass_non_collc_src_without_past BASS Non-Collocated Source(PAST Not Available)
 * \mscfile BASS_NonCollocated_PAST_Not_Available.signalling
 */

/** \} */
/** \} */
/** \} */

/** \} */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup ga_common_module
 * \{
 */

/**
 * \addtogroup ga_common_api_defs
 * \{
 */

/**
 * \name Common APIs - Init
 * \{
 * \brief This section describes the Generic Audio Common Init APIs.
 */

/**
 *  \brief Initialize the Generic Audio (GA) layer.
 *
 *  \par Description:
 *       This routine initializes the GA layer.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 */
GA_RESULT GA_init(void);

/**
 *  \brief Register GA application callback
 *
 *  \par Description:
 *       This routine registers the application callback with GA to deliver
 *       CAP and other generic events. This is the common callback for both
 *       CAP Client and CAP Server.
 *
 *  \param [in] cb Application callback of type \ref GA_PROFILE_CB.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 */
GA_RESULT GA_register_callback
          (
              /* IN */ GA_PROFILE_CB cb
          ); /* EXCLUDE */

#ifdef GA_HAVE_DYNAMIC_CONFIG
/**
 *  \brief Setup the configuration of the Generic Audio (GA) layer.
 *
 *  \par Description:
 *       This routine initializes the default configuration for
 *       the GA components.
 *
 *  \param [in] config Configuration for GA.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 */
GA_RESULT GA_configure
          (
              /* IN */ GA_CONFIG * config
          );
#endif /* GA_HAVE_DYNAMIC_CONFIG */

/**
 *  \brief Prepare the roles for Generic Audio (GA) CAP layer.
 *
 *  \par Description:
 *       This routine sets the role requirements of the application at the
 *       GA CAP layer. In case of support for Acceptor role, the application
 *       can also specify if it is a member of a Coordinated set with the
 *       parameters in \ref GA_SET_MEMBER.
 *
 *  \param [in] role Bitmask of CAP roles to be supported.
 *  \param [in] member Member information of type \ref GA_SET_MEMBER if
 *                     Acceptor is part of a Coordinated Set, otherwise NULL.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 */
GA_RESULT GA_prepare
          (
              /* IN */ UINT8 role,
              /* IN */ GA_SET_MEMBER * member
          );

/** \} */

/**
 * \name Common APIs - De-Init
 * \{
 * \brief This section describes the Generic Audio Common De-Init APIs.
 */

/**
 *  \brief Shutdown the Generic Audio (GA) layer.
 *
 *  \par Description:
 *       This routine shuts down the GA layer and cleans up all data.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 */
GA_RESULT GA_shutdown(void);

/** \} */

/**
 * \name Common APIs - Init
 * \{
 */

/**
 *  \brief Initialize the GA core module specified for the role.
 *
 *  \par Description:
 *       This routine initializes the given GA core module for the specified
 *       role, and saves the application callback provided.
 *
 *  \param [in] id GA Module ID.
 *  \param [in] role GA Specific role for the module.
 *  \param [in] cb Application profile callback of type \ref GA_PROFILE_CB.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 */
GA_RESULT GA_module_init
          (
              /* IN */ UINT8 id,
              /* IN */ UINT8 role,
              /* IN */ GA_PROFILE_CB cb
          );

/** \} */

/**
 * \name Common APIs - De-Init
 * \{
 */

/**
 *  \brief Shutdown the GA core module specified for the role.
 *
 *  \par Description:
 *       This routine shuts down the given GA core module for the specified
 *       role.
 *
 *  \param [in] id GA Module ID.
 *  \param [in] role GA Specific role for the module.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 */
GA_RESULT GA_module_shutdown
          (
              /* IN */ UINT8 id,
              /* IN */ UINT8 role
          );

/** \} */

/** \} */
/** \} */

/**
 * \addtogroup ga_bap_module
 * \{
 */

/**
 * \addtogroup ga_bap_uc_module
 * \{
 */

/**
 * \addtogroup ga_bap_uc_api_defs
 * \{
 */

#ifdef BAP_PACS_SERVER
/**
 * \defgroup ga_bap_server_api_defs BAP Server
 * \{
 * \brief This section describes the various APIs for UC Server.
 */

/**
 * \name BAP Server APIs - Init
 * \{
 * \brief This section describes the Generic Audio Init APIs for BAP Server.
 */

/**
 *  \brief Initialize the GA BAP PAC Server.
 *
 *  \par Description:
 *       This routine initializes GA BAP PAC Server.
 *
 *  \param [in] cb Application profile callback of type \ref GA_PROFILE_CB.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_bap_common_error_code
 */
#define GA_bap_server_init(                                  \
            /* IN - GA_PROFILE_CB */ cb                      \
        )                                                    \
        GA_module_init                                       \
        (                                                    \
            GA_MODULE_BAP,                                   \
            BAP_ROLE_SERVER,                                 \
            (cb)                                             \
        )

/** \} */

/**
 * \name BAP Server APIs - De-Init
 * \{
 * \brief This section describes the Generic Audio De-Init APIs for BAP Server.
 */

/**
 *  \brief Shutdown the GA BAP PAC Server.
 *
 *  \par Description:
 *       This routine shuts down GA BAP PAC Server. If there is an active
 *       Unicast and/or Broadcast[with SD role] ongoing, this function
 *       will return a failure.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_bap_common_error_code
 */
#define GA_bap_server_shutdown()                             \
        GA_module_shutdown                                   \
        (                                                    \
            GA_MODULE_BAP,                                   \
            BAP_ROLE_SERVER                                  \
        )

/** \} */
/** \} */

/**
 * \defgroup ga_bap_uc_server_pacs_api_defs UC Server - PACS
 * \{
 * \brief This section describes the various APIs for UC Server - PACS.
 */

/**
 * \name UC Server PACS APIs - Setup
 * \{
 * \brief This section describes the Generic Audio Setup APIs for Server PACS.
 */

/**
 *  \brief Register the GA capabilities.
 *
 *  \par Description:
 *       This routine registers the audio capabilities of the application
 *       profile residing over the GA layer.
 *
 *  \param [in] role \ref GA_ROLE_SOURCE or \ref GA_ROLE_SINK role for this
 *                   capability.
 *  \param [in] cap_count Count of capabilitites supported for this role.
 *  \param [in] audio_cap Reference to \ref GA_AUDIO_CAP data giving the audio
 *                        capability for this role.
 *  \param[out] record_id Record ID of the registered capabilities.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_bap_common_error_code
 */
GA_RESULT GA_register_audio_capabilities
          (
              /* IN */    UINT8 role,
              /* IN */    UINT8 cap_count,
              /* IN:^2 */ GA_AUDIO_CAP * audio_cap,
              /* OUT */   UINT8* record_id
          );

/**
 *  \brief Register the GA Audio Contexts and Locations.
 *
 *  \par Description:
 *       This routine registers the audio capabilities of the application
 *       profile residing over the GA layer.
 *
 *  \param [in] role \ref GA_ROLE_SOURCE or \ref GA_ROLE_SINK role for this
 *                   capability.
 *
 *  \param [in] aac Available Audio contexts for this role.
 *                  Represented as Bitmask field.
 *                  \ref ga_bap_common_constants.
 *
 *  \param [in] sac Supported Audio contexts for this role.
 *                  Represented as Bitmask field.
 *                  \ref ga_bap_common_constants.
 *
 *  \param [in] loc Locations for this role.
 *                  Represented as Bitmask field.
 *                  \ref ga_common_constants.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \note This API will append the 'Unspecified Audio Context' type to
 *        the capabilities bitmask of the Supported Audio Contexts as
 *        mandated by the specification
 *
 *  \sa ga_bap_common_error_code
 */
#define GA_register_audio_contexts_and_locations(                              \
            /* IN - UINT8 */  role,                                            \
            /* IN - UINT16 */ aac,                                             \
            /* IN - UINT16 */ sac,                                             \
            /* IN - UINT32 */ loc                                              \
        )                                                                      \
        BAP_register_audio_contexts_and_locations                              \
        (                                                                      \
            (role),                                                            \
            (aac),                                                             \
            (sac),                                                             \
            (loc)                                                              \
        )

/** \} */
/** \} */
#endif /* BAP_PACS_SERVER */

#ifdef BAP_UCS
/**
 * \defgroup ga_bap_uc_server_ascs_api_defs UC Server - ASCS
 * \{
 * \brief This section describes the various APIs for UC Server - ASCS.
 */

/**
 * \name UC Server ASCS APIs - BAP Procedures
 * \{
 * \brief This section describes the Generic Audio BAP Procedures
 * APIs for Unicast Server ASCS.
 */

/**
 *  \brief Initialize the Unicast Server.
 *
 *  \par Description:
 *       This routine initializes Unicast Server.
 *       Ensure to call GA_bap_server_init() this routine to initialize
 *       the BAP server module before invoking this API, else this will
 *       return a failure.
 *
 *  \param [in] cb Application profile callback of type \ref GA_PROFILE_CB.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_bap_common_error_code
 */
#define GA_uc_server_init(                                  \
            /* IN - GA_PROFILE_CB */ cb                     \
        )                                                   \
        GA_module_init                                       \
        (                                                    \
            GA_MODULE_BAP,                                   \
            BAP_ROLE_UCS,                                    \
            (cb)                                             \
        )

/**
 *  \brief Shutdown the Unicast Server.
 *
 *  \par Description:
 *       This routine shuts down Unicast Server.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_bap_common_error_code
 */
#define GA_uc_server_shutdown()                              \
        GA_module_shutdown                                   \
        (                                                    \
            GA_MODULE_BAP,                                   \
            BAP_ROLE_UCS                                     \
        )
/**
 *  \brief Register GA Streaming Endpoint.
 *
 *  \par Description:
 *       This routine registers a GA streaming endpoint for a given SEP
 *       configuration and QOS capability.
 *
 *  \param [in] role Role for the SEP.
 *  \param [in] codec Codec configuration for the SEP.
 *  \param [in] qos_cap Preferred QOS capability for the SEP,
 *  \param [out] ase_id Endpoint identifier for future reference on successful
 *                      registration.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_bap_common_error_code
 */
GA_RESULT GA_register_audio_sep
          (
              /* IN */ UINT8 role,
              /* IN */ GA_CODEC_INFO * codec,
              /* IN */ GA_QOS_CAP * qos_cap,
              /* OUT */ UINT8 * ase_id
          );

/**
 *  \brief Update QOS Capabilities of GA Streaming Endpoint.
 *
 *  \par Description:
 *       This routine updates the QOS capabilities registered with
 *       a GA streaming endpoint.
 *
 *  \param [in] ase_id Endpoint identifier.
 *  \param [in] qos_cap Preferred QOS capability for the SEP.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_bap_common_error_code
 */
GA_RESULT GA_update_audio_sep_qos_capabilities
          (
              /* IN */ UINT8 ase_id,
              /* IN */ GA_QOS_CAP * qos_cap
          );

/**
 *  \brief Send Auto configure for a given set of ASEs of a device.
 *
 *  \par Description:
 *       This routine transitins the ASE state to Codec Configured state.
 *
 *  \param [in] device Peer Endpoint address.
 *  \param [in] ase_count Number of Endpoints included.
 *  \param [in] ase_index List of ASE IDs.
 *  \param [in] codec_info Codec Info of ASE IDs.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_bap_common_error_code
 */
GA_RESULT GA_notify_ase_configure
          (
              /* IN */    GA_ENDPOINT* device,
              /* IN */    UINT8 ase_count,
              /* IN:^2 */ UINT8* ase_index,
              /* IN:^2 */ GA_CODEC_INFO * codec_info
          );

/**
 *  \brief Send Auto ASE Receiver Ready when local Server is a Sink ASE.
 *
 *  \par Description:
 *       This routine is to be called once the CIS is established with the
 *       remote Src ASE and when the Local Sink is ready for receiving
 *       Audio data.
 *
 *  \param [in] device Peer Endpoint address.
 *  \param [in] ase_count Number of Endpoints included.
 *  \param [in] ase_index List of ASE IDs.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_bap_common_error_code
 */
GA_RESULT GA_notify_ase_receiver_start_ready
          (
              /* IN */    GA_ENDPOINT * device,
              /* IN */    UINT8 ase_count,
              /* IN:^2 */ UINT8* ase_index
          );

/**
 *  \brief Suspend a given set of ASEs of a GA endpoint.
 *
 *  \par Description:
 *       This routine disables the given set of one or more ASE IDs of
 *       the GA Endpoint.
 *
 *  \param [in] device Peer Endpoint address.
 *  \param [in] ase_count Number of Endpoints included.
 *  \param [in] ase_index List of ASE IDs.
 *  \param [in] reason Reason for suspend \ref ga_cas_constants
 *                     GA Suspend Reason Type.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_bap_common_error_code
 */
GA_RESULT GA_notify_ase_suspend_with_reason
          (
              /* IN */    GA_ENDPOINT* device,
              /* IN */    UINT8 ase_count,
              /* IN:^2 */ UINT8* ase_index,
              /* IN */    UINT8  reason
          );

/**
 *  \brief Suspend a given set of ASEs of a GA endpoint due to CIS Loss.
 *
 *  \par Description:
 *       This routine disables the given set of one or more ASE IDs of
 *       the GA Endpoint whenever CIS Disconnection is detected.
 *
 *  \param [in] device Peer Endpoint address.
 *  \param [in] ase_count Number of Endpoints included.
 *  \param [in] ase_index List of ASE IDs.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_bap_common_error_code
 */
#define GA_notify_ase_suspend_on_CIS_loss(                                     \
            /* IN - GA_ENDPOINT* */ device,                                    \
            /* IN - UINT8 */ ase_count,                                        \
            /* IN:^2 - UINT8* */ ase_index                                     \
        )                                                                      \
        GA_notify_ase_suspend_with_reason                                      \
        (                                                                      \
            (device),                                                          \
            (ase_count),                                                       \
            (ase_index),                                                       \
            GA_ASE_SUSPEND_RELEASE_REASON_CIS_LOSS                             \
        )

/**
 *  \brief Suspend a given set of ASEs of a GA endpoint.
 *
 *  \par Description:
 *       This routine disables the given set of one or more ASE IDs of
 *       the GA Endpoint. This routine is called for ASE Control Point for
 *       Auto Disable.
 *
 *  \param [in] device Peer Endpoint address.
 *  \param [in] ase_count Number of Endpoints included.
 *  \param [in] ase_index List of ASE IDs.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_bap_common_error_code
 */
#define GA_notify_ase_suspend(                                                 \
            /* IN - GA_ENDPOINT* */ device,                                    \
            /* IN - UINT8 */ ase_count,                                        \
            /* IN:^2 - UINT8* */ ase_index                                     \
        )                                                                      \
        GA_notify_ase_suspend_with_reason                                      \
        (                                                                      \
            (device),                                                          \
            (ase_count),                                                       \
            (ase_index),                                                       \
            GA_ASE_SUSPEND_RELEASE_REASON_NONE                                 \
        )

/**
 *  \brief Update a given set of ASEs of a GA endpoint.
 *
 *  \par Description:
 *       This routine updates the given set of one or more ASE IDs of
 *       the GA Endpoint with new set of Content Control Information.
 *
 *  \param [in] device Peer Endpoint address.
 *  \param [in] ase_count Number of Endpoints included.
 *  \param [in] ase_index List of ASE IDs.
 *  \param [in] ase_content List of Content Control information for
 *                          every endpoint included.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_bap_common_error_code
 */
GA_RESULT GA_notify_ase_update
          (
              /* IN */    GA_ENDPOINT* device,
              /* IN */    UINT8 ase_count,
              /* IN:^2 */ UINT8* ase_index,
              /* IN:^2 */ GA_CONTENT_INFO* ase_content
          );

/**
 *  \brief Release a given set of ASEs of a GA endpoint.
 *
 *  \par Description:
 *       This routine indicates the release on the given set of one or more
 *       ASE IDs of the GA Endpoint.
 *
 *  \param [in] device Peer Endpoint address.
 *  \param [in] ase_count Number of Endpoints included.
 *  \param [in] ase_index List of ASE IDs.
 *  \param [in] reason Reason for suspend \ref ga_cas_constants
 *                     GA Suspend/Release Reason Type.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_bap_common_error_code
 */
GA_RESULT GA_notify_ase_release_with_reason
          (
              /* IN */    GA_ENDPOINT* device,
              /* IN */    UINT8 ase_count,
              /* IN:^2 */ UINT8* ase_index,
              /* IN */    UINT8  reason
          );

/**
 *  \brief Release a given set of ASEs of a GA endpoint due to CIS Loss.
 *
 *  \par Description:
 *       This routine indicates the release on the given set of one or more
 *       ASE IDs to the GA Endpoint whenever CIS Disconnection is detected.
 *
 *  \param [in] device Peer Endpoint address.
 *  \param [in] ase_count Number of Endpoints included.
 *  \param [in] ase_index List of ASE IDs.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_bap_common_error_code
 */
#define GA_notify_ase_release_on_CIS_loss(                                     \
            /* IN - GA_ENDPOINT* */ device,                                    \
            /* IN - UINT8 */ ase_count,                                        \
            /* IN:^2 - UINT8* */ ase_index                                     \
        )                                                                      \
        GA_notify_ase_release_with_reason                                      \
        (                                                                      \
            (device),                                                          \
            (ase_count),                                                       \
            (ase_index),                                                       \
            GA_ASE_SUSPEND_RELEASE_REASON_CIS_LOSS                             \
        )

/**
 *  \brief Release a given set of ASEs of a GA endpoint.
 *
 *  \par Description:
 *       This routine indicates the release on the given set of one or
 *       more ASE IDs to the GA Endpoint.
 *
 *  \param [in] device Peer Endpoint address.
 *  \param [in] ase_count Number of Endpoints included.
 *  \param [in] ase_index List of ASE IDs.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_bap_common_error_code
 */
#define GA_notify_ase_release(                                                 \
            /* IN - GA_ENDPOINT* */ device,                                    \
            /* IN - UINT8 */ ase_count,                                        \
            /* IN:^2 - UINT8* */ ase_index                                     \
        )                                                                      \
        GA_notify_ase_release_with_reason                                      \
        (                                                                      \
            (device),                                                          \
            (ase_count),                                                       \
            (ase_index),                                                       \
            GA_ASE_SUSPEND_RELEASE_REASON_NONE                                 \
        )

/**
 *  \brief Indicate release completion of a given set of ASEs to a GA endpoint.
 *
 *  \par Description:
 *       This routine indicates the release completion on the given set
 *       of one or more ASE IDs to the GA Endpoint.
 *
 *  \param [in] device Peer Endpoint address.
 *  \param [in] ase_count Number of Endpoints included.
 *  \param [in] ase_index List of ASE IDs.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_bap_common_error_code
 */
GA_RESULT GA_notify_release_complete
          (
              /* IN */    GA_ENDPOINT* device,
              /* IN */    UINT8 ase_count,
              /* IN:^2 */ UINT8* ase_index
          );

/**
 *  \brief Notify SEP state updates to an Endpoint.
 *
 *  \par Description:
 *       This routine notifies updates in all SEP states to the endpoint
 *       specified. To notify to all connected endpoints, the parameter is
 *       given NULL.
 *
 *  \param [in] device Endpoint to be notified. NULL if all connected endpoints
 *                     to be notified.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_bap_common_error_code
 */
GA_RESULT GA_sep_notify_updates
          (
              /* IN */ GA_ENDPOINT * device
          );

/** \} */
/** \} */
#endif /* BAP_UCS */

#ifdef BAP_PACS_SERVER
/**
 * \addtogroup ga_bap_uc_server_pacs_api_defs
 * \{
 */

/**
 * \name UC Server PACS APIs - Update/Notify
 * \{
 * \brief This section describes the Generic Audio Update/Notify APIs for
 * UC Server PACS.
 */

/**
 *  \brief Update and/or Notify Audio Capabilities for Source when changed.
 *
 *  \par Description:
 *       This routine updates and/or notifies the Source Audio Capabilities.
 *
 *  \param [in] device Address of \ref GA_ENDPOINT type holding peer device. \n
 *                     NULL here updates the value locally
 *  \param [in] role \ref GA_ROLE_SINK or \ref GA_ROLE_SOURCE.
 *  \param [in] record_id ID of the registered Source PAC record.
 *  \param [in] pcap Address of \ref GA_AUDIO_CAP holding the audio
 *                   capabilities. \n
 *                   NULL here notifies the existing value to peer
 *  \param [in] pcap_count Capability count, Indicates number of records in a
 *                         single instance.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \note Both parameters to the API cannot be of NULL value.
 *
 *  \sa ga_bap_common_error_code
 */
GA_RESULT GA_update_audio_capability
          (
              /* IN */    GA_ENDPOINT  * device,
              /* IN */    UINT8          role,
              /* IN */    UINT8          record_id,
              /* IN:^5 */ GA_AUDIO_CAP * pcap,
              /* IN */    UINT8          pcap_count
          );

/**
 *  \brief Update and/or Notify Supported Audio Contexts for Source when changed.
 *
 *  \par Description:
 *       This routine updates and/or notifies the
 *       Source Supported Audio Contexts.
 *
 *  \param [in] device Address of \ref GA_ENDPOINT type holding peer device. \n
 *                     NULL here updates the value locally.
 *  \param [in] audio_contexts Address of UINT16 type holding
 *                             Supported Audio Contexts. \n
 *                             NULL here notifies the existing value to peer.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \note Both parameters to the API cannot be of NULL value.
 *
 *  \sa ga_bap_common_error_code
 */
#define GA_update_source_supported_audio_contexts(                             \
             /* IN - GA_ENDPOINT* */ device,                                   \
             /* IN - UINT16* */ audio_contexts                                 \
        )                                                                      \
        BAP_update_and_notify_source_capabilities                              \
        (                                                                      \
            (device),                                                          \
            GA_CHAR_PACS_SUPPORTED_AUDIO_CONTEXTS,                             \
            0U,                                                                \
            (audio_contexts),                                                  \
            sizeof(UINT16)                                                     \
        )

/**
 *  \brief Update and/or Notify Available Audio Contexts for Source when changed.
 *
 *  \par Description:
 *       This routine updates and/or Notifies the
 *       Source Available Audio Contexts.
 *
 *  \param [in] device Address of \ref GA_ENDPOINT type holding peer device. \n
 *                     NULL here updates the value locally.
 *  \param [in] audio_contexts Address of UINT16 type holding
 *                             Available Audio Contexts. \n
 *                             NULL here notifies the existing value to peer.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \note Both parameters to the API cannot be of NULL value.
 *
 *  \sa ga_bap_common_error_code
 */
#define GA_update_source_available_audio_contexts(                             \
             /* IN - GA_ENDPOINT* */ device,                                   \
             /* IN - UINT16* */ audio_contexts                                 \
        )                                                                      \
        BAP_update_and_notify_source_capabilities                              \
        (                                                                      \
            (device),                                                          \
            GA_CHAR_PACS_AVAILABLE_AUDIO_CONTEXTS,                             \
            0U,                                                                \
            (audio_contexts),                                                  \
            sizeof(UINT16)                                                     \
        )

/**
 *  \brief Update and/or Notify Audio locations for Source when changed.
 *
 *  \par Description:
 *       This routine updates and/or notifies the Source Audio locations.
 *
 *  \param [in] device Address of \ref GA_ENDPOINT type holding peer device. \n
 *                     NULL here updates the value locally.
 *  \param [in] audio_locations Address of UINT32 type holding Audio Locations. \n
 *                             NULL here notifies the existing value to peer.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \note Both parameters to the API cannot be of NULL value.
 *
 *  \sa ga_bap_common_error_code
 */
#define GA_update_source_audio_locations(                                      \
            /* IN - GA_ENDPOINT* */ device,                                    \
            /* IN - UINT32* */ audio_locations                                 \
        )                                                                      \
        BAP_update_and_notify_source_capabilities                              \
        (                                                                      \
            (device),                                                          \
            GA_CHAR_PACS_SOURCE_AUDIO_LOCATIONS,                               \
            0U,                                                                \
            (audio_locations),                                                 \
            sizeof(UINT32)                                                     \
        )

/**
 *  \brief Update and/or Notify Audio Capabilities for Source when changed.
 *
 *  \par Description:
 *       This routine updates and/or notifies the Source Audio Capabilities.
 *
 *  \param [in] device Address of \ref GA_ENDPOINT type holding peer device. \n
 *                     NULL here updates the value locally.
 *  \param [in] record_id ID of the registered Source PAC record.
 *  \param [in] cap Address of \ref GA_AUDIO_CAP holding the audio
 *                  capabilities. \n
 *                  NULL here notifies the existing value to peer.
 *  \param [in] cap_count Capability count, Indicates number of records in a
 *                        single instance.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \note Both parameters to the API cannot be of NULL value.
 *
 *  \sa ga_bap_common_error_code
 */
#define GA_update_source_audio_capability(                                     \
            /* IN - GA_ENDPOINT* */ device,                                    \
            /* IN - UINT8 */ record_id,                                        \
            /* IN:^4 - GA_AUDIO_CAP* */ cap,                                   \
            /* IN - UINT8 */cap_count                                         \
        )                                                                      \
        GA_update_audio_capability                                             \
        (                                                                      \
            (device),                                                          \
            GA_ROLE_SOURCE,                                                    \
            (record_id),                                                       \
            (cap),                                                             \
            (cap_count)                                                        \
        )

/**
 *  \brief Update and/or Notify Supported Audio Contexts for Sink when changed.
 *
 *  \par Description:
 *       This routine updates and/or notifies the
 *       Sink Supported Audio Contexts.
 *
 *  \param [in] device Address of \ref GA_ENDPOINT type holding peer device. \n
 *                     NULL here updates the value locally.
 *  \param [in] audio_contexts Address of UINT16 type holding
 *                             Supported Audio Contexts. \n
 *                             NULL here notifies the existing value to peer.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \note Both parameters to the API cannot be of NULL value.
 *
 *  \sa ga_bap_common_error_code
 */
#define GA_update_sink_supported_audio_contexts(                               \
            /* IN - GA_ENDPOINT* */ device,                                    \
            /* IN - UINT16 */ audio_contexts                                   \
        )                                                                      \
        BAP_update_and_notify_sink_capabilities                                \
        (                                                                      \
            (device),                                                          \
            GA_CHAR_PACS_SUPPORTED_AUDIO_CONTEXTS,                             \
            0U,                                                                \
            (audio_contexts),                                                  \
            sizeof(UINT16)                                                     \
        )

/**
 *  \brief Update and/or Notify Available Audio Contexts for Sink when changed.
 *
 *  \par Description:
 *       This routine updates and/or notifies the
 *       Sink Available Audio Contexts.
 *
 *  \param [in] device Address of \ref GA_ENDPOINT type holding peer device. \n
 *                     NULL here updates the value locally.
 *  \param [in] audio_contexts Address of UINT16 type holding
 *                             Available Audio Contexts. \n
 *                             NULL here notifies the existing value to peer.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \note Both parameters to the API cannot be of NULL value.
 *
 *  \sa ga_bap_common_error_code
 */
#define GA_update_sink_available_audio_contexts(                               \
            /* IN - GA_ENDPOINT* */ device,                                    \
            /* IN - UINT16* */ audio_contexts                                  \
        )                                                                      \
        BAP_update_and_notify_sink_capabilities                                \
        (                                                                      \
            (device),                                                          \
            GA_CHAR_PACS_AVAILABLE_AUDIO_CONTEXTS,                             \
            0U,                                                                \
            (audio_contexts),                                                  \
            sizeof(UINT16)                                                     \
        )

/**
 *  \brief Update and/or Notify Audio locations for Sink when changed.
 *
 *  \par Description:
 *       This routine updates and/or notifies the Sink Audio locations.
 *
 *  \param [in] device Address of \ref GA_ENDPOINT type holding peer device. \n
 *                     NULL here updates the value locally.
 *  \param [in] audio_locations Address of UINT32 type holding Audio Locations. \n
 *                             NULL here notifies the existing value to peer.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \note Both parameters to the API cannot be of NULL value.
 *
 *  \sa ga_bap_common_error_code
 */
#define GA_update_sink_audio_locations(                                        \
            /* IN - GA_ENDPOINT* */ device,                                    \
            /* IN - UINT32* */ audio_locations                                 \
        )                                                                      \
        BAP_update_and_notify_sink_capabilities                                \
        (                                                                      \
            (device),                                                          \
            GA_CHAR_PACS_SINK_AUDIO_LOCATIONS,                                 \
            0U,                                                                \
            (audio_locations),                                                 \
            sizeof(UINT32)                                                     \
        )

 /**
 *  \brief Update and/or Notify Audio Capabilities for Sink when changed.
 *
 *  \par Description:
 *       This routine updates and/or notifies the Sink Audio Capabilities.
 *
 *  \param [in] device Address of \ref GA_ENDPOINT type holding peer device. \n
 *                     NULL here updates the value locally.
 *  \param [in] record_id ID of the registered Sink PAC record.
 *  \param [in] cap Address of \ref GA_AUDIO_CAP holding the audio
 *                  capabilities. \n
 *                  NULL here notifies the existing value to peer.
 *  \param [in] cap_count Capability count, Indicates number of records in a
 *                        single instance.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \note Both parameters to the API cannot be of NULL value.
 *
 *  \sa ga_bap_common_error_code
 */
#define GA_update_sink_audio_capability(                                       \
            /* IN - GA_ENDPOINT* */ device,                                    \
            /* IN - UINT8 */ record_id,                                        \
            /* IN:^4 - GA_AUDIO_CAP* */ cap,                                   \
            /* IN - UINT8 */cap_count                                          \
        )                                                                      \
        GA_update_audio_capability                                             \
        (                                                                      \
            (device),                                                          \
            GA_ROLE_SINK,                                                      \
            (record_id),                                                       \
            (cap),                                                             \
            (cap_count)                                                        \
        )

/** \} */
/** \} */
#endif /* BAP_PACS_SERVER */

/** \} */
/** \} */
/** \} */

/**
 * \addtogroup ga_cas_module
 * \{
 */

/**
 * \defgroup ga_cas_api_defs API Definitions
 * \{
 * \brief This section describes the CAS Procedure APIs.
 */

/**
 * \defgroup ga_cas_server_defs Server
 * \{
 * \brief This section describes the Common Audio Service APIs for Server.
 */

/**
 * \name CAS Server APIs - Init
 * \{
 * \brief This section describes the Common Audio Service Init
 * APIs for Server.
 */

/**
 *  \brief Register a GA content control service.
 *
 *  \par Description:
 *       This routine registers a supported content control service to the
 *       GA layer and obtains a unique identifier CCID.
 *
 *  \param [in] ccs_uuid UUID of the Content Control Service registered.
 *  \param [out] ccid Content Control Identifier allocated for the service.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 */
GA_RESULT GA_register_content_service
          (
              /* IN */ UINT16 ccs_uuid,
              /* OUT */ UINT8 * ccid
          );

/** \} */

#ifdef CAP_CSIP_MEMBER
/**
 * \name CAS Server APIs - Update/Notify
 * \{
 * \brief This section describes the Common Audio Service Update/Notify
 * APIs for Server.
 */

/**
 *  \brief Update/Notify the CAP Member attribute.
 *
 *  \par Description:
 *       This routine updates and/or notifies the given attribute to the
 *       peer endpoint specified.
 *
 *  \param [in] device Peer Endpoint.
 *  \param [in] attribute Attribute to update/notify.
 *  \param [in] info \ref GA_SET_MEMBER with the attribute to be
 *                   updated/notified.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 */
GA_RESULT GA_cap_member_update
          (
              /* IN */ GA_ENDPOINT * device,
              /* IN */ UINT16 attribute,
              /* IN */ GA_SET_MEMBER * info
          );

/**
 *  \brief Update/Notify the CAP Member SIRK.
 *
 *  \par Description:
 *       This routine updates and/or notifies the given SIRK to the
 *       peer endpoint specified.
 *
 *  \param [in] device Peer Endpoint.
 *  \param [in] info \ref GA_SET_MEMBER with the SIRK to be
 *                   updated/notified.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 */
#define GA_cap_member_sirk_update(                                      \
            /* IN - GA_ENDPOINT* */ device,                             \
            /* IN - GA_SET_MEMBER* */ info                              \
        )                                                               \
        GA_cap_member_update                                            \
        (                                                               \
            (device),                                                   \
            GA_CHAR_CSIS_SIRK,                                          \
            (info)                                                      \
        )

/**
 *  \brief Update/Notify the CAP Member Size.
 *
 *  \par Description:
 *       This routine updates and/or notifies the given Size to the
 *       peer endpoint specified.
 *
 *  \param [in] device Peer Endpoint.
 *  \param [in] info \ref GA_SET_MEMBER with the Size to be
 *                   updated/notified.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 */
#define GA_cap_member_size_update(                                      \
            /* IN - GA_ENDPOINT* */ device,                             \
            /* IN - GA_SET_MEMBER* */ info                              \
        )                                                               \
        GA_cap_member_update                                            \
        (                                                               \
            (device),                                                   \
            GA_CHAR_CSIS_SIZE,                                          \
            (info)                                                      \
        )

/**
 *  \brief Update the CAP Member Rank.
 *
 *  \par Description:
 *       This routine updates the given Rank to the
 *       peer endpoint specified.
 *
 *  \param [in] info \ref GA_SET_MEMBER with the Rank to be
 *                   updated/notified.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 */
#define GA_cap_member_rank_update(                                      \
            /* IN - GA_SET_MEMBER* */ info                              \
        )                                                               \
        GA_cap_member_update                                            \
        (                                                               \
            NULL,                                                       \
            GA_CHAR_CSIS_RANK,                                          \
            (info)                                                      \
        )

/**
 *  \brief Notify the CAP Member Lock.
 *
 *  \par Description:
 *       This routine notifies the given Lock to the
 *       peer endpoint specified.
 *
 *  \param [in] device Peer Endpoint.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 */
#define GA_cap_member_lock_update(                                      \
            /* IN - GA_ENDPOINT* */ device                              \
        )                                                               \
        GA_cap_member_update                                            \
        (                                                               \
            (device),                                                   \
            GA_CHAR_CSIS_LOCK,                                          \
            NULL                                                        \
        )

#ifdef CAP_SIMULATE_RANDOM_DEVICE_LOCKING
/**
 *  \brief Update the CAP Member Lock for testing.
 *
 *  \par Description:
 *       This routine updates the given Lock state to the CAP member
 *       as if from the device specified
 *
 *  \param [in] device Fake Endpoint to simulate the Coordinator doing the lock.
 *  \param [in] info \ref GA_SET_MEMBER with the lock to be updated.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 */
#define GA_cap_member_device_lock(                                      \
            /* IN - GA_ENDPOINT* */ device,                             \
            /* IN - GA_SET_MEMBER* */ info                              \
        )                                                               \
        GA_cap_member_update                                            \
        (                                                               \
            (device),                                                   \
            GA_CHAR_CSIS_LOCK,                                          \
            (info)                                                      \
        )
#endif /* CAP_SIMULATE_RANDOM_DEVICE_LOCKING */

/** \} */
#endif /* CAP_CSIP_MEMBER */
/** \} */

/**
 * \defgroup ga_cas_client_defs Client
 * \{
 * \brief This section describes the Common Audio Service APIs for Client.
 */

/**
 * \name CAS Client APIs - Setup
 * \{
 * \brief This section describes the Common Audio Service Setup
 * APIs for Client.
 */

/**
 *  \brief Discover CAS and included members if any.
 *
 *  \par Description:
 *       This routine discovers the CAS service in the peer endpoint, and also
 *       any included member services. On successful procedure start, this API
 *       generates the \ref GA_CAP_DISCOVER_CNF event to the application.
 *
 *  \param [in] device Peer Endpoint.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 */
GA_RESULT GA_cap_discover
          (
              /* IN */ GA_ENDPOINT * device
          );

#ifdef CAP_CSIP_COORDINATOR
/**
 *  \brief Setup the CAS member instance on the peer device.
 *
 *  \par Description:
 *       This routine is used to setup and configure the CAS member identified
 *       by the service info and range on the peer device. On successful start
 *       of procedure, this API generates the \ref GA_CAP_SETUP_MEMBER_CNF
 *       event to the application.
 *
 *  \param [in] device Peer Endpoint.
 *  \param [in] info Member Service information to setup.
 *  \param [out] context GA Context allocated.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 */
GA_RESULT GA_cap_setup_member
          (
              /* IN */  GA_ENDPOINT * device,
              /* IN */  GA_BRR_SVC_INFO * info,
              /* OUT */ GA_CONTEXT * context
          );
#endif /* CAP_CSIP_COORDINATOR */

/**
 * \cond EXCLUDE_PART
 */
#ifdef CSIP_SUPPORT_CONTEXT_MANAGE
/**
 *  \brief To manage the GA CAP CoordinatedSet characteristic handles of a device.
 *
 *  \par Description:
 *       The routine enables the application to get/set the service and
 *       characteristic handle ranges from/to a device context.
 *
 *  \param [in] set
 *         \ref GA_TRUE for Context SET and \ref GA_FALSE for Context GET.
 *  \param [in] device
 *         Remote device endpoint.
 *  \param [in, out] context
 *         Context for the endpoint.
 *  \param [in, out] range
 *         Service range array for CAP CSIS.
 *  \param [in, out] info
 *         Array of characteristic handles for CAP CSIS.
 *  \param [in, out] info_count
 *         Count of characteristics handles in above parameter.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 */
GA_RESULT GA_manage_cs_context_info
          (
              /* IN         */ UINT8              set,
              /* IN         */ GA_ENDPOINT      * device,
              /* IN, OUT    */ GA_CONTEXT       * context,
              /* IN, OUT    */ GA_BRR_SVC_RANGE ** range,
              /* IN, OUT:^6 */ GA_CHAR_INFO     ** info,
              /* IN, OUT    */ UINT16           * info_count
          );

/**
 *  \brief To set the GA CAP CoordinatedSet characteristic handles of a device.
 *
 *  \par Description:
 *       The routine enables the application to set the service and
 *       characteristic handle ranges to a device context.
 *
 *  \param [in] d
 *         Remote device endpoint.
 *  \param [out] h
 *         Context handle for the endpoint.
 *  \param [in] r
 *         Service range array for CAP CSIS.
 *  \param [in] i
 *         Array of characteristic handles for CAP CSIS.
 *  \param [in] c
 *         Count of characteristics handles in above parameter.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 */
#define GA_set_cs_context_info(                                         \
            /* IN - GA_ENDPOINT* */ d,                                  \
            /* OUT - GA_CONTEXT* */ h,                                  \
            /* IN - GA_BRR_SVC_RANGE** */r,                             \
            /* IN:^5 - GA_CHAR_INFO** */i,                              \
            /* IN - UINT16* */c                                         \
        )                                                               \
        GA_manage_cs_context_info                                       \
        (                                                               \
            GA_TRUE,                                                    \
            (d),                                                        \
            (h),                                                        \
            (r),                                                        \
            (i),                                                        \
            (c)                                                         \
        )

/**
 *  \brief To get the GA CAP CoordinatedSet characteristic handles of a device.
 *
 *  \par Description:
 *       The routine enables the application to get the service and
 *       characteristic handle ranges from a device context.
 *
 *  \param [in] d
 *         Remote device endpoint.
 *  \param [in] h
 *         Context handle for the endpoint.
 *  \param [out] r
 *         Service range array for CAP CSIS.
 *  \param [out] i
 *         Array of characteristic handles for CAP CSIS.
 *  \param [out] c
 *         Count of characteristics handles in above parameter.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 */
#define GA_get_cs_context_info(                                         \
            /* IN - GA_ENDPOINT* */ d,                                  \
            /* IN - GA_CONTEXT* */ h,                                  \
            /* OUT - GA_BRR_SVC_RANGE** */r,                            \
            /* OUT:^5 - GA_CHAR_INFO** */i,                             \
            /* OUT - UINT16* */c                                        \
        )                                                               \
        GA_manage_cs_context_info                                       \
        (                                                               \
            GA_FALSE,                                                   \
            (d),                                                        \
            (h),                                                        \
            (r),                                                        \
            (i),                                                        \
            (c)                                                         \
        )
#endif /* CSIP_SUPPORT_CONTEXT_MANAGE */

/**
 * \endcond
 */

/** \} */

/**
 * \name CAS Client APIs - Release
 * \{
 * \brief This section describes the Common Audio Service Release
 * APIs for Client.
 */

/**
 *  \brief Close or Release the given CAS member context.
 *
 *  \par Description:
 *       When 'release' is set to \ref GA_TRUE, this routine initiates the
 *       release procedure for the context. Once release is done, the context
 *       is freed up and the setup must be freshly done by calling
 *       \ref GA_cap_setup_member if required for the same device again. \n
 *       If the 'release' parameter is set to \ref GA_FALSE, this API just
 *       frees the context without the release procedure.
 *
 *  \param [in] context
 *         GA context.
 *
 *  \param [in] release
 *         \ref GA_TRUE : Indicates release with freeing of context \n
 *         \ref GA_FALSE : Indicates only freeing of context
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h. \n
 *          If \ref GA_SUCCESS, \ref GA_CAP_RELEASE_MEMBER_CNF is notified on
 *          completion with status as success or failure.
 */
GA_RESULT GA_cap_terminate_member
          (
              /* IN */ GA_CONTEXT * context,
              /* IN */ UINT8 release
          );

/**
 *  \brief Release the given CAS member context.
 *
 *  \par Description:
 *       This routine initiates the release procedure for the context. Once
 *       release is done, the context is freed up and the setup must be freshly
 *       done by calling \ref GA_cap_setup_member if required for the same
 *       device again.
 *
 *  \param [in] context
 *         GA Context for the endpoint to be released.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h. \n
 *          If \ref GA_SUCCESS, \ref GA_CAP_RELEASE_MEMBER_CNF is notified on
 *          completion with status as success or failure.
 */
#define GA_cap_release_member(                               \
            /* IN - GA_CONTEXT* */context                    \
        )                                                    \
        GA_cap_terminate_member                              \
        (                                                    \
            (context),                                       \
            GA_TRUE                                          \
        )

/**
 *  \brief Free the given CAS member context.
 *
 *  \par Description:
 *       This routine frees up the given context of the CAS member.
 *
 *  \param [in] context
 *         GA Context for the endpoint to be freed.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 */
#define GA_cap_close_member(                                 \
            /* IN - GA_CONTEXT* */context                    \
        )                                                    \
        GA_cap_terminate_member                              \
        (                                                    \
            (context),                                       \
            GA_FALSE                                         \
        )

/** \} */

#ifdef CAP_CSIP_COORDINATOR
/**
 * \name CAS Client APIs - Write
 * \{
 * \brief This section describes the Common Audio Service Write
 * APIs for Client.
 */

/**
 *  \brief Lock/Unlock the CAS member of the endpoint in the given context.
 *
 *  \par Description:
 *       This routine sets the lock attribure to the CAS member of the peer
 *       endpoint referred in the context.
 *
 *  \param [in] context GA context.
 *  \param [in] lock 1 - Unlocked, 2 - Locked (as in CSIS specification).
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 */
GA_RESULT GA_cap_lock_member
          (
              /* IN */ GA_CONTEXT * context,
              /* IN */ UINT8 lock
          );

/** \} */
#endif /* CAP_CSIP_COORDINATOR */

/** \} */
/** \} */
/** \} */

/**
 * \addtogroup ga_bap_module
 * \{
 */

/**
 * \addtogroup ga_bap_uc_module
 * \{
 */

/**
 * \addtogroup ga_bap_uc_api_defs
 * \{
 */

#ifdef BAP_PACS_CLIENT
/**
 * \defgroup ga_bap_client_api_defs BAP Client
 * \{
 * \brief This section describes the various APIs for BAP Client.
 */

/**
 * \name BAP Client APIs - Init
 * \{
 * \brief This section describes the Generic Audio Init APIs for BAP Client.
 */

/**
 *  \brief Initialize the GA BAP PAC Client.
 *
 *  \par Description:
 *       This routine initializes GA BAP PAC Client.
 *
 *  \param [in] cb Application profile callback of type \ref GA_PROFILE_CB.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_bap_common_error_code
 */
#define GA_bap_client_init(                                  \
            /* IN - GA_PROFILE_CB */ cb                      \
        )                                                    \
        GA_module_init                                       \
        (                                                    \
            GA_MODULE_BAP,                                   \
            BAP_ROLE_CLIENT,                                 \
            (cb)                                             \
        )

/** \} */

/**
 * \name UC Client APIs - De-Init
 * \{
 * \brief This section describes the Generic Audio De-Init APIs for UC Client.
 */

/**
 *  \brief Shutdown the GA BAP PAC Client.
 *
 *  \par Description:
 *       This routine shuts down GA BAP PAC Client. If there is an active
 *       Unicast and/or Broadcast[with BA role] ongoing, this routine
 *       will return a failure.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_bap_common_error_code
 */
#define GA_bap_client_shutdown()                             \
        GA_module_shutdown                                   \
        (                                                    \
            GA_MODULE_BAP,                                   \
            BAP_ROLE_CLIENT                                  \
        )

/** \} */
/** \} */

/**
 * \defgroup ga_bap_uc_client_pacs_api_defs UC Client - PACS
 * \{
 * \brief This section describes the various APIs for UC Client - PACS.
 */

/**
 * \name UC Client PACS APIs - Setup
 * \{
 * \brief This section describes the Generic Audio Setup APIs for
 * UC Client PACS.
 */

/**
 *  \brief Setup a GA context for a peer endpoint.
 *
 *  \par Description:
 *       This routine allocates a GA context for a peer endpoint, discovers the
 *       audio roles supported on the peer endpoint. \n
 *       The PACS Service, Char, Desc discovery is done and configuration of
 *       notification on the remote is performed.
 *
 *  \param [in] device Peer Endpoint address.
 *  \param [out] context Allocated GA context for the peer endpoint.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \note This procedure returns the \ref GA_SETUP_CNF event.
 *
 *  \sa ga_bap_common_error_code
 */
GA_RESULT GA_setup
          (
              /* IN */ GA_ENDPOINT * device,
              /* OUT */ GA_CONTEXT * context
          );

/** \} */
/** \} */

/**
 * \addtogroup ga_bap_client_api_defs
 * \{
 */

/**
 * \name UC Client APIs - Setup
 * \{
 * \brief This section describes the Generic Audio Setup APIs for
 * UC Client.
 */

/**
 * \cond EXCLUDE_PART
 */
#ifdef BAP_SUPPORT_CONFIG_SELECTION
/**
 *  \brief To enable configuration for Characteristic Notifications.
 *
 *  \par Description:
 *       The routine enables to configure notifications for individual
 *       characteristics of BAP related service.
 *
 *  \param [in] config
 *         Bitmask for characteristics IDs.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_bap_common_error_code
 */
#define GA_update_ntf_configuration(                         \
            /* IN - UINT32 */ config                         \
        )                                                    \
        BAP_update_ntf_configuration                         \
        (                                                    \
            (config)                                         \
        )
#endif /* BAP_SUPPORT_CONFIG_SELECTION */

#ifdef BAP_SUPPORT_CONTEXT_MANAGE
/**
 *  \brief To manage the GA BAP characteristic handles of a device.
 *
 *  \par Description:
 *       The routine enables the application to get/set the service and
 *       characteristic handle ranges from/to a device context.
 *
 *  \param [in] set
 *         \ref GA_TRUE for Context SET and \ref GA_FALSE for Context GET.
 *  \param [in] device
 *         Remote device endpoint.
 *  \param [in, out] handle
 *         Context handle for the endpoint.
 *  \param [in, out] range
 *         Service range array for PACS and ASCS.
 *  \param [in, out] info
 *         Array of characteristic handles for PACS and ASCS.
 *  \param [in, out] info_count
 *         Count of characteristics handles in above parameter.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_bap_common_error_code
 */
GA_RESULT GA_manage_context_info
          (
              /* IN         */ UINT8 set,
              /* IN         */ GA_ENDPOINT * device,
              /* IN, OUT    */ BAP_HANDLE * handle,
              /* IN, OUT    */ GA_BRR_SVC_RANGE ** range,
              /* IN, OUT:^6 */ GA_CHAR_INFO ** info,
              /* IN, OUT    */ UINT16 * info_count
          );

/**
 *  \brief To set the GA BAP characteristic handles of a device.
 *
 *  \par Description:
 *       The routine enables the application to set the service and
 *       characteristic handle ranges to a device context.
 *
 *  \param [in] d
 *         Remote device endpoint.
 *  \param [out] h
 *         Context handle for the endpoint.
 *  \param [in] r
 *         Service range array for PACS and ASCS.
 *  \param [in] i
 *         Array of characteristic handles for PACS and ASCS.
 *  \param [in] c
 *         Count of characteristics handles in above parameter.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_bap_common_error_code
 */
#define GA_set_context_info(                                            \
            /* IN - GA_ENDPOINT* */ d,                                  \
            /* OUT - GA_CONTEXT* */ h,                                   \
            /* IN - GA_BRR_SVC_RANGE** */r,                             \
            /* IN:^5 - GA_CHAR_INFO** */i,                              \
            /* IN - UINT16* */c                                         \
        )                                                               \
        GA_manage_context_info                                          \
        (                                                               \
            GA_TRUE,                                                    \
            (d),                                                        \
            (h),                                                        \
            (r),                                                        \
            (i),                                                        \
            (c)                                                         \
        )

/**
 *  \brief To get the GA BAP characteristic handles of a device.
 *
 *  \par Description:
 *       The routine enables the application to get the service and
 *       characteristic handle ranges from a device context.
 *
 *  \param [in] d
 *         Remote device endpoint.
 *  \param [in] h
 *         Context handle for the endpoint.
 *  \param [out] r
 *         Service range array for PACS and ASCS.
 *  \param [out] i
 *         Array of characteristic handles for PACS and ASCS.
 *  \param [out] c
 *         Count of characteristics handles in above parameter.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_bap_common_error_code
 */
#define GA_get_context_info(                                            \
            /* IN - GA_ENDPOINT* */ d,                                  \
            /* IN - GA_CONTEXT* */ h,                                   \
            /* OUT - GA_BRR_SVC_RANGE** */r,                            \
            /* OUT:^5 - GA_CHAR_INFO** */i,                             \
            /* OUT - UINT16* */c                                        \
        )                                                               \
        GA_manage_context_info                                          \
        (                                                               \
            GA_FALSE,                                                   \
            (d),                                                        \
            (h),                                                        \
            (r),                                                        \
            (i),                                                        \
            (c)                                                         \
        )

#endif /* BAP_SUPPORT_CONTEXT_MANAGE */
/**
 * \endcond
 */

/** \} */
/** \} */
#endif /* BAP_PACS_CLIENT */

#ifdef BAP_UCC
/**
 * \defgroup ga_bap_uc_client_ascs_api_defs UC Client - ASCS
 * \{
 * \brief This section describes the various APIs for UC Client - ASCS.
 */

/**
 * \name UC Client ASCS APIs - Setup
 * \{
 * \brief This section describes the Generic Audio Setup APIs for
 * UC Client ASCS.
 */

/**
 * \cond EXCLUDE_PART
 */

#ifdef BAP_SUPPORT_CONTEXT_MANAGE
/**
 *  \brief To manage the GA stream context of a device.
 *
 *  \par Description:
 *       The routine enables the application to get/set the stream contexts
 *       of a given device context.
 *
 *  \param [in] set
 *         \ref GA_TRUE for Context SET and \ref GA_FALSE for Context GET.
 *  \param [in, out] context
 *         Context handle for the endpoint.
 *  \param [in, out] sc_context
 *         Allocated array of \ref GA_STREAM_CONTEXT.
 *  \param [in, out] sc_count
 *         Count of \ref GA_STREAM_CONTEXT allocated.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_bap_common_error_code
 */
GA_RESULT GA_manage_stream_context
          (
              /* IN         */ UINT8               set,
              /* IN, OUT    */ GA_CONTEXT        * context,
              /* IN, OUT:^4 */ GA_STREAM_CONTEXT * sc_context,
              /* IN, OUT    */ UINT16            * sc_count
          );

/**
 *  \brief To set the GA stream context of a device.
 *
 *  \par Description
 *       The routine enables the application to set the stream contexts
 *       of a given device context.
 *
 *  \param [in] context
 *         Context handle for the endpoint.
 *  \param [in] sc_context
 *         Allocated array of \ref GA_STREAM_CONTEXT.
 *  \param [in] sc_count
 *         Count of \ref GA_STREAM_CONTEXT allocated.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_bap_common_error_code
 */
#define GA_set_stream_context(                                          \
            /* IN - GA_CONTEXT* */ context,                             \
            /* IN:^3 - GA_STREAM_CONTEXT* */ sc_context,                \
            /* IN - UINT16* */ sc_count                                 \
        )                                                               \
        GA_manage_stream_context                                        \
        (                                                               \
            GA_TRUE,                                                    \
            context,                                                    \
            sc_context,                                                 \
            sc_count                                                    \
        )

/**
 *  \brief To get the GA stream context of a device.
 *
 *  \par Description:
 *       The routine enables the application to get the stream contexts
 *       of a given device context.
 *
 *  \param [in] context
 *         Context handle for the endpoint.
 *  \param [out] sc_context
 *         Allocated array of \ref GA_STREAM_CONTEXT.
 *  \param [out] sc_count
 *         Count of \ref GA_STREAM_CONTEXT allocated.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_bap_common_error_code
 */
#define GA_get_stream_context(                                          \
            /* IN - GA_CONTEXT* */ context,                             \
            /* OUT:^3 - GA_STREAM_CONTEXT* */ sc_context,               \
            /* OUT - UINT16* */ sc_count                                \
        )                                                               \
        GA_manage_stream_context                                        \
        (                                                               \
            GA_FALSE,                                                   \
            context,                                                    \
            sc_context,                                                 \
            sc_count                                                    \
        )

#endif /* BAP_SUPPORT_CONTEXT_MANAGE */

/**
 * \endcond
 */

/** \} */
/** \} */
#endif /* BAP_UCC */

#ifdef BAP_PACS_CLIENT
/**
 * \addtogroup ga_bap_client_api_defs
 * \{
 */

/**
 * \name UC Client APIs - Release
 * \{
 * \brief This section describes the Generic Audio Release APIs for UC Client.
 */

/**
 *  \brief Close or Release the given GA context.
 *
 *  \par Description:
 *       When 'release' is set to \ref GA_TRUE, this routine initiates the
 *       release procedure for the context. Once release is done, the context
 *       is freed up and the setup must be freshly done by calling
 *       \ref GA_setup() for PACS and \ref GA_sep_discover() for ASCS if
 *       required for the same device again. \n
 *       If the 'release' parameter is set to \ref GA_FALSE, this API just
 *       frees the context without the release procedure.
 *
 *  \param [in] context
 *         GA Context for the endpoint to be released/freed.
 *
 *  \param [in] release
 *         \ref GA_TRUE : Indicates release with freeing of context \n
 *         \ref GA_FALSE : Indicates only freeing of context
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h. \n
 *          If \ref GA_SUCCESS, \ref GA_RELEASE_CNF is notified on
 *          completion with status as success or failure.
 *
 *  \sa ga_bap_common_error_code
 */
GA_RESULT GA_terminate
          (
              /* IN */ GA_CONTEXT * context,
              /* IN */ UCHAR        release
          );

/**
 *  \brief Release the given GA context.
 *
 *  \par Description:
 *       This routine initiates the release procedure for the context. Once
 *       release is done, the context is freed up and the setup must be freshly
 *       done by calling \ref GA_setup() for PACS and \ref GA_sep_discover()
 *       for ASCS if required for the same device again.
 *
 *  \param [in] ctx
 *         GA Context for the endpoint to be released.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h. \n
 *          If \ref GA_SUCCESS, \ref GA_RELEASE_CNF is notified on
 *          completion with status as success or failure.
 *
 *  \sa ga_bap_common_error_code
 */
#define GA_release(                                          \
            /* IN - GA_CONTEXT* */ ctx                       \
        )                                                    \
        GA_terminate                                         \
        (                                                    \
            (ctx),                                           \
            GA_TRUE                                          \
        )

/**
 *  \brief Free the given GA context.
 *
 *  \par Description:
 *       This routine frees up the given context of the GA.
 *
 *  \param [in] ctx
 *         GA Context for the endpoint to be freed.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_bap_common_error_code
 */
#define GA_close(                                            \
            /* IN - GA_CONTEXT* */ ctx                       \
        )                                                    \
        GA_terminate                                         \
        (                                                    \
            (ctx),                                           \
            GA_FALSE                                         \
        )

/** \} */
/** \} */

/**
 * \addtogroup ga_bap_uc_client_pacs_api_defs
 * \{
 */

/**
 * \name UC Client PACS APIs - Setup
 * \{
 */

/**
 *  \brief Get the capabilities of a GA endpoint.
 *
 *  \par Description:
 *       This routine gets the capabilities for a GA endpoint. Internally based
 *       on the role specified, the values of the PACS Chars is done by read
 *       operation.
 *
 *  \param [in] context Context of the peer endpoint that is setup.
 *  \param [in] role Role on the endpoint for which the capabilities is required.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \note This procedure returns the \ref GA_GET_CAPABILITIES_CNF event
 *        multiple times with \ref GA_CONTINUE and finally with
 *        \ref GA_SUCCESS. \n
 *        The role provided as part of \ref GA_SETUP_CNF shall be used here.
 *
 *  \sa ga_bap_common_error_code
 */
GA_RESULT GA_get_capabilities
          (
              /* IN */ GA_CONTEXT * context,
              /* IN */ UINT8 role
          );

/** \} */

/**
 * \name UC Client PACS APIs - Write
 * \{
 */

/**
 *  \brief To perform Write operation on Audio Location Characteristic.
 *
 *  \par Description:
 *       This function triggers write request.
 *
 *  \param [in] context
 *         Context of the peer endpoint that is setup.
 *
 *  \param [in] role
 *         Role on the endpoint for which the write should happen.
 *
 *  \param [in] audio_locations
 *         UINT32 type holding Audio Locations.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined
 *          in \ref GA_error.h. \n
 *
 *  \sa ga_bap_common_error_code
 *  \sa ga_common_constants
 */
GA_RESULT GA_set_audio_location
          (
              /* IN */ GA_CONTEXT * context,
              /* IN */ UINT8        role,
              /* IN */ UINT32       audio_locations
          );

/**
 *  \brief To set Source Audio Location.
 *
 *  \par Description:
 *       This routine enables to set Source Audio Location.
 *
 *  \param [in] ctx
 *         Context of the peer endpoint that is setup.
 *
 *  \param [in] audio_locations
 *         UINT32 type holding Audio Locations.
 *
 *  \return \ref GA_SUCCESS on success, or, an Error Code
 *           describing the cause of failure. \n
 *
 *  \sa ga_bap_common_error_code
 */
#define GA_set_source_audio_location(                        \
            /* IN - GA_CONTEXT* */ ctx,                      \
            /* IN - UINT32 */ audio_locations                \
        )                                                    \
        GA_set_audio_location                                \
        (                                                    \
            (ctx),                                           \
            GA_ROLE_SOURCE,                                  \
            (audio_locations)                                \
        )

/**
 *  \brief To set Sink Audio Location.
 *
 *  \par Description:
 *       This routine enables to set Sink Audio Location.
 *
 *  \param [in] ctx
 *         Context of the peer endpoint that is setup.
 *
 *  \param [in] audio_locations
 *         UINT32 type holding Audio Locations.
 *
 *  \return \ref GA_SUCCESS on success, or, an Error Code
 *           describing the cause of failure. \n
 *
 *  \sa ga_bap_common_error_code
 */
#define GA_set_sink_audio_location(                          \
            /* IN - GA_CONTEXT* */ ctx,                      \
            /* IN - UINT32 */ audio_locations                \
        )                                                    \
        GA_set_audio_location                                \
        (                                                    \
            (ctx),                                           \
            GA_ROLE_SINK,                                    \
            (audio_locations)                                \
        )

/** \} */
/** \} */
#endif /* BAP_PACS_CLIENT */

#ifdef BAP_UCC
/**
 * \addtogroup ga_bap_uc_client_ascs_api_defs
 * \{
 */

/**
 * \name UC Client ASCS APIs - BAP Procedures
 * \{
 * \brief This section describes the Generic Audio BAP Procedures
 * APIs for Unicast Client.
 */

/**
 *  \brief Initialize the Unicast Client.
 *
 *  \par Description:
 *       This routine initializes Unicast Client.
 *       Ensure to call GA_bap_client_init() to initialize the
 *       BAP client module before invoking this API, else this
 *       will return a failure.
 *
 *  \param [in] cb Application profile callback of type \ref GA_PROFILE_CB.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_bap_common_error_code
 */
#define GA_uc_client_init(                                   \
            /* IN - GA_PROFILE_CB */ cb                      \
        )                                                    \
        GA_module_init                                       \
        (                                                    \
            GA_MODULE_BAP,                                   \
            BAP_ROLE_UCC,                                    \
            (cb)                                             \
        )

/**
 *  \brief Shutdown the Unicast Client.
 *
 *  \par Description:
 *       This routine shuts down Unicast Client.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_bap_common_error_code
 */
#define GA_uc_client_shutdown()                              \
        GA_module_shutdown                                   \
        (                                                    \
            GA_MODULE_BAP,                                   \
            BAP_ROLE_UCC                                     \
        )

/**
 *  \brief Discover the Audio Stream Endpoints (ASE) of a GA endpoint.
 *
 *  \par Description:
 *       This routine discovers the available audio stream endpoints on a
 *       GA endpoint that is setup previously. Internally ASCS Service,
 *       Char, Desc is done post which the notification is enabled for the
 *       applicable ASCS Char. Read on the ASE Source and ASE Sink is done to
 *       fetch the current state of the ASE. The event \ref GA_SEP_DISCOVER_CNF
 *       is notified based on the number of ASCS Source and/or Sink Char are
 *       discovered.
 *
 *  \param [in] context Context of the peer endpoint that is setup.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \note This procedure returns the \ref GA_SEP_DISCOVER_CNF event
 *        multiple times with \ref GA_CONTINUE and finally with
 *        \ref GA_SUCCESS.
 *
 *  \sa ga_bap_common_error_code
 */
GA_RESULT GA_sep_discover
          (
              /* IN */ GA_CONTEXT * context
          );

/**
 *  \brief Configure a given set of ASEs of a GA endpoint.
 *
 *  \par Description:
 *       This routine configures the given set of one or more ASE IDs of the
 *       GA Endpoint with the requested Codec Configuration.
 *       This call shall only submit codec configuration parameters that are
 *       supported by the peer received via \ref GA_GET_CAPABILITIES_CNF.
 *       Internally, an ASE CP is performed and post receiving of the response
 *       and the notification of the ASE Sink/ASE Source, an event
 *       \ref GA_SEP_CONFIGURE_CNF is generated.
 *
 *  \param [in] context Context of the peer endpoint that is setup.
 *  \param [in] sep_count Number of Endpoints included.
 *  \param [in] sep_id List of ASE IDs.
 *  \param [in] sep_role List of roles for every endpoint included.
 *  \param [in] sep_codec List of Codec Configurations for every endpoint included.
 *  \param [in] sep_phy List of Phy for the ASE IDs.
 *  \param [in] sep_latency List of Latency for the ASE IDs.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \note This procedure returns the \ref GA_SEP_CONFIGURE_CNF event.
 *
 *  \sa ga_bap_common_error_code
 */
GA_RESULT GA_sep_configure
          (
              /* IN */ GA_CONTEXT * context,
              /* IN */ UINT8 sep_count,
              /* IN:^2 */ UINT8 * sep_id,
              /* IN:^2 */ UINT8 * sep_role,
              /* IN:^2 */ GA_CODEC_INFO * sep_codec,
              /* IN:^2 */ UINT8 * sep_phy,
              /* IN:^2 */ UINT8 * sep_latency
          );

/**
 *  \brief Setup a given set of ASEs of a GA endpoint.
 *
 *  \par Description:
 *       This routine sets up the QOS configuration on the given set of one or
 *       more ASE IDs of the GA Endpoint.
 *       This call shall submit the parameters provided by the peer in the
 *       event \ref GA_SEP_CONFIGURE_CNF.
 *       Internally, an ASE CP is performed and post receiving of the response
 *       and the notification of the ASE Sink/ASE Source, an event
 *       \ref GA_SEP_SETUP_CNF is generated.
 *
 *  \param [in] context Context of the peer endpoint that is setup.
 *  \param [in] sep_count Number of Endpoints included.
 *  \param [in] sep_id List of ASE IDs.
 *  \param [in] sep_qos List of QOS Configurations for every endpoint included.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \note This procedure returns the \ref GA_SEP_SETUP_CNF event.
 *
 *  \sa ga_bap_common_error_code
 */
GA_RESULT GA_sep_setup
          (
              /* IN */ GA_CONTEXT * context,
              /* IN */ UINT8 sep_count,
              /* IN:^2 */ UINT8 * sep_id,
              /* IN:^2 */ GA_QOS_CONF * sep_qos
          );

/**
 *  \brief Start a given set of ASEs of a GA endpoint.
 *
 *  \par Description:
 *       This routine enables the given set of one or more ASE IDs of
 *       the GA Endpoint.
 *       This call shall request the Metadata from peer for this ASE.
 *       Internally, an ASE CP is performed and post receiving of the response
 *       and the notification of the ASE Sink/ASE Source, an event
 *       \ref GA_SEP_START_CNF is generated.
 *
 *  \param [in] context Context of the peer endpoint that is setup.
 *  \param [in] sep_count Number of Endpoints included.
 *  \param [in] sep_id List of ASE IDs.
 *  \param [in] sep_content List of Content Control information for
 *                          every endpoint included.
 *                          If contexts is not required, Set it to
 *                          \ref GA_CONTEXT_TYPE_PROHIBITED.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \note This procedure returns the \ref GA_SEP_START_CNF event.
 *
 *  \sa ga_bap_common_error_code
 */
GA_RESULT GA_sep_start
          (
              /* IN */ GA_CONTEXT * context,
              /* IN */ UINT8 sep_count,
              /* IN:^2 */ UINT8 * sep_id,
              /* IN:^2 */ GA_CONTENT_INFO * sep_content
          );

/**
 *  \brief Receiver Start Ready to receive Audio data for a given set of ASEs
 *         of a GA endpoint.
 *
 *  \par Description:
 *       This routine indicates the given set of one or more ASE IDs of
 *       the GA Endpoint is ready to receive audio data and completes coupling
 *       an ASE to a CIS.
 *       Internally, an ASE CP is performed and post receiving of the response
 *       and the notification of the ASE Sink/ASE Source, an event
 *       \ref GA_SEP_RX_START_READY_CNF is generated.
 *
 *  \param [in] context Context of the peer endpoint that is setup.
 *  \param [in] sep_count Number of Endpoints included.
 *  \param [in] sep_id List of ASE IDs.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \note This procedure returns the \ref GA_SEP_RX_START_READY_CNF event.
 *
 *  \sa ga_bap_common_error_code
 */
GA_RESULT GA_sep_receiver_start_ready
          (
              /* IN */ GA_CONTEXT * context,
              /* IN */ UINT8 sep_count,
              /* IN:^2 */ UINT8 * sep_id
          );

/**
 *  \brief Receiver Stop Ready to receive Audio data for a given set of ASEs
 *         of a GA endpoint.
 *
 *  \par Description:
 *       This routine indicates the given set of one or more ASE IDs of
 *       the GA Endpoint is ready to stop receiving audio data and completes
 *       decoupling an ASE to a CIS.
 *       Internally, an ASE CP is performed and post receiving of the response
 *       and the notification of the ASE Sink/ASE Source, an event
 *       \ref GA_SEP_RX_STOP_READY_CNF is generated.
 *
 *  \param [in] context Context of the peer endpoint that is setup.
 *  \param [in] sep_count Number of Endpoints included.
 *  \param [in] sep_id List of ASE IDs.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \note This procedure returns the \ref GA_SEP_RX_STOP_READY_CNF event.
 *
 *  \sa ga_bap_common_error_code
 */
GA_RESULT GA_sep_receiver_stop_ready
          (
              /* IN */ GA_CONTEXT* context,
              /* IN */ UINT8 sep_count,
              /* IN:^2 */ UINT8* sep_id
          );

/**
 *  \brief Update a given set of ASEs of a GA endpoint.
 *
 *  \par Description:
 *       This routine updates the given set of one or more ASE IDs of
 *       the GA Endpoint with new set of Content Control Information.
 *
 *  \param [in] context Context of the peer endpoint that is setup.
 *  \param [in] sep_count Number of Endpoints included.
 *  \param [in] sep_id List of ASE IDs.
 *  \param [in] sep_content List of Content Control information for
 *                          every endpoint included.
 *                          If contexts is not required, Set it to
 *                          \ref GA_CONTEXT_TYPE_PROHIBITED.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \note This procedure returns the \ref GA_SEP_UPDATE_CNF event.
 *
 *  \sa ga_bap_common_error_code
 */
GA_RESULT GA_sep_update
          (
              /* IN */ GA_CONTEXT * context,
              /* IN */ UINT8 sep_count,
              /* IN:^2 */ UINT8 * sep_id,
              /* IN:^2 */ GA_CONTENT_INFO * sep_content
          );

/**
 *  \brief Suspend a given set of ASEs of a GA endpoint.
 *
 *  \par Description:
 *       This routine disables the given set of one or more ASE IDs of
 *       the GA Endpoint. This call starts decoupling a Source/Sink ASE from a
 *       CIS for one or more Source ASE/Sink ASEs.
 *       Internally, an ASE CP is performed and post receiving of the response
 *       and the notification of the ASE Sink/ASE Source, an event
 *       \ref GA_SEP_SUSPEND_CNF is generated.
 *
 *  \param [in] context Context of the peer endpoint that is setup.
 *  \param [in] sep_count Number of Endpoints included.
 *  \param [in] sep_id List of ASE IDs.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \note This procedure returns the \ref GA_SEP_SUSPEND_CNF event.
 *
 *  \sa ga_bap_common_error_code
 */
GA_RESULT GA_sep_suspend
          (
              /* IN */ GA_CONTEXT * context,
              /* IN */ UINT8 sep_count,
              /* IN:^2 */ UINT8 * sep_id
          );

/**
 *  \brief Release a given set of ASEs of a GA endpoint.
 *
 *  \par Description:
 *       This routine releases the given set of one or more ASE IDs of
 *       the GA Endpoint. This call releases resources associated with an ASE,
 *       immediately decouples the ASE from any previously coupled CIS, and
 *       tears down any CIS previously established for the ASE for one or more
 *       ASEs. Internally, an ASE CP is performed and post receiving of the
 *       response and the notification of the ASE Sink/ASE Source, an event
 *       \ref GA_SEP_RELEASE_CNF is generated.
 *
 *  \param [in] context Context of the peer endpoint that is setup.
 *  \param [in] sep_count Number of Endpoints included.
 *  \param [in] sep_id List of ASE IDs.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \note This procedure returns the \ref GA_SEP_RELEASE_CNF event.
 *
 *  \sa ga_bap_common_error_code
 */
GA_RESULT GA_sep_release
          (
              /* IN */ GA_CONTEXT * context,
              /* IN */ UINT8 sep_count,
              /* IN:^2 */ UINT8 * sep_id
          );

/** \} */
/** \} */
#endif /* BAP_UCC */

/** \} */
/** \} */

/**
 * \addtogroup ga_bap_bc_module
 * \{
 */

/**
 * \addtogroup ga_bap_bc_api_defs
 * \{
 */

/**
 * \defgroup ga_bap_bc_src_api_defs BC Source
 * \{
 * \brief This section describes the Generic Audio APIs for Broadcast Source.
 */

/**
 * \name BC Source APIs - Init
 * \{
 * \brief This section describes the Generic Audio Init APIs
 * for Broadcast Source.
 */

/**
 *  \brief Initialize the GA Broadcast Source.
 *
 *  \par Description:
 *       This routine initializes GA Broadcast Source.
 *
 *  \param [in] cb Application profile callback of type \ref GA_PROFILE_CB.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_bap_common_error_code
 */
#define GA_bc_source_init(                                   \
            /* IN - GA_PROFILE_CB */ cb                      \
        )                                                    \
        GA_module_init                                       \
        (                                                    \
            GA_MODULE_BAP,                                   \
            BAP_ROLE_BCSRC,                                  \
            (cb)                                             \
        )

/** \} */

/**
 * \name BC Source APIs - De-Init
 * \{
 * \brief This section describes the Generic Audio De-Init APIs
 * for Broadcast Source.
 */

/**
 *  \brief Shutdown the GA Broadcast Source
 *
 *  \par Description:
 *       This routine shuts down GA Broadcast Source.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_bap_common_error_code
 */
#define GA_bc_source_shutdown()                              \
        GA_module_shutdown                                   \
        (                                                    \
            GA_MODULE_BAP,                                   \
            BAP_ROLE_BCSRC                                   \
        )

/** \} */

/**
 *  \brief Allocate a Broadcast Source session.
 *
 *  \par Description:
 *       This routine allocates a Broadcast Source session at the GA and
 *       provides a session identifier on successful allocation.
 *
 *  \param [out] ssn Session Identifier for Broadcast Source.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_bap_common_error_code
 */
#define GA_broadcast_alloc_session(                          \
            /* OUT - UINT8* */ ssn                           \
        )                                                    \
        BAP_broadcast_alloc_session                          \
        (                                                    \
            (ssn)                                            \
        )

/**
 *  \brief Free the Broadcast Source session.
 *
 *  \par Description:
 *       This routine frees the Broadcast Source session at the GA identified
 *       by the Session Identifier.
 *
 *  \param [in] ssn Session Identifier for Broadcast Source.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_bap_common_error_code
 */
#define GA_broadcast_free_session(                           \
            /* IN - UINT8 */ ssn                             \
        )                                                    \
        BAP_broadcast_free_session                           \
        (                                                    \
            (ssn)                                            \
        )

/**
 *  \brief Configure a Broadcast Source session.
 *
 *  \par Description:
 *       This routine configures a Broadcast Source session identified by
 *       the session identifier with some of the broadcast parameters.
 *
 *  \param [in] ssn Session Identifier for Broadcast Source.
 *  \param [in] phy The Physical channel to be used for the Broadcast of
 *                  streams on this session. This can take any of the valid
 *                  values from \ref ga_bap_common_constants.
 *  \param [in] packing Recommendation for a preferred arrangement of
 *                      multiple BIS subevents. \n
 *                      0 - Sequential, 1 - Interleaved.
 *  \param [in] broadcast_code Address to 16 octet broadcast code if
 *                             encryption is to be enabled, else NULL.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_bap_common_error_code
 */
#define GA_broadcast_configure_session(                                             \
            /* IN - UINT8 */ ssn,                                                   \
            /* IN - UINT8 */ phy,                                                   \
            /* IN - UINT8 */ packing,                                               \
            /* IN:16 - UINT8* */ broadcast_code                                     \
        )                                                                           \
        BAP_broadcast_configure_session                                             \
        (                                                                           \
            (ssn),                                                                  \
            (phy),                                                                  \
            (packing),                                                              \
            (broadcast_code)                                                        \
        )

/**
 *  \brief Register a Source Endpoint.
 *
 *  \par Description:
 *       This routine registers a source endpoint with a given configuration
 *       on to a Broadcast session.
 *
 *  \param [in] ssn Session Identifier for Broadcast Source.
 *  \param [in] codec Codec Information for the endpoint.
 *  \param [in] meta Metadata Information for the endpoint.
 *  \param [in] nstream Number of media streams at this endpoint.
 *  \param [in] stream Array of stream specific codec information if any.
 *  \param [out] sep Endpoint ID allocated.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_bap_common_error_code
 */
#define GA_broadcast_register_sep(                                                  \
            /* IN - UINT8 */ ssn,                                                   \
            /* IN - GA_CODEC_INFO* */ codec,                                        \
            /* IN - GA_METADATA* */ meta,                                           \
            /* IN - UINT8 */ nstream,                                               \
            /* IN:^4 - GA_CODEC_IE* */ stream,                                      \
            /* OUT - UINT8* */ sep                                                  \
        )                                                                           \
        BAP_broadcast_register_sep                                                  \
        (                                                                           \
            (ssn),                                                                  \
            (codec),                                                                \
            (meta),                                                                 \
            (nstream),                                                              \
            (stream),                                                               \
            (sep)                                                                   \
        )

/**
 *  \brief Update a Source Endpoint.
 *
 *  \par Description:
 *       This routine updates a source endpoint with a given configuration
 *       on to a Broadcast session.
 *
 *  \param [in] sep Endpoint ID.
 *  \param [in] ssn Session Identifier for Broadcast Source.
 *  \param [in] codec Codec Information for the endpoint.
 *  \param [in] meta Metadata Information for the endpoint.
 *  \param [in] nstream Number of media streams at this endpoint.
 *  \param [in] stream Array of stream specific codec information if any.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_bap_common_error_code
 */
#define GA_broadcast_update_sep(                                                    \
            /* IN - UINT8 */ sep,                                                   \
            /* IN - UINT8 */ ssn,                                                   \
            /* IN - GA_CODEC_INFO* */ codec,                                        \
            /* IN - GA_METADATA* */ meta,                                           \
            /* IN - UINT8 */ nstream,                                               \
            /* IN:^5 - GA_CODEC_IE* */ stream                                       \
        )                                                                           \
        BAP_broadcast_update_sep                                                    \
        (                                                                           \
            (sep),                                                                  \
            (ssn),                                                                  \
            (codec),                                                                \
            (meta),                                                                 \
            (nstream),                                                              \
            (stream)                                                                \
        )

/**
 *  \brief Register an Advertising Set Handle to a Broadcast Source session.
 *
 *  \par Description:
 *       This routine registers an advertising set handle to be used by
 *       the broadcast session.
 *
 *  \param [in] ssn Session Identifier for Broadcast Source.
 *  \param [in] advset The advertising handle to be used during EA
 *                     and PA broadcast.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \note Application should ensure that a valid handle is registered
 *        before trying to setup announcements.
 *
 *  \sa ga_bap_common_error_code
 */
#define GA_broadcast_register_advset(                                               \
            /* IN - UINT8 */ ssn,                                                   \
            /* IN - UINT8 */ advset                                                 \
        )                                                                           \
        BAP_broadcast_register_advset_info                                          \
        (                                                                           \
            (ssn),                                                                  \
            (advset),                                                               \
            NULL,                                                                   \
            0U,                                                                     \
            NULL,                                                                   \
            0U                                                                      \
        )

/**
 *  \brief Register an Advertising Set Handle to a Broadcast Source session.
 *
 *  \par Description:
 *       This routine registers an advertising set handle to be used by
 *       the broadcast session.
 *
 *  \param [in] ssn Session Identifier for Broadcast Source.
 *  \param [in] advset The advertising handle to be used during EA
 *                     and PA broadcast.
 *  \param [in] sd Service Data of the application profile.
 *  \param [in] sdlen Length of Service Data.
 *  \param [in] ad Additional Adv Data of the application profile.
 *  \param [in] adlen Length of Additional Adv Data.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \note Application should ensure that a valid handle is registered
 *        before trying to setup announcements.
 *
 *  \sa ga_bap_common_error_code
 */
#define GA_broadcast_register_advset_info(                                          \
            /* IN - UINT8 */ ssn,                                                   \
            /* IN - UINT8 */ advset,                                                \
            /* IN:^4 - UCHAR* */ sd,                                                \
            /* IN - UINT16 */ sdlen,                                                \
            /* IN:^6 - UCHAR* */ ad,                                                \
            /* IN - UINT16 */ adlen                                                 \
        )                                                                           \
        BAP_broadcast_register_advset_info                                          \
        (                                                                           \
            (ssn),                                                                  \
            (advset),                                                               \
            (sd),                                                                   \
            (sdlen),                                                                \
            (ad),                                                                   \
            (adlen)                                                                 \
        )

/**
 *  \brief Unregister an Advertising Set Handle from a Broadcast Source session.
 *
 *  \par Description:
 *       This routine unregisters the Advertising Set handle from a session.
 *
 *  \param [in] ssn Session Identifier for Broadcast Source.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_bap_common_error_code
 */
#define GA_broadcast_unregister_advset(                                             \
            /* IN - UINT8 */ ssn                                                    \
        )                                                                           \
        BAP_broadcast_register_advset_info                                          \
        (                                                                           \
            (ssn),                                                                  \
            BAP_BC_INVALID_ADVSET_HANDLE,                                           \
            NULL,                                                                   \
            0U,                                                                     \
            NULL,                                                                   \
            0U                                                                      \
        )

/**
 *  \brief Setup Audio Announcement for a Broadcast Source session
 *
 *  \par Description:
 *       This routine initiates the audio announcement on a given session with
 *       the given configurations. This procedure moves the broadcast session
 *       into CONFIGURED state.
 *
 *  \param [in] ssn Session Identifier for Broadcast Source.
 *  \param [in] broadcast_id 3 octet broadcast id to identify the announcement.
 *  \param [in] type SQ or HQ specifier. Currently unused.
 *  \param [in] presentation_delay The presentation delay information for the
 *                                 session to the Broadcast Sinks.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \note This procedure triggers the \ref GA_BC_SETUP_ANNOUNCEMENT_CNF event.
 *
 *  \sa ga_bap_common_error_code
 */
#define GA_broadcast_setup_announcement(                                            \
            /* IN - UINT8 */ ssn,                                                   \
            /* IN - UINT32 */ broadcast_id,                                         \
            /* IN - UINT8 */ type,                                                  \
            /* IN - UINT32 */ presentation_delay                                    \
        )                                                                           \
        BAP_broadcast_setup_announcement                                            \
        (                                                                           \
            (ssn),                                                                  \
            (broadcast_id),                                                         \
            (type),                                                                 \
            (presentation_delay)                                                    \
        )

/**
 *  \brief End Audio Announcement for a Broadcast Source session
 *
 *  \par Description:
 *       This routine terminates an ongoing announcement in a Broadcast Source
 *       session. This procedure moves the broadcast session into IDLE state.
 *
 *  \param [in] ssn Session Identifier for Broadcast Source.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \note This procedure triggers the \ref GA_BC_END_ANNOUNCEMENT_CNF event.
 *
 *  \sa ga_bap_common_error_code
 */
#define GA_broadcast_end_announcement(                       \
            /* IN - UINT8 */ ssn                             \
        )                                                    \
        BAP_broadcast_end_announcement                       \
        (                                                    \
            (ssn)                                            \
        )

/**
 *  \brief Start the Isochronous Stream on Broadcast Source session.
 *
 *  \par Description:
 *       This routine sets up the Broadcast Isochronous stream with the given
 *       configuration on the session where the announcements are started.
 *       This procedure moves the broadcast session into STREAMING state.
 *
 *  \param [in] ssn Session Identifier for Broadcast Source.
 *  \param [in] sdu_interval SDU frame interval in uSec.
 *  \param [in] max_sdu Maximum SDU size requirement for application.
 *  \param [in] max_latency Maximum latency requirement for application.
 *  \param [in] rtn SDU retransmission recommendation.
 *  \param [in] framing SDU framing requirement for application.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \note This procedure triggers the \ref GA_BC_START_CNF event.
 *
 *  \sa ga_bap_common_error_code
 */
#define GA_broadcast_start(                                                         \
            /* IN - UINT8 */ ssn,                                                   \
            /* IN - UINT32 */ sdu_interval,                                         \
            /* IN - UINT16 */ max_sdu,                                              \
            /* IN - UINT16 */ max_latency,                                          \
            /* IN - UINT8 */ rtn,                                                   \
            /* IN - UINT8 */ framing                                                \
        )                                                                           \
        BAP_broadcast_start                                                         \
        (                                                                           \
            (ssn),                                                                  \
            (sdu_interval),                                                         \
            (max_sdu),                                                              \
            (max_latency),                                                          \
            (rtn),                                                                  \
            (framing)                                                               \
        )

/**
 *  \brief Suspend the Isochronous stream on a Broadcast Source session.
 *
 *  \par Description:
 *       This routine suspends an active Isochronous stream on a Broadcast
 *       Source session identified by  the session identifier. This procedure
 *       moves the broadcast session into CONFIGURED state.
 *
 *  \param [in] ssn Session Identifier for Broadcast Source.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \note This procedure triggers the \ref GA_BC_SUSPEND_CNF event.
 *
 *  \sa ga_bap_common_error_code
 */
#define GA_broadcast_suspend(                                \
            /* IN - UINT8 */ ssn                             \
        )                                                    \
        BAP_broadcast_suspend                                \
        (                                                    \
            (ssn)                                            \
        )

/** \} */

/**
 * \defgroup ga_bap_bc_snk_api_defs BC Sink
 * \{
 * \brief This section describes the Generic Audio APIs for Broadcast Sink.
 */

/**
 * \name BC Sink APIs - Init
 * \{
 * \brief This section describes the Generic Audio Init APIs
 * for Broadcast Sink.
 */

/**
 *  \brief Initialize the GA Broadcast Sink.
 *
 *  \par Description:
 *       This routine initializes GA Broadcast Sink.
 *
 *  \param [in] cb Application profile callback of type \ref GA_PROFILE_CB.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_bap_common_error_code
 */
#define GA_bc_sink_init(                                   \
            /* IN - GA_PROFILE_CB */ cb                      \
        )                                                    \
        GA_module_init                                       \
        (                                                    \
            GA_MODULE_BAP,                                   \
            BAP_ROLE_BCSNK,                                  \
            (cb)                                             \
        )

/** \} */

/**
 * \name BC Sink APIs - De-Init
 * \{
 * \brief This section describes the Generic Audio Init APIs
 * for Broadcast Sink.
 */

/**
 *  \brief Shutdown the GA Broadcast Sink.
 *
 *  \par Description:
 *       This routine shuts down GA Broadcast Sink.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_bap_common_error_code
 */
#define GA_bc_sink_shutdown()                                \
        GA_module_shutdown                                   \
        (                                                    \
            GA_MODULE_BAP,                                   \
            BAP_ROLE_BCSNK                                   \
        )

/** \} */

/**
 *  \brief Scan for Broadcast Audio announcements.
 *
 *  \par Description:
 *       This routine is used by a Broadcast Sink to start scanning for
 *       Broadcast Audio announcements.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \note This procedure triggers the \ref GA_BC_SCAN_ANNOUNCEMENT_CNF event.
 *
 *  \sa ga_bap_common_error_code
 *  \sa GA_BC_SOURCE_ANNOUNCEMENT_IND
 */
#define GA_broadcast_scan_announcement() \
        BAP_broadcast_scan_announcement()

/**
 *  \brief Stop scanning for Announcements.
 *
 *  \par Description:
 *       This routine is used by Broadcast Sink to stop scanning for
 *       Broadcast Audio Announcements.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \note This procedure triggers the \ref GA_BC_SCAN_END_CNF event.
 *
 *  \sa ga_bap_common_error_code
 */
#define GA_broadcast_scan_end() \
        BAP_broadcast_scan_end()

/**
 *  \brief Associate to a Broadcast Audio announcement.
 *
 *  \par Description:
 *       This routine sets up an periodic sync of the Broadcast sink device
 *       with the selected source of Broadcast Audio announcement.
 *
 *  \param [in] sid The advertising Source ID as received in the announcement.
 *  \param [in] device The source endpoint device address.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \note This procedure triggers the \ref GA_BC_ASSOCIATE_CNF event.
 *
 *  \sa ga_bap_common_error_code
 *  \sa GA_BC_SOURCE_CONFIG_IND
 */
#define GA_broadcast_associate(                                                \
            /* IN - UINT8 */ sid,                                              \
            /* IN - GA_ENDPOINT* */ device                                     \
        )                                                                      \
        BAP_broadcast_associate                                                \
        (                                                                      \
            (sid),                                                             \
            (device)                                                           \
        )

/**
 *  \brief Cancel any pending associate to a Broadcast Audio announcement.
 *
 *  \par Description:
 *       This routine cancels any pending periodic advertising sync which
 *       has not been established.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \note This procedure triggers the \ref GA_BC_ASSOCIATE_CNF event with
 *        error_code OPERATION CANCELLED BY HOST (0x44), if the controller has
 *        successfully cancelled a pending periodic advertising create sync
 *        command.
 *
 *  \sa ga_bap_common_error_code
 */
#define GA_broadcast_associate_cancel() \
        BAP_broadcast_associate_cancel()
/**
 *  \brief Update Associate Info of a Broadcast Audio announcement.
 *
 *  \par Description:
 *       This routine updates the Associate Info.
 *
 *  \param [in] sid The advertising Source ID as received in the announcement.
 *  \param [in] device The source endpoint device address.
 *  \param [in] sync_handle SyncHandle received as part of PAST or by any other
 *                          accepted method.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_bap_common_error_code
 */
#define GA_broadcast_update_associate_info(                                    \
            /* IN - UINT8 */ sid,                                              \
            /* IN - GA_ENDPOINT* */ device,                                    \
            /* IN - UINT16 */ sync_handle                                      \
        )                                                                      \
        BAP_update_associate_info                                              \
        (                                                                      \
            (sid),                                                             \
            (device),                                                          \
            (sync_handle)                                                      \
        )

/**
 *  \brief Dissociate from a Broadcast Audio Announcement.
 *
 *  \par Description:
 *       This routine terminates the periodic sync on the Broadcast sink
 *       with the source of the announcement.
 *
 *  \param [in] sync_handle The SyncHandle as received in a successful
 *                          \ref GA_BC_ASSOCIATE_CNF event.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \note This procedure triggers the \ref GA_BC_DISSOCIATE_CNF event.
 *
 *  \sa ga_bap_common_error_code
 */
#define GA_broadcast_dissociate(                                               \
            /* IN - UINT16 */ sync_handle                                      \
        )                                                                      \
        BAP_broadcast_dissociate                                               \
        (                                                                      \
            (sync_handle)                                                      \
        )

/**
 *  \brief Enable streaming mode at Broadcast Sink.
 *
 *  \par Description:
 *       This routine establishes a sync with the Broadcast stream of the
 *       audio announcement source with the given configuration. This
 *       procedure puts the Broadcast Sink in STREAMING state.
 *
 *  \param [in] sync_handle The SyncHandle as received in a successful
 *                          \ref GA_BC_ASSOCIATE_CNF event.
 *  \param [in] broadcast_code Address to 16 octet broadcast code if
 *                             encryption is enabled at source, else NULL.
 *  \param [in] bis_count Number of streams to be synchronized.
 *  \param [in] bis Array of bis_count number of stream ID to be synchronized.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \note This procedure triggers the \ref GA_BC_ENABLE_CNF event.
 *
 *  \sa ga_bap_common_error_code
 *  \sa GA_BC_SOURCE_STREAM_IND
 */
#define GA_broadcast_enable(                                                   \
            /* IN - UINT16 */ sync_handle,                                     \
            /* IN:16 - UCHAR* */ broadcast_code,                               \
            /* IN - UINT8 */ bis_count,                                        \
            /* IN:^3 - UINT8* */ bis                                           \
        )                                                                      \
        BAP_broadcast_enable                                                   \
        (                                                                      \
            (sync_handle),                                                     \
            (broadcast_code),                                                  \
            (bis_count),                                                       \
            (bis)                                                              \
        )

/**
 *  \brief Disable streaming mode at Broadcast Sink.
 *
 *  \par Description:
 *       This routine terminates sync with the Broadcast stream of the
 *       audio announcement source. This procedure puts the Broadcast Sink.
 *
 *  \param [in] sync_handle The SyncHandle as received in a successful
 *                          \ref GA_BC_ASSOCIATE_CNF event.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \note This procedure triggers the \ref GA_BC_DISABLE_CNF event.
 */
#define GA_broadcast_disable(                                                  \
            /* IN - UINT16 */ sync_handle                                      \
        )                                                                      \
        BAP_broadcast_disable                                                  \
        (                                                                      \
            (sync_handle)                                                      \
        )

/**
 *  \brief Utility to decode broadcast event parameters.
 *
 *  \par Description:
 *       This routine helps with decoding of the Broadcast event parameters
 *       for each of the event type received at the application.
 *
 *  \param [in] ev_type Broadcast Event Type.
 *  \param [in] ev_data Broadcast Event Data.
 *  \param [out] param Address to one of Broadcast event param structures.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_bap_common_error_code
 *  \sa GA_BC_SOURCE_ANNOUNCEMENT_IND
 *  \sa GA_BC_ASSOCIATE_CNF
 *  \sa GA_BC_SOURCE_CONFIG_IND
 *  \sa GA_BC_DISSOCIATE_IND
 *  \sa GA_BC_DISSOCIATE_CNF
 *  \sa GA_BC_ENABLE_CNF
 *  \sa GA_BC_SOURCE_STREAM_IND
 *  \sa GA_BC_DISABLE_IND
 *  \sa GA_BC_DISABLE_CNF
 */
#define GA_broadcast_decode_event_params(                                      \
            /* IN - UINT8 */ ev_type,                                          \
            /* IN - UCHAR* */ ev_data,                                         \
            /* OUT - void* */ param                                            \
        )                                                                      \
        BAP_broadcast_decode_event_params                                      \
        (                                                                      \
            (ev_type),                                                         \
            (ev_data),                                                         \
            (param)                                                            \
        )

/**
 *  \brief Utility to decode Broadcast Audio Announcement
 *
 *  \par Description:
 *       This routine helps with decoding of the Broadcast Audio
 *       Announcements received at the application.
 *
 *  \param [in] data Advertisement data of Broadcast Source.
 *  \param [in] data_len Advertisement data length of Broadcast Source.
 *  \param [out] param Address to \ref BAP_BROADCAST_ANNOUNCEMENT param
 *                     structure.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_bap_common_error_code
 */
#define GA_broadcast_decode_broadcast_announcement(                            \
            /* IN:^2 - UCHAR* */ data,                                         \
            /* IN - UINT16 */ data_len,                                        \
            /* OUT - BAP_BROADCAST_ANNOUNCEMENT* */ param                      \
        )                                                                      \
        BAP_broadcast_decode_broadcast_announcement                            \
        (                                                                      \
            (data),                                                            \
            (data_len),                                                        \
            (param)                                                            \
        )

/**
 *  \brief Utility to decode Basic Audio Announcement
 *
 *  \par Description:
 *       This routine helps with decoding of the Basic Audio
 *       Announcements received at the application.
 *       Ensure to move the pointer 'data' to point to the Data Type
 *       GA_ADTYPE_SERVICE_DATA.
 *
 *  \param [in] data
 *  \param [out] delay
 *  \param [out] nsg
 *  \param [out] len
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \note API checks only for Type \ref GA_ADTYPE_SERVICE_DATA, and always
 *        returns \ref GA_FAILURE for other Types.
 *        API also checks for minimum Length as 16 for GA_ADTYPE_SERVICE_DATA
 *        which is the Basic Audio Annoucement, and return \ref GA_FAILURE if
 *        not abiding by this.
 *
 *  \sa ga_bap_common_error_code
 */
#define GA_broadcast_decode_basic_announcement_info(                           \
            /* IN - UCHAR* */ data,                                            \
            /* OUT - UINT32* */ delay,                                         \
            /* OUT - UINT8* */ nsg,                                            \
            /* OUT - UINT8* */ len                                             \
        )                                                                      \
        BAP_broadcast_decode_basic_announcement_info                           \
        (                                                                      \
            (data),                                                            \
            (delay),                                                           \
            (nsg),                                                             \
            (len)                                                              \
        )

#define GA_broadcast_decode_basic_announcement_level_1(                        \
            /* IN - UCHAR* */ data,                                            \
            /* OUT - BAP_BASIC_ANNOUNCEMENT_LEVEL_1* */ param,                 \
            /* OUT - UINT8* */ nbis,                                           \
            /* OUT - UINT8* */ len                                             \
        )                                                                      \
        BAP_broadcast_decode_basic_announcement_level_1                        \
        (                                                                      \
            (data),                                                            \
            (param),                                                           \
            (nbis),                                                            \
            (len)                                                              \
        )

#define GA_broadcast_decode_basic_announcement_level_2(                        \
            /* IN - UCHAR* */ data,                                            \
            /* OUT - BAP_BASIC_ANNOUNCEMENT_LEVEL_2* */ param,                 \
            /* OUT - UINT8* */ len                                             \
        )                                                                      \
        BAP_broadcast_decode_basic_announcement_level_2                        \
        (                                                                      \
            (data),                                                            \
            (param),                                                           \
            (len)                                                              \
        )

/** \} */

/** \} */
/** \} */
/** \} */
/* ================ VCP Related ================ */
#ifdef GA_VCP
/**
 * \addtogroup ga_vcp_module
 * \{
 */

/**
 * \defgroup ga_vcp_api_sequences API Sequences
 * \{
 * \brief This section describes the EtherMind GA VCP Layer API Sequences.
 */

/**
 * \defgroup ga_vcp_api_seq API Sequences
 * \{
 * \brief This section describes the Volume Control Profile API Sequences.
 * MSC depicting the flow of APIs and Events.
 * \mscfile VCP.signalling
 */

/** \} */
/** \} */

/**
 * \defgroup ga_vcp_api_defs API Definitions
 * \{
 * \brief This section describes the Volume Control Profile APIs.
 */

/**
 * \defgroup ga_vcp_volcntrl_defs Volume Controller
 * \{
 * \brief This section describes the Volume Control Profile APIs
 * for Volume Controller.
 */

#ifdef VCP_CONTROLLER
/**
 * \name VCP Controller APIs - Init
 * \{
 * \brief This section describes the Volume Control Profile Init
 * APIs for Volume Controller.
 */

/**
 *  \brief Initialize the GA Volume Control Client.
 *
 *  \par Description:
 *       This routine initializes GA Volume Control Client.
 *
 *  \param [in] cb Application profile callback of type \ref GA_PROFILE_CB.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_vcp_error_code
 */
#define GA_vc_client_init(                                   \
            /* IN - GA_PROFILE_CB */ cb                      \
        )                                                    \
        GA_module_init                                       \
        (                                                    \
            GA_MODULE_VCP,                                   \
            VCP_ROLE_CLIENT,                                 \
            (cb)                                             \
        )

/** \} */

/**
 * \name VCP Controller APIs - De-Init
 * \{
 * \brief This section describes the Volume Control Profile De-Init
 * APIs for Volume Controller.
 */

/**
 *  \brief Shutdown the GA Volume Control Client
 *
 *  \par Description:
 *       This routine shuts down GA Volume Control Client.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_vcp_error_code
 */
#define GA_vc_client_shutdown()                              \
        GA_module_shutdown                                   \
        (                                                    \
            GA_MODULE_VCP,                                   \
            VCP_ROLE_CLIENT                                  \
        )

/** \} */

/**
 * \name VCP Controller APIs - Setup
 * \{
 * \brief This section describes the Volume Control Profile Setup
 * APIs for Volume Controller.
 */

/**
 *  \brief To Setup Volume Control Service(VCS) Context
 *
 *  \par Description:
 *       This function enables to setup VCS context with given device.
 *       Internally, Service, Characterstics and Descriptors Discovery is
 *       done and Notifications are enabled. Application/Upper Layer is
 *       expected to use the allocated 'vctx' for all further
 *       transactions on VCP with peer device.
 *
 *  \param [in] device
 *         Peer Device with which the context is setup.
 *
 *  \param [out] vctx
 *         Context Allocated for GA VCP with the peer device.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h. \n
 *          If \ref GA_SUCCESS, \ref GA_VC_SETUP_CNF is notified on
 *          completion with status as success or failure.
 *
 *  \sa GA_VC_SETUP_CNF
 *  \sa ga_vcp_error_code
 */
GA_RESULT GA_vc_setup
          (
              /* IN */  GA_ENDPOINT    * device,
              /* OUT */ GA_VC_CONTEXT  * vctx
          );

/**
 * \cond EXCLUDE_PART
 */
#ifdef VCP_SUPPORT_CONFIG_SELECTION
/**
 *  \brief To enable configuration for Characteristic Notifications.
 *
 *  \par Description:
 *       The routine enables to configure notifications for individual
 *       characteristics of a given service.
 *
 *  \param [in] s_type
 *         Service type \n
 *            - \ref VCP_SERVICE_TYPE_VCS.
 *            - \ref VCP_SERVICE_TYPE_VOCS.
 *            - \ref VCP_SERVICE_TYPE_AICS.
 *            .
 *
 *  \param [in] config
 *         Bitmask for characteristics IDs.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_vcp_error_code
 */
#define GA_vc_update_ntf_configuration(                                 \
            /* IN - UCHAR */ s_type,                                    \
            /* IN - UINT32 */ config                                    \
        )                                                               \
        VCP_update_ntf_configuration                                    \
        (                                                               \
            (s_type),                                                   \
            (config)                                                    \
        )
#endif /* VCP_SUPPORT_CONFIG_SELECTION */

#ifdef VCP_SUPPORT_CONTEXT_MANAGE
/**
 *  \brief To manage the VCP VCS Context Information.
 *
 *  \par Description:
 *       This function enables to manage the context information of VCS.
 *
 *  \param [in] set
 *         \ref GA_TRUE for Context SET and \ref GA_FALSE for Context GET.
 *
 *  \param [in] device
 *         Remote Device Address.
 *
 *  \param [in, out] handle
 *         VCP Handle which is allocated during VCS context setup.
 *
 *  \param [in, out] range
 *         VCS characteristics handle range.
 *
 *  \param [in, out] info
 *         VCS characteristics information.
 *
 *  \param [in, out] info_count
 *         VCS characteristics count.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_vcp_error_code
 */
GA_RESULT GA_vc_manage_context_info
          (
              /* IN         */ UINT8              set,
              /* IN         */ GA_ENDPOINT      * device,
              /* IN, OUT    */ GA_VC_CONTEXT    * vctx,
              /* IN, OUT    */ GA_BRR_SVC_RANGE ** range,
              /* IN, OUT:^6 */ GA_CHAR_INFO     ** info,
              /* IN, OUT    */ UINT16           * info_count
          );

/**
 *  \brief To retrieve the VCS Context Information.
 *
 *  \par Description:
 *       This function enables to retrieve the context information of VCS.
 *
 *  \param [in] d
 *         Remote Device Address.
 *
 *  \param [in] h
 *         VCP Handle which is allocated during VCS context setup.
 *
 *  \param [out] r
 *         VCS characteristics handle range.
 *
 *  \param [out] i
 *         VCS characteristics information.
 *
 *  \param [out] c
 *         VCS characteristics count.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_vcp_error_code
 */
#define GA_vc_get_context_info(                                         \
            /* IN - GA_ENDPOINT* */ d,                                  \
            /* IN - GA_VC_CONTEXT* */ h,                                \
            /* OUT - GA_BRR_SVC_RANGE** */ r,                           \
            /* OUT:^5 - GA_CHAR_INFO** */ i,                            \
            /* OUT - UINT16* */ c                                       \
        )                                                               \
        GA_vc_manage_context_info                                       \
        (                                                               \
            GA_FALSE,                                                   \
            (d),                                                        \
            (h),                                                        \
            (r),                                                        \
            (i),                                                        \
            (c)                                                         \
        )

/**
 *  \brief To save the VCS Context Information.
 *
 *  \par Description:
 *       This function enables to save the context information of VCS.
 *
 *  \param [in] d
 *         Remote Device Address.
 *
 *  \param [out] h
 *         VCP Handle which is allocated during VCS context setup.
 *
 *  \param [in] r
 *         VCS characteristics handle range.
 *
 *  \param [in] i
 *         VCS characteristics information.
 *
 *  \param [in] c
 *         VCS characteristics count.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_vcp_error_code
 */
#define GA_vc_set_context_info(                                         \
            /* IN - GA_ENDPOINT* */ d,                                  \
            /* OUT - GA_VC_CONTEXT* */ h,                               \
            /* IN - GA_BRR_SVC_RANGE** */ r,                            \
            /* IN:^5 - GA_CHAR_INFO** */ i,                             \
            /* IN - UINT16* */ c                                        \
        )                                                               \
        GA_vc_manage_context_info                                       \
        (                                                               \
            GA_TRUE,                                                    \
            (d),                                                        \
            (h),                                                        \
            (r),                                                        \
            (i),                                                        \
            (c)                                                         \
        )

/**
 *  \brief To manage the VOCS Context Information.
 *
 *  \par Description:
 *       This function enables to manage the context information of VOCS.
 *
 *  \param [in] set
 *         \ref GA_TRUE for Context SET and \ref GA_FALSE for Context GET.
 *
 *  \param [in] device
 *         Remote Device Address.
 *
 *  \param [in, out] vocs_ctx
 *         VOCS Handle which is allocated during VOCS context setup.
 *
 *  \param [in, out] range
 *         VOCS characteristics handle range.
 *
 *  \param [in, out] info
 *         VOCS characteristics information.
 *
 *  \param [in, out] info_coun
 *         VOCS characteristics count.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_vcp_error_code
 */
GA_RESULT GA_vc_manage_vocs_context_info
          (
              /* IN         */ UINT8                 set,
              /* IN         */ GA_ENDPOINT        *  device,
              /* IN, OUT    */ GA_VC_CONTEXT     *  vocs_ctx,
              /* IN, OUT    */ GA_BRR_SVC_RANGE  ** range,
              /* IN, OUT:^6 */ GA_CHAR_INFO      ** info,
              /* IN, OUT    */ UINT16            * info_count
          );

/**
 *  \brief To retrieve the VOCS Context Information.
 *
 *  \par Description:
 *       This function enables to retrieve the context information of VOCS.
 *
 *  \param [in] d
 *         Remote Device Address.
 *
 *  \param [in] h
 *         VOCS Handle which is allocated during VOCS context setup.
 *
 *  \param [out] r
 *         VOCS characteristics handle range.
 *
 *  \param [out] i
 *         VOCS characteristics information.
 *
 *  \param [out] c
 *         VOCS characteristics count.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_vcp_error_code
 */
#define GA_vc_get_vocs_context_info(                                    \
            /* IN - GA_ENDPOINT* */ d,                                  \
            /* IN - GA_VC_CONTEXT* */ h,                                \
            /* OUT - GA_BRR_SVC_RANGE** */ r,                           \
            /* OUT:^5 - GA_CHAR_INFO** */ i,                            \
            /* OUT - UINT16* */ c                                       \
        )                                                               \
        GA_vc_manage_vocs_context_info                                  \
        (                                                               \
            GA_FALSE,                                                   \
            (d),                                                        \
            (h),                                                        \
            (r),                                                        \
            (i),                                                        \
            (c)                                                         \
        )

/**
 *  \brief To retrieve the VOCS Context Information.
 *
 *  \par Description:
 *       This function enables to retrieve the context information of VOCS.
 *
 *  \param [in] d
 *         Remote Device Address.
 *
 *  \param [out] h
 *         VOCS Handle which is allocated during VOCS context setup.
 *
 *  \param [in] r
 *         VOCS characteristics handle range.
 *
 *  \param [in] i
 *         VOCS characteristics information.
 *
 *  \param [in] c
 *         VOCS characteristics count.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_vcp_error_code
 */
#define GA_vc_set_vocs_context_info(                                    \
            /* IN - GA_ENDPOINT* */ d,                                  \
            /* OUT - GA_VC_CONTEXT* */ h,                               \
            /* IN - GA_BRR_SVC_RANGE** */ r,                            \
            /* IN:^5 - GA_CHAR_INFO** */ i,                             \
            /* IN - UINT16* */ c                                        \
        )                                                               \
        GA_vc_manage_vocs_context_info                                  \
        (                                                               \
            GA_TRUE,                                                    \
            (d),                                                        \
            (h),                                                        \
            (r),                                                        \
            (i),                                                        \
            (c)                                                         \
        )

/**
 *  \brief To manage the AICS Context Information.
 *
 *  \par Description:
 *       This function enables to manage the context information of AICS.
 *
 *  \param [in] set
 *         \ref GA_TRUE for Context SET and \ref GA_FALSE for Context GET.
 *
 *  \param [in] device
 *         Remote Device Address.
 *
 *  \param [in, out] aics_ctx
 *         AICS Handle which is allocated during AICS context setup.
 *
 *  \param [in, out] range
 *         AICS characteristics handle range.
 *
 *  \param [in, out] info
 *         AICS characteristics information.
 *
 *  \param [in, out] info_coun
 *         AICS characteristics count.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_vcp_error_code
 */
GA_RESULT GA_vc_manage_aics_context_info
          (
              /* IN         */ UINT8                 set,
              /* IN         */ GA_ENDPOINT        *  device,
              /* IN, OUT    */ GA_VC_CONTEXT      *  aics_ctx,
              /* IN, OUT    */ GA_BRR_SVC_RANGE   ** range,
              /* IN, OUT:^6 */ GA_CHAR_INFO       ** info,
              /* IN, OUT    */ UINT16             * info_count
          );

/**
 *  \brief To retrieve the AICS Context Information.
 *
 *  \par Description:
 *       This function enables to retrieve the context information of AICS.
 *
 *  \param [in] d
 *         Remote Device Address.
 *
 *  \param [in] h
 *         AICS Handle which is allocated during AICS context setup.
 *
 *  \param [out] r
 *         AICS characteristics handle range.
 *
 *  \param [out] i
 *         AICS characteristics information.
 *
 *  \param [out] c
 *         AICS characteristics count.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_vcp_error_code
 */
#define GA_vc_get_aics_context_info(                                    \
            /* IN - GA_ENDPOINT* */ d,                                  \
            /* IN - GA_VC_CONTEXT* */ h,                                \
            /* OUT - GA_BRR_SVC_RANGE** */ r,                           \
            /* OUT:^5 - GA_CHAR_INFO** */ i,                            \
            /* OUT - UINT16* */ c                                       \
        )                                                               \
        GA_vc_manage_aics_context_info                                  \
        (                                                               \
            GA_FALSE,                                                   \
            (d),                                                        \
            (h),                                                        \
            (r),                                                        \
            (i),                                                        \
            (c)                                                         \
        )

/**
 *  \brief To save the AICS Context Information.
 *
 *  \par Description:
 *       This function enables to save the context information of AICS.
 *
 *  \param [in] d
 *         Remote Device Address.
 *
 *  \param [out] h
 *         AICS Handle which is allocated during AICS context setup.
 *
 *  \param [in] r
 *         AICS characteristics handle range.
 *
 *  \param [in] i
 *         AICS characteristics information.
 *
 *  \param [in] c
 *         AICS characteristics count.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_vcp_error_code
 */
#define GA_vc_set_aics_context_info(                                    \
            /* IN - GA_ENDPOINT* */ d,                                  \
            /* OUT - GA_VC_CONTEXT* */ h,                               \
            /* IN - GA_BRR_SVC_RANGE** */ r,                            \
            /* IN:^5 - GA_CHAR_INFO** */ i,                             \
            /* IN - UINT16* */ c                                        \
        )                                                               \
        GA_vc_manage_aics_context_info                                  \
        (                                                               \
            GA_TRUE,                                                    \
            (d),                                                        \
            (h),                                                        \
            (r),                                                        \
            (i),                                                        \
            (c)                                                         \
        )
#endif /* VCP_SUPPORT_CONTEXT_MANAGE */

/**
 * \endcond
 */

/**
 *  \brief To Discover the Included Service - VOCS and AICS from the
 *         remote device.
 *
 *  \par Description:
 *       This function enables to discover the optional included services -
 *       VOCS and AICS from the remote device.
 *
 *  \param [in] vctx
 *         Context associated with VCP.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \note This procedure returns the \ref GA_VC_GET_CAPABILITIES_CNF event
 *        for each optional service with event status \ref GA_CONTINUE.
 *        On completion of this procedure, \ref GA_VC_GET_CAPABILITIES_CNF
 *        event is notified with event status \ref GA_SUCCESS. \n
 *        Application/Upper Layer is expected to use the information returned
 *        along with \ref GA_VC_GET_CAPABILITIES_CNF event for setting up the
 *        optional capabilities.
 *
 *  \sa GA_VC_GET_CAPABILITIES_CNF
 *  \sa ga_vcp_error_code
 */
GA_RESULT GA_vc_get_capabilities
          (
              /* IN */ GA_VC_CONTEXT * vctx
          );

/**
 *  \brief Setup GA VCP optional capabiliy with the peer device.
 *
 *  \par Description:
 *       This routine allocates a VCP optional service context with a peer
 *       endpoint, discovers the optional(VOCS, AICS) service charactersicstic
 *       and configure for notification.
 *
 *  \param [in] vctx
 *         VCP Context
 *
 *  \param [in] svc
 *         Optional Service(VOCS/AICS) Service details to Setup.
 *
 *  \param [out] cctx
 *         Context Allocated for optional service.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h. \n
 *          If \ref GA_SUCCESS, \ref GA_VC_SET_CAPABILITY_CNF is notified on
 *          completion with status as success or failure.
 *
 *  \sa GA_VC_SET_CAPABILITY_CNF
 *  \sa ga_vcp_error_code
 */
GA_RESULT GA_vc_set_capability
          (
              /* IN */  GA_VC_CONTEXT   * vctx,
              /* IN */  GA_BRR_SVC_INFO * svc,
              /* OUT */ GA_VC_CONTEXT   * cctx
          );

/** \} */

/**
 * \name VCP Controller APIs - Release
 * \{
 * \brief This section describes the Volume Control Profile Release
 * APIs for Volume Controller.
 */

/**
 *  \brief Close or Release the given VCP context.
 *
 *  \par Description:
 *       When 'release' is set to \ref GA_TRUE, this routine initiates the
 *       release procedure for the context. Once release is done, the context
 *       is freed up and the setup must be freshly done by calling
 *       \ref GA_vc_setup() if required for the same device again. \n
 *       If the 'release' parameter is set to \ref GA_FALSE, this API just
 *       frees the context without the release procedure. Any associated
 *       VOCS and AICS contexts should be freed by the application before
 *       calling this function.
 *
 *  \param [in] vctx
 *         VCP Context for the endpoint to be released/freed.
 *
 *  \param [in] release
 *         \ref GA_TRUE : Indicates release with freeing of context \n
 *         \ref GA_FALSE : Indicates only freeing of context
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h. \n
 *          If \ref GA_SUCCESS, \ref GA_VC_RELEASE_CNF is notified on
 *          completion with status as success or failure.
 *
 *  \sa GA_VC_RELEASE_CNF
 *  \sa ga_vcp_error_code
 */
GA_RESULT GA_vc_terminate
          (
              /* IN */ GA_VC_CONTEXT * vctx,
              /* IN */ UCHAR           release
          );

/**
 *  \brief Release the given VCP context.
 *
 *  \par Description:
 *       This routine initiates the release procedure for the context. Once
 *       release is done, the context is freed up and the setup must be freshly
 *       done by calling \ref GA_vc_setup() if required for the same
 *       device again. \n Any associated VOCS and AICS contexts should be
 *       released/freed by the application before calling this function.
 *
 *  \param [in] ctx
 *         VCP Context for the endpoint to be released.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h. \n
 *          If \ref GA_SUCCESS, \ref GA_VC_RELEASE_CNF is notified on
 *          completion with status as success or failure.
 *
 *  \sa GA_VC_RELEASE_CNF
 *  \sa ga_vcp_error_code
 */
#define GA_vc_release(                                       \
            /* IN - GA_VC_CONTEXT* */ ctx                    \
        )                                                    \
        GA_vc_terminate                                      \
        (                                                    \
            (ctx),                                           \
            GA_TRUE                                          \
        )

/**
 *  \brief Free the given VCP context.
 *
 *  \par Description:
 *       This routine frees up the given context of the VCP. Any associated
 *       VOCS and AICS contexts should be released/freed by the application
 *       before calling this function.
 *
 *  \param [in] ctx
 *         VCP Context for the endpoint to be freed.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_vcp_error_code
 */
#define GA_vc_close(                                         \
            /* IN - GA_VC_CONTEXT* */ ctx                    \
        )                                                    \
        GA_vc_terminate                                      \
        (                                                    \
            (ctx),                                           \
            GA_FALSE                                         \
        )

/**
 *  \brief Close or Release the given VOCS/AICS context.
 *
 *  \par Description:
 *       When 'release' is set to \ref GA_TRUE, this routine initiates the
 *       release procedure for the context. Once release is done, the context
 *       is freed up and the setup must be freshly done by calling
 *       \ref GA_vc_set_capability() if required for the same device again. \n
 *       If the 'release' parameter is set to \ref GA_FALSE, this API just
 *       frees the context without the release procedure.
 *
 *  \param [in] vcp_srvc_type
 *          VCP optional service type \n
 *             - \ref VCP_SERVICE_TYPE_VOCS
 *             - \ref VCP_SERVICE_TYPE_AICS
 *             .
 *
 *  \param [in] vctx
 *         VOCS/AICS Context for the endpoint to be released/freed.
 *
 *  \param [in] release
 *         \ref GA_TRUE : Indicates release with freeing of context \n
 *         \ref GA_FALSE : Indicates only freeing of context
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h. \n
 *          If \ref GA_SUCCESS, \ref GA_VC_RELEASE_CAPABILITY_CNF is notified
 *          on completion with status as success or failure.
 *
 *  \sa GA_VC_RELEASE_CAPABILITY_CNF
 *  \sa ga_vcp_error_code
 */
GA_RESULT GA_vc_terminate_capability
          (
              /* IN */ UCHAR           vcp_srvc_type,
              /* IN */ GA_VC_CONTEXT * vctx,
              /* IN */ UCHAR           release
          );

/**
 *  \brief Release the given VOCS/AICS context.
 *
 *  \par Description:
 *       This routine initiates the release procedure for the context. Once
 *       release is done, the context is freed up and the setup must be freshly
 *       done by calling \ref GA_vc_set_capability() if required for the
 *       same device again.
 *
 *  \param [in] vcp_srvc_type
 *         VCP optional service type \n
 *            - \ref VCP_SERVICE_TYPE_VOCS
 *            - \ref VCP_SERVICE_TYPE_AICS
 *            .
 *
 *  \param [in] vctx
 *         VOCS/AICS Context for the endpoint to be released.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h. \n
 *          If \ref GA_SUCCESS, \ref GA_VC_RELEASE_CAPABILITY_CNF is notified
 *          on completion with status as success or failure.
 *
 *  \sa GA_VC_RELEASE_CAPABILITY_CNF
 *  \sa ga_vcp_error_code
 */
#define GA_vc_release_capability(                                       \
            /* IN - UCHAR */ vcp_srvc_type,                             \
            /* IN - GA_VC_CONTEXT* */ vctx                              \
        )                                                               \
        GA_vc_terminate_capability                                      \
        (                                                               \
            (vcp_srvc_type),                                            \
            (vctx),                                                     \
            GA_TRUE                                                     \
        )

/**
 *  \brief Free the given VOCS/AICS context.
 *
 *  \par Description:
 *       This routine frees up the given context of the VOCS/AICS.
 *
 *  \param [in] vcp_srvc_type
 *         VCP optional service type \n
 *            - \ref VCP_SERVICE_TYPE_VOCS
 *            - \ref VCP_SERVICE_TYPE_AICS
 *            .
 *
 *  \param [in] vctx
 *         VOCS/AICS Context for the endpoint to be freed.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_vcp_error_code
 */
#define GA_vc_close_capability(                                         \
            /* IN - UCHAR */ vcp_srvc_type,                             \
            /* IN - GA_VC_CONTEXT* */ vctx                              \
        )                                                               \
        GA_vc_terminate_capability                                      \
        (                                                               \
            (vcp_srvc_type),                                            \
            (vctx),                                                     \
            GA_FALSE                                                    \
        )

/** \} */

/**
 * \name VCP Controller APIs - Read
 * \{
 * \brief This section describes the Volume Control Profile Read APIs
 * for Volume Controller.
 */

/**
 *  \brief To get Volume State Information.
 *
 *  \par Description:
 *       The routine enables to get Volume State Information.
 *
 *  \param [in] s_ctx
 *         Context Allocated for GA VCP with the peer device.
 *
 *  \return \ref GA_SUCCESS on success, or, an Error Code
 *          describing the cause of failure. \n
 *          On completion of this procedure, the module returns the
 *          \ref GA_VC_GET_VOLUME_STATE_CNF event with associated data
 *          through the registered callback.
 *
 *  \sa GA_VC_GET_VOLUME_STATE_CNF
 *  \sa ga_vcp_error_code
 */
#define GA_vc_get_volume_state(                                    \
            /* IN - VCP_HANDLE */ s_ctx                            \
        )                                                          \
        VCP_read_request                                           \
        (                                                          \
            (s_ctx),                                               \
            (GA_VC_GET_VOLUME_STATE_CNF)                           \
        )

/**
 *  \brief To get Volume Flags Information.
 *
 *  \par Description:
 *       The routine enables to get Volume Flags Information.
 *
 *  \param [in] s_ctx
 *         Context Allocated for GA VCP with the peer device.
 *
 *  \return \ref GA_SUCCESS on success, or, an Error Code
 *          describing the cause of failure. \n
 *          On completion of this procedure, the module returns the
 *          \ref GA_VC_GET_VOLUME_FLAGS_CNF event with associated data
 *          through the registered callback.
 *
 *  \sa GA_VC_GET_VOLUME_FLAGS_CNF
 *  \sa ga_vcp_error_code
 */
#define GA_vc_get_volume_flags(                                    \
            /* IN - VCP_HANDLE */ s_ctx                            \
        )                                                          \
        VCP_read_request                                           \
        (                                                          \
            (s_ctx),                                               \
            (GA_VC_GET_VOLUME_FLAGS_CNF)                           \
        )

/**
 *  \brief To get Volume Offset State Information.
 *
 *  \par Description:
 *       The routine enables to get Volume Offset State Information.
 *
 *  \param [in] s_ctx
 *         Context Handle associated with VOCS.
 *
 *  \return \ref GA_SUCCESS on success, or, an Error Code
 *          describing the cause of failure. \n
 *          On completion of this procedure, the module returns the
 *          \ref GA_VC_VOCS_GET_OFFSET_STATE_CNF event with associated
 *          data through the registered callback.
 *
 *  \sa GA_VC_VOCS_GET_OFFSET_STATE_CNF
 *  \sa ga_vcp_error_code
 */
#define GA_vc_vocs_get_volume_offset_state(                            \
            /* IN - VCP_VOCS_HANDLE */ s_ctx                           \
        )                                                              \
        VCP_vocs_read_request                                          \
        (                                                              \
            (s_ctx),                                                   \
            (GA_VC_VOCS_GET_OFFSET_STATE_CNF)                          \
        )

/**
 *  \brief To get Audio Location Information.
 *
 *  \par Description:
 *       The routine enables to get Audio Location Information.
 *
 *  \param [in] s_ctx
 *         Context Handle associated with VOCS.
 *
 *  \return \ref GA_SUCCESS on success, or, an Error Code
 *          describing the cause of failure. \n
 *          On completion of this procedure, the module returns the
 *          \ref GA_VC_VOCS_GET_AUDIO_LOCATION_CNF event with associated
 *          data through the registered callback.
 *
 *  \sa GA_VC_VOCS_GET_AUDIO_LOCATION_CNF
 *  \sa ga_vcp_error_code
 */
#define GA_vc_vocs_get_audio_location(                                 \
            /* IN - VCP_VOCS_HANDLE */ s_ctx                           \
        )                                                              \
        VCP_vocs_read_request                                          \
        (                                                              \
            (s_ctx),                                                   \
            (GA_VC_VOCS_GET_AUDIO_LOCATION_CNF)                        \
        )

/**
 *  \brief To get Audio Output Information.
 *
 *  \par Description:
 *       The routine enables to get Audio Output Information.
 *
 *  \param [in] s_ctx
 *         Context Handle associated with VOCS.
 *
 *  \return \ref GA_SUCCESS on success, or, an Error Code
 *          describing the cause of failure. \n
 *          On completion of this procedure, the module returns the
 *          \ref GA_VC_VOCS_GET_AUDIO_OUT_DESC_CNF event with associated
 *          data through the registered callback.
 *
 *  \sa GA_VC_VOCS_GET_AUDIO_OUT_DESC_CNF
 *  \sa ga_vcp_error_code
 */
#define GA_vc_vocs_get_audio_out_description(                          \
            /* IN - VCP_VOCS_HANDLE */ s_ctx                           \
        )                                                              \
        VCP_vocs_read_request                                          \
        (                                                              \
            (s_ctx),                                                   \
            (GA_VC_VOCS_GET_AUDIO_OUT_DESC_CNF)                        \
        )

/**
 *  \brief To get Audio Input State Information.
 *
 *  \par Description:
 *       The routine enables to get Audio Input State Information.
 *
 *  \param [in] s_ctx
 *         Context Handle associated with AICS.
 *
 *  \return \ref GA_SUCCESS on success, or, an Error Code
 *          describing the cause of failure. \n
 *          On completion of this procedure, the module returns the
 *          \ref GA_VC_AICS_GET_INPUT_STATE_CNF event with associated
 *          data through the registered callback.
 *
 *  \sa GA_VC_AICS_GET_INPUT_STATE_CNF
 *  \sa ga_vcp_error_code
 */
#define GA_vc_aics_get_input_state(                                    \
            /* IN - VCP_AICS_HANDLE */ s_ctx                           \
        )                                                              \
        VCP_aics_read_request                                          \
        (                                                              \
            (s_ctx),                                                   \
            (GA_VC_AICS_GET_INPUT_STATE_CNF)                           \
        )

/**
 *  \brief To get Gain Setting Properties Information.
 *
 *  \par Description:
 *       The routine enables to get Gain Setting Properties Information.
 *
 *  \param [in] s_ctx
 *         Context Handle associated with AICS.
 *
 *  \return \ref GA_SUCCESS on success, or, an Error Code
 *          describing the cause of failure. \n
 *          On completion of this procedure, the module returns the
 *          \ref GA_VC_AICS_GET_GAIN_SETTING_PROPRTY_CNF event with associated
 *          data through the registered callback.
 *
 *  \sa GA_VC_AICS_GET_GAIN_SETTING_PROPRTY_CNF
 *  \sa ga_vcp_error_code
 */
#define GA_vc_aics_get_gain_setting_proprty(                           \
            /* IN - VCP_AICS_HANDLE */ s_ctx                           \
        )                                                              \
        VCP_aics_read_request                                          \
        (                                                              \
            (s_ctx),                                                   \
            (GA_VC_AICS_GET_GAIN_SETTING_PROPRTY_CNF)                  \
        )

/**
 *  \brief To get Audio Input Type Information.
 *
 *  \par Description:
 *       The routine enables to get Audio Input Type Information.
 *
 *  \param [in] s_ctx
 *         Context Handle associated with AICS.
 *
 *  \return \ref GA_SUCCESS on success, or, an Error Code
 *          describing the cause of failure. \n
 *          On completion of this procedure, the module returns the
 *          \ref GA_VC_AICS_GET_INPUT_TYPE_CNF event with associated
 *          data through the registered callback.
 *
 *  \sa GA_VC_AICS_GET_INPUT_TYPE_CNF
 *  \sa ga_vcp_error_code
 */
#define GA_vc_aics_get_input_type(                                     \
            /* IN - VCP_AICS_HANDLE */ s_ctx                           \
        )                                                              \
        VCP_aics_read_request                                          \
        (                                                              \
            (s_ctx),                                                   \
            (GA_VC_AICS_GET_INPUT_TYPE_CNF)                            \
        )

/**
 *  \brief To get Audio Input Status Information.
 *
 *  \par Description:
 *       The routine enables to get Audio Input State Status Information.
 *
 *  \param [in] s_ctx
 *         Context Handle associated with AICS.
 *
 *  \return \ref GA_SUCCESS on success, or, an Error Code
 *          describing the cause of failure. \n
 *          On completion of this procedure, the module returns the
 *          \ref GA_VC_AICS_GET_INPUT_STATUS_CNF event with associated
 *          data through the registered callback.
 *
 *  \sa GA_VC_AICS_GET_INPUT_STATUS_CNF
 *  \sa ga_vcp_error_code
 */
#define GA_vc_aics_get_input_status(                                   \
            /* IN - VCP_AICS_HANDLE */ s_ctx                           \
        )                                                              \
        VCP_aics_read_request                                          \
        (                                                              \
            (s_ctx),                                                   \
            (GA_VC_AICS_GET_INPUT_STATUS_CNF)                          \
        )

/**
 *  \brief To get Audio Input Description Information.
 *
 *  \par Description:
 *       The routine enables to get Audio Input Description Information.
 *
 *  \param [in] s_ctx
 *         Context Handle associated with AICS.
 *
 *  \return \ref GA_SUCCESS on success, or, an Error Code
 *          describing the cause of failure. \n
 *          On completion of this procedure, the module returns the
 *          \ref GA_VC_AICS_GET_AUDIO_INPUT_DESC_CNF event with associated
 *          data through the registered callback.
 *
 *  \sa GA_VC_AICS_GET_AUDIO_INPUT_DESC_CNF
 *  \sa ga_vcp_error_code
 */
#define GA_vc_aics_get_audio_input_description(                        \
            /* IN - VCP_AICS_HANDLE */ s_ctx                           \
        )                                                              \
        VCP_aics_read_request                                          \
        (                                                              \
            (s_ctx),                                                   \
            (GA_VC_AICS_GET_AUDIO_INPUT_DESC_CNF)                      \
        )

/** \} */

/**
 * \name VCP Controller APIs - Write
 * \{
 * \brief This section describes the Volume Control Profile Write
 * APIs for Volume Controller.
 */

/**
 *  \brief To set Relative Volume Down.
 *
 *  \par Description:
 *       This routine enables to set Relative Volume Down.
 *
 *  \param [in] sh
 *         VCP Context.
 *
 *  \param [in] val
 *         Data for Relative Volume Down. \n
 *            - Change_Counter.
 *            .
 *
 *  \param [in] len
 *         Data length for Relative Volume Down.
 *
 *  \return \ref GA_SUCCESS on success, or, an Error Code
 *           describing the cause of failure. \n
 *           If \ref GA_SUCCESS, \ref GA_VC_CP_WT_CNF is notified.
 *
 *  \sa ga_vcp_error_code
 */
#define GA_vc_set_rel_vol_down(                                        \
            /* IN - VCP_HANDLE */ sh,                                  \
            /* IN:^3 - UCHAR* */ val,                                  \
            /* IN - UINT16 */ len                                      \
        )                                                              \
        VCP_cp_request                                                 \
        (                                                              \
            (sh),                                                      \
            (VCS_CP_OP_RELATIVE_VOL_DOWN),                             \
            (val),                                                     \
            (len)                                                      \
        )

/**
 *  \brief To set Relative Volume Up.
 *
 *  \par Description:
 *       This routine enables to set Relative Volume Up.
 *
 *  \param [in] sh
 *         VCP Context.
 *
 *  \param [in] val
 *         Data for Relative Volume Up. \n
 *            - Change_Counter.
 *            .
 *
 *  \param [in] len
 *         Data length for Relative Volume Up.
 *
 *  \return  \ref GA_SUCCESS on success, or, an Error Code
 *           describing the cause of failure. \n
 *           If \ref GA_SUCCESS, \ref GA_VC_CP_WT_CNF is notified.
 *
 *  \sa ga_vcp_error_code
 */
#define GA_vc_set_rel_vol_up(                                          \
            /* IN - VCP_HANDLE */ sh,                                  \
            /* IN:^3 - UCHAR* */ val,                                  \
            /* IN - UINT16 */ len                                      \
        )                                                              \
        VCP_cp_request                                                 \
        (                                                              \
            (sh),                                                      \
            (VCS_CP_OP_RELATIVE_VOL_UP),                               \
            (val),                                                     \
            (len)                                                      \
        )

/**
 *  \brief To set UnMute and Relative Volume Down.
 *
 *  \par Description:
 *       This routine enables to set Unmute and Relative Volume Down.
 *
 *  \param [in] sh
 *         VCP Context.
 *
 *  \param [in] val
 *         Data for Unmute & Relative Volume Down. \n
 *            - Change_Counter.
 *            .
 *
 *  \param [in] len
 *         Data length for Unmute & Relative Volume Down.
 *
 *  \return \ref GA_SUCCESS on success, or, an Error Code
 *           describing the cause of failure. \n
 *           If \ref GA_SUCCESS, \ref GA_VC_CP_WT_CNF is notified.
 *
 *  \sa ga_vcp_error_code
 */
#define GA_vc_set_unmute_rel_vol_down(                                 \
            /* IN - VCP_HANDLE */ sh,                                  \
            /* IN:^3 - UCHAR* */ val,                                  \
            /* IN - UINT16 */ len                                      \
        )                                                              \
        VCP_cp_request                                                 \
        (                                                              \
            (sh),                                                      \
            (VCS_CP_OP_UNMUTE_RELATIVE_VOL_DOWN),                      \
            (val),                                                     \
            (len)                                                      \
        )

/**
 *  \brief To set UnMute and Relative Volume Up.
 *
 *  \par Description:
 *       This routine enables to set Unmute and Relative Volume Up.
 *
 *  \param [in] sh
 *         VCP Context.
 *
 *  \param [in] val
 *         Data for Unmute & Relative Volume Up. \n
 *            - Change_Counter.
 *            .
 *
 *  \param [in] len
 *         Data length for Unmute & Relative Volume Up.
 *
 *  \return \ref GA_SUCCESS on success, or, an Error Code
 *           describing the cause of failure. \n
 *           If \ref GA_SUCCESS, \ref GA_VC_CP_WT_CNF is notified.
 *
 *  \sa ga_vcp_error_code
 */
#define GA_vc_set_unmute_rel_vol_up(                                   \
            /* IN - VCP_HANDLE */ sh,                                  \
            /* IN:^3 - UCHAR* */ val,                                  \
            /* IN - UINT16 */ len                                      \
        )                                                              \
        VCP_cp_request                                                 \
        (                                                              \
             (sh),                                                     \
             (VCS_CP_OP_UNMUTE_RELATIVE_VOL_UP),                       \
             (val),                                                    \
             (len)                                                     \
        )

/**
 *  \brief To set Absolute Volume.
 *
 *  \par Description:
 *       This routine enables to set Absolution Volume.
 *
 *  \param [in] sh
 *         VCP Context.
 *
 *  \param [in] val
 *         Data to set absolute volume. \n
 *            - Change_Counter.
 *            - Volume_Setting.
 *            .
 *
 *  \param [in] len
 *         Data length of set absolute volume information.
 *
 *  \return \ref GA_SUCCESS on success, or, an Error Code
 *           describing the cause of failure. \n
 *           If \ref GA_SUCCESS, \ref GA_VC_CP_WT_CNF is notified.
 *
 *  \sa ga_vcp_error_code
 */
#define GA_vc_set_abs_volume(                                          \
            /* IN - VCP_HANDLE */ sh,                                  \
            /* IN:^3 - UCHAR* */ val,                                  \
            /* IN - UINT16 */ len                                      \
        )                                                              \
        VCP_cp_request                                                 \
        (                                                              \
             (sh),                                                     \
             (VCS_CP_OP_SET_ABSOLUE_VOL),                              \
             (val),                                                    \
             (len)                                                     \
        )

/**
 *  \brief To set Unmute.
 *
 *  \par Description:
 *       This routine enables to Unmute.
 *
 *  \param [in] sh
 *         VCP Context.
 *
 *  \param [in] val
 *         Data to Unmute. \n
 *            - Change_Counter.
 *            .
 *
 *  \param [in] len
 *         Data length of Unmute information.
 *
 *  \return \ref GA_SUCCESS on success, or, an Error Code
 *           describing the cause of failure. \n
 *           If \ref GA_SUCCESS, \ref GA_VC_CP_WT_CNF is notified.
 *
 *  \sa ga_vcp_error_code
 */
#define GA_vc_set_unmute(                                              \
            /* IN - VCP_HANDLE */ sh,                                  \
            /* IN:^3 - UCHAR* */ val,                                  \
            /* IN - UINT16 */ len                                      \
        )                                                              \
        VCP_cp_request                                                 \
        (                                                              \
             (sh),                                                     \
             (VCS_CP_OP_UNMUTE),                                       \
             (val),                                                    \
             (len)                                                     \
        )

/**
 *  \brief To set Mute.
 *
 *  \par Description:
 *       This routine enables to Mute.
 *
 *  \param [in] sh
 *         VCP Context.
 *
 *  \param [in] val
 *         Data to Mute. \n
 *            - Change_Counter.
 *            .
 *
 *  \param [in] len
 *         Data length of Mute information.
 *
 *  \return \ref GA_SUCCESS on success, or, an Error Code
 *           describing the cause of failure. \n
 *           If \ref GA_SUCCESS, \ref GA_VC_CP_WT_CNF is notified.
 *
 *  \sa ga_vcp_error_code
 */
#define GA_vc_set_mute(                                                \
            /* IN - VCP_HANDLE */ sh,                                  \
            /* IN:^3 - UCHAR* */ val,                                  \
            /* IN - UINT16 */ len                                      \
        )                                                              \
        VCP_cp_request                                                 \
        (                                                              \
             (sh),                                                     \
             (VCS_CP_OP_MUTE),                                         \
             (val),                                                    \
             (len)                                                     \
        )


/**
 *  \brief To set Audio Location Information.
 *
 *  \par Description:
 *       The routine enables to set Audio Location Information.
 *
 *  \param [in] s_ctx
 *         Context Handle associated with VOCS.
 *
 *  \param [in] al
 *         Audio Location Value.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \note Since it is WriteWithoutResponse request,
 *        there is no response expected for this event.
 *
 *  \sa ga_vcp_error_code
 */
#define GA_vc_vocs_set_audio_location(                                 \
            /* IN - VCP_VOCS_HANDLE */ s_ctx,                          \
            /* IN - UINT32 */ al                                       \
        )                                                              \
        VCP_vocs_set_audio_location                                    \
        (                                                              \
             (s_ctx),                                                  \
             (al)                                                      \
        )

/**
 *  \brief To set Audio Output Description Information.
 *
 *  \par Description:
 *       The routine enables to set Audio Output Description Information.
 *
 *  \param [in] s_ctx
 *         Context Handle associated with VOCS.
 *
 *  \param [in] aod
 *         Pointer to Audio Output Description Information.
 *
 *  \param [in] aodl
 *         Audio Output Description Length.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \note Since it is WriteWithoutResponse request,
 *        there is no response expected for this event.
 *
 *  \sa ga_vcp_error_code
 */
#define GA_vc_vocs_set_audio_output_description(                       \
            /* IN - VCP_VOCS_HANDLE */ s_ctx,                          \
            /* IN:^3 - UCHAR* */ aod,                                  \
            /* IN - UCHAR */ aodl                                      \
        )                                                              \
        VCP_vocs_set_audio_output_description                          \
        (                                                              \
             (s_ctx),                                                  \
             (aod),                                                    \
             (aodl)                                                    \
        )

/**
 *  \brief To Set Volume Offset Information.
 *
 *  \par Description:
 *       The routine enables to set Volume Offset Information.
 *
 *  \param [in] sh
 *         Context Handle associated with VOCS.
 *
 *  \param [in] val
 *         Volume Ofset Information. \n
 *            - Change_Counter.
 *            - Volume_Offset.
 *            .
 *
 *  \param [in] len
 *         Length of Volume Flag Information.
 *
 *  \return \ref GA_SUCCESS on success or an Error Code
 *           describing the cause of failure. \n
 *           If \ref GA_SUCCESS, \ref GA_VC_VOCS_CP_WT_CNF is notified.
 *
 *  \sa ga_vcp_error_code
 */
#define GA_vc_vocs_set_volume_offset(                                  \
            /* IN - VCP_VOCS_HANDLE */ sh,                             \
            /* IN:^3 - UCHAR* */ val,                                  \
            /* IN - UCHAR */ len                                       \
        )                                                              \
        VCP_vocs_cp_request                                            \
        (                                                              \
             (sh),                                                     \
             (VOCS_CP_OP_SET_VOLUME_OFFSET),                           \
             (val),                                                    \
             (len)                                                     \
        )

/**
 *  \brief To set Audio Input Description Information.
 *
 *  \par Description:
 *       The routine enables to set Audio Input Description Information.
 *
 *  \param [in] s_ctx
 *         Context Handle associated with AICS.
 *
 *  \param [in] aid
 *         Pointer to Audio Input Description Information.
 *
 *  \param [in] aidl
 *         Audio Input Description Length.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \note Since it is WriteWithoutResponse request,
 *        there is no response expected for this event.
 *
 *  \sa ga_vcp_error_code
 */
#define GA_vc_aics_set_audio_input_description(                        \
            /* IN - VCP_AICS_HANDLE */ s_ctx,                          \
            /* IN:^3 - UCHAR* */ aid,                                  \
            /* IN - UCHAR */ aidl                                      \
        )                                                              \
        VCP_aics_set_audio_input_description                           \
        (                                                              \
             (s_ctx),                                                  \
             (aid),                                                    \
             (aidl)                                                    \
        )

/**
 *  \brief To Set Gain Setting Information.
 *
 *  \par Description:
 *       The routine enables to set Gain Setting Information.
 *
 *  \param [in] sh
 *         Context Handle associated with AICS.
 *
 *  \param [in] val
 *         Gain Setting Information. \n
 *            - Change_Counter.
 *            - Gain_setting.
 *            .
 *
 *  \param [in] len
 *         Length of Gain Setting Information.
 *
 *  \return \ref GA_SUCCESS on success or an Error Code
 *           describing the cause of failure. \n
 *           If \ref GA_SUCCESS, \ref GA_VC_AICS_CP_WT_CNF
 *           will be notified.
 *
 *  \sa ga_vcp_error_code
 */
#define GA_vc_aics_set_gain_setting(                                   \
            /* IN - VCP_AICS_HANDLE */ sh,                             \
            /* IN:^3 - UCHAR* */ val,                                  \
            /* IN - UCHAR */ len                                       \
        )                                                              \
        VCP_aics_cp_request                                            \
        (                                                              \
             (sh),                                                     \
             (AICS_CP_OP_SET_GAIN_SETTING),                            \
             (val),                                                    \
             (len)                                                     \
        )

/**
 *  \brief To Unmute.
 *
 *  \par Description:
 *       The routine enables to Unmute.
 *
 *  \param [in] sh
 *         Context Handle associated with AICS.
 *
 *  \param [in] val
 *         Unmute Information. \n
 *            - Change_Counter.
 *            .
 *
 *  \param [in] len
 *         Length of Unmute Information.
 *
 *  \return \ref GA_SUCCESS on success or an Error Code
 *           describing the cause of failure. \n
 *           If \ref GA_SUCCESS, \ref GA_VC_AICS_CP_WT_CNF
 *           will be notified.
 *
 *  \sa ga_vcp_error_code
 */
#define GA_vc_aics_unmute(                                             \
            /* IN - VCP_AICS_HANDLE */ sh,                             \
            /* IN:^3 - UCHAR* */ val,                                  \
            /* IN - UCHAR */ len                                       \
        )                                                              \
        VCP_aics_cp_request                                            \
        (                                                              \
             (sh),                                                     \
             (AICS_CP_OP_UNMUTE),                                      \
             (val),                                                    \
             (len)                                                     \
        )

/**
 *  \brief To Mute.
 *
 *  \par Description:
 *       The routine enables to Mute.
 *
 *  \param [in] sh
 *         Context Handle associated with AICS.
 *
 *  \param [in] val
 *         Mute Information. \n
 *            - Change_Counter.
 *            .
 *
 *  \param [in] len
 *         Length of Mute Information.
 *
 *  \return \ref GA_SUCCESS on success or an Error Code
 *           describing the cause of failure. \n
 *           If \ref GA_SUCCESS, \ref GA_VC_AICS_CP_WT_CNF
 *           will be notified.
 *
 *  \sa ga_vcp_error_code
 */
#define GA_vc_aics_mute(                                               \
            /* IN - VCP_AICS_HANDLE */ sh,                             \
            /* IN:^3 - UCHAR* */ val,                                  \
            /* IN - UCHAR */ len                                       \
        )                                                              \
        VCP_aics_cp_request                                            \
        (                                                              \
             (sh),                                                     \
             (AICS_CP_OP_MUTE),                                        \
             (val),                                                    \
             (len)                                                     \
        )

/**
 *  \brief To set Manual Gain Mode.
 *
 *  \par Description:
 *       The routine enables to Set Manual Gain Mode.
 *
 *  \param [in] sh
 *         Context Handle associated with AICS.
 *
 *  \param [in] val
 *         Set Manual Gain Mode Information. \n
 *            - Change_Counter.
 *            .
 *
 *  \param [in] len
 *         Length of Set Manual Gain Mode Information.
 *
 *  \return \ref GA_SUCCESS on success or an Error Code
 *           describing the cause of failure. \n
 *           If \ref GA_SUCCESS, \ref GA_VC_AICS_CP_WT_CNF
 *           will be notified.
 *
 *  \sa ga_vcp_error_code
 */
#define GA_vc_aics_set_manual_gain_mode(                               \
            /* IN - VCP_AICS_HANDLE */ sh,                             \
            /* IN:^3 - UCHAR* */ val,                                  \
            /* IN - UCHAR */ len                                       \
        )                                                              \
        VCP_aics_cp_request                                            \
        (                                                              \
             (sh),                                                     \
             (AICS_CP_OP_SET_MANUAL_GAIN_MODE),                        \
             (val),                                                    \
             (len)                                                     \
        )

/**
 *  \brief To set Automatic Gain Mode.
 *
 *  \par Description:
 *       The routine enables to Set Automatic Gain Mode.
 *
 *  \param [in] sh
 *         Context Handle associated with AICS.
 *
 *  \param [in] val
 *         Set Automatic Gain Mode Information. \n
 *            - Change_Counter.
 *            .
 *
 *  \param [in] len
 *         Length of Set Automatic Gain Mode Information.
 *
 *  \return \ref GA_SUCCESS on success or an Error Code
 *           describing the cause of failure. \n
 *           If \ref GA_SUCCESS, \ref GA_VC_AICS_CP_WT_CNF
 *           will be notified.
 *
 *  \sa ga_vcp_error_code
 */
#define GA_vc_aics_set_auto_gain_mode(                                 \
            /* IN - VCP_AICS_HANDLE */ sh,                             \
            /* IN:^3 - UCHAR* */ val,                                  \
            /* IN - UCHAR */ len                                       \
        )                                                              \
        VCP_aics_cp_request                                            \
        (                                                              \
             (sh),                                                     \
             (AICS_CP_OP_SET_AUTO_GAIN_MODE),                          \
             (val),                                                    \
             (len)                                                     \
        )

/** \} */
/** \} */
#endif /* VCP_CONTROLLER */

#ifdef VCP_RENDERER
/**
 * \defgroup ga_vcp_vol_renderer_defs Volume Renderer
 * \{
 * \brief This section describes the Volume Control Profile APIs
 * for Volume Renderer.
 */

/**
 * \name VCP Renderer APIs - Init
 * \{
 * \brief This section describes the Volume Control Profile Init
 * APIs for Volume Renderer.
 */

/**
 *  \brief Initialize the GA Volume Control Server.
 *
 *  \par Description:
 *       This routine initializes GA Volume Control Server.
 *
 *  \param [in] cb Application profile callback of type \ref GA_PROFILE_CB.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_vcp_error_code
 */
#define GA_vc_server_init(                                   \
            /* IN - GA_PROFILE_CB */ cb                      \
        )                                                    \
        GA_module_init                                       \
        (                                                    \
            GA_MODULE_VCP,                                   \
            VCP_ROLE_SERVER,                                 \
            (cb)                                             \
        )

/** \} */

/**
 * \name VCP Renderer APIs - De-Init
 * \{
 * \brief This section describes the Volume Control Profile De-Init
 * APIs for Volume Renderer.
 */

/**
 *  \brief Shutdown the GA Volume Control Server.
 *
 *  \par Description:
 *       This routine shuts down GA Volume Control Server.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_vcp_error_code
 */
#define GA_vc_server_shutdown()                              \
        GA_module_shutdown                                   \
        (                                                    \
            GA_MODULE_VCP,                                   \
            VCP_ROLE_SERVER                                  \
        )

/** \} */

/**
 * \name VCP Renderer APIs - Init
 * \{
 */

/**
 *  \brief To register optional services with VCP Renderer.
 *
 *  \par Description:
 *       This function enables to register optional (VOCS/AICS) service
 *       with VCP Render module.
 *
 *  \param [in] srvc_type
 *         Flag indicating Service type. \n
 *            - \ref VCP_SERVICE_TYPE_VOCS.
 *            - \ref VCP_SERVICE_TYPE_AICS.
 *            .
 *
 *  \param [out] handle
 *         Allocated Service Handle.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_vcp_error_code
 */
GA_RESULT GA_vc_register
          (
              /* IN  */ UCHAR          srvc_type,
              /* OUT */ GA_VR_HANDLE * handle
          );

/** \} */

/**
 * \name VCP Renderer APIs - De-Init
 * \{
 */

/**
 *  \brief To unregister optional services with VCP Renderer.
 *
 *  \par Description:
 *       This function enables to unregister optional (VOCS/AICS) service
 *       with VCP Renderer module.
 *
 *  \param [in] vc_type
 *         Flag indicating Service type. \n
 *            - \ref VCP_SERVICE_TYPE_VOCS.
 *            - \ref VCP_SERVICE_TYPE_AICS.
 *            .
 *
 *  \param [out] handle
 *         Allocated Service Handle.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_vcp_error_code
 */
GA_RESULT GA_vc_unregister
          (
              /* IN  */ UCHAR          vc_type,
              /* IN */  GA_VR_HANDLE   handle
          );

/** \} */

/**
 * \name VCP Renderer APIs - Read/Write
 * \{
 * \brief This section describes the Volume Control Profile Read/Write
 * APIs for Volume Renderer.
 */

/**
 *  \brief To send response to incoming read/write request.
 *
 *  \par Description:
 *       This function enables to send response to incoming read/write
 *       request from the peer.
 *
 *  \param [in] d
 *         Peer Device Address Information.
 *
 *  \param [in] et
 *         Event type indicating response for read or write. \n
 *            - \ref GA_RSP_TYPE_RD.
 *            - \ref GA_RSP_TYPE_WT.
 *            .
 *
 *  \param [in] es
 *         Response status for the read/write operation.
 *
 *  \param [in] rd
 *         Response information for read/write operatios \ref VCP_RSP_INFO.
 *
 *  \param [in] rdl
 *         Response information size.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_vcp_error_code
 */
#define GA_vc_send_rsp(                                                \
            /* IN - GA_ENDPOINT* */ d,                                 \
            /* IN - UCHAR */ et,                                       \
            /* IN - UINT16 */ es,                                      \
            /* IN:^5 - VCP_RSP_INFO* */ rd,                             \
            /* IN - UCHAR */ rdl                                       \
        )                                                              \
        VCP_send_rsp                                                   \
        (                                                              \
            (d),                                                       \
            (et),                                                      \
            (es),                                                      \
            (rd),                                                      \
            (rdl)                                                      \
        )

/** \} */

/**
 * \name VCP Renderer APIs - Notify
 * \{
 * \brief This section describes the Volume Control Profile Notify
 * APIs for Volume Renderer.
 */

/**
 *  \brief To Notify Charateristic Values from Volume renderer to connected
 *         Volume Controller.
 *
 *  \par Description:
 *       This routine enables to notify updated char value to specified
 *       remote device.
 *
 *  \param [in] d
 *         Endpoint to be notified.
 *
 *  \param [in] si
 *         Associated Service Handle.
 *
 *  \param [in] st
 *         Flag to indicate Service Type. \n
 *            - \ref VCP_SERVICE_TYPE_VCS.
 *            - \ref VCP_SERVICE_TYPE_VOCS.
 *            - \ref VCP_SERVICE_TYPE_AICS.
 *            .
 *
 *  \param [in] cuid
 *         characteristic to be notified.
 *
 *  \param [in] cd
 *         characteristic data to be notificed.
 *
 *  \param [in] cdl
 *         characteristic data length.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_vcp_error_code
 */
#define GA_vc_notify(                                 \
            /* IN - GA_ENDPOINT* */ d,                \
            /* IN - UCHAR */ si,                      \
            /* IN - UCHAR */ st,                      \
            /* IN - UINT16 */ cuid,                   \
            /* IN:^6 - UCHAR* */ cd,                  \
            /* IN - UCHAR */ cdl                      \
        )                                             \
        VCP_notify_char                               \
        (                                             \
            (d),                                      \
            (si),                                     \
            (st),                                     \
            (cuid),                                   \
            (cd),                                     \
            (cdl)                                     \
        )

/**
 *  \brief Notify Volume state Information.
 *
 *  \par Description:
 *       This routine enables to notify Volume state information to the
 *       specified peer device.
 *
 *  \param [in] ep
 *         Device Endpoint Address to be notified.
 *
 *  \param [in] c_info
 *         Volume data Information.
 *
 *  \param [in] c_info_len
 *         Length of Volume State Information.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_vcp_error_code
 */
#define GA_vc_notify_vcs_volume_state(                               \
            /* IN - GA_ENDPOINT* */ ep,                              \
            /* IN:^3 - UCHAR* */ c_info,                             \
            /* IN - UCHAR */ c_info_len                              \
        )                                                            \
        GA_vc_notify                                                 \
        (                                                            \
             (ep),                                                   \
             (0x00),                                                 \
             (VCP_SERVICE_TYPE_VCS),                                 \
             (GA_CHAR_VCS_VOLUME_STATE),                             \
             (c_info),                                               \
             (c_info_len)                                            \
        )

/**
 *  \brief Notify Volume Flag Information.
 *
 *  \par Description:
 *       This routine enables to notify Volume Flag information to the
 *       specified peer device.
 *
 *  \param [in] ep
 *         Device Endpoint Address to be notified.
 *
 *  \param [in] c_info
 *         Volume Flag Information.
 *
 *  \param [in] c_info_len
 *         Length of Volume Flag Information.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_vcp_error_code
 */
#define GA_vc_notify_vcs_volume_flag(                                \
            /* IN - GA_ENDPOINT* */ ep,                              \
            /* IN:^3 - UCHAR* */ c_info,                             \
            /* IN - UCHAR */ c_info_len                              \
        )                                                            \
        GA_vc_notify                                                 \
        (                                                            \
             (ep),                                                   \
             0x00,                                                   \
             VCP_SERVICE_TYPE_VCS,                                   \
             (GA_CHAR_VCS_VOLUME_FLAGS),                             \
             (c_info),                                               \
             (c_info_len)                                            \
        )

/**
 *  \brief Notify Volume Offset State Information.
 *
 *  \par Description:
 *       This routine enables to notify Volume Offset Information to the specified
 *       peer device.
 *
 *  \param [in] ep
 *         Device Endpoint Address to be notified.
 *
 *  \param [in] si
 *         Service Instance associated with VOCS.
 *
 *  \param [in] c_info
 *         Volume Offset State Information. \n
 *            - Volume_Offset.
 *            - Change_Counter.
 *            .
 *
 *  \param [in] c_info_len
 *         Length of Volume Offset State Information.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_vcp_error_code
 */
#define GA_vc_notify_vocs_volume_offset(                             \
            /* IN - GA_ENDPOINT* */ ep,                              \
            /* IN - UCHAR */ si,                                     \
            /* IN:^4 - UCHAR* */ c_info,                             \
            /* IN - UCHAR */ c_info_len                              \
        )                                                            \
        GA_vc_notify                                                 \
        (                                                            \
             (ep),                                                   \
             (si),                                                   \
             VCP_SERVICE_TYPE_VOCS,                                  \
             (GA_CHAR_VOCS_OFFSET_STATE),                            \
             (c_info),                                               \
             (c_info_len)                                            \
        )

/**
 *  \brief Notify Audio Location Information.
 *
 *  \par Description:
 *       This routine enables to notify Audio Location Information to the
 *       specified peer device.
 *
 *  \param [in] ep
 *         Device Endpoint Address to be notified.
 *
 *  \param [in] si
 *         Service Instance associated with VOCS.
 *
 *  \param [in] c_info
 *         Audio Location Information.
 *
 *  \param [in] c_info_len
 *         Length of Audio Location Information.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_vcp_error_code
 */
#define GA_vc_notify_vocs_audio_location(                            \
            /* IN - GA_ENDPOINT* */ ep,                              \
            /* IN - UCHAR */ si,                                     \
            /* IN:^4 - UCHAR* */ c_info,                             \
            /* IN - UCHAR */ c_info_len                              \
        )                                                            \
        GA_vc_notify                                                 \
        (                                                            \
             (ep),                                                   \
             (si),                                                   \
             VCP_SERVICE_TYPE_VOCS,                                  \
             (GA_CHAR_VOCS_AUDIO_LOCATION),                          \
             (c_info),                                               \
             (c_info_len)                                            \
        )

/**
 *  \brief Notify Audio Output Description Information.
 *
 *  \par Description:
 *       This routine enables to notify Audio Output Description Information
 *        to the specified peer device.
 *
 *  \param [in] ep
 *         Device Endpoint Address to be notified.
 *
 *  \param [in] si
 *         Service Instance associated with VOCS.
 *
 *  \param [in] c_info
 *         Audio Location Information.
 *
 *  \param [in] c_info_len
 *         Length of Audio Location Information.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_vcp_error_code
 */
#define GA_vc_notify_vocs_audio_out_desc(                            \
            /* IN - GA_ENDPOINT* */ ep,                              \
            /* IN - UCHAR */ si,                                     \
            /* IN:^4 - UCHAR* */ c_info,                             \
            /* IN - UCHAR */ c_info_len                              \
        )                                                            \
        GA_vc_notify                                                 \
        (                                                            \
             (ep),                                                   \
             (si),                                                   \
             VCP_SERVICE_TYPE_VOCS,                                  \
             (GA_CHAR_VOCS_AUDIO_OUTPUT_DESC),                       \
             (c_info),                                               \
             (c_info_len)                                            \
        )

/**
 *  \brief Notify Audio Input state Information.
 *
 *  \par Description:
 *       This routine enables to notify Audio Input State Information to the
 *       specified peer device.
 *
 *  \param [in] ep
 *         Device Endpoint Address to be notified.
 *
 *  \param [in] si
 *         Service Instance associated with AICS.
 *
 *  \param [in] c_info
 *         Audio Input State Information. \n
 *            - Gain_Setting.
 *            - Mute.
 *            - Gain_Mode.
 *            - Change_Counter.
 *            .
 *
 *  \param [in] c_info_len
 *         Length of Audio Input State Information.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_vcp_error_code
 */
#define GA_vc_notify_aics_audio_input_state(                            \
            /* IN - GA_ENDPOINT* */ ep,                                 \
            /* IN - UCHAR */ si,                                        \
            /* IN:^4 - UCHAR* */ c_info,                                \
            /* IN - UCHAR */ c_info_len                                 \
        )                                                               \
        GA_vc_notify                                                    \
        (                                                               \
             (ep),                                                      \
             (si),                                                      \
             VCP_SERVICE_TYPE_AICS,                                     \
             (GA_CHAR_AICS_INPUT_STATE),                               \
             (c_info),                                                  \
             (c_info_len)                                               \
        )

/**
 *  \brief Notify Audio Input Status Information.
 *
 *  \par Description:
 *       This routine enables to notify Audio Input Status Information to the
 *       specified peer device.
 *
 *  \param [in] ep
 *         Device Endpoint Address to be notified.
 *
 *  \param [in] si
 *         Service Instance associated with AICS.
 *
 *  \param [in] c_info
 *         Audio Input Status Information.
 *
 *  \param [in] c_info_len
 *         Length of Audio Input Status Information.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_vcp_error_code
 */
#define GA_vc_notify_aics_audio_input_status(                           \
            /* IN - GA_ENDPOINT* */ ep,                                 \
            /* IN - UCHAR */ si,                                        \
            /* IN:^4 - UCHAR* */ c_info,                                \
            /* IN - UCHAR */ c_info_len                                 \
        )                                                               \
        GA_vc_notify                                                    \
        (                                                               \
             (ep),                                                      \
             (si),                                                      \
             VCP_SERVICE_TYPE_AICS,                                     \
             (GA_CHAR_AICS_INPUT_STATUS),                               \
             (c_info),                                                  \
             (c_info_len)                                               \
        )

/**
 *  \brief Notify Audio Input Description Information.
 *
 *  \par Description:
 *       This routine enables to notify Audio Input Description Information
 *       to the specified peer device.
 *
 *  \param [in] ep
 *         Device Endpoint Address to be notified.
 *
 *  \param [in] si
 *         Service Instance associated with AICS.
 *
 *  \param [in] c_info
 *         Audio Input Description Information.
 *
 *  \param [in] c_info_len
 *         Length of Audio Input Description Information.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_vcp_error_code
 */
#define GA_vc_notify_aics_audio_input_desc(                             \
            /* IN - GA_ENDPOINT* */ ep,                                 \
            /* IN - UCHAR */ si,                                        \
            /* IN:^4 - UCHAR* */ c_info,                                \
            /* IN - UCHAR */ c_info_len                                 \
        )                                                               \
        GA_vc_notify                                                    \
        (                                                               \
             (ep),                                                      \
             (si),                                                      \
             VCP_SERVICE_TYPE_AICS,                                     \
             (GA_CHAR_AICS_AUDIO_INPUT_DESC),                           \
             (c_info),                                                  \
             (c_info_len)                                               \
        )

/** \} */
/** \} */
#endif /* VCP_RENDERER */
/** \} */
/** \} */
#endif /* GA_VCP */

/* =====  MICP Related Defines ============= */
#ifdef GA_MICP
/**
 * \addtogroup ga_micp_module
 * \{
 */

/**
 * \defgroup ga_micp_api_sequences API Sequences
 * \{
 * \brief This section describes the EtherMind GA MICP Layer API Sequences.
 */

/**
 * \defgroup ga_micp_api_seq API Sequences
 * \{
 * \brief This section describes the Microphone Control Profile API Sequences.
 * MSC depicting the flow of APIs and Events.
 * \mscfile MICP.signalling
 */

/** \} */
/** \} */

/**
 * \defgroup ga_micp_api_defs API Definitions
 * \{
 * \brief This section describes the Microphone Control Profile APIs.
 */

#ifdef MICP_CONTROLLER
/**
 * \defgroup ga_micp_cont_defs Microphone Controller
 * \{
 * \brief This section describes the Microphone Control Profile APIs
 * for Microphone Controller.
 */

/**
 * \name MICP Controller APIs - Init
 * \{
 * \brief This section describes the Microphone Control Profile Init
 * APIs for Microphone Controller.
 */

/**
 *  \brief Initialize the GA Microphone Control Client.
 *
 *  \par Description:
 *       This routine initializes GA Microphone Control Client.
 *
 *  \param [in] cb Application profile callback of type \ref GA_PROFILE_CB.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_micp_error_code
 */
#define GA_mc_client_init(                                   \
            /* IN - GA_PROFILE_CB */ cb                      \
        )                                                    \
        GA_module_init                                       \
        (                                                    \
            GA_MODULE_MICP,                                  \
            MICP_ROLE_CLIENT,                                \
            (cb)                                             \
        )

/** \} */

/**
 * \name MICP Controller APIs - De-Init
 * \{
 * \brief This section describes the Microphone Control Profile Init
 * APIs for Microphone Controller.
 */

/**
 *  \brief Shutdown the GA Microphone Control Client.
 *
 *  \par Description:
 *       This routine shuts down GA Microphone Control Client.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_micp_error_code
 */
#define GA_mc_client_shutdown()                              \
        GA_module_shutdown                                   \
        (                                                    \
            GA_MODULE_MICP,                                  \
            MICP_ROLE_CLIENT                                 \
        )

/** \} */

/**
 * \name MICP Controller APIs - Setup
 * \{
 * \brief This section describes the Microphone Control Profile Setup APIs
 * for Microphone Controller.
 */

/**
 *  \brief To Setup Microphone Control Service(MICS) Context.
 *
 *  \par Description:
 *       This function enables to setup MICS context with given device.
 *       Internally, Service, Characterstics and Descriptors Discovery is
 *       done and Notifications are enabled.
 *       mics_ctx provided in this function to be used by application
 *       for further calls to have transaction on this MICS Handle.
 *
 *  \param [in] device
 *        Peer Device with which the context needs to be set-up.
 *
 *  \param [out] mc_ctx
 *        Allocated MICS Context Handle.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h. \n
 *          If \ref GA_SUCCESS, \ref GA_MC_SETUP_CNF is notified on
 *          completion with status as success or failure.
 *
 *  \sa GA_MC_SETUP_CNF
 *  \sa ga_micp_error_code
 */
GA_RESULT GA_mc_setup
          (
              /* IN */  GA_ENDPOINT * device,
              /* OUT */ GA_MC_CONTEXT  * mc_ctx
          );

/**
 * \cond EXCLUDE_PART
 */
#ifdef MICP_SUPPORT_CONFIG_SELECTION
/**
 *  \brief To enable configuration for Characteristic Notifications.
 *
 *  \par Description:
 *       The routine enables to configure notifications for individual
 *       characteristics of a given service.
 *
 *  \param [in] s_type
 *         Service type \n
 *            - \ref MICP_SERVICE_TYPE_MICS.
 *            - \ref MICP_SERVICE_TYPE_AICS.
 *            .
 *
 *  \param [in] config
 *         Bitmask for characteristics IDs.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_micp_error_code
 */
#define GA_mc_update_ntf_configuration(                                 \
            /* IN - UCHAR */ s_type,                                    \
            /* IN - UINT32 */ config                                    \
        )                                                               \
        MICP_update_ntf_configuration                                   \
        (                                                               \
            (s_type),                                                   \
            (config)                                                    \
        )
#endif /* MICP_SUPPORT_CONFIG_SELECTION */

#ifdef MICP_SUPPORT_CONTEXT_MANAGE
/**
 *  \brief To manage the MICS Context Information.
 *
 *  \par Description:
 *       This function enables to manage the context information of MICS.
 *
 *  \param [in] set
 *         \ref GA_TRUE for Context SET and \ref GA_FALSE for Context GET.
 *
 *  \param [in] device
 *         Remote Device Address.
 *
 *  \param [in, out] mctx
 *         MICP Handle which is allocated during MICS context setup.
 *
 *  \param [in, out] range
 *         AICS characteristics handle range.
 *
 *  \param [in, out] info
 *         AICS characteristics information.
 *
 *  \param [in, out] info_count
 *         AICS characteristics count.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_micp_error_code
 */
GA_RESULT GA_mc_manage_context_info
          (
              /* IN         */ UINT8              set,
              /* IN         */ GA_ENDPOINT       * device,
              /* IN, OUT    */ GA_MC_CONTEXT     * mctx,
              /* IN, OUT    */ GA_BRR_SVC_RANGE  ** range,
              /* IN, OUT:^6 */ GA_CHAR_INFO      ** info,
              /* IN, OUT    */ UINT16            * info_count
          );

/**
 *  \brief To retrieve the MICS Context Information.
 *
 *  \par Description:
 *       This function enables to retreive the context information of MICS.
 *
 *  \param [in] d
 *         Remote Device Address.
 *
 *  \param [in] h
 *         MICP Handle which is allocated during MICS context setup.
 *
 *  \param [out] r
 *         MICS characteristics handle range.
 *
 *  \param [out] i
 *         MICS characteristics information.
 *
 *  \param [out] c
 *         MICS characteristics count.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_micp_error_code
 */
#define GA_mc_get_context_info(                                         \
            /* IN - GA_ENDPOINT* */ d,                                  \
            /* IN - GA_MC_CONTEXT* */ h,                                \
            /* OUT - GA_BRR_SVC_RANGE** */r,                            \
            /* OUT:^5 - GA_CHAR_INFO** */i,                             \
            /* OUT - UINT16* */c                                        \
        )                                                               \
        GA_mc_manage_context_info                                       \
        (                                                               \
            GA_FALSE,                                                   \
            (d),                                                        \
            (h),                                                        \
            (r),                                                        \
            (i),                                                        \
            (c)                                                         \
        )

/**
 *  \brief To save the MICS Context Information.
 *
 *  \par Description:
 *       This function enables to save the context information of MICS.
 *
 *  \param [in] d
 *         Remote Device Address.
 *
 *  \param [out] h
 *         MICP Handle which is allocated during MICS context setup.
 *
 *  \param [out] r
 *         MICS characteristics handle range.
 *
 *  \param [out] i
 *         MICS characteristics information.
 *
 *  \param [out] c
 *         MICS characteristics count.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_micp_error_code
 */
#define GA_mc_set_context_info(                                         \
            /* IN - GA_ENDPOINT* */ d,                                  \
            /* OUT - GA_MC_CONTEXT* */ h,                               \
            /* OUT - GA_BRR_SVC_RANGE** */r,                            \
            /* OUT:^5 - GA_CHAR_INFO** */i,                             \
            /* OUT - UINT16* */c                                        \
        )                                                               \
        GA_mc_manage_context_info                                       \
        (                                                               \
            GA_TRUE,                                                    \
            (d),                                                        \
            (h),                                                        \
            (r),                                                        \
            (i),                                                        \
            (c)                                                         \
        )

/**
 *  \brief To manage the AICS Context Information.
 *
 *  \par Description:
 *       This function enables to manage the context information of AICS.
 *
 *  \param [in] set
 *         \ref GA_TRUE for Context SET and \ref GA_FALSE for Context GET.
 *
 *  \param [in] device
 *         Remote Device Address.
 *
 *  \param [in, out] aics_ctx
 *         AICS Handle which is allocated during AICS context setup.
 *
 *  \param [in, out] range
 *         AICS characteristics handle range.
 *
 *  \param [in, out] info
 *         AICS characteristics information.
 *
 *  \param [in, out] info_count
 *         AICS characteristics count.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_micp_error_code
 */
GA_RESULT GA_mc_manage_aics_context_info
          (
              /* IN         */ UINT8                 set,
              /* IN         */ GA_ENDPOINT        *  device,
              /* IN, OUT    */ GA_MC_CONTEXT      *  aics_ctx,
              /* IN, OUT    */ GA_BRR_SVC_RANGE   ** range,
              /* IN, OUT:^6 */ GA_CHAR_INFO       ** info,
              /* IN, OUT    */ UINT16             * info_count
          );

/**
 *  \brief To retrieve the AICS Context Information.
 *
 *  \par Description:
 *       This function enables to retrieve the context information of AICS.
 *
 *  \param [in] d
 *         Remote Device Address.
 *
 *  \param [in] h
 *         AICS Handle which is allocated during AICS context setup.
 *
 *  \param [out] r
 *         AICS characteristics handle range.
 *
 *  \param [out] i
 *         AICS characteristics information.
 *
 *  \param [out] c
 *         AICS characteristics count.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_micp_error_code
 */
#define GA_mc_get_aics_context_info(                                    \
            /* IN - GA_ENDPOINT* */ d,                                  \
            /* IN - GA_MC_CONTEXT* */ h,                                \
            /* OUT - GA_BRR_SVC_RANGE** */r,                            \
            /* OUT:^5 - GA_CHAR_INFO** */i,                             \
            /* OUT - UINT16* */c                                        \
        )                                                               \
        GA_mc_manage_aics_context_info                                  \
        (                                                               \
            GA_FALSE,                                                   \
            (d),                                                        \
            (h),                                                        \
            (r),                                                        \
            (i),                                                        \
            (c)                                                         \
        )

/**
 *  \brief To save the AICS Context Information.
 *
 *  \par Description:
 *       This function enables to save the context information of AICS.
 *
 *  \param [in] d
 *         Remote Device Address.
 *
 *  \param [out] aics_h
 *         AICS Handle which is allocated during AICS context setup.
 *
 *  \param [out] r
 *         AICS characteristics handle range.
 *
 *  \param [out] i
 *         AICS characteristics information.
 *
 *  \param [out] c
 *         AICS characteristics count.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_micp_error_code
 */
#define GA_mc_set_aics_context_info(                                    \
            /* IN - GA_ENDPOINT* */ d,                                  \
            /* OUT - GA_MC_CONTEXT* */ h,                               \
            /* OUT - GA_BRR_SVC_RANGE** */r,                            \
            /* OUT:^5 - GA_CHAR_INFO** */i,                             \
            /* OUT - UINT16* */c                                        \
        )                                                               \
        GA_mc_manage_aics_context_info                                  \
        (                                                               \
            GA_TRUE,                                                    \
            (d),                                                        \
            (h),                                                        \
            (r),                                                        \
            (i),                                                        \
            (c)                                                         \
        )
#endif /* MICP_SUPPORT_CONTEXT_MANAGE */

/**
 * \endcond
 */

/**
 *  \brief Get the Optional MICP capabilities from the peer device.
 *
 *  \par Description:
 *       This function enables to discover the optional included services
 *       (i.e. AICS) from the remote device.
 *
 *  \param [in] mc_cntx
 *         Context associated with MICP.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h. \n
 *          If \ref GA_SUCCESS, \ref GA_MC_GET_CAPABILITIES_CNF is
 *          notified.
 *
 *  \note This procedure returns the \ref GA_MC_GET_CAPABILITIES_CNF event for
 *        each optional service instance discovered with event status
 *        \ref GA_CONTINUE. \n
 *        On completion of this procedure, \ref GA_MC_GET_CAPABILITIES_CNF
 *        event is notified with event status \ref GA_SUCCESS. \n
 *        Application/Upper Layer is expected use the information returned along with
 *        \ref GA_MC_GET_CAPABILITIES_CNF event for setting up the optional
 *        capabilities. \n
 *        The device must have performed MICP setup before calling
 *        this function. \n
 *        If AICS context has to be setup, \ref GA_mc_set_capability() has to
 *        be called with the service handle range received as part of this
 *        event.
 *
 *  \sa GA_MC_GET_CAPABILITIES_CNF
 *  \sa ga_micp_error_code
 */
GA_RESULT GA_mc_get_capabilities
          (
              /* IN */ GA_MC_CONTEXT * mc_cntx
          );

/**
 *  \brief Setup MICP optional capabiliy with the peer device.
 *
 *  \par Description:
 *       This routine allocates a MICP optional service context with a peer
 *       endpoint, discovers the optional(AICS) service charactersicstics and
 *       configures for notification.
 *
 *  \param [in] mctx
 *         MICP Context.
 *
 *  \param [in] svc
 *         Optional Service(AICS) Service details to Setup.
 *
 *  \param [out] cctx
 *         Context Allocated for optional service.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h. \n
 *          If \ref GA_SUCCESS, \ref GA_MC_SET_CAPABILITIES_CNF is
 *          notified.
 *
 *  \sa GA_MC_SET_CAPABILITIES_CNF
 *  \sa ga_micp_error_code
 */
GA_RESULT GA_mc_set_capability
          (
              /* IN */  GA_MC_CONTEXT   * mctx,
              /* IN */  GA_BRR_SVC_INFO * svc,
              /* OUT */ GA_MC_CONTEXT   * cctx
          );

/** \} */

/**
 * \name MICP Controller APIs - Release
 * \{
 * \brief This section describes the Microphone Control Profile Release APIs
 * for Microphone Controller.
 */

/**
 *  \brief Close or Release the given MICP context.
 *
 *  \par Description:
 *       When 'release' is set to \ref GA_TRUE, this routine initiates the
 *       release procedure for the context. Once release is done, the context
 *       is freed up and the setup must be freshly done by calling
 *       \ref GA_mc_setup() if required for the same device again. \n
 *       If the 'release' parameter is set to \ref GA_FALSE, this API just
 *       frees the context without the release procedure. Any associated
 *       AICS contexts should be freed by the application before
 *       calling this function.
 *
 *  \param [in] mctx
 *         MICP Context for the endpoint to be released/freed.
 *
 *  \param [in] release
 *         \ref GA_TRUE : Indicates release with freeing of context \n
 *         \ref GA_FALSE : Indicates only freeing of context
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *          If \ref GA_SUCCESS, \ref GA_MC_RELEASE_CNF is notified on
 *          completion with status as success or failure.
 *
 *  \sa GA_MC_RELEASE_CNF
 *  \sa ga_micp_error_code
 */
GA_RESULT GA_mc_terminate
          (
              /* IN */ GA_MC_CONTEXT * mctx,
              /* IN */ UCHAR           release
          );

/**
 *  \brief Release the given MICP context.
 *
 *  \par Description:
 *       This routine initiates the release procedure for the context. Once
 *       release is done, the context is freed up and the setup must be freshly
 *       done by calling \ref GA_mc_setup() if required for the same
 *       device again. \n Any associated AICS contexts should be released/freed
 *       by the application before calling this function.
 *
 *  \param [in] mctx
 *         MICP Context for the endpoint to be released.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *          If \ref GA_SUCCESS, \ref GA_MC_RELEASE_CNF is notified on
 *          completion with status as success or failure.
 *
 *  \sa GA_MC_RELEASE_CNF
 *  \sa ga_micp_error_code
 */
#define GA_mc_release(                                       \
            /* IN - GA_MC_CONTEXT* */ mctx                   \
        )                                                    \
        GA_mc_terminate                                      \
        (                                                    \
            (mctx),                                          \
            GA_TRUE                                          \
        )

/**
 *  \brief Free the given MICP context.
 *
 *  \par Description:
 *       This routine frees up the given context of the MICP. Any associated
 *       AICS contexts should be released/freed by the application before
 *       calling this function.
 *
 *  \param [in] mctx
 *         MICP Context for the endpoint to be freed.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_micp_error_code
 */
#define GA_mc_close(                                         \
            /* IN - GA_MC_CONTEXT* */ mctx                   \
        )                                                    \
        GA_mc_terminate                                      \
        (                                                    \
            (mctx),                                          \
            GA_FALSE                                         \
        )

/**
 *  \brief Close or Release the given AICS context.
 *
 *  \par Description:
 *       When 'release' is set to \ref GA_TRUE, this routine initiates the
 *       release procedure for the context. Once release is done, the context
 *       is freed up and the setup must be freshly done by calling
 *       \ref GA_mc_set_capability() if required for the same device again. \n
 *       If the 'release' parameter is set to \ref GA_FALSE, this API just
 *       frees the context without the release procedure.
 *
 *  \param [in] micp_aics_cntx
 *         AICS Context for the endpoint to be released/freed.
 *
 *  \param [in] release
 *         \ref GA_TRUE : Indicates release with freeing of context \n
 *         \ref GA_FALSE : Indicates only freeing of context
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *          If \ref GA_SUCCESS, \ref GA_MC_RELEASE_CAPABILITY_CNF is notified
 *          on completion with status as success or failure.
 *
 *  \sa GA_MC_RELEASE_CAPABILITY_CNF
 *  \sa ga_micp_error_code
 */
GA_RESULT GA_mc_terminate_capability
          (
              /* IN */ GA_MC_CONTEXT * micp_aics_cntx,
              /* IN */ UCHAR           release
          );

/**
 *  \brief Release the given AICS context.
 *
 *  \par Description:
 *       This routine initiates the release procedure for the context. Once
 *       release is done, the context is freed up and the setup must be freshly
 *       done by calling \ref GA_mc_set_capability() if required for the
 *       same device again.
 *
 *  \param [in] micp_aics_cntx
 *         AICS Context for the endpoint to be released.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *          If \ref GA_SUCCESS, \ref GA_MC_RELEASE_CAPABILITY_CNF is notified
 *          on completion with status as success or failure.
 *
 *  \sa GA_MC_RELEASE_CAPABILITY_CNF
 *  \sa ga_micp_error_code
 */
#define GA_mc_release_capability(                                       \
            /* IN - GA_MC_CONTEXT* */ micp_aics_cntx                    \
        )                                                               \
        GA_mc_terminate_capability                                      \
        (                                                               \
            (micp_aics_cntx),                                           \
            GA_TRUE                                                     \
        )

/**
 *  \brief Free the given AICS context.
 *
 *  \par Description:
 *       This routine frees up the given context of the AICS.
 *
 *  \param [in] micp_aics_cntx
 *         AICS Context for the endpoint to be freed.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_micp_error_code
 */
#define GA_mc_close_capability(                                         \
            /* IN - GA_MC_CONTEXT* */ micp_aics_cntx                    \
        )                                                               \
        GA_mc_terminate_capability                                      \
        (                                                               \
            (micp_aics_cntx),                                           \
            GA_FALSE                                                    \
        )

/** \} */

/**
 * \name MICP Controller APIs - Read
 * \{
 * \brief This section describes the Microphone Control Profile Read APIs
 * for Microphone Controller.
 */

/**
 *  \brief To get Mute Status Information.
 *
 *  \par Description:
 *       The routine enables to get Mute Status Information.
 *
 *  \param [in] s_ctx
 *         Context Handle associated with MICS.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h. \n
 *          If \ref GA_SUCCESS, Char is Mute \ref GA_MC_GET_MUTE_CNF is
 *          notified with associated data through the registered callback.
 *
 *  \sa GA_MC_GET_MUTE_CNF
 *  \sa ga_micp_error_code
 */
#define GA_mc_mics_get_mute(                                            \
            /* IN - MICP_HANDLE */ s_ctx                                \
        )                                                               \
        MICP_read_request                                               \
        (                                                               \
             (s_ctx),                                                   \
             (GA_MC_GET_MUTE_CNF)                                       \
        )

/**
 *  \brief To get Input State Information.
 *
 *  \par Description:
 *       The routine enables to get Input State Information.
 *
 *  \param [in] s_ctx
 *         Context Handle associated with AICS.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h. \n
 *          If \ref GA_SUCCESS \ref GA_MC_AICS_GET_INPUT_STATE_CNF is notified
 *          through the registered callback.
 *
 *  \sa ga_micp_cont_defs
 *  \sa ga_micp_error_code
 */
#define GA_mc_aics_get_input_state(                                    \
            /* IN - MICP_AICS_HANDLE */ s_ctx                          \
        )                                                              \
        MICP_aics_read_request                                         \
        (                                                              \
             (s_ctx),                                                  \
             (GA_MC_AICS_GET_INPUT_STATE_CNF)                          \
        )

/**
 *  \brief To get Gain Setting Property Information.
 *
 *  \par Description:
 *       The routine enables to get Gain Setting Property Information.
 *
 *  \param [in] s_ctx
 *         Context Handle associated with AICS.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h. \n
 *          If \ref GA_SUCCESS \ref GA_MC_AICS_GET_GAIN_SETTING_PROPRTY_CNF is
 *          notified through the registered callback.
 *
 *  \sa ga_micp_cont_defs
 *  \sa ga_micp_error_code
 */
#define GA_mc_aics_get_gain_setting_proprty(                           \
            /* IN - MICP_AICS_HANDLE */ s_ctx                          \
        )                                                              \
        MICP_aics_read_request                                         \
        (                                                              \
             (s_ctx),                                                  \
             (GA_MC_AICS_GET_GAIN_SETTING_PROPRTY_CNF)                 \
        )

/**
 *  \brief To get Input Type Information.
 *
 *  \par Description:
 *       The routine enables to get Input Type Information.
 *
 *  \param [in] s_ctx
 *         Context Handle associated with AICS.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h. \n
 *          If \ref GA_SUCCESS \ref GA_MC_AICS_GET_INPUT_TYPE_CNF is
 *          notified through the registered callback.
 *
 *  \sa ga_micp_cont_defs
 *  \sa ga_micp_error_code
 */
#define GA_mc_aics_get_input_type(                                     \
            /* IN - MICP_AICS_HANDLE */ s_ctx                          \
        )                                                              \
        MICP_aics_read_request                                         \
        (                                                              \
             (s_ctx),                                                  \
             (GA_MC_AICS_GET_INPUT_TYPE_CNF)                           \
        )

/**
 *  \brief To get Input Status Information.
 *
 *  \par Description:
 *       The routine enables to get Input State Status Information.
 *
 *  \param [in] s_ctx
 *         Context Handle associated with AICS.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h. \n
 *          If \ref GA_SUCCESS \ref GA_MC_AICS_GET_INPUT_STATUS_CNF is
 *          notified through the registered callback.
 *
 *  \sa ga_micp_cont_defs
 *  \sa ga_micp_error_code
 */
#define GA_mc_aics_get_input_status(                                   \
            /* IN - MICP_AICS_HANDLE */ s_ctx                          \
        )                                                              \
        MICP_aics_read_request                                         \
        (                                                              \
             (s_ctx),                                                  \
             (GA_MC_AICS_GET_INPUT_STATUS_CNF)                         \
        )

/**
 *  \brief To get Audio Input Description Information.
 *
 *  \par Description:
 *       The routine enables to get Audio Input Description Information.
 *
 *  \param [in] s_ctx
 *         Context Handle associated with AICS.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h. \n
 *          If \ref GA_SUCCESS \ref GA_MC_AICS_GET_AUDIO_INPUT_DESC_CNF is
 *          notified through the registered callback.
 *
 *  \sa ga_micp_cont_defs
 *  \sa ga_micp_error_code
 */
#define GA_mc_aics_get_audio_input_description(                        \
            /* IN - MICP_AICS_HANDLE */ s_ctx                          \
        )                                                              \
        MICP_aics_read_request                                         \
        (                                                              \
             (s_ctx),                                                  \
             (GA_MC_AICS_GET_AUDIO_INPUT_DESC_CNF)                     \
        )

/** \} */

/**
 * \name MICP Controller APIs - Write
 * \{
 * \brief This section describes the Microphone Control Profile Write APIs
 * for Microphone Controller.
 */

/**
 *  \brief To Set Mute Status as Unmuted
 *
 *  \par Description:
 *       The routine enables to set Mute Status as Unmuted.
 *
 *  \param [in] s_ctx
 *         Context Handle associated with MICS.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h. \n
 *          If \ref GA_SUCCESS \ref GA_MC_SET_MUTE_CNF is notified
 *          through the registered callback.
 *
 *  \sa MICS_CHR_VAL_NOT_MUTED
 *  \sa ga_micp_error_code
 */
#define GA_mc_mics_set_unmute(                                          \
            /* IN - MICP_HANDLE */ s_ctx                                \
        )                                                               \
        MICP_set_mute                                                   \
        (                                                               \
             (s_ctx),                                                   \
             (MICS_CHR_VAL_NOT_MUTED)                                   \
        )

/**
 *  \brief To Set Mute Status as Muted
 *
 *  \par Description:
 *       The routine enables to set Mute Status as Muted
 *
 *  \param [in] s_ctx
 *         Context Handle associated with MICS.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h. \n
 *          If \ref GA_SUCCESS \ref GA_MC_SET_MUTE_CNF is notified
 *          through the registered callback.
 *
 *  \sa MICS_CHR_VAL_MUTED
 *  \sa ga_micp_error_code
 */
#define GA_mc_mics_set_mute(                                            \
            /* IN - MICP_HANDLE */ s_ctx                                \
        )                                                               \
        MICP_set_mute                                                   \
        (                                                               \
             (s_ctx),                                                   \
             (MICS_CHR_VAL_MUTED)                                       \
        )

/**
 *  \brief To Set Mute Status as Disabled
 *
 *  \par Description:
 *       The routine enables to set Mute Status as Disabled
 *
 *  \param [in] s_ctx
 *         Context Handle associated with MICS.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h. \n
 *          If \ref GA_SUCCESS \ref GA_MC_SET_MUTE_CNF is notified
 *          through the registered callback.
 *
 *  \sa MICS_CHR_VAL_DISABLED
 *  \sa ga_micp_error_code
 */
#define GA_mc_mics_set_mute_disable(                                    \
            /* IN - MICP_HANDLE */ s_ctx                                \
        )                                                               \
        MICP_set_mute                                                   \
        (                                                               \
             (s_ctx),                                                   \
             (MICS_CHR_VAL_DISABLED)                                    \
        )

/**
 *  \brief To set Audio Input Description Information.
 *
 *  \par Description:
 *       The routine enables to set Audio Input Description Information.
 *
 *  \param [in] s_ctx
 *         Context Handle associated with AICS.
 *
 *  \param [in] aid
 *         Pointer to Audio Input Description Information.
 *
 *  \param [in] aidl
 *         Audio Input Description Length.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \note Since it is WriteWithoutResponse request,
 *        there is no response expected for this event.
 *
 *  \sa ga_micp_error_code
 */
#define GA_mc_aics_set_audio_input_description(                        \
            /* IN - MICP_AICS_HANDLE */ s_ctx,                         \
            /* IN:^3 - UCHAR* */ aid,                                  \
            /* IN - UCHAR */ aidl                                      \
        )                                                              \
        MICP_aics_set_audio_input_description                          \
        (                                                              \
             (s_ctx),                                                  \
             (aid),                                                    \
             (aidl)                                                    \
        )

/**
 *  \brief To Set Gain Setting Information.
 *
 *  \par Description:
 *       The routine enables to set Gain Setting Information.
 *
 *  \param [in] sh
 *         Context Handle associated with AICS.
 *
 *  \param [in] val
 *         Gain Setting Information. \n
 *            - Change_Counter.
 *            - Gain_setting.
 *            .
 *
 *  \param [in] len
 *         Length of Gain Setting Information.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h. \n
 *          If \ref GA_SUCCESS \ref GA_MC_AICS_CP_WT_CNF is
 *          notified through the registered callback.
 *
 *  \sa ga_micp_error_code
 */
#define GA_mc_aics_set_gain_setting(                                   \
            /* IN - MICP_AICS_HANDLE */ sh,                            \
            /* IN:^3 - UCHAR* */ val,                                   \
            /* IN - UINT16 */ len                                      \
        )                                                              \
        MICP_aics_cp_request                                           \
        (                                                              \
             (sh),                                                     \
             (AICS_CP_OP_SET_GAIN_SETTING),                            \
             (val),                                                    \
             (len)                                                     \
        )

/**
 *  \brief To Unmute.
 *
 *  \par Description:
 *       The routine enables to Unmute.
 *
 *  \param [in] sh
 *         Context Handle associated with AICS.
 *
 *  \param [in] val
 *         Unmute Information. \n
 *            - Change_Counter.
 *            .
 *
 *  \param [in] len
 *         Length of Unmute Information.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h. \n
 *          If \ref GA_SUCCESS \ref GA_MC_AICS_CP_WT_CNF is
 *          notified through the registered callback.
 *
 *  \sa ga_micp_error_code
 */
#define GA_mc_aics_unmute(                                   \
            /* IN - MICP_AICS_HANDLE */ sh,                            \
            /* IN:^3 - UCHAR* */ val,                                   \
            /* IN - UINT16 */ len                                      \
        )                                                              \
        MICP_aics_cp_request                                           \
        (                                                              \
             (sh),                                                     \
             (AICS_CP_OP_UNMUTE),                                      \
             (val),                                                    \
             (len)                                                     \
        )

/**
 *  \brief To Mute.
 *
 *  \par Description:
 *       The routine enables to Mute.
 *
 *  \param [in] sh
 *         Context Handle associated with AICS.
 *
 *  \param [in] val
 *         Mute Information. \n
 *            - Change_Counter.
 *            .
 *
 *  \param [in] len
 *         Length of Mute Information.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h. \n
 *          If \ref GA_SUCCESS \ref GA_MC_AICS_CP_WT_CNF is
 *          notified through the registered callback.
 *
 *  \sa ga_micp_error_code
 */
#define GA_mc_aics_mute(                                   \
            /* IN - MICP_AICS_HANDLE */ sh,                            \
            /* IN:^3 - UCHAR* */ val,                                   \
            /* IN - UINT16 */ len                                      \
        )                                                              \
        MICP_aics_cp_request                                           \
        (                                                              \
             (sh),                                                     \
             (AICS_CP_OP_MUTE),                                        \
             (val),                                                    \
             (len)                                                     \
        )

/**
 *  \brief To set Manual Gain Mode.
 *
 *  \par Description:
 *       The routine enables to Set Manual Gain Mode.
 *
 *  \param [in] sh
 *         Context Handle associated with AICS.
 *
 *  \param [in] val
 *         Set Manual Gain Mode Information. \n
 *            - Change_Counter.
 *            .
 *
 *  \param [in] len
 *         Length of Set Manual Gain Mode Information.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h. \n
 *          If \ref GA_SUCCESS \ref GA_MC_AICS_CP_WT_CNF is
 *          notified through the registered callback.
 *
 *  \sa ga_micp_error_code
 */
#define GA_mc_aics_set_manual_gain_mode(                               \
            /* IN - MICP_AICS_HANDLE */ sh,                            \
            /* IN:^3 - UCHAR* */ val,                                   \
            /* IN - UINT16 */ len                                      \
        )                                                              \
        MICP_aics_cp_request                                           \
        (                                                              \
             (sh),                                                     \
             (AICS_CP_OP_SET_MANUAL_GAIN_MODE),                        \
             (val),                                                    \
             (len)                                                     \
        )

/**
 *  \brief To set Automatic Gain Mode.
 *
 *  \par Description:
 *       The routine enables to Set Automatic Gain Mode.
 *
 *  \param [in] sh
 *         Context Handle associated with AICS.
 *
 *  \param [in] val
 *         Set Automatic Gain Mode Information. \n
 *            - Change_Counter.
 *            .
 *
 *  \param [in] len
 *         Length of Set Automatic Gain Mode Information.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h. \n
 *          If \ref GA_SUCCESS \ref GA_MC_AICS_CP_WT_CNF is
 *          notified through the registered callback.
 *
 *  \sa ga_micp_error_code
 */
#define GA_mc_aics_set_auto_gain_mode(                                 \
            /* IN - MICP_AICS_HANDLE */ sh,                            \
            /* IN:^3 - UCHAR* */ val,                                   \
            /* IN - UINT16 */ len                                      \
        )                                                              \
        MICP_aics_cp_request                                           \
        (                                                              \
             (sh),                                                     \
             (AICS_CP_OP_SET_AUTO_GAIN_MODE),                          \
             (val),                                                    \
             (len)                                                     \
        )

/** \} */
/** \} */
#endif /* MICP_CONTROLLER */

#ifdef MICP_DEVICE
/**
 * \defgroup ga_micp_dev_defs Microphone Device
 * \{
 * \brief This section describes the Microphone Control Profile APIs
 * for Microphone Device.
 */

/**
 * \name MICP Device APIs - Init
 * \{
 * \brief This section describes the Microphone Control Profile Init APIs
 * for Microphone Device.
 */

/**
 *  \brief Initialize the GA Microphone Control Server.
 *
 *  \par Description:
 *       This routine initializes GA Microphone Control Server.
 *
 *  \param [in] cb Application profile callback of type \ref GA_PROFILE_CB.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_micp_error_code
 */
#define GA_mc_server_init(                                   \
            /* IN - GA_PROFILE_CB */ cb                      \
        )                                                    \
        GA_module_init                                       \
        (                                                    \
            GA_MODULE_MICP,                                  \
            MICP_ROLE_SERVER,                                \
            (cb)                                             \
        )

/** \} */

/**
 * \name MICP Device APIs - De-Init
 * \{
 * \brief This section describes the Microphone Control Profile De-Init APIs
 * for Microphone Device.
 */

/**
 *  \brief Shutdown the GA Microphone Control Server.
 *
 *  \par Description:
 *       This routine shuts down GA Microphone Control Server.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_micp_error_code
 */
#define GA_mc_server_shutdown()                              \
        GA_module_shutdown                                   \
        (                                                    \
            GA_MODULE_MICP,                                  \
            MICP_ROLE_SERVER                                 \
        )

/** \} */

/**
 * \name MICP Device APIs - Init
 * \{
 */

/**
 *  \brief To register optional AICS service with MICS.
 *
 *  \par Description:
 *       This function enables to register optional AICS service.
 *       It will include the AICS service and add its characteristics.
 *
 *  \param [out] aics_hndle
 *         Allocated service Handle.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_micp_error_code
 */
#define GA_mc_register_aics(                                 \
            /* IN - UCHAR* */ aics_hndle                     \
        )                                                    \
        MICP_register_aics                                   \
        (                                                    \
            (aics_hndle)                                     \
        )

/** \} */

/**
 * \name MICP Device APIs - De-Init
 * \{
 */

/**
 *  \brief To unregister optional AICS service with MICS.
 *
 *  \par Description:
 *       This function enables to unregister optional AICS service.
 *
 *  \param [in] aics_hndle
 *         Allocated service Handle.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_micp_error_code
 */
#define GA_mc_unregister_aics(                              \
            /* IN - UCHAR */ aics_hndle                     \
        )                                                   \
        MICP_unregister_aics                                \
        (                                                   \
            (aics_hndle)                                    \
        )

/** \} */

/**
 * \name MICP Device APIs - Read/Write
 * \{
 * \brief This section describes the Microphone Control Profile Read/Write APIs
 * for Microphone Device.
 */

/**
 *  \brief To send response to incoming request.
 *
 *  \par Description:
 *       This function enables to send response to incoming request
 *       from the peer.
 *
 *  \param [in] d
 *         Peer Device Address Information.
 *
 *  \param [in] et
 *         Event type indicating response for read or write. \n
 *            - \ref GA_RSP_TYPE_RD.
 *            - \ref GA_RSP_TYPE_WT.
 *            .
 *
 *  \param [in] es
 *         Response status for the read/write operation.
 *
 *  \param [in] rd
 *         Response information for read/write operatios \ref MICP_RSP_INFO.
 *
 *  \param [in] rdl
 *         Response information size.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_micp_error_code
 */
#define GA_mc_send_rsp(                                                \
            /* IN - GA_ENDPOINT* */ d,                                 \
            /* IN - UCHAR */ et,                                       \
            /* IN - UINT16 */ es,                                      \
            /* IN:^5 - MICP_RSP_INFO* */ rd,                            \
            /* IN - UCHAR */ rdl                                       \
        )                                                              \
        MICP_send_rsp                                                  \
        (                                                              \
            (d),                                                       \
            (et),                                                      \
            (es),                                                      \
            (rd),                                                      \
            (rdl)                                                      \
        )

/** \} */

/**
 * \name MICP Device APIs - Notify
 * \{
 * \brief This section describes the Microphone Control Profile Profile Notify
 * APIs for Microphone Device.
 */

/**
 *  \brief Notify Mute Status Information.
 *
 *  \par Description:
 *       This routine enables to notify MICS Mute state Information to the
 *       specified peer device.
 *
 *  \param [in] ep
 *         Device Endpoint Address to be notified.
 *
 *  \param [in] c_info
 *         Mute Status Information.
 *
 *  \param [in] c_info_len
 *         Length of Mute Status Information.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_micp_dev_defs
 *  \sa ga_micp_error_code
 */
#define GA_mcd_notify_mics_mute_status(                                  \
            /* IN - GA_ENDPOINT* */ ep,                                  \
            /* IN:^3 - UCHAR* */ c_info,                                  \
            /* IN - UCHAR */ c_info_len                                  \
        )                                                                \
        MICP_notify_char                                                 \
        (                                                                \
             (ep),                                                       \
             (0x00),                                                     \
             (MICP_SERVICE_TYPE_MICS),                                   \
             (GA_CHAR_MICS_MUTE),                                        \
             (c_info),                                                   \
             (c_info_len)                                                \
        )

/**
 *  \brief Notify Audio Input state Information.
 *
 *  \par Description:
 *       This routine enables to notify Audio Input State Information to the
 *       specified peer device.
 *
 *  \param [in] ep
 *         Device Endpoint Address to be notified.
 *
 *  \param [in] si
 *         Service Instance associated with AICS.
 *
 *  \param [in] c_info
 *         Audio Input State Information. \n
 *            - Gain_Setting.
 *            - Mute.
 *            - Gain_Mode.
 *            - Change_Counter.
 *            .
 *
 *  \param [in] c_info_len
 *         Length of Audio Input State Information.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_micp_dev_defs
 *  \sa ga_micp_error_code
 */
#define GA_mcd_notify_aics_audio_input_state(                             \
            /* IN - GA_ENDPOINT* */ ep,                                   \
            /* IN - UCHAR */ si,                                          \
            /* IN:^4 - UCHAR* */ c_info,                                   \
            /* IN - UCHAR */ c_info_len                                   \
        )                                                                 \
        MICP_notify_char                                                  \
        (                                                                 \
             (ep),                                                        \
             (si),                                                        \
             (MICP_SERVICE_TYPE_AICS),                                    \
             (GA_CHAR_AICS_INPUT_STATE),                                  \
             (c_info),                                                    \
             (c_info_len)                                                 \
        )

/**
 *  \brief Notify Audio Input Status Information.
 *
 *  \par Description:
 *       This routine enables to notify Audio Input Status Information to the
 *       specified peer device.
 *
 *  \param [in] ep
 *         Device Endpoint Address to be notified.
 *
 *  \param [in] si
 *         Service Instance associated with AICS.
 *
 *  \param [in] c_info
 *         Audio Input Status Information.
 *
 *  \param [in] c_info_len
 *         Length of Audio Input Status Information.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_micp_dev_defs
 *  \sa ga_micp_error_code
 */
#define GA_mcd_notify_aics_audio_input_status(                            \
            /* IN - GA_ENDPOINT* */ ep,                                   \
            /* IN - UCHAR */ si,                                          \
            /* IN:^4 - UCHAR* */ c_info,                                   \
            /* IN - UCHAR */ c_info_len                                   \
        )                                                                 \
        MICP_notify_char                                                  \
        (                                                                 \
             (ep),                                                        \
             (si),                                                        \
             (MICP_SERVICE_TYPE_AICS),                                    \
             (GA_CHAR_AICS_INPUT_STATUS),                                 \
             (c_info),                                                    \
             (c_info_len)                                                 \
        )

/**
 *  \brief Notify Audio Input Description Information.
 *
 *  \par Description:
 *       This routine enables to notify Audio Input Description Information
 *       to the specified peer device.
 *
 *  \param [in] ep
 *         Device Endpoint Address to be notified.
 *
 *  \param [in] si
 *         Service Instance associated with AICS.
 *
 *  \param [in] c_info
 *         Audio Input Description Information.
 *
 *  \param [in] c_info_len
 *         Length of Audio Input Description Information.
 *
 *  \return ref GA_SUCCESS or one of the error codes as defined in \ref
 *          ga_micp_error_code
 *
 *  \sa ga_micp_dev_defs
 *  \sa ga_micp_error_code
 */
#define GA_mcd_notify_aics_audio_input_desc(                              \
            /* IN - GA_ENDPOINT* */ ep,                                   \
            /* IN - UCHAR */ si,                                          \
            /* IN:^4 - UCHAR* */ c_info,                                   \
            /* IN - UCHAR */ c_info_len                                   \
        )                                                                 \
        MICP_notify_char                                                  \
        (                                                                 \
             (ep),                                                        \
             (si),                                                        \
             (MICP_SERVICE_TYPE_AICS),                                    \
             (GA_CHAR_AICS_AUDIO_INPUT_DESC),                             \
             (c_info),                                                    \
             (c_info_len)                                                 \
        )

/** \} */
/** \} */
#endif /* MICP_DEVICE */
/** \} */
/** \} */
#endif /* GA_MICP */

#ifdef GA_CSIP
/**
 * \addtogroup ga_csip_module
 * \{
 */

/**
 * \defgroup ga_csip_api_sequences API Sequences
 * \{
 * \brief This section describes the EtherMind GA CSIP Layer API Sequences.
 */

/**
 * \defgroup ga_csip_api_seq API Sequences
 * \{
 * \brief This section describes the Coordinated Set Identification Profile
 * API Sequences.
 * MSC depicting the flow of APIs and Events.
 * \mscfile CSIP.signalling
 */

/** \} */
/** \} */

/**
 * \defgroup ga_csip_api_defs API Definitions
 * \{
 * \brief This section describes the Coordinated Set Identification Profile
 * APIs.
 */

#ifdef CSIP_COORDINATOR
/**
 * \defgroup ga_csip_setco_defs SetCoordinator
 * \{
 * \brief This section describes the Coordinated Set Identification Profile
 * APIs for SetCoordinator.
 */

/**
 * \name CSIP SetCoordinator APIs - Init
 * \{
 * \brief This section describes the Coordinated Set Identification Profile
 * Init APIs for SetCoordinator.
 */

/**
 *  \brief Initialize the GA Coordinated Set Client.
 *
 *  \par Description:
 *       This routine initializes GA Coordinated Set Client.
 *
 *  \param [in] cb Application profile callback of type \ref GA_PROFILE_CB.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_csip_error_code
 */
#define GA_cs_client_init(                                              \
            /* IN - GA_PROFILE_CB */ cb                                 \
        )                                                               \
        GA_module_init                                                  \
        (                                                               \
            GA_MODULE_CSIP,                                             \
            CSIP_ROLE_CLIENT,                                           \
            (cb)                                                        \
        )

/** \} */

/**
 * \name CSIP SetCoordinator APIs - De-Init
 * \{
 * \brief This section describes the Coordinated Set Identification Profile
 * De-Init APIs for SetCoordinator.
 */

/**
 *  \brief Shutdown the GA Coordinated Set Client.
 *
 *  \par Description:
 *       This routine shuts down GA Coordinated Set Client.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_csip_error_code
 */
#define GA_cs_client_shutdown()                                         \
        GA_module_shutdown                                              \
        (                                                               \
            GA_MODULE_CSIP,                                             \
            CSIP_ROLE_CLIENT                                            \
        )

/** \} */

/**
 * \name CSIP SetCoordinator APIs - Setup
 * \{
 * \brief This section describes the Coordinated Set Identification Profile
 * Setup APIs for SetCoordinator.
 */

/**
 *  \brief To Setup Coordinated Set Idenitfication Profile (CSIP) Context.
 *
 *  \par Description:
 *       This function enables to setup CSIP context with given device.
 *       Internally, CSIS Char/Desc is discovered, post which configuration
 *       of notification for applicable char is done.
 *
 *  \param [in] device
 *         Peer Device with which the context is setup.
 *
 *  \param [in] svc_info
 *         Service UUID and Range information.
 *
 *  \param [out] cs_context
 *         Allocated CSIP Context Handle.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \note For \ref GA_SUCCESS, \ref GA_CS_SETUP_CNF will be notified.
 *
 *  \sa ga_csip_error_code
 */
#define GA_cs_setup(                                                    \
            /* IN - GA_ENDPOINT* */ device,                             \
            /* IN - GA_BRR_SVC_INFO* */ svc_info,                       \
            /* OUT - CSIP_HANDLE* */ cs_context                         \
        )                                                               \
        CSIP_setup_context                                              \
        (                                                               \
            (device),                                                   \
            (svc_info),                                                 \
            (cs_context)                                                \
        )

/**
 * \cond EXCLUDE_PART
 */
#ifdef CSIP_SUPPORT_CONFIG_SELECTION
/**
 *  \brief To enable configuration for Characteristic Notifications.
 *
 *  \par Description:
 *       The routine enables to configure notifications for individual
 *       characteristics of CSIS service.
 *
 *  \param [in] config
 *         Bitmask for characteristics IDs.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_csip_error_code
 */
#define GA_cs_update_ntf_configuration(                                 \
            /* IN - UINT32 */ config                                    \
        )                                                               \
        CSIP_update_ntf_configuration                                   \
        (                                                               \
            (config)                                                    \
        )
#endif /* CSIP_SUPPORT_CONFIG_SELECTION */

#ifdef CSIP_SUPPORT_CONTEXT_MANAGE
/**
 *  \brief To retrieve the CSIS Context Information.
 *
 *  \par Description:
 *       This function enables to retrieve the context information of CSIS.
 *
 *  \param [in] d
 *         Remote Device Address.
 *
 *  \param [in] h
 *         CSIP Handle which is allocated during CSIS context setup.
 *
 *  \param [out] r
 *         CSIS characteristics handle range.
 *
 *  \param [out] i
 *         CSIS characteristics information.
 *
 *  \param [out] c
 *         CSIS characteristics count.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_csip_error_code
 */
#define GA_cs_get_context_info(                                         \
            /* IN - GA_ENDPOINT* */ d,                                  \
            /* IN - GA_CONTEXT* */ h,                                  \
            /* OUT - GA_BRR_SVC_RANGE** */r,                            \
            /* OUT:^5 - GA_CHAR_INFO** */i,                             \
            /* OUT - UINT16* */c                                        \
        )                                                               \
        CSIP_manage_csis_context_info                                   \
        (                                                               \
            GA_FALSE,                                                   \
            (d),                                                        \
            (h),                                                        \
            (r),                                                        \
            (i),                                                        \
            (c)                                                         \
        )

/**
 *  \brief To save the CSIS Context Information.
 *
 *  \par Description:
 *       This function enables to save the context information of CSIS.
 *
 *  \param [in] d
 *         Remote Device Address.
 *
 *  \param [out] h
 *         CSIP Handle which is allocated during CSIS context setup.
 *
 *  \param [out] r
 *         CSIS characteristics handle range.
 *
 *  \param [out] i
 *         CSIS characteristics information.
 *
 *  \param [out] c
 *         CSIS characteristics count.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_csip_error_code
 */
#define GA_cs_set_context_info(                                         \
            /* IN - GA_ENDPOINT* */ d,                                  \
            /* OUT - GA_CONTEXT* */ h,                                  \
            /* OUT - GA_BRR_SVC_RANGE** */r,                            \
            /* OUT:^5 - GA_CHAR_INFO** */i,                             \
            /* OUT - UINT16* */c                                        \
        )                                                               \
        CSIP_manage_csis_context_info                                   \
        (                                                               \
            GA_TRUE,                                                    \
            (d),                                                        \
            (h),                                                        \
            (r),                                                        \
            (i),                                                        \
            (c)                                                         \
        )
#endif /* CSIP_SUPPORT_CONTEXT_MANAGE */

/**
 * \endcond
 */

/**
 *  \brief To discover Coordinated Set Idenitfication Service (CSIS)
 *
 *  \par Description:
 *       This function discovers the CSIS in a given device. \n
 *       It triggers a Service discovery for CSIS on the remote device.
 *
 *  \param [in] device
 *         Peer Device on which the discovery is performed.
 *  \param [in] range
 *         Service Range as \ref GA_BRR_SVC_RANGE of the primary service
 *         if discovering CSIS as included service.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \note For \ref GA_SUCCESS, \ref GA_CS_DISCOVER_CNF will be notified. \n
 *        To setup a CSIS context, Call \ref GA_cs_setup().
 *
 *  \sa ga_csip_error_code
 */
#define GA_cs_discover(                                                 \
            /* IN - GA_ENDPOINT* */ device,                             \
            /* IN - GA_BRR_SVC_RANGE* */ range                          \
        )                                                               \
        CSIP_discover_csis                                              \
        (                                                               \
            (device),                                                   \
            (range)                                                     \
        )

/** \} */

/**
 * \name CSIP SetCoordinator APIs - Release
 * \{
 * \brief This section describes the Coordinated Set Identification Profile
 * Release APIs for SetCoordinator.
 */

/**
 *  \brief To Release the given CSIP context.
 *
 *  \par Description:
 *       This routine initiates the release procedure for the context. Once
 *       release is done, the context is freed up and the setup must be freshly
 *       done by calling \ref GA_cs_setup if required for the same
 *       device again.
 *
 *  \param [in] cs_context
 *         CSIP Context for the endpoint to be released.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h. \n
 *          If \ref GA_SUCCESS, \ref GA_CS_RELEASE_CNF is notified on
 *          completion with status as success or failure.
 *
 *  \sa ga_csip_error_code
 */
#define GA_cs_release(                                                  \
            /* IN - CSIP_HANDLE */ cs_context                           \
        )                                                               \
        CSIP_release_context                                            \
        (                                                               \
            (cs_context),                                               \
            GA_TRUE                                                     \
        )

/**
 *  \brief To Free the given CSIP context.
 *
 *  \par Description:
 *       This routine frees up the given context of the CSIP.
 *
 *  \param [in] cs_context
 *         CSIP Context for the endpoint to be freed.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_csip_error_code
 */
#define GA_cs_close(                                                    \
            /* IN - CSIP_HANDLE */ cs_context                           \
        )                                                               \
        CSIP_release_context                                            \
        (                                                               \
            (cs_context),                                               \
            GA_FALSE                                                    \
        )

/** \} */

/**
 * \name CSIP SetCoordinator APIs - Read
 * \{
 * \brief This section describes the Coordinated Set Identification Profile
 * Read APIs for SetCoordinator.
 */

/**
 *  \brief To get the SIRK from the context set member.
 *
 *  \par Description:
 *       This function reads the SIRK attribute from the set member pointed
 *       by the context.
 *
 *  \param [in] ch
 *         Allocated CISP Context Handle.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \note For \ref GA_SUCCESS, \ref GA_CS_SIRK_GET_CNF will be notified.
 *
 *  \sa ga_csip_error_code
 */
#define GA_cs_get_sirk(                                                 \
            /* IN - CSIP_HANDLE */ ch                                   \
        )                                                               \
        CSIP_get_value                                                  \
        (                                                               \
            (ch),                                                       \
            CSIP_SIRK_GET_CNF                                           \
        )

/**
 *  \brief To get the Set Size from the context set member.
 *
 *  \par Description:
 *       This function reads the Set Size attribute from the set member pointed
 *       by the context.
 *
 *  \param [in] ch
 *         Allocated CISP Context Handle.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \note For \ref GA_SUCCESS, \ref GA_CS_SETSIZE_GET_CNF will be notified.
 *
 *  \sa ga_csip_error_code
 */
#define GA_cs_get_setsize(                                              \
            /* IN - CSIP_HANDLE */ ch                                   \
        )                                                               \
        CSIP_get_value                                                  \
        (                                                               \
            (ch),                                                       \
            CSIP_SETSIZE_GET_CNF                                        \
        )

/**
 *  \brief To get the SetMember rank from the context set member.
 *
 *  \par Description:
 *       This function reads the SetMember rank attribute from the set member
 *       pointed by the context.
 *
 *  \param [in] ch
 *         Allocated CISP Context Handle.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \note For \ref GA_SUCCESS, \ref GA_CS_SETMEMBER_RANK_GET_CNF will be
 *        notified.
 *
 *  \sa ga_csip_error_code
 */
#define GA_cs_get_setmember_rank(                                       \
            /* IN - CSIP_HANDLE */ ch                                   \
        )                                                               \
        CSIP_get_value                                                  \
        (                                                               \
            (ch),                                                       \
            CSIP_SETMEMBER_RANK_GET_CNF                                 \
        )

/**
 *  \brief To get the SetMember Lock from the context set member.
 *
 *  \par Description:
 *       This function reads the SetMember Lock attribute from the set member
 *       pointed by the context.
 *
 *  \param [in] ch
 *         Allocated CISP Context Handle.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \note For \ref GA_SUCCESS, \ref GA_CS_SETMEMBER_LOCK_GET_CNF will be
 *        notified.
 *
 *  \sa ga_csip_error_code
 */
#define GA_cs_get_setmember_lock(                                       \
            /* IN - CSIP_HANDLE */ ch                                   \
        )                                                               \
        CSIP_get_value                                                  \
        (                                                               \
            (ch),                                                       \
            CSIP_SETMEMBER_LOCK_GET_CNF                                 \
        )

/** \} */

/**
 * \name CSIP SetCoordinator APIs - Write
 * \{
 * \brief This section describes the Coordinated Set Identification Profile
 * Write APIs for SetCoordinator.
 */

/**
 *  \brief To set the SetMember lock from the context set member.
 *
 *  \par Description:
 *       This function writes the SetMember lock attribute from the set member
 *       pointed by the context.
 *
 *  \param [in] ch
 *         Allocated CISP Context Handle.
 *
 *  \param [in] s
 *         Data for the attribute (Lock Value).
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \note For \ref GA_SUCCESS, \ref GA_CS_SETMEMBER_LOCK_SET_CNF will be
 *        notified.
 *
 *  \sa ga_csip_error_code
 */
#define GA_cs_set_setmember_lock(                                       \
            /* IN - CSIP_HANDLE */ ch,                                  \
            /* IN - UINT8* */ s                                         \
        )                                                               \
        CSIP_set_value                                                  \
        (                                                               \
            (ch),                                                       \
            CSIP_SETMEMBER_LOCK_SET_CNF,                                \
            &(s),                                                       \
            sizeof(UINT8)                                               \
        )

/** \} */
/** \} */
#endif /* CSIP_COORDINATOR */

#ifdef CSIP_MEMBER
/**
 * \defgroup ga_csip_setmem_defs SetMember
 * \{
 * \brief This section describes the Coordinated Set Identification Profile
 * APIs for SetMember.
 */

/**
 * \name CSIP SetMember APIs - Init
 * \{
 * \brief This section describes the Coordinated Set Identification Profile
 * Init APIs for SetMember.
 */

/**
 *  \brief Initialize the GA Coordinated Set Server.
 *
 *  \par Description:
 *       This routine initializes GA Coordinated Set Server.
 *
 *  \param [in] cb Application profile callback of type \ref GA_PROFILE_CB.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_csip_error_code
 */
#define GA_cs_server_init(                                              \
            /* IN - GA_PROFILE_CB */ cb                                 \
        )                                                               \
        GA_module_init                                                  \
        (                                                               \
            GA_MODULE_CSIP,                                             \
            CSIP_ROLE_SERVER,                                           \
            (cb)                                                        \
        )

/** \} */

/**
 * \name CSIP SetMember APIs - De-Init
 * \{
 * \brief This section describes the Coordinated Set Identification Profile
 * De-Init APIs for SetMember.
 */

/**
 *  \brief Shutdown the GA Coordinated Set Server.
 *
 *  \par Description:
 *       This routine shuts down GA Coordinated Set Server.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_csip_error_code
 */
#define GA_cs_server_shutdown()                                         \
        GA_module_shutdown                                              \
        (                                                               \
            GA_MODULE_CSIP,                                             \
            CSIP_ROLE_SERVER                                            \
        )

/** \} */

/**
 * \name CSIP SetMember APIs - Init
 * \{
 */

/**
 *  \brief To register a local CSIP set member instance.
 *
 *  \par Description:
 *       This function registers a local CSIP Set Member instance.
 *
 *  \param [out] handle
 *         Address to hold assigned member handle as in \ref CSIP_MEMBER_HANDLE.
 *
 *  \param [out] svc_id
 *         Service ID.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_csip_error_code
 */
#define GA_cs_register(                                                 \
            /* OUT - CSIP_MEMBER_HANDLE* */ handle,                     \
            /* OUT - GA_BRR_SVC_INST* */ svc_id                         \
        )                                                               \
        CSIP_register_member                                            \
        (                                                               \
            (handle),                                                   \
            (svc_id)                                                    \
        )

/** \} */

/**
 * \name CSIP SetMember APIs - Read/Write
 * \{
 * \brief This section describes the Coordinated Set Identification Profile
 * Read/Write APIs for SetMember.
 */

/**
 *  \brief To send response to incoming request.
 *
 *  \par Description:
 *       This function enables to send response to incoming request from the peer.
 *
 *  \param [in] d
 *         Peer Device Address Information.
 *
 *  \param [in] et
 *         Event type for which response is sent.
 *
 *  \param [in] es
 *         Response status for the read/write operation.
 *
 *  \param [in] rs
 *         Response information for read/write operatios \ref CISP_RSP_INFO.
 *
 *  \param [in] sz
 *         Response information size.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_csip_error_code
 */
#define GA_cs_send_response(                                            \
            /* IN - GA_ENDPOINT* */ d,                                  \
            /* IN - UCHAR */ et,                                        \
            /* IN - UINT16 */ es,                                       \
            /* IN:^5 - CSIP_RSP_INFO* */ rs,                            \
            /* IN - UCHAR */ sz                                         \
        )                                                               \
        CSIP_send_rsp                                                   \
        (                                                               \
            (d),                                                        \
            (et),                                                       \
            (es),                                                       \
            (rs),                                                       \
            (sz)                                                        \
        )

/** \} */

/**
 * \name CSIP SetMember APIs - Notify
 * \{
 * \brief This section describes the Coordinated Set Identification Profile
 * Notify APIs for SetMember.
 */

/**
 *  \brief To send Notifications - Set Member Lock.
 *
 *  \par Description:
 *       This function sends notifications if configured for Set Member Lock.
 *
 *  \param [in] d
 *         If NULL, Ntf to all connected CSIP sessions will be sent. \n
 *         Else, to the corresponsing address passed.
 *
 *  \param [in] ch
 *         CSIS Handle Identifier.
 *
 *  \param [in] s
 *         Data to be sent as part of the notification - UINT8.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_csip_error_code
 */
#define GA_cs_send_setmember_lock_ntf(                                  \
            /* IN - GA_ENDPOINT* */ d,                                  \
            /* IN - CSIP_MEMBER_HANDLE */ ch,                           \
            /* IN - UINT8* */ s                                         \
        )                                                               \
        CSIP_send_ntf                                                   \
        (                                                               \
            (d),                                                        \
            (ch),                                                       \
            GA_CHAR_CSIS_LOCK,                                          \
            &(s),                                                       \
            sizeof(UINT8)                                               \
        )

/**
 *  \brief To send Notifications - Set Identity Resolving Key.
 *
 *  \par Description:
 *       This function sends notifications if configured for SIRK.
 *
 *  \param [in] d
 *         If NULL, Ntf to all connected CSIP sessions will be sent. \n
 *         Else, to the corresponsing address passed.
 *
 *  \param [in] ch
 *         CSIS Handle Identifier.
 *
 *  \param [in] ntf_data
 *         Data to be sent as part of the notification.
 *
 *  \param [in] ntf_datalen
 *         Length of the data to be sent as part of the notification.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_csip_error_code
 */
#define GA_cs_send_sirk_ntf(                                            \
            /* IN - GA_ENDPOINT* */ d,                                  \
            /* IN - CSIP_MEMBER_HANDLE */ ch,                           \
            /* IN:^4 - UINT8* */ ntf_data,                              \
            /* IN - UINT16 */ ntf_datalen                               \
        )                                                               \
        CSIP_send_ntf                                                   \
        (                                                               \
            (d),                                                        \
            (ch),                                                       \
            GA_CHAR_CSIS_SIRK,                                          \
            (ntf_data),                                                 \
            (ntf_datalen)                                               \
        )

/**
 *  \brief To send Notifications - Coordinated Set Size.
 *
 *  \par Description:
 *       This function sends notifications if configured for
 *       Coordinated Set Size.
 *
 *  \param [in] d
 *         If NULL, Ntf to all connected CSIP sessions will be sent. \n
 *         Else, to the corresponsing address passed.
 *
 *  \param [in] ch
 *         CSIS Handle Identifier.
 *
 *  \param [in] s
 *         Data to be sent as part of the notification - UINT8.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_csip_error_code
 */
#define GA_cs_send_coord_set_size_ntf(                                  \
            /* IN - GA_ENDPOINT* */ d,                                  \
            /* IN - CSIP_MEMBER_HANDLE */ ch,                           \
            /* IN - UINT8* */ s                                         \
        )                                                               \
        CSIP_send_ntf                                                   \
        (                                                               \
            (d),                                                        \
            (ch),                                                       \
            GA_CHAR_CSIS_SIZE,                                          \
            &(s),                                                       \
            sizeof(UINT8)                                               \
        )

/** \} */
/** \} */
#endif /* CSIP_MEMBER */

/**
 * \defgroup ga_csip_common_defs Common
 * \{
 * \brief This section describes Common APIs for the
 * Coordinated Set Identification Profile.
 */

/**
 * \name CSIP Common APIs - RPA Operations
 * \{
 * \brief This section describes the Coordinated Set Identification Profile
 * Common APIs associated with RPA generation operations.
 */

/**
 *  \brief Start an RSI creation/verification.
 *
 *  \par Description:
 *       This routine is used to start an RSI Creation or Verification
 *       for a given SIRK and RSI (for verification).
 *
 *  \param [in] rsi Resolvable Set Identifier to verify. NULL to create one.
 *  \param [in] sirk Set Identity Resolving Key to create/verify RSI
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_brr_error_code
 */
GA_RESULT GA_cs_rsi_operate
          (
              /* IN:6 */ UCHAR * rsi,
              /* IN:16 */ UCHAR * sirk
          );

/**
 *  \brief Start an RSI creation.
 *
 *  \par Description:
 *       This routine is used to start an RSI Creation for a given SIRK.
 *       On successful start, this notifies the application
 *       with \ref GA_CS_RSI_CREATE_COMPLETE event.
 *
 *  \param [in] sirk Set Identity Resolving Key to create/verify RSI.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_brr_error_code
 */
#define GA_cs_rsi_create(                                               \
            /* IN:16 - UCHAR* */ sirk                                    \
        )                                                               \
        GA_cs_rsi_operate                                               \
        (                                                               \
            NULL,                                                       \
            (sirk)                                                      \
        )

/**
 *  \brief Start an RSI verification.
 *
 *  \par Description:
 *       This routine is used to start an RSI Verification for a given
 *       SIRK and RSI. On successful start, this notifies the application
 *       with \ref GA_CS_RSI_VERIFY_COMPLETE event.
 *
 *  \param [in] rsi Resolvable Set Identifier to verify.
 *  \param [in] sirk Set Identity Resolving Key to create/verify RSI.
 *
 *  \return \ref GA_SUCCESS or one of the error codes as defined in
 *          \ref GA_error.h.
 *
 *  \sa ga_brr_error_code
 */
#define GA_cs_rsi_verify(                                               \
            /* IN:6 - UCHAR* */ rsi,                                    \
            /* IN:16 - UCHAR* */ sirk                                   \
        )                                                               \
        GA_cs_rsi_operate                                               \
        (                                                               \
            (rsi),                                                      \
            (sirk)                                                      \
        )

/** \} */
/** \} */

/** \} */
/** \} */
#endif /* GA_CSIP */

/**
 * \addtogroup ga_cas_module
 * \{
 */

/**
 * \addtogroup ga_cas_api_defs
 * \{
 */

#ifdef CAP_CSIP_COORDINATOR
/**
 * \addtogroup ga_cas_client_defs
 * \{
 */
/**
 * \name CAS Client APIs - Utility
 * \{
 * \brief This section describes the CAP Set Utility APIs for Client.
 */

/* CAP Set Utility APIs */
GA_RESULT GA_cap_set_create
          (
              /* IN:16 */  UCHAR * sirk,
              /* IN */  UCHAR   size,
              /* OUT */ UINT8 * handle
          );

GA_RESULT GA_cap_set_delete
          (
              /* IN */ UINT8 handle
          );

GA_RESULT GA_cap_set_find_count
          (
              /* IN */ UINT8   handle,
              /* IN */ UINT8 * size,
              /* IN */ UINT8 * actual
          );

GA_RESULT GA_cap_set_find
          (
              /* IN:16 */ UCHAR * sirk,
              /* IN */  UCHAR   size,
              /* OUT */ UINT8 * handle
          );

GA_RESULT GA_cap_set_add_member
          (
              /* IN */ UINT8 handle,
              /* IN */ GA_ENDPOINT * device,
              /* IN */ UCHAR rank
          );

GA_RESULT GA_cap_set_remove_member
          (
              /* IN */ UINT8 handle,
              /* IN */ GA_ENDPOINT * device
          );

GA_RESULT GA_cap_set_lockprocedure
          (
              /* IN */ UINT8  handle,
              /* IN */ UINT8  value,
              /* IN */ UINT8  srank,
              /* IN */ UINT8  erank
          );

#define GA_cap_set_lockrequest(                                         \
            /* IN - UINT8 */ handle                                     \
        )                                                               \
        GA_cap_set_lockprocedure                                        \
        (                                                               \
            (handle),                                                   \
            CAP_SETOP_LOCKREQUEST,                                      \
            0U,                                                         \
            0U                                                          \
        )
#define GA_cap_set_lockrelease(                                         \
            /* IN - UINT8 */ handle                                     \
        )                                                               \
        GA_cap_set_lockprocedure                                        \
        (                                                               \
            (handle),                                                   \
            CAP_SETOP_LOCKRELEASE,                                      \
            0U,                                                         \
            0U                                                          \
        )
#define GA_cap_set_lockrequest_range(                                   \
            /* IN - UINT8 */ handle,                                    \
            /* IN - UINT8 */ srank,                                     \
            /* IN - UINT8 */ erank                                      \
        )                                                               \
        GA_cap_set_lockprocedure                                        \
        (                                                               \
            (handle),                                                   \
            CAP_SETOP_LOCKREQUEST,                                      \
            srank,                                                      \
            erank                                                       \
        )
#define GA_cap_set_lockrelease_range(                                   \
            /* IN - UINT8 */ handle,                                    \
            /* IN - UINT8 */ srank,                                     \
            /* IN - UINT8 */ erank                                      \
        )                                                               \
        GA_cap_set_lockprocedure                                        \
        (                                                               \
            (handle),                                                   \
            CAP_SETOP_LOCKRELEASE,                                      \
            srank,                                                      \
            erank                                                       \
        )
GA_RESULT GA_cap_fetch_member_from_device
          (
              /* IN */ UINT8         handle,
              /* IN */ GA_ENDPOINT * device,
              /* OUT */ UINT8      * index
          );

GA_RESULT GA_cap_set_orderedaccess
          (
              /* IN */ UINT8 handle,
              /* IN */ UINT8 start
          );

#define GA_cap_set_orderedaccess_begin(                                 \
            /* IN - UINT8 */ handle                                     \
        )                                                               \
        GA_cap_set_orderedaccess                                        \
        (                                                               \
            (handle),                                                   \
            GA_TRUE                                                     \
        )
#define GA_cap_set_orderedaccess_end(                                   \
            /* IN - UINT8 */ handle                                     \
        )                                                               \
        GA_cap_set_orderedaccess                                        \
        (                                                               \
            (handle),                                                   \
            GA_FALSE                                                    \
        )

GA_RESULT GA_cap_set_access_next_member
          (
              /* IN */ UINT8  handle,
              /* OUT */ GA_ENDPOINT * device
          );

GA_RESULT GA_cap_set_update_member
          (
              /* IN */ UINT8         handle,
              /* IN */ GA_ENDPOINT * device,
              /* IN */ UINT16        char_uuid,
              /* IN */ UINT8       * sm_data
          );

#define GA_cap_set_update_member_sirk(                                  \
            /* IN - UINT8 */ handle,                                    \
            /* IN - GA_ENDPOINT* */ device,                             \
            /* IN:16 - UINT8* */ sm_data                                \
        )                                                               \
        GA_cap_set_update_member                                        \
        (                                                               \
            (handle),                                                   \
            (device),                                                   \
            GA_CHAR_CSIS_SIRK,                                          \
            (sm_data)                                                   \
        )
#define GA_cap_set_update_member_size(                                  \
            /* IN - UINT8 */ handle,                                    \
            /* IN - GA_ENDPOINT* */ device,                             \
            /* IN:1 - UINT8* */ sm_data                                 \
        )                                                               \
        GA_cap_set_update_member                                        \
        (                                                               \
            (handle),                                                   \
            (device),                                                   \
            GA_CHAR_CSIS_SIZE,                                          \
            (sm_data)                                                   \
        )
#define GA_cap_set_update_member_lock(                                  \
            /* IN - UINT8 */ handle,                                    \
            /* IN - GA_ENDPOINT* */ device,                             \
            /* IN:1 - UINT8* */ sm_data                                 \
        )                                                               \
        GA_cap_set_update_member                                        \
        (                                                               \
            (handle),                                                   \
            (device),                                                   \
            GA_CHAR_CSIS_LOCK,                                          \
            (sm_data)                                                   \
        )

/** \} */
/** \} */
#endif /* CAP_CSIP_COORDINATOR */
/** \} */
/** \} */

#ifdef __cplusplus
};
#endif

/** \} */
/** \} */
/** \} */

#endif /* _H_GA_API_ */

