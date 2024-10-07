
//
// Database.c(pp)
//
// Implementation Database functions that finally call the fix or the csv database functions
// 
// Martin Jansen
// 
//#include "stdafx.h"
#include <setjmp.h>
#include <string.h>
#include "boards.h"
#include "lib.h"
#include "ff.h"
#include "database.h"
#include "dbasecsv.h"
#include "dbasefix.h"

#if defined(WIN32)
#include <io.h>
#endif

char g_Record[MAX_RECORD_SIZE];


int OpenBarcodeDatabase(const char* filename, const char *idx_file, SDBOutVal *dbOut) 
{
	int ret;

	if( f_open(dbOut->fdDb, filename, FA_READ | FA_WRITE) != FR_OK )
		return ERR_OPEN_DATABASE;

	if(idx_file != NULL && OpenIndex( idx_file, &(dbOut->ix), TRUE ) != IX_OK )
	{
		f_close( dbOut->fdDb );
		return ERR_OPEN_INDEX;	// Error creating the index file 
	}

	return DATABASE_OK;
}

int CreateBarcodeDatabase(const char* filename, const char *idx_file, SDBOutVal *dbOut) 
{
	if( f_open(dbOut->fdDb, filename, FA_CREATE_ALWAYS | FA_WRITE) != FR_OK )
		return ERR_OPEN_DATABASE;

	if(idx_file != NULL && MakeIndex( idx_file, &(dbOut->ix), TRUE ) != IX_OK )
	{
		f_close( dbOut->fdDb );
		return ERR_OPEN_INDEX;	// Error creating the index file 
	}

	return DATABASE_OK;
}

void CloseBacodeDatabase(SDBOutVal *dbOut) 
{
	// Close the index file
	if (dbOut->ix.ixfile != NULL)
		CloseIndex(&(dbOut->ix));

	// Close the database file
	f_close(dbOut->fdDb);

	dbOut->fdDb = NULL;
}

int IsBarcodeDatabaseOpen(SDBOutVal *dbFile) 
{
	if (dbFile->fdDb == NULL)
		return ERR_OPEN_DATABASE;

	if (dbFile->ix.ixfile == NULL)
		return ERR_OPEN_INDEX;

	return DATABASE_OK;
}

int ReadBarcodeRecord(SDBOutVal *dbFile, ENTRY *e, struct barcode *pCode) 
{
	int bytes_read;

	pCode->length = e->length;
	pCode->id = e->code_id;
	pCode->quantity = e->quantity;

	TimeStampToDateTime(e->timestamp, &pCode->date, &pCode->time );

	if( f_lseek(dbFile->fdDb, e->recptr) != FR_OK )
		return ERR_INDEX_KEY_NF; // TODO: maybe change this in some other value

	if( f_read(dbFile->fdDb, &pCode->text, e->length, &bytes_read) != FR_OK || bytes_read != e->length )
		return ERR_INDEX_KEY_NF; // TODO: maybe change this in some other value

	return DATABASE_OK;
}

int SearchBarcodeDatabase(SDBOutVal *dbFile, struct barcode *pCode, int origin, long offset, ENTRY *pFoundEntry) 
{
	ENTRY e;
	int error;

	pFoundEntry = NULL;

	if ((error = IsBarcodeDatabaseOpen(dbFile)) != DATABASE_OK)
		return ERROR;

	e.key = hash(pCode->text, pCode->length);
	e.code_id = pCode->id;
	e.quantity = pCode->quantity;

	dbFile->ix.duplicate = TRUE;

	switch(origin)
	{
		case SEEK_SET:
			if ( (pFoundEntry = FindFirstKey(&e, &(dbFile->ix))) == NULL)
				return ERR_INDEX_KEY_NF;
			break;

		case SEEK_END:
			if ( (pFoundEntry = FindLastKey(&e, &(dbFile->ix))) == NULL)
				return ERR_INDEX_KEY_NF;
			break;

		case SEEK_CUR:
			if(offset >= 0)
			{
				if ( (pFoundEntry = FindNextKey(&e, &(dbFile->ix))) == NULL)
					return ERR_INDEX_KEY_NF;
			}
			else
			{
				if ( (pFoundEntry = FindPrevKey(&e, &(dbFile->ix))) == NULL)
					return ERR_INDEX_KEY_NF;
			}
			break;
	}

	return DATABASE_OK;
}

int ReadFirstBarcode(SDBOutVal *dbFile, struct barcode *pCode, ENTRY *pFoundEntry) 
{
	static ENTRY e;
	
	if (IsBarcodeDatabaseOpen(dbFile) != DATABASE_OK)
		return ERROR;

	if (FirstKey(&e, &(dbFile->ix)) != IX_OK)
		return ERROR;

	pFoundEntry = &e;
	return ReadBarcodeRecord(dbFile, &e, pCode);
}

