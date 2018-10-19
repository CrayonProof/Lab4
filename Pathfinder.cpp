#include "Pathfinder.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <ctime>

using namespace std;

static const int MAZE_SIZE = 5;
int currentMaze[MAZE_SIZE][MAZE_SIZE][MAZE_SIZE];
vector<string> path;

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
                //cout << "THIS CHARACTER " << x << " " << y << " " << z << ": "<< currentMaze[x][y][z] << endl;
                mazeString = mazeString + to_string(currentMaze[x][y][z]);
                if (x < MAZE_SIZE - 1)
                    mazeString = mazeString + " ";
            }
            if (y < MAZE_SIZE - 1)
                    mazeString = mazeString + "\n";
        }
        if (z < MAZE_SIZE - 1)
                    mazeString = mazeString + "\n\n";
    }
     mazeString = mazeString + "\n";
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
    
    ifstream inputFile;
    inputFile.open(file_name);
    
    char ch;
    char preCh = 'o';
    fstream fin(file_name, fstream::in);
    
    int x = 0;
    int y = 0;
    int z = 0;
    
    //cout << inputFile.rdbuf() << endl;
    while (fin >> noskipws >> ch)
    {
        //cout << ch << endl;
        if (ch == '0')
        {
            currentMaze[x][y][z] = 0;
            x++;
        }
        else if (ch == '1')
        {
            currentMaze[x][y][z] = 1;
            x++;
        }
        else if (ch == ' ')
        {
        }
        else if (ch == '\n')
        {
            if (preCh == '\n')
            {
                z++;
                x=0;
                y=0;
            }
            else
            {
                y++;
                x=0;
            }
        }
        else
        {
            inputFile.close();
            return false;
        }
        preCh = ch;
        //cout << "PRECH: " << "\"" << preCh << "\"" << endl;
        if (x > 5 || y > 5 || z > 5)
        {
            inputFile.close();
            return false;
        }
    }
    inputFile.close();
    return true;
}

bool outOfBounds(int x, int a, int z)
{
    return (x < a || x > z);
}

bool findPath (int x, int y, int z)
{
    path.push_back("(" + to_string(x) + "," + to_string(y) + "," + to_string(z) + ")");
    
    bool xB = outOfBounds(x, 0, MAZE_SIZE);
    bool yB = outOfBounds(y, 0, MAZE_SIZE);
    bool zB = outOfBounds(y, 0, MAZE_SIZE);
    
    if(xB || yB || zB || currentMaze[x][y][z] !=1)
    {
        path.pop_back();
        return false;
    }
    if (x >= MAZE_SIZE && y >= MAZE_SIZE && z >= MAZE_SIZE)
    {
        return true;
    }
    
    currentMaze[x][y][z] = 2;
    
    if(findPath(x + 1, y, z) || findPath(x - 1, y, z) || findPath(x, y + 1, z) || findPath(x, y - 1, z) || findPath(x, y, z + 1) || findPath(x, y, z - 1))
    {
        return true;
    }
    else
    {
        path.pop_back();
        return false;
    }
}

vector<string> Pathfinder::solveMaze()
{
    for (int i = 0; i < path.size(); i++)
    {
        path.erase(path.begin());
    }
    
    findPath(0, 0, 0);
    return path;
    
}