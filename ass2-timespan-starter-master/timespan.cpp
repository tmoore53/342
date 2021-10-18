//
// Created by Tyler Moore
// 10/13/21
// Implimentation class for TimeSpan
// represents a duration in hours,
// minutes and seconds
//

#include "timespan.h"
#include <cmath>
#include <sstream>

//
// Output returns padded 0's for the values of hours,
// minutes, and seconds and negative time spans.
//
// Outputs: hh:mm:ss
// or
// Outputs: 0h:0m:0s
//
ostream &operator<<(ostream &out, const TimeSpan &ts)
{
  //
  // Capture absolute value of TimeSpan data values
  // Into String
  //
  string hr(to_string(abs(ts.getHour())));
  string mn(to_string(abs(ts.getMinute())));
  string sec(to_string(abs(ts.getSecond())));

  //
  // Adding padded 0 to positive TimeSpan
  //
  if (ts.isPositive())
  {
    if (ts.getHour() < 10)
    {
      hr = "0" + hr;
    }

    if (ts.getMinute() < 10)
    {
      mn = "0" + mn;
    }
    if (ts.getSecond() < 10)
    {
      sec = "0" + sec;
    }
    return out << hr << ":"
               << mn << ":"
               << sec;
  }

  //
  // Adding padded 0 to negative valued TimeSpan
  // and adding '-' to the front.
  //
  if (ts.isNegative())
  {
    if (ts.getHour() > -10)
    {
      hr = "0" + hr;
    }

    if (ts.getMinute() > -10)
    {
      mn = "0" + mn;
    }
    if (ts.getSecond() > -10)
    {
      sec = "0" + sec;
    }
    return out << "-" << hr << ":"
               << mn << ":"
               << sec;
  }
  return out;
}

//
// Constructor that interprets and captures
// negative Time values or exceeding values of
// minutes and seconds.
//
TimeSpan::TimeSpan(double hour, double minute, double second)
{
  // Initialize counter
  int count(0);

  //
  // If the parameters contain negative numbers they will
  // go through these checks or continue if all positive.
  //
  if (hour <= 0 || minute <= 0 || second <= 0)
  {
    //
    // Rreduces seconds to appropriate value
    //
    while (second < -60)
    {
      second += 60;
      count++;
    }
    minute -= count;
    count = 0;

    //
    // Rreduces minutes to appropriate value
    //
    while (minute < -60)
    {
      minute += 60;
      count++;
    }
    hour -= 0;
    count = 0;

    //
    // These checks and balances will remove any
    // imperfect values to make the time span more
    // readable
    //
    if ((second < 0) && (minute > 0 || hour > 0))
    {
      second = 60 - abs(second);
      minute--;
    }
    if ((minute < 0) && (hour > 0))
    {
      minute = 60 - abs(minute);
      hour--;
    }

    if ((hour < 0) && (minute > 0 && second > 0))
    {
      second = second - 60;
      minute++;
      if ((hour < 0) && (minute > 0))
      {
        minute = minute - 60;
        hour++;
      }
    }
  }

  //
  // Here any decimal values are converted into whole
  // numbers
  //
  minute += 60.0 * decimaltrn(hour);
  second += 60.0 * decimaltrn(minute);
  decimaltrn(second);

  //
  // Here positive values are are handled
  //
  while (second >= 60)
  {
    second -= 60;
    count++;
  }
  minute += count;
  count = 0;
  while (minute >= 60)
  {
    minute -= 60;
    count++;
  }
  hour += count;

  //
  // Once the inputs have gone through the logical checks
  // they are input into the class data values.
  //
  _Hour = hour;
  _Minute = minute;
  _Second = second;
}

// Changes the decimal values to a whole number
// Returns that remainder decimal value to be used to
// convert the other time values
double TimeSpan::decimaltrn(double &num)
{
  double temp(0);
  if (num >= 0)
  {
    temp = (int)(num + .5);
    temp = num - temp;
    num = num - abs(temp);
    return abs(temp);
  }
  if (num < 0)
  {
    temp = (int)(num - .5);
    temp = num + abs(temp);
    num = num + temp;
    return temp;
  }
  return temp;
}

// Hour getter component
int TimeSpan::getHour() const { return (int)_Hour; }

// Minute getter component
int TimeSpan::getMinute() const { return (int)_Minute; }

// Second getter component
int TimeSpan::getSecond() const { return (int)_Second; }

