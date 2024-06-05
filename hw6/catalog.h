#ifndef _CATALOG_H_
#define _CATALOG_H_

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "movie.h"
#include "book.h"
#include "music.h"

using namespace std;

template <class T>
class Catalog
{
public:
	void readDataFile(const string&);
	void processCommands(const string&);

private:
	vector<T> items;
	vector<string> log;
};

#endif //_MOVIE_CATALOG_H_