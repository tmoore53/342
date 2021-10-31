//
//

#ifndef _HOME_NETID_TMOORE53_ASSIGNMENTS_342_ASS3_MAZE_STARTER_MASTER_CREATURE_H
#define _HOME_NETID_TMOORE53_ASSIGNMENTS_342_ASS3_MAZE_STARTER_MASTER_CREATURE_H

#include "maze.h"
#include <ostream>

class Creature
{
public:
  friend ostream &operator<<(ostream &out, const Creature &Creature);

private:
  int Row;
  int Col;
  bool Found;

  string revString(const string &str);
  bool mover(Maze *maze, int row, int col);
  bool checkAtExit(const Maze &maze, const int &row, const int &col) const;

  string Path;

public:
  Creature(int row, int col);
  string solve(Maze *maze);
  bool atExit(const Maze &maze) const;
  string goNorth(Maze *maze);
  string goSouth(Maze *maze);
  string goEast(Maze *maze);
  string goWest(Maze *maze);

  //Getters
  int getRow() const;
  int getCol() const;
};

#endif //_HOME_NETID_TMOORE53_ASSIGNMENTS_342_ASS3_MAZE_STARTER_MASTER_CREATURE_H
