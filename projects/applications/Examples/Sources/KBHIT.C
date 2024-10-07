
/* kbhit() */

#include <stdio.h>
#include "lib.h"

void main( void )
{
    int color = GREEN;

    for(;;)
    {
         printf("\nPress any key");

         while(!kbhit())
            idle();

         resetkey();

         goodreadled(color, 50);        // ON, 1 second

         color = (color == GREEN) ? (RED) : (GREEN);
    }
}

 