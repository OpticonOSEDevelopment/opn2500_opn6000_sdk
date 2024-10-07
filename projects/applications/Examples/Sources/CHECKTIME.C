
/* checktime */

#include <stdio.h>
#include "lib.h"

void app_main( void )
{
    struct time t;

    t.ti_hour = 12;
    t.ti_min = 12;
    
    for(;;)
    {
        t.ti_sec = 62;
        
        if( checktime( &t ) == OK )
            printf("\fTime ok!!\n");
        else
            printf("\fIllegal time!!");
            
        while( !kbhit() )
            Idle();
            
        resetkey();

        t.ti_sec = 12;
        
        if( checktime( &t ) == OK )
            printf("\fTime ok!!\n");
        else
            printf("\fIllegal time!!");

        while( !kbhit() )
            idle();
        
		resetkey();
    }
}

