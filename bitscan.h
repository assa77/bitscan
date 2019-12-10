/****************************************************************************
*
*	bitscan.h	Portable BitScan implementation	(MSC, ICL, GNUC, etc.
*			for WIN32/IA32/Intel64/ARM only)
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


/*
* Detecting C++ version and whether exceptions are enabled
*/
#ifdef _IS_CPP98
# undef _IS_CPP98
#endif
#ifdef _IS_CPP03
# undef _IS_CPP03
#endif
#ifdef _IS_CPP11
# undef _IS_CPP11
#endif
#ifdef _IS_CPP14
# undef _IS_CPP14
#endif
#ifdef _IS_CPP17
# undef _IS_CPP17
#endif
#ifdef _IS_NOTHROW
# undef _IS_NOTHROW
#endif
#ifdef _IS_NOTHROWC
# undef _IS_NOTHROWC
#endif

#if defined( __cplusplus__ ) && !defined( __cplusplus )
# define __cplusplus		__cplusplus__
#elif !defined( __cplusplus__ ) && defined( __cplusplus )
# define __cplusplus__		__cplusplus
#endif

#ifdef __cplusplus
# if __cplusplus >= 199711L
#  define _IS_CPP98		1
#  define _IS_CPP03		1
# endif
# if __cplusplus >= 201103L ||\
	defined( __cpp_constexpr ) && defined( __cpp_decltype ) &&\
	defined( __cpp_rvalue_references ) && defined( __cpp_variadic_templates ) &&\
	defined( __cpp_lambdas ) && defined( __cpp_unicode_characters ) ||\
	defined( _MSC_VER ) && _MSC_VER >= 1900
#  define _IS_CPP11		1
# endif
# if __cplusplus >= 201402L
#  define _IS_CPP14		1
# endif
# if __cplusplus >= 201703L
#  define _IS_CPP17		1
# endif
# if defined( __CPPUNWIND ) && !defined( _CPPUNWIND )
#  define _CPPUNWIND		__CPPUNWIND
# elif !defined( __CPPUNWIND ) && defined( _CPPUNWIND )
#  define __CPPUNWIND		_CPPUNWIND
# endif
# if defined( _CPPUNWIND ) && !defined( __EXCEPTIONS )
#  define __EXCEPTIONS		_CPPUNWIND
# endif
# if defined( __cpp_exceptions ) && !defined( __EXCEPTIONS )
#  define __EXCEPTIONS		__cpp_exceptions
# endif
# if defined( __EXCEPTIONS ) && !defined( _EXCEPTIONS )
#  define _EXCEPTIONS		__EXCEPTIONS
# elif !defined( __EXCEPTIONS ) && defined( _EXCEPTIONS )
#  define __EXCEPTIONS		_EXCEPTIONS
# endif
# if defined( _IS_CPP11 ) && defined( __EXCEPTIONS )
#  define _IS_NOTHROW		noexcept
#  define _IS_NOTHROWC( ... )	noexcept( __VA_ARGS__ )
# elif defined( __EXCEPTIONS )
#  define _IS_NOTHROW		throw( )
#  define _IS_NOTHROWC( __e )
# else
#  define _IS_NOTHROW
#  define _IS_NOTHROWC( __e )
# endif
#else		/* !__cplusplus */
# define _IS_NOTHROW
# define _IS_NOTHROWC( __e )
#endif		/* __cplusplus */

/*
* C99 or OpenWatcom 1.5 (long long support, ... (1.2), new headers, inline
*	keyword, ... (1.3), Exit( ), new printf format specifiers, ... (1.5))
*/
#ifdef _IS_C99
# undef _IS_C99
#endif
#ifdef _IS_C10
# undef _IS_C10
#endif
#ifdef _IS_C11
# undef _IS_C11
#endif

#if defined( __STDC_VERSION__ ) && __STDC_VERSION__ >= 199901L ||\
	!defined( __cplusplus ) && defined( __WATCOMC__ ) && __WATCOMC__ >= 1250
# define _IS_C99		1
# ifndef __STDC_WANT_LIB_EXT1__
#  define __STDC_WANT_LIB_EXT1__ 1
# endif
#endif
#if defined( __STDC_VERSION__ ) && __STDC_VERSION__ >= 201000L
# define _IS_C10		1
#endif
#if defined( __STDC_VERSION__ ) && __STDC_VERSION__ >= 201112L
# define _IS_C11		1
#endif

/*
* Normalization of predefined macros
*/

/* _WIN64 */
#ifndef _WIN64
# ifdef WIN64
#  define _WIN64		WIN64
# elif defined( __WIN64 )
#  define _WIN64		__WIN64
# elif defined( __WIN64__ )
#  define _WIN64		__WIN64__
# elif defined( __MINGW64__ )
#  define _WIN64		__MINGW64__
# endif
#endif

#if defined( _WIN64 ) && !defined( WIN64 )
# define WIN64			_WIN64
#endif

