/****************************************************************************
*
*	bitscan.cpp	BitScan implementation test
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

#ifdef __cplusplus
# include <cstdlib>
# include <cstdio>
#else
# include <stdlib.h>
# include <stdio.h>
#endif
#include "bitscan.h"


#define PRINTM( __x )	printf( "%-12s : %lu\n", #__x, ( unsigned long )( __x ) )

#ifdef __cplusplus
using namespace std;

int main( )
#else
int main( void )
#endif
{
	unsigned long long input;
	unsigned result;
	unsigned status;

	fputs( "\nBitScan - Copyright (c) 2019 by Alexander M. Albertian <assa@4ip.ru>.\nAll rights reserved.\n\n", stdout );

	PRINTM( __WORDSIZE );

#ifdef _IS_X86
	PRINTM( _IS_X86 );
#endif
#ifdef _IS_386
	PRINTM( _IS_386 );
#endif
#ifdef _IS_X64
	PRINTM( _IS_X64 );
#endif
#ifdef _IS_ARM
	PRINTM( _IS_ARM );
#endif
#ifdef _IS_THUMB
	PRINTM( _IS_THUMB );
#endif
#ifdef _IS_IN_THUMB
	PRINTM( _IS_IN_THUMB );
#endif
#ifdef _IS_ARM64
	PRINTM( _IS_ARM64 );
#endif
#ifdef _IS_NEON
	PRINTM( _IS_NEON );
#endif

	fputs( "\nInput unsigned integer> ", stdout );
	scanf( "%llu", &input );

	printf( "\n32-bit input value: %lu\n", ( unsigned long )( uint32_t )input );
#ifdef _IS_BITSCANR32
	status = _BSR32( &result, ( uint32_t )input );
	printf( "_BSR32( %lu ): %u (Success=%u)\n", ( unsigned long )( uint32_t )input, result, status );
#endif
#ifdef _IS_BITSCANF32
	status = _BSF32( &result, ( uint32_t )input );
	printf( "_BSF32( %lu ): %u (Success=%u)\n", ( unsigned long )( uint32_t )input, result, status );
#endif
#ifdef _IS_BITSCAN64
	printf( "\n64-bit input value: %llu\n", input );
	status = _BSR64( &result, input );
	printf( "_BSR64( %llu ): %u (Success=%u)\n", input, result, status );
	status = _BSF64( &result, input );
	printf( "_BSF64( %llu ): %u (Success=%u)\n", input, result, status );
#endif

	return EXIT_SUCCESS;
}
