#ifndef _BOOK_H_
#define _BOOK_H_

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Book
{
public:
	//constructor
	Book(int, const string&, vector<string>&, vector<string>&);

	//getters function
	int getYear() const;
	string getTitle() const;
	vector<string> getAuthors() const;
	vector<string> getTags() const;

	//setter functions
	void setYear(int);
	void setTitle(string);
	void setAuthors(vector<string>);
	void setTags(vector<string>);

private:
	int year;
	string title;
	vector<string> authors;
	vector<string> tags;
};

#endif //_BOOK_H_