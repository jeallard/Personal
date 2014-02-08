#ifndef DLLIST_H
#define DLLIST_H

#include    <stdlib.h>
#include    "listbase.h"

class NIDNode : public DNode {
    //
    // Non-Intrusive Double-Linked Node.
    //
    friend  class GDList;
public:
            NIDNode(void *obj) : object(obj) {}
    void    *GetObject()    const   { return object; }
    NIDNode *GetPrev()  const   { return (NIDNode *)DNode::GetPrev(); }
    NIDNode *GetNext()  const   { return (NIDNode *)DNode::GetNext(); }

private:
    void    *object;
};

class GDList : public GDBase {
    //
    // GDList (General Double-Linked List) is a non-intrusive implementation
    // of a double-linked list.  This is an abstract class which is inherited
    // by the DList<T> class below.  This class does all the work and DList<T>
    // provides a properly typed interface.
    //
public:
    void    clean();
    void    sort(int (*sort_func)(void *p1,void *p2));

protected:
            GDList(clean_t mode=active) : GDBase(mode) {}
            ~GDList() { clean(); }

    NIDNode *NFind(void *obj);
    void    remove(NIDNode *node)        { unlink(node); delete node; }

    void    *insert(void *obj,position=before); 
    void    *remove(void *obj)           { return rem_del(obj,0); }
    void    *remove(position rel=before) { return rem_del(rel,0); }
    void    *del(void *obj)              { return rem_del(obj,1); }
    void    *del(position rel=before)    { return rem_del(rel,1); }

    NIDNode *GetHead()  const   { return (NIDNode *)GDBase::GetHead(); }
    NIDNode *GetTail()  const   { return (NIDNode *)GDBase::GetTail(); }
    NIDNode *GetCurr()  const   { return (NIDNode *)GDBase::GetCurr(); }

    void    *first()    const   { return GetHead() ? GetHead()->object : 0; }
    void    *last()     const   { return GetTail() ? GetTail()->object : 0; }
    void    *curr()     const   { return GetCurr() ? GetCurr()->object : 0; }
    void    *find(void *obj)
                 { NIDNode *p = NFind(obj); return p ? p->object : 0; }
    void    *moveto(void *obj)
                 { NIDNode *p = NFind(obj); SetCurr(p); return p ? p->object:0; }
    void    *move(int amount)
                 { NIDNode *p = (NIDNode *)GDBase::move(amount);
                   return p ? p->object : 0; }

private:
    void    *rem_del(void *obj,int mode);
    void    *rem_del(position,int mode);
    virtual void zap_object(void *obj) = 0;
};

template<class T> class DList : public GDList {
    void    zap_object(void *object) { delete (T *)object; }
public:
            DList(clean_t mode = active) : GDList(mode) {}
    T       *insert(T *a,GDBase::position where = before)
                            { return GDList::insert(a,where); }
    T       *append(T *a)   { return GDList::insert(a,GDBase::listend); }
    T       *prepend(T *a)  { return GDList::insert(a,GDBase::liststart); }

    T       *remove(GDBase::position rel=current){ return GDList::remove(rel);  }
    T       *remove(T *a)   { return GDList::remove(a); }
    T       *del(GDBase::position rel=current)   { return GDList::del(rel);  }
    T       *del(T *a)      { return GDList::del(a);    }
    T       *getfirst()     { return GDList::remove(GDBase::liststart); }
    T       *getlast()      { return GDList::remove(GDBase::listend);   }

    T       *first() const  { return GDList::first(); }
    T       *last()  const  { return GDList::last();  }
    T       *curr()  const  { return GDList::curr();  }

    T       *find(T *a)     { return GDList::find(a); }
    T       *moveto(T *a)   { return GDList::moveto(a); }
    T       *prev()         { return GDList::move(-1);}
    T       *next()         { return GDList::move(1); }
    T       *move(int a)    { return GDList::move(a); }
    T       *get()
                { T *t = (T *)GDList::curr(); GDList::move(1); return t; }

    T       *operator()() const { return GDList::curr(); }
    T       *operator++()       { return GDList::move(1); }
    T       *operator++(int)    { return get(); }
    T       *operator--()       { return GDList::move(-1); }
    T       *operator--(int)
                { T *t = (T *) GDList::curr(); GDList::move(-1); return t; }
};

