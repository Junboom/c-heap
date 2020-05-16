template <typename HeapType>
void CHeap<HeapType>::DestroyHeap()
{
    CSimpleList<HeapType>::DestroyList();
}

template <typename HeapType>
void CHeap<HeapType>::Insert(const HeapType& item)
{
    if (CSimpleList<HeapType>::IsFull())
    {
        throw CHeapEx(H_FULL);
    }
    int child = CSimpleList<HeapType>::GetNumItems();
    int parent = (child - 1) / 2;
    HeapType value = 0;

    while (0 < child)
    {
        CSimpleList<HeapType>::GetItem(parent, value);
        if (item <= value)
        {
            break;
        }
        child = parent;
        parent = (parent - 1) / 2;
    }

    CSimpleList<HeapType>::Insert(child, item);
}

template <typename HeapType>
void CHeap<HeapType>::PeekTop(HeapType& item) const
{
    CSimpleList<HeapType>::GetItem(0, item);
}

template <typename HeapType>
void CHeap<HeapType>::Remove(HeapType& item)
{
    CSimpleList<HeapType>::GetItem(0, item);

    RebuildHeap(0);
}

template <typename HeapType>
void CHeap<HeapType>::RebuildHeap(int rootIndex)
{
    int lastChildIndex = CSimpleList<HeapType>::GetNumItems();
    if (lastChildIndex-- == rootIndex)
    {
        throw CHeapEx(H_EMPTY);
    }
    HeapType lastChild = 0;
    CSimpleList<HeapType>::GetItem(lastChildIndex, lastChild);

    while (rootIndex < lastChildIndex)
    {
        int left = rootIndex * 2 + 1;
        HeapType leftItem = 0;
        CSimpleList<HeapType>::GetItem(left, leftItem);

        int right = rootIndex * 2 + 2;
        HeapType rightItem = 0;
        CSimpleList<HeapType>::GetItem(right, rightItem);

        int maxIndex = 0;
        int maxItem = 0;
        int minIndex = 0;
        int minItem = 0;
        if (leftItem < rightItem)
        {
            maxIndex = right;
            maxItem = rightItem;
            minIndex = left;
            minItem = leftItem;
        }
        else
        {
            maxIndex = left;
            maxItem = leftItem;
            minIndex = right;
            minItem = rightItem;
        }

        if (lastChild < maxItem)
        {
            rootIndex = maxIndex;
        }
        else if (lastChild < minItem)
        {
            rootIndex = minIndex;
        }
        else
        {
            break;
        }
    }

    CSimpleList<HeapType>::Insert(rootIndex, lastChild);
    CSimpleList<HeapType>::Remove(0);
    CSimpleList<HeapType>::Remove(lastChildIndex);
}
