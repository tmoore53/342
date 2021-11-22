#include <cassert>
#include <iostream>

#include "skiplist.h"

using namespace std;

void test1() {
  // setting seed for easy testing
  srand(10000);
  SkipList skp(5, 80);
  cout << boolalpha;
  skp.add(3);
  skp.add(5);
  skp.add(vector<int>{1, 7, 9});
  // cannot add existing
  assert(!skp.add(vector<int>{1, 7}));
  cout << skp << endl;
  cout << "7 ? " << skp.contains(7) << endl;
  cout << "3 ? " << skp.contains(3) << endl;
  cout << "-100 ? " << skp.contains(-100) << endl;
  cout << "100 ? " << skp.contains(100) << endl;
  bool result = skp.remove(5);
  assert(result);
  result = skp.remove(5);
  assert(!result);
  cout << skp << endl;

  cout << "Test1 Done.\n" << endl;
}

/**
 * @brief Testing with more numbers
 *
 */
void test2() {
  srand(100000);

  SkipList skp1(5, 50);
  skp1.add(
      vector<int>{1, 3, 4, 2, 7, -1, 9, 8, 6, 5, 1, 11, 21, 12, 32, 45, 65});

  skp1.add(4);
  skp1.add(3);
  skp1.add(5);
  skp1.add(2);
  skp1.add(3);
  skp1.add(-1);

  cout << skp1 << endl;
  cout << "75 ? " << skp1.contains(75) << endl;
  cout << "7 ? " << skp1.contains(7) << endl;

  skp1.remove(11);
  skp1.remove(45);
  skp1.remove(3);
  // skp1.remove(1);
  // skp1.remove(4);
  // skp1.remove(2);
  // skp1.remove(11);
  // skp1.remove(45);
  // skp1.remove(3);

  cout << skp1 << endl;

  cout << "Test2 Done. \n" << endl;
}

void test3() {
  srand(1000000);

  SkipList skp1(5, 50);
  skp1.add(
      vector<int>{1, 3, 4, 2, 7, -1, 9, 8, 6, 5, 1, 11, 21, 12, 32, 45, 65});

  cout << skp1 << endl;
  cout << "75 ? " << skp1.contains(75) << endl;
  cout << "7 ? " << skp1.contains(7) << endl;

  skp1.remove(11);
  skp1.remove(45);
  skp1.remove(3);
  skp1.remove(1);
  skp1.remove(4);
  skp1.remove(2);
  skp1.remove(7);
  skp1.remove(-1);
  skp1.remove(9);
  skp1.remove(8);
  skp1.remove(6);
  skp1.remove(5);
  skp1.remove(21);
  skp1.remove(32);
  skp1.remove(12);
  skp1.remove(65);

  cout << skp1 << endl;

  cout << "Test3 Done. \n" << endl;
}

void test4() {
  srand(1000000);

  SkipList skp1(5, 50);
  skp1.add(
      vector<int>{1, 3, 4, 2, 7, -1, 9, 8, 6, 5, 1, 11, 21, 12, 32, 45, 65});

  skp1.add(-2147483648);
  skp1.add(2147483647);

  cout << skp1 << endl;

  cout << "Test4 Done. \n" << endl;
}

int main() {

  // Executed using bash ./create-output.sh > output.txt 2>&1

  test1();
  test2();
  test3();
  test4();

  cout << "Done." << endl;
  return 0;
}