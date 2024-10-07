
/* GetBatteryVoltage_mV() */

#include <stdio.h>
#include <stdlib.h>
#include "lib.h"

void main( void )
{
    unsigned int i=0, voltage[5] = {0};

	printf("\fBattery voltage (with 15s delay):");

	autopowerdown(OFF, 0);

    for(;;)
    {
		voltage[i] = GetBatteryVoltage_mV();

		printf("\r%dmV", voltage[(i+1) % 5]);		// Show voltage of 15 seonds earlier
		
		delay(3*50);

		if(++i == 5)
			i=0;

	}	
}		

