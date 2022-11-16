#pragma once

#include "../Optimizer/Constants/pch.h"
#include "crow.h"

// implementation of crow
class Katsudon {
 private:
  crow::json::rvalue request_body_;

 public:
  // construct from crow
  Katsudon(crow::json::rvalue &request_body) {
    request_body_ = std::move(request_body);
  }

  int getInt(std::string &&key) {
    return request_body_[key].i();
  }

  double getDouble(std::string &&key) {
    return request_body_[key].d();
  }

  std::string getString(std::string &&key) {
    return request_body_[key].s();
  }

  // integer list
  std::vector<int> getIntVector(std::string &&key) {
    auto crowList = request_body_[key];
    int list_size = crowList.lo().size();

    std::vector<int> result;
    for (int i = 0; i < list_size; i++) {
      result.push_back(crowList.lo()[i].i());
    }

    return result;
  }

  // double list
  std::vector<double> getDoubleVector(std::string &&key) {
    auto crowList = request_body_[key];
    int list_size = crowList.lo().size();

    std::vector<double> result;
    for (int i = 0; i < list_size; i++) {
      result.push_back(crowList.lo()[i].d());
    }

    return result;
  }

  // string list
  std::vector<std::string> getStringVector(std::string &&key) {
    auto crowList = request_body_[key];
    int list_size = crowList.lo().size();

    std::vector<std::string> result;
    for (int i = 0; i < list_size; i++) {
      result.push_back(crowList.lo()[i].s());
    }

    return result;
  }
};
