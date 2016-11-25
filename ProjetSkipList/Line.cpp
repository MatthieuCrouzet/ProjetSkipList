#include "Line.h"
#include <map>

using namespace std;
//
//Line::Line(string name):
//	m_name(name)
//{
//}
//
//Line::~Line()
//{
//	for (int i = 0; i < m_stations.size(); i++) {
//		delete m_stations[i];
//		m_stations[i] = nullptr;
//	}
//	m_stations.~vector();
//}
//
//void Line::deleteStation(string name)
//{
//	for (int i = 0; i < m_stations.size(); i++) {
//		if (m_stations[i]->getName() == name) {			
//			m_stations[i]->~Station();
//			m_stations.erase(m_stations.begin() + i, m_stations.begin() + i + 1);
//		}
//	}
//}
//
//Station * Line::findStation(string stationName)
//{
//	for (int i = 0; i < m_stations.size(); i++) {
//		if (m_stations[i]->getName() == stationName) {
//			return m_stations[i];
//		}
//	}
//	return nullptr;
//}
//
//SkipListEntry<int, Station>* Line::toSkipListEntries(int lvl, SkipListEntry<int, Station>* tail)
//{
//	SkipListEntry<int, Station>* curr = nullptr;
//	SkipListEntry<int, Station>* prev = nullptr;
//	SkipListEntry<int, Station>* head = nullptr;
//	if (m_stations.size() > 0) {
//		head = new SkipListEntry<int, Station>(m_stations[0]->getKey(), m_stations[0], lvl);
//		prev = head;
//		for (int i = 1; i < m_stations.size(); i++) {
//			curr = new SkipListEntry<int, Station>(m_stations[i]->getKey(), m_stations[i], lvl);
//			prev->setForwardEntry(0, curr);
//			prev = curr;
//		}
//		prev->setForwardEntry(0, tail);
//	}
//	return head;
//}
//

Line::Line(SkipListEntry<Station>* first, SkipListEntry<Station>* last):
	SkipList<Station>(first, last)
{
}

void printRecLine(SkipListEntry<Station>* current, int lastStation, map<int, int>& linePrinted) {

	int key = current->getKey();
	for (int i = lastStation + 1; i < key; i++) {
		cout << "--";
		for (int j = 0; j < floor(log10(abs(i))) + 1; j++)
			cout << "-";
	}

	cout << "--" << key;

	size_t tempSize = current->getAllNext().size();
	if (tempSize != 0) {
		printRecLine(current->getNext(linePrinted[key]), key, linePrinted);
		linePrinted[key]++;
	}
}

void printRecStationsNames(SkipListEntry<Station>* current, int nb)
{
	cout << "- " << nb << "  " << current->getValue().name.c_str() << endl;

	size_t tempSize = current->getAllNext().size();
	if (tempSize != 0) {
		printRecStationsNames(current->getNext(tempSize - 1), nb + 1);
	}
}

void Line::printLine()
{
	size_t nbLines = m_head->getAllNext().size();
	int nbStops = m_tail->getKey(); // nb stop is from 1 to max Key

	map<int, int> linePrinted;

	for (int i = 0; i < nbLines; i++) {
		SkipListEntry<Station>* temp = m_head->getAllNext()[i];
		cout << "1";
		printRecLine(temp, 1, linePrinted);
		cout << endl;
	}

	cout << endl;
	printRecStationsNames(m_head, 1);
}


