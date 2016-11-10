#ifndef STATION_H
#define STATION_H

#include <iostream>

using namespace std;

class Station {
public:
	Station(string name) { this->name = name; }
	string name;
};
ostream& operator<<(ostream &flux, Station const& s);

#endif