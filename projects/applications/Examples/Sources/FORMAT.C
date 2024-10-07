

/* format()  */


#include "lib.h"
#include <stdio.h>
#include <stdlib.h>

void main(void)
{	
	const char data[2000] = { "Hello world\n" };
	FILE *fp;

	for(;;)
	{	
		printf("\fDisk space: %lu", coreleft());
		
		if( (fp = fopen("TEST.DAT", "wb")) != NULL )
		{	
			fwrite(data, 1, 2000, fp);
			fclose(fp);
		}

		printf("\n- File written -");
		printf("\nDisk space: %lu", coreleft());
		
		format();
		printf("\n- Disk Formatted -");

		printf("\nDisk space: %lu", coreleft());
		
		resetkey();
		while (!kbhit())
			idle();
	}
}

