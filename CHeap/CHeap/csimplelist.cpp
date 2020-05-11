template<typename ListType>
class CSimpleList
{
	CSimpleList(int numItems)
	{
		SetListSize(numItems);
		m_items = new ListType[numItems];
	}

	CSimpleList(const CSimpleList& other)
	{
		int numItems = other.GetNumItems() const;
		SetListSize(numItems);
		m_items = new ListType[numItems];
	}

	void DestroyList()
	{
		m_currMax = m_numItems = 0;
		delete[] m_items;
	}

	void GetItem(int index, ListType& item) const
	{
		item = m_items[index];
	}

	void Insert(int index, const ListType& item)
	{
		if (IsFull())
		{
			throw CListEx(L_INVALID_INDEX);
		}

		MoveItems(index, MOVE_TOWARDS_BACK);
		m_items[index] = item;
		++m_numItems;
	}

	void Remove(int index)
	{
		if (IsEmpty())
		{
			throw CListEx(L_EMPTY);
		}

		MoveItems(index, MOVE_TOWARDS_FRONT);
		--m_numItems;
	}

	void SetListSize(int numItems)
	{
		m_numItems = numItems;
	}

	CSimpleList<ListType>& operator=(const CSimpleList& rhs)
	{
		return rhs;
	}

	ListType& operator[](int index)
	{
		return m_items[index];
	}

	int CopyList(const CSimpleList& other)
	{
		for (int index = 0; index < GetNumItems(); ++index)
		{
			m_items[index] = other.m_items[index];
		}

		return GetNumItems();
	}

	int MoveItems(int index, int direction)
	{
		int numItemsMoved = 0;

		if (direction == MOVE_TOWARDS_BACK)
		{
			int numItems = m_currMax == GetNumItems() ? m_currMax - 1 : GetNumItems();

			for (int i = numItems; i > index; --i)
			{
				m_items[i] = m_items[i - 1];
				++numItemsMoved;
			}
		}
		else
		{
			for (int i = index; i < GetNumItems(); ++i)
			{
				m_items[i] = m_items[i + 1];
				++numItemsMoved;
			}
		}

		return numItemsMoved;
	}
};
