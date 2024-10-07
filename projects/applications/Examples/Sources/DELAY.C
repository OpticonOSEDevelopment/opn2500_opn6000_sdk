
/* delay() */

#include <stdio.h>
#include "lib.h"

void main(void)
{
	for(;;)
    {
    	printf("Hello world.");
        delay(100);     /* show the message on the screen for 2 seconds */
		printf("\f");
		delay(100);
	}
}

