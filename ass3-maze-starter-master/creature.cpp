//
//

#include "creature.h"

std::ostream &operator<<(std::ostream &Out, const Creature &Creature)
{
  return Out << "Creature is at [" << this->Row << "," << this->Col << "]";
}

Creature::Creature(int Row, int Col) : Row(Row), Col(Col) {}

bool Creature::atExit(const Maze &Maze) const
{
  return true;
}

//Method returns path in the form of a string
string Creature::solve(const Maze &Maze)
{
  string Path = "";
  if (Row == Maze.getExitRow() && Col == Maze.getExitColumn())
    return Path;
  else
  {
    return Path;
  }
}

string Creature::move(const int row, const int col)
{
  string path = "";

  return path;
}

string Creature::goNorth(const Maze &Maze)
{
  if (Maze.isClear(this->Row, this->Col + 1))
    return "N";
  else
  {
    return "";
  }
}

string Creature::goWest(const Maze &Maze)
{
  if (Maze.isClear(this->Row, this->Col + 1))
    return "W";
  else
  {
    return "";
  }
}

string Creature::goEast(const Maze &Maze)
{
  if (Maze.isClear(this->Row, this->Col + 1))
    return "E";
  else
  {
    return "";
  }
}

string Creature::goSouth(const Maze &Maze)
{
  if (Maze.isClear(this->Row, this->Col + 1))
    return "s";
  else
  {
    return "";
  }
}
