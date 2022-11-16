#include "../../Katsudon/katsudon.h"
#include "../Game/Character.h"
#include "../Game/Enemy.h"
#include "./generate.h"

namespace Initial {
// Character characterFromRequest(crow::json::rvalue &requestBody) {
//   Katsudon payload(requestBody);

//   std::string element = payload.getString("element");
//   double base_attack = payload.getDouble("base_attack");        // 843
//   double crit_damage = payload.getDouble("crit_damage");        // 1.382
//   double flat_attack = payload.getDouble("flat_attack");        // 1491
//   double attack_percent = payload.getDouble("attack_percent");  // 1.22

//   double damage_bonus_elemental = payload.getDouble("damage_bonus_elemental");  // 1.126
//   double damage_bonus_all = payload.getDouble("damage_bonus_all");              // 1.00

//   std::string talent_stat = payload.getString("talent_stat");   // "total_attack"
//   double talent_percent = payload.getDouble("talent_percent");  // 9.86

//   Character character(element);
//   character.setStat(BASE_ATK, base_attack);
//   character.setStat(CRIT_DAMAGE, crit_damage);

//   character.setStat(FLAT_ATK, flat_attack);
//   character.setStat(ATK_PERCENT, attack_percent);
//   character.setStat(ELEMENTAL_MASTERY, 567 + 180);
//   character.setStat(MELT_BONUS, .15);

//   character.setTalentDetails(BURST, talent_stat, talent_percent);

//   character.setDamageBonus(HYDRO, damage_bonus_elemental);
//   character.setDamageBonus(ALL, damage_bonus_all);
  
//   return character;
// }

vector<string> subStatPreference = {
    FLAT_ATK,
    ATK_PERCENT,
    ENERGY_RECHARGE,
    ELEMENTAL_MASTERY,
    CRIT_DAMAGE,
};

vector<string> mainStatPreference = {
    FLAT_HP,   // Flower
    FLAT_ATK,  // Feather
    ATK_PERCENT,
    ELEMENTAL_MASTERY,
    CRYO_DAMAGE_BONUS,
    CRIT_DAMAGE,
};

vector<string> mainStatGobletPref = {
    HYDRO_DAMAGE_BONUS,
};
vector<string> mainStatCircletPref = {
    CRIT_DAMAGE,
};

vector<string> FlowerMainStats = {FLAT_HP};
vector<string> FeatherMainStats = {FLAT_ATK};
vector<string> SandsMainStats = {ATK_PERCENT, ELEMENTAL_MASTERY};
vector<string> GobletMainStats = {HYDRO_DAMAGE_BONUS};
vector<string> CircletMainStats = {CRIT_DAMAGE, ATK_PERCENT, ELEMENTAL_MASTERY};

// unordered_map<string, vector<string>> mainStatPreference = {
//     {FLOWER, FlowerMainStats},
//     {FEATHER, FeatherMainStats},
//     {SANDS, SandsMainStats},
//     {GOBLET, GobletMainStats},
//     {CIRCLET, CircletMainStats},
// };

vector<string> FlowerMainPref = Utils::intersection(Constants::artifact_main_stats_[FLOWER], mainStatPreference);
vector<string> FeatherMainPref = Utils::intersection(Constants::artifact_main_stats_[FEATHER], mainStatPreference);
vector<string> SandsMainPref = Utils::intersection(Constants::artifact_main_stats_[SANDS], mainStatPreference);
vector<string> GobletMainPref = Utils::intersection(Constants::artifact_main_stats_[GOBLET], mainStatGobletPref);
vector<string> CircletMainPref = Utils::intersection(Constants::artifact_main_stats_[CIRCLET], mainStatCircletPref);

vector<Artifact> FlowerArtifacts = Generate::generateArtifacts(FlowerMainPref, subStatPreference);
vector<Artifact> FeatherArtifacts = Generate::generateArtifacts(FeatherMainPref, subStatPreference);
vector<Artifact> SandsArtifacts = Generate::generateArtifacts(SandsMainPref, subStatPreference);
vector<Artifact> GobletArtifacts = Generate::generateArtifacts(GobletMainPref, subStatPreference);
vector<Artifact> CircletArtifacts = Generate::generateArtifacts(CircletMainPref, subStatPreference);

}  // namespace Initial