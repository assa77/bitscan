/****************************************************************************
*
*	bitscan.h	Portable BitScan implementation
*			(for MSC, ICL, GNUC, etc. on IA32/Intel64/ARM only)
*
*****************************************************************************
*  Copyright (c) 2019 by Alexander M. Albertian <assa@4ip.ru>.
*  All rights reserved.
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <http://www.gnu.org/licenses/>.
****************************************************************************/

#ifndef _ASSA_BITSCAN_H_INCLUDED
#define _ASSA_BITSCAN_H_INCLUDED


#ifdef __cplusplus
# include <cstdint>
#else
# include <stdint.h>
#endif


#ifndef __INTEL_COMPILER
# ifdef __ICL
#  define __INTEL_COMPILER	__ICL
# elif defined( __ICL__ )
#  define __INTEL_COMPILER	__ICL__
# endif
#endif

#if defined( __INTEL_COMPILER ) && !defined( __ICL )
# define __ICL			__INTEL_COMPILER
#endif

#if defined( __INTEL_COMPILER ) && !defined( __ICL__ )
# define __ICL__		__INTEL_COMPILER
#endif


/*
* TODO: Complete ARM features detection: word size, compatible with types.h,
*	check endianness (__ARMEB__ for BE, __ARM_EABI__, __EABI__, __VFP_FP__,
*	_WIN32_WCE, ANDROID for ME)
*/
#ifdef _IS_ARM64
# undef _IS_ARM64
#endif

#ifdef _IS_ARM
# undef _IS_ARM
#endif

#ifdef _IS_THUMB
# undef _IS_THUMB
#endif

#ifdef _IS_IN_THUMB
# undef _IS_IN_THUMB
#endif

#ifndef _M_ARM
# ifdef __ARM_ARCH
#  define _M_ARM		__ARM_ARCH
# elif defined( __TARGET_ARCH_ARM )
#  define _M_ARM		__TARGET_ARCH_ARM
# endif
#endif

#if !defined( _M_ARMT ) && defined( __TARGET_ARCH_THUMB )
# define _M_ARMT		__TARGET_ARCH_THUMB
#endif

#ifdef __aarch64__
# define _IS_ARM64		__aarch64__
#elif defined( _M_ARM64 )
# define _IS_ARM64		_M_ARM64
#endif

#if defined( __ARM_ARCH_7__ ) \
	|| defined( __ARM_ARCH_7A__ ) \
	|| defined( __ARM_ARCH_7R__ ) \
	|| defined( __ARM_ARCH_7M__ ) \
	|| defined( __ARM_ARCH_7S__ ) \
	|| defined( __ARMV7__ )
# define _IS_ARM		7
#elif defined( __ARM_ARCH_6__ ) \
	|| defined( __ARM_ARCH_6J__ ) \
	|| defined( __ARM_ARCH_6K__ ) \
	|| defined( __ARM_ARCH_6Z__ ) \
	|| defined( __ARM_ARCH_6ZK__ ) \
	|| defined( __ARM_ARCH_6T2__ ) \
	|| defined( __ARMV6__ )
# define _IS_ARM		6
#elif defined( __ARM_ARCH_5__ ) \
	|| defined( __ARM_ARCH_5E__ ) \
	|| defined( __ARM_ARCH_5T__ ) \
	|| defined( __ARM_ARCH_5TE__ ) \
	|| defined( __ARM_ARCH_5TEJ__ ) \
	|| defined( __ARMV5__ ) \
	|| defined( __MARM_ARMV5__ )
# define _IS_ARM		5
#elif defined( __ARM_ARCH_4__ ) \
	|| defined( __ARM_ARCH_4T__ ) \
	|| defined( __ARMV4__ ) \
	|| defined( __MARM_ARMV4__ ) \
	|| defined( __MARM_ARM4__ ) \
	|| defined( __TARGET_ARM_4T__ )
# define _IS_ARM		4
#elif defined( __ARM_ARCH_3__ ) \
	|| defined( __ARM_ARCH_3M__ ) \
	|| defined( __ARMV3__ )
# define _IS_ARM		3
#elif defined( __ARM_ARCH_2__ ) \
	|| defined( __ARMV2__ )
# define _IS_ARM		2
#elif defined( _M_ARM )
# define _IS_ARM		_M_ARM
#elif defined( __arm__ )
# define _IS_ARM		1
#elif defined( arm )
# define _IS_ARM		1
#elif defined( _ARM_ )
# define _IS_ARM		1
#elif defined( ARM )
# define _IS_ARM		1
#endif

