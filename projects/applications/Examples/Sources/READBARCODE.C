
/* readbarcode  */

// This program reads and outputs a barcode. After each successful barcode reading,
// it gives a good read signal on the LED and a buzzer signal.

#include <stdio.h>
#include "lib.h"

void main( void )
{
    char bcr_buf[42] = {0};
    struct barcode code = {0};

    code.min   = 3;
    code.max   = 41;
    code.text  = bcr_buf;

    scannerpower(SINGLE | TRIGGER, 100);        // Single read

    for(;;)
    {
        if(readbarcode(&code) == OK)
        {
             goodreadled(GREEN, 10);
             sound( TSTANDARD, VHIGH, SMEDIUM, SHIGH, 0);
             printf("%s\n",code.text);
        }

		idle();
    }
}
