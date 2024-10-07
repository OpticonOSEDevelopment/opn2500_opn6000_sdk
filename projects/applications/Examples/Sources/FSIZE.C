
/*  fsize()  */

#include <stdio.h>
#include <stdlib.h>
#include "lib.h"

void main( void )
{
	const char data[13] = "Hello World!";
	long size;
	FILE *fp;
    
	printf("\fPress a key");

	for(;;)
    {
		resetkey();
        while( !kbhit())
            idle();

		printf("\f");

	    // Open for appending or else create (binary) file
        if( (fp = fopen("TEST.DAT","a+")) == NULL)
        {
            printf("\nError opening\nTEST.DAT");
            continue;
        }

		if( fwrite(data, 1, 12, fp) != 12 )
			printf("\nError writing\nTEST.DAT");

        fclose(fp);

        size = fsize("TEST.DAT");
        
		if( size > -1)
		{
            printf("\nSize = %ld bytes", size);
			printf("\nMem = %lu", coreleft());
		}
        else
            printf("\nTEST.DAT cannot\nbe found!");
    }
}
