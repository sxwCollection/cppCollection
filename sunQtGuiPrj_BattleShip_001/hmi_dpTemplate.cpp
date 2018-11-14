#include "hmi_dpTemplate.h"

hmi_dpTemplate::hmi_dpTemplate(int const & iCRef_HmiBoardSize): pubI_HmiBoardSize(iCRef_HmiBoardSize)
{
}

/*

bool hmi_dpTemplate::parsePosition(const string &strPosition)
{
   regex strRe_positionDef("([A-J])([0-9])");
   smatch smatchResults;
   if(regex_match(strPosition, smatchResults, strRe_positionDef))
   {
       ssub_match sub_match_String = smatchResults[1];
       ssub_match sub_match_Number = smatchResults[2];
       int id1 = sub_match_String.str()[0] - 65 ;
       int id2 = stoi(sub_match_Number.str());
       emit inputPosition(id1, id2);
       return true;
   }
   else
   {
       return false;
   }
}

void hmi_dpTemplate::handleMultipleFired()
{
    cout<<"you have already fired at this place..."<<endl;
}
void hmi_dpTemplate::handleFleetSunk(int iScore_in)
{
     cout<<"Congratulation, you have sunk all ships!!!\n  Your score is "<< iScore_in<<endl<<"reset the game input 's'"<<endl;
}
void hmi_dpTemplate::handleSunkFire(const ship_2d &cref_sunkShip)
{
    cout<<"you have sunk one ship!!" <<endl;
    emit requestGameRoundState();
}
void hmi_dpTemplate::handleGameRoundeFinished()
{
    cout<<"this game round has been finished!!!\n"<<"reset the game input 's'"<<endl;
}
void hmi_dpTemplate::handleReportBoardState(unordered_set<int> firedPositions, unordered_set<int> hitPositions, unordered_set<int> sunkPositions)
{
    for(int i=0;i<prvI_HmiSize;i++)
    {
        for(int j=0;j<prvI_HmiSize;j++)
        {
            if(sunkPositions.find(i*10+j)!=sunkPositions.end())
            {
                printf("%c ", prvC_sunkPosition);
            }
            else if(hitPositions.find(i*10+j)!=hitPositions.end())
            {
                printf("%c ", prvC_hitPosition);
            }
            else if(firedPositions.find(i*10+j)!=firedPositions.end())
            {
                printf("%c ", prvC_firedPosition);
            }
            else
            {
                printf("%c ", prvC_unfiredPosition);
            }
        }
         printf("\n");
    }
}

void hmi_dpTemplate::startService()
{
    bool bExitServiceLoop=false;
    cout<<prvStr_menu<<endl;
    while (bExitServiceLoop==false)
    {
        string strIn;
        cin>>strIn;
        transform(strIn.begin(), strIn.end(), strIn.begin(), ::toupper);
        if (parsePosition(strIn)==false)
        {
            if(strIn=="Q")
            {
                bExitServiceLoop=true;
                break;
            }
            if(strIn=="R")
            {
                emit requestGameReset();
                bExitServiceLoop=true;
                break;
            }
            if(strIn=="S")
            {
                emit requestGameRoundBoardState();
            }
            else
            {
                cout<<"your input is ill formed, please read the menu"<<endl;
            }
        }
    }
}
*/
