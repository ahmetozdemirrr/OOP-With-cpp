#include <iostream>
#include <cstdlib>
#include "Humanic.h"

using namespace std;

class Robot;

Humanic :: Humanic() : Robot()
{}

Humanic :: Humanic(int comType, int comStrength, int comHit, string comName) : Robot(comType,comStrength,comHit,comName)
{}

int Humanic :: getDamage()
{
	int damage;

	damage = (rand() % getStrength()) + 1;

	cout << getType() << " attacks for " << damage << " points! " << endl;

	return damage;
}

void Humanic :: takeDamage(int damage) 
{
    hit -= damage;

    if (hit <= 0) 
    {
        cout << name << " is dead. (" << getType() << ")" << endl;
        hit = 0;
    }
}

string Humanic :: getType() const
{
    switch(type)
    {
    case 0: return "optimusprime";

    case 1: return "robocop";
    }
    return "unknown";
}