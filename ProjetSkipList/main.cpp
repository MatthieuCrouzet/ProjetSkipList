#include <iostream>
#include <vector>

#include "SkipListNode.h"
#include "SkipList.h"
#include "Line.h"
#include "TrainLineParser.h"
#include "Station.h"
#include "Path.h"

using namespace std;

int main() {

	
	//	cout << "Entries creation" << endl;
	//	
	//	SkipListNode<int>* one		= new SkipListNode<int>(1, 1);
	//	SkipListNode<int>* two		= new SkipListNode<int>(2, 2);
	//	SkipListNode<int>* three	= new SkipListNode<int>(3, 3);
	//	SkipListNode<int>* four	= new SkipListNode<int>(4, 4);
	//	SkipListNode<int>* five	= new SkipListNode<int>(5, 5);
	//	SkipListNode<int>* six		= new SkipListNode<int>(6, 6);
	//	SkipListNode<int>* seven	= new SkipListNode<int>(7, 7);
	//	SkipListNode<int>* eight	= new SkipListNode<int>(8, 8);
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
	//	vector<SkipListNode<int>*> shortestPath = skipList.shortestPath(2, 7);
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
		lyonGrenoble.printLine(Path<Station>());
		cout << endl << "Entrer the key of the station you are : ";
		cin >> from;
		cout << "Entrer the key of the station where you want to go : ";
		cin >> to;
		Path<Station> stationsOnPath = lyonGrenoble.shortestPath(from, to);
		lyonGrenoble.printLine(stationsOnPath);
		cout << endl;
		for (int i = 0; i < stationsOnPath.path.size(); i++) {
			if (i < 9)
				cout << "\t > Step " << i + 1 << "  : " << stationsOnPath.path[i] << endl;
			else
				cout << "\t > Step " << i + 1 << " : " << stationsOnPath.path[i] << endl;
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