template <typename ListType>
CSimpleList<ListType>::CSimpleList(int numItems)
{
    SetListSize(numItems);
}

template <typename ListType>
CSimpleList<ListType>::CSimpleList(const CSimpleList& other)
{
    DestroyList();
    CopyList(other);
}

template <typename ListType>
void CSimpleList<ListType>::DestroyList()
{
    m_items = NULL;
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
        throw CListEx(L_INVALID_INDEX);
    }

    MoveItems(index, MOVE_TOWARDS_BACK);
    m_items[index] = item;
    ++m_numItems;
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
    m_currMax = m_currMax < numItems ? numItems : m_currMax;
    m_items = new ListType[m_currMax];
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
    SetListSize(other.GetNumItems());

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
