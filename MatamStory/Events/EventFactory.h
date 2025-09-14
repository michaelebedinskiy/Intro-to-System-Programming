
#pragma once

#include "Events/Event.h"
#include "Events/Monster.h"
#include <vector>
#include <memory>
#include <map>
#include <functional>

using std::shared_ptr;

class EventFactory {
public:
    static const map<string, function<unique_ptr<Encounter>(std::istream &eventsStream)>> encounterTypes;

    static const map<string, function<unique_ptr<Monster>(std::istream &eventsStream)>> monsterTypes;

    static const map<string, function<unique_ptr<SpecialEvent>()>> specialEventTypes;
};

unique_ptr<Pack> createPack(std::istream &eventsStream);

unique_ptr<SpecialEvent> createSpecialEvent(const string &type);






