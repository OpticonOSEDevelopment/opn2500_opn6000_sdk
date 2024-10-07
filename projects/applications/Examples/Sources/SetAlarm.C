// The following example demonstrates the use of SetAlarm() function.
#include <stdio.h>
#include "lib.h"

void main( void )
{
    struct time AlarmTime = {0};

	autopowerdown(ON, 5*50);				// 5 Seconds idle time until power down
	autopowerdown(APD_SHUTDOWN_ON, 20*50);	// 20 Seconds until shut down. However, auto shut down is deactivated when a user alarm is set!!!!

	for(;;)
    {
		if(powereddown())					// Returns true once after being powered down or restart
		{
			sound( TSTANDARD, VHIGH, SMEDIUM, SHIGH, 0);

			gettime( &AlarmTime );					// Get current time
    
			AlarmTime.ti_sec = 0;
			AlarmTime.ti_min += 1;					// Set Alarm to next minute
			
			if(AlarmTime.ti_min >= 60)
			{
				AlarmTime.ti_min -= 60;

				if(++AlarmTime.ti_hour >= 24)
					AlarmTime.ti_hour = 0;
			}

			SetAlarm(&AlarmTime, ON);				// Configure the Alarm
		}

		idle();								// Reduces the power consumption
	}
}

