//
// Author: Tyler A. Moore
//
// Created: October 28, 2021
//
// Creature Class Implimentation
//

#include "creature.h"
#include <iostream>
#include <stack>
using namespace std;

/* Operator overload to print out the starting location of the creature*/
std::ostream &operator<<(std::ostream &Out, const Creature &Creature)
{
    return Out << "Creature started at [" << Creature.Row << "," << Creature.Col << "]";
}

/* Creature constructor
   initializes the location of the creature in the maze and 
   sets the value of being found to false
*/
Creature::Creature(int Row, int Col) : Row(Row), Col(Col), Found(false) {}

//Method returns path in the form of a string
//Remove int Row, int Col
//add and impliment another function
string Creature::solve(Maze &Maze)
{
    mover(&Maze, Row, Col);
    return Path;
}

bool Creature::mover(Maze *maze, int row, int col)
{

    bool ExitFound;
    if (Found && maze->isClear(row, col))
    {
        ExitFound = false;
    }
    else if (maze->isClear(row, col)){
        ExitFound = checkAtExit(*maze, row, col);
    }
    else
    {
        ExitFound = Found;
    }
    maze->markAsVisited(row, col);
    bool CheckN = maze->isClear(row - 1, col);
    bool CheckS = maze->isClear(row + 1, col);
    bool CheckE = maze->isClear(row, col + 1);
    bool CheckW = maze->isClear(row, col - 1);
    while (!ExitFound && (CheckN || CheckS || CheckE || CheckW))
    {

        if (!ExitFound && CheckN)
        {
            ExitFound = mover(maze, row - 1, col);

            if (ExitFound)
            {
                Path += "N";
                maze->markAsPath(row, col);
            }
        }
        if (!ExitFound && CheckS)
        {
            ExitFound = mover(maze, row + 1, col);

            if (ExitFound)
            {
                Path += "S";
                maze->markAsPath(row, col);
            }
        }
        if (!ExitFound && CheckE)
        {
            ExitFound = mover(maze, row, col + 1);
            if (ExitFound)
            {
                Path += "E";
                maze->markAsPath(row, col);
            }
        }
        if (!ExitFound && CheckW)
        {
            ExitFound = mover(maze, row, col - 1);
            if (ExitFound)
            {
                Path += "W";
                maze->markAsPath(row, col);
            }
        }
        CheckN = maze->isClear(row - 1, col);
        CheckS = maze->isClear(row + 1, col);
        CheckE = maze->isClear(row, col + 1);
        CheckW = maze->isClear(row, col - 1);
    }
    if (ExitFound)
    {
        maze->markAsPath(row, col);
        this->Found = true;
    }
    return ExitFound;
}

string Creature::goNorth(Maze &Maze)
{
    if (Maze.isClear(Row - 1, Col))
    {
        Row = Row - 1;
        Maze.markAsVisited(Row, Col);
        return "W";
    }
    cout << "Can't move to the North!" << endl;
    return "";
}

string Creature::goWest(Maze &Maze)
{
    if (Maze.isClear(Row, Col - 1))
    {
        Col = Col - 1;
        Maze.markAsVisited(Row, Col);
        return "W";
    }
    cout << "Can't move to the West!" << endl;

    return "";
}

string Creature::goEast(Maze &Maze)
{
    if (Maze.isClear(Row, Col + 1))
    {
        Col = Col + 1;
        Maze.markAsVisited(Row, Col);
        return "E";
    }
    cout << "Can't move to the East!" << endl;

    return "";
}
string Creature::goSouth(Maze &Maze)
{
    if (Maze.isClear(Row + 1, Col))
    {
        Row = Row + 1;
        Maze.markAsVisited(Row, Col);
        return "S";
    }
    cout << "Can't move to the South!" << endl;

    return "";
}
bool Creature::atExit(const Maze &Maze) const
{

    return checkAtExit(Maze, this->Row, this->Col);
}

bool Creature::checkAtExit(const Maze &Maze, const int &row, const int &col) const
{
    return row == Maze.getExitRow() && col == Maze.getExitColumn();
}

int Creature::getRow() const
{
    return this->Row;
}
int Creature::getCol() const
{
    return this->Col;
}
