//
// DBaseCsv.C(PP)
//
// implementation of the CSV database file handling 
// functions.
//
// Martin Jansen
//

#include <string.h>
#include "boards.h"
#include "lib.h"
#include "ff.h"
#include "DBaseCsv.h"
#include "index.h"
#include "Database.h"

#ifdef WIN32
	#include <io.h>
#else
	//#include "WaitCurs.h"
#endif
#include "lib.h"
#include "ff.h"

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

int CsvGetField( char *fieldBuffer, const char *buffer, int fieldNr, int maxFieldSize, int delimiter )
{
	int inQuote = 0;
	int fieldCount = 0;
	char ch;
	int fieldDataSize = 0;
	
	if(fieldBuffer != NULL)
		fieldBuffer[0] = '\0';

	for(;;)
	{
		if( buffer == NULL || *buffer == '\0' || *buffer == '\r' || *buffer == '\n' )
			return -100;	// HACK HACK HACK

		if( (inQuote = ( *buffer == '\"' )) != 0 )
			buffer++;	// Skip the quote

		if( fieldCount == fieldNr )
		{
			// Found the field nummer now copy the data
			// until the next delimiter or terminator
			while( ((ch = *buffer) != 0) && ch != '\r' && ch != '\n' && ((!inQuote && (*buffer != (char)delimiter )) || inQuote) )
			{
				if( ch == '\"' )
				{
					buffer++;
					inQuote = 0;
					continue;
				}
				if(fieldBuffer != NULL)
					*fieldBuffer++ = ch;

				fieldDataSize++;
				buffer++;
				if( fieldDataSize >= maxFieldSize )
				{
					if(fieldBuffer != NULL)
						*fieldBuffer = '\0';
					return fieldDataSize;
				}
			}
			if(fieldBuffer != NULL)
				*fieldBuffer = '\0';

			return fieldDataSize;	// HACK HACK HACK the length of the field
		}

		while( *buffer && ((!inQuote && (*buffer != (char)delimiter )) || inQuote))
		{
			if( *buffer == '\"' )
				inQuote = 0;
			buffer++;
		}
		if( *buffer == '\0' || *buffer == '\r' || *buffer == '\n' )
			return -1;
		buffer++;
		fieldCount++;
	}
}

/*
int CsvBuildIndex( SDBOutVal *dbOut, const char *idxName, int delimiter, int fieldNr, int dup )
{
	static ENTRY e;
	int error;
	long filePos = 0L;
	int fieldLength;

    if(dbOut->fdDb == NULL || dbOut->ix.ixfile == NULL)
        return ERR_OPEN_DATABASE;

	if( idxName == NULL )
		return ERR_OPEN_INDEX; 

	if( MakeIndex( idxName, &dbOut->ix, dup ) == IX_FAIL )
	{
		CloseDatabase(dbOut);
		return ERR_OPEN_INDEX; 
	}

	error = OK;

	while( f_gets(g_Record, MAX_RECORD_SIZE, dbOut->fdDb ) > 0 )
	{
		// parse the csv string and use the field number as new index value
		if( (fieldLength = CsvGetField( g_fieldBuffer, g_Record, fieldNr, MAX_G_FIELD, delimiter )) < 0 )
		{
			// empty record line or empty field
			// continue with indexing next record
			filePos = f_tell(dbOut->fdDb);
			continue;
		}
		if( fieldLength == 0 )
		{
			// empty record line or empty field
			// continue with indexing next record
			filePos = f_tell(dbOut->fdDb);
			continue;
		}
		
		e.key = hash(g_fieldBuffer);
		e.recptr  = (RECPOS)filePos;

		// Add the key to the indexing file
		if( AddKey( &e, &dbOut->ix ) != IX_OK )
		{
			error = ERR_INDEX_DUPLICATE;
			break;
		}
		filePos = f_tell(dbOut->fdDb);
	}

    CloseDatabase(dbOut);
	return error;
}

int CsvRebuildIndex(  SDatabaseItem *dbItem, SDBOutVal *dbOut )
{
	int ret;

	if(dbItem->idxFilename == NULL)
	{
		dbOut->ix.ixfile = NULL;
		return DATABASE_OK;
	}

	if( (ret = CsvBuildIndex( dbOut, dbItem->idxFilename, dbItem->csvChar, dbItem->keyfield, dbItem->flags & F_DB_APPEND )) < OK )
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
*/

int CsvOpenDatabase( SDatabaseItem *dbItem, SDBOutVal *dbOut )
{
	int ret;

	if( f_open(dbOut->fdDb, dbItem->dbFilename, FA_READ | FA_WRITE) != FR_OK )
		return ERR_OPEN_DATABASE;

	if( dbItem->idxFilename == NULL )
	{
		dbOut->ix.ixfile = NULL;
	}
	else if(OpenIndex( dbItem->idxFilename, &(dbOut->ix), dbItem->flags & F_DB_APPEND ) != IX_OK )
	{
		if( (ret = CsvBuildIndex( dbOut, dbItem->idxFilename, dbItem->csvChar, dbItem->keyfield, dbItem->flags & F_DB_APPEND )) < OK )
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


int CsvCreateDatabase( SDatabaseItem *dbItem, SDBOutVal *dbOut )
{
	if( f_open(dbOut->fdDb, dbItem->dbFilename, FA_CREATE_ALWAYS | FA_WRITE) != FR_OK )
		return ERR_OPEN_DATABASE;

	if(dbItem->idxFilename == NULL)
	{
		dbOut->ix.ixfile = NULL;
	}
	else if(MakeIndex( dbItem->idxFilename, &(dbOut->ix), dbItem->flags & F_DB_APPEND ) != IX_OK )
	{
		f_close( dbOut->fdDb );
		return ERR_OPEN_INDEX;	// Error creating the index file 
	}

	return DATABASE_OK;
}


