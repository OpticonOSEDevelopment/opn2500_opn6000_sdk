#include <stdio.h>
#include <stdlib.h>
#include "lib.h"

void main( void )
{
    unsigned char *block_1, *block_2;

    for(;;)
    {
    	while( getchar() == EOF )
            idle();

		sound(TCLICK, VHIGH, SHIGH, 0);

        printf("\r1: mem = %lu", Heap_CoreLeft());

        while( getchar() == EOF )
            idle();

		sound(TCLICK, VHIGH, SHIGH, 0);

        block_1 = malloc(5000L);

        printf("\r2: mem = %lu", Heap_CoreLeft());

        while( getchar() == EOF )
            idle();

		sound(TCLICK, VHIGH, SHIGH, 0);

        block_2 = malloc(10000L);

        printf("\r3: mem = %lu", Heap_CoreLeft());

        while( getchar() == EOF )
            idle();

		sound(TCLICK, VHIGH, SHIGH, 0);

        free(block_1);

        printf("\r4: mem = %lu", Heap_CoreLeft());

        while( getchar() == EOF )
		    idle();

		sound(TCLICK, VHIGH, SHIGH, 0);

        free(block_2);

        printf("\r5: mem = %lu", Heap_CoreLeft());
    }
}
