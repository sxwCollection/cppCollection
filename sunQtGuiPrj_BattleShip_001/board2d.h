#ifndef BOARD2D_H
#define BOARD2D_H
#include <QObject>
#include <tuple>
#include <unordered_set>

using namespace std;

class board2D : public QObject
{
    Q_OBJECT
public:
    explicit board2D(int id1_in, int id2_in);
    tuple<int, int> getBoard2DSize(void) const;
    unordered_set<int> pubUSet_firedPositions;
    unordered_set<int> pubUSet_hitPositions;


private:
    int id1Size, id2Size;
};

#endif // BOARD2D_H
