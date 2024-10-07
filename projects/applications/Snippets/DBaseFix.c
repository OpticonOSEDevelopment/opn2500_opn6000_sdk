#include <string.h>
#include "boards.h"
#include "lib.h"
#include "ff.h"
#include "DBaseFix.h"
#include "index.h"

#if defined(WIN32)
	#include <io.h>
#endif
#include "lib.h"
#include "ff.h"
#include "FileSystem.h"

#ifdef WIN32
	#define open		_open
	#define close		_close
	#define read		_read
	#define write		_write
	#define lseek		_lseek
	#define O_RDWR		_O_RDWR 
	#define O_BINARY	_O_BINARY
	#define O_CREAT		_O_CREAT 
	#define O_TRUNC		_O_TRUNC  
#endif

extern char g_fieldBuffer[];

int FixGetField( char *fieldBuffer, const char *buffer, int offset, int fieldLength )
{
	if( buffer == NULL || buffer[0] == '\0')
		return -1;
	strncpy( fieldBuffer, buffer + offset, fieldLength );
	fieldBuffer[ fieldLength ] = '\0';
	return fieldLength;
}

int FixBuildIndex( SDBOutVal *dbOut, const char *idxName, int offset, int maxFieldLength, int dup )
{
	static ENTRY e;
	int error;
	long filePos = 0L;
	int fieldLength;

    if(dbOut->fdDb == NULL || dbOut->ix.ixfile == NULL)
        return ERR_OPEN_DATABASE;

    if( idxName == NULL )
		return ERR_OPEN_INDEX; 

	if(MakeIndex( idxName, &dbOut->ix, dup ) == IX_FAIL )
	{
        CloseDatabase(dbOut);
		return ERR_OPEN_INDEX; 
	}
	error = OK;

	while( f_gets(g_Record, MAX_RECORD_SIZE, dbOut->fdDb ) > 0 )
	{
		// Fixed record string
		if( (fieldLength = FixGetField( g_fieldBuffer, g_Record, offset, maxFieldLength  )) < 0 )
		{
			error = fieldLength; 
			goto build_index_error;
		}
		
		e.key = hash(g_fieldBuffer, fieldLength);
		e.recptr = (RECPOS)filePos;

		// Add the key to the indexing file
		if( AddKey( &e, &dbOut->ix ) != IX_OK )
		{
			error = ERR_INDEX_DUPLICATE;
			goto build_index_error;
		}
		filePos = f_tell( dbOut->fdDb );
	}

build_index_error:
	CloseDatabase(dbOut);
	return error;
}

int FixRebuildIndex(  SDatabaseItem *dbItem, SDBOutVal *dbOut )
{
	int ret;

	if( (ret = FixBuildIndex( dbOut, dbItem->idxFilename, dbItem->field[ dbItem->keyfield ].offsetField, dbItem->field[ dbItem->keyfield ].maxField, dbItem->flags & F_DB_APPEND )) < OK )
	{
		// Error while creating index file, so remove it
		f_unlink( dbItem->idxFilename );
		return ret;	// ERROR!!!!
	}

	if( OpenIndex( dbItem->idxFilename, &(dbOut->ix), dbItem->flags & F_DB_APPEND ) != IX_OK )
		return ERR_OPEN_INDEX;

    if( f_open(dbOut->fdDb, dbItem->dbFilename, FA_READ | FA_WRITE) != FR_OK )
		return ERR_OPEN_DATABASE;

	return DATABASE_OK;
}


int FixOpenDatabase( SDatabaseItem *dbItem, SDBOutVal *dbOut )
{
	int ret;
	long lookupSize = 0L;

	if( (lookupSize = fsize(dbItem->dbFilename)) == -1L )
		return ERR_OPEN_DATABASE;

	if( (lookupSize % dbItem->maxRecordSize) != 0 )
		return ERR_DB_WRONG_FORMAT;

    if( f_open(dbOut->fdDb, dbItem->dbFilename, FA_READ | FA_WRITE) != FR_OK )
		return ERR_OPEN_DATABASE;

	if( dbItem->idxFilename == NULL )
	{
		dbOut->ix.ixfile = NULL;
	}
	else if( OpenIndex( dbItem->idxFilename, &(dbOut->ix), dbItem->flags & F_DB_APPEND ) != IX_OK )
	{
		if( (ret = FixBuildIndex( dbOut, dbItem->idxFilename, dbItem->field[ dbItem->keyfield ].offsetField, dbItem->field[ dbItem->keyfield ].maxField, dbItem->flags & F_DB_APPEND )) < OK )
		{
			// Error while creating index file, so remove it
			f_unlink( dbItem->idxFilename );
			return ret;	// ERROR!!!!
		}	

		if( OpenIndex( dbItem->idxFilename, &(dbOut->ix), dbItem->flags & F_DB_APPEND ) != IX_OK )
			return ERR_OPEN_INDEX;

        if( f_open(dbOut->fdDb, dbItem->dbFilename, FA_READ | FA_WRITE) != FR_OK )
			return ERR_OPEN_DATABASE;
	}
	return DATABASE_OK;
}

int FixCreateDatabase( SDatabaseItem *dbItem, SDBOutVal *dbOut )
{
    if( f_open(dbOut->fdDb, dbItem->dbFilename, FA_CREATE_ALWAYS | FA_WRITE) != FR_OK )
		return ERR_OPEN_DATABASE;

	if( dbItem->idxFilename == NULL )
	{
		dbOut->ix.ixfile = NULL;
	}
	else if( MakeIndex( dbItem->idxFilename, &(dbOut->ix), dbItem->flags & F_DB_APPEND ) == IX_OK )
	{
		return DATABASE_OK;
	}
	
	f_close( dbOut->fdDb );
	return ERR_OPEN_INDEX;	// Error creating the index file 
}


