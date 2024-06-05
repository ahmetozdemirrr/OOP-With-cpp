#ifndef _ROBOT_H_
#define _ROBOT_H_

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "Map.h"

using namespace std;

class Map;

class Robot
{

friend class Map;

public:
	Robot();
	Robot(int,int,int,string);
	Robot(int,int,Map *);

	void setType(int);
	void setStrength(int);
	void setHit(int);
	void setName(string);
	string getName() const;
	int getStrength() const;
	int getHit() const;
	void move();
	bool isAlive() const;
	virtual int getDamage();
	virtual string getType() const;
	virtual void takeDamage(int);
	virtual ~Robot() {};

protected:
	int x;
	int y;
	int type;
	int strength;
	int hit;
	bool moved;
	string name;
	Map * map;
};

#endif //_ROBOT_H_