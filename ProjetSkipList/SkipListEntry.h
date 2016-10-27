#ifndef SKIPLIST_ENTRY_H
#define SKIPLIST_ENTRY_H

#include <vector>

using namespace std;

template<typename K, typename V>
class SkipListEntry
{
private:
	int		m_entryHeight;
	vector<SkipListEntry<K,V>*> m_forward; // pointers to successor entries
	K		m_key;
	V*		m_value;
public:
	/*constructor*/
	SkipListEntry(K key, V* value, int height);
	/*destructor*/
	~SkipListEntry();

	/*getter*/
	int									getEntryHeight()		{ return m_entryHeight; };
	K									getKey()				{ return m_key;			};
	V*									getValue()				{ return m_value;		};
	vector<SkipListEntry<K,V>*>	getForwardEntries()		{ return m_forward;		};
	SkipListEntry<K,V>*					getForwardEntry(int i)	{ return m_forward[i];  };

	/*setter*/
	void setEntryHeight(int height)							{ m_entryHeight = height; };
	void setKey(K key)										{ m_key = key;			  };
	void setValue(V* value)									{ m_value = value;        };
	void setForwardEntry(int i, SkipListEntry<K, V>* entry)	{ m_forward[i] = entry;	  };


};


template<typename K, typename V>
inline SkipListEntry<K, V>::SkipListEntry(K key, V * value, int height):
	m_key(key),
	m_value(value),
	m_entryHeight(height)
{
	for (int i = 0; i < height; ++i) {
		m_forward.emplace_back(nullptr);
	}
}

template<typename K, typename V>
inline SkipListEntry<K, V>::~SkipListEntry()
{
	delete m_value;
	m_value = nullptr;
}


/*constructor head and tail*/
template<typename K, typename V>
SkipListEntry<K, V>* SkipListHeadEntry(int maxLevel);

template<typename K, typename V>
SkipListEntry<K, V>* SkipListTailEntry(int maxLevel);

template<typename K, typename V>
inline SkipListEntry<K, V>* SkipListHeadEntry(int maxLevel)
{
	return new SkipListEntry<K, V>(numeric_limits<K>::min(), nullptr, maxLevel);
}

template<typename K, typename V>
inline SkipListEntry<K, V>* SkipListTailEntry(int maxLevel)
{
	return new SkipListEntry<K, V>(numeric_limits<K>::max(), nullptr, maxLevel);
}

#endif