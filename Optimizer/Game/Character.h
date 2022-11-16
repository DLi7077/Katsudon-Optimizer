#pragma once
#include "../Constants/constants.h"
#include "../Constants/pch.h"
#include "./Artifact/artifact.h"
#include "../../Katsudon/katsudon.h"

#define CHARACTER_LEVEL "level"
#define SKILL "Elemental Skill"
#define BURST "Elemental Burst"
#define MELT_BONUS "Melt Bonus"

#define DEFAULT_CHARACTER_LEVEL 90
#define DEFAULT_BASE_ATK 800
#define DEFAULT_BASE_HP 10000
#define DEFAULT_BASE_DEF 200

#define SKILL_SCALING_DEFAULT 3.656
#define BURST_SCALING_DEFAULT 3.026

using TalentScalingStat = std::unordered_map<std::string, std::string>;
using TalentDMGPercent = std::unordered_map<std::string, double>;

class Character {
 private:
  int character_level_ = DEFAULT_CHARACTER_LEVEL;
  std::unordered_map<std::string, double> stats_;
  std::unordered_map<std::string, double> damage_bonus_;
  std::unordered_map<std::string, double> final_stats_;
  std::vector<Artifact> artifact_set_;
  std::string damage_element_;
  TalentScalingStat scaling_stat_;
  TalentDMGPercent damage_scaling_;

  void InitCharacterStats() {
    stats_[BASE_ATK] = DEFAULT_BASE_ATK;
    stats_[BASE_HP] = DEFAULT_BASE_HP;
    stats_[BASE_DEFENSE] = DEFAULT_BASE_DEF;
    stats_[ATK_PERCENT] = 0;
    stats_[HP_PERCENT] = 0;
    stats_[DEF_PERCENT] = 0;
    stats_[FLAT_ATK] = 0;
    stats_[FLAT_HP] = 0;
    stats_[FLAT_DEF] = 0;
    stats_[ELEMENTAL_MASTERY] = 0;
    stats_[ENERGY_RECHARGE] = 1;
    stats_[CRIT_RATE] = .05;
    stats_[CRIT_DAMAGE] = .5;
    stats_[MELT_BONUS] = 0;
  }

  void InitCharacterDamageBonus() {
    damage_bonus_[ANEMO] = 0;
    damage_bonus_[CRYO] = 0;
    damage_bonus_[DENDRO] = 0;
    damage_bonus_[ELECTRO] = 0;
    damage_bonus_[HYDRO] = 0;
    damage_bonus_[PYRO] = 0;
    damage_bonus_[PHYSICAL] = 0;
    damage_bonus_[ALL] = 0;
  }

  void InitTalentDetails() {
    scaling_stat_[SKILL] = "total_attack";
    damage_scaling_[SKILL] = SKILL_SCALING_DEFAULT;
    scaling_stat_[BURST] = "total_attack";
    damage_scaling_[BURST] = BURST_SCALING_DEFAULT;
  }

  void updateStatModel() {
    final_stats_["total_attack"] = stats_[BASE_ATK] * (1 + stats_[ATK_PERCENT]) + stats_[FLAT_ATK];
    final_stats_["total_hp"] = stats_[BASE_HP] * (1 + stats_[HP_PERCENT]) + stats_[FLAT_HP];
    final_stats_["total_defense"] = stats_[BASE_DEFENSE] * (1 + stats_[DEF_PERCENT]) + stats_[FLAT_DEF];
    final_stats_["elemental_mastery"] = stats_[ELEMENTAL_MASTERY];
    final_stats_["energy_recharge"] = stats_[ENERGY_RECHARGE];
    final_stats_["crit_rate"] = stats_[CRIT_RATE];
    final_stats_[MELT_BONUS] = stats_[MELT_BONUS];
    final_stats_["crit_damage"] = stats_[CRIT_DAMAGE];
    final_stats_["damage_bonus_anemo"] = damage_bonus_[ANEMO];
    final_stats_["damage_bonus_cryo"] = damage_bonus_[CRYO];
    final_stats_["damage_bonus_dendro"] = damage_bonus_[DENDRO];
    final_stats_["damage_bonus_electro"] = damage_bonus_[ELECTRO];
    final_stats_["damage_bonus_hydro"] = damage_bonus_[HYDRO];
    final_stats_["damage_bonus_pyro"] = damage_bonus_[PYRO];
    final_stats_["damage_bonus_physical"] = damage_bonus_[PHYSICAL];
    final_stats_["damage_bonus_all"] = damage_bonus_[ALL];
  }

  bool validFinalStat(std::string statLabel) {
    static std::vector<std::string> validStats = {
        "total_attack",
        "total_hp",
        "total_defense",
        "elemental_mastery",
        "energy_recharge",
        "crit_rate",
        "crit_damage",
        "damage_bonus_anemo",
        "damage_bonus_cryo",
        "damage_bonus_dendro",
        "damage_bonus_electro",
        "damage_bonus_hydro",
        "damage_bonus_pyro",
        "damage_bonus_physical",
        MELT_BONUS,
    };
    for (const std::string& stat : validStats) {
      if (statLabel == stat) return true;
    }

    return false;
  }

