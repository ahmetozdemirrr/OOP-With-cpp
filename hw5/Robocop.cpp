#include <iostream>
#include "Robocop.h"

class Humanic;

Robocop :: Robocop(string comName) : Humanic(1,30,40,comName)
{}

int Robocop :: getDamage()
{
	int damage = Humanic :: getDamage();

    if (rand() % 100 < 15) 
    {
        damage += 50;
        cout << getName() << " attacks with a powerful hit for " << damage << " points!" << endl;
    } 

    else 
    {
        cout << getName() << " attacks for " << damage << " points!" << endl;
    }
    return damage;
}

string Robocop :: getType()
{
    return "robocop";
}

void Robocop :: takeDamage(int damage) 
{
    hit -= damage;

    if (hit <= 0) 
    {
        cout << name << " is dead. (" << getType() << ")" << endl;
        hit = 0;
    }
}