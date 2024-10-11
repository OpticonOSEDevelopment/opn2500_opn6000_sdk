
// This example will sound the buzzer when the down key is pressed

#include <stdio.h>
#include "lib.h"

void main(void)
{
	printf("\nPress the function key!");
	for (;;)
	{
		if (DownPressed())
			Sound(TSTANDARD, VHIGH, SMEDIUM, 0);

		Idle();
	}
}
