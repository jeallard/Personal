#ifndef DSTRING_H
#define DSTRING_H

#include    <string.h>

class DString {
    char    *string;
public:
            DString() : string(0) {}
            DString(const char *str) : string(0) { if(str) string=strdup(str); }
            DString(const DString& item) : string(0)
                    { if(item.string) string=strdup(item.string); }
            ~DString() { delete string; }
    const   char    *GetString(void) const { return string; }
    char    *GetNCStr()                    { return string; }
    int     GetLen()                 const { return string ? strlen(string) : 0; }

    DString&    operator=(const DString& right);
    DString&    operator=(const char *str);
    DString&    operator+=(const DString& right);
    DString&    operator+=(const char *str);
    DString     operator+(const DString& right) const
                    { DString ret_val(*this); return ret_val+=right; }
    int         operator<(const DString& right) const
                            { return strcmp(string,right.string)<0; }
    int         operator>(const DString& right) const
                            { return strcmp(string,right.string)>0; }
    int         operator<=(const DString& right) const
                            { return strcmp(string,right.string)<=0; }
    int         operator>=(const DString& right) const
                            { return strcmp(string,right.string)>=0; }
    int         operator==(const DString& right) const
                            { return !strcmp(string,right.string); }
    int         operator!=(const DString& right) const
                            { return strcmp(string,right.string);  }
    const char  *operator()()    const { return string; }
};

int strwcmp(const char *s1,const char *s2);


#endif
