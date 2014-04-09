#ifndef INTELHEX_H
#define INTELHEX_H

#include    "progfile.h"

class IntelHex : public ProgFile {
    //
    // Class for reading and writing IntelHex files.
    //
public:

    virtual int LoadFile(const char *fname);
		// Loads the specified programming file. The proper memory is allocated and
		// the data is partitioned into blocks of 'blk_size'.
		// Returns: 0=OK, 1=Mem alloc failed, 2=Address not monotonic, 
		//          3=Can't open file,4=File format error,5=Premature EOF
		//			6=Block address out of range,7=Checksum error

private:

};


#endif

