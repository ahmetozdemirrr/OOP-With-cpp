#ifndef _ROOMBA_H_
#define _ROOMBA_H_

#include <iostream>
#include <cstdlib>
#include <string>
#include "Robot.h"

using namespace std;

class Robot;

class Roomba : public Robot
{

friend class Map;

public:
	Roomba(string);

	int getDamage();
	string getType();
	void takeDamage(int);
	~Roomba() {};
};

#endif //_ROOMBA_H_