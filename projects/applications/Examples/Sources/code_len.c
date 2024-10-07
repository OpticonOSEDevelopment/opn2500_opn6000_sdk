#include <stdio.h>
#include "lib.h"

const char Length_Test_Table[][16] =
{
	"H0",
	"H0S",
	"H07G",
	"H08Z",
	"H0ZZ",
	"H1",
	"H1S",
	"H17G",
	"H18Z",
	"H1ZZ",
	"H110",
	"H110S",
	"H1107G",
	"H1108Z",
	"H110ZZ",
	"H11005",
	"H11005S",
	"H110057G",
	"H110058Z",
	"H11005ZZ",
	"H110057GS",
	"H1100506",
	"H1100506S",
	"H11005067G",
	"H11005068Z",
	"H1100506ZZ",
	"HK",
	"HKS",
	"HK7G",
	"HK8Z",
	"HK_",
	"HK_z",
	"HK_C",
	"HK_V",
	"HK_V0",
	"HK_VS",
	"HK_V7G",
	"HK_V8Z",
	"HK_VA0",
	"HK_V10",
	"HK_V10S",
	"HK_V107G",
	"HK_V108Z",
	"HK_V10ZZ",
	"HK_V1006",
	"HK_V10_V06",
	"HK_V10_V067G",
	"HK_V10_V068Z",
	"HK_V10_V06ZZ",
	"HK_V10_V06ZZ",
	"HK_V10_N10",
	"HK_V10_V06_N10",
	"HK_V10_$06",
	"HK_V10_V06_V0X",
	"HL",
	"HLS",
	"HL7G",
	"HL8Z",
	"HL_",
	"HL_z",
	"HL_C",
	"HL_V",
	"HL_V0",
	"HL_VS",
	"HL_V7G",
	"HL_V8Z",
	"HL_VA0",
	"HL_V09",
	"HL_V10",
	"HL_V11",
	"HL_V10S",
	"HL_V107G",
	"HL_V108Z",
	"HL_V10ZZ",
	"HL_V10_V06",
	"HL_V10_N10",
	"HL_V10_N107G",
	"HL_V10_N108Z",
	"HL_V10_N10",
	"HL_V10_V06_N10",
	"HL_V10_$06",
	"HM",
	"HMS",
	"HM7G",
	"HM8Z",
	"HM_",
	"HM_z",
	"HM_C",
	"HM_V",
	"HM_V0",
	"HM_VS",
	"HM_V7G",
	"HM_V8Z",
	"HM_VA0",
	"HM_V09",
	"HM_V10",
	"HM_V11",
	"HM_V10S",
	"HM_V107G",
	"HM_V108Z",
	"HM_V10ZZ",
	"HM_V10_V06",
	"HM_V10_N10",
	"HM_V10_N107G",
	"HM_V10_N108Z",
	"HM_V10_N10",
	"HM_V10_V06_N10",
	"HM_V10_$06",
};


void main( void )
{
	char bcr_buf[42] = {0};
	struct barcode code = {0};
	int key;
	int i = 0;
	int result;

	code.min   = 1;
	code.max   = 41;
	code.text  = bcr_buf;

	systemsetting("U2YC");					// Always make sure menu-labels are enabled after a restart

    scannerpower(TRIGGER | SINGLE, 250);    // Trigger mode, 5 seconds read time, laser off after 1 barcode


	for(;;)
	{
		if(kbhit())
		{
			key = getchar();
			
			if (key == CLR_KEY)
			{
				sound(TCLICK, VSTANDARD, SMEDIUM, 0);

				if (i < (sizeof(Length_Test_Table)/16)-1)
					i++;
			}

			printf("\rSystemSetting:\n%s", Length_Test_Table[i]);

			systemsetting("U2YC");
			
			result = systemsetting(Length_Test_Table[i]);
			if (result == ERROR)
				printf("\r settings ERROR");
			else
				printf("\r setting ok");

			resetkey();
		}

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
                               delay(TSTANDARD * 4);        // Wait till buzzer sound ends before saving (saving flash settings temp. turns of sound timer)

                               while(triggerpressed())      // Wait for release before resetting read mode
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
                           case ERROR:
                               break;
                        }
                    }
                }
            }
			else
			{
				printf("\n%s\n",code.text);
				goodreadled(GREEN, 10);
				sound( TSTANDARD, VHIGH, SMEDIUM, SHIGH, 0);
			}

        }
		idle();
	}
}


