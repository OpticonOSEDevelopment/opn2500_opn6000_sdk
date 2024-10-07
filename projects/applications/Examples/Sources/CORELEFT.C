/* coreleft() */

#include <stdio.h>
#include <string.h>
#include "lib.h"

int main( void )
{
    const char data[] = {"Hello World Example Program To Demonstrate The Function 'coreleft'"};

    FILE *fp;
	
    for(;;)
    {
		while( getchar() == EOF )
            idle();

        printf("\r1: mem = %lu", coreleft());
        
		while( getchar() == EOF )
            idle();
		
		if( (fp = fopen("TEST.DAT", "wb")) != NULL )	// Store a file in RAM
        {
            fwrite( data, 1, 1000, fp);
            fclose(fp);
        }
		
        printf("\r2: mem = %lu", coreleft());
		
		while( getchar() == EOF )
            idle();

		if( (fp = fopen("TEST2.DAT", "wb")) != NULL )	// Store a file in RAM
        {
            fwrite( data, 1, 5000, fp);
            fclose(fp);
        }
		
        printf("\r3: mem = %lu", coreleft());

		while( getchar() == EOF )
            idle();

		if( (fp = fopen("TEST3.DAT", "wb")) != NULL )	// Store a file in RAM
        {
            fwrite( data, 1, 1000, fp);
            fclose(fp);
        }
		
        printf("\r4: mem = %lu", coreleft());
		
		while( getchar() == EOF )
            idle();

		if( (fp = fopen("TEST4.DAT", "wb")) != NULL )	// Store a file in RAM
        {
            fwrite( data, 1, 8000, fp);
            fclose(fp);
        }

		printf("\r5: mem = %lu", coreleft());

		format();										// Format RAM disk (remove all files)
    }
}


