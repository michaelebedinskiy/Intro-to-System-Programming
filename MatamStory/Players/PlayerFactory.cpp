
#include "PlayerFactory.h"
#include "sstream"

using std::string;
using std::map;
using std::ostringstream;

const std::map<string, function<shared_ptr<Job>()>> PlayerFactory::jobTypes = {
        {"Warrior",  []() { return std::make_shared<Warrior>(); }},
        {"Archer",   []() { return std::make_shared<Archer>(); }},
        {"Magician", []() { return std::make_shared<Magician>(); }}
};

const map<string, function<shared_ptr<Character>()>> PlayerFactory::characterTypes = {
        {"Responsible", []() { return std::make_shared<Responsible>(); }},
        {"RiskTaking",  []() { return std::make_shared<RiskTaking>(); }}
};


std::shared_ptr<Player> createPlayer(const string &name, const string &jobType, const string &characterType) {
    auto jobIt = PlayerFactory::jobTypes.find(jobType);
    if (jobIt == PlayerFactory::jobTypes.end()) {
        throw std::invalid_argument("Invalid Players File");
    }

    auto characterIt = PlayerFactory::characterTypes.find(characterType);
    if (characterIt == PlayerFactory::characterTypes.end()) {
        throw std::invalid_argument("Invalid Players File");
    }

    // Create a Player with the name, selected job, and selected character
    return std::make_shared<Player>(name, jobIt->second(), characterIt->second());
}
