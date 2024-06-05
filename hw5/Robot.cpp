#include <iostream>
#include <cstdlib>
#include <string>
#include "Robot.h"
#include "Map.h"

class Map;

Robot :: Robot() : type(4), strength(0), hit(0), name("")
{}

Robot :: Robot(int comType, int comStrength, int comHit, string comName)
{
	this -> type = comType;
	this -> strength = comStrength;
	this -> hit = comHit;
	this -> name = comName;
}

Robot :: Robot(int comX, int comY, Map * comMap)
{
	this -> map = comMap;
	this -> x = comX;
	this -> y = comY;

	map -> setAt(x,y,this); //map matrisimizin (x,y) koordinatına objemizi yerleştiriyoruz
}

void Robot :: setType(int comType)
{
	this -> type = comType;
}

void Robot :: setStrength(int comStrength)
{
	this -> strength = comStrength;
}

void Robot :: setHit(int comHit)
{
	this -> hit = comHit;
}

void Robot :: setName(string comName)
{
	this -> name = comName;
}

string Robot :: getType() const
{
	switch(this -> type)
	{
	case 0: return "optimusprime";

	case 1: return "robocop";

	case 2: return "roomba";

	case 3: return "bulldozer";

	}
	return "unknown";
}

string Robot :: getName() const
{
	return this -> name;
}

int Robot :: getStrength() const
{
	return this -> strength;
}

int Robot :: getHit() const
{
	return this -> hit;
}

int Robot :: getDamage()
{
	int damage;

	damage = (rand() % getStrength()) + 1;

	return damage;
}

void Robot :: takeDamage(int damage) 
{
    this -> hit -= damage;

    if (hit <= 0) 
    {
        cout << name << " is dead." << endl;
        hit = 0;
        (map->aliveRobots)--;
    }
}

bool Robot :: isAlive() const
{
	if (this -> hit > 0)
	{
		return true;
	}
	return false;
}

void Robot :: move()
{
    int path = rand() % 4;//rastgele hareket

    if (path == 0) 
    {
        if ((y > 0) && (map -> getAt(x,y-1) == NULL))
        {
            map -> setAt(x,y-1,map -> getAt(x,y));
            map -> setAt(x,y,NULL);  
            y--;
        }
    }

    else if (path == 1)
    {
        if ((y < MAPSIZE - 1) && (map -> getAt(x,y+1) == NULL))
        {
            map -> setAt(x,y+1,map -> getAt(x,y));
            map -> setAt(x,y,NULL);
            y++;
        }
    }

    else if (path == 2)
    {
        if ((x > 0) && (map -> getAt(x-1,y) == NULL))
        {
            map -> setAt(x-1,y,map -> getAt(x,y));  
            map -> setAt(x,y,NULL);  
            x--;
        }
    }

    else
    {
        if ((x < MAPSIZE - 1) && (map -> getAt(x+1,y) == NULL))
        {
            map -> setAt(x+1,y,map -> getAt(x,y));  
            map -> setAt(x,y,NULL); 
            x++;
        }
    }
}