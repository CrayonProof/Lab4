#include "Pathfinder.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <ctime>

using namespace std;

static const int MAZE_SIZE = 5;
int currentMaze[MAZE_SIZE][MAZE_SIZE][MAZE_SIZE];
int tempMaze[MAZE_SIZE][MAZE_SIZE][MAZE_SIZE];
vector<string> path;

Pathfinder::Pathfinder()
{
    srand (time(NULL));
    
    for (int z = 0; z < MAZE_SIZE; z++)
    {
            for (int y = 0; y < MAZE_SIZE; y++)
        {
                for (int x = 0; x < MAZE_SIZE; x++)
            {
                currentMaze[x][y][z] = 1;
            }
        }
    }
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
    vector<char> charVec;
    
    ifstream inputFile;
    inputFile.open(file_name);
    
    char c;
    char preCh = 'o';
    fstream fin(file_name, fstream::in);
    
    int x = 0;
    int y = 0;
    int z = 0;
    
    int cCount = 0;
    //cout << inputFile.rdbuf() << endl;
    while (fin >> noskipws >> c)
    {
        
        if (c == '1' || c == '0' || c == ' ' || c == '\n')
        {
            charVec.push_back(c);
        }
        else
        {
            cout << "INVALID CHARACTER" << endl;
            return false;
        }
    }
    
    for (char c : charVec)
    {
        if(c == '1')
        {
            cCount++;
        }
        else if( c == '0')
        {
            cCount++;
            if((cCount == 1 || cCount == MAZE_SIZE*MAZE_SIZE*MAZE_SIZE))
            {
                cout << "INVALID BEGIN OR END" << endl;
                return false;
            }
        }
    }
    
    if(cCount != MAZE_SIZE*MAZE_SIZE*MAZE_SIZE)
    {
        cout << "INVALID DIMENSIONS" << endl;
        return false;
    }
    
    inputFile.close();
    
    for (char ch : charVec)
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
            cout << "OUT OF BOUNDS" << endl;
            return false;
        }
    }
    
    return true;
}

bool Pathfinder::findPath (int x, int y, int z)
{
    if ((x >= 0 && x < MAZE_SIZE) && (y >= 0 && y < MAZE_SIZE) && (z >= 0 && z < MAZE_SIZE))
    {
         if(currentMaze[x][y][z] == 1)
        {
            path.push_back("(" + to_string(x) + ", " + to_string(y) + ", " + to_string(z) + ")");
        }
        else
        {
            currentMaze[x][y][z] = 0;
            return false;
        }
    }
    else
    {
        currentMaze[x][y][z] = 0;
        return false;
    }
    if (x >= MAZE_SIZE - 1 && y >= MAZE_SIZE - 1 && z >= MAZE_SIZE - 1)
    {
        return true;
    }
    
    currentMaze[x][y][z] = 2;   
    
    if(findPath(x + 1, y, z) || findPath(x - 1, y, z) || findPath(x, y + 1, z) || findPath(x, y - 1, z) || findPath(x, y, z + 1) || findPath(x, y, z - 1))
    {
        currentMaze[x][y][z] = 1;
        return true;
    }
    else
    {
        currentMaze[x][y][z] = 0;
        path.pop_back();
        return false;
    }
}

vector<string> Pathfinder::solveMaze()
{
    for (int i = 0; i < path.size(); i++)
    {
        path.pop_back();
    }
    
    
    for (int z = 0; z < MAZE_SIZE; z++)
    {
            for (int y = 0; y < MAZE_SIZE; y++)
        {
                for (int x = 0; x < MAZE_SIZE; x++)
            {
               tempMaze[x][y][z] = currentMaze[x][y][z];
            }
        }
    }
    
    
    
    findPath(0, 0, 0);
    
    for (int z = 0; z < MAZE_SIZE; z++)
    {
            for (int y = 0; y < MAZE_SIZE; y++)
        {
                for (int x = 0; x < MAZE_SIZE; x++)
            {
               currentMaze[x][y][z] = tempMaze[x][y][z];
            }
        }
    }
    
    //cout << "path: " << endl;
    for(string s : path)
    {
        //cout << s << endl;
    }
    return path;
    
}