/*
#include <QCanBus>

int main(int argc, char *argv[])
{
QString errorString;
//QCanBus::instance()->createDevice(QStringLiteral("KvaserCan"), QStringLiteral("vcan0"), &errorString);
QStringList myStringList= QCanBus::instance()->plugins();
QCanBusDevice *device = QCanBus::instance()->createDevice(QStringLiteral("kvasercan"), QStringLiteral("vcan0"), &errorString);
if (!device)
    qDebug( errorString.toLatin1());

for (QStringList::Iterator S =  myStringList.begin(); S != myStringList.end(); S++)
      {
        QString current = *S;
        qDebug(current.toLatin1());
      }

printf("hello");
}
*/
#include "kvasercanbackend.h"
#include <QtSerialBus/qcanbus.h>
#include <QtSerialBus/qcanbusdevice.h>
#include <QtSerialBus/qcanbusfactory.h>
#include <QtCore/qloggingcategory.h>

#include <QCoreApplication>
#include <QCanBus>

QT_BEGIN_NAMESPACE

class KvaserCanPlugin : public QObject, public QCanBusFactoryV2
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QCanBusFactory" FILE "plugin.json")
    Q_INTERFACES(QCanBusFactoryV2)
public:
    QList<QCanBusDeviceInfo> availableDevices(QString *errorMessage) const override
    {

        return KvaserCanBackend::interfaces();
    }
    QCanBusDevice *createDevice(const QString &interfaceName, QString *errorMessage) const override
    {
        QString errorReason;

        auto device = new KvaserCanBackend(interfaceName);
        return device;
    }
};
QT_END_NAMESPACE

#include "main.moc"
