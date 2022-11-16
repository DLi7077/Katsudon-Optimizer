#pragma once
#include "../../Constants/constants.h"
#include "../../Constants/pch.h"
#include "crow.h"

class Stat {
 public:
  // default
  Stat() {
    label_ = "";
    value_ = 0;
  }

  // one-param
  Stat(std::string label) {
    label_ = label;
    value_ = Constants::substat_max_roll_mapping_[label];
  }

  // copy constructor
  Stat(const Stat& rhs) {
    label_ = rhs.label_;
    value_ = rhs.value_;
  }

  // copy assignment
  Stat& operator=(const Stat& rhs) {
    Stat tempCopy = rhs;
    std::swap(*this, tempCopy);

    return *this;
  }

  // move constructor
  Stat(Stat&& rhs) {
    label_ = rhs.label_;
    value_ = rhs.value_;

    rhs.label_ = "";
    rhs.value_ = 0;
  }

  // move assignment
  Stat& operator=(Stat&& rhs) {
    std::swap(label_, rhs.label_);
    std::swap(value_, rhs.value_);

    return *this;
  }

  ~Stat() = default;

  // simulate roll
  void addRolls(int rolls) {
    double value = Constants::substat_max_roll_mapping_[this->label_];
    value_ += rolls * value;
    return;
  }

  void setMainStat() {
    value_ = Constants::main_stat_max_roll_mapping_[label_];
  }

  std::string& label() {
    return label_;
  }

  double value() {
    return value_;
  }

  friend std::ostream& operator<<(std::ostream& out, const Stat& rhs) {
    std::cout << rhs.label_ << " " << rhs.value_ << "\n";
    return out;
  }

  crow::json::wvalue toJSON() {
    crow::json::wvalue statJson;
    statJson["label"] = label_;
    statJson["value"] = value_;

    return statJson;
  }

 private:
  std::string label_;
  double value_;
};
