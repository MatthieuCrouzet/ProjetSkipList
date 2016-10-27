#ifndef STATION_H
#define STATION_H

#include <iostream>
#include <vector>

using namespace std;

class Station
{
private:
	string m_name;
	string m_city;
public:
	/*constructor*/
	Station(string name, string city);

	/*destructor*/
	~Station();

	/*getter*/
	string getName()		{ return m_name; };
	string	getCityName()	{ return m_city; };

	/*setter*/
	void setName(string name)	{ m_name = name; };
};

#endif