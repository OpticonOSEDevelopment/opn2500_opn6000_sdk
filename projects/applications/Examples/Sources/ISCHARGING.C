
/* ischarging  */

#include <stdio.h>
#include "lib.h"

void main( void )
{
    int previous_state, current_state;

    previous_state = -1;

    while( 1 )
    {
        current_state = ischarging();
        if( current_state != previous_state)
        {
            previous_state = current_state;
            switch( current_state )
            {
            #if PHL | PHL1000 | PHL2700 | OPH | OPH1004
                case 0:
                    printf("Not charging\n");
                    break;
                case 1:
                    printf("Charging\n");
                    break;
                case 2:
                    printf("Completed\n");
                    break;
                case 3:
                    printf("Disabled\n");
                    break;
            #else
                case 0:
                    printf("Not in cradle\n");
                    break;
                case 1:
                case 2:
                case 4:
                    printf("Slow charging\n");
                    break;
                case 3:
                    printf("Quick charging\n");
                    break;
                case 5:
                    printf("Completed\n");
                    break;
            #endif
            }
        }
        idle();
    }
}
