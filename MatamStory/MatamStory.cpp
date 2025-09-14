
#include "MatamStory.h"
#include "Utilities.h"
#include <sstream>
#include <algorithm>


using std::getline;
using std::string;
using std::make_unique;
using std::istringstream;
using std::ostringstream;

MatamStory::MatamStory(std::istream &eventsStream, std::istream &playersStream) {
    string event;
    while (eventsStream >> event) {
        auto it = EventFactory::encounterTypes.find(event);
        if (it != EventFactory::encounterTypes.end()) {
            m_events.push_back(it->second(eventsStream));
        } else {
            auto it = EventFactory::specialEventTypes.find(event);
            if (it != EventFactory::specialEventTypes.end()) {
                m_events.push_back(createSpecialEvent(event));
            } else {
                throw std::invalid_argument("Invalid Events File");
            }
        }
    }
    if (m_events.size() < 2) {
        throw std::invalid_argument("Invalid Events File");
    }
    m_currentEvent = m_events.cbegin();
    string name, job, character;
    while (playersStream >> name) {
        if (!(playersStream >> job) || !(playersStream >> character)) {
            throw std::invalid_argument("Invalid Players File");
        }
        m_players.push_back(createPlayer(name, job, character));
    }
    if (m_players.size() < 2 || m_players.size() > 6) {
        throw std::invalid_argument("Invalid Players File");
    }
    for (const shared_ptr<Player> &player : m_players) {
        m_leaderboard.push_back(player);
    }
    this->m_turnIndex = 1;
}

void MatamStory::playTurn(Player &player) {
    /**
     * Steps to implement (there may be more, depending on your design):
     * 1. Get the next event from the events list
     * 2. Print the turn details with "printTurnDetails"
     * 3. Play the event
     * 4. Print the turn outcome with "printTurnOutcome"
    */
    if (m_currentEvent == m_events.cend()) {
        m_currentEvent = m_events.cbegin();
    }
    printTurnDetails(m_turnIndex, player, *(*m_currentEvent));
    string outcome = (*m_currentEvent)->getEventOutcome(player);
    printTurnOutcome(outcome);

    m_currentEvent++;
    m_turnIndex++;
}

void MatamStory::playRound() {

    printRoundStart();
    /*===== TODO: Play a turn for each player =====*/
    for (const shared_ptr<Player> &player: m_players) {
        if (!(player->isPlayerKnockedOut())) {
            playTurn(*player);
        }
    }
    /*=============================================*/

    printRoundEnd();

    printLeaderBoardMessage();

    /*===== TODO: Print leaderboard entry for each player using "printLeaderBoardEntry" =====*/
    updateLeaderboard();
    int i = 1;
    for (const shared_ptr<Player> &player: m_leaderboard) {
        printLeaderBoardEntry(i, *player);
        i++;
    }
    /*=======================================================================================*/

    printBarrier();
}

bool MatamStory::isGameOver() const {
    /*===== TODO: Implement the game over condition =====*/
    shared_ptr<Player> best = *m_leaderboard.begin();
    if (best->getLevel() >= 10) {
        return true;
    }
    bool flag = true;
    for (const shared_ptr<Player> &player: m_leaderboard) {
        if (player->getHealthPoints() > 0) {
            flag = false;
        }
    }
    return flag;
    /*===================================================*/
}

void MatamStory::play() {
    printStartMessage();
    /*===== TODO: Print start message entry for each player using "printStartPlayerEntry" =====*/
    unsigned int i = 0;
    for (const shared_ptr<Player> &player: m_players) {
        printStartPlayerEntry(++i, *player);
    }
    /*=========================================================================================*/
    printBarrier();

    while (!isGameOver()) {
        playRound();
    }

    printGameOver();
    /*===== TODO: Print either a "winner" message or "no winner" message =====*/
    shared_ptr<Player> best = *m_leaderboard.begin();
    if (best->getLevel() >= 10) {
        printWinner(*best);
    } else {
        printNoWinners();
    }
    /*========================================================================*/
}

void MatamStory::updateLeaderboard() {
    std::sort(m_leaderboard.begin(), m_leaderboard.end(), [](const std::shared_ptr<Player>& p1, const std::shared_ptr<Player>& p2) {
        if (p1->getLevel() != p2->getLevel()) {
            return p1->getLevel() > p2->getLevel();
        }
        if (p1->getCoins() != p2->getCoins()) {
            return p1->getCoins() > p2->getCoins();
        }
        return p1->getName() < p2->getName();
    });
}
