#include <iostream>
#include <vector>
#include <string>
#include "music.h"

using namespace std;

class Music;

Music :: Music(int newYear, const string& newTitle, vector<string>& newArtists, vector<string>& newGenres)
{
	year = newYear;
	title = newTitle;
	artists = newArtists;
	genre = newGenres;
}

int Music :: getYear() const
{
	return year;
}

string Music :: getTitle() const
{
	return title;
}

vector<string> Music :: getArtists() const
{
	return artists;
}

vector<string> Music :: getGenres() const
{
	return genre;
}

void Music :: setYear(int newYear)
{
	year = newYear;
}

void Music :: setTitle(string newTitle)
{
	title = newTitle;
}

void Music :: setArtists(vector<string> newArtists)
{
	artists = newArtists;
}

void Music :: setTags(vector<string> newGenres)
{
	genre = newGenres;
}