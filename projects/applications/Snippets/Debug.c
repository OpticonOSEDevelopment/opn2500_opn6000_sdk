//------------------------------------------------------------------------------
// OPN2001 simulation app for OPN2004/5/6 and PX20 based on RRF35100
//
// Debug.c
//
// Author: Ronny de Winter
// Company: Opticon Sensors Europe BV
//------------------------------------------------------------------------------

// Includes
#include "lib.h"
#include "Debug.h"
#include "string.h"

// Defines

#ifdef DEBUG
// Global Variables
char debugBuffer[256];
#endif

// Local Variables


// Function Prototypes
int putcom2(int port, unsigned char data); // Hiddem function in Startup.o
char* itoa(int val, char *buf, int base);  // Hiddem function in Startup.o

void PutString2(int port, char *str)
{
	int i;

	for(i=0; i<strlen(str); ++i)
		putcom2(port, str[i]);
}
