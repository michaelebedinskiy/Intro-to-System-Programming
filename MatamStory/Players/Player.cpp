
#include <string>
#include "Player.h"
#include "Job.h"
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <memory>


const string characterNames[] = {
        "Responsible", "RiskTaking"
};



int Player::getMaxHP() const {
   return m_maxHP;
}

string Player::getName() const {
    return m_name;
}

int Player::getLevel() const {
    return m_level;
}

int Player::getForce() const {
    return m_force;
}

int Player::getHealthPoints() const {
    return m_currentHP;
}

int Player::getCoins() const {
    return m_coins;
}

int Player::getCombatPower() const { //not sure about this function
    return m_job_ptr->calculateCombatPower(this->getForce(), this->getLevel());
}

void Player::levelUp() {
    this->m_level++;
}

bool Player::isPlayerKnockedOut() const {
    return this->m_isKnockedOut;
}

void Player::changeHP(int health) {
    int newHealth = static_cast<int>(m_currentHP) + health;
    if (newHealth > 0) {
        m_currentHP = static_cast<unsigned int>(newHealth);
    } else {
        m_currentHP = 0;
    }
}

void Player::changeCoins(int changeInCoins) {
    int newCoins = this->m_coins + changeInCoins;
    if (newCoins > 0) {
        m_coins = newCoins;
    } else {
        m_coins = 0;
    }
}

jobType Player::getJob() const //not sure about this function
{
    return this->m_job_ptr->getJobType();
}


std::string Player::getDescription() const {
    std::stringstream ssDescription;
    ssDescription << this->getName() << ", "
                  << this->m_job_ptr->getJobName() << " with "
                  << this->m_character_ptr->getCharacterName()
                  << " character (level " << m_level << ", force "
                  << this->getForce() << ")";

    std::string description = ssDescription.str();
    return description;
}

characterType Player::getCharacter() const {
    return m_character_ptr->getCharacterType();
}

void Player::knockOut() {
    this->m_isKnockedOut = true;
}

void Player::changeForce(int changeInForce) {
    int newForce = this->m_force + changeInForce;
    if (newForce > 0) {
        m_force = newForce;
    } else {
        m_force = 0;
    }
}

string Player::getAttackRange() const {
    return this->m_job_ptr->getRange();
}

Player::Player(const string &name, std::shared_ptr<Job> job, std::shared_ptr<Character> character) :
        m_name(name),
        m_job_ptr(job),
        m_character_ptr(character),
        m_level(1),
        m_force(5),
        m_maxHP(m_job_ptr->getMaxHP()),
        m_coins(m_job_ptr->getInitialCoins()),
        m_isKnockedOut(false)
{
    if (m_name.length() < 3 || m_name.length() > 15) {
        throw std::invalid_argument("Invalid Players File");
    }
    m_currentHP = m_maxHP;
    m_job_ptr->setMagicStatus(m_job_ptr->getMagicStatus()); // true if magician, otherwise false
}

