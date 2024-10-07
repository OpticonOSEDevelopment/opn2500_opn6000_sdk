
/*  version_os()  */

#include "lib.h"
#include <stdio.h>

void main(void)
{
	static char os[9+1];
	int key;

	resetkey();
	printf("\fPress TRIGGER key");

	for(;;)
	{
		if ((key =getchar()) != EOF)
		{
			resetkey();
			switch (key)
			{
			case TRIGGER_KEY:
				sound(TSTANDARD,VHIGH,SHIGH,0);
				version_os(os);
				printf("\nO/S = %s", os);
				break;
			default:
				sound(TCLICK,VHIGH,SLOW,0);
				break;
			}
		}
		idle();
	}
}