/* Intel compiler definitions */
#ifndef __INTEL_COMPILER
# ifdef __ICL
#  define __INTEL_COMPILER	__ICL
# elif defined( __ICL__ )
#  define __INTEL_COMPILER	__ICL__
# elif defined( __ICC )
#  define __INTEL_COMPILER	__ICC
# endif
#endif

#if defined( __INTEL_COMPILER ) && !defined( __ICL )
# define __ICL			__INTEL_COMPILER
#endif

#if defined( __INTEL_COMPILER ) && !defined( __ICL__ )
# define __ICL__		__INTEL_COMPILER
#endif

#if defined( __INTEL_COMPILER ) && !defined( __ICC )
# define __ICC			__INTEL_COMPILER
#endif

#if defined( __CYGWIN64__ ) && !defined( __CYGWIN__ )
# define __CYGWIN__		__CYGWIN64__
#endif

#if defined( __CYGWIN32__ ) && !defined( __CYGWIN__ )
# define __CYGWIN__		__CYGWIN32__
#endif

#if defined( __MINGW64__ ) && !defined( __MINGW__ )
# define __MINGW__		__MINGW64__
#endif

#if defined( __MINGW32__ ) && !defined( __MINGW__ )
# define __MINGW__		__MINGW32__
#endif

#if ( defined( __powerpc__ ) || defined( __powerpc ) || defined( __POWERPC__ ) ||\
	defined( __ppc ) || defined( __PPC__ ) || defined( __PPC ) || defined( __ppc__ ) ||\
	defined( _MPPC_ ) || defined( _M_MPPC ) || defined( _ARCH_PPC ) ) && !defined( _M_PPC )
# define _M_PPC			1
#endif

#if ( defined( __PPC64__ ) || defined( __ppc64 ) || defined( _M_PPC64 ) ) && !defined( __ppc64__ )
# define __ppc64__		1
#endif
#if defined( __ppc64__ ) && !defined( _M_PPC64 )
# define _M_PPC64		__ppc64__
#endif

#if ( defined( __alpha ) || defined( __ALPHA__ ) || defined( __alpha__ ) ||\
	defined( __axp ) || defined( __axp__ ) || defined( __AXP__ ) ) &&\
	!defined( _M_ALPHA )
# define _M_ALPHA		1
#endif

#if ( defined( __m68k__ ) || defined( __m68000__ ) || defined( __mc68000__ ) ||\
	defined( __mc68010__ ) || defined( __mc68020__ ) || defined( __mc68030__ ) ||\
	defined( __mc68040__ ) || defined( __mc68060__ ) || defined( _68K_ ) ||\
	defined( M68000 ) ) && !defined( _M_M68K )
# define _M_M68K		1
#endif
#if defined( _M_M68K ) && !defined( _68K_ )
# define _68K_			_M_M68K
#endif

#if ( defined( __itanium__ ) || defined( __ia64__ ) || defined( __ia64 ) || defined( _IA64 ) ||\
	defined( __IA64__ ) ) && !defined( _M_IA64 )
# define _M_IA64		1
#endif

#if ( defined( __amd64__ ) || defined( __amd64 ) || defined( __x86_64__ ) || defined( __x86_64 ) ||\
	defined( _AMD64_ ) || defined( _M_AMD64 ) || defined( M_X64 ) ) && !defined( _M_X64 )
# ifdef _M_AMD64
#  define _M_X64		_M_AMD64
# elif defined( M_X64 )
#  define _M_X64		M_X64
# else
#  define _M_X64		100
# endif
#endif
#if defined( _M_X64 ) && !defined( _M_AMD64 )
# define _M_AMD64		_M_X64
#endif

#ifndef _M_ARM
# ifdef __ARM_ARCH
#  define _M_ARM		__ARM_ARCH
# elif defined( __TARGET_ARCH_ARM )
#  define _M_ARM		__TARGET_ARCH_ARM
# elif defined( __TARGET_ARCH_THUMB ) && __TARGET_ARCH_THUMB >= 4
#  define _M_ARM		7
# elif defined( __ARM_ARCH_ISA_THUMB ) && __ARM_ARCH_ISA_THUMB >= 2
#  define _M_ARM		7
# elif defined( __thumb2__ ) || defined( __thumb2 ) || defined( thumb2 )
#  define _M_ARM		7
# elif defined( __thumb__ ) || defined( __thumb ) || defined( __TARGET_ARCH_THUMB ) ||\
	defined( __ARM_ARCH_ISA_THUMB )
#  define _M_ARM		1
# elif defined( __arm__ )
#  define _M_ARM		1
# elif defined( __arm )
#  define _M_ARM		1
# elif defined( arm )
#  define _M_ARM		1
# elif defined( _ARM_ )
#  define _M_ARM		1
# elif defined( ARM )
#  define _M_ARM		1
# endif
#endif

#if defined( __aarch64 ) && !defined( __aarch64__ )
# defined __aarch64__		__aarch64
#endif

#if defined( __aarch64__ ) && !defined( _M_ARM64 )
# define _M_ARM64		__aarch64__
#endif

#if defined( _M_ARM64 ) && !defined( _M_ARM )
# define _M_ARM			8
#endif

