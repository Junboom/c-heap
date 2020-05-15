#ifndef CHEAP_HEADER
#define CHEAP_HEADER

#include    "csimplelist.h"

// enumerated list for heap exceptions
enum    HeapExType {
    H_FULL
    , H_EMPTY
    , H_ERROR
    , H_SUCCESS
};


// constants
const   int     DEFAULT_HEAP_ITEMS = DEFAULT_NUM_ITEMS;


// exception class for CHeap class
class  CHeapEx
{
public:
    CHeapEx(HeapExType  exType) : m_exType(exType) {}
    HeapExType  GetExType() const { return  m_exType; }

private:
    HeapExType      m_exType;
};


// class declaration
template    <typename  HeapType>
class   CHeap : private CSimpleList<HeapType>
{
public:
    // constructors and destructor
    CHeap(int  numItems = DEFAULT_HEAP_ITEMS) : CSimpleList<HeapType>(numItems) {}
    virtual ~CHeap() { DestroyHeap(); }

    // member functions
    void    DestroyHeap();
    void    Insert(const HeapType& item);
    void    PeekTop(HeapType& item) const;
    void    Remove(HeapType& item);

private:
    // member functions
    void    RebuildHeap(int  rootIndex);
};

#include    "cheap.cpp"

#endif  // CHEAP_HEADER
