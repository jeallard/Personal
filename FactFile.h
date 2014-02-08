#ifndef FACTFILE_H
#define FACTFILE_H

#include    "progfile.h"

class FactFile : public ProgFile {
    //
    // Class for reading and writing factory settings files.
    //
public:
		FactFile(bool addr_req=false) : address_required(addr_req) {}
		// If 'addr_req' is true, loading the file will return an error
		// if an address is not specified for each factory setting.

    virtual int LoadFile(const char *fname);
		// Loads the specified programming file. 
		// Returns: 0=OK, 1=Mem alloc failed, 2=Address not monotonic, 
		//          3=Can't open file,4=File format error,5=Premature EOF
		//			6=Block address out of range,7=Checksum error

private:
	bool address_required;	

};

#endif