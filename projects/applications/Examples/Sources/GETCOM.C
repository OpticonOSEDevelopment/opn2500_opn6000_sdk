
/* getcom() */

#include <stdio.h>
#include "lib.h"

void main( void )
{
    int ch;

    systemsetting("SZ");
	
	comopen( COM2 );    // Open the COM port for cradle

    for(;;)
    {
        if( (ch = getcom( 0 )) != -1)
        {
            putchar( ch );
            putcom( ch );
        }

        if( (ch = getchar()) != EOF)
        {
            putchar( ch );
            putcom( ch );
        }

        idle();    // Very important to lower the power consumption
    }
}