int ReadLastBarcode(SDBOutVal *dbFile, struct barcode *pCode, ENTRY *pFoundEntry) 
{
	static ENTRY e;
	
	if (IsBarcodeDatabaseOpen(dbFile) != DATABASE_OK)
		return ERROR;

	if (LastKey(&e, &(dbFile->ix)) != IX_OK)
		return ERROR;

	pFoundEntry = &e;

	if(pCode == NULL)
		return DATABASE_OK;

	return ReadBarcodeRecord(dbFile, &e, pCode);
}

int ReadPreviousBarcode(SDBOutVal *dbFile, struct barcode *pCode, ENTRY *pFoundEntry) 
{
	static ENTRY e;

	if (IsBarcodeDatabaseOpen(dbFile) != DATABASE_OK)
		return ERROR;

	if (PrevKey(&e, &(dbFile->ix)) != IX_OK)
		return ERROR;

	pFoundEntry = &e;
	return ReadBarcodeRecord(dbFile, &e, pCode);
}

int ReadNextBarcode(SDBOutVal *dbFile, struct barcode *pCode, ENTRY *pFoundEntry) 
{
	static ENTRY e;

	if (IsBarcodeDatabaseOpen(dbFile) != DATABASE_OK)
		return ERROR;

	if (NextKey(&e, &(dbFile->ix)) != IX_OK)
		return ERROR;

	pFoundEntry = &e;
	return ReadBarcodeRecord(dbFile, &e, pCode);
}

int ReadCurrentBarcode(SDBOutVal *dbFile, struct barcode *pCode, ENTRY *pFoundEntry) 
{
	static ENTRY e;

	if (IsBarcodeDatabaseOpen(dbFile) != DATABASE_OK)
		return ERROR;

	if (CurrentKey(&e, &(dbFile->ix)) != IX_OK)
		return ERROR;

	pFoundEntry = &e;
	return ReadBarcodeRecord(dbFile, &e, pCode);
}

int DeleteCurrentBarcode(SDBOutVal *dbFile) 
{
	static ENTRY e;

	if (IsBarcodeDatabaseOpen(dbFile) != DATABASE_OK)
		return ERROR;

	if (CurrentKey(&e, &(dbFile->ix)) != IX_OK)
		return ERROR;

	if(e.quantity <= 0)
		return ERROR;

	return WriteBarcode(dbFile, &e, NULL);
}

int WriteBarcode( SDBOutVal *dbOut, ENTRY *pEntry, struct barcode *pCode) 
{
	int length, bytes_written;
	ENTRY e;

	if (dbOut->fdDb == NULL)
		return ERROR;

	if(pEntry == NULL)
	{
		length = pCode->length;

		e.key = hash(pCode->text, length);
		e.recptr =  f_tell(dbOut->fdDb);
		e.length = length;
		e.quantity = pCode->quantity;
		e.code_id = pCode->id;
		DateTimeToTimeStamp(&pCode->date, &pCode->time, e.timestamp); // Update timestamp
	
		// Append to the end of the database
		if(f_lseek(dbOut->fdDb, e.recptr) != FR_OK)
			return ERR_DB_WRITE;

		if (f_write(dbOut->fdDb, pCode->text, length, &bytes_written ) != FR_OK || bytes_written != length)
			return ERR_DB_WRITE;
		
		if(AddKey(&e, &(dbOut->ix)) == IX_FAIL)
			return ERR_DB_WRITE;
	} 
	else 
	{
		if(pCode == NULL)
		{
			--pEntry->quantity;
		}
		else
		{
			pEntry->quantity += pCode->quantity;

			if(pCode->quantity > 0)
				DateTimeToTimeStamp(&pCode->date, &pCode->time, pEntry->timestamp); // Update timestamp
		}

		// Overwrite the current key
		if(UpdateKey(pEntry, &(dbOut->ix)) == IX_FAIL)
			return ERR_DB_WRITE;
	}
	return DATABASE_OK;
}


long GetTotalBarcodes( SDBOutVal *dbFile )
{
    int bytes_read;
    int offset;
	ENTRY e;

	if (IsBarcodeDatabaseOpen(dbFile) != DATABASE_OK)
		return ERROR;

	if(dbFile->lTotalRecords == -1L)
	{
		dbFile->lTotalRecords = 0;
		
		if (FirstKey(&e, &(dbFile->ix)) != IX_OK)
			return ERR_INDEX_KEY_NF;

		do
		{
			dbFile->lTotalRecords += e.quantity;
		} 
		while(NextKey(&e, &(dbFile->ix)) == IX_OK);
	}

	return dbFile->lTotalRecords;
}


// adapted from String.hashCode()
unsigned long hash(const char *str, int str_len)		// 32-bit hash key
{
    unsigned long hash = 5381;
    int i,c;

	i = str_len;

    while (i != 0)
	{
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
		--i;
	}

    return hash;
}