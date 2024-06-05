#ifndef _MOVIE_H_
#define _MOVIE_H_

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Movie
{
public:
	//constructor
	Movie(const string&, const string&, int, const vector<string>&,const vector<string>&);

	//getters function
	int getYear() const;
	string getTitle() const;
	string getDirector() const;
	vector<string> getGenres() const;
	vector<string> getStarring() const;

	//setter functions
	void setYear(int);
	void setTitle(string);
	void setDirector(string);
	void setGenres(vector<string>);
	void setStarring(vector<string>);

private:
	int year;
	string title;
	string director;
	vector<string> genres;
	vector<string> starring;
};

#endif //_MOVIE_H_