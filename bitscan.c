/****************************************************************************
*
*	bitscan.c	BitScan implementation test
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


#ifdef __cplusplus
int main( )
#else
int main( void )
#endif
{
	unsigned long long input;
	unsigned result;
	unsigned status;

	printf( "\n%-12s : %u\n", "WORDSIZE", ( unsigned )__WORDSIZE );

#ifdef _IS_ARM
	printf( "%-12s : %u\n", "_IS_ARM", ( unsigned )_IS_ARM );
#endif
#ifdef _IS_THUMB
	printf( "%-12s : %u\n", "_IS_THUMB", ( unsigned )_IS_THUMB );
#endif
#ifdef _IS_IN_THUMB
	printf( "%-12s : %u\n", "_IS_IN_THUMB", ( unsigned )_IS_IN_THUMB );
#endif
#ifdef _IS_ARM64
	printf( "%-12s : %u\n", "_IS_ARM64", ( unsigned )_IS_ARM64 );
#endif

	fputs( "\nInput unsigned integer> ", stdout );
	scanf( "%llu", &input );

	printf( "\n32-bit input value: %lu\n", ( unsigned long )( uint32_t )input );
#ifdef _IS_BITSCANF32
	status = _BSF32( &result, ( uint32_t )input );
	printf( "_BitScanForward( %lu ): %u (Success=%u)\n", ( unsigned long )( uint32_t )input, result, status );
#endif
#ifdef _IS_BITSCANR32
	status = _BSR32( &result, ( uint32_t )input );
	printf( "_BitScanReverse( %lu ): %u (Success=%u)\n", ( unsigned long )( uint32_t )input, result, status );
#endif
#ifdef _IS_BITSCAN64
	printf( "\n64-bit input value: %llu\n", input );
	status = _BSF64( &result, input );
	printf( "_BitScanForward64( %llu ): %u (Success=%u)\n", input, result, status );
	status = _BSR64( &result, input );
	printf( "_BitScanReverse64( %llu ): %u (Success=%u)\n", input, result, status );
#endif

	return EXIT_SUCCESS;
}