#if defined( __ARM_ARCH_6T2__ ) \
	|| defined( __ARM_ARCH_7__ ) \
	|| defined( __ARM_ARCH_7A__ ) \
	|| defined( __ARM_ARCH_7M__ ) \
	|| defined( __ARM_ARCH_7R__ ) \
	|| defined( __ARM_ARCH_7S__ )
# define _IS_THUMB		4
#elif defined( __ARM_ARCH_6J__ ) \
	|| defined( __ARM_ARCH_6K__ ) \
	|| defined( __ARM_ARCH_6Z__ ) \
	|| defined( __ARM_ARCH_6ZK__ ) \
	|| defined( __ARM_ARCH_6M__ )
# define _IS_THUMB		3
#elif defined( __ARM_ARCH_5T__ ) \
	|| defined( __ARM_ARCH_5TE__ ) \
	|| defined( __ARM_ARCH_5TEJ__ )
# define _IS_THUMB		2
#elif defined( __ARM_ARCH_4T__ ) \
	|| defined( __TARGET_ARM_4T__ )
# define _IS_THUMB		1
#elif defined( _IS_ARM ) && _IS_ARM >= 7
# define _IS_THUMB		_IS_ARM
#elif defined( _M_ARMT )
# define _IS_THUMB		0/*_M_ARMT*/
#elif defined( __thumb__ )
# define _IS_THUMB		0/*__thumb__*/
#endif

#if defined( _M_ARMT ) || defined( __thumb__ )
# define _IS_IN_THUMB		1
#endif

#if defined( _IS_THUMB ) && !defined( _IS_ARM )
# define _IS_ARM		1
#endif


/*
* Check the target architecture, e.g.:
*  https://sourceforge.net/p/predef/wiki/Architectures/
*  https://www.boost.org/doc/libs/1_58_0/libs/predef/doc/html/predef/reference/boost_arch_architecture_macros.html
*/
#ifdef _IS_BITSCAN64
# undef _IS_BITSCAN64
#endif

#ifdef _IS_BITSCAN32
# undef _IS_BITSCAN32
#endif

#ifdef _IS_BITSCANF32
# undef _IS_BITSCANF32
#endif

#ifdef _IS_BITSCANR32
# undef _IS_BITSCANR32
#endif

#ifdef _BSF32
# undef _BSF32
#endif

#ifdef _BSR32
# undef _BSR32
#endif

#ifdef _BSF64
# undef _BSF64
#endif

#ifdef _BSR64
# undef _BSR64
#endif

#if defined( _MSC_VER ) && _MSC_VER >= 1400

/* Intrinsic versions */
# include <intrin.h>

/* Prototypes: */
/*  unsigned char _BitScanForward( unsigned long *_Index, unsigned long _Mask ); */
/*  unsigned char _BitScanReverse( unsigned long *_Index, unsigned long _Mask ); */
# define _BSF32( __i, __m )	_BitScanForward( ( __i ), ( __m ) )
# define _BSR32( __i, __m )	_BitScanReverse( ( __i ), ( __m ) )
# define _IS_BITSCANF32		1
# define _IS_BITSCANR32		1

# ifdef _WIN64
#  ifndef WORDSIZE
#   define WORDSIZE		64
#  endif
/* or # if defined( _M_X64 ) || defined( _M_ARM64 ) || defined( _M_IA64 ) */
/* Prototypes: */
/*  unsigned char _BitScanForward64( unsigned long *_Index, unsigned __int64 _Mask ); */
/*  unsigned char _BitScanReverse64( unsigned long *_Index, unsigned __int64 _Mask ); */
#  define _BSF64( __i, __m )	_BitScanForward64( ( __i ), ( __m ) )
#  define _BSR64( __i, __m )	_BitScanReverse64( ( __i ), ( __m ) )
#  define _IS_BITSCAN64		1
# else
#  ifndef WORDSIZE
#   define WORDSIZE		32
#  endif
# endif

# ifndef __WORDSIZE
#  define __WORDSIZE		WORDSIZE
# endif
# if __WORDSIZE != WORDSIZE
#  undef WORDSIZE
#  define WORDSIZE		__WORDSIZE
# endif

#elif defined( __GNUC__ ) || defined( __INTEL_COMPILER )

# if defined( __amd64__ ) || defined( __amd64 ) || defined( __x86_64__ ) ||\
	defined( __x86_64 ) || defined( _M_AMD64 ) || defined( _M_X64 ) ||\
	defined( M_X64 )

