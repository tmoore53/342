//
//

#include <fstream>
#include <iostream>
#include "maze.h"
#include <string>

using namespace std;

ostream &operator<<(ostream &Out, const Maze &Maze) {
  for (int Row = 0; Row < Maze.Height; ++Row) {
    for (int Col = 0; Col < Maze.Width; ++Col) {
      Out << Maze.Field[Row][Col];
    }
    Out << endl;
  }
  Out << endl;
  return Out;
}

// For Clion, need the following line in CMakeLists.txt so maze.txt is found
// at the same location as the cpp files
// # need to load data files from current directory as cpp files
// set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
Maze::Maze(const string &FileName) {
  ifstream InFile;
  InFile.open(FileName);
  if (!InFile) {
    cout << "Unable to open file";
    exit(1); // terminate with error
  }
  InFile >> Width >> Height;
  InFile >> ExitRow >> ExitColumn;
  string Str;
  getline(InFile, Str);
  for (int Row = 0; Row < Height; ++Row) {
    for (int Col = 0; Col < Width; ++Col) {
      InFile.get(Field[Row][Col]);
      // cout << Row << ", " << col << ": " << field[Row][col] << endl;
    }
    getline(InFile, Str);
  }

}

int Maze::getExitRow() const {
  return ExitRow;
}

int Maze::getExitColumn() const {
  return ExitColumn;
}

bool Maze::isClear(int Row, int Col) const {
  return Field[Row][Col] == ' ';
}

void Maze::markAsPath(int Row, int Col) {
  Field[Row][Col] = '*';
}

void Maze::markAsVisited(int Row, int Col) {
  Field[Row][Col] = '+';
}
