#include <iostream>
#include "Map.h"

using namespace std;

const int deltaRow[] = {-1, 0, 1, 0};
const int deltaCol[] = {0, 1, 0, -1};

Map :: Map()
{    
	for (int i = 0; i < MAPSIZE; ++i)
	{
		for (int j = 0; j < MAPSIZE; ++j)
		{
			grid[i][j] = NULL;
		}
	}
}

Map :: ~Map()
{
    for(int i = 0; i < MAPSIZE; i++)
    {
        for(int j = 0; j < MAPSIZE; j++)
        {
            if(grid[i][j] != NULL)
            {
                delete grid[i][j];
            }
        }
    }
}

void Map :: setAlive(int comAlive)
{
    this -> aliveRobots = comAlive;
}

Robot * Map :: getAt(int x, int y)
{
    if((x >= 0) && (x < MAPSIZE) && (y >= 0) && (y < MAPSIZE))
    {
        return grid[x][y];  
    }
    return NULL;
}

void Map :: setAt(int x, int y, Robot *rob)
{
    if ((x >= 0) && (x < MAPSIZE) && (y >= 0) && (y < MAPSIZE))
    {
        grid[x][y] = rob;
    }
}

void Map :: display()
{
    cout << endl;
    cout << "\033[1;31m.\033[0m" << "-> Empty cell" << endl;
    cout << "\033[1;35mO\033[0m" << "-> Optimusprime" << endl;
    cout << "\033[1;35mR\033[0m" << "-> Robocop" << endl;
    cout << "\033[1;35mM\033[0m" << "-> Roomba" << endl;
    cout << endl;

    for(int j = 0; j < MAPSIZE; j++)
    {
        for(int i = 0; i < MAPSIZE; i++)
        {
            if(grid[i][j] == NULL)
            {
                cout << "\033[1;31m.\033[0m";
            }

            else if(grid[i][j]->getType() == "optimusprime")
            {
                cout << "\033[1;35mO\033[0m";
            }

            else if(grid[i][j]->getType() == "robocop")
            {
                cout << "\033[1;35mR\033[0m";
            }

            else if(grid[i][j]->getType() == "roomba")
            {
                cout << "\033[1;35mM\033[0m";
            }

            else if(grid[i][j]->getType() == "bulldozer")
            {
                cout << "\033[1;35mB\033[0m";
            }

            else
            {
                cout << "\033[1;33mX\033[0m";
            }
        }
        cout << endl;
    }
}

void Map :: simulateOneFight() 
{
    while (aliveRobots > 0)
    {
        // iterate over all cells of the map
        for (int row = 0; row < MAPSIZE; row++) 
        {
            for (int col = 0; col < MAPSIZE; col++) 
            {
                Robot* currRobot = this->getAt(row, col);

                if (currRobot != nullptr && currRobot -> isAlive()) 
                {
                    // try to move the robot in each direction
                    for (int dir = 0; dir < 4; dir++) 
                    {
                        int newRow = row + deltaRow[dir];
                        int newCol = col + deltaCol[dir];

                        // check if the new cell is within the map boundaries
                        if (newRow >= 0 && newRow < MAPSIZE && newCol >= 0 && newCol < MAPSIZE) 
                        {
                            if (this -> getAt(newRow, newCol) != NULL)
                            {
                                Robot* otherRobot = this -> getAt(newRow, newCol);

                                if (otherRobot == nullptr) 
                                {
                                    // move the robot to the new cell if it is empty
                                    this -> setAt(newRow, newCol, currRobot);
                                    this -> setAt(row, col, nullptr);
                                    currRobot -> move();
                                    break;
                                }

                                else if (otherRobot != currRobot) 
                                {
                                    // fight between two robots
                                    while (currRobot -> isAlive() && otherRobot -> isAlive()) 
                                    {
                                        int currRobotDamage = currRobot -> getDamage();
                                        int otherRobotDamage = otherRobot -> getDamage();

                                        currRobot -> takeDamage(otherRobotDamage);
                                        otherRobot -> takeDamage(currRobotDamage);

                                        // print hit message
                                        cout << currRobot->getName() << "(" << currRobot->getHit() << ") hits " << otherRobot->getName() << "(" << otherRobot->getHit() + otherRobotDamage << ") with " << otherRobotDamage << endl;
                                    }

                                    if (currRobot -> isAlive()) 
                                    {
                                        // currRobot wins the fight
                                        this -> setAt(newRow, newCol, currRobot);
                                        this -> setAt(row, col, nullptr);
                                        currRobot -> move();
                                        break;
                                    }

                                    else 
                                    {
                                        // otherRobot wins the fight
                                        this -> setAt(row, col, otherRobot);
                                        this -> setAt(newRow, newCol, nullptr);
                                
                                        // print new hitpoints message
                                        cout << "The new hitpoints of " << otherRobot->getName() << " is " << otherRobot->getHit() << endl;

                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}