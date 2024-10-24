
/**
 *  \file lc3_common_internal.h
 *
 *  \brief  This file defines common internal definations
 */

/*
 *  Copyright (C) 2021. Mindtree Ltd.
 *  All rights reserved.
 */

#ifndef _H_LC3_COMMON_INTERNAL_
#define _H_LC3_COMMON_INTERNAL_

/* --------------------------------------------- Header File Inclusion */
#include "LC3_api.h"

#if 1

static __inline INT32 ssat(INT32 x, INT32 y)
{
    INT32 ret;
#if __ARMCOMPILER_VERSION > 6000000
    __asm ("ssat %0, #16, %1": "=r" (ret) : "r" (x));
#else
      __asm {
        ssat ret, 16, x;
    }
#endif

    return ret;
}

static __inline INT32 clz(INT32 x)
{
    INT32 ret;
#if __ARMCOMPILER_VERSION > 6000000
    __asm ("clz %0, %1": "=r" (ret) : "r" (x));
#else
      __asm {
        clz ret, x;
    }
#endif
    return ret;
}

static __inline INT32 qadd(INT32 x, INT32 y)
{
    INT32 ret;
#if __ARMCOMPILER_VERSION > 6000000
    __asm ("qadd %0, %1, %2": "=r" (ret) : "r" (x), "r" (y));
#else
    __asm {
        qadd ret, x, y;
    }
#endif

    return ret;
}

static __inline INT32 qadd16(INT32 x, INT32 y)
{
    INT32 ret;
#if __ARMCOMPILER_VERSION > 6000000
    __asm ("qadd16 %0, %1, %2": "=r" (ret) : "r" (x), "r" (y));
#else
    __asm {
        qadd16 ret, x, y;
    }
#endif

    return ret;
}

static __inline INT32 qdadd(INT32 x, INT32 y)
{
    INT32 ret;
#if __ARMCOMPILER_VERSION > 6000000
    __asm ("qdadd %0, %1, %2": "=r" (ret) : "r" (x), "r" (y));
#else
    __asm {
        qdadd ret, x, y;
    }
#endif

    return ret;
}

static __inline INT32 qsub(INT32 x, INT32 y)
{
    INT32 ret;
#if __ARMCOMPILER_VERSION > 6000000
    __asm ("qsub %0, %1, %2": "=r" (ret) : "r" (x), "r" (y));
#else
    __asm {
        qsub ret, x, y;
    }
#endif
    return ret;
}


static __inline INT32 qsub16(INT32 x, INT32 y)
{
    INT32 ret;
#if __ARMCOMPILER_VERSION > 6000000
    __asm ("qsub16 %0, %1, %2": "=r" (ret) : "r" (x), "r" (y));
#else
    __asm {
        qsub16 ret, x, y;
    }
#endif
    return ret;
}

static __inline INT32 qdsub(INT32 x, INT32 y)
{
    INT32 ret;
#if __ARMCOMPILER_VERSION > 6000000
    __asm ("qdsub %0, %1, %2": "=r" (ret) : "r" (x), "r" (y));
#else
    __asm {
        qdsub ret, x, y;
    }
#endif
    return ret;
}


static __inline  INT32 smlad(INT32 x, INT32 y, INT32 a)
{
    INT32 ret;
#if __ARMCOMPILER_VERSION > 6000000
    __asm ("smlad %0, %1, %2, %3": "=r" (ret) : "r" (x), "r" (y), "r" (a));
#else
      __asm {
        smlad ret, x, y, a;
    }
#endif
    return ret;
}


static __inline  INT32 smulbb(INT32 x, INT32 y )
{
    INT32 ret;
#if __ARMCOMPILER_VERSION > 6000000
    __asm ("smulbb %0, %1, %2": "=r" (ret) : "r" (x), "r" (y));
#else
      __asm {
        smulbb ret, x, y;
    }
#endif
    return ret;
}

static __inline  INT32 smultt(INT32 x, INT32 y )
{
    INT32 ret;
#if __ARMCOMPILER_VERSION > 6000000
    __asm ("smultt %0, %1, %2": "=r" (ret) : "r" (x), "r" (y));
#else
    __asm {
        smultt ret, x, y;
    }
#endif
    return ret;
}

