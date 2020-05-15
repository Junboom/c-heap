#include "cheap.h"

void CHeap<int>::DestroyHeap();

void CHeap<int>::Insert(const int& item);

void CHeap<int>::PeekTop(int& item) const;

void CHeap<int>::Remove(int& item);

void CHeap<int>::RebuildHeap(int rootIndex);
