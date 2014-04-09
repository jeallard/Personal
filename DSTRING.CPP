#include "dstring.h"
gfdgfd

DString& DString::operator+=(const DString& right)
{
    if(right.string)
    {
        int     len         = GetLen() + right.GetLen();
        char    *new_string = new char[len+1];

        if(string)
        {
            strcpy(new_string,string);
            delete string;
        }
        strcat(new_string,right.string);
        string = new_string;
    }
    return *this;
}

DString& DString::operator=(const DString& right)
{
    delete string;
    string = right.string ? strdup(right.string) : 0;
    return *this;
}

DString& DString::operator=(const char *str)
{
    delete string;
    string = str ? strdup(str) : 0;
    return *this;
}

DString& DString::operator+=(const char *str)
{
    if(str)
    {
        int len             = GetLen() + strlen(str);
        char    *new_string = new char[len+1];

        if(string)
        {
            strcpy(new_string,string);
            delete string;
        }
        strcat(new_string,str);
        string = new_string;
    }
    return *this;
}

int strwcmp(const char *s1,const char *s2)
{
    // This string compare function operates just like the 'strcmp' function
    // but it allows wild cards (i.e. '?' and '*').

    while(*s1!='*' && *s2!='*')
    {
        if(*s1!=*s2 && *s1!='?' && *s2!='?')
        {
            if(*s1 > *s2)
                return 1;
            else
                return -1;
        }
        if(!*s1 || !*s2)
            break;
        s1++;
        s2++;
    }
    return 0;
}

