#include "elma/elma.h"
#include <json/json.h>
#include <set>

using nlohmann::json;
using namespace std::chrono;
using namespace elma;

class BetterStateMachine : public StateMachine {
    public:
    BetterStateMachine(std::string name) : StateMachine(name){
        this->name = name;
    }
    json to_json() const {
        json res = { {"name", name} };
        json tr;
        std::set<string> states;
        for (auto i : _transitions){
            states.insert(i.from().name());
            states.insert(i.to().name());
            json temp;
            temp["from"] = i.from().name();
            temp["to"] = i.to().name();
            temp["when"] = i.event_name();
            tr.push_back(temp);

        }
        res["states"] = states;
        res["transitions"] = tr;

        return res;




    }
    private:
        std::string name;



};