static __inline__ __attribute__ ((__always_inline__))
unsigned char _BitScanForward( unsigned *i, uint32_t m )
{
	register uint32_t tmp;
	register uint8_t nzf;
	__asm__ (
#  ifdef INTEL_SYNTAX
#   ifdef __INTEL_COMPILER
		"bsf	%1,%2\n\t"
		"setnz	%0"
#   else
		"bsfl	%1,%2\n\t"
		"setnz	%0"
#   endif
#  else
		"bsfl	%2,%1\n\t"
		"setnz	%0"
#  endif
		: "=r" ( nzf ), "=r" ( tmp )
		: "rm" ( m )
		:
		);
	*i = tmp;
	return nzf;
}

static __inline__ __attribute__ ((__always_inline__))
unsigned char _BitScanForward64( unsigned *i, uint64_t m )
{
	register uint64_t tmp;
	register uint8_t nzf;
	__asm__ (
#  ifdef INTEL_SYNTAX
		"bsfq	%1,%2\n\t"
		"setnz	%0"
#  else
		"bsfq	%2,%1\n\t"
		"setnz	%0"
#  endif
		: "=r" ( nzf ), "=r" ( tmp )
		: "rm" ( m )
		:
		);
	*i = ( unsigned )tmp;
	return nzf;
}

static __inline__ __attribute__ ((__always_inline__))
unsigned char _BitScanReverse( unsigned *i, uint32_t m )
{
	register uint32_t tmp;
	register uint8_t nzf;
	__asm__ (
#  ifdef INTEL_SYNTAX
#   ifdef __INTEL_COMPILER
		"bsr	%1,%2\n\t"
		"setnz	%0"
#   else
		"bsrl	%1,%2\n\t"
		"setnz	%0"
#   endif
#  else
		"bsrl	%2,%1\n\t"
		"setnz	%0"
#  endif
		: "=r" ( nzf ), "=r" ( tmp )
		: "rm" ( m )
		:
		);
	*i = tmp;
	return nzf;
}

static __inline__ __attribute__ ((__always_inline__))
unsigned char _BitScanReverse64( unsigned *i, uint64_t m )
{
	register uint64_t tmp;
	register uint8_t nzf;
	__asm__ (
#  ifdef INTEL_SYNTAX
		"bsrq	%1,%2\n\t"
		"setnz	%0"
#  else
		"bsrq	%2,%1\n\t"
		"setnz	%0"
#  endif
		: "=r" ( nzf ), "=r" ( tmp )
		: "rm" ( m )
		:
		);
	*i = ( unsigned )tmp;
	return nzf;
}

#  define _BSF32( __i, __m )	_BitScanForward( ( __i ), ( __m ) )
#  define _BSR32( __i, __m )	_BitScanReverse( ( __i ), ( __m ) )
#  define _BSF64( __i, __m )	_BitScanForward64( ( __i ), ( __m ) )
#  define _BSR64( __i, __m )	_BitScanReverse64( ( __i ), ( __m ) )
#  define _IS_BITSCANF32	1
#  define _IS_BITSCANR32	1
#  define _IS_BITSCAN64		1

#  ifndef WORDSIZE
#   define WORDSIZE		64
#  endif
#  ifndef __WORDSIZE
#   define __WORDSIZE		WORDSIZE
#  endif
#  if __WORDSIZE != WORDSIZE
#   undef WORDSIZE
#   define WORDSIZE		__WORDSIZE
#  endif

# elif defined( __386__ ) || defined( _I386 ) || defined( __i386__ ) || defined( __i386 ) ||\
	defined( _M_I386 ) || defined( M_I386 ) || defined( DOS386 ) ||\
	defined( __i486__ ) || defined( __i586__ ) || defined( __i686__ ) ||\
	defined( __FLAT__ ) || ( defined( _M_IX86 ) && _M_IX86 >= 300 ) ||\
	( defined( __I86__ ) && __I86__ >= 3 )

static __inline__ __attribute__ ((__always_inline__))
unsigned char _BitScanForward( unsigned *i, uint32_t m )
{
	register uint32_t tmp;
	register uint8_t nzf;
	__asm__ (
#  ifdef INTEL_SYNTAX
#   ifdef __INTEL_COMPILER
		"bsf	%1,%2\n\t"
		"setnz	%0"
#   else
		"bsfl	%1,%2\n\t"
		"setnz	%0"
#   endif
#  else
		"bsfl	%2,%1\n\t"
		"setnz	%0"
#  endif
		: "=r" ( nzf ), "=r" ( tmp )
		: "rm" ( m )
		:
		);
	*i = tmp;
	return nzf;
}

