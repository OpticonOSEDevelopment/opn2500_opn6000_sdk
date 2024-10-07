@echo off

echo Generating "version.c"
echo // !!!!AUTO GENERATED FILE by prebuild.bat!!!! > ..\..\Source\version.c
echo #include "lib.h" >> ..\..\Source\version.c
echo #ifdef APP_VERSION >> ..\..\Source\version.c
echo APP_VERSION_SECT const char APPversionstring[16] = APP_VERSION; >> ..\..\Source\version.c
echo #endif // APP_VERSION >> ..\..\Source\version.c