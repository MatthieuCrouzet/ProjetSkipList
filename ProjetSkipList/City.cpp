#include "City.h"

using namespace std;

City::City(string name):
	m_name(name)
{
}

City::~City()
{
	for (int i = 0; i < m_stations.size(); i++) {
		delete m_stations[i];
		m_stations[i] = nullptr;
	}
	m_stations.~vector();
}

void City::deleteStation(string name)
{
	for (int i = 0; i < m_stations.size(); i++) {
		if (m_stations[i]->getName() == name) {			
			m_stations[i]->~Station();
			m_stations.erase(m_stations.begin() + i, m_stations.begin() + i + 1);
		}
	}
}

Station * City::findStation(string stationName)
{
	for (int i = 0; i < m_stations.size(); i++) {
		if (m_stations[i]->getName() == stationName) {
			return m_stations[i];
		}
	}
	return nullptr;
}
