
/* starttimer(), timervalue(), endtimer() */

#include <stdio.h>
#include "lib.h"

void main(void)
{
	for(;;)
	{
		printf("\fTimer of 5 sec");
		
		starttimer(255);
		
		while(!endtimer())
		{
			printf("\nTime left %d s", timervalue()/50);
			sound(TSTANDARD, VSTANDARD, SMEDIUM,0);
			delay(50);
		}
		
		printf("\nDone");
		resetkey();

		while(!kbhit())
			idle();
	}
}
