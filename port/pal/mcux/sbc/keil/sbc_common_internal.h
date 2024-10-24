
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

#define SBC_MAX_16                        (INT16)0x7FFF
#define SBC_MIN_16                        (INT16)0x8000
#define SBC_MAX_32                        (INT32)0x7FFFFFFF
#define SBC_MIN_32                        (INT32)0x80000000

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


/* ---------------------------------- Macros */
/*
 *  32 bits addition of the two 32 bits variables
 *  (L_var1 + L_var2) with overflow control and saturation.
 */
#define SBC_ADD_32(L_var_out, L_var1, L_var2)                   \
{                                                               \
    L_var_out = (L_var1) + (L_var2);                            \
}

/*
 *  32 bits subtraction of the two 32 bits variables
 *  (L_var1 - L_var2) with overflow control and saturation.
 */
#define SBC_SUB_32(L_var_out, L_var1, L_var2)                    \
{                                                                \
    L_var_out = (L_var1) - (L_var2);                             \
}

/* Limit the 32 bit input to the range of a 16 bit word */
#define SBC_SATURATE_32(var_out, L_var1)                         \
{                                                                \
    var_out = (INT16) (L_var1);                                  \
}

/* Multiplication of a 32-bit signed number with a 16-bit unsigned number */
#define SBC_USMPY_32_16(L_32, H_32, M_32, n)                     \
{                                                                \
    INT32 lo;                                                    \
    INT32 hi;                                                    \
                                                                 \
    hi = (M_32) >> 16;                                           \
    H_32 = hi * (n);                                             \
    lo = (M_32) & 0x0000FFFF;                                    \
    L_32 = (UINT32)lo * (UINT32)(n);                             \
    lo = ((UINT32)(L_32) >> 16) + (H_32);                        \
    L_32 = (L_32) + ((H_32) << 16);                              \
    H_32 = lo >> 16;                                             \
}

/*
 *  Multiply a 32 bit integer by a 32 bit (DPF) and accumulate
 *  with (normal) 32 bit integer. The multiplication result is
 *  divided by 2**16
 */
#define SBC_MPY_32_Q15(L_32, M_32, N_32)                         \
{                                                                \
    INT32 L_low;                                                 \
    INT32 L_high;                                                \
                                                                 \
    SBC_MPY_32_32(L_low, L_high, (M_32), (N_32));                \
    L_32 = ((L_high) << 16) | (((UINT32)L_low) >> 16);           \
}

/*
 *  Multiply a 16 bit integer by a 32 bit (DPF). The
 *  multiplication result is divided by 2**15.
 */
#define SBC_MAC_32_16_Q15(L_var_out, L_32, M_32, n)              \
{                                                                \
    INT32 T_32;                                                  \
    SBC_MPY_32_16_Q15((T_32), (M_32), (n));                      \
    (L_var_out) = T_32 + (L_32);                                 \
}

/*
 * Unsigned Multiplication and accumulation of a 32-bit number
 * with a 16-bit number
 */
#define SBC_UMAC_32_16(L_32, H_32, M_32, n)                      \
{                                                                \
    INT32 high, low;                                             \
    UINT32 carry;                                                \
                                                                 \
    SBC_UMPY_32_16(low, high, (M_32), (n));                      \
    carry = ((0xFFFFFFFF - (UINT32)low) <= (UINT32)(L_32));      \
    L_32 = (UINT32)(L_32) + (UINT32)low;                         \
    H_32 += high + (carry);                                      \
}

/*
 *  Multiply a 16 bit integer by a 32 bit (DPF). The result is
 *  divided by 2**15
 */
#define SBC_MPY_32_16_Q15(L_32, M_32, n)                         \
{                                                                \
    INT32 L_temp;                                                \
                                                                 \
    SBC_MPY_32_16_16BY16(L_temp, (L_32), (M_32), (n))            \
    SBC_LEFT_SHIFT_64_15((L_32), (L_32), L_temp);                \
}

