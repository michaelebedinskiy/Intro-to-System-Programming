
#pragma once

#include <string>
#include <memory>

using std::string;

enum jobType {
    ARCHER,
    MAGICIAN,
    WARRIOR
};

class Job {
protected:
    string m_attackRange;
    bool m_isMagical;
public:
    virtual const string getJobName() const = 0;

    virtual const jobType getJobType() const = 0; // no use for generic one

    virtual int getInitialCoins() const;

    virtual int getMaxHP() const;

    virtual string getRange() const = 0;

    virtual bool getMagicStatus() const;

    void setMagicStatus(bool magicStatus);

    virtual int calculateCombatPower(int force, int level) const;

    virtual ~Job() = default;
};

class Warrior : public Job {
public:
    Warrior() = default;

    int calculateCombatPower(int force, int level) const override;

    int getMaxHP() const override;

    const string getJobName() const override;

    const jobType getJobType() const override;

    string getRange() const override;

    ~Warrior() override = default;

};

class Archer : public Job {
public:
    Archer() = default;

    int getInitialCoins() const override;

    const string getJobName() const override;

    const jobType getJobType() const override;

    string getRange() const override;

    ~Archer() override = default;
};

class Magician : public Job {
public:
    Magician() = default;

    const string getJobName() const override;

    const jobType getJobType() const override;

    string getRange() const override;

    bool getMagicStatus() const override;

    ~Magician() override = default;
};