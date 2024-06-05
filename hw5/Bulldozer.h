#ifndef _BULLDOZER_H_
#define _BULLDOZER_H_

#include <iostream>
#include <cstdlib>
#include "Robot.h"

using namespace std;

class Robot;

class Bulldozer : public Robot
{

friend class Map;

public:
	Bulldozer(string);

	int getDamage();
	string getType();
	void takeDamage(int);
	~Bulldozer() {};
};

#endif //_BULLDOZER_H_