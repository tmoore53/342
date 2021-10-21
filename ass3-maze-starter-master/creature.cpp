//
//

#include "creature.h"

std::ostream &operator<<(std::ostream &Out, const Creature &Creature) {
  return Out;
}

Creature::Creature(int Row, int Col) : Row(Row), Col(Col) {}

bool Creature::atExit(const Maze &Maze) const {
  return true;
}

string Creature::solve(Maze &Maze) {
  string Path;
  return Path;
}

string Creature::goNorth(Maze &Maze) {
  return "X";
}

string Creature::goWest(Maze &Maze) {
  return "X";
}

string Creature::goEast(Maze &Maze) {
  return "X";
}

string Creature::goSouth(Maze &Maze) {
  return "X";
}
