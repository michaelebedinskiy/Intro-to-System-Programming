
#pragma once

#include "Players/Player.h"
#include <vector>
#include <memory>
#include <map>
#include <functional>

using std::map;
using std::function;
using std::shared_ptr;

class PlayerFactory {
public:
    static const map<string, function<shared_ptr<Job>()>> jobTypes;

    static const map<string, function<shared_ptr<Character>()>> characterTypes;
};

shared_ptr<Player> createPlayer(const string &name, const string &jobType, const string &characterType);






