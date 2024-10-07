
/* uppressed() & downpressed() */

#include "lib.h"
#include <stdio.h>

void main( void )
{
    printf("\fPress up\nor down key!");
    
	for(;;)
    {
        if( uppressed() )
            sound( TSTANDARD, VHIGH, SHIGH, 0);

        if( downpressed() )
            sound( TSTANDARD, VHIGH, SMEDIUM, 0);

        idle();
    }
}