#if ( defined( __DJGPP__ ) || defined( __EMX__ ) || defined( __CYGWIN__ ) ||\
	defined( __MINGW__ ) ) && !defined( __GNUC__ )
# define __GNUC__		0
#endif


/****************************************************************************
* Macro definitions for debugging
*/
#if __LINE__ + 0 == 0
# ifndef __LINE__
#  define __LINE__		0
# endif
# ifndef __FILE__
#  define __FILE__		""
# endif
#endif

#ifdef ToStr
# undef ToStr
#endif
#ifdef _ToStr
# undef _ToStr
#endif
#define ToStr( s )		_ToStr( s )
#define _ToStr( s )		#s

#ifndef _IsLocation
# ifdef _tIsLocation
#  undef _tIsLocation
# endif
# ifdef IsLocation
#  undef IsLocation
# endif
# ifdef tIsLocation
#  undef tIsLocation
# endif
#  define _IsLocation		__FILE__ "(" ToStr( __LINE__ ) "): "
#  define _tIsLocation		_T( __FILE__ ) _T( "(" ) _T( ToStr( __LINE__ ) ) _T( "): " )
# define IsLocation		_IsLocation
# define tIsLocation		_tIsLocation
#endif

#ifndef _IS_LOCATION
# ifdef _IS_2STR
#  undef _IS_2STR
# endif
# ifdef _IS_2STR_
#  undef _IS_2STR_
# endif
# ifdef _IS_LOCATION_
#  undef _IS_LOCATION_
# endif
# ifdef _IS_LOCATIONP
#  undef _IS_LOCATIONP
# endif
# define _IS_2STR( x )		#x
# define _IS_2STR_( x )		_IS_2STR( x )
# define _IS_LOCATION		_IsLocation
# define _IS_LOCATION_		_IsLocation
# define _IS_LOCATIONP		_IsLocation
#endif

/*
* _STATIC_ASSERT( ) macro: Static assertion implementation
*/
#ifdef _ASSERT_CONCAT_
# undef _ASSERT_CONCAT_
#endif
#ifdef _ASSERT_CONCAT
# undef _ASSERT_CONCAT
#endif
#define _ASSERT_CONCAT_( __a, __b )	__a##__b
#define _ASSERT_CONCAT( __a, __b )	_ASSERT_CONCAT_( __a, __b )

#ifdef _STATIC_ASSERT
# undef _STATIC_ASSERT
#endif
#ifdef _STATIC_ASSERTE
# undef _STATIC_ASSERTE
#endif
#define _STATIC_ASSERTE( __c, __m )	typedef int __static_assert[ 1 - 2 * !( __c ) ]
#define _STATIC_ASSERT( __c )		_STATIC_ASSERTE( __c, "*** FATAL: ASSERTION FAILED!!!" )

#ifdef _IS_INTEGRAL
# undef _IS_INTEGRAL
#endif
#define _IS_INTEGRAL( __t, __m )	typedef int __is_integral_assert[ ( __t )1 | ( __t )1 ]


/****************************************************************************
* Detecting C compiler capabilities...
*/
#ifndef _ISOC95_SOURCE
# define _ISOC95_SOURCE		1
#endif
#ifndef _ISOC99_SOURCE
# define _ISOC99_SOURCE		1
#endif
#ifndef _ISOC11_SOURCE
# define _ISOC11_SOURCE		1
#endif
#ifndef _POSIX_SOURCE
# define _POSIX_SOURCE		1
#endif
#ifndef _POSIX_C_SOURCE
# define _POSIX_C_SOURCE	200809L
#endif
#ifndef _GNU_SOURCE
# define _GNU_SOURCE		1
#endif

#ifdef _IS_NEW_HEADERS
# undef _IS_NEW_HEADERS
#endif
#ifdef _IS_STD
# undef _IS_STD
#endif

#ifdef _IS_ERRORLOG_H
# undef _IS_ERRORLOG_H
#endif
#ifdef _IS_STDINT_H
# undef _IS_STDINT_H
#endif
#ifdef _IS_UCHAR_H
# undef _IS_UCHAR_H
#endif
#ifdef _IS_INTPTR
# undef _IS_INTPTR
#endif

#if defined( __cplusplus ) && (\
	defined( _IS_CPP98 )					/* C++ standard >= 1998 (doesn't work properly with some MINGW) or */\
	&& !defined( __BORLANDC__ ) && !defined( __DMC__ )	/* wtf Borland C++ ???, Digital Mars C++ */\
	&& !defined( _MSC_VER ) && !defined( __WATCOMC__ )	/* wtf Borland C++ ???, Digital Mars C++ */\
	|| defined( _MSC_VER ) && _MSC_VER >= 1310		/* Visual C++ >= .NET (7.1) or */\
	|| defined( __WATCOMC__ ) && __WATCOMC__ >= 1240	/* OpenWatcom >= 1.4 (or 1.3? - w/o new) or */\
	)
# define _IS_NEW_HEADERS	1
# define _IS_STD		std::
#else
# define _IS_STD
#endif

