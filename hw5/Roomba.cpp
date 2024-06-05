#include <iostream>
#include <cstdlib>
#include <string>
#include "Roomba.h"

using namespace std;

class Robot;

Roomba :: Roomba(string comName) : Robot(2,3,10,comName)
{}

int Roomba :: getDamage()
{
	int damage = 0;

    for (int i = 0; i < 2; i++) 
    {
        damage += (rand() % strength) + 1;
        cout << getType() << " attacks for " << damage << " points! " << endl;
    }
    return damage;
}

string Roomba :: getType()
{
    return "roomba";
}

void Roomba :: takeDamage(int damage) 
{
    hit -= damage;

    if (hit <= 0) 
    {
        cout << name << " is dead. (" << getType() << ")" << endl;
        hit = 0;
    }
}