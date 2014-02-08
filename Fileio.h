#ifndef FILEIO_H
#define FILEIO_H

#include	<stdio.h>
#include	"dattypes.h"
#include	"spectok.h"
#include	"dstring.h"

#undef putc
#undef getc

class FileIO {
public:
            FileIO();
            FileIO(const char *filen) : filename(filen), fp(0), line_number(0) { comment_str[0]=0; }
			FileIO(const char *filen,const char *flags);	
			~FileIO();

	// Open/Close functions
    void	close();
    FILE    *operator()()   { return fp; }
	FILE 	*open(const char *filen,const char *flags);
	FILE 	*open(const char *flags);

	// Information
	int			isopen()		const	{ return fp ? 1:0; }
	const char *GetName()		const 	{ return filename(); }	
	const char *GetFileExt()	const;

	// Parsing Functions
    void		SetCommentStr(const char *str)  { strncpy(comment_str,str,MAX_COMMENT_LEN); }
	SpecTok&	token()					{ return tok; }
	char		*GetNextToken(const char *list,int no_eat=0);
	long		GetLineNum()			{ return line_number; }

	// Location functions
	void	rewind()		{ fseek(fp,0,SEEK_SET); tok.set(0); line_number=0; }
	void	waste(int num)	{ fseek(fp,num,SEEK_CUR); tok.set(0); }
    long    GetCurrPos()    { return ftell(fp); }
    void    SetCurrPos(long pos)    { fseek(fp,pos,SEEK_SET); tok.set(0); }
	void	SeekRel(long pos) { fseek(fp,pos,SEEK_CUR); tok.set(0); }

	// Functions for writing
    void    putc(char c)            { fputc(c,fp); }
    void    puts(const char *str)   { fputs(str,fp); }
    void    PutHex8(int val);
	void	PutUShort(ushort val)	{ fwrite(&val,sizeof(ushort),1,fp); }
	void	PutULong(ulong val)		{ fwrite(&val,sizeof(ulong),1,fp); }
	size_t	WriteUChar(uchar *data,ulong num)	{ return fwrite(data,sizeof(uchar),num,fp); }

	// Functions for reading
	void	getc(char *buf,int num);
    char    *GetLine(char *str,int max_len)   { return fgets(str,max_len,fp); }
	size_t	GetByte(uchar *data)	{ return fread(data,sizeof(ubyte),1,fp); }
	ushort	getword()		{ ushort d; fread(&d,sizeof(ushort),1,fp); return d; }
    short   getsword()      { short d; fread(&d,sizeof(short),1,fp); return d; }
	ulong	getulong()		{ ulong d; fread(&d,sizeof(ulong),1,fp); return d; }
    void    GetNSWords(short *ptr,long N) { fread(ptr,sizeof(short),N,fp); }
	size_t	ReadData(void *data,ulong num) { return fread(data,sizeof(uchar),num,fp); }


private:
	enum	{MAX_LINE_LEN=200};
	enum	{MAX_COMMENT_LEN=3};

	FILE	*fp;
    char    comment_str[MAX_COMMENT_LEN+1];
	long	line_number;
	DString	filename;
	SpecTok	tok;
	char	line[MAX_LINE_LEN];
    static  const   char    empty_str[];

    void    StripComments(char *str);

};


#endif
