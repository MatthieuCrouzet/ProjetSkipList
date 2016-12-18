#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <vector>

#include "SkipListNode.h"
#include "Path.h"

using namespace std;

template<typename V>
class SkipList
{
protected:
	SkipListNode<V>* m_head; //A pointer on the first element
	SkipListNode<V>* m_tail; //A pointer on the last element
	SkipListNode<V>* find(int key); //returns a the element which has this key or throw an error if any element has this key
public:
	SkipList(SkipListNode<V>* first, SkipListNode<V>* last); //ctor
		
	Path<V> shortestPath(int fromKey, int toKey); //returns a vector with all element of the shortest path between the two keys
};



template<typename V>
SkipList<V>::SkipList(SkipListNode<V>* first, SkipListNode<V>* last) :
	m_head(first), m_tail(last)
{
}


//Retourne le noeud qui a la cl� "key"
template<typename V>
SkipListNode<V>* SkipList<V>::find(int key)
{
	SkipListNode<V>* current(m_head); // On part de la t�te
	if (m_head != nullptr && m_head->getKey() == key) { //on regarde si la t�te a la valeur recherch�e
		return m_head;
	}
	while (current->getKey() != m_tail->getKey()) {//Tant que le noeud courant n'a pas la cl� recherch�e
		int i = 0;
		//On parcourt toutes les couches jusqu'� celle qui a la valeur la plus proche de la cl� recherch�e
		while (i < current->getAllNext().size() && current->getNext(i)->getKey() > key) i++;
		if (i == current->getAllNext().size()) return nullptr;
		current = current->getNext(i);//On actualise le noeud courant
		if (current->getKey() == key) return current;//Si on a trouv� la cl�, on termine
	}
	return nullptr;// On ne trouve rien
}

template<typename V>
Path<V> SkipList<V>::shortestPath(int fromKey, int toKey)
{
	vector<V> path = vector<V>(); // Initialisation du path
	SkipListNode<V>* current(nullptr); //Pointeur de noeud de skiplist
										// Si la cl� de d�part est sup�rieure � la cl� d'arriv�e, on renvoit un path vide.
	if (fromKey > toKey) {
		cout << "Impossible because key " << fromKey << " is after key " << toKey << endl;
		return  Path<V>(vector<V>());
	}
	else {
		current = this->find(fromKey); // On trouve le noeud correspond � la cl�
									   //S'il existe, on regarde si c'est le noeud terminal, on retourne le path
		if (current != nullptr) {
			if (fromKey == toKey) {
				path.push_back(current->getValue());
				return Path<V>(path);
			}
			//Sinon, on continue de chercher la cl� d'arriv�e tant qu'on ne la trouve pas ou qu'on arrive � la fin de la liste.
			else {
				while (current->getKey() != m_tail->getKey()) {
					int i = 0;
					path.push_back(current->getValue());
					//On parcours tous les noeuds suivants pour savoir o� on va
					while (i < current->getAllNext().size() && current->getNext(i)->getKey() > toKey) i++;
					if (i == current->getAllNext().size()) return Path<V>(vector<V>());
					current = current->getNext(i);
					if (current->getKey() == toKey) { // On a trouv� le noeud d'arriv�e
						path.push_back(current->getValue());
						return Path<V>(path);
					}
				}
				return Path<V>(vector<V>());
			}
		}
		else { return Path<V>(vector<V>()); }
	}
}


#endif