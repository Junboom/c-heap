#include <iostream>
#include "cheap.h"

using namespace std;

int     main()
{
    CHeap<int>      myHeap;
    int             heapInts[] = { 5, 20, 4, 12, 7, 5, 20, 4, 12, 7 };
    unsigned int    index;
    int             intVal;

    // insert some values into the heap
    for (index = 0; index < (sizeof(heapInts) / sizeof(*heapInts)); ++index)
    {
        try {
            myHeap.Insert(heapInts[index]);
        }
        catch (CHeapEx&)
        {
            cerr << "Error inserting " << heapInts[index] << endl;
            exit(EXIT_FAILURE);
        }
    }

    // try removing some items (we loop a few extra times here to try out the
    // exception handling)
    cout << "Remove some items: " << endl;
    for (index = 0; index < (sizeof(heapInts) / sizeof(*heapInts)) + 3; ++index)
    {
        try {
            myHeap.Remove(intVal);
            cout << "intVal = " << intVal << endl;
        }
        catch (CHeapEx&)
        {
            cerr << "Error removing heap value..." << endl;
        }
    }

    return (EXIT_SUCCESS);
}
