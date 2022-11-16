#pragma once
#include "../Game/Artifact/artifact.h"
#include "../Constants/pch.h"
#include "./utils.cpp"

using namespace std;

class Generate {
 public:
  /**
   * @brief Generates all possible distributions of rolls into substats
   * Removes duplicates
   * @param substats number of substats
   * @param rolls number of rolls
   * @return vector<vector<int>> all possible distributions
   */
  static vector<vector<int>> generateRolls(int substats, int rolls) {
    vector<vector<int>> result;
    unordered_set<string> duplicates;

    vector<int> base(substats, 0);
    dfs(result, duplicates, base, rolls);

    return result;
  }

  // Generates Combinations of starting N substats - Leetcode Combinations
  template <class Object>
  static vector<vector<Object>> generateStartingStats(vector<Object> &substats, int startingStats, int start = 0) {
    if (start == substats.size() || startingStats <= 0) {
      return {{}};
    }

    vector<vector<Object>> result;
    for (int i = start; i < substats.size() - (startingStats - 1); i++) {
      vector<vector<Object>> subResult = generateStartingStats(substats, startingStats - 1, i + 1);

      for (vector<Object> &sub : subResult) {
        sub.insert(sub.begin(), substats[i]);

        result.push_back(sub);
      }
    }

    return result;
  }

  /**
   * @brief Generates all starting artifact stats given a main stat and possible substats
   * @param mainStat The artifact's main stat
   * @param substats Possible substats
   * @return vector<Artifact> a list of lv.0 artifacts
   */
  static vector<Artifact> generateStartingArtifacts(string mainStat, vector<string> &substats) {
    vector<Artifact> result;

    vector<vector<string>> startingStats = generateStartingStats(substats, SUBSTAT_COUNT);
    for (vector<string> &startingStat : startingStats) {  // possible starting stats using pool
      // convert to std::array
      array<string, SUBSTAT_COUNT> startingSubstats;

      for (int i = 0; i < SUBSTAT_COUNT; i++) {
        startingSubstats[i] = move(startingStat[i]);
      }

      result.push_back(Artifact(startingSubstats, mainStat));
    }

    return result;
  }

  /**
   * @brief Given an artifact, generates all possible outcomes using max rolls
   *
   * @param artifact An artifact with no extra rolls at lv. 0
   * @return vector<Artifact> A list of all possible outcomes
   */
  static vector<Artifact> generateArtifactOutcomes(const Artifact &artifact) {
    static vector<vector<int>> rollDistributions = generateRolls(SUBSTAT_COUNT, ROLL_COUNT);

    vector<Artifact> outcomes(rollDistributions.size(), artifact);

    // add rolls to each copy artifact
    for (size_t roll = 0; roll < rollDistributions.size(); roll++) {
      Artifact &curr = outcomes[roll];

      for (size_t value = 0; value < SUBSTAT_COUNT; value++) {
        curr[value].addRolls(rollDistributions[roll][value]);
      }
    }

    return outcomes;
  }

  static vector<Artifact> generateArtifacts(
      vector<string> &mainStatPool,
      vector<string> &substatPool = Constants::possible_substats_) {
    vector<Artifact> result;

    // consider every possible main stat
    for (string &mainStat : mainStatPool) {
      // generate possible starting stats
      vector<string> possibleSubstats = Utils::omit(substatPool, mainStat);
      vector<Artifact> startingStats = Generate::generateStartingArtifacts(mainStat, possibleSubstats);

      // generate rolls for each base artifact
      for (Artifact &baseArtifact : startingStats) {
        vector<Artifact> artifactRollResults = Generate::generateArtifactOutcomes(baseArtifact);

        // add every possible roll outcome for every artifact to result
        for (Artifact &rollResult : artifactRollResults) {
          result.push_back(move(rollResult));
        }
      }
    }

    return result;
  }

 private:
  static string serialize(vector<int> &list) {
    string result = "";
    for (int i : list) result += to_string(i) + " ";

    return result;
  }

  static void dfs(vector<vector<int>> &result, unordered_set<string> &duplicates, vector<int> &substats, int rolls) {
    if (rolls == 0) {
      result.push_back(substats);
      return;
    }

    for (size_t i = 0; i < substats.size(); i++) {
      substats[i]++;

      string serialized = serialize(substats);
      if (duplicates.count(serialized)) {
        substats[i]--;
        continue;
      }
      duplicates.insert(serialized);

      dfs(result, duplicates, substats, rolls - 1);
      substats[i]--;
    }
  }
};
