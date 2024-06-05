#ifndef _MAP_H_
#define _MAP_H_

#include <iostream>
#include <cstdlib>
#include "Robot.h"

using namespace std;

const int MAPSIZE = 10;

class Robot;

class Map
{
friend class Robot;

private:
	Robot * grid[MAPSIZE][MAPSIZE];
	int aliveRobots;

public:
	Map();
	~Map();

	void setAlive(int);
	Robot * getAt(int x, int y);
	void setAt(int x, int y, Robot * rob);
	void display();
	void simulateOneFight();
};

#endif //_MAP_H_