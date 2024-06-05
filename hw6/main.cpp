#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>

#include "movie.h"
#include "book.h"
#include "music.h"
#include "catalog.h"

int main(int argc, char const *argv[])
{
	Catalog<Movie> movie;
	Catalog<Music> music;
	Catalog<Book> book;

	movie.readDataFile("data.txt");

	return 0;
}

