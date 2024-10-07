/* coreleft() */

#include <stdio.h>
#include <string.h>
#include "lib.h"

unsigned char buzzer_enabled;

// Customized default
void Custom_Default(void)
{
    systemsetting("U2");            // Inherit OS menu option "U2"
    systemsetting("A0");            // Enable all decoders
    buzzer_enabled = TRUE;
    systemsetting("YC");            // Enable menu labels
}

//
// The following table implements systemsetting options that need to be added to the OS or overruled
//
// Note: The use of 'systemsetting()' inside the functions in the table below is limited to protect against recursion.
//       It is still possible to use systemsetting() but only with 1 menu option per function call.
//
const OPTION menu_option_table[] =
{                                                // CLEAR mask                              SET mask (use 0xFF 0xFF in case of a function call)
    { "U2",(void*)Custom_Default,                   0xFF,                                   0xFF                        },
    { "W0",(void*)&(buzzer_enabled),                0x01,                                   0x00                        },
    { "W8",(void*)&(buzzer_enabled),                0x00,                                   0x01                        },
};

#define MAX_OPTIONS sizeof(menu_option_table)/sizeof(OPTION)


void main( void )
{
    char bcr_buf[42] = {0};
    struct barcode code  = {0};
    int result;

    //
    // The following function implements systemsettings / menu options that aren't present in the OS or need to be overruled
    //
    AddMenuOptionTable(menu_option_table, MAX_OPTIONS);

    systemsetting("U2");        // Reset to customized default

    code.min   = 1;
    code.max   = 41;
    code.text  = bcr_buf;

    scannerpower(TRIGGER | SINGLE, 250);    // Trigger mode, 5 seconds read time, laser off after 1 barcode

    for(;;)
    {
        if(readbarcode(&code) == OK)
        {
            result = 0;

            if(code.id == MENU_CODE)
            {
                scannerpower(ON, -1);        // Scanner on indefinitely

                while(result != EXITING_MENU_MODE && result != ERROR)
                {
                    if(result == 0 || readbarcode(&code) == OK)
                    {
                       switch( (result=ExecuteMenuLabel(&code)) )
                       {
                           case ENTERING_MENU_MODE:
                               sound(TSTANDARD, VHIGH, SHIGH, SMEDIUM, SHIGH, 0);
                               break;

                           case EXITING_MENU_MODE:
                               scannerpower(OFF, 0);
                               sound(TSTANDARD,VHIGH, SHIGH, SMEDIUM, SHIGH, 0);

                               while(triggerpressed())               // Wait for release before resetting read mode
                                   idle();

                               scannerpower(TRIGGER | SINGLE, 250);  // Reset read mode, because it's turned off after reading menu labels
                               break;

                           case INVALID_OPTION_READ:
                               sound(TLONG, VHIGH, SLOW, 0);
                               break;

                           case VALID_OPTION_READ:
                               sound(TSTANDARD, VHIGH, SHIGH, SMEDIUM, SHIGH,0);
                               break;

                           case LABEL_IGNORED:
							   break;

                           case ERROR:
							   scannerpower(OFF, 0);

							   while(triggerpressed())               // Wait for release before resetting read mode
                                   idle();

                               scannerpower(TRIGGER | SINGLE, 250);  // Reset read mode, because it's turned off after reading menu labels
                               break;
                        }
                    }
                }
            }
            else
            {
                if(buzzer_enabled)        // Read menu option "W0" and "W8" to enable/disabled the buzzer
                    sound(TSTANDARD, VHIGH, SMEDIUM, SHIGH, 0);

                goodreadled(GREEN, 10);
            }
        }

        idle();        // Reduces power consumption
    }
}
