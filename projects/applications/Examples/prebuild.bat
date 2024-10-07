@echo off

echo Generating "version.c"
echo // !!!!AUTO GENERATED FILE by prebuild.bat!!!! > version.c
echo #include "lib.h" >> version.c
echo #ifdef APP_VERSION >> version.c
echo APP_VERSION_SECT const char APPversionstring[16] = APP_VERSION; >> version.c
echo #endif // APP_VERSION >> version.c