/*AUTHORS :
BRANGER Mathias
CROUZET Matthieu

Functions used to parse a transport Line
*/
#include <sstream>
#include <algorithm>

#include "TrainLineParser.h"

#include <vector>

using namespace std;

TrainLineParser::TrainLineParser(string filename)
{
	m_file = ifstream(filename);
}


void makeLevel(vector<int> keys, vector<SkipListNode<Station>*> stations) {
	SkipListNode<Station>* current(nullptr);
	SkipListNode<Station>* next(nullptr);
	for (int i = 0; i < stations.size(); i++) { //On cherche le noeud courant
		if (stations[i]->getKey() == keys[0]) {
			current = stations[i];
			break;
		}
	}
	if (current == nullptr) return; // On cherche qui doit être le suivant
	for (int i = 1; i < keys.size(); i++) {
		for (int j = 0; j < stations.size(); j++) {
			if (stations[j]->getKey() == keys[i]) {
				next = stations[j];
				break;
			}
		}
		if (next == nullptr) break; // On ajoute le suivant au courant
		current->addNext(next);
		current = next;
	}
}

Line TrainLineParser::parseFile()
{
	if (m_file.is_open()) {
		vector<SkipListNode<Station>*> stations = vector<SkipListNode<Station>*>(); // Initialisation de la skiplist
		vector<int> keys = vector<int>(); // Initialisation de la liste des clés
		string station; // nom de la station
		int nbStations, nbStationsTotal, previous;
		int key;
		m_file >> nbStations; // on récupère le nombre de station
		nbStationsTotal = nbStations;
		previous = nbStations;
		getline(m_file, station); //on ignore la fin de la première ligne
		for (int i = 1; i <= nbStations; i++) { //On ajoute chaque station à la skipList la plus basse
			getline(m_file, station);
			stations.push_back(new SkipListNode<Station>(i, Station(station, i)));
			keys.push_back(i);
		}
		makeLevel(keys, stations); //on fait la liaison entre les noeuds
		while (!m_file.eof()) {	//on continue de lire les stations
			m_file >> nbStations;
			keys.clear(); // On réinitialise les clés lues
			if (nbStations <= previous && nbStations > 0) {
				for (int i = 0; i < nbStations; i++) { //On lit les stations déservies
					m_file >> key;
					keys.push_back(key); // On les ajoute à celles désservies par le train
				}
				makeLevel(keys, stations); // On ajoute toutes les stations déservies par le train à la ligne
				std::cout << endl;
				previous = nbStations;
			}
			else {
				cout << "Error nb stations can't be negative or greater than nb stations total" << endl;
			}
		}
		m_file.close();
		return Line(stations[0], stations[nbStationsTotal - 1]); //Retourner la ligne construite
	}
	throw logic_error("file not open");
}
