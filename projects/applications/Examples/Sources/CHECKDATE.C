
/* checkdate */

#include <stdio.h>
#include "lib.h"

void main( void )
{
    struct date d;

    d.da_year = 2023;
    d.da_mon = 2;

    for(;;)
    {
        d.da_day = 29; // not 29 days in non leap year

        if( checkdate( &d ) == OK )
            printf("\fDate ok!!\n");
        else
            printf("\fIllegal Date!!");
        
		while( !kbhit() )
            idle();
        
		resetkey();

        d.da_day = 28;
        
		if( checkdate( &d ) == OK )
            printf("\fDate ok!!\n");
        else
            printf("\fIllegal Date!!");
        
		while( !kbhit() )
            idle();
        
		resetkey();
    }
}
