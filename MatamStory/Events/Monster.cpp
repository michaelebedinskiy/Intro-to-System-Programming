
#include "Monster.h"
#include <sstream>

using std::istringstream;
using std::ostringstream;

const int BALROG_POWER_INCREASE = 2;

void Pack::initializeCombatPower() {
    m_combatPower = 0;
    m_loot = 0;
    m_damage = 0;
    for (const unique_ptr<Monster> &monster: m_pack) {
        m_combatPower += monster->getCombatPower();
        m_loot += monster->getLoot();
        m_damage += monster->getDamage();
    }
}

void Pack::updateCombatPower() {
    for (const unique_ptr<Monster> &monster: m_pack) {
        if (monster->getType() == "Pack") {
            dynamic_cast<Pack *>(monster.get())->updateCombatPower();
        }
        if (monster->getType() == "Balrog") {
            dynamic_cast<Balrog *>(monster.get())->addCombatPower();
        }
    }
    initializeCombatPower();
}


void Pack::addMonster(unique_ptr<Monster> monster) {
    if (!monster) {
        throw std::invalid_argument("Monster is null");
    }
    m_pack.push_back(std::move(monster));
}

void Balrog::addCombatPower() {
    m_combatPower += BALROG_POWER_INCREASE;
}

Balrog::Balrog() : Monster("Balrog", 15, 100, 9001) {}

Snail::Snail() : Monster("Snail", 5, 2, 10) {}

Slime::Slime() : Monster("Slime", 12, 5, 25) {}


