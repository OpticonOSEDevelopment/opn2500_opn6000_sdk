
#include <stdio.h>
#include "lib.h"

void main( void )
{
    AutoPowerDown( ON, 10 * 50 );    // switch off after 10 sec
    printf("\nTesting\npowereddown..");

    for(;;)
    {
        if( PoweredDown())
        {
            printf("\nTerminal was\nswitched off!");
            Delay( 2 * 50 );
            printf("\nRunning again");
        }

        Idle();
    }
}