// true if timespan is 0 or larger
bool TimeSpan::isPositive() const
{
  if ((_Hour >= 0) && (_Minute >= 0) && (_Second >= 0))
    return true;
  else
  {
    return false;
  }
}

// Returns true if there are any negative values
bool TimeSpan::isNegative() const
{
  if (_Hour <= 0 || _Minute <= 0 || _Second <= 0)
    return true;
  else
  {
    return false;
  }
}

// add
TimeSpan TimeSpan::operator+(const TimeSpan &ts) const
{
  TimeSpan tsSum(this->getHour() + ts.getHour(),
                 this->getMinute() + ts.getMinute(),
                 this->getSecond() + ts.getSecond());

  return tsSum;
}

// subtract
TimeSpan TimeSpan::operator-(const TimeSpan &ts) const
{
  TimeSpan tsSub(this->getHour() - ts.getHour(),
                 this->getMinute() - ts.getMinute(),
                 this->getSecond() - ts.getSecond());

  return tsSub;
}

// multiply with an integer
TimeSpan TimeSpan::operator*(unsigned int number) const
{
  TimeSpan tsLarge(this->getHour() * number, this->getMinute() * number, this->getSecond() * number);
  return tsLarge;
}

// equality ==
bool TimeSpan::operator==(const TimeSpan &ts) const
{
  if ((ts.getHour() == this->getHour()) && (ts.getMinute() == this->getMinute()) && (ts.getSecond() == this->getSecond()))
    return true;
  else
  {
    return false;
  }
}

// inequality !=
bool TimeSpan::operator!=(const TimeSpan &ts) const
{
  if (ts.getHour() != this->getHour() || ts.getMinute() != this->getMinute() || ts.getSecond() != this->getSecond())
  {
    return true;
  }
  else
  {
    return false;
  }
}

/*Hour setter*/
void TimeSpan::setHour(const double &hr) { this->_Hour = hr; }

/*Minute setter*/
void TimeSpan::setMin(const double &min) { this->_Minute = min; }

/*Second setter*/
void TimeSpan::setSec(const double &sec) { this->_Second = sec; }

/* Append Time Span by adding another Time Span */
TimeSpan &TimeSpan::operator+=(const TimeSpan &ts)
{
  TimeSpan temp(this->getHour() + ts.getHour(),
                this->getMinute() + ts.getMinute(),
                this->getSecond() + ts.getSecond());

  this->setHour(temp.getHour());
  this->setMin(temp.getMinute());
  this->setSec(temp.getSecond());

  return *this;
}

/* Append Time Span by subtracting another Time Span */
TimeSpan &TimeSpan::operator-=(const TimeSpan &ts)
{
  TimeSpan temp(this->getHour() - ts.getHour(),
                this->getMinute() - ts.getMinute(),
                this->getSecond() - ts.getSecond());

  this->setHour(temp.getHour());
  this->setMin(temp.getMinute());
  this->setSec(temp.getSecond());

  return *this;
}

/* Comparing another Time Span - Less Than */
bool TimeSpan::operator<(const TimeSpan &ts)
{
  if (this->getHour() < ts.getHour())
  {
    return true;
  }
  else if (this->getMinute() < ts.getMinute() && this->getHour() <= ts.getHour())
  {
    return true;
  }
  else if (this->getSecond() < ts.getSecond() && this->getMinute() <= ts.getMinute() && this->getHour() <= ts.getHour())
  {
    return true;
  }
  else
  {
    return false;
  }
}

/* Comparing another Time Span - Greater Than */

bool TimeSpan::operator>(const TimeSpan &ts)
{
  if (this->getHour() > ts.getHour())
  {
    return true;
  }
  else if (this->getMinute() > ts.getMinute() && this->getHour() >= ts.getHour())
  {
    return true;
  }
  else if (this->getSecond() > ts.getSecond() && this->getMinute() >= ts.getMinute() && this->getHour() >= ts.getHour())
  {
    return true;
  }
  else
  {
    return false;
  }
}

/* Comparing another Time Span - Less or Equal Than */

bool TimeSpan::operator<=(const TimeSpan &ts)
{
  return (*this < ts || *this == ts);
}

/* Comparing another Time Span - Greater or Equal Than */

bool TimeSpan::operator>=(const TimeSpan &ts)
{
  return (*this > ts || *this == ts);
}
