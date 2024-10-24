
/*
 *  \file sbc_common_internal.h
 *
 *  Comman internal header file of SBC encoder and decoder module.
 *  This file contains the data structures, type definitions, and MACROS
 *  declarations that the SBC encoder and decoder implementation uses
 *  internally.
 */

/*
 *  Copyright (C) 2013. Mindtree Ltd.
 *  All rights reserved.
 */

#ifndef _H_SBC_COMMON_INTERNAL_
#define _H_SBC_COMMON_INTERNAL_

/* ---------------------------------- Header File Inclusion */
#include "sbc_api.h"


/* ---------------------------------- SBC Debug Macros */
#ifdef SBC_DEBUG

#define SBC_DEBUG_DEVICE    stderr
#define SBC_TRC             fprintf
#define SBC_ERR             fprintf

#else  /* SBC_DEBUG */

#define SBC_DEBUG_DEVICE    stderr
#define SBC_TRC(...)
#define SBC_ERR(...)

#endif /* SBC_DEBUG */


/* ---------------------------------- Global Definitions */

#define SBC_MAX_16                        (INT16)0x7FFFL
#define SBC_MIN_16                        (INT16)0x8000L
#define SBC_MAX_32                        (INT32)0x7FFFFFFFL
#define SBC_MIN_32                        (INT32)0x80000000L

/* SBC Bitpool constant */
#define SBC_BITPOOL_MIN                   2
#define SBC_BITPOOL_MAX                   250
#define SBC_MAX_BITRATE_MONO              320
#define SBC_MAX_BITRATE_STEREO            512

/* SBC CRC constant */
#define SBC_CRC_HIGHBIT                   0x80
#define SBC_CRC_POLYN                     0x1D

/* SBC Bitpool constant */
#define SBC_MIN_BITPOOL                   2
#define SBC_MAX_BITPOOL                   250
#define SBC_MAX_BITRATE_MONO              320
#define SBC_MAX_BITRATE_STEREO            512


/* SBC Misc Constants */
#define mSBC_SYNCWORD                     0xAD
#define SBC_SYNCWORD                      0x9C

#define SBC_MULTIPLIER_8_80               -8
#define SBC_MULTIPLIER_4_40               -4
#define SBC_MASK_SAMPLING_FREQUECY        0xC0
#define SBC_MASK_BLOCKS                   0x30
#define SBC_MASK_CHANNEL_MODE             0x0C
#define SBC_MASK_ALLOCATION_METHOD        0x02
#define SBC_MASK_JOIN_INFO                0x80
#define SBC_MASK_SUBBAND                  0x01

/* Compilation switch to build for Cortex-M3 or M4 */
/* #define HAVE_CORTEX_MX_SUPPORT */

/* ---------------------------------- Macros */

/* Limit the 32 bit input to the range of a 16 bit word */
#define SBC_SATURATE_32(var_out, L_var1)                         \
{                                                                \
    var_out = (INT16) (L_var1);                                  \
}

/*
 *  Saturates a integer to a 16-bit signed number.
 *
 *  For Cortex-M3 or M4, disable the __asm define,
 *  and use the ANSI-C equivalent defined below.
 */
#ifndef HAVE_CORTEX_MX_SUPPORT
#define SBC_SATURATE_16(var1)                                    \
{                                                                \
    INT32 temp;                                                  \
    INT32 m = SBC_MAX_16;                                        \
    __asm __volatile("mov %0,%1,ASR #15\n    "                   \
                     "teq %0,%1,ASR #31\n    "                   \
                     "IT NE\n                "                   \
                     "eorne %1,%2,%0,ASR #31"                    \
                     :"=&r"(temp),"=&r"(var1)                    \
                     :"r"(m),"1"(var1),"0"(temp)                 \
                    );                                           \
}
#else
#define SBC_SATURATE_16(var1)                                    \
{                                                                \
    if((var1) > (INT16)0x7FFF)                                   \
    {                                                            \
        (var1) = (INT16)0x7FFF;                                  \
    }                                                            \
    else if((var1) < (INT16)0x8000)                              \
    {                                                            \
        (var1) = (INT16)0x8000;                                  \
    }                                                            \
    else                                                         \
    {                                                            \
        (var1) = (INT16)(var1);                                  \
    }                                                            \
}
#endif /* HAVE_CORTEX_MX_SUPPORT */

/*
 *  Multiply a 16 bit integer by a 32 bit. The multiplication
 *  result is divided by 2**15.
 */
#define SBC_MAC_32_16_Q15(L_var_out, L_32, M_32, n)              \
{                                                                \
    INT32 T_32;                                                  \
    SBC_MPY_32_16_Q15((T_32), (M_32), (n));                      \
    (L_var_out) = T_32 + (L_32);                                 \
}

/*
 *  Multiply a 32 bit integer by a 32 bit. The multiplication
 *  result is divided by 2**16
 */
#define SBC_MPY_32_Q15(L_32, M_32, N_32)                         \
{                                                                \
    INT32 L_low;                                                 \
    __asm __volatile(                                            \
                      "SMULL %0,%1,%2,%3"                        \
                      :"=&r"(L_low),"=&r"(L_32)                  \
                      :"r"(M_32),"r"(N_32)                       \
                    );                                           \
    (L_32) = ((L_32) << 16) | (((UINT32)L_low) >> 16);           \
}

/*
 * Multiply a 32-bit integer by a 16-bit integer and accumulate
 * the result in two 32-bit integers.
 */
