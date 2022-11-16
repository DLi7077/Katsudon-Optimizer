#pragma once
#include "../Constants/constants.h"
#include "../Constants/pch.h"

#define DEFAULT_ENEMY_LEVEL 93
#define DEFAULT_AFFECTED_ELEMENT PYRO

class Enemy {
 private:
  int enemy_level_;
  std::unordered_map<std::string, double> resistance_percent_;
  std::string affected_element_ = DEFAULT_AFFECTED_ELEMENT;

 public:
  // default
  Enemy() {
    enemy_level_ = DEFAULT_ENEMY_LEVEL;
    resistance_percent_[ANEMO] = .10;
    resistance_percent_[CRYO] = .10;
    resistance_percent_[DENDRO] = .10;
    resistance_percent_[ELECTRO] = .10;
    resistance_percent_[HYDRO] = .10;
    resistance_percent_[PYRO] = .10;
    resistance_percent_[PHYSICAL] = .10;
  }

  // one-param
  Enemy(std::string affectedElement) {
    enemy_level_ = DEFAULT_ENEMY_LEVEL;
    resistance_percent_[ANEMO] = .10;
    resistance_percent_[CRYO] = .10;
    resistance_percent_[DENDRO] = .10;
    resistance_percent_[ELECTRO] = .10;
    resistance_percent_[HYDRO] = .10;
    resistance_percent_[PYRO] = .10;
    resistance_percent_[PHYSICAL] = .10;
    affected_element_ = affectedElement;
  }

  // copy-construct
  Enemy(const Enemy& rhs) {
    enemy_level_ = rhs.enemy_level_;
    resistance_percent_ = rhs.resistance_percent_;
    affected_element_ = rhs.affected_element_;
  }

  // copy-assign
  Enemy operator=(const Enemy& rhs) {
    Enemy copy = rhs;
    std::swap(*this, copy);

    return *this;
  }

  // move-construct
  Enemy(Enemy&& rhs) {
    enemy_level_ = rhs.enemy_level_;
    resistance_percent_ = rhs.resistance_percent_;
    affected_element_ = rhs.affected_element_;
  }

  // move-assign
  Enemy operator=(Enemy&& rhs) {
    std::swap(enemy_level_, rhs.enemy_level_);
    std::swap(resistance_percent_, rhs.resistance_percent_);
    std::swap(affected_element_, rhs.affected_element_);

    return *this;
  }

  ~Enemy() = default;

  int getLevel() {
    return enemy_level_;
  }

  double getResistance(std::string element) {
    if (!(Constants::validateElement(element))) {
      std::cerr << "\"" << element << "\" is not a valid element type.\n";
      abort();
    }
    return resistance_percent_[element];
  }

  std::string getAffectedElement() {
    return affected_element_;
  }

  void setLevel(int level) {
    enemy_level_ = level;
  }
  void setResistance(std::string element, double value) {
    if (!(Constants::validateElement(element))) {
      std::cerr << "\"" << element << "\" is not a valid element type.\n";
      abort();
    }
    resistance_percent_[element] = value;
  }
  void setAffectedElement(std::string element) {
    affected_element_ = element;
  }

  friend std::ostream& operator<<(std::ostream& out, Enemy& rhs) {
    out << "Level:\t" << rhs.enemy_level_ << "\n";
    out << ANEMO << " Res:\t" << rhs.resistance_percent_[ANEMO] << "\n";
    out << CRYO << " Res:\t" << rhs.resistance_percent_[CRYO] << "\n";
    out << DENDRO << " Res:\t" << rhs.resistance_percent_[DENDRO] << "\n";
    out << ELECTRO << " Res:\t" << rhs.resistance_percent_[ELECTRO] << "\n";
    out << HYDRO << " Res:\t" << rhs.resistance_percent_[HYDRO] << "\n";
    out << PYRO << " Res:\t" << rhs.resistance_percent_[PYRO] << "\n";
    out << PHYSICAL << " Res:\t" << rhs.resistance_percent_[PHYSICAL] << "\n";
    out << "Affected:\t" << rhs.affected_element_ << "\n";

    return out;
  }
};
