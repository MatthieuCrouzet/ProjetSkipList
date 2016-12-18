/*AUTHORS :
BRANGER Mathias
CROUZET Matthieu

Functions to work on Line
*/
#include "Line.h"
#include <map>
#include <windows.h>
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
//SkipListNode<int, Station>* Line::toSkipListEntries(int lvl, SkipListNode<int, Station>* tail)
//{
//	SkipListNode<int, Station>* curr = nullptr;
//	SkipListNode<int, Station>* prev = nullptr;
//	SkipListNode<int, Station>* head = nullptr;
//	if (m_stations.size() > 0) {
//		head = new SkipListNode<int, Station>(m_stations[0]->getKey(), m_stations[0], lvl);
//		prev = head;
//		for (int i = 1; i < m_stations.size(); i++) {
//			curr = new SkipListNode<int, Station>(m_stations[i]->getKey(), m_stations[i], lvl);
//			prev->setForwardEntry(0, curr);
//			prev = curr;
//		}
//		prev->setForwardEntry(0, tail);
//	}
//	return head;
//}
//

Line::Line(SkipListNode<Station>* first, SkipListNode<Station>* last):
	SkipList<Station>(first, last)
{
}

void printRecLine(SkipListNode<Station>* current, int lastStation, int linePrinted, Path<Station>& pathToPrint) {

	int key = current->getKey();
	size_t tempSize = current->getAllNext().size();
	bool firstPrint = false;

	//If it corresponds to the path, color in red
	if (pathToPrint.path.size() > 0 ) {
		for (int i = 0; i < pathToPrint.path.size() - 1; i++) {
			if (pathToPrint.path[i].id == lastStation &&
				pathToPrint.path[i + 1].id == key)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
			else if (i == 0 && pathToPrint.path[i].id == key &&
				pathToPrint.path[i + 1].id == current->getNext(tempSize - 1 - linePrinted)->getKey()) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
				firstPrint = true;
			}
		}
	}

	for (int i = lastStation + 1; i < key; i++) {
		cout << "--";
		for (int j = 0; j < floor(log10(abs(i))) + 1; j++)
			cout << "-";
	}

	if(firstPrint)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

	if (key != 1)
		cout << "--";

	if (firstPrint)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
	cout << key;


	if (tempSize>0 && tempSize-1 >=linePrinted) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		printRecLine(current->getNext(tempSize - 1 -linePrinted), key, linePrinted, pathToPrint);

	}
}

void printRecStationsNames(SkipListNode<Station>* current, int nb)
{
	cout << "- " << nb << "  " << current->getValue().name.c_str() << endl;

	size_t tempSize = current->getAllNext().size();
	if (tempSize != 0) {
		printRecStationsNames(current->getNext(tempSize - 1), nb + 1);
	}
}

void Line::printLine(Path<Station> pathToPrint)
{
	size_t nbLines = m_head->getAllNext().size();
	int nbStops = m_tail->getKey(); // nb stop is from 1 to max Key



	for (int i = nbLines-1; i >= 0; i--) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		printRecLine(m_head, 1, i, pathToPrint);
		cout << endl;
	}

	cout << endl;
	printRecStationsNames(m_head, 1);
}
