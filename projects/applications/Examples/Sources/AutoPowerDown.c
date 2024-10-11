
/* autopowerdown */

#include <stdio.h>
#include "lib.h"

void main( void )
{
    autopowerdown(ON, 2*50);				// 1 Seconds until power down
	
	autopowerdown(APD_SHUTDOWN_ON, 10*50);	// 10 Seconds until shut down

	if(IsColdBoot())		// True is the reset was caused by a power off
		sound(TSTANDARD, VHIGH, SLOW, SMEDIUM, SHIGH, SLOW, SMEDIUM, SHIGH, 0);	// Start-up beep
	else
		sound(TSTANDARD, VHIGH, SMEDIUM, SHIGH, SMEDIUM, 0);	// Start-up beep

	delay(TSTANDARD * 6);       // Wait till buzzer sound ends
		
	for(;;)
	{
		if(powereddown())		// Returns true once after being powered down or restart
		{
			sound(TCLICK, VHIGH, SHIGH, 0);
		}

		idle();
	}
}