static __inline__ __attribute__ ((__always_inline__))
unsigned char _BitScanReverse( unsigned *i, uint32_t m )
{
	register uint32_t tmp;
	register uint8_t nzf;
	__asm__ (
#  ifdef INTEL_SYNTAX
#   ifdef __INTEL_COMPILER
		"bsr	%1,%2\n\t"
		"setnz	%0"
#   else
		"bsrl	%1,%2\n\t"
		"setnz	%0"
#   endif
#  else
		"bsrl	%2,%1\n\t"
		"setnz	%0"
#  endif
		: "=r" ( nzf ), "=r" ( tmp )
		: "rm" ( m )
		:
		);
	*i = tmp;
	return nzf;
}

#  define _BSF32( __i, __m )	_BitScanForward( ( __i ), ( __m ) )
#  define _BSR32( __i, __m )	_BitScanReverse( ( __i ), ( __m ) )
#  define _IS_BITSCANF32	1
#  define _IS_BITSCANR32	1

#  ifndef WORDSIZE
#   define WORDSIZE		32
#  endif
#  ifndef __WORDSIZE
#   define __WORDSIZE		WORDSIZE
#  endif
#  if __WORDSIZE != WORDSIZE
#   undef WORDSIZE
#   define WORDSIZE		__WORDSIZE
#  endif

# elif defined( _IS_ARM64 )

static __inline__ __attribute__ ((__always_inline__))
unsigned char _BitScanForward( unsigned *i, uint32_t m )
{
	register uint32_t nzf, tmp;
	__asm__ (
		"rbit	%w1,%w2\n\t"
		"clz	%w1,%w1\n\t"
		"sub	%w0,%w0,%w1,lsr #5"
		: "=r" ( nzf ), "=r" ( tmp )
		: "r" ( m ), "0" ( 1 )
		:
		);
	*i = tmp;
	return ( unsigned char )nzf;
}

static __inline__ __attribute__ ((__always_inline__))
unsigned char _BitScanForward64( unsigned *i, uint64_t m )
{
	register uint32_t nzf, tmp;
	__asm__ (
		"rbit	%1,%2\n\t"
		"clz	%1,%1\n\t"
		"sub	%0,%0,%1,lsr #6"
		: "=r" ( nzf ), "=r" ( tmp )
		: "r" ( m ), "0" ( 1 )
		:
		);
	*i = tmp;
	return ( unsigned char )nzf;
}

static __inline__ __attribute__ ((__always_inline__))
unsigned char _BitScanReverse( unsigned *i, uint32_t m )
{
	register uint32_t nzf, tmp;
	__asm__ (
		"clz	%w2,%w2\n\t"
		"sub	%w1,%w1,%w2\n\t"
		"sub	%w0,%w0,%w2,lsr #5"
		: "=r" ( nzf ), "=r" ( tmp ), "=r" ( m )
		: "2" ( m ), "0" ( 1 ), "1" ( 31 )
		:
		);
	*i = tmp;
	return ( unsigned char )nzf;
}

static __inline__ __attribute__ ((__always_inline__))
unsigned char _BitScanReverse64( unsigned *i, uint64_t m )
{
	register uint32_t nzf, tmp;
	__asm__ (
		"clz	%2,%2\n\t"
		"sub	%1,%1,%2\n\t"
		"sub	%0,%0,%2,lsr #6"
		: "=r" ( nzf ), "=r" ( tmp ), "=r" ( m )
		: "2" ( m ), "0" ( 1 ), "1" ( 63 )
		:
		);
	*i = tmp;
	return ( unsigned char )nzf;
}

#  define _BSF32( __i, __m )	_BitScanForward( ( __i ), ( __m ) )
#  define _BSR32( __i, __m )	_BitScanReverse( ( __i ), ( __m ) )
#  define _BSF64( __i, __m )	_BitScanForward64( ( __i ), ( __m ) )
#  define _BSR64( __i, __m )	_BitScanReverse64( ( __i ), ( __m ) )
#  define _IS_BITSCANF32	1
#  define _IS_BITSCANR32	1
#  define _IS_BITSCAN64		1

#  ifndef WORDSIZE
#   define WORDSIZE		64
#  endif
#  ifndef __WORDSIZE
#   define __WORDSIZE		WORDSIZE
#  endif
#  if __WORDSIZE != WORDSIZE
#   undef WORDSIZE
#   define WORDSIZE		__WORDSIZE
#  endif

# elif defined( _IS_ARM ) && ( _IS_ARM >= 5 \
	|| defined( _IS_THUMB ) && _IS_THUMB >= 2 )

#  if _IS_ARM >= 7 || _IS_ARM == 6 \
	&& defined( _IS_THUMB ) && _IS_THUMB >= 4

