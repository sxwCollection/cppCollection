#include "fleet.h"

fleet::fleet(board2D & board2d_in)
{
    prvBoard2d=&board2d_in;
    srand(time(0));
}

bool fleet::placeShipInFleet(ship_2d *p_ship_inOut)
{
    unordered_set<int> s_positionsToTry, s_tryResult, sPlacedFleetPositions;
    int iR,iRandEnd, id1, id2, id_tmp;
    int iBoardSize = get<0>(prvBoard2d->getBoard2DSize());
    iRandEnd=iBoardSize-(p_ship_inOut->length());
    for(const auto & pShip:prvVShips)
    {
        unordered_set<int> sRes=pShip->getShipPositions();
        sPlacedFleetPositions.insert(sRes.begin(),sRes.end());
    }
    iR=rand()%2;
    if(iR==0)
    {
        id1=rand() % iBoardSize;
        id2=rand() % (iRandEnd);
        int iend=id2+p_ship_inOut->length();

        for(id_tmp=id2; id_tmp<iend;id_tmp++)
        {
            if(Witness::enable_Witness)
            {
                qDebug()<<QString("%1: %2 %3 %4 %5").arg(Witness::strLocation).arg("fleet::placeShipInFleet:").arg("id1*10, id2: ").arg(id1*10).arg(id_tmp);
            }
            s_positionsToTry.insert( (id1*10) +id_tmp);
        }
    }
    else // vertically place a ship
    {
        id2=rand() % iBoardSize;
        id1=rand() % (iRandEnd);
        int iend=id1+p_ship_inOut->length();

        for(id_tmp=id1; id_tmp<iend;id_tmp++)
        {
            if(Witness::enable_Witness)
            {
                qDebug()<<QString("%1: %2 %3 %4 %5").arg(Witness::strLocation).arg("fleet::placeShipInFleet:").arg("id1*10, id2: ").arg(id_tmp*10).arg(id2);
            }
            s_positionsToTry.insert( (id_tmp*10) + id2);
        }
    }
    set_difference(s_positionsToTry.begin(),s_positionsToTry.end(),sPlacedFleetPositions.begin(),sPlacedFleetPositions.end(),std::inserter(s_tryResult,s_tryResult.end()));

    if(s_positionsToTry==s_tryResult) //no collision with the placed ships
    {
        p_ship_inOut->setPositions(id1, id2, iR);
        prvVShips.push_back(p_ship_inOut);
        return true;
    }
    return false;
}

fleet::~fleet()
{
    for(const auto & ai: prvVShips)
    {
        delete ai;
    }
    delete prvBoard2d;
}

vector<ship_2d*> fleet::getPlacedShips()
{
    return prvVShips;
}

board2D* fleet::getBoard2D()
{
    return prvBoard2d;
}

tuple<bool, ship_2d*> fleet::hitAtPosition(int id1_in, int id2_in)
{
    bool bisHit=false;
    ship_2d* pSunkShip=0;
    for(auto const & ai: prvVShips)
    {
        if(ai->hitAtPosition(id1_in, id2_in))
        {
            bisHit=true;
            prvBoard2d->pubUSet_hitPositions.insert(id1_in*10+id2_in);
            if(ai->checkSunk()) // ship sunk
            {
                pubVSunkShips.push_back(ai);
                pSunkShip= ai;
            }
        }
        else
        {
            prvBoard2d->pubUSet_firedPositions.insert(id1_in*10+id2_in);
        }
    }
    return make_tuple(bisHit, pSunkShip);
}
bool fleet::isFleetSunk()
{
    if(Witness::enable_Witness)
    {
        qDebug()<<QString("%1: %2 %3 %4 %5").arg(Witness::strLocation).arg("fleet::isFleetSunk:").arg("prvVShips.size(), pubVSunkShips.size: ").arg(prvVShips.size()).arg(pubVSunkShips.size());
    }
    if(prvVShips.size()==pubVSunkShips.size())
    {
        return true;
    }
    return false;
}

