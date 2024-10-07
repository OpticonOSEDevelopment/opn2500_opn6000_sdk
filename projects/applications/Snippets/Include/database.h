//
// Database.h
//
// Database functions that finally call the fix or the csv functions
//
// Martin Jansen
//

#ifndef __DATABASE_H__
#define __DATABASE_H__

// include is needed to get the IX_DESC value
#include "lib.h"
#include "index.h"

//
// Error code defines, these should match the fix database error code
//
#define DATABASE_OK			(0)			// OK message
#define ERR_OPEN_DATABASE	(-1)		// Cannot open the database file
#define ERR_OPEN_INDEX		(-2)		// cannot open/create the index file
#define	ERR_NOT_OPEN		(-3)		// Error Database is not open
#define	ERR_EMPTY			(-4)		// Error Database is empty
#define ERR_INDEX_DUPLICATE	(-5)		// Duplicate key found in index while not allowed
#define ERR_INDEX_KEY_NF	(-6)		// Key has not been found.

#define ERR_DB_READ			(-3)
#define ERR_DB_WRITE		(-4)
#define ERR_INDEX_READ		(-10)		// Cannot read from index file
#define ERR_INDEX_WRITE		(-11)		// Cannot write to index file

#define ERR_DB_WRONG_FORMAT (-12)		// Fix size database has the wrong size

#define MAX_FIELDS		10

//#define MAX_G_BUFFER    256
#define MAX_G_FIELD     80

#ifndef HAS_2D_ENGINE
#define MAX_RECORD_SIZE			300
#else
#define MAX_RECORD_SIZE			2500
#endif

extern char g_Record[MAX_RECORD_SIZE];


//
// Special Database flags
//
enum
{
	F_DB_CSV	= 1,	// if this flag is set then it is a CSV style database
	F_DB_LOOKUP	= 2,	// if this flag is set then index file that cannot contain duplicates
	F_DB_DATE	= 4,	// the datafile database contains a date field
	F_DB_TIME	= 8,	// the datafile database contains a time field
	F_DB_APPEND = 16	// Append database multiple keys are allowed in the index files
};

typedef struct
{
	short offsetField;					// offset or the field number
	short maxField;						// max field size (csv) or field size fixed size db
}SFields;

typedef struct
{
	char *dbFilename;					// Database filename
	char *idxFilename;					// index filename
	unsigned char flags;				// Special options flags
	int	 maxRecordSize;					// The maximum record size including the <CR><LF> and CSV separator
	int  keyfield;						// The field number that holds the search key
	int  csvChar;						// the csv separator character
	SFields field[ MAX_FIELDS ];	    // The field description that makeup a record
}SDatabaseItem;

typedef struct
{
	uint8_t	status;
	uint16_t length;
	int16_t quantity;
	uint8_t code_id;
	uint8_t timestamp[4];
} __attribute__((__packed__ )) db_record_info;

//
// This is really the handle that is returned by open/create database
//
typedef struct
{
	FIL *fdDb;					// database file descriptor
	IX_DESC ix;					// holds the indexing values
	long	lTotalRecords;		// total amount of records
}SDBOutVal;

int IsBarcodeDatabaseOpen(SDBOutVal *dbOutVal);

int OpenBarcodeDatabase(const char* filename, const char *idx_file, SDBOutVal *dbOut, uint8_t allow_duplicates);
int CreateBarcodeDatabase(const char* filename, const char *idx_file, SDBOutVal *dbOut, uint8_t allow_duplicates);

void CloseBacodeDatabase(SDBOutVal *dbOut); 

int ReadBarcodeRecord(SDBOutVal *dbFile, ENTRY *e, struct barcode *pCode); 

int SearchBarcodeDatabase(SDBOutVal *dbFile, struct barcode *pCode, int origin, long offset, ENTRY *pFoundEntry ); 
int ReadFirstBarcode(SDBOutVal *dbFile, struct barcode *pCode, ENTRY *pFoundEntry); 
int ReadLastBarcode(SDBOutVal *dbFile, struct barcode *pCode, ENTRY *pFoundEntry);
int ReadPreviousBarcode(SDBOutVal *dbFile, struct barcode *pCode, ENTRY *pFoundEntry); 
int ReadNextBarcode(SDBOutVal *dbFile, struct barcode *pCode, ENTRY *pFoundEntry); 


int ReadCurrentBarcode(SDBOutVal *dbFile, struct barcode *pCode, ENTRY *pFoundEntry);
int DeleteCurrentBarcode(SDBOutVal *dbFile); 

int WriteBarcode( SDBOutVal *dbOut, ENTRY *pEntry, struct barcode *pCode); 
long GetTotalBarcodes( SDBOutVal *dbFile );

unsigned long hash(const char *str, int str_len);	// 32-bit hash key

#endif // __DATABASE_H__


