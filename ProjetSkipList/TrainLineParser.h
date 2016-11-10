#ifndef TRAIN_LINE_PARSER_H
#define TRAIN_LINE_PARSER_H

#include <iostream>
#include <fstream>

#include "Line.h"

using namespace std;

class TrainLineParser {
private:
	ifstream m_file;
public:
	TrainLineParser(string filename);
	Line parseFile();
};



#endif