static __inline  INT32 smulbt(INT32 x, INT32 y )
{
    INT32 ret;
#if __ARMCOMPILER_VERSION > 6000000
    __asm ("smulbt %0, %1, %2": "=r" (ret) : "r" (x), "r" (y));
#else
    __asm {
        smulbt ret, x, y;
    }
#endif
    return ret;
}

static __inline  INT32 smultb(INT32 x, INT32 y )
{
    INT32 ret;
#if __ARMCOMPILER_VERSION > 6000000
    __asm ("smultb %0, %1, %2": "=r" (ret) : "r" (x), "r" (y));
#else
    __asm {
        smultb ret, x, y;
    }
#endif
    return ret;
}


static __inline  INT32 smlabb(INT32 x, INT32 y, INT32 a)
{
    INT32 ret;
#if __ARMCOMPILER_VERSION > 6000000
    __asm ("smlabb %0, %1, %2, %3": "=r" (ret) : "r" (x), "r" (y), "r" (a));
#else
    __asm {
        smlabb ret, x, y, a;
    }
#endif
    return ret;
}

static __inline  INT32 smlabt(INT32 x, INT32 y, INT32 a)
{
    INT32 ret;
#if __ARMCOMPILER_VERSION > 6000000
    __asm ("smlabt %0, %1, %2, %3": "=r" (ret) : "r" (x), "r" (y), "r" (a));
#else
    __asm {
        smlabt ret, x, y, a;
    }
#endif
    return ret;
}

static __inline  INT32 smlatb(INT32 x, INT32 y, INT32 a)
{
    INT32 ret;
#if __ARMCOMPILER_VERSION > 6000000
    __asm ("smlatb %0, %1, %2, %3": "=r" (ret) : "r" (x), "r" (y), "r" (a));
#else
    __asm {
        smlatb ret, x, y, a;
    }
#endif
    return ret;
}


static __inline  INT32 smlatt(INT32 x, INT32 y, INT32 a)
{
    INT32 ret;
#if __ARMCOMPILER_VERSION > 6000000
    __asm ("smlatt %0, %1, %2, %3": "=r" (ret) : "r" (x), "r" (y), "r" (a));
#else
    __asm {
        smlatt ret, x, y, a;
    }
#endif
    return ret;
}

static __inline  INT32 smulwb(INT32 x, INT32 y )
{
    INT32 ret;
#if __ARMCOMPILER_VERSION > 6000000
    __asm ("smulwb %0, %1, %2": "=r" (ret) : "r" (x), "r" (y));
#else
    __asm {
        smulwb ret, x, y;
    }
#endif
    return ret;
}

static __inline  INT32 smulwt(INT32 x, INT32 y )
{
    INT32 ret;
#if __ARMCOMPILER_VERSION > 6000000
    __asm ("smulwt %0, %1, %2": "=r" (ret) : "r" (x), "r" (y));
#else
    __asm {
        smulwt ret, x, y;
    }
#endif
    return ret;
}

static __inline  INT32 smlawb(INT32 x, INT32 y, INT32 a)
{
    INT32 ret;
#if __ARMCOMPILER_VERSION > 6000000
    __asm ("smlawb %0, %1, %2, %3": "=r" (ret) : "r" (x), "r" (y), "r" (a));
#else
    __asm {
        smlawb ret, x, y, a;
    }
#endif
    return ret;
}

static __inline  INT32 smlawt(INT32 x, INT32 y, INT32 a)
{
    INT32 ret;
#if __ARMCOMPILER_VERSION > 6000000
    __asm ("smlawt %0, %1, %2, %3": "=r" (ret) : "r" (x), "r" (y), "r" (a));
#else
    __asm {
        smlawt ret, x, y, a;
    }
#endif
    return ret;
}

static __inline  INT32 smmul(INT32 x, INT32 y)
{
    INT32 ret;
#if __ARMCOMPILER_VERSION > 6000000
    __asm ("smmul %0, %1, %2": "=r" (ret) : "r" (x), "r" (y));
#else
    __asm {
        smmul ret, x, y;
    }
#endif
    return ret;
}


