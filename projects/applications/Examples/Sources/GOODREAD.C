
/* goodreadled() */

#include <stdio.h>
#include "lib.h"

void main( void )
{
    int x;

    for(;;)
    {
        for( x=0; x < 10; x++)
        {
            goodreadled( RED, 25);
            delay( 50 );
            goodreadled( GREEN, 25);
            delay( 50 );
        #ifdef BLUE
            goodreadled( BLUE, 25);
            delay( 50 );
        #endif
        }
        goodreadled( RED, -1);
        delay( 200 );
        goodreadled( RED, 0);
        goodreadled( GREEN, -1);
        delay( 200 );
        goodreadled( GREEN, 0);
    #ifdef BLUE
        goodreadled( BLUE, -1);
        delay( 200 );
        goodreadled( BLUE, 0);
    #endif
    }
}
