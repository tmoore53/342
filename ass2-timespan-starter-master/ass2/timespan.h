//
// Created by Tyler Moore
// 10/13/21
// Header class for TimeSpan class
// represents a duration in hours,
// minutes and seconds.
//

#ifndef ASS2_TIMESPAN_H
#define ASS2_TIMESPAN_H

#include <iostream>

using namespace std;

class TimeSpan
{
  friend ostream &operator<<(ostream &out, const TimeSpan &ts);

public:
  // explicit TimeSpan(int Hour = 0, int Minute = 0, int Second = 0);
  TimeSpan(double hour, double minute, double second);

  // add
  TimeSpan operator+(const TimeSpan &ts) const;

  // subtract
  TimeSpan operator-(const TimeSpan &ts) const;

  // check equality
  bool operator==(const TimeSpan &ts) const;

  // check if not equal
  bool operator!=(const TimeSpan &ts) const;

  // multiply timespan by an unsigned number
  TimeSpan operator*(unsigned int number) const;

  // TODO(student)
  // to add operator+=, operator-=, operator<, operator>, operator<=, operator>=
  //Done.

  TimeSpan &operator+=(const TimeSpan &ts);
  TimeSpan &operator-=(const TimeSpan &ts);
  bool operator<(const TimeSpan &ts);
  bool operator>(const TimeSpan &ts);
  bool operator<=(const TimeSpan &ts);
  bool operator>=(const TimeSpan &ts);

  // hour component of timespan
  int getHour() const;

  // minute component of timespan
  int getMinute() const;

  // second component of timespan
  int getSecond() const;

  // true if timespan is 0 or larger
  bool isPositive() const;

  bool isNegative() const;

private:
  double decimaltrn(double &num);

  void setHour(const double &hr);
  void setMin(const double &min);
  void setSec(const double &sec);

  double _Hour;
  double _Minute;
  double _Second;
};

#endif // ASS2_TIMESPAN_H
