//
//

#ifndef ASS3_CREATURE_H
#define ASS3_CREATURE_H

#include "maze.h"
#include <ostream>

class Creature
{
public:
  friend ostream &operator<<(ostream &Out, const Creature &Creature);

private:
  int Row;
  int Col;
  string move(const int row, const int col);

public:
  Creature(int Row, int Col);
  string solve(const Maze &Maze);
  bool atExit(const Maze &Maze) const;
  string goNorth(const Maze &Maze);
  string goSouth(const Maze &Maze);
  string goEast(const Maze &Maze);
  string goWest(const Maze &Maze);
};

#endif //ASS3_CREATURE_H
