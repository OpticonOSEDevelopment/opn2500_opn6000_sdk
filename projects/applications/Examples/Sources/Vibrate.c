// This program reads and displays a barcode. After each successful barcode reading,
// it gives a good read signal on the LED, a buzzer signal and vibrates.
//
// Note that an extra check is made on the minimum length when the barcode symbology
// is one of the 2 of 5 codes, or Codabar. This is done because of the poor
// specifications of these symbologies.
// Note the use of a loop, repeatedly invoking ReadBarcode().

#include <stdio.h>
#include "lib.h"

void main( void )
{
    char bcr_buf[42];
    struct barcode code;

    code.min   = 1;
    code.max   = 41;
    code.text  = bcr_buf;

    ScannerPower(ON, 250);

    for(;;)
    {
        if( ReadBarcode( &code ) == OK)
        {
            GoodReadLed(GREEN, 10);
            Sound(TSTANDARD, VHIGH, SMEDIUM, SHIGH, 0);
            Vibrate(TSTANDARD);
            printf("%s\n",code.text);
        }
        Idle();
    }
}
