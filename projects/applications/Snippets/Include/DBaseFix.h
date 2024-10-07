//
// DBaseFix.h
//
// Fixed size Database helper functions
// 
// Martin Jansen
// 


#ifndef __DBASE_FIX_H__
#define __DBASE_FIX_H__

#include "database.h"

int FixOpenDatabase( SDatabaseItem *dbItem, SDBOutVal *dbOut );
int FixCreateDatabase( SDatabaseItem *dbItem, SDBOutVal *dbOut );
void FixCloseDatabase( SDBOutVal *dbOut );

int FixBuildIndex( SDBOutVal *dbOut, const char *idxName, int offset, int fieldLength, int dup );
int FixRebuildIndex( SDatabaseItem *dbItem, SDBOutVal *dbOut );

int FixGetField( char *fieldBuffer, const char *buffer, int offset, int maxFieldLength );

#endif // __DBASE_FIX_H__

