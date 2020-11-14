#include "node.h"

bool EmptyNode::Evaluate(const Date& date, const string& event) const {
  return true;
}

DateComparisonNode::DateComparisonNode(const Comparison& cmp, const Date& date)
                    : date_(date), cmp_(cmp){}

bool DateComparisonNode::Evaluate(const Date& date, const string& event) const {
  if (cmp_ == Comparison::Less) {
    return date < date_;
  }
  else if (cmp_ == Comparison::LessOrEqual) {
    return ((date < date_) || (date_ == date));
  }
  else if (cmp_ == Comparison::Greater) {
    return date_ < date;
  }
  else if (cmp_ == Comparison::GreaterOrEqual) {
    return ((date_ < date) || (date_ == date));
  }
  else if (cmp_ == Comparison::Equal) {
    return date_ == date;
  }
  else if (cmp_ == Comparison::NotEqual) {
    return !(date_ == date);
  }
  return false;
}

EventComparisonNode::EventComparisonNode(const Comparison& cmp, const string& event)
                    : event_(event), cmp_(cmp) {}
bool EventComparisonNode::Evaluate(const Date& date, const string& event) const {
  if (cmp_ == Comparison::Less) {
    return event.compare(event_) == -1;
  }
  else if (cmp_ == Comparison::LessOrEqual) {
    return event.compare(event_) < 1;
  }
  else if (cmp_ == Comparison::Greater) {
    return event.compare(event_) == 1;
  }
  else if (cmp_ == Comparison::GreaterOrEqual) {
    return event.compare(event_) > -1;
  }
  else if (cmp_ == Comparison::Equal) {
    return event.compare(event_) == 0;
  }
  else if (cmp_ == Comparison::NotEqual) {
    return event.compare(event_) != 0;
  }
  return false;
}

LogicalOperationNode::LogicalOperationNode(LogicalOperation logical_operation, shared_ptr<Node> left,
                      shared_ptr<Node> right) : lo_([logical_operation] {
                        if (logical_operation == LogicalOperation::And) {
                          return 2;
                        } else if (logical_operation == LogicalOperation::Or) {
                          return 1;
                        } else {
                          return 0;
                        }
                      }()), left_(left), right_(right) {}

bool LogicalOperationNode::Evaluate(const Date& date, const string& event) const {
  if (lo_ == 2) {
    return left_->Evaluate(date, event) && right_->Evaluate(date, event);
  }
  else if (lo_ == 1) {
    return left_->Evaluate(date, event) || right_->Evaluate(date, event);
  }
  return false;
}
