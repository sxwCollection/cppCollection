#include "bs_game.h"

bs_game::bs_game(hmi_dpTemplate* pHmiDPInterface)
{
    initGame(pHmiDPInterface);
}
bs_game::~bs_game()
{
    deinitGame();
}
void bs_game::initGame(hmi_dpTemplate* pHmiDPInterface)
{
    pubPHmi = pHmiDPInterface;
    prvPSettings = new settings();
    prvPPlayer = new player();
    pubP_gameRound = new game_round(*prvPSettings, *prvPPlayer);
    connect(pubPHmi, hmi_dpTemplate::inputPosition, prvPPlayer, player::getInputPosition);
    connect(prvPPlayer, player::fireAt, pubP_gameRound, game_round::getFiredAtPosition);
    connect(pubP_gameRound, game_round::getHit, pubPHmi, hmi_dpTemplate::handleHitFire);
    connect(pubP_gameRound, game_round::getSunk, pubPHmi, hmi_dpTemplate::handleSunkFire);
    connect(pubP_gameRound, game_round::multipleFired, pubPHmi, hmi_dpTemplate::handleMultipleFired);
    connect(pubPHmi, hmi_dpTemplate::requestGameRoundState, pubP_gameRound, game_round::checkGameRoundState);
    connect(pubP_gameRound, game_round::getFleetSunk, pubPHmi, hmi_dpTemplate::handleFleetSunk);
    connect(pubP_gameRound, game_round::gameRoundState_finished, pubPHmi, hmi_dpTemplate::handleGameRoundeFinished);
    connect(pubPHmi, hmi_dpTemplate::requestGameRoundBoardState, pubP_gameRound, game_round::handleRequest_BoardState);
    connect(pubP_gameRound, game_round::reportBoardState, pubPHmi, hmi_dpTemplate::handleReportBoardState);

    connect(pubPHmi, hmi_dpTemplate::requestGameReset, this, bs_game::handleReset);
}

void bs_game::deinitGame()
{
    disconnect(pubPHmi, hmi_dpTemplate::inputPosition, prvPPlayer, player::getInputPosition);
    disconnect(prvPPlayer, player::fireAt, pubP_gameRound, game_round::getFiredAtPosition);
    disconnect(pubP_gameRound, game_round::getHit, pubPHmi, hmi_dpTemplate::handleHitFire);
    disconnect(pubP_gameRound, game_round::getSunk, pubPHmi, hmi_dpTemplate::handleSunkFire);
    disconnect(pubP_gameRound, game_round::multipleFired, pubPHmi, hmi_dpTemplate::handleMultipleFired);
    disconnect(pubPHmi, hmi_dpTemplate::requestGameRoundState, pubP_gameRound, game_round::checkGameRoundState);
    disconnect(pubP_gameRound, game_round::getFleetSunk, pubPHmi, hmi_dpTemplate::handleFleetSunk);
    disconnect(pubP_gameRound, game_round::gameRoundState_finished, pubPHmi, hmi_dpTemplate::handleGameRoundeFinished);
    disconnect(pubPHmi, hmi_dpTemplate::requestGameRoundBoardState, pubP_gameRound, game_round::handleRequest_BoardState);
    delete prvPSettings;
    delete prvPPlayer;
    pubPHmi = 0;
    delete pubP_gameRound;
}

void bs_game::resetGame(hmi_dpTemplate* pHmiDPInterface)
{
    deinitGame();
    initGame(pHmiDPInterface);
}

void bs_game::handleReset(hmi_dpTemplate* pHmiDPInterface)
{
    resetGame(pHmiDPInterface);
    pubP_gameRound->startRound();
    pubPHmi->startService();
}

