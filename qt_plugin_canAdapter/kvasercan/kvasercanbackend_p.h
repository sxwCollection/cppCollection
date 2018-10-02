#ifndef KVASERCANBACKENDPRIVATE_H
#define KVASERCANBACKENDPRIVATE_H

#include"kvasercanbackend.h"
#include<QVector>
#include "witness.h"

QT_BEGIN_NAMESPACE

class QSocketNotifier;
class QWinEventNotifier;
class QTimer;


class KvaserCanBackendPrivate
{
    Q_DECLARE_PUBLIC(KvaserCanBackend)

public:
    KvaserCanBackendPrivate(KvaserCanBackend *q);
    KvaserCanBackend * const q_ptr;
    bool open();
    void close();
    bool setConfigurationParameter(int key, const QVariant &value);
    void setupChannel(const QString &interfaceName);
    void setupDefaultConfigurations(void);
    QString systemErrorString(canStatus ST_ErrorCode_In);
    void startWrite();
    void startRead();
    bool verifyBitRate(int bitrate);
    bool isOpen = false;
    QTimer *writeNotifier = nullptr;

    KvaserCanConfig kvaserCanConfig={.i_canHandle=-1, .i_selectedChannel=-1};
    void setKvaserCanConfig(void);
    bool enable_Witness=true;

    QWinEventNotifier *readNotifier = nullptr;
    HANDLE event_readHandle  = INVALID_HANDLE_VALUE;


};

QT_END_NAMESPACE

#endif // KVASERCANBACKENDPRIVATE_H
