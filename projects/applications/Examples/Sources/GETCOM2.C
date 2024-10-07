
/* getcom2() */

#include <stdio.h>
#include "lib.h"

void main( void )
{
    int ch;

    comopen( COM2 );    // Open the COM port for the cradle

    for(;;)
    {
        if( (ch = getcom2(COM2, 0)) != -1)
        {
            putchar(ch);
            putcom2(COM2, ch);
        }

        if( (ch = getchar()) != EOF)
        {
            putchar(ch);
            putcom2(COM2, ch);
        }

        idle();    // Very important to lower the power consumption
    }
}
