#include <iostream>
#include <sstream>

#include "SkipList.h"
#include "BusLineParser.h"

using namespace std;

int main() {

	BusLineParser* parser = nullptr;
	try {
		parser = new BusLineParser("Line1.txt");
	}
	catch (exception e) {
		cout << "Error : " << e.what() << endl;
		system("pause");
		return -1;
	}

	

	SkipList<int,Station> skipList;

	for (int i = 0; i < parser->getStations().size(); ++i) {
		skipList.insertEntry(i, parser->getStation(i));
	}
	skipList.print();

	SkipListEntry<int,Station>* f = nullptr;
	f = skipList.findKey(1);
	if (f) std::cout << "Entry found!\nvalue: " << f->getValue() << '\n';
	else std::cout << "Entry NOT found!\n";

	skipList.insertEntry(40, new Station("NOUVELLE STATION", "CHICOUTIMI"));

	
	skipList.print();
	
	skipList.deleteEntry(40);
	skipList.print();

	std::cout << "\nDone!\n";
	system("pause");
	return 0;
}