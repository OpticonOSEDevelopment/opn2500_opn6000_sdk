
// This example will sound the buzzer when the trigger key is being pressed

#include <stdio.h>
#include "lib.h"

void main( void )
{
    printf("\nPress trigger!");
    for(;;)
    {
        if( TriggerPressed() )
            Sound( TSTANDARD, VHIGH, SMEDIUM, 0);
        Idle();
    }
}
