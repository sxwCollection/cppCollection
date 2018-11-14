#ifndef PLAYER_H
#define PLAYER_H
#include <QObject>
#include <QDebug>

class player : public QObject
{
    Q_OBJECT
public:
    player();
    ~player();
    int pubI_score;


signals:
    void fireAt(int id1_in,int id2_in);

public slots:
    void getInputPosition(int id1_in, int id2_in);
};

#endif // PLAYER_H
