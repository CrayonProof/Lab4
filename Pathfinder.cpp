#include "Pathfinder.h"
#include <ctime>

using namespace std;

static const int MAZE_SIZE = 5;
int currentMaze[MAZE_SIZE][MAZE_SIZE][MAZE_SIZE];

Pathfinder::Pathfinder()
{
    srand (time(NULL));
}


Pathfinder::~Pathfinder()
{
}

string Pathfinder::toString() const
{
    string mazeString = "";
    
    for (int z = 0; z < MAZE_SIZE; z++)
    {
            for (int y = 0; y < MAZE_SIZE; y++)
        {
                for (int x = 0; x < MAZE_SIZE; x++)
            {
                mazeString = mazeString + to_string(currentMaze[x][y][z]);
                if (x < MAZE_SIZE - 1)
                    mazeString = mazeString + " ";
            }
            if (y < MAZE_SIZE - 1)
                    mazeString = mazeString + "\n";
        }
        if (z < MAZE_SIZE - 1)
                    mazeString = mazeString + "\n";
    }
    return mazeString;
}

void Pathfinder::createRandomMaze()
{
    for (int z = 0; z < MAZE_SIZE; z++)
    {
            for (int y = 0; y < MAZE_SIZE; y++)
        {
                for (int x = 0; x < MAZE_SIZE; x++)
            {
               currentMaze[x][y][z] = rand() % 2;
            }
        }
    }
}

bool Pathfinder::importMaze(string file_name)
{
}

vector<string> Pathfinder::solveMaze()
{
}