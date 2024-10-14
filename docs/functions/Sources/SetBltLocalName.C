
#include <stdio.h>
#include "lib.h"

void main( void )
{
    for(;;)
    {
        printf("\nchange localn\n%s\nto\nEXAMPLE NAME", GetBltLocalName());
        ResetKey();
        while( !kbhit() )
            Idle();
        SetBltLocalName("EXAMPLE NAME");

        printf("\nLocalname:\n%s", GetBltLocalName() );
        ResetKey();
        while( !kbhit() )
            Idle();
    }
}
