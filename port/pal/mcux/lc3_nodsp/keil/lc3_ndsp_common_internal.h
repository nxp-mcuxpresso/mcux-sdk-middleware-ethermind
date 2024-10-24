
/**
 *  \file lc3_ndsp_common_internal.h
 *
 *  \brief  This file defines common internal definations
 */

/*
 *  Copyright (C) 2021. Mindtree Ltd.
 *  All rights reserved.
 */
#if defined(LC3_DSP) && (LC3_DSP == 0)
#ifndef _H_LC3_NDSP_COMMON_INTERNAL_
#define _H_LC3_NDSP_COMMON_INTERNAL_

/* --------------------------------------------- Header File Inclusion */
#include "EM_os.h"

#ifndef _ARM_MATH_H
#include "arm_math.h"
#endif

/* --------------------------------------------- Global Definitions */
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
#define LC3_BUFFER_SET(ptr, offset)  (void *)( (UINT8*)ptr + (((offset+3)>>2)<<2) )

#define LC3_ASSERT(test)  ((void)0)

#define LC3_MEMSET		memset
#define LC3_MEMCPY		memcpy
#define LC3_MEMMOVE		memmove

/* Depends on intrinsics */

/* Note : Replace these if abs(), max(),min() intrinsics available */
#define L_abs(x)             ((x)<0 ? -(x) : (x))
#define L_max(x, y)          ((x) >= (y) ? (x) : (y))
#define L_min(x, y)          ((x) <= (y) ? (x) : (y))

//#ifndef WIN32
/* gets exact 32 bit top from 47bit result of smull [32x16] */
static __inline  INT32 __SMULL_32_16(INT32 x, INT32 y)
{
#ifndef WIN32
    INT32  mh;
    INT32  ml;
#if __ARMCOMPILER_VERSION > 6000000
    __asm ("smull %0 ,%1, %2, %3"
    : "=r" (ml), "=r" (mh)
    : "r" (x), "r" (y));
#else
      __asm {
        smull ml, mh, x, ml;
    }
#endif

    mh = ( (mh)<<17) | (((UINT32)ml)>>15 );

    return mh;
#else
	__int64 prod = (__int64)x * y;
	return (INT32)(prod >> 15);	
#endif
}

//data is in the high 16-bits of y
//both x and y are unsigned int 
static __inline  UINT32 __MULL_32_16_T(UINT32 x, UINT32 y)
{
#ifndef WIN32
    UINT32  mh;
    UINT32  ml;
#if __ARMCOMPILER_VERSION > 6000000
    __asm ("umull %0 ,%1, %2, %3"
    : "=r" (ml), "=r" (mh)
    : "r" (x), "r" (y));
#else
      __asm {
    	umull ml, mh, x, ml;
    }
#endif
    return mh;
#else
	__int64 prod = (__int64)x * y;
	return (UINT32)(prod >> 32);	
#endif
}

/* gets exact 32 bit top from 63bit result of smull [32x32] */
static __inline  INT32 __SMULL_32_32(INT32 x, INT32 y)
{
#ifndef WIN32
    INT32  mh;
    INT32  ml;
#if __ARMCOMPILER_VERSION > 6000000
    __asm ("smull %0 ,%1, %2, %3"
    : "=r" (ml), "=r" (mh)
    : "r" (x), "r" (y));
#else
      __asm {
    	smull ml, mh, x, ml;
    }
#endif

    //mh = __QDADD(((UINT32)ml>>31), mh);
    mh = ( (mh)<<1) | (((UINT32)ml)>>31 );

    return mh;
#else
	__int64 prod = (__int64)x * y;
	return (INT32)(prod >> 31);	
#endif
}


static __inline  INT32 __MLA(INT32 x, INT32 y, INT32 a)
{
#ifndef WIN32
    INT32  sum;
#if __ARMCOMPILER_VERSION > 6000000
    __asm ("mla %0, %1, %2, %3"
    : "=r" (sum)
    : "r" (x), "r" (y), "r" (a));
#else
      __asm {
    	mla sum, x, y, a;
    }
#endif
    return sum;
#else
	INT32 prod = x * y + a;
	return prod;	
#endif
}