#define SBC_MAC_32_16(L_32, H_32, M_32, n)                       \
{                                                                \
    INT32 N_32;                                                  \
    N_32=(INT32)n;                                               \
    __asm __volatile(                                            \
                      "SMLAL %0,%1,%2,%3"                        \
                      :"=&r"(L_32),"=&r"(H_32)                   \
                      :"r"(M_32),"r"(N_32),"0"(L_32),"1"(H_32)   \
                    );                                           \
}

/*
 * Multiply a 32-bit integer by a 32-bit integer and accumulate
 * the result in two 32-bit integers.
 */
#define SBC_MAC_32_32(L_32, H_32, M_32, n)                       \
{                                                                \
    __asm __volatile(                                            \
                      "SMLAL %0,%1,%2,%3"                        \
                      :"=&r"(L_32),"=&r"(H_32)                   \
                      :"r"(M_32),"r"(n),"0"(L_32),"1"(H_32)      \
                    );                                           \
}

/*
 * Multiply a 32-bit unsigned integer by a 16-bit unsigned integer and
 * accumulate the result in two 32-bit integers.
 */
#define SBC_UMAC_32_16(L_32, H_32, M_32, n)                      \
{                                                                \
    __asm __volatile(                                            \
                      "UMLAL %0,%1,%2,%3"                        \
                      :"=&r"(L_32),"=&r"(H_32)                   \
                      :"r"(M_32),"r"(n),"0"(L_32),"1"(H_32)      \
                    );                                           \
}

/* Multiply a 32-bit and a 16-bit unsigned values */
#define SBC_UMPY_32_16(L_32, H_32, M_32, n)                      \
{                                                                \
   __asm __volatile(                                             \
                     "UMULL %0,%1,%2,%3"                         \
                     :"=&r"(L_32),"=&r"(H_32)                    \
                     :"r"(M_32),"r"(n)                           \
                   );                                            \
}

/*
 *  Multiply a 16 bit integer by a 32 bit. The multiplication
 *  result is divided by 2**15.
 */
#define SBC_MPY_32_16_Q15(L_32, M_32, n)                         \
{                                                                \
    INT32 L_temp;                                                \
    __asm __volatile(                                            \
                      "SMULL %0,%1,%2,%3"                        \
                      :"=&r"(L_temp),"=&r"(L_32)                 \
                      :"r"(M_32),"r"(n)                          \
                    );                                           \
    (L_32) = ((L_32) << 17) | (((UINT32)L_temp) >> 15);          \
}

/*
 *  Multiply a 32-bit integer by a 16-bit. The result is in two
 *  32-bit integers.
 */
#define SBC_MPY_32_16(L_32, H_32, M_32, n)                       \
{                                                                \
    INT32 N_32;                                                  \
    N_32=(INT32)n;                                               \
    __asm __volatile(                                            \
                      "SMULL %0,%1,%2,%3"                        \
                      :"=&r"(L_32),"=&r"(H_32)                   \
                      :"r"(M_32),"r"(N_32)                       \
                    );                                           \
}

/*
 *  Multiply a 32-bit integer by a 32-bit. The result is in two
 *  32-bit integers.
 */
#define SBC_MPY_32_32(L_32, H_32, M_32, n)                       \
{                                                                \
   __asm __volatile (                                            \
                      "SMULL %0,%1,%2,%3"                        \
                      :"=&r"(L_32),"=&r"(H_32)                   \
                      :"r"(M_32),"r"(n)                          \
                    );                                           \
}

/* Rotates a 64-bit value right by 15 places */
#define SBC_LEFT_SHIFT_64_15(result, hi, lo)                     \
{                                                                \
    (result) = ((hi) << 17) | (((UINT32)(lo)) >> 15);            \
}

/* Rotates a 64-bit value right by 17 places */
#define SBC_LEFT_SHIFT_64_17(result, hi, lo)                     \
{                                                                \
    (result) = ((hi) << 15) | (((UINT32)(lo)) >> 17);            \
}

/* Add 0.5 (in Q30) format and rotates a 64-bit value by 30 places left */
#if (SBC_SPEED == SBC_INCLUDE_FEATURE)
#define SBC_LEFT_SHIFT_64_30(result, hi, lo)                     \
{                                                                \
    (result) = ((hi) << 2) | (((UINT32)(lo)) >> 30);             \
    (result) = (result) + 1;                                     \
}
#else  /* (SBC_SPEED == SBC_INCLUDE_FEATURE) */
#define SBC_LEFT_SHIFT_64_30(result, hi, lo)                     \
{                                                                \
    (result) = ((hi) << 3) | (((UINT32)(lo)) >> 29);             \
    (result) += 1;                                               \
    (result) >>= 1;                                              \
}
#endif /* (SBC_SPEED == SBC_INCLUDE_FEATURE) */

#define SBC_LEFT_SHIFT_64_7(result, hi, lo)                     \
{                                                               \
    (result) = ((hi) << 25) | (((UINT32)(lo)) >> 7);            \
}

/* ---------------------------------- External Variables */

/* ---------------------------------- Internal Function Declarations */

/* Calculate CRC */
#if 0
UCHAR sbc_calculate_8bit_crc
      (
          /* IN */  SBC_CODEC_PARAM * params,
          /* IN */  UCHAR *           msg,
          /* IN */  INT32             length
      );
#endif /* 0 */

/*
 *  This routine is used to calculate the Bitwise CRC summing for less
 *  than 8 bits.
 */
UCHAR sbc_calculate_crc
(
    UCHAR crc,
    UCHAR input
);

#endif /* _H_SBC_COMMON_INTERNAL_ */