//
// ------------------------ Intrusive Linked List --------------------
//

class IDNode : public DNode {
    //
    // Intrusive Double-Linked Node.
    //
    friend  class GIDList;
public:
    virtual ~IDNode() {}
    IDNode *GetPrev()  const   { return (IDNode *)DNode::GetPrev(); }
    IDNode *GetNext()  const   { return (IDNode *)DNode::GetNext(); }

protected:
    virtual void    *cast() const   { return (void *)this; }
};

class GIDList : public GDBase {
    //
    // GIDList (General Intrusive Double-Linked List) is a intrusive
    // implementation of a double-linked list.  This is an abstract class
    // which is inherited by the IDList<T> class below.  This class does
    // all the work while IDList<T> provides a properly typed interface.
    //
public:
    void    clean();

protected:
            GIDList(clean_t mode=active) : GDBase(mode) {}
            ~GIDList() { clean(); }

    void    *insert(IDNode *obj,position=before); 

    IDNode  *NFind(IDNode *obj);    // Doesn't affect curr pointer
    void    *find(IDNode *obj)
                { IDNode *p=NFind(obj); return p ? (SetCurr(p),cast(p)) : 0; }

    void    *remove(IDNode *obj);
    void    *remove(position rel=current);
    int     del(IDNode *obj);
    int     del(position rel=current);

    void    *first()    const           { return cast(GetHead()); }
    void    *last()     const           { return cast(GetTail()); }
    void    *curr()     const           { return cast(GetCurr()); }
    void    *move(int a)                { return cast((IDNode *)GDBase::move(a)); }

    IDNode  *GetHead()  const   { return (IDNode *)GDBase::GetHead(); }
    IDNode  *GetTail()  const   { return (IDNode *)GDBase::GetTail(); }
    IDNode  *GetCurr()  const   { return (IDNode *)GDBase::GetCurr(); }

    void    *cast(IDNode *p)     const   { return p ? p->cast() : 0; }

};

template<class T> class IDList : public GIDList {
public:
            IDList(clean_t mode = active) : GIDList(mode) {}
    T       *insert(T *a,GDBase::position where = before)
                            { return (T *)GIDList::insert(a,where); }
    T       *append(T *a)   { return (T *)GIDList::insert(a,GDBase::listend); }
    T       *prepend(T *a)  { return (T *)GIDList::insert(a,GDBase::liststart);}

    T       *remove()       { return (T *)GIDList::remove(); }
    T       *remove(T *a)   { return (T *)GIDList::remove(a);}
    int     del()           { return GIDList::del();    }
    int     del(T *a)       { return GIDList::del(a);   }
    T       *getfirst()     { return (T *)GIDList::remove(GDBase::liststart); }
    T       *getlast()      { return (T *)GIDList::remove(GDBase::listend);   }

    T       *first() const  { return (T *)GIDList::first(); }
    T       *last()  const  { return (T *)GIDList::last();  }
    T       *curr()  const  { return (T *)GIDList::curr();  }

    T       *find(T *a)     { return (T *)GIDList::find(a); }
    T       *prev()         { return (T *)GIDList::move(-1);}
    T       *next()         { return (T *)GIDList::move(1); }
    T       *move(int a)    { return (T *)GIDList::move(a); }
    T       *get()
                { T *t = (T *)GIDList::curr(); GIDList::move(1); return t; }

    T       *operator()() const { return GIDList::curr(); }
    T       *operator++()       { return GIDList::move(1); }
    T       *operator++(int)    { return get(); }
    T       *operator--()       { return GIDList::move(-1); }
    T       *operator--(int)
                { T *t = GIDList::curr(); GIDList::move(-1); return t; }

};


#endif

