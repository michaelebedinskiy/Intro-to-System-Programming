
#include "Job.h"

const string jobNames[] = {
        "Archer", "Magician", "Warrior"
};

int Archer::getInitialCoins() const {
    return 20;
}

const string Archer::getJobName() const {
    return "Archer";
}

const jobType Archer::getJobType() const {
    jobType job = ARCHER;
    return job;
}

string Archer::getRange() const {
    return "Ranged";
}

int Job::getInitialCoins() const {
    return 10;
}

int Job::getMaxHP() const {
    return 100;
}

int Job::calculateCombatPower(int force, int level) const {
    return force + level;
}

bool Job::getMagicStatus() const {
    return false;
}

void Job::setMagicStatus(bool magicStatus) {
    m_isMagical = magicStatus;
}

const string Warrior::getJobName() const {
    return jobNames[WARRIOR];
}

int Warrior::calculateCombatPower(int force, int level) const {
    int combatPower = 2 * force + level;
    return combatPower;
}

int Warrior::getMaxHP() const {
    int maxHP = 150;
    return maxHP;
}

const jobType Warrior::getJobType() const {
    jobType job = WARRIOR;
    return job;
}

string Warrior::getRange() const {
    return "Melee";
}

const string Magician::getJobName() const {
    return "Magician";
}

const jobType Magician::getJobType() const {
    jobType job = MAGICIAN;
    return job;
}

string Magician::getRange() const {
    return "Ranged";
}

bool Magician::getMagicStatus() const {
    return true;
}
