#pragma once
#ifndef PATH_H
#define PATH_H

#include <vector>

using namespace std;

template <typename T>
class Path
{
public:
	Path(vector<T> path) { this->path = path; };
	vector<T> path;
};

#endif
