#ifndef CITY_H
#define CITY_H

#include <iostream>
#include <vector>

#include "Station.h"

using namespace std;

class City {
private:
	string m_name;
	vector<Station*> m_stations;
public:
	/*constructor*/
	City(string name);
	
	/*destructor*/
	~City();

	/*getter*/
	string				getName()				{ return m_name;			};
	vector<Station*>	getStations()			{ return m_stations;		};
	Station*				getStation(int index)	{ return m_stations[index]; };

	/*setter*/
	void setName(string name)					{ m_name = name;				};
	void setStation(int index, Station* station)	{ m_stations[index] = station;	};
	void setStations(vector<Station*> stations){ m_stations = stations;		};

	/*method*/
	void		insertStation(Station* station)		{ m_stations.push_back(station);					};
	void		deleteStation(Station* station)		{ deleteStation(station->getName());				};
	void		insertStation(string name)		{ m_stations.push_back(new Station(name, m_name));	};
	void		deleteStation(string name);
	Station*	findStation(string stationName);

};


#endif