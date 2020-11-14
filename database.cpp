#include "database.h"
#include <string>

ostream &operator<<(ostream &os, const pair<Date, string> &p) {
  os << p.first << " " << p.second;
  return os;
}

bool operator!=(const string& event, const pair<Date, string> &p) {
  string s = p.first.GetFull();
  stringstream stream("");
  stream << s << " " << p.second;
  string ss = stream.str();
  return (ss).compare(event) != 0;
}

bool operator!=(const pair<Date, string>& p, const string& event) {
  string s = p.first.GetFull();
  stringstream stream("");
  stream << s << " " << p.second;
  string ss = stream.str();
  return (ss).compare(event) != 0;
}

void Database::Add(const Date& date, const string& event) {
  auto it = db[date].insert(event);
  if (it.second) {
    db_last[date].push_back(event);
  }
}

void Database::Print(ostream& stream) const {
  for(const auto& date : db_last){
    for(const auto& event : date.second) {
      stream << date.first << " " << event << endl;
    }
  }
}

int Database::RemoveIf(function<bool(const Date& date, const string& event)> pred) {
  int num_removes = 0;
  vector<Date> erases;
  for (auto& [date, events]: db_last) {
    auto stable = stable_partition(begin(events), end(events), [pred, date = date](const string& event) {
      return !pred(date, event);
    });
    for (auto j = stable; j != end(events); ++j) {
      num_removes++;
      db[date].erase(*j);
    }
    events.erase(stable, end(events));
    if (events.empty()) {
        erases.push_back(date);
    }
  }
  for (const auto &date: erases) {
    auto it = db.erase(date);
    if (it) {
        db_last.erase(date);
    }

}
  return num_removes;
}

vector<pair<Date, string>> Database::FindIf(function<bool(const Date& date, const string& even)> pred) const{
  vector<pair<Date, string>> output;
  for (const auto& [key, vals]: db_last) {
    for (const auto val: vals) {
      if (pred(key, val) && db.at(key).count(val)) {
        output.emplace_back(key, val);
      }
    }
  }
  return output;
}


pair<Date, string> Database::Last(const Date& date) const {
  auto it = db_last.upper_bound(date);
  if (it == db_last.begin()) {
    throw invalid_argument("");
  }
  it = prev(it);
  if (it->second.empty()) {
    throw invalid_argument("");
  }

  return make_pair(it->first, it->second.back());
}
