// The code fragment below installs a callback function
// that is executed by the operating system every 20ms.
// The callback makes sure that the red LED is switched
// on for a short time every 2 seconds.
#include <stdio.h>
#include "lib.h"

void Callback(void)
{
    static int counter=100;

    if (--counter == 0)
    {
        GoodReadLed(RED,10);
        counter = 100;
    }

}

void main( void )
{
    printf("\nTimer callback");

    InstallHeartbeatHandler(Callback);

    while(1)
    {
        if (kbhit())
        {
            if (getchar() == TRIGGER_KEY)
                RemoveHeartbeatHandler(Callback);
        }
        Idle();
    }
}
