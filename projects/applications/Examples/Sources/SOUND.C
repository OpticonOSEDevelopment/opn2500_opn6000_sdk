
/* sound() */

#include "lib.h"
#include <stdio.h>

void main(void)
{
	for(;;)
	{
      sound(TCLICK,VHIGH,SERROR,SPAUSE,SLOW,SPAUSE,SMEDIUM,SPAUSE,SHIGH,0);
      delay(200); // Wait 4 sec

      sound(TSTANDARD,VHIGH,SERROR,SPAUSE,SLOW,SPAUSE,SMEDIUM,SPAUSE,SHIGH,0);
      delay(200);

      sound(TLONG,VHIGH,SERROR,SPAUSE,SLOW,SPAUSE,SMEDIUM,SPAUSE,SHIGH,0);
      delay(200);

      sound(TVLONG,VHIGH,SERROR,SPAUSE,SLOW,SPAUSE,SMEDIUM,SPAUSE,SHIGH,0);
      delay(200);
	}
}

