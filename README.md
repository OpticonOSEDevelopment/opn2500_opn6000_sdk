# opn6000_opn2500-sdk

This is the official SDK from Opticon Sensors Europe BV for the Companion Scanners OPN-2500 and OPN-6000

The prerequisites for using this SDK are:
- Latest SDK files from this repository
- SEGGER Embedded Studio for ARM (download from here: https://www.segger.com/downloads/embedded-studio/)
- Appload firmware upload application for Windows (https://www.opticon.com/support/Appload/Appload%20Setup.exe)

- Opticon USB Drivers (download from here: https://www.opticon.com/support/Drivers/USB%20Drivers%20Installer.exe)

The SEGGER Embedded studio can be licensed for free when using devices with a Nordic CPU like the OPN-6000 / OPN-2500
For more inf see: https://wiki.segger.com/Get_a_License_for_Nordic_Semiconductor_Devices
It can be useful to attach a nRF52 DK board to you PC, see the license is automatically recognized, although not it's not necessary to build applications

**** Getting started *****

- Download and extract this complete repository into a working folder

- Download and install the latest Opticon USB drivers

- Download and install the latest Appload version 

- Install the SEGGER Embedded Studio for ARM

**** SDK Files *******
This SDK contains the following components

/firmware
    /bootloader
            FAMVxxx.HEX     -> Bootloader of the OPN6000
            FANVxxxx.HEX    -> Bootloader of the OPN2500
    
    /library
            OPN2500_FBNVxxxx.a  -> OPN2500 Operating System library file
            OPN6000_FBMVxxxx.a  -> OPN6000 Operating System library file

/include
            lib.h               -> OS library include file
            lib_legacy.h        -> Legacy OS library with legacy lower-case function names, file system and defines (for porting existing application)
            Debug.h             -> Used for debugging
            /FileSystem         -> Header files for the FatFs Generic file system (http://elm-chan.org/fsw/ff/FileSystem)
            (other OS related header files)
/mdk
            OPN2500 / OPN6000 / nRF528xx header specific header files
/nrfutil
            nrfutil.exe Nordic tool for signing and packing bootloader, softdevice, OS and application

/softdevice
            /MBR        -> Master boot record (starts the bootloader)
            /S113       -> Compiled softdevice S113 (Bluetooth BLE wireless protocol stack for nRF52840 Nordic CPU)
            /Common     -> Softdevice header files
            
/toolchain
            /CMSIS      -> provides software components for retargeting I/O operations in standard C run-time libraries

/documentation      
            OPN-6000 User Manual.pdf    (latest version is always available at https://www.opticon.com/support/OPN-6000/OPN-6000%20User%20Manual.pdf)
            OPN-2500 User Manual.pdf    (latest version is always available at https://www.opticon.com/support/OPN-2500/OPN-2500%20User%20Manual.pdf)

***** Applications ******

In the folder Projects/Applications, 2 applications can be found that are installed on the OPN2500/OPN6000 by default. They provide a good starting point when only small customizations are required:

BatchApplication
    -> Batch application to demonstrate using the OPN as batch device and communication using USB-MSD and OseComm

BluetoothAppl
    -> Bluetooth application to demonstrate Bluetooth BLE Serial, HID and OptiConnect as well as USB-HID, USB-CDC and USB-VCP and memorizing

Snippets
    -> Source files used by both applications for storing, updating and exporting bar code data in the file system

- Open the projects file: BatchApplication\Projects\ses\Batch_Appl.emProject or BluetoothAppl\Projects\ses\Bluetooth_Appl.emProject

- After building, the resulting .bin file can be found in the root folder of the applications and loaded using Appload

- The User Manuals of the OPN-2500 and OPN-6000 in the SDK provide more information on how to use these applications

****** EXAMPLES ******

In the folder Projects/Examples, you'll find small example applications for all basic peripheral functions of the OPN-2500 / OPN-6000 
    
- Open the projects file: 'OPN_Examples.emProject' in Segger IDE

- In the 'Project explorer', right click the source files and use the 'Exclude from build' option to select which sample application to build.

- After building, the resulting .bin file can be found in the /Output folder and loaded using Appload

****** Loading of Firmware ******

- See 'documentation/How to load Firmware.pdf' for more information on how to load the resulting .bin files on to the OPN-2500 / OPN-6000

****** Trouble Shooting ******

By default, the OPN will have the USB-VCP COM-port enabled, which makes it possible to load firmware using Appload over USB. 
In application where this COM-port is not enabled (i.e. USB-MSD) or when the application has crashed, use this method to enter firmware update mode:

- Press and hold both the trigger and function key for at least 15 seconds. 
- After the companion scanner LED turns white, release the function first to enter firmware update mode.
- If successful, the LED of your companion scanner should now be blinking red. 

You should now be able to load new firmware using Appload or OptiConnect. 
To exit firmware update mode, press both keys for 3 seconds (or wait 30 seconds).

****** OptiConnect ******

OptiConnect is a free application developed by Opticon to configure and manage the OPN series of barcode scanners and your bar code data. 

It is available on all platforms and can be found here:
https://opticon.com/opticonnect/

To connect your OPN to the OptiConnect app:
1. Download and install the OptiConnect app from your app store or go to https://opticonnect.opticon.com (available for iOS, Android, Mac OS and Windows).
2. Make sure the OPN-6000 is set to BLE mode by scanning the label in the quick start guide.
3. In OptiConnect, go to ‘Pair Scanner,’ and select the discovered ‘OPN-6000’ or 'OPN-25000' to connect

A Flutter SDK is available for mobile app developers to use the OptiConnect functionality in your own application:
https://github.com/OpticonOSEDevelopment/opticonnect_sdk_flutter

****** OptiConfigure ******

Opticon barcode readers can be customized using configuration barcodes. All available configurations for each device can be found here: 

OPN-6000: https://opticonfigure.opticon.com/configure?scanner=OPN6000
OPN-2500: https://opticonfigure.opticon.com/configure?scanner=OPN2500

The SystemSetting()-function in the SDK makes it possible to use these configurations in your own application.

<code>int SystemSetting( const char *option_string );</code>

Note that 3-letter menu codes should be prefixed with the character '['. Likewise, 4-letter menu codes should be prefixed with the character ']'. 

Example: 
<code>SystemSetting("[BCM");  // BCM: Enable all 1D codes excl. add-on</code>

****** Porting existing OPN-2006 / PX-20 / RS-3000 applications ******

New features in OPN-6000 / OPN-2500
•   BLE OptiConnect service (BLE and USB)
•   Bluetooth Device Firmware Update (DFU) (via OptiConnect)
•   Bluetooth BLE HID supported (replaces Bluetooth Classic HID)
•   Both USB-VCP (default) and USB-CDC driver are supported
•   Bluetooth, Batch and OPN2001 application merged into a single default application
•   New defaults (default firmware):
    o   OPND: OseComm data collector mode (previously Batch application + ‘C01’)
    o   BPC: Switch to USB-CDC (Serial scanner mode)
    o   BQZ: Switch to USB-CDC (OPN2001 mode)
    o   U2: OPN-2001 default

Removed / missing features from OPN6000
•   Bluetooth Classic (HID/SPP) is not supported
•   Scanning of Bluetooth address labels to connect is removed (BLE is always slave)
•   Setting of Pin code not supported
•   NetO protocol is no longer supported (OseComm is recommended as alternative)

Changed default behaviour (Bluetooth application)
•   Bluetooth BLE HID is set as factory default
•   Device immediately becomes discoverable when pressing the trigger key
•   Memorizing enabled (when not connected) is enabled by default
•   Memorizing option: ‘Trigger to send’ is enabled in BLE HID and USB-HID mode
•   Keyboard toggle on iOS is now enabled by default
•   'Trigger to connect(able)’ is implemented on the function key, not the trigger
•   OPN6000 switches into OPN2001 mode after receiving an OPN2001 interrogate command
•   Manual reset, by pressing both keys for 15 seconds, results in white LED. Release function key to enter bootloader
•   Device can enter sleep mode in all connection status (except when connect to USB), which greatly improves battery life when connected to Bluetooth.
•   Function key can be used to remove barcodes when connected to OptiConnect (and when memorizing)
•   Default Bluetooth local name is OPN6000_(serial) instead of OPN6000_(MAC Address), because mobile platforms often hide the Bluetooth address nowadays for privacy reasons

File system / database functions
•   Since the Bluetooth, Batch and OPN2001 application are merged into a single default application, each application now stores its barcode data in the same formatting, which makes it possible to switch between applications without loosing your data.
•   Because barcode data is stored in a fixed file format (SCANNED.DAT / SCANNED.IDX). The batch application generates the CSV-file with the configured formatting as soon as the USB-cable is connected instead of while scanning
•   USB-MSD file system is now 'read/write' instead of 'read/only' because issues that could case the filesystem to be corrupted by Windows on the OPN-2006/PX-20 have been resolved
•   The OPN-6000/OPN-2500 makes use of ChaN's FatFS fileystem, which uses file system functions like f_open and f_close ("ff.h" and "FileSystem.h"). For backwards compatiblity the "stdio.h" functions like 'fopen' and 'fclose' are supported using a wrapper. Low-level I/O functions open/close/read/write are no longer supported.

Source code
- In case your application is derived from the OPN-2006 batch application it is recommended to add your customizations to the new Batch application instead of porting the OPN-2006 based application, because it's been optimized for and tested with the new scanners
- In case your application is derived from the OPN-2006 Bluetooth demo, it is recommended to add your customizations to the new Bluetooth application instead of porting the OPN-2006 based application, because it's been optimized for and tested with the new scanners


