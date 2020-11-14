#pragma once
#include "date.h"

using namespace std;

enum class LogicalOperation {
  Or,
  And,
};

enum class Comparison {
  Less,
  LessOrEqual,
  Greater,
  GreaterOrEqual,
  Equal,
  NotEqual,
};

class Node {
public:
  virtual bool Evaluate(const Date& date, const string& event) const = 0;
};

class EmptyNode : public Node{
public:
  bool Evaluate(const Date& date, const string& event) const override;
};

class DateComparisonNode : public Node {
public:
  DateComparisonNode(const Comparison& cmp, const Date& date);
  bool Evaluate(const Date& date, const string& event) const override;
private:
  const Date date_;
  const Comparison cmp_;
};

class EventComparisonNode : public Node {
public:
  EventComparisonNode(const Comparison& cmp, const string& event);
  bool Evaluate(const Date& date, const string& event) const override;
private:
  const string event_;
  const Comparison cmp_;
};

class LogicalOperationNode : public Node{
public:
  LogicalOperationNode(LogicalOperation logical_operation, shared_ptr<Node> left, shared_ptr<Node> right);
  bool Evaluate(const Date& date, const string& event) const override;
private:
  const uint8_t lo_;
  const shared_ptr<const Node> left_, right_;
};
