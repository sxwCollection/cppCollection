#include "KvaserCanbackend.h"
#include "kvasercanbackend_p.h"
//#include "KvaserCan_symbols_p.h"
#include <QtSerialBus/qcanbusdevice.h>
#include <QtCore/qtimer.h>
#include <QtCore/qcoreevent.h>
#include <QtCore/qloggingcategory.h>
#include <algorithm>
#include<QDebug>
#include<windows.h>

#include <canlib.h>

#ifdef Q_OS_WIN32
#   include <QtCore/qwineventnotifier.h>
#else
#   include <QtCore/qsocketnotifier.h>
#endif
QT_BEGIN_NAMESPACE
Q_DECLARE_LOGGING_CATEGORY(QT_CANBUS_PLUGINS_KvaserCan)

bool KvaserCanBackend::canCreate(QString *errorReason)
{
#ifdef LINK_LIBPCANBASIC
    return true;
#else

    return true;
#endif
}

class WriteNotifier : public QTimer
{
    // no Q_OBJECT macro!
public:
    WriteNotifier(KvaserCanBackendPrivate *d, QObject *parent)
        : QTimer(parent)
        , dptr(d)
    {
    }

protected:
    void timerEvent(QTimerEvent *e) override
    {
        if (e->timerId() == timerId()) {
            dptr->startWrite();
            return;
        }
        QTimer::timerEvent(e);
    }

private:
    KvaserCanBackendPrivate *dptr;
};

class ReadNotifier : public QWinEventNotifier
{
    // no Q_OBJECT macro!
public:
    explicit ReadNotifier(KvaserCanBackendPrivate *d, QObject *parent)
        : QWinEventNotifier(parent)
        , dptr(d)
    {
        setHandle(dptr->event_readHandle);
    }

protected:
    bool event(QEvent *e) override
    {
        if (e->type() == QEvent::WinEventAct) {
            dptr->startRead();
            return true;
        }
        return QWinEventNotifier::event(e);
    }

private:
    KvaserCanBackendPrivate *dptr;
};

QList<QCanBusDeviceInfo> KvaserCanBackend::interfaces()
{
    QList<QCanBusDeviceInfo> result;
    int stat = 0;
    int channels = 0;
    canUnloadLibrary();
    canInitializeLibrary();
    stat = canGetNumberOfChannels(&channels);
    if (stat < canOK) {
      //qDebug(QString("canGetNumberOfChannels() failed, %1").arg(can_handle));
      return result;
    }

    for (int i=0; i<channels; i++) {
      char name[64];
      stat = canGetChannelData(i, canCHANNELDATA_CHANNEL_NAME, name, sizeof(name));
      result.append(std::move(createDeviceInfo(QLatin1String(name), QString(name).contains("Virtual"), false)));
    }
    return result;
}

bool Witness::enable_Witness=false;

KvaserCanBackendPrivate::KvaserCanBackendPrivate(KvaserCanBackend *q)
    : q_ptr(q)
{

}

struct BitrateItem
{
    int bitrate;
    int code;
};

struct BitrateLessFunctor
{
    bool operator()( const BitrateItem &item1, const BitrateItem &item2) const
    {
        return item1.bitrate < item2.bitrate;
    }
};



static int bitrateCodeFromBitrate(int bitrate)
{
    static const BitrateItem bitratetable[] = {
        { 10000, canBITRATE_10K },
        { 50000, canBITRATE_50K },
        { 62000, canBITRATE_62K },
        { 83000,  canBITRATE_83K},
        { 100000, canBITRATE_100K },
        { 125000, canBITRATE_125K },
        { 250000, canBITRATE_250K },
        { 500000, canBITRATE_500K },
        { 1000000, canBITRATE_1M }
    };

    static const BitrateItem *endtable = bitratetable + (sizeof(bitratetable) / sizeof(*bitratetable));

    const BitrateItem item = { bitrate , 0 };
    const BitrateItem *where = std::lower_bound(bitratetable, endtable, item, BitrateLessFunctor());
    return where != endtable ? where->code : -1;
}