static __inline  INT32 smmla(INT32 x, INT32 y, INT32 a)
{
    INT32 ret;
#if __ARMCOMPILER_VERSION > 6000000
    __asm ("smmla %0, %1, %2, %3": "=r" (ret) : "r" (x), "r" (y), "r" (a));
#else
    __asm {
        smmla ret, x, y, a;
    }
#endif
    return ret;
}



#define __QADD          qadd
#define __QDADD     qdadd
#define __QSUB          qsub
#define __QDSUB     qdsub

#define __QADD16        qadd16
#define __QSUB16        qsub16

#define __SSAT      ssat
#define __CLZ       clz

#define __SMULBB    smulbb
#define __SMULBT        smulbt
#define __SMULTT        smultt
#define __SMULTB        smultb
#define __SMULWB        smulwb
#define __SMULWT        smulwt

#define __SMLABB    smlabb
#define __SMLABT        smlabt
#define __SMLATT        smlatt
#define __SMLATB        smlatb
#define __SMLAWB        smlawb
#define __SMLAWT        smlawt

#define __SMLAD         smlad

#define __SMMUL         smmul
#define __SMMLA         smmla


#endif


/* --------------------------------------------- Global Definitions */
/* typedef          long long   INT64;   */
/* typedef unsigned long long   UINT64;  */

#define MAX_32 (INT32)0x7FFFFFFFL
#define MIN_32 (INT32)0x80000000L

#define MAX_16 (INT16)0x7FFF
#define MIN_16 (INT16)0x8000

/* TODO check 4 or 16 byte */
#if defined(__GNUC__)
#define DATA_ALIGN __attribute__((aligned(16)))
#elif defined(__CC_ARM)
#define DATA_ALIGN __align(16)
#elif defined(_MSC_VER)
#define DATA_ALIGN __declspec(align(16))
#else
#define DATA_ALIGN
#endif

#define PROPERTY_OPTIMIZE_NONE

/* TODO disable for if any max(), min() intrinsics */
#ifdef min
#undef min
#endif /* min */
#define min(a,b) (((a) < (b)) ? (a) : (b))   /*avoid error in mac*/

#ifdef max
#undef max
#endif /* max */
#define max(a,b) (((a) > (b)) ? (a) : (b))   /*avoid error in mac*/

/* #define LC3_BUFFER_SET(ptr, offset) (void *)((UINT8*)(ptr) + (offset)) */
#define LC3_BUFFER_SET(ptr, offset)  ((void *)( (UINT8*)(ptr) + ((((offset)+3)>>2)<<2)))

#define LC3_ASSERT(test)  ((void)0)

static __inline void lc3_memcpy(void *dst, const void *src, size_t n)
{
    memcpy(dst, src, n);
}

static __inline void lc3_memmove(void *dst, const void *src, size_t n)
{
    memmove(dst, src, n);
}

static __inline void lc3_memset(void *dst, INT32 val, size_t n)
{
    memset(dst, val, n);
}


/* Depends on intrinsics */

/* Note : Replace these if abs(), max(),min() intrinsics available */
#define L_abs(x)             ((x)<0 ? -(x) : (x))
#define L_max(x, y)          ((x) >= (y) ? (x) : (y))
#define L_min(x, y)          ((x) <= (y) ? (x) : (y))


/* gets exact 32 bit top from 47bit result of smull [32x16] */
static __inline  INT32 __SMULL_32_16(INT32 x, INT32 y)
{
    INT32  mh;
    INT32  ml;
#if 0
    asm volatile ("SMULL %0 ,%1, %2, %3"
    : "=r" (ml), "=r" (mh)
    : "r" (x), "r" (y));
#endif
#if 1
#if __ARMCOMPILER_VERSION > 6000000
    __asm  ("smull %0 ,%1, %2, %3"
                  : "=r" (ml), "=r" (mh)
                  : "r" (x), "r" (y));
#else
    __asm {
        smull ml, mh, x, y;
    }
#endif
#endif

    mh = ( (mh)<<17) | (((UINT32)ml)>>15 );

    return mh;
}

