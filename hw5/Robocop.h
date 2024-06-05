#ifndef _ROBOCOP_H_
#define _ROBOCOP_H_

#include <iostream>
#include "Humanic.h"

using namespace std;

class Humanic;

class Robocop : public Humanic
{

friend class Map;

public:
	Robocop(string);

	int getDamage();
	void takeDamage(int);
	string getType();
	~Robocop() {};
};

#endif //_ROBOCOP_H_