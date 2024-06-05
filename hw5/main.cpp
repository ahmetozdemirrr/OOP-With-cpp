#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Robot.h"
#include "Map.h"

using namespace std;

const int INITIAL_COUNT = 5;

int main(int argc, char const *argv[])
{
	srand(time(NULL));

	Map m;

	m.setAlive(25);

	int optimusCount = 0;
	int robocopCount = 0;
	int roombaCount = 0;
	int bulldozerCount = 0;

	while(optimusCount < INITIAL_COUNT)
	{
        int x = rand() % MAPSIZE;
        int y = rand() % MAPSIZE;
        
        if(m.getAt(x,y) == NULL)
        {
            optimusCount++;

            Robot * a1 = new Robot(x,y,&m);

            for (int i = 0; i < INITIAL_COUNT; ++i)
            {
            	string temp = "optimusprime_" + to_string(i);
            	
            	a1 -> setName(temp);
            	a1 -> setStrength(100);
            	a1 -> setHit(100);
            	a1 -> setType(0);
            }
        }
    }

    while(robocopCount < INITIAL_COUNT)
	{
        int x = rand() % MAPSIZE;
        int y = rand() % MAPSIZE;
        
        if(m.getAt(x,y) == NULL)
        {
            robocopCount++;

            Robot * a1 = new Robot(x,y,&m);

            for (int i = 0; i < INITIAL_COUNT; ++i)
            {
            	string temp = "robocop_" + to_string(i);
            	
            	a1 -> setName(temp);
            	a1 -> setStrength(30);
            	a1 -> setHit(40);
            	a1 -> setType(1);
            }
        }
    }

    while(roombaCount < INITIAL_COUNT)
	{
        int x = rand() % MAPSIZE;
        int y = rand() % MAPSIZE;
        
        if(m.getAt(x,y) == NULL)
        {
            roombaCount++;

            Robot * a1 = new Robot(x,y,&m);

            for (int i = 0; i < INITIAL_COUNT; ++i)
            {
            	string temp = "roomba_" + to_string(i);
            	
            	a1 -> setName(temp);
            	a1 -> setStrength(3);
            	a1 -> setHit(10);
            	a1 -> setType(2);
            }
        }
    }

    while(bulldozerCount < INITIAL_COUNT)
	{
        int x = rand() % MAPSIZE;
        int y = rand() % MAPSIZE;
        
        if(m.getAt(x,y) == NULL)
        {
            bulldozerCount++;

            Robot * a1 = new Robot(x,y,&m);

            for (int i = 0; i < INITIAL_COUNT; ++i)
            {
            	string temp = "bulldozer_" + to_string(i);
            	
            	a1 -> setName(temp);
            	a1 -> setStrength(50);
            	a1 -> setHit(200);
            	a1 -> setType(3);
            }
        }
    }

    m.simulateOneFight();

	return 0;
}