#if defined( _IS_C99 ) || defined( _IS_CPP98 ) ||\
	defined( __WATCOMC__ ) && __WATCOMC__ >= 1230 ||\
	defined( _MSC_VER ) && _MSC_VER >= 1600 ||\
	defined( __DMC__ )
# ifndef __STDC_LIMIT_MACROS
#  define __STDC_LIMIT_MACROS
# endif
# ifndef __STDC_CONSTANT_MACROS
#  define __STDC_CONSTANT_MACROS
# endif
# ifdef _IS_C99
#  include <stdbool.h>
# endif
# ifdef _IS_NEW_HEADERS
#  if defined( _IS_CPP11 ) ||\
	defined( __WATCOMC__ ) && __WATCOMC__ >= 1280 ||\
	defined( _MSC_VER ) && _MSC_VER >= 1600
#   include <cstdint>
#  endif
#  include <ciso646>
#  include <cwctype>
#  if defined( _IS_CPP11 ) && !defined( __MIC__ )
#   define _IS_UCHAR_H		1
#   include <cuchar>
#  endif
# else
#  include <iso646.h>
#  include <wctype.h>
#  ifdef _IS_C10
#   define _IS_UCHAR_H		1
#   include <uchar.h>
#  endif
# endif
# define _IS_STDINT_H		1
# include <stdint.h>
# include <inttypes.h>
# if !defined( _IS_NO_INTPTR ) && defined( INTPTR_MAX ) && defined( UINTPTR_MAX )
#  if /*defined( __WATCOMC__ ) && */defined( _DEBUG )
#   ifdef __GNUC__
#    pragma message "*** INFO: Assume that [u]intptr_t types are present"
#   else
#    pragma message( _IS_LOCATIONP "*** INFO: Assume that [u]intptr_t types are present" )
#   endif
#  endif
#  define _IS_INTPTR		1
# endif
#else
# ifdef __STDC_LIMIT_MACROS
#  undef __STDC_LIMIT_MACROS
# endif
#endif

/* get off annoying min/max macros */
#ifdef __cplusplus
# ifdef NOMINMAX
#  undef NOMINMAX
# endif
# define NOMINMAX	/* for WINDEF.H */
# ifdef min
#  undef min
# endif
# ifdef max
#  undef max
# endif
#endif

#ifdef EXTERNC
# undef EXTERNC
#endif
#ifdef _IS_EXTERNC_BEGIN
# undef _IS_EXTERNC_BEGIN
#endif
#ifdef _IS_EXTERNC_END
# undef _IS_EXTERNC_END
#endif

#ifdef __cplusplus
# define EXTERNC		extern "C"
# define _IS_EXTERNC_BEGIN	extern "C" {
# define _IS_EXTERNC_END	}
#else
# define EXTERNC
# define _IS_EXTERNC_BEGIN
# define _IS_EXTERNC_END
#endif


#ifndef __STDC_LIMIT_MACROS
# error "*** FATAL: stdint.h/cstdint is required for now!"
#endif


/****************************************************************************
* Detecting target Architecture... (Simplified!!!)
*/
#ifdef _IS_386
# undef _IS_386
#endif
#ifdef _IS_X64
# undef _IS_X64
#endif
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
#ifdef _IS_NEON
# undef _IS_NEON
#endif

#ifdef _M_X64
# define _IS_X64	1
# ifdef _IS_X86
#  undef _IS_X86
# endif
# ifdef M_IX86
#  undef M_IX86
# endif
# ifdef _M_IX86
#  undef _M_IX86
# endif
# ifndef M_X64
#  define M_X64		_M_X64
# endif
# ifndef _M_X64
#  define _M_X64	M_X64
# endif
#elif defined( __386__ ) || defined( _I386 ) || defined( __i386__ ) || defined( __i386 ) || \
	defined( _M_I386 ) || defined( M_I386 ) || defined( DOS386 ) || \
	defined( __i486__ ) || defined( __i586__ ) || defined( __i686__ ) || \
	defined( __FLAT__ ) || ( defined( _M_IX86 ) && _M_IX86 >= 300 ) || \
	( defined( __I86__ ) && __I86__ >= 3 )
# define _IS_386	1
# ifndef _IS_X86
#  define _IS_X86	1
# endif
# ifndef M_IX86
#  ifdef _M_IX86
#   define M_IX86	_M_IX86
#  else
/*#   define M_IX86	300*/
#   define M_IX86	600
#  endif
# endif
# ifndef _M_IX86
#  define _M_IX86	M_IX86
# endif
#else
# if defined( _M_ARMT ) || defined( __thumb__ ) || defined( __thumb ) \
	|| defined( __thumb2__ ) || defined( __thumb2 ) || defined( thumb2 )
#  define _IS_IN_THUMB		1
# endif
# ifdef _M_ARM64
#  define _IS_ARM64		1
# endif
# if defined( __ARM_ARCH_8M__ ) \
	|| defined( __ARM_ARCH_8M_BASE__ ) \
	|| defined( __ARM_ARCH_8M_MAIN__ ) \
	|| defined( __ARM_ARCH_8M ) \
	|| defined( __ARM_ARCH_8M_BASE ) \
	|| defined( __ARM_ARCH_8M_MAIN ) \
	|| defined( __ARM_ARCH_7M__ ) \
	|| defined( __ARM_ARCH_7EM__ ) \
	|| defined( __ARM_ARCH_6M__ ) \
	|| defined( __ARM_ARCH_6SM__ )
