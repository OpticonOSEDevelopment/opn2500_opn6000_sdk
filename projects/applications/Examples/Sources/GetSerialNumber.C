#include <stdio.h>
#include <string.h>
#include "lib.h"

void main(void)
{
    for(;;)
	{
		resetkey();

		while(!kbhit())
			idle();
		
		printf("\rSerial: %06ld", GetSerialNumber());
		sound(TSTANDARD, VHIGH, SHIGH, 0);
	}
}

