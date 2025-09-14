
#pragma once

#include "Events/EventFactory.h"
#include "Players/PlayerFactory.h"
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <set>
#include "Players/Player.h"
#include "Events/Event.h"


using std::vector;
using std::set;
using std::unique_ptr;
using std::shared_ptr;

class MatamStory {
private:
    unsigned int m_turnIndex;
    vector<shared_ptr<Player>> m_players;
    vector<unique_ptr<Event>> m_events;
    vector<shared_ptr<Player>> m_leaderboard;
    vector<unique_ptr<Event>>::const_iterator m_currentEvent;


    /**
     * Playes a single turn for a player
     *
     * @param player - the player to play the turn for
     *
     * @return - void
    */
    void playTurn(Player &player);

    /**
     * Plays a single round of the game
     *
     * @return - void
    */
    void playRound();

    /**
     * Checks if the game is over
     *
     * @return - true if the game is over, false otherwise
    */
    bool isGameOver() const;

public:
    /**
     * Constructor of MatamStory class
     *
     * @param eventsStream - events input stream (file)
     * @param playersStream - players input stream (file)
     *
     * @return - MatamStory object with the given events and players
     *
    */
    MatamStory(std::istream &eventsStream, std::istream &playersStream);

    /**
     * Plays the entire game
     *
     * @return - void
    */
    void play();

    void updateLeaderboard();
};

