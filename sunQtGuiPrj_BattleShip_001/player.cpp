#include "player.h"

player::player()
{
    pubI_score=0;
}
player::~player()
{
}
void player::getInputPosition(int id1_in, int id2_in)
{
    emit fireAt(id1_in, id2_in);
}
