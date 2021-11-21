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
  // cout << "7 ? " << skp.contains(7) << endl;
  cout << "3 ? " << skp.contains(3) << endl;
  cout << "-100 ? " << skp.contains(-100) << endl;
  cout << "100 ? " << skp.contains(100) << endl;
  bool result = skp.remove(5);
  assert(result);
  result = skp.remove(5);
  assert(!result);
  cout << skp << endl;

  cout << "Test1 Done." << endl;
}

int main() {
  SkipList skp(5, 50);
  //skp.add(
  //     vector<int>{1, 3, 4, 2, 7, -1, 9, 8, 6, 5, 1, 11, 21, 12, 32, 45, 65});
  // // cout << skp.containsSNode(75) << endl;

  // // skp.add(4);
  // // skp.add(3);
  // // skp.add(5);
  // // skp.add(2);
  // // skp.add(3);
  // // skp.add(-1);

  // cout << skp << endl;

  // skp.remove(11);
  // skp.remove(45);
  // skp.remove(3);

  cout << skp << endl;

  test1();

  cout << "Done." << endl;
  return 0;
}