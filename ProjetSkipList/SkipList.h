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


//Retourne le noeud qui a la clé "key"
template<typename V>
SkipListNode<V>* SkipList<V>::find(int key)
{
	SkipListNode<V>* current(m_head); // On part de la tête
	if (m_head != nullptr && m_head->getKey() == key) { //on regarde si la tête a la valeur recherchée
		return m_head;
	}
	while (current->getKey() != m_tail->getKey()) {//Tant que le noeud courant n'a pas la clé recherchée
		int i = 0;
		//On parcourt toutes les couches jusqu'à celle qui a la valeur la plus proche de la clé recherchée
		while (i < current->getAllNext().size() && current->getNext(i)->getKey() > key) i++;
		if (i == current->getAllNext().size()) return nullptr;
		current = current->getNext(i);//On actualise le noeud courant
		if (current->getKey() == key) return current;//Si on a trouvé la clé, on termine
	}
	return nullptr;// On ne trouve rien
}

template<typename V>
Path<V> SkipList<V>::shortestPath(int fromKey, int toKey)
{
	vector<V> path = vector<V>(); // Initialisation du path
	SkipListNode<V>* current(nullptr); //Pointeur de noeud de skiplist
										// Si la clé de départ est supérieure à la clé d'arrivée, on renvoit un path vide.
	if (fromKey > toKey) {
		cout << "Impossible because key " << fromKey << " is after key " << toKey << endl;
		return  Path<V>(vector<V>());
	}
	else {
		current = this->find(fromKey); // On trouve le noeud correspond à la clé
									   //S'il existe, on regarde si c'est le noeud terminal, on retourne le path
		if (current != nullptr) {
			if (fromKey == toKey) {
				path.push_back(current->getValue());
				return Path<V>(path);
			}
			//Sinon, on continue de chercher la clé d'arrivée tant qu'on ne la trouve pas ou qu'on arrive à la fin de la liste.
			else {
				while (current->getKey() != m_tail->getKey()) {
					int i = 0;
					path.push_back(current->getValue());
					//On parcours tous les noeuds suivants pour savoir où on va
					while (i < current->getAllNext().size() && current->getNext(i)->getKey() > toKey) i++;
					if (i == current->getAllNext().size()) return Path<V>(vector<V>());
					current = current->getNext(i);
					if (current->getKey() == toKey) { // On a trouvé le noeud d'arrivée
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