
#include <stdio.h>
#include "lib.h"

const char string[] = "Hello world";

void main(void)
{
    char c, *s;

    AutoPowerDown(ON, 1*50); // 1 second
    AutoPowerDown(APD_SHUTDOWN_ON, 60*50); // 60 seconds

    s = (char*)string;
    while ((c = *s) != '\0')
    {
        putchar(c);
        Delay(50);
        s++;
    }

    for (;;)
        Idle();
}
