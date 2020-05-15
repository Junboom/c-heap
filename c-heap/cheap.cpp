void CHeap<int>::DestroyHeap()
{
  DestroyList();
}

void CHeap<int>::Insert(const int& item);
{
  Insert(item);
}

void CHeap<int>::PeekTop(int& item) const;
{
  GetItem(item);
}

void CHeap<int>::Remove(int& item);
{
  Remove(item);
}

void CHeap<int>::RebuildHeap(int rootIndex);
{
  SetListSize(rootIndex);
}
