
#include "Event.h"
#include "Utilities.h"
#include <sstream>

const int HALF_HP = 50;
const int HEAL_AMOUNT = 10;
const int HEAL_PRICE = 5;
const int SOLAR_ECLIPSE_IMPACT = 1;
const int END_TURN_MELEE_HP_DECREASE = -10;

using std::ostringstream;

string Encounter::getDescription() const {
    ostringstream result;
    if (m_monster->getType() == "Pack") {
        result << "Pack of " << dynamic_cast<const Pack *>(m_monster.get())->getSize() << " members";
    } else {
        result << m_monster->getType();
    }
    result << " (power "
           << m_monster->getCombatPower() << ", loot "
           << m_monster->getLoot() << ", damage "
           << m_monster->getDamage() << ")";
    return result.str();
}

string Encounter::getEventOutcome(Player &player) {
    if (player.getCombatPower() > m_monster->getCombatPower()) {
        player.levelUp();
        player.changeCoins(m_monster->getLoot());
        if (player.getAttackRange() == "Melee") {
            player.changeHP(END_TURN_MELEE_HP_DECREASE);
            if (player.getHealthPoints() == 0) {
                player.knockOut();
            }
        }
        return getEncounterWonMessage(player, m_monster->getLoot());
    }
    player.changeHP(-m_monster->getDamage());
    if (player.getHealthPoints() == 0) {
        player.knockOut();
    }
    if (this->m_monster->getType() == "Balrog") {
        dynamic_cast<Balrog *>(this->m_monster.get())->addCombatPower();
    }
    if (this->m_monster->getType() == "Pack") {
        dynamic_cast<Pack *>(this->m_monster.get())->updateCombatPower();
    }
    return getEncounterLostMessage(player, m_monster->getDamage());
}

string SolarEclipse::getEventOutcome(Player &player) {
    if (player.getJob() == jobType::MAGICIAN) {
        player.changeForce(SOLAR_ECLIPSE_IMPACT);
        return getSolarEclipseMessage(player, SOLAR_ECLIPSE_IMPACT);
    }
    if (player.getForce() == 0) {
        return getSolarEclipseMessage(player, 0);
    }
    player.changeForce(-SOLAR_ECLIPSE_IMPACT);
    return getSolarEclipseMessage(player, -SOLAR_ECLIPSE_IMPACT);
}

string PotionsMerchant::getEventOutcome(Player &player) {
    int potionAmount = 0;
    if (player.getCharacter() == characterType::RESPONSIBLE) {
        while (player.getHealthPoints() < player.getMaxHP() && player.getCoins() >= HEAL_PRICE) {
            player.changeHP(HEAL_AMOUNT);
            player.changeCoins(-HEAL_PRICE);
            potionAmount++;
        }
    }
    if (player.getCharacter() == characterType::RISKTAKING) {
        if (player.getHealthPoints() < HALF_HP && player.getCoins() >= HEAL_PRICE) {
            player.changeHP(HEAL_AMOUNT);
            player.changeCoins(-HEAL_PRICE);
            potionAmount++;
        }
    }
    return getPotionsPurchaseMessage(player,potionAmount);
}

string SolarEclipse::getDescription() const {
    return "SolarEclipse";
}

string PotionsMerchant::getDescription() const {
    return "PotionsMerchant";
}
