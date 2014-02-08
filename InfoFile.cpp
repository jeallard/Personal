// -------------------------------------------------------
// InfoFile.cpp
// -------------------------------------------------------
#include "infofile.h"
#include "fileio.h"

int InfoFile::LoadFile(const char *fname)
{
	FileIO		file;
	const char	*str;
	ProgBlock	*block;
	bool		parse_enable = true;

	if(!InitForLoad())
		return 1;	

	// List is locked so each setting has its own block.
	SetLock(true);

	// Copy all global defines to the list.
	if(CopyAllGlobal())
		return 3;	

	if(file.open(fname,"rt") == NULL)
		return 3;

	file.SetCommentStr("//");

	// Parse each line.
	while((str = file.GetNextToken(" ,\t\n")) != NULL)
	{
		if(!strcmp(str,"#define"))
		{
			if(parse_enable && (str = file.token().next(" ,\t\n")))
			{
				if(block = NewBlock())
				{
					DefEntry *sym = block->SetSymbol(str);

					if(str = file.token().next(" \",\t\n"))
					{
						if(file.token().GetStopChar() == '\"')
							sym->SetStrValue(str);
						else
							sym->SetIntValue(strtol(str,NULL,0));
					}
				}
			}
		}
		else if(!strcmp(str,"#ifdef"))
		{
			if(str = file.token().next(" ,\t\n"))
				parse_enable = FindBySymbolName(str) ? true : false;	
		}
		else if(!strcmp(str,"#ifndef"))
		{
			if(str = file.token().next(" ,\t\n"))
				parse_enable = FindBySymbolName(str) ? false : true;
		}
		else if(!strcmp(str,"#else"))
		{
			if(!parse_enable)
				parse_enable = true;
		}
		else if(!strcmp(str,"#elif"))
		{
			if(!parse_enable)
			{
				str = file.token().next(" ,\t\n");
				if(str && !strcmp(str,"defined"))
					str = file.token().next(" ,\t\n");

				if(str)
					parse_enable = FindBySymbolName(str) ? true : false;
			}
		}
    	else if(!strcmp(str,"#endif"))
			parse_enable = true;
	}

	return 0;
}

int InfoFile::CopyAllGlobal()
{
	DefEntry	*def;

	if(!global_defs)
		return 0;
	
	global_defs->Rewind();

	while(def = global_defs->GetNext())
	{
		ProgBlock *block = NewBlock();

		DefEntry *sym = block->SetSymbol(*def);

	}

	return 0;
}
