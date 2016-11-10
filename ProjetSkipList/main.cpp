#include <iostream>
#include <vector>

#include "SkipListEntry.h"
#include "SkipList.h"
#include "Line.h"
#include "TrainLineParser.h"
#include "Station.h"
#include "Path.h"

using namespace std;

int main() {

	
	//	cout << "Entries creation" << endl;
	//	
	//	SkipListEntry<int>* one		= new SkipListEntry<int>(1, 1);
	//	SkipListEntry<int>* two		= new SkipListEntry<int>(2, 2);
	//	SkipListEntry<int>* three	= new SkipListEntry<int>(3, 3);
	//	SkipListEntry<int>* four	= new SkipListEntry<int>(4, 4);
	//	SkipListEntry<int>* five	= new SkipListEntry<int>(5, 5);
	//	SkipListEntry<int>* six		= new SkipListEntry<int>(6, 6);
	//	SkipListEntry<int>* seven	= new SkipListEntry<int>(7, 7);
	//	SkipListEntry<int>* eight	= new SkipListEntry<int>(8, 8);
	//	
	//	/*
	//		.							.
	//		.				.			.
	//		.		.		.	.		.
	//		.	.	.	.	.	.	.	.
	//		1	2	3	4	5	6	7	8
	//	*/
	//	
	//	cout << "Links creation" << endl;
	//	
	//	one->addNext(two->addNext(three->addNext(four->addNext(five->addNext(six->addNext(seven->addNext(eight)))))));
	//	one->addNext(three->addNext(five->addNext(six->addNext(eight))));
	//	one->addNext(five->addNext(eight));
	//	one->addNext(eight);
	//	
	//	cout << "SkipList creation" << endl;
	//	
	//	SkipList<int> skipList(one, eight);
	//	
	//	cout << "Creation success" << endl;
	//	
	//	cout << "Calcul shortesWay from key 2 to key 7" << endl;
	//	
	//	vector<SkipListEntry<int>*> shortestPath = skipList.shortestPath(2, 7);
	//	
	//	for (int i = 0; i < shortestPath.size(); i++) {
	//		cout << "Step " << i + 1 << " : " << shortestPath[i]->getValue() << endl;
	//	}

	TrainLineParser parser("LyonGrenoble.txt");
	Line lyonGrenoble = parser.parseFile();
	/*
		*						*			*		*		- 1 Lyon Part-Dieu			 - 5 La Verpilliere		- 9  Saint-Andre-Le-Gaz
		*				*		*	*		*		*		- 2 Venissieux				 - 6 L'Isle D'abeau		- 10 Voiron	
		*	*	*	*	*	*	*	*	*	*	*	*		- 3 Saint-Priest			 - 7 Bourgoin-Jallieu	- 11 Moirans			
		1	2	3	4	5	6	7	8	9	10	11	12		- 4 Saint-Quentin Fallavier	 - 8 La Tour-Du-Pin		- 12 Grenoble			
	*/
	int from, to;
	bool retry = true;
	while (retry) {
		cout << "*-----------------------------------*" << endl;
		cout << "*-----------------*---------*-------*" << endl;
		cout << "*-----------*-----*--*------*-------*" << endl;	
		cout << "*--*--*--*--*--*--*--*--*---*---*---*" << endl;	
		cout << "1--2--3--4--5--6--7--8--9--10--11--12" << endl;
		cout << endl;
		cout << "- 1  Lyon Part-Dieu" << endl;
		cout << "- 2  Venissieux" << endl;
		cout << "- 3  Saint-Priest" << endl;
		cout << "- 4  Saint-Quentin Fallavier" << endl;
		cout << "- 5  La Verpilliere" << endl;
		cout << "- 6  L'Isle D'abeau" << endl;
		cout << "- 7  Bourgoin-Jallieu" << endl;
		cout << "- 8  La Tour-Du-Pin" << endl;
		cout << "- 9  Saint-Andre-Le-Gaz" << endl;
		cout << "- 10 Voiron" << endl;
		cout << "- 11 Moirans" << endl;
		cout << "- 12 Grenoble" << endl;
		cout << endl << "Entrer the key of the station you are : ";
		cin >> from;
		cout << "Entrer the key of the station where you want to go : ";
		cin >> to;
		Path<Station> stationsOnPath = lyonGrenoble.shortestPath(from, to);

		for (int i = 0; i < stationsOnPath.path.size(); i++) {
			if (i < 9)
				cout << "Step " << i + 1 << "  : " << stationsOnPath.path[i] << endl;
			else
				cout << "Step " << i + 1 << " : " << stationsOnPath.path[i] << endl;
		}
		bool yn = false;
		char response;
		while (!yn) {
			cout << "Retry ? (y/n)" << endl;
			cin >> response;
			if (response == 'y' || response == 'n') yn = true;
		}
		if (response == 'n') retry = false;
	}
	return 0;
}