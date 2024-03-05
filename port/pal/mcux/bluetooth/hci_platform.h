
/**
 *  \file hci_platform.h
 *
 *  This files containes the definitins used by the HCI PLATFORM Transport Layer
 */

/* -------------------------------------------------------------------------- */
/*                           Copyright 2021-2022 NXP                          */
/*                            All rights reserved.                            */
/*                    SPDX-License-Identifier: BSD-3-Clause                   */
/* -------------------------------------------------------------------------- */

#ifndef _H_HCI_PLATFORM_
#define _H_HCI_PLATFORM_

/* -------------------------------------------------------------------------- */
/*                                  Includes                                  */
/* -------------------------------------------------------------------------- */
#include "BT_common.h"

/* -------------------------------------------------------------------------- */
/*                                Public macros                               */
/* -------------------------------------------------------------------------- */

#define HCI_PLATFORM_WR_BUF_SIZE           2048U
#define HCI_PLATFORM_MAX_PACKET_SIZE       264U

/* -------------------------------------------------------------------------- */
/*                              Public prototypes                             */
/* -------------------------------------------------------------------------- */

/** HCI PLATFORM Initialization & Shutdown */
void hci_platform_init (void);
void hci_platform_bt_init (void);
void hci_platform_bt_shutdown (void);

/* HCI PLATFORM Send Data */
API_RESULT hci_platform_send_data (UCHAR, UCHAR *, UINT16, UCHAR);
API_RESULT hci_transport_write_data (UCHAR, UCHAR *, UINT16, UCHAR);
void hci_platform_write_data(UCHAR *, UINT16);

#endif /* _H_HCI_PLATFORM_ */