/* gets exact 32 bit top from 63bit result of smull [32x32] */
static __inline  INT32 __SMULL_32_32(INT32 x, INT32 y)
{
    INT32  mh;
    INT32  ml;
#if 0
    asm volatile ("SMULL %0 ,%1, %2, %3"
    : "=r" (ml), "=r" (mh)
    : "r" (x), "r" (y));
#endif
#if 1
#if __ARMCOMPILER_VERSION > 6000000
    __asm  ("smull %0 ,%1, %2, %3"
                  : "=r" (ml), "=r" (mh)
                  : "r" (x), "r" (y));
#else
    __asm {
        smull ml, mh, x, y;
    }
#endif
#endif

    mh = __QDADD(((UINT32)ml>>31), mh);

    return mh;
}

static __inline  INT32 __MLA(INT32 x, INT32 y, INT32 a)
{
    INT32  sum;
#if 0
    asm volatile ("MLA %0, %1, %2, %3"
    : "=r" (sum)
    : "r" (x), "r" (y), "r" (a));
#endif
#if 1
#if __ARMCOMPILER_VERSION > 6000000
    __asm ("mla %0, %1, %2, %3"
    : "=r" (sum)
    : "r" (x), "r" (y), "r" (a));
#else
    __asm {
        mla sum, x, y, a;
    }
#endif
#endif

    return sum;
}

static __inline  INT32 __MLS(INT32 x, INT32 y, INT32 a)
{
    INT32  sum;
#if 0
    asm volatile ("MLS %0, %1, %2, %3"
    : "=r" (sum)
    : "r" (x), "r" (y), "r" (a));
#endif
#if 1
#if __ARMCOMPILER_VERSION > 6000000
    __asm ("mls %0, %1, %2, %3"
    : "=r" (sum)
    : "r" (x), "r" (y), "r" (a));
#else
    __asm {
        mls sum, x, y, a;
    }
#endif
#endif

    return sum;
}

static __inline  INT32 __SMULWB_h(INT32 x, INT32 y)
{
    INT32  mh;
#if 0
    asm volatile ("SMULWB %0 ,%1, %2 "
    : "=r" (mh)
    : "r" (x), "r" (y));
#endif
#if 1
#if __ARMCOMPILER_VERSION > 6000000
    __asm  ("smulwb %0 ,%1, %2 "
    : "=r" (mh)
    : "r" (x), "r" (y));
#else
    __asm {
        smulwb mh, x, y;
    }
#endif
#endif

    return mh;
}

static __inline  INT32 __SMLAWB_h(INT32 x, INT32 y, INT32 z)
{
    INT32  mh;
#if 0
    asm volatile ("SMLAWB %0 ,%1, %2, %3 "
    : "=r" (mh)
    : "r" (x), "r" (y), "r" (z));
#endif
#if 1
#if __ARMCOMPILER_VERSION > 6000000
    __asm  ("smlawb %0 ,%1, %2, %3 "
    : "=r" (mh)
    : "r" (x), "r" (y), "r" (z));
#else
    __asm {
        smlawb mh, x, y, z;
    }
#endif
#endif

    return mh;
}

static __inline INT16 norm_s(INT16 var1)
{
    return __CLZ(var1 ^ ((INT32)var1 << 17)) & 15;
}

static __inline  INT16 norm_l(INT32 L_var1)
{
    return __CLZ(L_var1 ^ (L_var1 << 1)) & 31;
}

static __inline  INT16 norm_ul(INT32 L_var1)
{
    return __CLZ(L_var1) & 31;
}


/* A list of functions that need saturation can be find below marked with an _sat */


