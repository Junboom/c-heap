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

    int index = CSimpleList<HeapType>::GetNumItems();
    CSimpleList<HeapType>::Insert(index, item);

    int parentIndex = (index - 1) / 2;
    HeapType parentItem = 0;
    CSimpleList<HeapType>::GetItem(parentIndex, parentItem);

    while (0 < index && parentItem < item)
    {
        CSimpleList<HeapType>::Remove(parentIndex);
        CSimpleList<HeapType>::Insert(parentIndex, item);
        CSimpleList<HeapType>::Remove(index);
        CSimpleList<HeapType>::Insert(index, parentItem);

        parentIndex = ((index = parentIndex) - 1) / 2;
        CSimpleList<HeapType>::GetItem(parentIndex, parentItem);
    }

    cout << "insertIndex: " << index << " item: " << item << endl;
}

template <typename HeapType>
void CHeap<HeapType>::PeekTop(HeapType& item) const
{
    CSimpleList<HeapType>::GetItem(0, item);
}

template <typename HeapType>
void CHeap<HeapType>::Remove(HeapType& item)
{
    if (CSimpleList<HeapType>::IsEmpty())
    {
        throw CHeapEx(H_EMPTY);
    }

    int rootIndex = 0;
    CSimpleList<HeapType>::GetItem(rootIndex, item);

    int lastIndex = CSimpleList<HeapType>::GetNumItems() - 1;
    HeapType lastItem = 0;
    CSimpleList<HeapType>::GetItem(lastIndex, lastItem);
    CSimpleList<HeapType>::Remove(lastIndex);

    CSimpleList<HeapType>::Remove(rootIndex);
    CSimpleList<HeapType>::Insert(rootIndex, lastItem);

    RebuildHeap(rootIndex);
}

template <typename HeapType>
void CHeap<HeapType>::RebuildHeap(int rootIndex)
{
    HeapType rootItem = 0;
    CSimpleList<HeapType>::GetItem(rootIndex, rootItem);

    int numItems = CSimpleList<HeapType>::GetNumItems();

    while (rootIndex < numItems)
    {
        int leftIndex = rootIndex * 2 + 1;
        HeapType leftItem = 0;
        CSimpleList<HeapType>::GetItem(leftIndex, leftItem);

        int rightIndex = rootIndex * 2 + 2;
        HeapType rightItem = 0;
        CSimpleList<HeapType>::GetItem(rightIndex, rightItem);

        int maxIndex = 0;
        HeapType maxItem = 0;
        if (leftItem < rightItem)
        {
            maxIndex = rightIndex;
            maxItem = rightItem;
        }
        else
        {
            maxIndex = leftIndex;
            maxItem = leftItem;
        }

        if (maxItem <= rootItem)
        {
            break;
        }

        CSimpleList<HeapType>::Remove(rootIndex);
        CSimpleList<HeapType>::Insert(rootIndex, maxItem);
        CSimpleList<HeapType>::Remove(maxIndex);
        CSimpleList<HeapType>::Insert(maxIndex, rootItem);

        rootIndex = maxIndex;
    }
}
