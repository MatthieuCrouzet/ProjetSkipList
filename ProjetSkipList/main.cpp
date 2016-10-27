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


	// 1.Initialize an empty Skip_list object
	SkipList<int,Station> skipList;

	// 2. insert()
	for (int i = 0; i < parser->getStations().size(); ++i) {
		skipList.insertEntry(i, parser->getStation(i));
	}

	// 2a. print()
	skipList.print();
	system("pause");

	// 3. find()
	SkipListEntry<int,Station>* f = nullptr;
	f = skipList.findKey(1);
	if (f) std::cout << "Entry found!\nvalue: " << f->getValue()->getName() << '\n';
	else std::cout << "Entry NOT found!\n";

	// 4. insert() - reassign
	skipList.insertEntry(40, new Station("NOUVELLE STATION", "CHICOUTIMI"));

	// 4a. print()
	skipList.print();
	system("pause");

	// 5. erase()
	skipList.deleteEntry(40);

	// 5a. print();
	skipList.print();

	std::cout << "\nDone!\n";
	system("pause");
	return 0;
}