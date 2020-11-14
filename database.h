#pragma once

#include <iostream>
#include <string>
#include <map>
#include <set>
#include <functional>
#include <utility>
#include <tuple>
#include "date.h"

using namespace std;


ostream &operator<<(ostream &os, const pair<Date, string>& p);
bool operator!=(const string& event, const pair<Date, string>& p);
bool operator!=(const pair<Date, string>& p, const string& event);

class Database {
public:
  void Add(const Date& date, const string& event);
  void Print(ostream& stream) const;
  int RemoveIf(function<bool(const Date& date, const string& even)> pred);
  vector<pair<Date, string>> FindIf(function<bool(const Date& date, const string& even)> pred) const;
  pair<Date, string> Last(const Date& date) const;
private:
  map<Date, set<string>> db;
  map<Date, vector<string>> db_last;
};