bool KvaserCanBackendPrivate::verifyBitRate(int bitrate)
{
    Q_Q(KvaserCanBackend);

    if (Q_UNLIKELY(isOpen)) {
        q->setError(KvaserCanBackend::tr("Impossible to reconfigure bitrate for the opened device"),
                    QCanBusDevice::ConfigurationError);
        return false;
    }

    if (Q_UNLIKELY(bitrateCodeFromBitrate(bitrate) == -1)) {
        q->setError(KvaserCanBackend::tr("Unsupported bitrate value"),
                    QCanBusDevice::ConfigurationError);
        return false;
    }

    return true;
}

bool KvaserCanBackendPrivate::open()
{
    Q_Q(KvaserCanBackend);
    if(Witness::enable_Witness)
    {
        qDebug()<<QString("%1: %2 ").arg(Witness::strLocation).arg("KvaserCanBackendPrivate::open:");//.arg("Variable:");
    }
    const int conI_bitrate = q->configurationParameter(QCanBusDevice::BitRateKey).toInt();
    kvaserCanConfig.i_bitrateCode = bitrateCodeFromBitrate(conI_bitrate);
    canStatus e_status = canSetBusParams(kvaserCanConfig.i_canHandle, kvaserCanConfig.i_bitrateCode, kvaserCanConfig.ui_tseg1, kvaserCanConfig.ui_tseg2, kvaserCanConfig.ui_sjw, kvaserCanConfig.ui_noSamp, kvaserCanConfig.ui_syncmode);

    if(Witness::enable_Witness)
    {
        if (e_status != canOK)
        {
          qDebug()<<QString("%1 %2 : %3: %4 %5").arg(Witness::strLocation).arg("KvaserCanBackendPrivate::open:").arg(Witness::strEvt_FunctionFailed).arg("canSetBusParams(): ").arg(e_status);
        }
    }
    if (Q_UNLIKELY(e_status < canOK))
    {
        q->setError(systemErrorString(e_status), QCanBusDevice::ConfigurationError);
        return false;
    }
    e_status = canBusOn(kvaserCanConfig.i_canHandle);
    if(Witness::enable_Witness)
    {
        if (e_status != canOK)
        {
          qDebug()<<QString("Witness:Location: %1 : %2: %3 %4").arg("KvaserCanBackendPrivate::open:").arg("Event").arg("canBusOn() failed, ").arg(e_status);
        }
    }
    if (Q_UNLIKELY(e_status < canOK))
    {
        q->setError(systemErrorString(e_status), QCanBusDevice::ConnectionError);
        return false;
    }
    if(event_readHandle==INVALID_HANDLE_VALUE)
    {
        event_readHandle=CreateEvent(NULL, TRUE, FALSE, TEXT("RxEvent"));
    }
    e_status = canIoCtl (kvaserCanConfig.i_canHandle, canIOCTL_GET_EVENTHANDLE, &event_readHandle, sizeof (event_readHandle));
    if(Witness::enable_Witness)
    {
        if (e_status != canOK)
        {
          qDebug()<<QString("Witness:Location: %1 : %2: %3 %4").arg("KvaserCanBackendPrivate::open:").arg("Event").arg("canIoCtl canIOCTL_GET_EVENTHANDLE() failed, ").arg(e_status);
        }
    }
    if (Q_UNLIKELY(e_status < canOK))
    {
        q->setError(systemErrorString(e_status), QCanBusDevice::ConfigurationError);
        return false;
    }

    isOpen = true;
    q->setState(QCanBusDevice::ConnectedState);

    writeNotifier = new WriteNotifier(this, q);
    writeNotifier->setInterval(0);

    readNotifier = new ReadNotifier(this, q);
    readNotifier->setEnabled(true);


    return true;
}


