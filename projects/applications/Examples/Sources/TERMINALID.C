
/* getterminalid() & setterminalid() */

#include <stdio.h>
#include "lib.h"

void main( void )
{
   // Function Prototypes
   extern int SetSerialNumber(char *serial); // hidden in jumptable (not listed in lib.h)

   SetSerialNumber("100812");

   while(!triggerpressed())
	   idle();

   printf("\fterminal ID\n%d", GetSerialNumber() );

   for(;;)
        idle();
}
