#ifndef _MUSIC_H_
#define _MUSIC_H_

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Music
{
public:
	//constructor
	Music(int, const string&, vector<string>&, vector<string>&);

	//getters function
	int getYear() const;
	string getTitle() const;
	vector<string> getArtists() const;
	vector<string> getGenres() const;

	//setter functions
	void setYear(int);
	void setTitle(string);
	void setArtists(vector<string>);
	void setTags(vector<string>);

private:
	int year;
	string title;
	vector<string> artists;
	vector<string> genre;
};

#endif //_MUSIC_H_