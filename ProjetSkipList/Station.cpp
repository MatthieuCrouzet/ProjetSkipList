#include "Station.h"

ostream& operator<<(ostream &flux, Station const& s)
{
	flux << "("<<s.id<<")"<< s.name.c_str();
	return flux;
}