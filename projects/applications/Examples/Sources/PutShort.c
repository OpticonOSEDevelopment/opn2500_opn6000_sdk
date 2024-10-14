
#include <stdio.h>
#include "lib.h"

void main( void )
{
    unsigned short ch;
    unsigned char c;
    int counter = 0;

    ComOpen( COM9 );    // Open the COM port for USB-VCP

    for(;;)
    {
        if( (c = getchar()) != EOF)
        {
            putchar( c );
			
            if (counter == 0)
            {
                ch = c;
                ch <<= 8;
                counter++;
            }
            else
            {
                ch |= c;
                PutShort( ch );
                counter = 0;
            }
        }
        Idle();    // Very important to lower the power consumption
    }
}
