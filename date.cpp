#include "date.h"

Date::Date(const int& year, const int& month, const int& day) : year_(year), month_(month), day_(day){
}

int Date::GetYear() const {
  return year_;
}
int Date::GetMonth() const {
  return month_;
}
int Date::GetDay() const {
  return day_;
}
string Date::GetFull() const {
  stringstream stream("");
  stream << setw(4) << setfill('0') << year_ <<
      "-" << setw(2) << setfill('0') << month_ <<
      "-" << setw(2) << setfill('0') << day_;
  return stream.str();
}

template <typename It>
int IntFromRange(It beg, It end){
  string s = "";
  for(auto it = beg; it != end; ++it) {
    s += *it;
  }
  istringstream is(s);
  int day;
  is >> day;
  return day;
}

Date ParseDate(istream& is) {
  int year, month, day;
  is >> year;
  is.ignore(1);
  is >> month;
  is.ignore(1);
  is >> day;
  is.ignore(1);
  return Date(year, month, day);
}

ostream& operator<<(ostream& stream, const Date& date){
  stream << setw(4) << setfill('0') << date.GetYear() <<
      "-" << setw(2) << setfill('0') << date.GetMonth() <<
      "-" << setw(2) << setfill('0') << date.GetDay();
  return stream;
}

bool operator<(const Date& d_left, const Date& d_right) {
  return vector<int>{d_left.GetYear(), d_left.GetMonth(), d_left.GetDay()} < vector<int>{d_right.GetYear(), d_right.GetMonth(), d_right.GetDay()};
}

bool operator==(const Date& d_left, const Date& d_right) {
  return vector<int>{d_left.GetYear(), d_left.GetMonth(), d_left.GetDay()} == vector<int>{d_right.GetYear(), d_right.GetMonth(), d_right.GetDay()};
}