static __inline INT32 L_shl_sat(INT32 L_var1, INT16 var2)
{
    INT32 L_var_out = 0;

    if (var2 <= 0)
    {
        if (var2 < -32)
        {
            var2 = -32;
        }
        var2 = -var2;
        if (var2 >= 31)
        {
            L_var_out = (L_var1 < 0L) ? -1 : 0;
        }
        else
        {
            if (L_var1 < 0)
            {
                L_var_out = ~((~L_var1) >> var2);
            }
            else
            {
                L_var_out = L_var1 >> var2;
            }
        }
    }
    else
    {
        if (var2 > norm_l(L_var1))  /* L_var1==0 ?? ==> L_var_out = 0 */
        {
            if (L_var1 > 0)         /* +ve */
            {
                L_var_out = (MAX_32);
            }
            else if (L_var1 < 0)    /* -ve */
            {
                L_var_out = (MIN_32);
            }
            else
            {
                /* MISRA C-2012 Rule 15.7 */
            }
        }
        else
        {
            L_var_out = L_var1 << var2;
        }
    }
    return L_var_out;
}

static __inline INT32 L_shr_sat(INT32 L_var1, INT16 var2)
{
    INT32 L_var_out =0;

    if (var2 < 0)
    {
        if (var2 < -32)
        {    var2 = -32;  }

        var2 = -var2;


        if (var2 > norm_l(L_var1))  /* L_var1==0 ?? ==> L_var_out = 0 */
        {
            if (L_var1 > 0)         /* +ve */
            {
                L_var_out = (MAX_32);
            }
            else if (L_var1 < 0)    /* -ve */
            {
                L_var_out = (MIN_32);
            }
            else
            {
                /* MISRA C-2012 Rule 15.7 */
            }
        }
        else
        {
            L_var_out = L_var1 << var2;
        }
    }
    else
    {
        if (var2 >= 31)
        {
            L_var_out = (L_var1 < 0L) ? -1 : 0;
        }
        else
        {
            if (L_var1 < 0)
            {
                L_var_out = ~((~L_var1) >> var2);
            }
            else
            {
                L_var_out = L_var1 >> var2;
            }
        }
    }
    return L_var_out;
}

static __inline INT16 div_s(INT16 var1, INT16 var2)
{
    INT32 quot;
    LC3_ASSERT(var2 > 0);
    LC3_ASSERT(var1 >= 0);
    LC3_ASSERT(var1 <= var2);
    quot = 0x8000 * var1;

    quot /= var2;
    if (quot > 32767)
    {
        return 32767;
    }
    else
    {
        return (INT16)quot;
    }
}

#define div_l_unroll_1x( var_out,L_num,L_den)         \
        var_out = (var_out << 1);                     \
        L_num = (L_num << 1);                         \
        if (L_num >= L_den)                           \
        {   L_num = __QSUB(L_num,L_den);              \
            var_out = __QADD16(var_out,1);            \
        }                                             \

static __inline  INT16 div_l(INT32  L_num, INT16 den)
{
    INT32   var_out = (INT16)0;
    INT32   L_den;

    if (den == (INT16)0)
    {
        abort();
    }

    if ((L_num < (INT32)0) || (den < (INT16)0))
    {
        abort();
    }

    L_den = (den << 16);

    if (L_num >= L_den)
    {
        return MAX_16;
    }
    else
    {
        L_num = (L_num >> 1);
        L_den = (L_den >> 1);

        div_l_unroll_1x(var_out,L_num,L_den);
        div_l_unroll_1x(var_out,L_num,L_den);
        div_l_unroll_1x(var_out,L_num,L_den);
        div_l_unroll_1x(var_out,L_num,L_den);
        div_l_unroll_1x(var_out,L_num,L_den);
        div_l_unroll_1x(var_out,L_num,L_den);
        div_l_unroll_1x(var_out,L_num,L_den);
        div_l_unroll_1x(var_out,L_num,L_den);
        div_l_unroll_1x(var_out,L_num,L_den);
        div_l_unroll_1x(var_out,L_num,L_den);
        div_l_unroll_1x(var_out,L_num,L_den);
        div_l_unroll_1x(var_out,L_num,L_den);
        div_l_unroll_1x(var_out,L_num,L_den);
        div_l_unroll_1x(var_out,L_num,L_den);
        div_l_unroll_1x(var_out,L_num,L_den);

        return (INT16)(var_out);
    }
}

#endif /* _H_LC3_COMMON_INTERNAL_ */
