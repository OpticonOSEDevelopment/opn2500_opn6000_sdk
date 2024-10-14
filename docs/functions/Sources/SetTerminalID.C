
#include <stdio.h>
#include "lib.h"

void main( void )
{
    SetTerminalId( 1234 );

    printf("\nterminal ID\n%d", GetTerminalId() );

    for(;;)
        Idle();
}
