#pragma once

#include "../Optimizer/Constants/pch.h"
#include "../Optimizer/Game/Character/Character.h"
#include "../Optimizer/Game/Enemy.h"
#include "crow.h"

// implementation of crow
class Katsudon {
 private:
  crow::json::rvalue request_body_;

 public:
  // construct parser from crow
  Katsudon(crow::json::rvalue request_body) {
    request_body_ = request_body;
  }

  // construct bonus damage gains
  std::vector<Attributes::BonusStatGain> constructBonusGain() {
    std::vector<crow::json::rvalue> bonusGainJsons = vector_json("bonus_stat_gain");

    std::vector<Attributes::BonusStatGain> bonusGains;
    for (const crow::json::rvalue &bonusGainJsons : bonusGainJsons) {
      std::string sourceStat = bonusGainJsons["source_stat"].s();
      std::string targetStat = bonusGainJsons["target_stat"].s();
      double sourceOffset = bonusGainJsons["source_offset"].d();
      double percentGain = bonusGainJsons["percent_gain"].d();
      double maxGain = bonusGainJsons["max_gain"].d();

      Attributes::BonusStatGain bonusGain(sourceStat, targetStat, sourceOffset, percentGain, maxGain);
      bonusGains.push_back(bonusGain);
    }

    return bonusGains;
  }

  // construct Character from request body
  Character constructCharacter() {
    std::string element = getString("element");
    double base_attack = getDouble("base_attack");              // 843
    double crit_damage = getDouble("crit_damage");              // .882
    double flat_attack = getDouble("flat_attack");              // 1491
    double attack_percent = getDouble("attack_percent");        // 1.22
    double elemental_mastery = getDouble("elemental_mastery");  // 747
    double energy_recharge = getDouble("energy_recharge");      // 0

    double damage_bonus_elemental = getDouble("damage_bonus_elemental");  // 1.126
    double damage_bonus_all = getDouble("damage_bonus_all");              // 1.00

    std::string talent_stat = getString("talent_stat");   // "total_attack"
    double talent_percent = getDouble("talent_percent");  // 9.86

    Character character(element);
    character.setStat(BASE_ATK, base_attack);
    character.setStat(CRIT_DAMAGE, DEFAULT_CRIT_DAMAGE + crit_damage);

    character.setStat(FLAT_ATK, flat_attack);
    character.setStat(ATK_PERCENT, attack_percent);
    character.setStat(ELEMENTAL_MASTERY, elemental_mastery);
    character.setStat(ENERGY_RECHARGE, energy_recharge);
    character.setStat(MELT_BONUS, .15);

    character.setTalentDetails(BURST, talent_stat, talent_percent);

    character.setDamageBonus(HYDRO, damage_bonus_elemental);
    character.setDamageBonus(ALL, damage_bonus_all);

    return character;
  }

  Enemy constructEnemy() {
    Enemy enemy;

    std::string character_dmg_element = getString("element");
    int level = getInt("enemy_level");                                                // 90
    std::string affected_element = getString("affected_element");                     // PYRO
    double resistance_to_damage_element = getDouble("resistance_to_damage_element");  // -1.8

    enemy.setAffectedElement(affected_element);
    enemy.setLevel(level);
    enemy.setResistance(character_dmg_element, resistance_to_damage_element);

    return enemy;
  }

  bool hasKey(std::string key) {
    return request_body_.has(key);
  }

  int getInt(std::string key) {
    if (!hasKey(key)) return 0;
    return request_body_[key].i();
  }

  double getDouble(std::string key) {
    if (!hasKey(key)) return 0;
    return request_body_[key].d();
  }

  std::string getString(std::string key) {
    if (!hasKey(key)) return "";
    return request_body_[key].s();
  }

  // integer list
  std::vector<int> getIntVector(std::string key) {
    if (!hasKey(key)) return {};
    auto crowList = request_body_[key];
    int list_size = crowList.lo().size();

    std::vector<int> result;
    for (int i = 0; i < list_size; i++) {
      result.push_back(crowList.lo()[i].i());
    }

    return result;
  }

  // double list
  std::vector<double> getDoubleVector(std::string key) {
    if (!hasKey(key)) return {};

    auto crowList = request_body_[key];
    int list_size = crowList.lo().size();

    std::vector<double> result;
    for (int i = 0; i < list_size; i++) {
      result.push_back(crowList.lo()[i].d());
    }

    return result;
  }

  // string list
  std::vector<std::string> getStringVector(std::string key) {
    if (!hasKey(key)) return {};

    auto crowList = request_body_[key];
    int list_size = crowList.lo().size();

    std::vector<std::string> result;
    for (int i = 0; i < list_size; i++) {
      result.push_back(crowList.lo()[i].s());
    }

    return result;
  }

  // json list
  std::vector<crow::json::rvalue> vector_json(std::string key) {
    if (!hasKey(key)) return {};
    
    auto crowList = request_body_[key];
    int list_size = crowList.lo().size();

    std::vector<crow::json::rvalue> result;
    for (int i = 0; i < list_size; i++) {
      result.push_back(crowList.lo()[i]);
    }

    return result;
  }
};
