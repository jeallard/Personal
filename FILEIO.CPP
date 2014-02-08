#include	"fileio.h"
#include    <iostream>
using namespace std;

// -------------------------------------------------------
// FileIO class functions
// -------------------------------------------------------
const char FileIO::empty_str[1] = {'\0'};

FileIO::FileIO() : fp(0), line_number(0)
{
	comment_str[0] = 0;
}

FileIO::FileIO(const char *filen,const char *flags) : filename(filen), fp(0), line_number(0)
{
	comment_str[0] = 0;
	open(filen,flags);
}

FileIO::~FileIO()
{
	close();
}

FILE *FileIO::open(const char *filen,const char *flags)
{
	filename = filen;
	return open(flags);
}

void FileIO::close()
{
    if(fp)
    {
        fclose(fp);
        fp=0;
    }
}

FILE *FileIO::open(const char *flags)
{
	if(fp)
		fclose(fp);

	if(!filename())
	{
		cout << "ERROR: File has no name 'FileIO::open'\n";
		return 0;
	}
	
	fp = fopen(filename(),flags);
	if(!fp)
		cout << "ERROR: Can't open file: " << filename() << '\n';

    tok.set(0);
	return fp;
}

void FileIO::getc(char *buf,int num)
{
	for(int k=0,val=0;k < num && val!=EOF;k++)
	{
		val = fgetc(fp);
		buf[k]=val;
	}
}

void FileIO::PutHex8(int val)
{
    fprintf(fp,"%02x",val);
}
	
char *FileIO::GetNextToken(const char *list,int no_eat)
{
	char *str = tok.next(list,no_eat);

	if(!str)
	{
        while(GetLine(line,MAX_LINE_LEN))
        {
			++line_number;
            StripComments(line);
            tok.set(line);
            if((str = tok.next(list,no_eat)) != NULL)
                break;
        }
	}
	return str;
}

const char *FileIO::GetFileExt()	const
{
	const char *str = strrchr(filename(),'.');

	return str ? str+1 : empty_str;
}

void FileIO::StripComments(char *str)
{
    // Places a zero at the first comment char found.

    if(!comment_str[0])
        return;

    char *sp = strstr(str,comment_str);
    if(sp)
        *sp = 0;
}