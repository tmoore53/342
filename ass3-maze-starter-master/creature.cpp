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
  return Out << "Creature started at ["  << Creature.Row << ","<< Creature.Col << "]";
}

/* Creature constructor
   initializes the location of the creature in the maze and 
   sets the value of being found to false
*/
Creature::Creature(int Row, int Col) : Row(Row), Col(Col), InitialRow(Row), InitialCol(Col), Found(false) {}

//Method returns path in the form of a string
//Remove int Row, int Col 
//add and impliment another function
string Creature::solve( Maze &Maze)
{
  //return move( Maze, Row, Col);
    mover(Maze, Row, Col);
    return Path;

}

bool Creature::mover(Maze& Maze, int row, int col) {
    bool exitFound;
    bool temp = false;
    if (Found && Maze.isClear(row, col)) {
        exitFound = false;
    }
    else if (Maze.isClear(row, col))
        exitFound = checkAtExit(Maze, row, col);
    else {
        exitFound = Found;
    }
    Maze.markAsVisited(row, col);
    bool checkN = Maze.isClear(row - 1, col);
    bool checkS = Maze.isClear(row + 1, col);
    bool checkE = Maze.isClear(row, col + 1);
    bool checkW = Maze.isClear(row, col - 1);
    while (!exitFound && (checkN || checkS || checkE || checkW)) {

        if (!exitFound && checkN) {
            exitFound = mover(Maze, row - 1, col);

            if (exitFound) {
                Path += "N";
                Maze.markAsPath(row, col);
            }

        }
        if (!exitFound && checkS) {
            exitFound = mover(Maze, row + 1, col);

            if (exitFound) {
                Path += "S";
                Maze.markAsPath(row, col);
            }

        }
        if (!exitFound && checkE) {
            exitFound = mover(Maze, row, col + 1);
            if (exitFound) {
                Path += "E";
                Maze.markAsPath(row, col);
            }
        }
        if (!exitFound && checkW) {
            exitFound = mover(Maze, row, col - 1);
            if (exitFound) {
                Path += "W";
                Maze.markAsPath(row, col);
            }
        }
        checkN = Maze.isClear(row - 1, col);
        checkS = Maze.isClear(row + 1, col);
        checkE = Maze.isClear(row, col + 1);
        checkW = Maze.isClear(row, col - 1);
    }
    if (exitFound) {
        Maze.markAsPath(row, col);
        this->Found = true;
    }
    return exitFound;
}

string Creature::revString(string str) {
    if (str.empty()) {
        return "";
    }
    else {
        return str[str.length() - 1] + revString(str.substr(0, str.length() - 1));
    }
}

string Creature::goNorth(Maze& Maze)
{
    if (Maze.isClear(Row-1, Col)) {
        Row - 1;
        Maze.markAsVisited(Row, Col);
        return "W";

    }
    cout << "Can't move to the North!" << endl;
    return "";
}


string Creature::goWest(Maze& Maze)
{
    if (Maze.isClear(Row, Col - 1)) {
        Col - 1;
        Maze.markAsVisited(Row, Col);
        return "W";

    }
    cout << "Can't move to the West!" << endl;

    return "";
}

string Creature::goEast( Maze &Maze)
{
    if (Maze.isClear(Row, Col + 1)) {
        Col + 1;
        Maze.markAsVisited(Row, Col);
        return "E";

    }
    cout << "Can't move to the East!" << endl;

    return "";
}
string Creature::goSouth(Maze &Maze)
{
    if (Maze.isClear(Row+1, Col)) {
        Row + 1;
        Maze.markAsVisited(Row, Col);
        return "S";

    }
    cout << "Can't move to the South!" << endl;

    return "";
}
bool Creature::atExit(const Maze& Maze) const 
{

    return checkAtExit(Maze, this->Row, this->Col);
}

bool Creature::checkAtExit(const Maze& Maze, const int &row, const int &col) const {
    if (row == Maze.getExitRow() &&
        col == Maze.getExitColumn()) {  
        return true;
    }
    return false;
}

int Creature::getRow() const {
    return this->Row;
}
int Creature::getCol() const {
    return this->Col;
}

bool Creature::canMove(const Maze& Maze) const
{
    if (Maze.isClear(Row, Col + 1) || Maze.isClear(Row + 1, Col) ||
        Maze.isClear(Row, Col - 1) || Maze.isClear(Row - 1, Col))
        return true;
    return false;
}





