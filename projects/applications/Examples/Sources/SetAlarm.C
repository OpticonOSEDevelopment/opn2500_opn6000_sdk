
// The following example demonstrates the use of SetAlarm() function.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"

void main( void )
{
    struct time at = {0};
    struct time t = {0};

    AutoPowerDown(ON, 1*50); // 1 second
    AutoPowerDown(APD_SHUTDOWN_ON, 60*50); // 60 seconds

    ResetKey();

    for(;;)
    {
        at.ti_hour = 12;
        at.ti_min = 0;
        at.ti_sec = 0;

        SetAlarm( &at, ON);
		
        printf("\nALARM SET\n%02d:%02d\nwaiting...", at.ti_hour, at.ti_min);
        for(;;)
        {
            GetTime( &t );
            ResetKey();
            //
            // Check to see if terminal is woken by the Alarm function
            //
            if( (t.ti_hour == at.ti_hour) && (t.ti_min == at.ti_min))
            {
                //
                // Wakeup was done by alarm...
                //
                for(;;)
                {
                    printf("\nALARM\nALARM");
                    Sound( TSTANDARD, VHIGH, SERROR, SLOW, SMEDIUM, SHIGH, SLOW, SMEDIUM, SHIGH, 0);
                    Delay( 50 );
                    if( kbhit())
                    {
                        ResetKey();
                        break;
                    }
                }
                break;
            }
            Delay( 50 );
        }
    }
}

