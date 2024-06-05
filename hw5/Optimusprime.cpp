#include <iostream>
#include "Optimusprime.h"

class Humanic;

Optimusprime :: Optimusprime (string comName) : Humanic(0,100,100,comName)
{}

int Optimusprime :: getDamage() 
{
    int damage = Humanic :: getDamage();
    int chance = rand() % 100;

    if (chance >= 10 && chance < 15) //Eğer yüzde 10 şans sağnalırsa +50 hasar verilir
    {
        damage += 50;
        cout << getName() << " attacks with a powerful hit for " << damage << " points!" << endl;
    } 

    else if (chance >= 15) //Eğer yüzde 15 şans sağlanırsa x2 hasar verilir
    {
    	damage *= 2;
    }

    else //Öbür şartlarda standart hasar verilir
    {
        cout << getName() << " attacks for " << damage << " points!" << endl;
    }
    return damage;
}

string Optimusprime :: getType()
{
    return "optimusprime";
}

void Optimusprime :: takeDamage(int damage) 
{
    hit -= damage;

    if (hit <= 0) 
    {
        cout << name << " is dead. (" << getType() << ")" << endl;
        hit = 0;
    }
}