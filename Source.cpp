#define CROW_MAIN
#include <sstream>
#include <string>
#include <vector>

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

  CROW_ROUTE(app, "/")
      .name("hello")([] {
        return "Hello World!";
      });

  // simple json response
  CROW_ROUTE(app, "/json")
  ([] {
    crow::json::wvalue responseBody;

    Character Tartaglia(HYDRO);
    Tartaglia.setStat(BASE_ATK, 301 + 542);
    Tartaglia.setStat(CRIT_DAMAGE, 0.5 + 0.882);  // from weapon

    double weaponDMGBonus = 0.4;
    double ascensionDMGBonus = 0.288;
    double dmgBonusBuff = 0.838;
    double bonusAtkPercent = 1.08 + 0.14;

    Tartaglia.setStat(FLAT_ATK, 1491);
    Tartaglia.setStat(ATK_PERCENT, bonusAtkPercent);
    Tartaglia.setStat(ELEMENTAL_MASTERY, 567 + 180);
    Tartaglia.setStat(MELT_BONUS, .15);

    Tartaglia.setTalentDetails(BURST, "total_attack", 9.86);

    Tartaglia.setDamageBonus(HYDRO, ascensionDMGBonus + dmgBonusBuff);
    Tartaglia.setDamageBonus(ALL, weaponDMGBonus + 0.6);

    Enemy enemy(PYRO);
    enemy.setLevel(90);
    enemy.setResistance(HYDRO, 0.3 - 0.4 - 1.7);

    Character best = Optimize::optimize(Tartaglia, enemy);
    responseBody = best.toJSON();
    responseBody["damageOutput"] = Calculator::damageOutput(best, enemy);

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