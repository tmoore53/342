#include <iostream>

#include "creature.h"
#include "maze.h"


void test() {
    Maze M("maze2.txt");
    // cout << m << endl;
    Creature C(4, 4);
    cout << "Path: " << C.solve(M) << endl;
    cout << M << endl;
    cout << C << endl;
}
int main() {
    test();
    cout << "Done!" << std::endl;
    return 0;
}