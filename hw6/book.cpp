#include <iostream>
#include <string>
#include <vector>
#include "book.h"

using namespace std;

class Book;

Book :: Book(int newYear, const string& newTitle, vector<string>& newAuthors, vector<string>& newTags)
{
	year = newYear;
	title = newTitle;
	authors = newAuthors;
	tags = newTags;
}

int Book :: getYear() const
{
	return year;
}

string Book :: getTitle() const
{
	return title;
}

vector<string> Book :: getAuthors() const
{
	return authors;
}

vector<string> Book :: getTags() const
{
	return tags;
}

void Book :: setYear(int newYear)
{
	year = newYear;
}

void Book :: setTitle(string newTitle)
{
	title = newTitle;
}

void Book :: setAuthors(vector<string> newAuthors)
{
	authors = newAuthors;
}

void Book :: setTags(vector<string> newTags)
{
	tags = newTags;
}