
#pragma once

#include <string>
#include <memory>
#include "Job.h"
#include "Character.h"

using std::string;

class Player {
    const string m_name;
    std::shared_ptr<Job> m_job_ptr;
    std::shared_ptr<Character> m_character_ptr;
    unsigned int m_level; //1-10
    unsigned int m_force;
    unsigned int m_currentHP; //less or equal to m_maxHP
    const unsigned int m_maxHP;  // TODO: make it const if possible
    unsigned int m_coins;
    bool m_isKnockedOut;



public:
    Player() = delete; //no purpose for empty constructor
    Player(const string &name, std::shared_ptr<Job> job,
           std::shared_ptr<Character> character); //constructor from factory
    // Player(const string& name, const jobType jobName, const characterType character); //matamstory or other function should change strings to enums
    string getDescription() const;

    string getName() const;

    int getLevel() const;

    int getForce() const;

    int getHealthPoints() const;

    int getMaxHP() const;

    int getCoins() const;

    int getCombatPower() const;

    jobType getJob() const;

    characterType getCharacter() const;

    string getAttackRange() const;

    void changeHP(int health); // adds or subtracts HP, gets the delta as variable (positive or negative)
    void changeCoins(int changeInCoins); // adds or subtracts coin amount, gets the delta as variable (positive or negative)
    void changeForce(int changeInForce); // adds or subtracts force, gets the delta as variable (positive or negative)
    void levelUp();

    void knockOut();

    bool isPlayerKnockedOut() const;

    ~Player() = default;
};




