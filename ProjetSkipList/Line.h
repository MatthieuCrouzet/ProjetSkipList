#ifndef LINE_H
#define LINE_H

#include <iostream>
#include <vector>

#include "Station.h"
#include "SkipList.h"

using namespace std;

class Line : SkipList<Station> {
public:
	Line(SkipListNode<Station>* first, SkipListNode<Station>* last);
	Path<Station> shortestPath(int fromKey, int toKey) { return SkipList<Station>::shortestPath(fromKey, toKey); };
	void printLine();
};

#endif