  bool isDmgBonus(std::string& label) {
    if (label == ANEMO_DAMAGE_BONUS) return true;
    if (label == CRYO_DAMAGE_BONUS) return true;
    if (label == DENDRO_DAMAGE_BONUS) return true;
    if (label == ELECTRO_DAMAGE_BONUS) return true;
    if (label == HYDRO_DAMAGE_BONUS) return true;
    if (label == PYRO_DAMAGE_BONUS) return true;
    if (label == PHYSICAL_DAMAGE_BONUS) return true;

    return false;
  }

  std::string labelCastToElement(std::string& label) {
    if (label == ANEMO_DAMAGE_BONUS) return ANEMO;
    if (label == CRYO_DAMAGE_BONUS) return CRYO;
    if (label == DENDRO_DAMAGE_BONUS) return DENDRO;
    if (label == ELECTRO_DAMAGE_BONUS) return ELECTRO;
    if (label == HYDRO_DAMAGE_BONUS) return HYDRO;
    if (label == PYRO_DAMAGE_BONUS) return PYRO;
    if (label == PHYSICAL_DAMAGE_BONUS) return PHYSICAL;

    return label;
  }

 public:
  // default
  Character() {
    InitCharacterStats();
    InitCharacterDamageBonus();
    InitTalentDetails();
    updateStatModel();
  }

  // one-param
  Character(std::string damage_element) {
    damage_element_ = damage_element;
    InitCharacterStats();
    InitCharacterDamageBonus();
    InitTalentDetails();
    updateStatModel();
  }

  // copy-construct
  Character(const Character& rhs) {
    character_level_ = rhs.character_level_;
    stats_ = rhs.stats_;
    damage_bonus_ = rhs.damage_bonus_;
    final_stats_ = rhs.stats_;
    damage_element_ = rhs.damage_element_;
    scaling_stat_ = rhs.scaling_stat_;
    damage_scaling_ = rhs.damage_scaling_;
    character_level_ = rhs.character_level_;
    artifact_set_ = rhs.artifact_set_;

    updateStatModel();
  }

  // copy assign
  Character operator=(const Character& rhs) {
    Character copy = rhs;
    std::swap(*this, copy);
    updateStatModel();

    return *this;
  }

  // move construct
  Character(Character&& rhs) {
    character_level_ = rhs.character_level_;
    stats_ = rhs.stats_;
    damage_bonus_ = rhs.damage_bonus_;
    final_stats_ = rhs.stats_;
    damage_element_ = rhs.damage_element_;
    scaling_stat_ = rhs.scaling_stat_;
    damage_scaling_ = rhs.damage_scaling_;
    character_level_ = rhs.character_level_;
    artifact_set_ = rhs.artifact_set_;

    updateStatModel();
  }

  // move assign
  Character& operator=(Character&& rhs) {
    std::swap(character_level_, rhs.character_level_);
    std::swap(stats_, rhs.stats_);
    std::swap(damage_bonus_, rhs.damage_bonus_);
    std::swap(final_stats_, rhs.stats_);
    std::swap(damage_element_, rhs.damage_element_);
    std::swap(scaling_stat_, rhs.scaling_stat_);
    std::swap(damage_scaling_, rhs.damage_scaling_);
    std::swap(character_level_, rhs.character_level_);
    std::swap(artifact_set_, rhs.artifact_set_);

    updateStatModel();

    return *this;
  }

  // destructor
  ~Character() = default;

  int getLevel() {
    return character_level_;
  }

  std::string& getDamageElement() {
    return damage_element_;
  }
  // retrieve info from complete built
  double getStat(std::string label) {
    if (!validFinalStat(label)) {
      std::cerr << label << " is not a valid stat\n";
      abort();
    }
    return final_stats_[label];
  }

  double getDMGBonus(std::string label) {
    return damage_bonus_[label];
  }

  // modify base stats
  void setStat(std::string label, double value) {
    stats_[label] = value;
    updateStatModel();
  }
  void setDamageBonus(std::string label, double value) {
    damage_bonus_[label] = value;
    updateStatModel();
  }

  const std::unordered_map<std::string, double>& finalStats() {
    return final_stats_;
  }

  void addArtifact(Artifact& artifact) {
    artifact_set_.push_back(artifact);

    Stat mainStat = artifact.mainStat();
    std::string mainLabel = mainStat.label();
    std::unordered_map<std::string, double>& stats = isDmgBonus(mainLabel) ? damage_bonus_ : stats_;
    mainLabel = labelCastToElement(mainStat.label());

    stats[mainLabel] += mainStat.value();

    for (size_t i = 0; i < artifact.size(); i++) {
      std::string statLabel = artifact[i].label();
      stats_[statLabel] += artifact[i].value();
    }

    updateStatModel();
  }