void KvaserCanBackendPrivate::close()
{
    //Q_Q(KvaserCanBackend);
    delete writeNotifier;
    writeNotifier = nullptr;
    isOpen = false;
    delete readNotifier;
    readNotifier = nullptr;
    canBusOff(kvaserCanConfig.i_canHandle);
    canClose(kvaserCanConfig.i_canHandle);
    kvaserCanConfig.i_canHandle=canINVALID_HANDLE;

}
void KvaserCanBackendPrivate::setupChannel(const QString &interfaceName)
{
    Q_Q(KvaserCanBackend);
    canStatus e_status;
    int i_channelNumber;
    if(Witness::enable_Witness)
    {
        qDebug()<<QString("%1 %2 ").arg(Witness::strLocation).arg("KvaserCanBackendPrivate::setupChannel:");
    }
    e_status = canGetNumberOfChannels(&i_channelNumber);

    if (e_status < canOK)
    {
      qDebug("canGetNumberOfChannels() failed");
    }
    if (Q_UNLIKELY(e_status < canOK))
        q->setError(systemErrorString(e_status), QCanBusDevice::ConfigurationError);

    for (int i=0; i<i_channelNumber; i++)
    {
      char charAry_channelName[64];
      e_status = canGetChannelData(i, canCHANNELDATA_CHANNEL_NAME, charAry_channelName, sizeof(charAry_channelName));
      if(Witness::enable_Witness)
      {
       qDebug()<<QString("%1 %2 %3 %4 %5").arg(Witness::strLocation).arg("KvaserCanBackendPrivate:setupChannel:").arg(Witness::strVariable).arg("name: ").arg(charAry_channelName);
      }
      if(QString::compare(QLatin1String(charAry_channelName), interfaceName, Qt::CaseInsensitive)==0)
      {
          kvaserCanConfig.i_selectedChannel=i;
          canGetChannelData(i, canCHANNELDATA_CHANNEL_NAME, kvaserCanConfig.ca_selectedInterfaceName, sizeof(kvaserCanConfig.ca_selectedInterfaceName));
          if(Witness::enable_Witness)
          {
              qDebug()<<QString("Witness:Location: %1 Witness:Event: %2 kvaserCanConfig.i_selectedChannel: %3").arg("KvaserCanBackendPrivate::setupChannel::").arg("Variable:").arg(kvaserCanConfig.i_selectedChannel);
          }
          break;
      }
    }
    if (kvaserCanConfig.i_selectedChannel==KCAN_SELECTED_CHANEL_INIT)
    {
        qDebug()<<"Witness:Location: KvaserCanBackendPrivate:setupChannel:Witness:Event: function failed: "<<interfaceName;
    }

}
void KvaserCanBackendPrivate::setKvaserCanConfig()
{
    Q_Q(KvaserCanBackend);
    kvaserCanConfig.i_openChanelFlags=canOPEN_ACCEPT_VIRTUAL;
    kvaserCanConfig.i_busControlMode=canDRIVER_NORMAL;
    kvaserCanConfig.ui_noSamp=0;
    kvaserCanConfig.ui_syncmode=0;
    kvaserCanConfig.ui_tseg1  =0;
    kvaserCanConfig.ui_tseg2=0;
    kvaserCanConfig.ui_sjw=0;

    kvaserCanConfig.i_canHandle = canOpenChannel(kvaserCanConfig.i_selectedChannel, kvaserCanConfig.i_openChanelFlags);
    if(Witness::enable_Witness)
    {
        qDebug()<<QString("Witness:Location: %1 Witness:Event: %2 kvaserCanConfig.i_selectedChannel: %3, kvaserCanConfig.i_canHandle: %4").arg("KvaserCanBackendPrivate::setKvaserCanConfig:").arg("Variable:").arg(kvaserCanConfig.i_selectedChannel).arg(kvaserCanConfig.i_canHandle);
    }
    if (kvaserCanConfig.i_canHandle < canOK) {
      qDebug() << QString("canOpenChannel() failed, %1").arg(kvaserCanConfig.i_canHandle);
      qDebug() << QString("canOpenChannel() failed, %d").arg(kvaserCanConfig.i_selectedChannel);

    }
    if (Q_UNLIKELY(kvaserCanConfig.i_canHandle < canOK))
        q->setError(systemErrorString((canStatus)kvaserCanConfig.i_canHandle), QCanBusDevice::ConnectionError);
    canStatus status = canSetBusOutputControl(kvaserCanConfig.i_canHandle, kvaserCanConfig.i_busControlMode);
    if (Q_UNLIKELY(status != canOK))
        q->setError(systemErrorString(status), QCanBusDevice::ConfigurationError);

}
// Calls only when the device is closed
void KvaserCanBackendPrivate::setupDefaultConfigurations()
{
    Q_Q(KvaserCanBackend);
    q->setConfigurationParameter(QCanBusDevice::BitRateKey, 250000);

}

