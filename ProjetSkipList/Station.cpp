#include "Station.h"

ostream& operator<<(ostream &flux, Station const& s)
{
	flux << s.name.c_str();
	return flux;
}