static __inline  INT32 __MUL(INT32 x, INT32 y)
{
#ifndef WIN32
    INT32  sum;
#if __ARMCOMPILER_VERSION > 6000000
    __asm ("mul %0, %1, %2"
    : "=r" (sum)
    : "r" (x), "r" (y));
#else
      __asm {
    	mul sum, x, y;
    }
#endif
    return sum;
#else
	INT32 prod = x * y;
	return prod;	
#endif
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
#ifndef WIN32
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
#else
	INT32 quot = ((INT32)var1 << 15) / var2;
    if (quot > 32767){
        return 32767;
    }
    else{
        return (INT16)quot;
    }
#endif
}

static __inline  INT32 __QADD_2(INT32 m, INT32 a, INT32 b)
{
#ifndef WIN32
	INT32 c;
#if __ARMCOMPILER_VERSION > 6000000
	__asm ("adds %0, %1, %2": "=r" (c): "r" (a), "r" (b));
	__asm ("eor %0, %1, #2": "=r" (c): "r" (m), "r" (c));
#else
      __asm {
    	adds c, a, b;
    }
     __asm {
    	eor c, m, c;
    }
#endif
	return (c);
#else
    return ((int32_t)(clip_q63_to_q31((q63_t)a + (q31_t)b)));
#endif
}


#ifndef WIN32

#ifndef __ARM_FEATURE_DSP
static __inline  INT32 __SMULBB(INT32 x, INT32 y)
{
    INT32  mh;
	INT32 x1, y1;
	x1 = (x << 16) >> 16;
	y1 = (y << 16) >> 16;

#if __ARMCOMPILER_VERSION > 6000000
    __asm ("mul %0, %1, %2"
    : "=r" (mh)
	  : "r" (x1), "r" (y1));
#else
      __asm {
    	mul mh, x1, y1;
    }
#endif
      return mh;
}

static __inline  INT32 __SMULBT(INT32 x, INT32 y)
{
    INT32  mh;
	INT32 x1, y1;
	x1 = (x << 16) >> 16;
	y1 = y >> 16;

#if __ARMCOMPILER_VERSION > 6000000
	__asm ("mul %0 ,%1, %2 "
    : "=r" (mh)
    : "r" (x1), "r" (y1));
#else
      __asm {
    	mul mh, x1, y1;
    }
#endif
    return mh;
}

static __inline  INT32 __SMULTB(INT32 x, INT32 y)
{
    INT32  mh;
	INT32 x1, y1;
	x1 = x >> 16;
	y1 = (y << 16) >> 16;
#if __ARMCOMPILER_VERSION > 6000000
	__asm ("mul %0 ,%1, %2 "
    : "=r" (mh)
    : "r" (x1), "r" (y1));
#else
      __asm {
    	mul mh, x1, y1;
    }
#endif
    return mh;
}

static __inline  INT32 __SMULTT(INT32 x, INT32 y)
{
    INT32  mh;
	INT32 x1, y1;
	x1 = x >> 16;
	y1 = y >> 16;
#if __ARMCOMPILER_VERSION > 6000000
	__asm ("MUL %0 ,%1, %2 "
    : "=r" (mh)
    : "r" (x1), "r" (y1));
#else
      __asm {
    	mul mh, x1, y1;
    }
#endif
    return mh;
}

static __inline  INT32 __SMLABB(INT32 x, INT32 y, INT32 z)
{
    INT32  sum;
	INT32 x1, y1;
	x1 = (x << 16) >> 16;
	y1 = (y << 16) >> 16;
#if __ARMCOMPILER_VERSION > 6000000
	__asm ("mla %0, %1, %2, %3"
    : "=r" (sum)
    : "r" (x1), "r" (y1), "r" (z));
#else
      __asm {
		mla sum, x1, y1, z;
    }
#endif
    return sum;
}

static __inline  INT32 __SMLABT(INT32 x, INT32 y, INT32 z)
{
    INT32  sum;
	INT32 x1, y1;
	x1 = (x << 16) >> 16;
	y1 = y >> 16;
#if __ARMCOMPILER_VERSION > 6000000
	__asm ("mla %0, %1, %2, %3"
    : "=r" (sum)
    : "r" (x1), "r" (y1), "r" (z));
#else
      __asm {
		mla sum, x1, y1, z;
    }
#endif
    return sum;
}

