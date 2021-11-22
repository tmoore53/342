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
  SkipList skp1(5, 50);
  skp1.add(
      vector<int>{1, 3, 4, 2, 7, -1, 9, 8, 6, 5, 1, 11, 21, 12, 32, 45, 65});
  cout << skp1.containsSNode(75) << endl;

  skp1.add(4);
  skp1.add(3);
  skp1.add(5);
  skp1.add(2);
  skp1.add(3);
  skp1.add(-1);

  cout << skp1 << endl;

  skp1.remove(11);
  skp1.remove(45);
  skp1.remove(3);

  cout << skp1 << endl;

  test1();

  cout << "Done." << endl;
  return 0;
}