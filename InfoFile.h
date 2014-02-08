#ifndef INFOFILE_H
#define INFOFILE_H

#include "progfile.h"
#include "deflist.h"

class InfoFile : public ProgFile {
	//
	// Class for reading info from .h files.
	//
public:
	InfoFile(DefList *gl_def) : global_defs(gl_def) {}

	virtual int LoadFile(const char *fname);
		// Loads the specified info (.h) file.
		//
		// RETURNS: 

private:
	DefList	*global_defs;


	int	CopyAllGlobal();
		// Copies all global symbols to prog file blocks.
};

#endif
