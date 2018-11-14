#ifndef GAME_ROUND_H
#define GAME_ROUND_H
#include <QObject>
#include <player.h>
#include <settings.h>
#include <fleet.h>
#include <iostream>
#include <unordered_set>

using namespace std;
enum class EnuC_gameRoundState { running, finished};

class game_round : public QObject
{
    Q_OBJECT
public:
    explicit game_round(settings const & settings_In, player & player_In);
    ~game_round();
    EnuC_gameRoundState pubEnuC_gameRoundState;
    static int statInt_RoundCounter;
    void startRound();

public slots:
    void getFiredAtPosition(int id1_in,int id2_in);
    bool isFiredAtThisPosition(int id1_in,int id2_in);
    void checkGameRoundState(void);
    void handleRequest_BoardState(void);
signals:
    void getSunk(ship_2d const & cref_sunkShip);
    void getHit(bool bGetHit);
    void multipleFired(void);
    void getFleetSunk(int iScore_in);
    void gameRoundState_finished(void);
    void reportBoardState(unordered_set<int> firedPositions, unordered_set<int> hitPositions, unordered_set<int> sunkPositions);

private:
    settings const * prvSettings;
    player * prvPlayer;
    fleet * prvFleet;
    int prvI_sunkShipCounter;
};


#endif // GAME_ROUND_H
