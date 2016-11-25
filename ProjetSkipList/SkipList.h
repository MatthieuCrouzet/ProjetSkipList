#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <vector>

#include "SkipListEntry.h"
#include "Path.h"

using namespace std;

template<typename V>
class SkipList
{
protected:
	SkipListEntry<V>* m_head; //A pointer on the first element
	SkipListEntry<V>* m_tail; //A pointer on the last element
	SkipListEntry<V>* find(int key); //returns a the element which has this key or throw an error if any element has this key
public:
	SkipList(SkipListEntry<V>* first, SkipListEntry<V>* last); //ctor
		
	Path<V> shortestPath(int fromKey, int toKey); //returns a vector with all element of the shortest path between the two keys
};



template<typename V>
SkipList<V>::SkipList(SkipListEntry<V>* first, SkipListEntry<V>* last) :
	m_head(first), m_tail(last)
{
}


template<typename V>
SkipListEntry<V>* SkipList<V>::find(int key)
{
	SkipListEntry<V>* current(m_head);
	if (m_head != nullptr && m_head->getKey() == key) {
		return m_head;
	}
	while (current->getKey() != m_tail->getKey()) {
		int i = 0;
		while (i < current->getAllNext().size() && current->getNext(i)->getKey() > key) i++;
		if (i == current->getAllNext().size()) return nullptr;
		current = current->getNext(i);
		if (current->getKey() == key) return current;
	}
	return nullptr;
}

template<typename V>
Path<V> SkipList<V>::shortestPath(int fromKey, int toKey)
{
	vector<V> path = vector<V>();
	SkipListEntry<V>* current(nullptr);
	if (fromKey > toKey) {
		cout << "Impossible because key " << fromKey << " is after key " << toKey << endl;
		return  Path<V>(vector<V>());
	}
	else {
		current = this->find(fromKey);
		if (current != nullptr) {
			if (fromKey == toKey) {
				path.push_back(current->getValue());
				return Path<V>(path);
			}
			else {
				while (current->getKey() != m_tail->getKey()) {
					int i = 0;
					path.push_back(current->getValue());
					while (i < current->getAllNext().size() && current->getNext(i)->getKey() > toKey) i++;
					if (i == current->getAllNext().size()) return Path<V>(vector<V>());
					current = current->getNext(i);
					if (current->getKey() == toKey) {
						path.push_back(current->getValue());
						return Path<V>(path);
					}
				}
				return Path<V>(vector<V>());
			}
		}
		else {
			return Path<V>(vector<V>());
		}
	}
}

#endif