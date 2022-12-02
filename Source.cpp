#define CROW_MAIN
#include <sstream>
#include <string>
#include <vector>

#include "./Katsudon/katsudon.h"
#include "./Optimizer/Constants/constants.h"
#include "./Optimizer/Game/Character/Character.h"
#include "./Optimizer/Utils/optimize.cpp"
#include "crow.h"

class ExampleLogHandler : public crow::ILogHandler {
 public:
  void log(std::string /*message*/, crow::LogLevel /*level*/) override {
    //            cerr << "ExampleLogHandler -> " << message;
  }
};

int main() {
  crow::SimpleApp app;

  /**
   * @brief
   * @param element string
   * @param base_attack int
   * @param crit_damage double
   * @param damage_bonus_elemental int
   * @param damage_bonus_all double
   * @param flat_attack int
   * @param flat_attack int
   * @param flat_attack int
   * @param flat_attack int
   * @param flat_attack int
   * @param flat_attack int
   * @param flat_attack int
   *
   */
  CROW_ROUTE(app, "/optimize")
  ([](const crow::request& req) {
    crow::json::wvalue responseBody;
    crow::json::rvalue requestBody = crow::json::load(req.body);

    Katsudon payload(requestBody);

    Character character = payload.constructCharacter();
    // Attributes::BonusStatGain fourEmblem("energy_recharge", OTHER_DAMAGE_BONUS, 0, 0.25, 0.75);
    // character.addBonusStatGain(fourEmblem);

    Enemy enemy = payload.constructEnemy();

    std::vector<Attributes::BonusStatGain> bonusStatGains = payload.constructBonusGain();

    // add emblem /hutao talent bonuses
    for (const Attributes::BonusStatGain& bonusBuff : bonusStatGains) {
      character.addBonusStatGain(bonusBuff);
    }

    Character best = Optimize::optimize(character, enemy);

    responseBody["damage_output"] = Calculator::damageOutput(best, enemy);

    // std::array<std::string, 4> start = {HP_PERCENT, CRIT_DAMAGE, CRIT_RATE, ELEMENTAL_MASTERY};
    // Artifact x(start, FLAT_HP);
    // std::cout<<x;

    // best.addArtifact(x);

    std::cout << "melt multiplier" << Calculator::meltBonus(best, enemy) << "\n";

    responseBody["character_stats"] = best.toJSON();

    return responseBody;
  });

  CROW_ROUTE(app, "/hello/<int>")
  ([](int count) {
    if (count > 100)
      return crow::response(400);
    std::ostringstream os;
    os << count << " bottles of beer!";
    return crow::response(os.str());
  });

  CROW_ROUTE(app, "/add/<int>/<int>")
  ([](const crow::request& /*req*/, crow::response& res, int a, int b) {
    std::ostringstream os;
    os << a + b;
    res.write(os.str());
    res.end();
  });

  // Compile error with message "Handler type is mismatched with URL paramters"
  // CROW_ROUTE(app,"/another/<int>")
  //([](int a, int b){
  // return crow::response(500);
  //});

  // more json example
  CROW_ROUTE(app, "/add_json")
  ([](const crow::request& req) {
    auto x = crow::json::load(req.body);
    if (!x)
      return crow::response(400);
    int sum = x["a"].i() + x["b"].i();
    std::ostringstream os;
    os << sum;
    return crow::response{os.str()};
  });

  CROW_ROUTE(app, "/params")
  ([](const crow::request& req) {
    std::ostringstream os;
    os << "Params: " << req.url_params << "\n\n";
    os << "The key 'foo' was " << (req.url_params.get("foo") == nullptr ? "not " : "") << "found.\n";
    if (req.url_params.get("pew") != nullptr) {
      double countD = boost::lexical_cast<double>(req.url_params.get("pew"));
      os << "The value of 'pew' is " << countD << '\n';
    }
    auto count = req.url_params.get_list("count");
    os << "The key 'count' contains " << count.size() << " value(s).\n";
    for (const auto& countVal : count) {
      os << " - " << countVal << '\n';
    }
    return crow::response{os.str()};
  });

  // ignore all log
  crow::logger::setLogLevel(crow::LogLevel::Debug);
  // crow::logger::setHandler(std::make_shared<ExampleLogHandler>());

  app.port(18080)
      .multithreaded()
      .run();
}