QString KvaserCanBackendPrivate::systemErrorString(canStatus ST_ErrorCode_In)
{
    //Q_Q(KvaserCanBackend);
    char buf[100];
    buf[0] = '\0';

    if ( Q_UNLIKELY(canGetErrorText(ST_ErrorCode_In, buf, sizeof(buf)) != canOK))
    {
        return KvaserCanBackend::tr("Unable to retrieve an error string");
    }
    return QString(buf);
}


void KvaserCanBackendPrivate::startWrite()
{
    Q_Q(KvaserCanBackend);

    if (!q->hasOutgoingFrames()) {
        writeNotifier->stop();
        return;
    }

    if(Witness::enable_Witness)
    {
        qDebug()<<QString("Witness:Location: %1 ").arg("KvaserCanBackendPrivate::startWrite:");//.arg("Variable:").arg(kvaserCanConfig.i_selectedChannel).arg(kvaserCanConfig.i_canHandle);
    }
    const QCanBusFrame frame = q->dequeueOutgoingFrame();
    const QByteArray payload = frame.payload();

    CanMessage strct_message;
    ::memset(&strct_message, 0, sizeof(strct_message));

    strct_message.id = frame.frameId();
    strct_message.dlc = payload.size();
    strct_message.flags = frame.hasExtendedFrameFormat() ? canMSG_EXT : canMSG_STD;

    if (frame.frameType() == QCanBusFrame::RemoteRequestFrame)
        strct_message.flags |= canMSG_RTR; // we do not care about the payload
    else
        ::memcpy(strct_message.data, payload.constData(), sizeof(strct_message.data));

    const canStatus st = canWrite(kvaserCanConfig.i_canHandle, strct_message.id, strct_message.data, strct_message.dlc, strct_message.flags);
    if (Q_UNLIKELY(st != canOK))
        //q->setError(systemErrorString(st), QCanBusDevice::WriteError);
        q->setError("systemErrorString(st)", QCanBusDevice::WriteError);
    else
        emit q->framesWritten(qint64(1));

    if(Witness::enable_Witness)
    {
        qDebug()<<QString("Witness:Location: %1 %2: message id: %3, message dlc: %4").arg("KvaserCanBackendPrivate::startWrite:").arg("Witness:Event: Variable:").arg(strct_message.id).arg(strct_message.dlc);
    }

    if (q->hasOutgoingFrames() && !writeNotifier->isActive())
        writeNotifier->start();
}

void KvaserCanBackendPrivate::startRead()
{
    Q_Q(KvaserCanBackend);
    if(Witness::enable_Witness)
    {
        qDebug()<<QString("Witness:Location: %1 ").arg("KvaserCanBackendPrivate::startRead:");//.arg("Variable:").arg(kvaserCanConfig.i_selectedChannel).arg(kvaserCanConfig.i_canHandle);
    }

    QVector<QCanBusFrame> newFrames;

    CanMessage msg;
    canStatus e_status;
    do
    {
        e_status = canRead(kvaserCanConfig.i_canHandle, &msg.id, &msg.data, &msg.dlc, &msg.flags, &msg.time);
        if (e_status == canOK)
        {
            QCanBusFrame frame(msg.id, QByteArray((const char *)(msg.data), int(msg.dlc)));//reinterpret_cast<const char *>
            frame.setTimeStamp(QCanBusFrame::TimeStamp::fromMicroSeconds(msg.time*1000));
            frame.setExtendedFrameFormat(msg.flags & canMSG_EXT);
            frame.setFrameType((msg.flags & canMSG_RTR)
                               ? QCanBusFrame::RemoteRequestFrame
                               : (msg.flags & canMSG_ERROR_FRAME)
                                 ? QCanBusFrame::ErrorFrame
                                 : QCanBusFrame::DataFrame);

            newFrames.append(std::move(frame));
        }
    }while (e_status == canOK);

    q->enqueueReceivedFrames(newFrames);//this will trigger QCanBusDevice::framesReceived signal

}



