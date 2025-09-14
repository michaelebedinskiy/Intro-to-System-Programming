
#pragma once

#include "../Players/Player.h"
#include "Monster.h"
#include <vector>
#include <memory>
#include <map>
#include <functional>

using std::vector;
using std::string;
using std::map;
using std::unique_ptr;
using std::make_unique;
using std::istringstream;
using std::move;
using std::function;


class Event {
public:
    virtual ~Event() = default;

    /**
     * Gets the description of the event
     *
     * @return - the description of the event
    */
    virtual string getDescription() const = 0;

    virtual string getEventOutcome(Player &player) = 0;
};

class Encounter : public Event {
    unique_ptr<Monster> m_monster;
public:
    explicit Encounter(unique_ptr<Monster> monster) : m_monster(std::move(monster)) {}

    string getDescription() const override;

    string getEventOutcome(Player &player) override;

};

class SpecialEvent : public Event {
protected:
    string m_type;
public:
    explicit SpecialEvent(const string &type) : m_type(type) {}
};

class SolarEclipse : public SpecialEvent {
public:
    SolarEclipse() : SpecialEvent("SolarEclipse") {}

    string getDescription() const override;

    string getEventOutcome(Player &player) override;
};

class PotionsMerchant : public SpecialEvent {
public:
    PotionsMerchant() : SpecialEvent("PotionsMerchant") {}

    string getDescription() const override;

    string getEventOutcome(Player &player) override;
};
