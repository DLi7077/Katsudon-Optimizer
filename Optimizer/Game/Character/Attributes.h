#pragma once
#include "../../Constants/pch.h"

namespace Attributes {
// support for stats like Hu Tao E and 4pc emblem of severed fate
struct BonusStatGain {
  std::string source_stat_;  // stat that bonus is proportional to
  std::string target_stat_;  // target stat to buff
  double source_offset_;     // threshold to gain bonus (4pc emblem = min(0.75, (ER-100) * .25))
  double percent_gain_;      // percentage gain
  double max_gain_;          // maximum gain

  // constructor
  BonusStatGain(
      std::string sourceStat,
      std::string targetStat,
      double sourceOffset,
      double percentGain,
      double maxGain) {
    source_stat_ = sourceStat;
    target_stat_ = targetStat;
    source_offset_ = sourceOffset;
    percent_gain_ = percentGain;
    max_gain_ = maxGain;
  }

  friend std::ostream& operator<<(std::ostream& out, BonusStatGain& rhs) {
    out << "source_stat_\t" << rhs.source_stat_ << "\n";
    out << "target_stat_\t" << rhs.target_stat_ << "\n";
    out << "source_offset_\t" << rhs.source_offset_ << "\n";
    out << "percent_gain_\t" << rhs.percent_gain_ << "\n";
    out << "max_gain_\t" << rhs.max_gain_ << "\n";

    return out;
  }
};

}  // namespace Attributes