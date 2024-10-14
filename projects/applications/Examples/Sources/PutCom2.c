
#include <stdio.h>
#include "lib.h"

void main( void )
{
    int ch;

    ComOpen( COM9 );    // Open the COM port for USB-VCP

    for(;;)
    {
        if( (ch = GetCom2( COM9, 0 )) != -1)
        {
            putchar( ch );
            PutCom2( COM9, ch );
        }

        if( (ch = getchar()) != EOF)
        {
            putchar( ch );
            PutCom2( COM9, ch );
        }
        Idle();    // Very important to lower the power consumption
    }
}
