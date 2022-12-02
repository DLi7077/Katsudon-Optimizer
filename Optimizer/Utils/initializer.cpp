#include "../../Katsudon/katsudon.h"
#include "../Game/Character/Character.h"
#include "../Game/Enemy.h"
#include "./generate.h"

namespace Initial {

// general substat preference
vector<string> subStatPreference = {
    FLAT_ATK,
    ATK_PERCENT,
    FLAT_HP,
    HP_PERCENT,
    ELEMENTAL_MASTERY,
    CRIT_DAMAGE,
};

vector<string> mainStatPreference = {
    FLAT_HP,   // Flower
    FLAT_ATK,  // Feather
    ATK_PERCENT,
    HP_PERCENT,
    ELEMENTAL_MASTERY,
    PYRO_DAMAGE_BONUS,
    CRIT_DAMAGE,
};

vector<string> mainStatSandsPref = {
    HP_PERCENT
};

vector<string> mainStatGobletPref = {
    PYRO_DAMAGE_BONUS,
};
vector<string> mainStatCircletPref = {
    CRIT_DAMAGE,
};

vector<string> FlowerMainStats = {FLAT_HP};
vector<string> FeatherMainStats = {FLAT_ATK};
vector<string> SandsMainStats = {ATK_PERCENT, ENERGY_RECHARGE, HP_PERCENT};
vector<string> GobletMainStats = {PYRO_DAMAGE_BONUS, ATK_PERCENT, HP_PERCENT};
vector<string> CircletMainStats = {CRIT_DAMAGE, ATK_PERCENT};

// unordered_map<string, vector<string>> mainStatPreference = {
//     {FLOWER, FlowerMainStats},
//     {FEATHER, FeatherMainStats},
//     {SANDS, SandsMainStats},
//     {GOBLET, GobletMainStats},
//     {CIRCLET, CircletMainStats},
// };

vector<string> FlowerMainPref = Utils::intersection(Constants::artifact_main_stats_[FLOWER], mainStatPreference);
vector<string> FeatherMainPref = Utils::intersection(Constants::artifact_main_stats_[FEATHER], mainStatPreference);
vector<string> SandsMainPref = Utils::intersection(Constants::artifact_main_stats_[SANDS], mainStatSandsPref);
vector<string> GobletMainPref = Utils::intersection(Constants::artifact_main_stats_[GOBLET], mainStatGobletPref);
vector<string> CircletMainPref = Utils::intersection(Constants::artifact_main_stats_[CIRCLET], mainStatCircletPref);

vector<Artifact> FlowerArtifacts = Generate::generateArtifacts(FlowerMainPref, subStatPreference);
vector<Artifact> FeatherArtifacts = Generate::generateArtifacts(FeatherMainPref, subStatPreference);
vector<Artifact> SandsArtifacts = Generate::generateArtifacts(SandsMainPref, subStatPreference);
vector<Artifact> GobletArtifacts = Generate::generateArtifacts(GobletMainPref, subStatPreference);
vector<Artifact> CircletArtifacts = Generate::generateArtifacts(CircletMainPref, subStatPreference);

}  // namespace Initial