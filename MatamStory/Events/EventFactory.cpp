
#include "EventFactory.h"
#include "sstream"

using std::string;
using std::map;
using std::ostringstream;

const map<string, function<unique_ptr<Encounter>(std::istream &eventsStream)>> EventFactory::encounterTypes = {
        {"Balrog", [](std::istream &eventsStream) { return make_unique<Encounter>(make_unique<Balrog>()); }},
        {"Snail",  [](std::istream &eventsStream) { return make_unique<Encounter>(make_unique<Snail>()); }},
        {"Slime",  [](std::istream &eventsStream) { return make_unique<Encounter>(make_unique<Slime>()); }},
        {"Pack", [](std::istream &eventsStream) { return make_unique<Encounter>(createPack(eventsStream));}}
};

const map<string, function<unique_ptr<Monster>(std::istream &eventsStream)>> EventFactory::monsterTypes = {
        {"Balrog", [](std::istream &eventsStream) { return make_unique<Balrog>(); }},
        {"Snail",  [](std::istream &eventsStream) { return make_unique<Snail>(); }},
        {"Slime",  [](std::istream &eventsStream) { return make_unique<Slime>(); }},
        {"Pack", [](std::istream &eventsStream) { return createPack(eventsStream); }}
};

const map<string, function<unique_ptr<SpecialEvent>()>> EventFactory::specialEventTypes = {
        {"SolarEclipse",    []() { return make_unique<SolarEclipse>(); }},
        {"PotionsMerchant", []() { return make_unique<PotionsMerchant>(); }}
};


unique_ptr<Pack> createPack(std::istream &eventsStream) {
    int size;
    if (!(eventsStream >> size) || size <= 0) {
        throw std::invalid_argument("Invalid Events File");
    }
    string current;
    unique_ptr<Pack> pack = make_unique<Pack>();
    for (int i = 0; i < size; i++) {
        if (!(eventsStream >> current)) {
            throw std::runtime_error("Invalid Events File");
        }
        auto it = EventFactory::monsterTypes.find(current);
        if (it != EventFactory::monsterTypes.end()) {
            unique_ptr<Monster> monster = it->second(eventsStream);
            if(!monster) {
                throw std::runtime_error("Failed to create encounter");
            }
            pack->addMonster(std::move(monster));
        } else {
            throw std::invalid_argument("Invalid Events File");
        }
    }
    if (pack->getSize() !=  size) {
        throw std::runtime_error("Invalid Events File");
    }
    pack->initializeCombatPower();
    return pack;
}

unique_ptr<SpecialEvent> createSpecialEvent(const string &type) {
    auto it = EventFactory::specialEventTypes.find(type);
    if (it != EventFactory::specialEventTypes.end()) {
        return it->second();
    } else {
        throw std::invalid_argument("Invalid Events File");
    }
}
