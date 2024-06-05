#ifndef _OPTIMUSPRIME_H_
#define _OPTIMUSPRIME_H_

#include <iostream>
#include "Humanic.h"

using namespace std;

class Humanic;

class Optimusprime : public Humanic
{

friend class Map;

public:
	Optimusprime(string);

	int getDamage();
    string getType();
	void takeDamage(int);
	~Optimusprime() {};
};

#endif //_OPTIMUSPRIME_H_