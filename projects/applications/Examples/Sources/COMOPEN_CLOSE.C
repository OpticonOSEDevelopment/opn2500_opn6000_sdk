
/* comopen & comclose */

/* Opens BLE HID port (and default USB COM-port) and inndicate status */

#include <stdio.h>
#include "lib.h"

void main( void )
{
    int ch, open = FALSE;

	char bcr_buf[42] = {0};
    struct barcode code = { .min = 3, .max = 41 };

    code.text  = bcr_buf;

	comopen(COM10);				// Open the COM port for BLE HID
	
	SystemSetting("BPV");		// Set interface independent default suffix: <CR> (VCP) / Enter key (HID)
		
    for(;;)
    {
		if(BltIsConnected() || UsbIsConnected())
		{
			if(!open)
			{
				open = TRUE;
				Sound(TVLONG, VHIGH, SHIGH, 0);
			}
			
		}
		else 
		{
			if(open)
			{
				open = FALSE;
				sound(TVLONG, VHIGH, SLOW, 0);
			}
		}

		if(readbarcode(&code) == OK)
        {
             goodreadled(GREEN, 10);
             
             if( PutString(code.text) == OK)
				sound( TSTANDARD, VHIGH, SMEDIUM, SHIGH, 0);
			else 
				sound( TSTANDARD, VHIGH, SLOW, 0);
        }

        idle();    // Very important to lower the power consumption
    }
}
