
#include <stdio.h>
#include "lib.h"

void main( void )
{
    unsigned char packet[] = "22-\xFF\xFF";   //SYN,SYN,ENQ,PAD,PAD
    
   ComOpen( COM9 );    // Open the COM port for USB-VCP

    PutBuffer(packet, 5);

    for(;;)
    {
        Idle();    // Very important to lower the power consumption
    }
}
