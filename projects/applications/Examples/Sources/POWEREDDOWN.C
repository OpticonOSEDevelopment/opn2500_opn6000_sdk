
/* powereddown() */

#include <stdio.h>
#include "lib.h"

void main( void )
{
	for(;;)
    {
		if( powereddown())
        {
			printf("\fTerminal was\nswitched off!");
            delay( 50 );
            printf("\fRunning again");
        }

    }
}
