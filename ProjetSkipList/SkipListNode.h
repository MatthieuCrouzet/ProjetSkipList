/*AUTHORS :
BRANGER Mathias
CROUZET Matthieu

Defines a skipList node, component of skiplist
*/
#ifndef SKIPLIST_ENTRY_H
#define SKIPLIST_ENTRY_H

#include <vector>

using namespace std;

template<typename V>
class SkipListNode
{
private:
	vector<SkipListNode<V>*> m_next; //All directly next elements 
	int		m_key; //The key of the element
	V		m_value; //The value of the element
public:
	SkipListNode(int key, V value); //ctor

	int getKey() { return m_key; }; //returns the key of the element
	V getValue() { return m_value; }; //returns the value of the element
	vector<SkipListNode<V>*> getAllNext() { return m_next; }; //returns all directly next elements
	SkipListNode<V>* getNext(int i) { return m_next[i]; }; //returns the directly next elements i level under

	SkipListNode<V>* addNext(SkipListNode<V>* next) { m_next.insert(m_next.begin(), next); return this; }; //add a next element on the same level

};


template<typename V>
SkipListNode<V>::SkipListNode(int key, V value) :
	m_key(key), m_value(value)
{
}

#endif