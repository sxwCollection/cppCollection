#ifndef CANREADER_H
#define CANREADER_H

#include <QThread>
#include <QList>

#include "canlib.h"
#include "kvasercan_global.h"
#include<QtSerialBus/QCanBusFrame>
typedef void (*enqueueReceivedFrames)(const QVector<QCanBusFrame> &);

class CanReader : public QThread
{
  Q_OBJECT

private:
  CanHandle handle;
  CanReader() {};
  int exec();
  bool is_running;
  int can_channel;
  enqueueReceivedFrames fp_enqueueReceivedFrames;
  HANDLE readHandle  = INVALID_HANDLE_VALUE;
  //QVector<QCanBusFrame> newFrames;
  CanMessage* p_CMsg;

public:
  CanReader(CanHandle canHandle, HANDLE &readHandle_In, CanMessage* p_CMsg_InOut);
  void run();
  void stopRunning();

signals:
  void gotRx(CanMessage msg);
};

#endif // CANREADER_H