static __inline  INT32 __SMLATB(INT32 x, INT32 y, INT32 z)
{
    INT32  sum;
	INT32 x1, y1;
	x1 = x >> 16;
	y1 = (y << 16) >> 16;
#if __ARMCOMPILER_VERSION > 6000000
	__asm ("mla %0, %1, %2, %3"
    : "=r" (sum)
    : "r" (x1), "r" (y1), "r" (z));
#else
      __asm {
		mla sum, x1, y1, z;
    }
#endif
    return sum;
}

static __inline  INT32 __SMLATT(INT32 x, INT32 y, INT32 z)
{
    INT32  sum;
	INT32 x1, y1;
	x1 = x >> 16;
	y1 = y >> 16;
#if __ARMCOMPILER_VERSION > 6000000
	__asm ("mla %0, %1, %2, %3"
    : "=r" (sum)
    : "r" (x1), "r" (y1), "r" (z));
#else
      __asm {
		mla sum, x1, y1, z;
    }
#endif
    return sum;
}

static __inline  INT32 __SMULWB(INT32 x, INT32 y)
{
    INT32  mh;
    INT32  ml;
	ml = y << 16;
#if __ARMCOMPILER_VERSION > 6000000
	__asm ("smull %0 ,%1, %2, %3"
    : "=r" (ml), "=r" (mh)
    : "r" (x), "r" (ml));
#else
      __asm {
        smull ml, mh, x, ml;
    }
#endif
    return mh;
}

static __inline  INT32 __SMULWT(INT32 x, INT32 y)
{
    INT32  mh;
    INT32  ml;
#if __ARMCOMPILER_VERSION > 6000000
    __asm ("smull %0 ,%1, %2, %3"
    : "=r" (ml), "=r" (mh)
    : "r" (x), "r" (y));
#else
      __asm {
        smull ml, mh, x, y;
    }
#endif
    return mh;
}

static __inline  INT32 __SMLAWB(INT32 x, INT32 y, INT32 sum)
{
    INT32  mh;
    INT32  ml;

	ml = y << 16;
#if __ARMCOMPILER_VERSION > 6000000
	__asm ("smull %0 ,%1, %2, %3"
    : "=r" (ml), "=r" (mh)
    : "r" (x), "r" (ml));
#else
      __asm {
        smull ml, mh, x, ml;
    }
#endif
    return (mh + sum);
}

static __inline  INT32 __SMLAWT(INT32 x, INT32 y, INT32 sum)
{
    INT32  mh;
    INT32  ml;
#if __ARMCOMPILER_VERSION > 6000000
    __asm ("smull %0 ,%1, %2, %3"
    : "=r" (ml), "=r" (mh)
    : "r" (x), "r" (y));
#else
      __asm {
        smull ml, mh, x, y;
    }
#endif
    return (mh + sum);
}

static __inline  INT32 __SMMUL(INT32 x, INT32 y)
{
    INT32  mh;
    INT32  ml;
#if __ARMCOMPILER_VERSION > 6000000
    __asm ("smull %0 ,%1, %2, %3"
    : "=r" (ml), "=r" (mh)
    : "r" (x), "r" (y));
#else
      __asm {
        smull ml, mh, x, y;
    }
#endif
    return mh;
}


static __inline  INT32 __QDADD(INT32 x, INT32 y) {
	long long sum = (long long)y << 1;
	if (sum > 2147483647) {
		sum = 2147483647;
	}
	else if (sum < -2147483648ll) {
		sum = -2147483648ll;
	}

	sum += (long long)x;
	if (sum > 2147483647) {
		sum = 2147483647;
	}
	else if (sum < -2147483648ll) {
		sum = -2147483648ll;
	}

	return ((int32_t)sum);
}

static __inline  INT32 __QDSUB(INT32 x, INT32 y) {
	long long sum = (long long)y << 1;
	if (sum > 2147483647) {
		sum = 2147483647;
	}
	else if (sum < -2147483648ll) {
		sum = -2147483648ll;
	}

	sum =(long long)x - sum;
	if (sum > 2147483647) {
		sum = 2147483647;
	}
	else if (sum < -2147483648ll) {
		sum = -2147483648ll;
	}

	return ((int32_t)sum);
}


#endif //__ARM_FEATURE_DSP
#endif //WIN32

#endif /* _H_LC3_NDSP_COMMON_INTERNAL_ */
#endif /*defined(LC3_DSP) && (LC3_DSP == 0)*/
