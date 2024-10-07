
/* idle() */

#include <stdio.h>
#include "lib.h"

// The following example demonstrates the use of idle() and the power reduction.
// The example may reduce power consumption by about 2-4 times!

void main( void )
{
    unsigned int x;
    
	for(;;)
    {
        printf("\fidle loop");

        for( x=0; x < 200; x++)
            idle();
        
		printf("\nnormal loop");
        
		for( x=0; x < 100000; x++)
            continue;
    }
}