/*#   pragma push*/
/*
#   if _IS_ARM < 7 && !defined( _IS_IN_THUMB )
#    pragma thumb
#   endif
*/
/*
#   if _IS_ARM < 7 && !defined( _IS_IN_THUMB )
static __inline__ __attribute__ ((__always_inline__,target("thumb")))
#   else*/
static __inline__ __attribute__ ((__always_inline__))
/*#   endif*/
unsigned char _BitScanForward( unsigned *i, uint32_t m )
{
	register uint32_t nzf, tmp;
	__asm__ (
#   if _IS_ARM < 7 && !defined( _IS_IN_THUMB )
		"0:\n\t"
		".thumb\n\t"
		"rbit	%1,%2\n\t"
		"1:\n\t"
		".arm\n\t"
		"clz	%1,%1\n\t"
		"sub	%0,%0,%1,lsr #5"
#   else
		"rbit	%1,%2\n\t"
		"clz	%1,%1\n\t"
		"sub	%0,%0,%1,lsr #5"
#   endif
		: "=r" ( nzf ), "=r" ( tmp )
		: "r" ( m ), "0" ( 1 )
		:
		);
	*i = tmp;
	return ( unsigned char )nzf;
}
/*
#   if _IS_ARM < 7 && !defined( _IS_IN_THUMB )
#    pragma arm
#   endif
*/
/*#   pragma pop*/

#   define _BSF32( __i, __m )	_BitScanForward( ( __i ), ( __m ) )
#   define _IS_BITSCANF32	1

#  endif

static __inline__ __attribute__ ((__always_inline__))
unsigned char _BitScanReverse( unsigned *i, uint32_t m )
{
	register uint32_t nzf, tmp;
	__asm__ (
		"clz	%2,%2\n\t"
		"sub	%1,%1,%2\n\t"
		"sub	%0,%0,%2,lsr #5"
		: "=r" ( nzf ), "=r" ( tmp ), "=r" ( m )
		: "2" ( m ), "0" ( 1 ), "1" ( 31 )
		:
		);
	*i = tmp;
	return ( unsigned char )nzf;
}

#  define _BSR32( __i, __m )	_BitScanReverse( ( __i ), ( __m ) )
#  define _IS_BITSCANR32	1

#  ifndef WORDSIZE
#   define WORDSIZE		32
#  endif
#  ifndef __WORDSIZE
#   define __WORDSIZE		WORDSIZE
#  endif
#  if __WORDSIZE != WORDSIZE
#   undef WORDSIZE
#   define WORDSIZE		__WORDSIZE
#  endif

# endif

#elif defined( _WIN32 )

/* WIN32 API versions */
# ifndef _WINNT_
#  include <winnt.h>
# endif

/* They're defined as macros in winnt.h */
# if defined( BitScanForward ) && defined( BitScanReverse )

/* Prototypes: */
/*  BOOLEAN BitScanForward( DWORD *Index, DWORD Mask ); */
/*  BOOLEAN BitScanReverse( DWORD *Index, DWORD Mask ); */
#  define _BSF32( __i, __m )	BitScanForward( ( __i ), ( __m ) )
#  define _BSR32( __i, __m )	BitScanReverse( ( __i ), ( __m ) )
#  define _IS_BITSCANF32	1
#  define _IS_BITSCANR32	1

# endif

# if defined( BitScanForward64 ) && defined( BitScanReverse64 )

/* Prototypes: */
/*  BOOLEAN BitScanForward64( DWORD *Index, DWORD64 Mask ); */
/*  BOOLEAN BitScanReverse64( DWORD *Index, DWORD64 Mask ); */
#  define _BSF64( __i, __m )	BitScanForward64( ( __i ), ( __m ) )
#  define _BSR64( __i, __m )	BitScanReverse64( ( __i ), ( __m ) )
#  define _IS_BITSCAN64		1

# endif

# ifdef _WIN64
#  ifndef WORDSIZE
#   define WORDSIZE		64
#  endif
# else
#  ifndef WORDSIZE
#   define WORDSIZE		32
#  endif
# endif
# ifndef __WORDSIZE
#  define __WORDSIZE		WORDSIZE
# endif
# if __WORDSIZE != WORDSIZE
#  undef WORDSIZE
#  define WORDSIZE		__WORDSIZE
# endif

#endif

#if defined( _IS_BITSCANF32 ) && defined( _IS_BITSCANR32 )
# define _IS_BITSCAN32		1
#endif


#endif		/* _ASSA_BITSCAN_H_INCLUDED */
