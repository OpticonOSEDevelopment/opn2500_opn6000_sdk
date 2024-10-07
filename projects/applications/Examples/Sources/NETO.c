#include "lib.h"
#include <stdio.h>
#include <string.h>

//
// This function fills the file name array with all 
// the files that are present on the RAM disk
//
int GetFileList(char (*filename)[MAX_FNAME])		
{
	int nr;
	struct ffblk finddata;

	nr = 0;
	if (findfirst("*.*", &finddata ) == OK)
	{
		do
		{
			sprintf(filename[nr++], "%s.%s", finddata.name, finddata.ext);
		}while ((nr<10) && (findnext(&finddata) == OK));
	}
	return nr;
}

//
// This application demonstrates the sending and receiving of files using 
// The NetO protocol by sending back all the files that it receives 
// from the host.
//
void main(void)
{
    char ftest[10][MAX_FNAME];
    int test, test2;

	char serial_number[6+1];

	sprintf(serial_number, "%-6.6lu",  GetSerialNumber());		// Convert the serial number to a 6-digit string

	comopen(COM0);

	for(;;)
	{
		test = neto_receive( ftest, serial_number, CLR_KEY, 3);

		if (test < 0)
		{
			sound(TSTANDARD, VHIGH, SLOW, 0);
		}
		else
		{
			test2 = neto_transmit( ftest, test, serial_number, CLR_KEY, 3);

			if (test2 < 0)
			{
				sound(TSTANDARD, VHIGH, SHIGH, 0);
			}
		}
	}
}