#  define _IS_ARM		0
# elif defined( __ARM_ARCH_8__ ) \
	|| defined( __ARM_ARCH_8A__ ) \
	|| defined( __ARM_ARCH_8R__ ) \
	|| defined( __ARM_ARCH_8 ) \
	|| defined( __ARM_ARCH_8A ) \
	|| defined( __ARM_ARCH_8R ) \
	|| defined( __ARMV8__ )
#  define _IS_ARM		8
# elif defined( __ARM_ARCH_7__ ) \
	|| defined( __ARM_ARCH_7A__ ) \
	|| defined( __ARM_ARCH_7R__ ) \
	|| defined( __ARM_ARCH_7S__ ) \
	|| defined( __ARMV7__ )
#  define _IS_ARM		7
# elif defined( __ARM_ARCH_6__ ) \
	|| defined( __ARM_ARCH_6J__ ) \
	|| defined( __ARM_ARCH_6K__ ) \
	|| defined( __ARM_ARCH_6Z__ ) \
	|| defined( __ARM_ARCH_6ZK__ ) \
	|| defined( __ARM_ARCH_6T2__ ) \
	|| defined( __ARMV6__ )
#  define _IS_ARM		6
# elif defined( __ARM_ARCH_5__ ) \
	|| defined( __ARM_ARCH_5E__ ) \
	|| defined( __ARM_ARCH_5T__ ) \
	|| defined( __ARM_ARCH_5TE__ ) \
	|| defined( __ARM_ARCH_5TEJ__ ) \
	|| defined( __ARMV5__ ) \
	|| defined( __MARM_ARMV5__ )
#  define _IS_ARM		5
# elif defined( __ARM_ARCH_4__ ) \
	|| defined( __ARM_ARCH_4T__ ) \
	|| defined( __ARMV4__ ) \
	|| defined( __MARM_ARMV4__ ) \
	|| defined( __MARM_ARM4__ ) \
	|| defined( __TARGET_ARM_4T__ )
#  define _IS_ARM		4
# elif defined( __ARM_ARCH_3__ ) \
	|| defined( __ARM_ARCH_3M__ ) \
	|| defined( __ARMV3__ )
#  define _IS_ARM		3
# elif defined( __ARM_ARCH_2__ ) \
	|| defined( __ARMV2__ )
#  define _IS_ARM		2
# elif defined( _M_ARM )
#  define _IS_ARM		_M_ARM
# endif
# if ( defined( __ARM_ARCH_8M__ ) \
	|| defined( __ARM_ARCH_8M_BASE__ ) \
	|| defined( __ARM_ARCH_8M ) \
	|| defined( __ARM_ARCH_8M_BASE ) \
	|| defined( __ARM_ARCH_6__ ) \
	|| defined( __ARM_ARCH_6J__ ) \
	|| defined( __ARM_ARCH_6K__ ) \
	|| defined( __ARM_ARCH_6Z__ ) \
	|| defined( __ARM_ARCH_6ZK__ ) \
	|| defined( __ARM_ARCH_6M__ ) \
	|| defined( __ARM_ARCH_6SM__ ) \
	|| defined( __ARMV6__ ) ) \
	&& !defined( __ARM_ARCH_6T2__ )
#  define _IS_THUMB		3
# elif defined( __ARM_ARCH_8__ ) \
	|| defined( __ARM_ARCH_8A__ ) \
	|| defined( __ARM_ARCH_8R__ ) \
	|| defined( __ARM_ARCH_8 ) \
	|| defined( __ARM_ARCH_8A ) \
	|| defined( __ARM_ARCH_8R ) \
	|| defined( __ARM_ARCH_8M_MAIN__ ) \
	|| defined( __ARMV8__ ) \
	|| defined( __ARM_ARCH_7__ ) \
	|| defined( __ARM_ARCH_7A__ ) \
	|| defined( __ARM_ARCH_7M__ ) \
	|| defined( __ARM_ARCH_7EM__ ) \
	|| defined( __ARM_ARCH_7R__ ) \
	|| defined( __ARM_ARCH_7S__ ) \
	|| defined( __ARMV7__ ) \
	|| defined( __ARM_ARCH_6T2__ )
#  define _IS_THUMB		4
# elif defined( __ARM_ARCH_5__ ) \
	|| defined( __ARM_ARCH_5E__ ) \
	|| defined( __ARM_ARCH_5T__ ) \
	|| defined( __ARM_ARCH_5TE__ ) \
	|| defined( __ARM_ARCH_5TEJ__ ) \
	|| defined( __ARMV5__ ) \
	|| defined( __MARM_ARMV5__ )
#  define _IS_THUMB		2
# elif defined( __ARM_ARCH_4T__ ) \
	|| defined( __TARGET_ARM_4T__ )
