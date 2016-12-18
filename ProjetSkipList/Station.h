/*AUTHORS :
BRANGER Mathias
CROUZET Matthieu

Defines a Station
*/
#ifndef STATION_H
#define STATION_H

#include <iostream>

using namespace std;

class Station {
public:
	Station(string name,int id) { this->name = name; this->id = id;}
	string name;
	int id;
};
ostream& operator<<(ostream &flux, Station const& s);

#endif