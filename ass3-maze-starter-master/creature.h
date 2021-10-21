//
//

#ifndef ASS3_CREATURE_H
#define ASS3_CREATURE_H

#include "maze.h"
#include <ostream>

class Creature {
public:
  friend ostream &operator<<(ostream &Out, const Creature &Creature);

private:
  int Row;
  int Col;

public:
  Creature(int Row, int Col);
  string solve(Maze &Maze);
  bool atExit(const Maze &Maze) const;
  string goNorth(Maze &Maze);
  string goSouth(Maze &Maze);
  string goEast(Maze &Maze);
  string goWest(Maze &Maze);
};

#endif //ASS3_CREATURE_H
