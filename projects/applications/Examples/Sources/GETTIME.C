
/* gettime() & GetDate() */

#include <stdio.h>
#include "lib.h"

// The following example shows the current date and time on the display.

void main( void )
{
    struct time t;
    struct date d;

    for(;;)
    {
        gettime(&t);
        GetDate(&d);

		printf("\r\nTime: %2d:%02d:%02d", t.ti_hour, t.ti_min, t.ti_sec);
        printf("\r\nYear: %d", d.da_year);
        printf("\r\nDay : %d", d.da_day);
        printf("\r\nMon : %d", d.da_mon);
        
		delay(10);	// Update time every 0,2 second
    }
}