bool KvaserCanBackendPrivate::setConfigurationParameter(int key, const QVariant &value)
{
    Q_Q(KvaserCanBackend);

    switch (key) {
    case QCanBusDevice::BitRateKey:
        if(Witness::enable_Witness)
        {
            qDebug()<<QString("Witness:Location: %1 Witness:Event: %2 key: %3, value: %4").arg("KvaserCanBackendPrivate:setConfigurationParameter:").arg("Variable:").arg(key).arg(value.toInt());
        }

        return verifyBitRate(value.toInt());
    default:
        q->setError(KvaserCanBackend::tr("Unsupported configuration key: %1").arg(key),
                    QCanBusDevice::ConfigurationError);
        return false;
    }
}

KvaserCanBackend::KvaserCanBackend(const QString &name, QObject *parent)
    : QCanBusDevice(parent)
    ,d_ptr(new KvaserCanBackendPrivate(this))
{
    Q_D(KvaserCanBackend);
    canInitializeLibrary();
    d->setupChannel(name);
    d->setKvaserCanConfig();
    d->setupDefaultConfigurations();

}

KvaserCanBackend::~KvaserCanBackend()
{
    Q_D(KvaserCanBackend);
    if(d->isOpen)
        {d->close();}
    delete d_ptr;
}


bool KvaserCanBackend::open()
{
    Q_D(KvaserCanBackend);
    if(Witness::enable_Witness)
    {
        qDebug()<<QString("Witness:Location: %1").arg("KvaserCanBackend::open:");//.arg("Variable:").arg(key).arg(value.toInt());
    }
    d->open();


    return true;
}
void KvaserCanBackend::close()
{
    Q_D(KvaserCanBackend);
    d->close();


}
void KvaserCanBackend::setConfigurationParameter(int key, const QVariant &value)
{
    Q_D(KvaserCanBackend);
    if (d->setConfigurationParameter(key, value))
        QCanBusDevice::setConfigurationParameter(key, value);

}
bool KvaserCanBackend::writeFrame(const QCanBusFrame &newData)
{
    Q_D(KvaserCanBackend);
    if (Q_UNLIKELY(state() != QCanBusDevice::ConnectedState))
        return false;

    if (Q_UNLIKELY(!newData.isValid())) {
        setError(tr("Cannot write invalid QCanBusFrame"), QCanBusDevice::WriteError);
        return false;
    }

    if (Q_UNLIKELY(newData.frameType() != QCanBusFrame::DataFrame
                   && newData.frameType() != QCanBusFrame::RemoteRequestFrame)) {
        setError(tr("Unable to write a frame with unacceptable type"),
                 QCanBusDevice::WriteError);
        return false;
    }

    // CAN FD frame format not implemented at this stage
    if (Q_UNLIKELY(newData.payload().size() > 8)) {
        setError(tr("CAN FD frame format not supported."), QCanBusDevice::WriteError);
        return false;
    }

    enqueueOutgoingFrame(newData);

    if (!d->writeNotifier->isActive())
        d->writeNotifier->start();

    return true;
}


// TODO: Implement me
QString KvaserCanBackend::interpretErrorFrame(const QCanBusFrame &errorFrame)
{

    Q_UNUSED(errorFrame);

    return QString(" ");
}



QT_END_NAMESPACE
