
/**
 *  \file cap.h
 *
 *  \brief This file defines the internal profile interfaces for CAP.
 */

/*
 *  Copyright (C) 2020. Mindtree Ltd.
 *  All rights reserved.
 */

#ifndef _H_CAP_
#define _H_CAP_


/* --------------------------------------------- Header File Inclusion */
#include "GA_api.h"

/* --------------------------------------------- Global Definitions */
/* BAP Event Definitions */

/* CSIP Event Definitions */

/* MICP Event Definitions */

/* VCP Event Definitions */

/* --------------------------------------------- Data types /Structures */

/* --------------------------------------------- Macros */

/* --------------------------------------------- APIs */
#if ((defined BAP_PACS_CLIENT) || (defined BAP_PACS_SERVER) || (defined BAP_BROADCAST_SOURCE) || (defined BAP_BROADCAST_SINK))
GA_RESULT cap_iface_process_bap_event
          (
              GA_ENDPOINT * device,
              UINT8 event_type,
              UINT16 status,
              void * data,
              UINT16 datalen
          );
#endif /* ((defined BAP_PACS_CLIENT) || (defined BAP_PACS_SERVER) || (defined BAP_BROADCAST_SOURCE) || (defined BAP_BROADCAST_SINK)) */

#ifdef VCP_CONTROLLER
GA_RESULT cap_iface_process_vcp_event
          (
              VCP_HANDLE *vctx,
              UINT8 event_type,
              UINT16 status,
              void * data,
              UINT16 datalen
          );
#endif /* VCP_CONTROLLER */

#ifdef VCP_RENDERER
GA_RESULT cap_iface_process_vcs_event
          (
              GA_ENDPOINT * device,
              UINT8 event_type,
              UINT16 status,
              void * data,
              UINT16 datalen
          );
#endif /* VCP_RENDERER */

#ifdef MICP_CONTROLLER
GA_RESULT cap_iface_process_micp_event
          (
              MICP_HANDLE * mctx,
              UINT8 event_type,
              UINT16 status,
              void   *data,
              UINT16 datalen
          );
#endif /* MICP_CONTROLLER */

#ifdef MICP_DEVICE
GA_RESULT cap_iface_process_mics_event
          (
              GA_ENDPOINT * device,
              UINT8         event_type,
              UINT16        status,
              void        * data,
              UINT16        datalen
          );
#endif /* MICP_CONTROLLER */

#ifdef CSIP_COORDINATOR
GA_RESULT cap_iface_process_csip_event
          (
              GA_ENDPOINT * device,
              UINT8 event_type,
              UINT16 status,
              void * data,
              UINT16 datalen
          );
#endif /* CSIP_COORDINATOR */

#ifdef CSIP_MEMBER
GA_RESULT cap_iface_process_csis_event
          (
              GA_ENDPOINT * device,
              UINT8         event_type,
              UINT16        status,
              void        * data,
              UINT16        datalen
          );
#endif /* CSIP_COORDINATOR */
#endif /* _H_CAP_ */




