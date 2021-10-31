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
using std::string;

/* Operator overload to print out the starting location of the creature*/
std::ostream &operator<<(std::ostream &out, const Creature &creature)
{
    return out << "Creature started at [" << creature.Row << "," << creature.Col << "]";
}

/* Creature constructor
   initializes the location of the creature in the maze and 
   sets the value of being found to false
*/
Creature::Creature(int row, int col) : Row(row), Col(col), Found(false) {}

/* Pre: Takes in a maze to travers */

/* Post: After using it's helper method "mover" this method 
  will return the path it took to get to the end of the maze */
string Creature::solve(Maze *maze)
{
    mover(maze, Row, Col);
    Path = revString(Path);

    return Path;
}

/* Pre: Takes in a maze to travers */

/* Post: After using it's helper method "mover" this method 
  will return the path it took to get to the end of the maze */

string Creature::revString(const string &str)
{
    if (str.length() < 1)
        return str;
    stack<char> St;
    string ReturnStr;
    for (char C : str)
    {
        St.push(C);
    }
    while (!St.empty())
    {
        ReturnStr += St.top();
        St.pop();
    }
    return ReturnStr;
}

// Recursive method that traverses the maze to find the
// end. Once Found it marks the path to get to the end.
//

/* Helper method to check if the creature is at the exit 
  Pre: Takes in the maze that already has been passed through 
  and additionally the location of the creature. */

/* Post: returns a boolean value if the creature is at the exit. */
bool Creature::mover(Maze *maze, int row, int col)
{

    bool ExitFound;
    if (Found && maze->isClear(row, col))
    {
        ExitFound = false;
    }
    else if (maze->isClear(row, col))
    {
        ExitFound = checkAtExit(*maze, row, col);
    }
    else
    {
        ExitFound = Found;
    }
    //Mark location as visited
    maze->markAsVisited(row, col);

    //Check what directions are available to move in
    bool CheckN = maze->isClear(row - 1, col);
    bool CheckS = maze->isClear(row + 1, col);
    bool CheckE = maze->isClear(row, col + 1);
    bool CheckW = maze->isClear(row, col - 1);

    // While the exit is not found and you can go in any direction
    // recursively traverse the maze.
    while (!ExitFound && (CheckN || CheckS || CheckE || CheckW))
    {
        //Check North
        if (!ExitFound && CheckN)
        {
            ExitFound = mover(maze, row - 1, col);

            if (ExitFound)
            {
                Path += "N";
                maze->markAsPath(row, col);
            }
        }
        //Check South
        if (!ExitFound && CheckS)
        {
            ExitFound = mover(maze, row + 1, col);

            if (ExitFound)
            {
                Path += "S";
                maze->markAsPath(row, col);
            }
        }
        //Check East
        if (!ExitFound && CheckE)
        {
            ExitFound = mover(maze, row, col + 1);
            if (ExitFound)
            {
                Path += "E";
                maze->markAsPath(row, col);
            }
        }
        //Check West
        if (!ExitFound && CheckW)
        {
            ExitFound = mover(maze, row, col - 1);
            if (ExitFound)
            {
                Path += "W";
                maze->markAsPath(row, col);
            }
        }

        //Check what directions are available to move in
        CheckN = maze->isClear(row - 1, col);
        CheckS = maze->isClear(row + 1, col);
        CheckE = maze->isClear(row, col + 1);
        CheckW = maze->isClear(row, col - 1);
    }

    // If we found the path mark it as the path taken
    // Change the boolean value to true to backtrack to
    // the starting location of the creature
    if (ExitFound)
    {
        maze->markAsPath(row, col);
        this->Found = true;
    }
    return ExitFound;
}

/* Pre: These methods take in a maze and are used to manually 
  move the creature to traverse the maze.
  
  Must be certain the creature can go in that direction before using method*/
/* Post: Returns a string value of the direction it took: N, S, E, and W.*/
string Creature::goNorth(Maze *maze)
{
    if (maze->isClear(Row - 1, Col))
    {
        Row = Row - 1;
        maze->markAsVisited(Row, Col);
        return "W";
    }
    cout << "Can't move to the North!" << endl;
    return "";
}

string Creature::goWest(Maze *maze)
{
    if (maze->isClear(Row, Col - 1))
    {
        Col = Col - 1;
        maze->markAsVisited(Row, Col);
        return "W";
    }
    cout << "Can't move to the West!" << endl;

    return "";
}

string Creature::goEast(Maze *maze)
{
    if (maze->isClear(Row, Col + 1))
    {
        Col = Col + 1;
        maze->markAsVisited(Row, Col);
        return "E";
    }
    cout << "Can't move to the East!" << endl;

    return "";
}
string Creature::goSouth(Maze *maze)
{
    if (maze->isClear(Row + 1, Col))
    {
        Row = Row + 1;
        maze->markAsVisited(Row, Col);
        return "S";
    }
    cout << "Can't move to the South!" << endl;

    return "";
}

/* Pre: Takes in a maze to compare the creatures location and 
  the end of the maze, uses a helper method "checkAtExit".*/

/* Post: Returns a boolean value if it at the exit. */
bool Creature::atExit(const Maze &maze) const
{

    return checkAtExit(maze, this->Row, this->Col);
}

/* Helper method to check if the creature is at the exit 
  
  Pre: Takes in the maze that already has been passed through 
  and additionally the location of the creature. */

/* Post: returns a boolean value if the creature is at the exit. */
bool Creature::checkAtExit(const Maze &maze, const int &row, const int &col) const
{
    return row == maze.getExitRow() && col == maze.getExitColumn();
}

//Getters
int Creature::getRow() const
{
    return this->Row;
}
int Creature::getCol() const
{
    return this->Col;
}
