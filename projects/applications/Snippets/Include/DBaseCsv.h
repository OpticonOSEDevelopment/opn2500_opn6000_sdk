//
// DBaseCsv.h
//
// CSV Database helper functions
// 
// Martin Jansen
// 

#ifndef __DBASE_CSV_H__
#define __DBASE_CSV_H__

#include "database.h"

int CsvOpenDatabase( SDatabaseItem *dbItem, SDBOutVal *dbOut );
int CsvCreateDatabase( SDatabaseItem *dbItem, SDBOutVal *dbOut );
//void CsvCloseDatabase( SDBOutVal *dbOut );
int CsvRebuildIndex(  SDatabaseItem *dbItem, SDBOutVal *dbOut );

int CsvBuildIndex( SDBOutVal *dbOut, const char *idxName, int separator, int fieldNr, int dup );

int CsvGetField( char *fieldBuffer, const char *buffer, int fieldNr, int maxFieldSize, int delimiter );

//int SearchDatabase( SDatabaseItem *dbItem, SDBOutVal *dbOut, const char *searchItem, char *outputBuffer );

#endif // __DBASE_CSV_H__

