
/*  triggerpressed()  */

#include <stdio.h>
#include "lib.h"

void main(void)
{
	printf("\fPress trigger!");

    for(;;)
    {
    	if (triggerpressed())
        	sound(TSTANDARD, VHIGH, SMEDIUM, 0);
        idle();
    }
}

