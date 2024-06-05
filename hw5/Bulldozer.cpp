#include <iostream>
#include <cstdlib>
#include "Bulldozer.h"

using namespace std;

Bulldozer :: Bulldozer(string comName) : Robot(3,50,200,comName)
{}

int Bulldozer :: getDamage()
{
	int damage;

	damage = (rand() % getStrength()) + 1;

	cout << getType() << " attacks for " << damage << " points! " << endl;

	return damage;
}

string Bulldozer :: getType()
{
	return "bulldozer";
}

void Bulldozer :: takeDamage(int damage) 
{
    hit -= damage;

    if (hit <= 0) 
    {
        cout << name << " is dead. (" << getType() << ")" << endl;
        hit = 0;
    }
}