#  define _IS_THUMB		1
# elif defined( __TARGET_ARCH_THUMB )
#  define _IS_THUMB		__TARGET_ARCH_THUMB
# elif defined( __ARM_ARCH_ISA_THUMB ) && __ARM_ARCH_ISA_THUMB >= 2
#  define _IS_THUMB		4
# elif defined( _IS_ARM ) && _IS_ARM >= 7
#  define _IS_THUMB		_IS_ARM
# elif defined( __ARM_ARCH_ISA_THUMB )
#  define _IS_THUMB		1
# elif defined( _IS_IN_THUMB )
#  if defined( __thumb2__ ) || defined( __thumb2 ) || defined( thumb2 )
#   define _IS_THUMB		4
#  else
#   define _IS_THUMB		1
#  endif
# endif
# if defined( _IS_THUMB ) && !defined( _IS_ARM )
#  if _IS_THUMB >= 4
#   define _IS_ARM		7
#  elif _IS_THUMB >= 3
#   define _IS_ARM		6
#  elif _IS_THUMB >= 2
#   define _IS_ARM		5
#  else
#   define _IS_ARM		4
#  endif
# endif
# if ( defined( __ARM_NEON__ ) || defined( __ARM_NEON ) ) \
	&& ( !defined( __GNUC__ ) || __GNUC__ > 4 || __GNUC__ == 4 \
	&& defined( __GNUC_MINOR__ ) && __GNUC_MINOR__ >= 7 )
#  define _IS_NEON		1
# endif
#endif


/*
* Inline macros
*/
#ifdef _ALWAYS_INLINE
# undef _ALWAYS_INLINE
#endif
#ifdef _IS_NOINLINE
# undef _IS_NOINLINE
#endif
#ifdef _STATIC_INLINE
# undef _STATIC_INLINE
#endif
#ifdef _STATIC_ALWAYS_INLINE
# undef _STATIC_ALWAYS_INLINE
#endif
#ifdef _STATIC_NOINLINE
# undef _STATIC_NOINLINE
#endif
#ifdef _INLINE_ASM
# undef _INLINE_ASM
#endif

#if !defined( __cplusplus ) && !defined( _IS_C99 ) && ( !defined( __WATCOMC__ ) || __WATCOMC__ < 1230 )
# ifdef __GNUC__
#  define inline		__inline__
# elif defined( _MSC_VER ) || defined( __WATCOMC__ ) || defined( __BORLANDC__ ) ||\
	defined( __ICL ) || defined( __DECC ) || defined( __DMC__ )
#  define inline		__inline
# else
#  pragma message( _IS_LOCATIONP "*** WARNING: inline keyword will be suppressed" )
#  define inline
# endif
#endif

#if defined( _MSC_VER )/* || defined( __ICL )*/
# define _ALWAYS_INLINE		__forceinline
# define _IS_NOINLINE		__declspec( noinline )
#elif defined( __GNUC__ )
# define _ALWAYS_INLINE		__inline__ __attribute__ ((__always_inline__/*, __nodebug__*/))
# define _IS_NOINLINE		__attribute__ ((noinline))
#else
# define _ALWAYS_INLINE		inline
# define _IS_NOINLINE
#endif

#define _STATIC_ALWAYS_INLINE	static _ALWAYS_INLINE
#define _STATIC_INLINE		static inline
/*#define _STATIC_INLINE		_STATIC_ALWAYS_INLINE*/
#define _STATIC_NOINLINE	static _IS_NOINLINE


/*
* Various BitScan implemenations
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

typedef unsigned int bsint_t;

#if defined( _M_ALPHA ) || defined( _M_IA64 ) || defined( _M_X64 ) || defined( _M_ARM64 ) \
	|| defined( _M_PPC64 ) || defined( _WIN64 ) || defined( __MINGW64__ )
# ifndef WORDSIZE
#  define WORDSIZE		64
# endif
# ifndef __WORDSIZE
#  define __WORDSIZE		WORDSIZE
# endif
# if __WORDSIZE != WORDSIZE
#  undef WORDSIZE
#  define WORDSIZE		__WORDSIZE
# endif
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
# pragma intrinsic( _BitScanForward )
# pragma intrinsic( _BitScanReverse )

# ifdef __cplusplus

_STATIC_ALWAYS_INLINE
unsigned char _BitScanForward( bsint_t *i, uint32_t m ) _IS_NOTHROW
{
	register unsigned long r;
	register const unsigned char s = _BSF32( &r, m );
	return *i = static_cast< bsint_t >( r ), s;
}

_STATIC_ALWAYS_INLINE
unsigned char _BitScanReverse( bsint_t *i, uint32_t m ) _IS_NOTHROW
{
	register unsigned long r;
	register const unsigned char s = _BSR32( &r, m );
	return *i = static_cast< bsint_t >( r ), s;
}

# endif		/* __cplusplus */

# if defined( __WORDSIZE ) && __WORDSIZE > 32

