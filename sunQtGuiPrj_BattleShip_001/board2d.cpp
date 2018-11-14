#include "board2d.h"

board2D::board2D(int id1_in, int id2_in)
{
    id1Size=id1_in;
    id2Size=id2_in;
}

tuple<int,int> board2D::getBoard2DSize() const
{
    return make_tuple(id1Size, id2Size);
}

