
#pragma once

#include <vector>
#include <memory>
#include <map>
#include <string>

using std::vector;
using std::string;
using std::unique_ptr;
using std::map;
using std::make_unique;
using std::istringstream;
using std::move;

class Monster {
protected:
    string m_type;
    int m_combatPower;
    int m_loot;
    int m_damage;

    explicit Monster(const string &type) : m_type(type), m_combatPower(0), m_loot(0), m_damage(0) {}

    Monster(const string &type, int combatPower, int loot, int damage) :
            m_type(type), m_combatPower(combatPower), m_loot(loot), m_damage(damage) {}
public:
    Monster() = delete;

    virtual ~Monster() = default;

    int getCombatPower() const {
        return m_combatPower;
    }

    int getLoot() const {
        return m_loot;
    }

    int getDamage() const {
        return m_damage;
    }

    string getType() const {
        return m_type;
    }

};

class Balrog : public Monster {
public:
    Balrog();

    void addCombatPower();
};

class Snail : public Monster {
public:
    Snail();
};

class Slime : public Monster {
public:
    Slime();
};

class Pack : public Monster {
    vector<unique_ptr<Monster>> m_pack;
public:
    int getSize() const {
        return m_pack.size();
    }

    Pack() : Monster("Pack") {}

    void updateCombatPower();

    void initializeCombatPower();

    void addMonster(unique_ptr<Monster> monster);
};