/* Prototypes: */
/*  unsigned char _BitScanForward64( unsigned long *_Index, unsigned __int64 _Mask ); */
/*  unsigned char _BitScanReverse64( unsigned long *_Index, unsigned __int64 _Mask ); */
#  define _BSF64( __i, __m )	_BitScanForward64( ( __i ), ( __m ) )
#  define _BSR64( __i, __m )	_BitScanReverse64( ( __i ), ( __m ) )
#  define _IS_BITSCAN64		1
#  pragma intrinsic( _BitScanForward64 )
#  pragma intrinsic( _BitScanReverse64 )

#  ifdef __cplusplus

_STATIC_ALWAYS_INLINE
unsigned char _BitScanForward64( bsint_t *i, uint64_t m ) _IS_NOTHROW
{
	register unsigned long r;
	register const unsigned char s = _BSF64( &r, m );
	return *i = static_cast< bsint_t >( r ), s;
}

_STATIC_ALWAYS_INLINE
unsigned char _BitScanReverse64( bsint_t *i, uint64_t m ) _IS_NOTHROW
{
	register unsigned long r;
	register const unsigned char s = _BSR64( &r, m );
	return *i = static_cast< bsint_t >( r ), s;
}

#  endif	/* __cplusplus */

# else		/* !__WORDSIZE || __WORDSIZE <= 32 */

#  ifndef WORDSIZE
#   define WORDSIZE		32
#  endif

# endif		/* __WORDSIZE && __WORDSIZE > 32 */

# ifndef __WORDSIZE
#  define __WORDSIZE		WORDSIZE
# endif
# if __WORDSIZE != WORDSIZE
#  undef WORDSIZE
#  define WORDSIZE		__WORDSIZE
# endif

#elif defined( __GNUC__ ) || defined( __INTEL_COMPILER )

# ifdef _IS_X64

_STATIC_ALWAYS_INLINE
unsigned char _BitScanForward( bsint_t *i, uint32_t m ) _IS_NOTHROW
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

_STATIC_ALWAYS_INLINE
unsigned char _BitScanForward64( bsint_t *i, uint64_t m ) _IS_NOTHROW
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

_STATIC_ALWAYS_INLINE
unsigned char _BitScanReverse( bsint_t *i, uint32_t m ) _IS_NOTHROW
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

_STATIC_ALWAYS_INLINE
unsigned char _BitScanReverse64( bsint_t *i, uint64_t m ) _IS_NOTHROW
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

# elif defined( _IS_386 )

_STATIC_ALWAYS_INLINE
unsigned char _BitScanForward( bsint_t *i, uint32_t m ) _IS_NOTHROW
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

_STATIC_ALWAYS_INLINE
unsigned char _BitScanReverse( bsint_t *i, uint32_t m ) _IS_NOTHROW
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

_STATIC_ALWAYS_INLINE
unsigned char _BitScanForward( bsint_t *i, uint32_t m ) _IS_NOTHROW
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

_STATIC_ALWAYS_INLINE
unsigned char _BitScanForward64( bsint_t *i, uint64_t m ) _IS_NOTHROW
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

_STATIC_ALWAYS_INLINE
unsigned char _BitScanReverse( bsint_t *i, uint32_t m ) _IS_NOTHROW
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

_STATIC_ALWAYS_INLINE
unsigned char _BitScanReverse64( bsint_t *i, uint64_t m ) _IS_NOTHROW
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

#  if _IS_ARM >= 7 ||/* _IS_ARM == 6 &&*/ \
	defined( _IS_THUMB ) && _IS_THUMB >= 4

_STATIC_ALWAYS_INLINE
#   if _IS_ARM < 7 && !defined( _IS_IN_THUMB )
__attribute__ ((target("thumb")))
#   endif
unsigned char _BitScanForward( bsint_t *i, uint32_t m ) _IS_NOTHROW
{
	register uint32_t nzf, tmp;
	__asm__ (
		"rbit	%1,%2\n\t"
		"clz	%1,%1\n\t"
		"sub	%0,%0,%1,lsr #5"
		: "=r" ( nzf ), "=r" ( tmp )
		: "r" ( m ), "0" ( 1 )
		:
		);
	*i = tmp;
	return ( unsigned char )nzf;
}

#   define _IS_BITSCANF32	1

#  endif

_STATIC_ALWAYS_INLINE
unsigned char _BitScanReverse( bsint_t *i, uint32_t m ) _IS_NOTHROW
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

# ifdef _IS_BITSCANF32

#  define _BSF32( __i, __m )	_BitScanForward( ( __i ), ( __m ) )

#  ifdef __cplusplus

_STATIC_ALWAYS_INLINE
unsigned char _BitScanForward( unsigned long *i, uint32_t m ) _IS_NOTHROW
{
	register bsint_t r;
	register const unsigned char s = _BSF32( &r, m );
	return *i = r, s;
}

#  endif	/* __cplusplus */

# endif		/* _IS_BITSCANF32 */

# ifdef _IS_BITSCANR32

#  define _BSR32( __i, __m )	_BitScanReverse( ( __i ), ( __m ) )

#  ifdef __cplusplus

