#pragma once
#include <vector>
#include "PathfinderInterface.h"
using namespace std;

class Pathfinder :
    public PathfinderInterface
{
    public:
        Pathfinder();
        ~Pathfinder();
        string toString() const;
        void createRandomMaze();
        bool importMaze(string file_name);
        vector<string> solveMaze();
    private:
        static const int MAZE_SIZE = 5;
        int currentMaze[MAZE_SIZE][MAZE_SIZE][MAZE_SIZE];
};