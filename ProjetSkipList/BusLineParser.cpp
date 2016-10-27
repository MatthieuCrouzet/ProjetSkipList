#include <sstream>

#include "BusLineParser.h"

BusLineParser::BusLineParser(string filename)
{
	//open the file filename
	m_file = ifstream(filename);
	if (!m_file.is_open())
	{
		string message = filename + " opening failed !";
		throw exception(message.c_str());
	}
	else {
		this->parseFile();
	}
}

void BusLineParser::parseFile()
{
	string line;

	//check if the file is still open
	if (m_file.is_open())
	{
		//read all lines
		while (getline(m_file, line)) {
			parseLine(line);
		}
		//close the file
		m_file.close();
	}
}

void BusLineParser::parseLine(string line)
{
	string city;
	string station;
	//the first element is the city
	city = line.substr(0, line.find(","));
	City* c = new City(city);
	m_cities.push_back(c);
	line.erase(0, city.size() + 1);
	//All elements after are the station in this city
	while (line.find(",") != string::npos) { //while we can reach "," in line
		station = line.substr(0, line.find(","));
		m_stations.push_back(new Station(station, c->getName()));
		line.erase(0, station.size() + 1);
	}
	m_stations.push_back(new Station(line, c->getName()));	//Add the last remaining station
}