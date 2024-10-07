
/* resetreceive */

#include <stdio.h>
#include "lib.h"

void main( void )
{
    int ch;

	comopen(COM9);    // Open the COM port for USB-VCP
	
    for(;;)
    {
		while(!triggerpressed())	// Buffer all data as long as trigger is not pressed
		{
			if(uppressed())			// Reset receive buffer when the small clear key is pressed
				resetreceive();

			idle();    // Reduces power consumption
		}
        
		if( (ch = getcom( 0 )) != -1)	// Echo all receive data
			putchar( ch );
    }
}