/* Saturates a 32-bit integer to a 16-bit integer */
#define SBC_SATURATE_16(var1)                                    \
{                                                                \
    if(var1 > (INT16)0x7FFF)                                     \
    {                                                            \
        var1 = (INT16)0x7FFF;                                    \
    }                                                            \
    else if(var1 < (INT16)0x8000)                                \
    {                                                            \
        var1 = (INT16)0x8000;                                    \
    }                                                            \
    else                                                         \
    {                                                            \
        var1 = (INT16)(var1);                                    \
    }                                                            \
}

/* Unsigned multiplication of a 32-bit number with a 16-bit number */
#define SBC_UMPY_32_16(L_32, H_32, M_32, n)                      \
{                                                                \
    INT32 lo;                                                    \
    H_32 = ((UINT32)(M_32) >> 16) * (n);                         \
    L_32 = (UINT32)((M_32) & 0x0000FFFF) * (UINT32)(n);          \
    lo   = ((UINT32)L_32 >> 16) + (H_32);                        \
    L_32 = (L_32) + ((H_32) << 16);                              \
    H_32 = lo >> 16;                                             \
}

/* Signed multiplication of a 32-bit number with a 32-bit number */
#define SBC_MPY_32_32(L_32, H_32, M_32, N_32)               \
{                                                           \
    INT32 BD, AD_BC, AC;                                    \
                                                            \
    BD = ((M_32) & 0x0000FFFF) * ((N_32) & 0x0000FFFF);     \
    AD_BC = ((M_32) >> 16) * ((N_32) & 0x0000FFFF) +        \
            ((M_32) & 0x0000FFFF) * ((N_32) >> 16);         \
    AC = ((M_32) >> 16) * ((N_32) >> 16);                   \
    L_32 = BD + ((AD_BC) << 16);                            \
    H_32 = AC + ((AD_BC + ((BD >> 16) & 0x0000FFFF)) >> 16);\
}

/*
 *  Multiply a 32 bit integer by a 32 bit (DPF) and accumulate
 *  with (normal) 32 bit integer.
 */
#define SBC_MAC_32_32(L_32, H_32, M_32, n)                           \
{                                                                    \
    INT32 high, low;                                                 \
    SBC_MPY_32_32(low, high, (M_32), (n));                           \
    H_32 += high + (((0xFFFFFFFF - (UINT32)low) <= (UINT32)(L_32))); \
    L_32 += low;                                                     \
}

#define SBC_MAC_32_321(L_32, H_32, M_32, n)                        \
{                                                                  \
    INT32 high, low;                                               \
    SBC_MPY_32_32(low, high, (M_32), (n));                         \
    L_32 += low;                                                   \
    H_32 += high + ((UINT32)(L_32) < (UINT32)low);                 \
}

/*
 *  Multiply a 32-bit integer by a 16-bit. The 48-bit value is
 *  represented by two 32-bit values.
 */
#define SBC_MPY_32_16_16BY16(L_32, H_32, M_32, n)                \
{                                                                \
    INT32 lo;                                                    \
                                                                 \
    /*                                                           \
     * Multiply the 16-bit MSB of the 32-bit interger with       \
     * the 16-bit interger.                                      \
     */                                                          \
    H_32 = ((M_32) >> 16) * (n);                                 \
                                                                 \
    /*                                                           \
     * Multiply the 16-bit LSB of the 32-bit interger with       \
     * the 16-bit interger.                                      \
     */                                                          \
    L_32 = ((M_32) & 0x0000FFFF) * (n);                          \
                                                                 \
    lo   = ((L_32) >> 16) + (H_32);                              \
    L_32 = (L_32) + ((H_32) << 16);                              \
    H_32 = (lo >> 16);                                           \
}


