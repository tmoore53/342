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
  bool Found;
  int InitialRow;
  int InitialCol;
  bool canMove(const Maze& Maze) const;
  string revString(string str);
  bool mover(Maze& Maze, int Row, int Col);
  bool checkAtExit(const Maze& Maze,const int &row,const int &col) const;

  string Path;
public:
  Creature(int Row, int Col);
  string solve( Maze &Maze);
  bool atExit(const Maze &Maze) const;
  string goNorth( Maze &Maze);
  string goSouth( Maze &Maze);
  string goEast( Maze &Maze);
  string goWest(Maze &Maze);

  //Getters
  int getRow() const;
  int getCol() const;

};

#endif //ASS3_CREATURE_H
