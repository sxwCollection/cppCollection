#include "hmi_gui.h"

hmi_gui::hmi_gui(int const & iCRef_HmiBoardSize): hmi_dpTemplate(iCRef_HmiBoardSize)
{
    prvB_isServiceRunning = false;
}
hmi_gui::~hmi_gui()
{
}

void hmi_gui::startService()
{
    if(prvB_isServiceRunning == false)
    {
        prvB_isServiceRunning = true;
        emit sigStartGui();
    }

}
void hmi_gui::handleFleetSunk(int iScore_in)
{
    emit sigFleetSunk(iScore_in);
}
void hmi_gui::handleGameRoundeFinished()
{
    emit sigGameRoundeFinished();
}
void hmi_gui::handleHitFire(bool bGetHit)
{
    emit sigHitFire(bGetHit);
}
void hmi_gui::handleMultipleFired()
{
    emit sigMultipleFired();
}
void hmi_gui::handleReportBoardState(unordered_set<int> firedPositions, unordered_set<int> hitPositions, unordered_set<int> sunkPositions)
{
    emit sigReportBoardState(firedPositions, hitPositions, sunkPositions);
}
void hmi_gui::handleSunkFire(const ship_2d &cref_sunkShip)
{
    emit sigSunkFire(cref_sunkShip);
}
