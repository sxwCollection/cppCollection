#include "ship_2d.h"

ship_2d::ship_2d( int shipLength_in )
{
    prvLength = shipLength_in;
    prvHitCounter=0;
    prvBSunk=false;
    pubI_maxHits=shipLength_in;
}
ship_2d::~ship_2d()
{

}
int ship_2d::setPositions(int id1_in, int id2_in, int mode_in)
{
    setHeadPositions(id1_in, id2_in);
    int shipEnd;
    switch (mode_in)
    {
    case 0:// set vertically
        shipEnd=prvLength+id2_in;
        for( ; id2_in<shipEnd; id2_in++)
        {
            if(Witness::enable_Witness)
            {
                qDebug()<<QString("%1: %2 %3 %4").arg(Witness::strLocation).arg("ship_2d::setPositions:").arg("id1*10, id2: ").arg(id1_in*10 + id2_in);
            }
            prvShipPositions.insert({(id1_in*10) + id2_in, false});
        }
        break;
    case 1:
        shipEnd=prvLength+id1_in;
        for( ; id1_in<shipEnd; id1_in++)
        {
            prvShipPositions.insert({(id1_in*10) + id2_in, false});
        }
        break;
    default:
        return 1;
    }
    return 0;
}

bool ship_2d::isIDInShipPositions(int id1_in, int id2_in)
{
    auto search = prvShipPositions.find(id1_in*10+id2_in);
    if(search!=prvShipPositions.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}

void ship_2d::setHeadPositions(int id1_in, int id2_in)
{
    prvHeadPosition1 = id1_in;
    prvHeadPosition2 = id2_in;
}

int ship_2d::length()
{
    return prvLength;
}

unordered_map <int, bool> ship_2d::getShipStates()
{
    return prvShipPositions;
}
unordered_set<int> ship_2d::getShipPositions()
{
    unordered_set<int> sOutput;
    for( const auto& i : prvShipPositions )
    {
         sOutput.insert(i.first);
    }
    return sOutput;
}

bool ship_2d::hitAtPosition(int id1_in, int id2_in)
{
    if(isIDInShipPositions(id1_in, id2_in)==true && prvShipPositions.at(id1_in*10+id2_in)==false)
    {
        prvHitCounter++;
        prvShipPositions.at(id1_in*10+id2_in)=true;
        checkSunk();
        return true;
    }
    return false;
}
bool ship_2d::checkSunk()
{
    if(prvHitCounter==pubI_maxHits)
    {
        prvBSunk=true;
        return true;
    }
    return false;
}

