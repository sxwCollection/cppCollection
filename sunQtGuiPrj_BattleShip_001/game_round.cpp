#include "game_round.h"

int game_round::statInt_RoundCounter=0;
game_round::game_round(settings const & settings_In, player & player_In)
{
    ++game_round::statInt_RoundCounter;
    prvSettings = &settings_In;
    prvPlayer = &player_In;
    prvFleet=new fleet( *(new board2D(prvSettings->pub_BoardSize, prvSettings->pub_BoardSize)));
    prvI_sunkShipCounter=0;
    pubEnuC_gameRoundState = EnuC_gameRoundState::running;
}
game_round::~game_round()
{
    delete prvFleet;
    prvFleet=0;
}

void game_round::startRound()
{
    for(auto const & ai:prvSettings->pubB_Ships)
    {
        ship_2d* pShip = new ship_2d(ai);
        while(prvFleet->placeShipInFleet(pShip)==false)
        {
            cout<<""<<endl;
            if(Witness::enable_Witness)
            {
                qDebug()<<QString("%1: %2 %3").arg(Witness::strLocation).arg("game_round::startRound: ").arg("placed ship not correctly");
            }
        }
    }
}

void game_round::getFiredAtPosition(int id1_in, int id2_in)
{
    if(pubEnuC_gameRoundState==EnuC_gameRoundState::running)
    {
        prvPlayer->pubI_score++;
        if(isFiredAtThisPosition(id1_in, id2_in)==false)
        {
            tuple<bool, ship_2d*> tupRes = prvFleet->hitAtPosition(id1_in, id2_in);
            if(get<0>(tupRes))
            {
                if(get<1>(tupRes)!=0) // ship sunk
                {
                    emit getSunk(*get<1>(tupRes));
                }
                else
                {
                    emit getHit(true);
                }
            }
            else
            {
                emit getHit(false);
            }
        }
        else
        {
            emit multipleFired();
        }
    }
    else
    {
        emit gameRoundState_finished();
    }
}
bool game_round::isFiredAtThisPosition(int id1_in, int id2_in)
{
    if((prvFleet->getBoard2D()->pubUSet_firedPositions.find(id1_in*10+id2_in) == prvFleet->getBoard2D()->pubUSet_firedPositions.end()) && (prvFleet->getBoard2D()->pubUSet_hitPositions.find(id1_in*10+id2_in) == prvFleet->getBoard2D()->pubUSet_firedPositions.end()))
    {// not found
        return false;
    }
    return true; //found fired position
}
void game_round::checkGameRoundState()
{
    if(prvFleet->isFleetSunk())
    {
        pubEnuC_gameRoundState = EnuC_gameRoundState::finished;
        emit getFleetSunk(prvPlayer->pubI_score);
    }
}
void game_round::handleRequest_BoardState()
{
    unordered_set<int> us_sunkPositions, us_tmp;
    for(auto const & ai:prvFleet->pubVSunkShips)
    {
        us_tmp = ai->getShipPositions();
        us_sunkPositions.insert(us_tmp.begin(), us_tmp.end());
    }
    emit reportBoardState(prvFleet->getBoard2D()->pubUSet_firedPositions, prvFleet->getBoard2D()->pubUSet_hitPositions, us_sunkPositions);

}

