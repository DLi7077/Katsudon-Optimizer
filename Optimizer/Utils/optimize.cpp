#include "../Constants/constants.h"
#include "../Game/DamageCalculator.cpp"
#include "../Game/Character/Character.h"
#include "./initializer.cpp"

namespace Optimize {

// https://stackoverflow.com/questions/16111337/declaring-a-priority-queue-in-c-with-a-custom-comparator
Character optimize(Character& character, Enemy& enemy) {
  std::cout << "Flower Artifacts:\t" << Initial::FlowerArtifacts.size() << "\n";
  std::cout << "Feather Artifacts:\t" << Initial::FeatherArtifacts.size() << "\n";
  std::cout << "Sands Artifacts:\t" << Initial::SandsArtifacts.size() << "\n";
  std::cout << "Goblet Artifacts:\t" << Initial::GobletArtifacts.size() << "\n";
  std::cout << "Circlet Artifacts:\t" << Initial::CircletArtifacts.size() << "\n\n";

  std::vector<std::vector<Artifact>> artifactSets = {
      Initial::FlowerArtifacts,
      Initial::FeatherArtifacts,
      Initial::SandsArtifacts,
      Initial::GobletArtifacts,
      Initial::CircletArtifacts,
  };

  // permit to refer to variables in external scope
  // https://stackoverflow.com/questions/26903602/an-enclosing-function-local-variable-cannot-be-referenced-in-a-lambda-body-unles
  auto DamageComparator = [&](Character a, Character b) {
    double damageA = Calculator::damageOutput(a, enemy);
    double damageB = Calculator::damageOutput(b, enemy);
    return damageA > damageB;

    return true;
  };

  const size_t limit = 30;
  std::vector<Character> population = {character};
  std::priority_queue<
      Character,
      std::vector<Character>,
      decltype(DamageComparator)>
      minHeap(DamageComparator);

  for (std::vector<Artifact>& artifactPool : artifactSets) {
    for (Character character : population) {
      for (Artifact& piece : artifactPool) {
        Character curr = character;
        curr.addArtifact(piece);
        minHeap.push(curr);

        if (minHeap.size() > limit) {
          minHeap.pop();
        }
      }
    }

    population.clear();

    while (minHeap.size()) {
      population.push_back(minHeap.top());
      minHeap.pop();
    }
  }

  Character best = population[limit - 1];
  cout << best;

  std::vector<Artifact> artifacts = best.getArtifacts();

  for (Artifact& artifact : artifacts) std::cout << artifact;

  std::cout.precision(8);
  cout << "best damage " << Calculator::damageOutput(best, enemy) << "\n";
  return best;
}
}  // namespace Optimize