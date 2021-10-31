//
// Author: Tyler A. Moore
//
// Created: October 28, 2021
//
// Creature Class header file
//

#ifndef _HOME_NETID_TMOORE53_ASSIGNMENTS_342_ASS3_MAZE_STARTER_MASTER_CREATURE_H
#define _HOME_NETID_TMOORE53_ASSIGNMENTS_342_ASS3_MAZE_STARTER_MASTER_CREATURE_H

#include "maze.h"
#include <ostream>

class Creature
{
public:
  /*Operator override that prints where the creature startin location is at*/
  friend ostream &operator<<(ostream &out, const Creature &Creature);

private:
  /* Attibutes:
    Row and Col represent the location of the creature.
    Found is marked true when the end of the maze is found.*/
  int Row;
  int Col;
  bool Found;
  string Path;

  /* Pre: Takes in a string, handles a empty string by returning a empty string. */
  /* Post: Returns a string in reverse order that was taken in. */

  string revString(const string &str);

  /* Helper class that recursively checks North, South, East, West
  Pre: Takes the maze that was already passed in and additionally the position the
  creature is at. */

  /* Post: returns a boolean value if the end was found or not. */
  bool mover(Maze *maze, int row, int col);

  /* Helper method to check if the creature is at the exit 

  Pre: Takes in the maze that already has been passed through 
  and additionally the location of the creature. */

  /* Post: returns a boolean value if the creature is at the exit. */

  bool checkAtExit(const Maze &maze, const int &row, const int &col) const;

public:
  /* Creature constructor
   initializes the location of the creature in the maze and 
   sets the value of being found to false.
  */
  Creature(int row, int col);

  /* Pre: Takes in a maze to travers. */
  /* Post: After using it's helper method "mover" this method 
  will return the path it took to get to the end of the maze. */
  string solve(Maze *maze);

  /* Pre: Takes in a maze to compare the creatures location and 
  the end of the maze, uses a helper method "checkAtExit".*/

  /* Post: Returns a boolean value if it at the exit. */
  bool atExit(const Maze &maze) const;

  /* Pre: These methods take in a maze and are used to manually 
  move the creature to traverse the maze.
  
  Must be certain the creature can go in that direction before using method*/
  /* Post: Returns a string value of the direction it took: N, S, E, and W.*/
  string goNorth(Maze *maze);
  string goSouth(Maze *maze);
  string goEast(Maze *maze);
  string goWest(Maze *maze);

  //Getters
  int getRow() const;
  int getCol() const;
};

#endif //_HOME_NETID_TMOORE53_ASSIGNMENTS_342_ASS3_MAZE_STARTER_MASTER_CREATURE_H
