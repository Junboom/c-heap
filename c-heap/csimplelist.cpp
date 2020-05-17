template <typename ListType>
CSimpleList<ListType>::CSimpleList(int numItems)
{
    SetListSize(numItems);
}

template <typename ListType>
CSimpleList<ListType>::CSimpleList(const CSimpleList& other)
{
    SetListSize(other.m_currMax);
    CopyList(other);
}

template <typename ListType>
void CSimpleList<ListType>::DestroyList()
{
    m_items = NULL;
    delete[] m_items;
    m_currMax = m_numItems = 0;
}

template <typename ListType>
void CSimpleList<ListType>::GetItem(int index, ListType& item) const
{
    item = m_items[index];
}

template <typename ListType>
void CSimpleList<ListType>::Insert(int index, const ListType& item)
{
    if (IsFull())
    {
        throw CListEx(L_FULL);
    }

    MoveItems(index, MOVE_TOWARDS_BACK);
    m_items[index] = item;
    ++m_numItems;

    if (IsFull())
    {
        int index;
        int currMax = m_currMax + DEFAULT_NUM_ITEMS;
        int numItems = GetNumItems();
        ListType* items = new ListType[currMax];

        for (index = 0; index < numItems; ++index)
        {
            items[index] = m_items[index];
        }

        SetListSize(currMax);
        m_numItems = numItems;
        for (index = 0; index < numItems; ++index)
        {
            m_items[index] = items[index];
        }

        items = NULL;
        delete[] items;
    }
}

template <typename ListType>
void CSimpleList<ListType>::Remove(int index)
{
    if (IsEmpty())
    {
        throw CListEx(L_EMPTY);
    }

    MoveItems(index, MOVE_TOWARDS_FRONT);
    --m_numItems;
}

template <typename ListType>
void CSimpleList<ListType>::SetListSize(int numItems)
{
    m_currMax = numItems;
    m_numItems = 0;
    m_items = new ListType[numItems];
}

template <typename ListType>
CSimpleList<ListType>& CSimpleList<ListType>::operator=(const CSimpleList& rhs)
{
    CopyList(rhs);
    return *this;
}

template <typename ListType>
ListType& CSimpleList<ListType>::operator[](int index)
{
    return m_items[index];
}

template <typename ListType>
int CSimpleList<ListType>::CopyList(const CSimpleList& other)
{
    m_numItems = other.GetNumItems();

    for (int index = 0; index < GetNumItems(); ++index)
    {
        m_items[index] = other.m_items[index];
    }

    return GetNumItems();
}

template <typename ListType>
int CSimpleList<ListType>::MoveItems(int index, int direction)
{
    int numItemsMoved = 0;

    if (direction == MOVE_TOWARDS_BACK)
    {
        for (int i = m_currMax - 1; i > index; --i)
        {
            m_items[i] = m_items[i - 1];
            ++numItemsMoved;
        }
    }
    else
    {
        for (int i = index + 1; i < m_currMax - 1; ++i)
        {
            m_items[i - 1] = m_items[i];
            ++numItemsMoved;
        }
    }

    return numItemsMoved;
}
