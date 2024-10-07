
/* setRTS() / setDTR() */

#include <stdio.h>
#include "lib.h"

void main( void )
{
    int ch, rts=0, dtr=0;
	
	comopen( COM9 );			// USB-VCP COM-port

    for(;;)
    {
        if( (ch = getcom( 0 )) != -1)
        {
			sound(TSTANDARD, VHIGH, ch*100, 0);		// Beep on incoming data
        }

        if( (ch = getchar()) != EOF)
        {
			if(ch == TRIGGER_KEY)
			{
				setRTS(rts);
				rts = (rts) ? 0 : 1;
			}
			else // CLR_KEY
			{
				setDTR(dtr);
				dtr = (dtr) ? 0 : 1;
			}
        }
        idle();    // Important to lower the power consumption
    }
}
