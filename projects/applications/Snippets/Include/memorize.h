

#define DBASE_NAME	"SCANNED.DAT"
#define DBASE_IDX	"SCANNED.IDX"

#define ALLOW_NEGATIVES			0x01
#define KEEP_ZERO_QUANTITY		0x02
#define SUMMED_QUANTITIES		0x04

//------------------------------------------------------------------------------
//	Initialize storage with options
//	=====================
//-----------------------------------------------------------------------------
int InitStorage(uint8_t quantity_options);

//------------------------------------------------------------------------------
//	OpenStorage
//	=====================
//	Opens the database and creates a new one if it doesn't exist
//-----------------------------------------------------------------------------
int OpenStorage(void);

//------------------------------------------------------------------------------
//	CloseStorage
//	=====================
//	Closes the main database
//-----------------------------------------------------------------------------
int CloseStorage(void);

//------------------------------------------------------------------------------
//	DeleteBarcodeMemory
//	=====================
//	Deletes all barcodes from memory
//-----------------------------------------------------------------------------
void DeleteBarcodeMemory(void);

//------------------------------------------------------------------------------
//	BarcodesInMemory
//	=====================
//	Returns the number of (untransmitted) barcodes in memory
//-----------------------------------------------------------------------------
int BarcodesInMemory(void);

int BarcodesInMemoryISR(void);	// For heartbeats

//------------------------------------------------------------------------------
//	StoreBarcodeInMemory
//	=====================
//	Updates a barcode in the database file (pCode->quantity determines the action)
//-----------------------------------------------------------------------------
int UpdateBarcodeInMemory(struct barcode *pCode);

//------------------------------------------------------------------------------
//	DeleteBarcodeFromMemory
//	========================
//	Deletes the barcode that was last retrieved by 'GetCurrentBarcodeFromMemory'
//-----------------------------------------------------------------------------
int DeleteCurrentBarcodeFromMemory(void);

int FindFirstBarcodeInMemory(struct barcode *pCode);
int FindLastBarcodeInMemory(struct barcode *pCode);

int IsLastBarcodeInMemory(struct barcode *pCode);
int ReadCurrentBarcodeFromMemory(struct barcode *pCode);
int ReadNextBarcodeFromMemory(struct barcode *pCode);
int ReadFirstBarcodeFromMemory(struct barcode *pCode);
int ReadLastBarcodeFromMemory(struct barcode *pCode);

//------------------------------------------------------------------------------
//	AdvanceMemoryIndex
//	========================
//	Moves the record index up by one
//-----------------------------------------------------------------------------
int AdvanceMemoryIndex(uint8_t qty_options);

//------------------------------------------------------------------------------
//	ResetMemoryIndex
//	========================
//	Moves the record index back to the beginning
//-----------------------------------------------------------------------------
void ResetMemoryIndex(void);


int AllowDuplicates(void);
int DontAllowDuplicates(void);