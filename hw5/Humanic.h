#ifndef _HUMANIC_H_
#define _HUMANIC_H_

#include <iostream>
#include "Robot.h"

using namespace std;

class Robot;

class Humanic : public Robot
{

friend class Map;

public:
	Humanic();
	Humanic(int,int,int,string);

	string getType() const;
	int getDamage();
	void takeDamage(int);
	~Humanic() {};
};

#endif //_HUMANIC_H_