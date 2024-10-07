// This program reads barcodes by both the trigger key and the small clear key. 
// After each successful decode it shows a good read LED and makes a buzzer sound.

#include <stdio.h>
#include "lib.h"

void main( void )
{
	int ch;
	char bcr_buf[42] = {0};
	struct barcode code = {0};

	static int last_key_pressed = -1;	// Used to determine whether a barcode was read using the clear key or trigger key

	code.min   = 3;
	code.max   = 41;
	code.text  = bcr_buf;

	ClearKeyAsTrigger(TRUE);			// This function makes it possible to use the small clear key 
										// as additional trigger key to enable the laser and read barcodes. 

	scannerpower(SINGLE|TRIGGER, 250);	// Single read / Trigger mode / 5 seconds

	for(;;)
	{
		if( (ch=getchar()) > 0 ) 
			last_key_pressed = ch;		// Used to determine whether a barcode was read using the clear key or trigger key
		
		if(readbarcode(&code) == OK)
		{
			if(last_key_pressed == TRIGGER_KEY)
				goodreadled(GREEN, 10);
			else
				goodreadled(ORANGE, 10);

			sound( TSTANDARD, VHIGH, SMEDIUM, SHIGH, 0);
			printf("%s\n",code.text);
		}

		idle();
	}
}
