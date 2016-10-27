#include "Station.h"

using namespace std;

Station::Station(string name, string city):
	m_city(city),
	m_name(name)
{
}


Station::~Station()
{
}

ostream& operator<<(ostream& flux, Station s) {
	flux << s.getName().c_str();
	return flux;
}
