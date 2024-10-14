
#include <stdio.h>
#include "lib.h"

void main( void )
{
    int ch;

    ComOpen( COM9 );    // Open the COM port for USB-VCP

    for(;;)
    {
        if( (ch = GetCom( 0 )) != -1)
        {
            putchar( ch );
            PutCom( ch );
        }

        if( (ch = getchar()) != EOF)
        {
            putchar( ch );
            PutCom( ch );
        }
        Idle();    // Very important to lower the power consumption
    }
}