  void removeArtifact(Artifact& artifact) {
    Stat mainStat = artifact.mainStat();
    std::string mainLabel = mainStat.label();
    std::unordered_map<std::string, double>& stats = isDmgBonus(mainLabel) ? damage_bonus_ : stats_;
    mainLabel = labelCastToElement(mainStat.label());

    stats[mainLabel] -= mainStat.value();

    for (size_t i = 0; i < artifact.size(); i++) {
      std::string statLabel = artifact[i].label();

      stats[statLabel] -= artifact[i].value();
    }

    updateStatModel();
  }

  std::vector<Artifact> getArtifacts() {
    return artifact_set_;
  }

  void setTalentDetails(std::string talent, std::string scaling_stat, double scaling_percent) {
    scaling_stat_[talent] = scaling_stat;
    damage_scaling_[talent] = scaling_percent;
  }

  std::string& getTalentScalingStat(std::string talent) {
    return scaling_stat_[talent];
  }

  double& getTalentScalingDMG(std::string talent) {
    return damage_scaling_[talent];
  }

  friend std::ostream& operator<<(std::ostream& out, Character& rhs) {
    out << "Character Level:\t" << rhs.character_level_ << "\n";
    out << "Base FLAT_ATK:\t\t" << rhs.stats_[BASE_ATK] << "\n";
    out << "ATK\t\t\t" << rhs.final_stats_["total_attack"] << "\n";
    out << "MAX HP:\t\t\t" << rhs.final_stats_["total_hp"] << "\n";
    out << "DEF:\t\t\t" << rhs.final_stats_["total_defense"] << "\n";
    out << "Elemental Mastery:\t" << rhs.final_stats_["elemental_mastery"] << "\n";
    out << "Energy Recharge:\t" << rhs.final_stats_["energy_recharge"] * 100 << "%\n";
    out << "Crit Rate:\t\t" << rhs.final_stats_["crit_rate"] * 100 << "%\n";
    out << "Crit Damage:\t\t" << rhs.final_stats_["crit_damage"] * 100 << "%\n";
    out << "Anemo DMG Bonus:\t" << rhs.final_stats_["damage_bonus_anemo"] * 100 << "%\n";
    out << "Cryo DMG Bonus: \t" << rhs.final_stats_["damage_bonus_cryo"] * 100 << "%\n";
    out << "Dendro DMG Bonus:\t" << rhs.final_stats_["damage_bonus_dendro"] * 100 << "%\n";
    out << "Electro DMG Bonus:\t" << rhs.final_stats_["damage_bonus_electro"] * 100 << "%\n";
    out << "Hydro DMG Bonus:\t" << rhs.final_stats_["damage_bonus_hydro"] * 100 << "%\n";
    out << "Pyro DMG Bonus: \t" << rhs.final_stats_["damage_bonus_pyro"] * 100 << "%\n";
    out << "Physical DMG Bonus:\t" << rhs.final_stats_["damage_bonus_physical"] * 100 << "%\n";
    out << "Other DMG Bonus:\t" << rhs.final_stats_["damage_bonus_all"] * 100 << "%\n";
    out << std::string(30, '-') << "\n";

    return out;
  }

  crow::json::wvalue toJSON() {
    crow::json::wvalue characterJson;

    // character stats
    characterJson["Character Level"] = character_level_;
    characterJson["Base FLAT_ATK"] = stats_[BASE_ATK];
    characterJson["ATK"] = final_stats_["total_attack"];
    characterJson["MAX HP"] = final_stats_["total_hp"];
    characterJson["DEF"] = final_stats_["total_defense"];
    characterJson["Elemental Mastery"] = final_stats_["elemental_mastery"];
    characterJson["Energy Recharge"] = final_stats_["energy_recharge"];
    characterJson["Crit Rate"] = final_stats_["crit_rate"];
    characterJson["Crit Damage"] = final_stats_["crit_damage"];
    characterJson["Anemo DMG Bonus"] = final_stats_["damage_bonus_anemo"];
    characterJson["Cryo DMG Bonus "] = final_stats_["damage_bonus_cryo"];
    characterJson["Dendro DMG Bonus"] = final_stats_["damage_bonus_dendro"];
    characterJson["Electro DMG Bonus"] = final_stats_["damage_bonus_electro"];
    characterJson["Hydro DMG Bonus"] = final_stats_["damage_bonus_hydro"];
    characterJson["Pyro DMG Bonus "] = final_stats_["damage_bonus_pyro"];
    characterJson["Physical DMG Bonus"] = final_stats_["damage_bonus_physical"];
    characterJson["Other DMG Bonus"] = final_stats_["damage_bonus_all"];

    // character artifacts
    std::vector<crow::json::wvalue> artifactsJson;

    for (Artifact& artifact : artifact_set_) {
      artifactsJson.push_back(artifact.toJSON());
    }

    characterJson["artifacts"] = std::move(artifactsJson);

    return characterJson;
  }
};