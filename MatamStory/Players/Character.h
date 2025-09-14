
#pragma once

#include <string>
#include <memory>

using std::string;

enum characterType {
    RESPONSIBLE, RISKTAKING
};

class Character {
    //Character() = delete; //no purpose for general character
    //string characterName;
public:
    virtual string getCharacterName() const = 0;

    virtual characterType getCharacterType() const = 0; // no use for generic one

    virtual ~Character() = default;
};

class Responsible : public Character {
    string getCharacterName() const override;

    characterType getCharacterType() const override;
};

class RiskTaking : public Character {
    string getCharacterName() const override;

    characterType getCharacterType() const override;
};
