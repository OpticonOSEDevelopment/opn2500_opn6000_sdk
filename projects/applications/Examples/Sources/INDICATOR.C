
/* charging  indicator on OPN2003 */

#include <stdio.h>
#include "lib.h"

void main( void )
{
	for(;;)
    {
		if(triggerpressed())
			systemsetting("7G");		// Enabled
		else if(uppressed())
			systemsetting("8Z");		// Disabled
		else 
			systemsetting("U2");		// Default

		goodreadled(GREEN_FLASH, -1);

		WaitKey();
    }
}