_STATIC_ALWAYS_INLINE
unsigned char _BitScanReverse( unsigned long *i, uint32_t m ) _IS_NOTHROW
{
	register bsint_t r;
	register const unsigned char s = _BSR32( &r, m );
	return *i = r, s;
}

#  endif	/* __cplusplus */

# endif		/* _IS_BITSCANR32 */

# ifdef _IS_BITSCAN64

#  define _BSF64( __i, __m )	_BitScanForward64( ( __i ), ( __m ) )
#  define _BSR64( __i, __m )	_BitScanReverse64( ( __i ), ( __m ) )

#  ifdef __cplusplus

_STATIC_ALWAYS_INLINE
unsigned char _BitScanForward64( unsigned long *i, uint64_t m ) _IS_NOTHROW
{
	register bsint_t r;
	register const unsigned char s = _BSF64( &r, m );
	return *i = r, s;
}

_STATIC_ALWAYS_INLINE
unsigned char _BitScanReverse64( unsigned long *i, uint64_t m ) _IS_NOTHROW
{
	register bsint_t r;
	register const unsigned char s = _BSR64( &r, m );
	return *i = r, s;
}

#  endif	/* __cplusplus */

# endif		/* _IS_BITSCAN64 */

#endif

/* Trying to use WIN32 API implementation of absent functions */
#ifdef _WIN32

/* They're defined as macros in winnt.h */
# ifndef _WINNT_
#  ifndef WIN32_LEAN_AND_MEAN
#   define WIN32_LEAN_AND_MEAN
#  endif
#  ifndef STRICT
#   define STRICT
#  endif
#  include <windows.h>
# endif

# if !defined( _IS_BITSCANF32 ) && defined( BitScanForward )

/* Prototypes: */
/*  BOOLEAN BitScanForward( DWORD *Index, DWORD Mask ); */
#  define _BSF32( __i, __m )	BitScanForward( ( __i ), ( __m ) )
#  define _IS_BITSCANF32	1
#  pragma intrinsic( _BitScanForward )

#  ifdef __cplusplus

_STATIC_ALWAYS_INLINE
unsigned char BitScanForward( bsint_t *i, uint32_t m ) _IS_NOTHROW
{
	register DWORD r;
	register const BOOLEAN s = _BSF32( &r, m );
	return *i = static_cast< bsint_t >( r ), static_cast< unsigned char >( s );
}

#  endif	/* __cplusplus */

# endif		/* !_IS_BITSCANF32 && BitScanForward */

# if !defined( _IS_BITSCANR32 ) && defined( BitScanReverse )

/* Prototypes: */
/*  BOOLEAN BitScanReverse( DWORD *Index, DWORD Mask ); */
#  define _BSR32( __i, __m )	BitScanReverse( ( __i ), ( __m ) )
#  define _IS_BITSCANR32	1
#  pragma intrinsic( _BitScanReverse )

#  ifdef __cplusplus

_STATIC_ALWAYS_INLINE
unsigned char BitScanReverse( bsint_t *i, uint32_t m ) _IS_NOTHROW
{
	register DWORD r;
	register const BOOLEAN s = _BSR32( &r, m );
	return *i = static_cast< bsint_t >( r ), static_cast< unsigned char >( s );
}

#  endif	/* __cplusplus */

# endif		/* !_IS_BITSCANR32 && BitScanReverse */

# if !defined( _IS_BITSCAN64 ) && defined( BitScanForward64 ) && defined( BitScanReverse64 )

/* Prototypes: */
/*  BOOLEAN BitScanForward64( DWORD *Index, DWORD64 Mask ); */
/*  BOOLEAN BitScanReverse64( DWORD *Index, DWORD64 Mask ); */
#  define _BSF64( __i, __m )	BitScanForward64( ( __i ), ( __m ) )
#  define _BSR64( __i, __m )	BitScanReverse64( ( __i ), ( __m ) )
#  define _IS_BITSCAN64		1
#  if defined( __WORDSIZE ) && __WORDSIZE > 32
#   pragma intrinsic( _BitScanForward64 )
#   pragma intrinsic( _BitScanReverse64 )
#  endif

#  ifdef __cplusplus

_STATIC_ALWAYS_INLINE
unsigned char BitScanForward64( bsint_t *i, uint64_t m ) _IS_NOTHROW
{
	register DWORD r;
	register const BOOLEAN s = _BSF64( &r, m );
	return *i = static_cast< bsint_t >( r ), static_cast< unsigned char >( s );
}

_STATIC_ALWAYS_INLINE
unsigned char BitScanReverse64( bsint_t *i, uint64_t m ) _IS_NOTHROW
{
	register DWORD r;
	register const BOOLEAN s = _BSR64( &r, m );
	return *i = static_cast< bsint_t >( r ), static_cast< unsigned char >( s );
}

#  endif	/* __cplusplus */

# endif		/* !_IS_BITSCAN64 && BitScanForward64 && BitScanReverse64 */

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

#endif		/* _WIN32 */

#if defined( _IS_BITSCANF32 ) && defined( _IS_BITSCANR32 )
# define _IS_BITSCAN32		1
#endif


#endif		/* _ASSA_BITSCAN_H_INCLUDED */
