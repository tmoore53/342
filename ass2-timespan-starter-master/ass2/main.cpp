#include <iostream>
// #include "node.h"
#include <cassert>
#include <sstream>

#include "timespan.h"

using namespace std;
using namespace std;

void test1()
{
  TimeSpan ts(1, 20, 30);
  stringstream ss;
  ss << ts;
  cout << ts << endl;
  assert(ss.str() == "01:20:30");

  TimeSpan ts2(4, -20, -90);
  ss.str("");
  ss << ts2;
  assert(ss.str() == "03:38:30");

  TimeSpan ts3(1.5, 30.5, -90);
  ss.str("");
  ss << ts3;
  assert(ss.str() == "01:59:00");

  TimeSpan ts4(0, 0.07, 0);
  ss.str("");
  ss << ts4;
  assert(ss.str() == "00:00:04");
  cout << "test1 complete" << endl;
}

// testing equality, addition, subtraction, multiplication
void test2()
{
  TimeSpan ts(1, 20, 30);
  TimeSpan ts2(1, 20, 30);
  TimeSpan ts3(0, 0, 0);
  assert(ts == ts2);
  assert(!(ts != ts2));
  assert(ts != ts3);
  assert((ts + ts + ts) == (ts2 * 3));
  assert((ts * 5) == (ts2 * 4) + ts2);
  assert((ts * 5) == (ts2 * 6) - ts2);
  assert((ts + ts - ts) == ((ts2 * 2) - ts));
  assert((ts - ts2) == ts3);
  assert((ts3 * 5) == ts3);
  cout << "test2 complete" << endl;
}

void test3()
{
  TimeSpan ts0(0, 0, 0);
  TimeSpan ts1(0, 0, 10);
  TimeSpan ts2 = ts0 - ts1;
  assert(ts1.isPositive() && !ts2.isPositive());
  stringstream ss;
  ss << ts2;
  assert(ss.str() == "-00:00:10");
  cout << "test3 complete" << endl;
}

void test4()
{
  TimeSpan ts(1, 20, 30);
  TimeSpan ts2(1, 20, 30);
  TimeSpan ts3(0, 0, 0);
  TimeSpan ts4(42, 56, 0);

  assert(ts == ts2);
  assert(!(ts != ts2));
  assert(ts != ts3);
  assert((ts += ts) == (ts2 * 2));
  cout << ts << endl;
  assert((ts2) < (ts += ts));
  assert(!((ts2) > (ts += ts)));
  assert(!((ts2) >= (ts += ts)));
  assert(((ts2) >= (ts2)));
  assert((ts2) < (ts += ts));
  assert(((ts2) <= (ts2)));
  cout << "ts " << ts << endl;
  cout << "ts2 " << ts2 << endl;
  assert((ts -= ts2) == (ts4 -= ts2));
  cout << ts << endl;
  cout << "test4 complete" << endl;
}

void test5()
{
  TimeSpan ts0(1, -20, 30);
  TimeSpan ts1(-1, 20, 30);
  TimeSpan ts2(1, 20, -30);

  cout << "ts0 " << ts0 << endl;
  cout << "ts1 " << ts1 << endl;
  cout << "ts2 " << ts2 << endl;
}

int main()
{
  TimeSpan ts0(0, 0, 0);
  TimeSpan ts1(0, 0, 10);
  TimeSpan ts2 = ts0 - ts1;

  cout << "ts0 " << ts0 << endl;
  cout << "ts1 " << ts1 << endl;
  cout << "ts2 " << ts2 << endl;

  test1();
  test2();
  test3();
  test4();
  test5();
  cout << "Done." << std::endl;
  return 0;
}