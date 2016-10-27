#ifndef BUS_LINE_PARSER_H
#define BUS_LINE_PARSER_H

#include <iostream>
#include <fstream>
#include <vector>

#include "City.h"

using namespace std;

class BusLineParser
{
public:
	BusLineParser(string filename);
	void parseFile();
	vector<City*>		getCities()				{ return m_cities; };
	vector<Station*>	getStations()			{ return m_stations; };
	City*				getCity(int index)		{ return m_cities[index]; };
	Station*			getStation(int index)	{ return m_stations[index]; };

private:
	ifstream m_file;
	vector<City*> m_cities;
	vector<Station*> m_stations;
	void parseLine(string line);
};



#endif