#ifndef SKIPLIST_H
#define SKIPLIST_H

#include "SkipListEntry.h"
#include "RandomHeight.h"

#define LEVEL_MAX 16

using namespace std;

template<typename K, typename V>
class SkipList
{
private:
	SkipListEntry<K, V>*	m_head; 
	SkipListEntry<K, V>*	m_tail; 
	int						m_entriesCount;
	float					m_probability;
	int						m_maxLevel;
	RandomHeight*			m_randGen;
public:
	/*constructor*/
	SkipList();

	/*destructor*/
	~SkipList();

	/*getter*/
	SkipListEntry<K,V>	getHead()			{ return m_head;		 };
	SkipListEntry<K,V>	getTail()			{ return m_tail;		 };
	int					getEntriesCount()	{ return m_entriesCount; };

	/*method*/
	void				insertEntry	(K key, V* entry);
	void				deleteEntry	(K key);
	SkipListEntry<K,V>*	findKey		(K key);
	int					randomLevel ();
	int					entriesLevel(vector<SkipListEntry<K, V>*> entries);
	void				print();
};


template<typename K, typename V>
inline SkipList<K, V>::SkipList(): 
	m_probability(0.5), 
	m_maxLevel(LEVEL_MAX)
{
	m_head = SkipListHeadEntry<K, V>(LEVEL_MAX);
	m_tail = SkipListTailEntry<K, V>(LEVEL_MAX);
	for (int i = 0; i < m_head->getForwardEntries().size(); ++i) {
		m_head->setForwardEntry(i, m_tail);
	}
}

template<typename K, typename V>
inline SkipList<K, V>::~SkipList()
{
	delete m_head;
	m_head = nullptr;
	delete m_tail;
	m_tail = nullptr;
}

template<typename K, typename V>
inline void SkipList<K, V>::insertEntry(K key, V* entry)
{
	SkipListEntry<K,V>* x = nullptr;
	x = findKey(key);
	if (x) {
		x->setValue(entry);
		return;
	}

	vector<SkipListEntry<K, V>*> update(m_head->getForwardEntries());
	int currentMaximum = entriesLevel(update);
	x = m_head;
	for (int i = currentMaximum-1; i >= 0; i--) {
		while (x->getForwardEntry(i) != nullptr && x->getForwardEntry(i)->getKey() < key) {
			x = x->getForwardEntry(i);
		}
		update[i] = x;
	}
	x = x->getForwardEntry(0);
	int newEntryLevel = 1;
	if (x->getKey() != key) {
		newEntryLevel = randomLevel();
		int currentLevel = entriesLevel(update);
		if (newEntryLevel > currentLevel) {
			for (int i = currentLevel + 1; i < newEntryLevel; i++) {
				update[i] = m_head;
			}
		}
		x = new SkipListEntry<K,V>(key, entry, newEntryLevel);
	}
	for (int i = 0; i < newEntryLevel; ++i) {
		x->setForwardEntry(i, update[i]->getForwardEntry(i));
		update[i]->setForwardEntry(i, x);
	}
}

template<typename K, typename V>
inline void SkipList<K, V>::deleteEntry(K key)
{
	vector<SkipListEntry<K, V>*> update(m_head->getForwardEntries());
	SkipListEntry<K, V>* x = m_head;
	int currentMaximum = entriesLevel(m_head->getForwardEntries());
	for (int i = currentMaximum-1; i>= 0; i-- ) {
		while (x->getForwardEntry(i) != nullptr && x->getForwardEntry(i)->getKey() < key) {
			x = x->getForwardEntry(i);
		}
		update[i] = x;
	}
	x = x->getForwardEntry(0);
	if (x->getKey() == key) {
		for (int i = 0; i < update.size(); ++i) {
			if (update[i]->getForwardEntry(i) != x) break;
			update[i]->setForwardEntry(i, x->getForwardEntry(i));
		}
		delete x;
	}
}

template<typename K, typename V>
inline SkipListEntry<K, V>* SkipList<K, V>::findKey(K key)
{
	SkipListEntry<K, V>* x(m_head);
	int currentMaximum = entriesLevel(m_head->getForwardEntries());
	for (int i = currentMaximum; i-- > 0;) {
		while (x->getForwardEntry(i) != nullptr && x->getForwardEntry(i)->getKey() < key) {
			x = x->getForwardEntry(i);
		}
	}
	x = x->getForwardEntry(0);
	if (x->getKey() == key) {
		return x;
	}
	else {
		return nullptr;
	}
}

template<typename K, typename V>
inline int SkipList<K, V>::randomLevel()
{
	int lvl(1);
	while ((((double)rand() / RAND_MAX)) < m_probability
			&&	abs(lvl) < m_maxLevel) {
		lvl++;
	}
	return abs(lvl);
}

template<typename K, typename V>
inline int SkipList<K, V>::entriesLevel(vector<SkipListEntry<K,V>*> entries)
{
	int currentLevel(1);
	if (entries[0]->getKey() == m_tail->getKey()) {
		return currentLevel;
	}
	for (int i = 0; i < entries.size(); ++i) {
		if (entries[i] != nullptr && entries[i]->getKey() != m_tail->getKey()) {
			currentLevel++;
		}
		else {
			break;
		}
	}
	return currentLevel;
}

template<typename K, typename V>
inline void SkipList<K, V>::print()
{
	SkipListEntry<K,V>* list = m_head;
	cout << endl << "{";
	while (list->getForwardEntry(0) != nullptr) {
		cout	<< "value: " << list->getForwardEntry(0)->getValue()->getName()
					<< ", key: " << list->getForwardEntry(0)->getKey()
					<< ", level: " << entriesLevel(list->getForwardEntries())
					<< endl;
		list = list->getForwardEntry(0);
	}
	cout << "}" << endl;
}



#endif