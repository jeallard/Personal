#include    "dllist.h"
ghjkghjkg
this will error
// --------------------------
// GDList class functions
// --------------------------
void    *GDList::insert(void *obj,GDBase::position where)
{
    NIDNode *p = new NIDNode(obj);

    if(p)
    {
        link(p,where);
        return obj;
    }
    return 0;
}

void GDList::clean(void)
{
    NIDNode *node = GetHead(), *next_node;

    while(node)
    {
        decc();
        next_node = node->GetNext();
        if(cleanup() == ListBase::active)
            zap_object(node->object);
        delete node;
        node = next_node;
    }
    ResetPointers();
}

NIDNode *GDList::NFind(void *obj)
{
    //
    // Finds the entry containing the object "obj".  If the entry is found,
    // a pointer to the node is returned.  If the entry is NOT found, NULL
    // is returned.  In either case, the current pointer is NOT modified.
    //
    NIDNode *node = GetHead();

    while(node)
    {
        if(node->object == obj)
            break;
        node = node->GetNext();
    }
    return node;
}

void    *GDList::rem_del(position rel,int mode)
{
    NIDNode *node = 0;
    switch(rel)
    {
        case GDBase::liststart: node=GetHead();  break;
        case GDBase::listend:   node=GetTail();  break;
        case GDBase::current:   node=GetCurr();  break;
        case GDBase::before:    if((node=GetCurr()) != 0)
                                    node = node->GetPrev();
                                break;
        case GDBase::after:     if((node=GetCurr()) != 0)
                                    node = node->GetNext();
                                break;
    }
    if(node)
    {
        void *obj = node->object;
        remove(node);
        if(mode && cleanup() == ListBase::active)
            zap_object(obj);
        return obj;
    }
    return 0;
}

void *GDList::rem_del(void *obj,int mode)
{
    NIDNode *node = NFind(obj);

    if(node)
    {
        remove(node);
        if(mode && cleanup() == ListBase::active)
            zap_object(obj);
        return obj;
    }
    return 0;
}

void GDList::sort(int (*sort_func)(void *p1,void *p2))
{
    int     num = count();

    while(num)
    {
        NIDNode *p1 = GetHead();
        NIDNode *p2 = p1->GetNext();
        for(int k=1;k < num;k++)
        {
            // If this returns true, p1 is sorted toward the end

            if(sort_func(p1->GetObject(),p2->GetObject()))
            {
                GDBase::swap(p1,p2);
                p2 = p1->GetNext();
            }
            else
            {
                p1 = p2;
                p2 = p2->GetNext();
            }
        }
        num--;
    }
}

// --------------------------
// GIDList class functions
// --------------------------
IDNode *GIDList::NFind(IDNode *obj)
{
    //
    // Finds the entry containing the object "obj".  If the entry is found,
    // a pointer to the node is returned.  If the entry is NOT found, NULL
    // is returned.  In either case, the current pointer is NOT modified.
    //
    IDNode *node = GetHead();

    while(node)
    {
        if(node == obj)
            break;
        node = node->GetNext();
    }
    return node;
}

void *GIDList::insert(IDNode *obj,GDBase::position where)
{
    if(obj)
    {
        link(obj,where);
        return obj;
    }
    return 0;
}

void GIDList::clean(void)
{
    IDNode *node = GetHead(), *next_node;

    while(node)
    {
        decc();
        next_node = node->GetNext();
        if(cleanup() == ListBase::active)
            delete node;
        node = next_node;
    }
    ResetPointers();
}

int  GIDList::del(position rel)
{
    IDNode *node = 0;
    switch(rel)
    {
        case GDBase::liststart: node=GetHead();  break;
        case GDBase::listend:   node=GetTail();  break;
        case GDBase::current:   node=GetCurr();  break;
    }
    if(node)
    {
        unlink(node);
        if(cleanup() == ListBase::active)
            delete node;
        return 1;
    }
    return 0;
}

int GIDList::del(IDNode *obj)
{
    IDNode *node = NFind(obj);

    if(node)
    {
        unlink(node);
        if(cleanup() == ListBase::active)
            delete node;
        return 1;
    }
    return 0;
}

void *GIDList::remove(position rel)
{
    IDNode *node = 0;
    switch(rel)
    {
        case GDBase::liststart: node=GetHead();  break;
        case GDBase::listend:   node=GetTail();  break;
        case GDBase::current:   node=GetCurr();  break;
    }
    if(node)
        unlink(node);
    return cast(node);
}

void *GIDList::remove(IDNode *obj)
{
    IDNode *node = NFind(obj);

    if(node)
        unlink(node);
    return cast(node);
}


