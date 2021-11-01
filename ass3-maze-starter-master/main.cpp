//
// Author: Tyler A. Moore
//
// Created: October 28, 2021
//
// Creature Main method to demonstrate how to
// recursively ttraverse a maze and return the
// path taken
//
#include <iostream>
#include "creature.h"
#include "maze.h"

void test()
{
    Maze M("maze.txt");
    Maze M2("maze2.txt");
    Maze M3("maze3.txt");
    Maze M4("maze4.txt");

    Creature C(4, 4);
    Creature C2(4, 10);
    Creature C3(4, 4);
    Creature C4(14, 38);

    /*Modified to fix google syntax errors
 Added & next to each Map */
    cout << "Path: " << C.solve(&M) << endl;
    cout << M << endl;

    cout << "Path: " << C2.solve(&M2) << endl;
    cout << M2 << endl;

    cout << "Path: " << C3.solve(&M3) << endl;
    cout << M3 << endl;

    cout << "Path: " << C4.solve(&M4) << endl;
    cout << M4 << endl;

    cout << C << endl;
    cout << C2 << endl;
    cout << C3 << endl;
    cout << C4 << endl;
}
int main()
{
    test();
    cout << "Done!" << std::endl;
    return 0;
}