#define SBC_MPY_32_16(L_32, H_32, M_32, n)                       \
{                                                                \
    INT32 lo;                                                    \
                                                                 \
    /*                                                           \
     * Multiply the 16-bit MSB of the 32-bit interger with       \
     * the 16-bit interger.                                      \
     */                                                          \
    (H_32) = ((M_32) >> 16) * (n);                               \
                                                                 \
    /*                                                           \
     * Multiply the 16-bit LSB of the 32-bit interger with       \
     * the 16-bit interger.                                      \
     */                                                          \
    (L_32) = ((M_32) & 0x0000FFFF) * (n);                        \
                                                                 \
    lo   = ((L_32) >> 16) + (H_32);                              \
    (L_32) = (L_32) + ((H_32) << 16);                            \
    (H_32) = (lo >> 16);                                         \
}


#define SBC_MPY_32_16_16BY13(L_32, H_32, M_32, n)                \
{                                                                \
    /*                                                           \
     * Multiply the 16-bit MSB of the 32-bit interger with       \
     * the 16-bit interger.                                      \
     */                                                          \
    H_32 = ((M_32) >> 13) * (n);                                 \
                                                                 \
    /*                                                           \
     * Multiply the 16-bit LSB of the 32-bit interger with       \
     * the 16-bit interger.                                      \
     */                                                          \
    L_32 = ((M_32) & 0x00001FFF) * (n);                          \
}

#define SBC_MPY_32_16_16By14(L_32, H_32, M_32, n)                \
{                                                                \
    /*                                                           \
     * Multiply the 16-bit MSB of the 32-bit interger with       \
     * the 16-bit interger.                                      \
     */                                                          \
    H_32 = ((M_32) >> 14) * (n);                                 \
                                                                 \
    /*                                                           \
     * Multiply the 16-bit LSB of the 32-bit interger with       \
     * the 16-bit interger.                                      \
     */                                                          \
    L_32 = ((M_32) & 0x00003FFF) * (n);                          \
}

/*
 *  Multiply a 32-bit integer by a 16-bit. The 48-bit value is
 *  represented by two 32-bit values. Accumulate this with the
 *  48-bit value represented by two 32-bit values
 */
#define SBC_MAC_32_16(L_32, H_32, M_32, n)                             \
{                                                                      \
    INT32 high, low;                                                   \
                                                                       \
    SBC_MPY_32_16_16BY16(low, high, (M_32), (n));                      \
    (H_32) += high + (((0xFFFFFFFF - (UINT32)low) <= (UINT32)(L_32))); \
    (L_32) += low;                                                     \
}

#define SBC_MAC_32_161(L_32, H_32, M_32, n)                      \
{                                                                \
    INT32 high, low;                                             \
                                                                 \
    SBC_MPY_32_16(low, high, (M_32), (n));                       \
    L_32 += low;                                                 \
    H_32 += high + ((UINT32)(L_32) < (UINT32)low);               \
}

/* Rotates a 64-bit value by 15 places left */
#define SBC_LEFT_SHIFT_64_15(result, hi, lo)                     \
{                                                                \
    result = ((hi) << 17) | (((UINT32)(lo)) >> 15);              \
}

/* Rotates a 64-bit value by 15 places left */
#define SBC_LEFT_SHIFT_64_14(result, hi, lo)                     \
{                                                                \
    result = ((hi) << 18) | (((UINT32)(lo)) >> 14);              \
}

/* Rotates a 64-bit value left by 17 places */
#define SBC_LEFT_SHIFT_64_17(result, hi, lo)                     \
{                                                                \
    result = ((hi) << 15) | (((UINT32)(lo)) >> 17);              \
}

/* Add 0.5 (in Q30) format and rotates a 64-bit value by 30 places left */
#define SBC_LEFT_SHIFT_64_30(result, hi, lo)                     \
{                                                                \
    result = (((hi) << 3) | (((UINT32)(lo)) >> 29)) + 1;         \
    result >>= 1;                                                \
}

/* ---------------------------------- External Variables */

/* ---------------------------------- Internal Function Declarations */
/* Calculate CRC */
UCHAR sbc_calculate_8bit_crc
      (
          /* IN */  SBC_CODEC_PARAM * params,
          /* IN */  UCHAR *           msg,
          /* IN */  INT32             length
      );

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

