#include <iostream>
#include <vector>
#include <string>
#include "movie.h"

using namespace std;

class Movie;

Movie :: Movie(const string& newTitle, const string& newDirector, int newYear, const vector<string>& newGenres,const vector<string>& newStarring)
{
	title = newTitle;
	director = newDirector;
	year = newYear;
	genres = newGenres;
	starring = newStarring;
}

int Movie :: getYear() const
{
	return year;
}

string Movie :: getTitle() const
{
	return title;
}

string Movie :: getDirector() const
{
	return director;
}

vector<string> Movie :: getGenres() const
{
	return genres;
}

vector<string> Movie :: getStarring() const
{
	return starring;
}

void Movie :: setYear(int newYear)
{
	year = newYear;
}

void Movie :: setTitle(string newTitle)
{
	title = newTitle;
}

void Movie :: setDirector(string newDirector)
{
	director = newDirector;
}

void Movie :: setGenres(vector<string> newGenres)
{
	genres = newGenres;
}

void Movie :: setStarring(vector<string> newStarring)
{
	starring = newStarring;
}