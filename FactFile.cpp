// ------------------------------------------------------------
// Factfile.cpp gjk ui ghj
// ------------------------------------------------------------
#include "factfile.h"
#include "fileio.h"

int FactFile::LoadFile(const char *fname)
{
	FileIO		file;
	ProgBlock	*block;
	char		*str;
	long		addr = 0;
	int			fact_setting = -1;
	int			data_size	 = 0;
	bool		have_address = false;
	long		val;

    if(!InitForLoad())
        return 1;

	// List is locked so that each factory setting will have its own block.
	SetLock(true);

	if(file.open(fname,"rt") == NULL)
		return 3;	

	file.SetCommentStr(";");

	// Parse each line.
    while((str = file.GetNextToken(" ,\t\n")) != NULL)
    {
		if(str[0] == '$')
		{
			// --------------------------------------
			// Header
			// --------------------------------------
			for(int idx=0;(str = file.token().next(" ,\t\n")) != NULL;idx++)
			{
				switch(idx)
				{
					case 0:		// fact number
						fact_setting = strtol(str,NULL,0);
						data_size = 2;		// Default data size
						addr = 0;			// Default address
						have_address = false;
						if(block = NewBlock())
							block->SetBlockID(fact_setting);
						break;
					case 1:		// data size
						data_size = strtol(str,NULL,0);
						if(data_size < 1 || data_size > 4 || data_size==3)
							return 4;
						break;
					case 2:		// address
						addr = strtol(str,NULL,0);
						if(block)
							block->SetStartAddress(addr);
						have_address = true;
						break;
				}
			}
		}
		else
		{
			// ----------------------------
			// Data
			// ----------------------------

			// Check if we have an address for this factory setting.
			if(!have_address && address_required)
			{
				return 4;
			}

			// Check for a valid factory setting.
			if(fact_setting < 0)
			{
				return 4;
			}

			// Check for string or numeric data.
			if(str[0] == '"')
			{
				// Write the string
				while(*++str && *str != '"')
					if(PutByte(addr++,*str))
						return 1;
			}
			else
			{
				// Write numeric value.
				val = strtol(str,NULL,0);
				for(int k=0;k < data_size;k++)
				{
					if(PutByte(addr++,(char)val&0xff))
						return 1;
					val >>= 8;
				}
			}
		}
	}

	return 0;
}

