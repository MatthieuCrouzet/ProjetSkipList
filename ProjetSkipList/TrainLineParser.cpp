#include <sstream>
#include <algorithm>

#include "TrainLineParser.h"

#include <vector>

using namespace std;

TrainLineParser::TrainLineParser(string filename)
{
	m_file = ifstream(filename);
}


void makeLevel(vector<int> keys, vector<SkipListEntry<Station>*> stations) {
	SkipListEntry<Station>* current(nullptr);
	SkipListEntry<Station>* next(nullptr);
	for (int i = 0; i < stations.size(); i++) {
		if (stations[i]->getKey() == keys[0]) {
			current = stations[i];
			break;
		}
	}
	if (current == nullptr) return;
	for (int i = 1; i < keys.size(); i++) {
		for (int j = 0; j < stations.size(); j++) {
			if (stations[j]->getKey() == keys[i]) {
				next = stations[j];
				break;
			}
		}
		if (next == nullptr) break;
		current->addNext(next);
		current = next;
	}
}

Line TrainLineParser::parseFile()
{
	if (m_file.is_open())
	{
		vector<SkipListEntry<Station>*> stations = vector<SkipListEntry<Station>*>();
		vector<int> keys = vector<int>();
		string station;
		int nbStations, nbStationsTotal, previous;
		int key;
		m_file >> nbStations;
		nbStationsTotal = nbStations;
		previous = nbStations;
		getline(m_file, station); //ignored end of first line
		for (int i = 1; i <= nbStations; i++) {
			getline(m_file, station);
			stations.push_back(new SkipListEntry<Station>(i, Station(station)));
			keys.push_back(i);
		}
		makeLevel(keys, stations);
		while (!m_file.eof()) {	
			m_file >> nbStations;
			keys.clear();
			if (nbStations <= previous && nbStations > 0) {
				for (int i = 0; i < nbStations; i++) {
					m_file >> key;
					keys.push_back(key);
				}
				makeLevel(keys, stations);
				std::cout << endl;
				previous = nbStations;
			}
			else {
				cout << "Error nb stations can't be negative or greater than nb stations total" << endl;
			}
		}
		m_file.close();
		return Line(stations[0], stations[nbStationsTotal - 1]);
	}
	throw logic_error("file not open");
}
