#if 0
$ mkdir -p ~/.config/QtProject
$ cat > ~/.config/QtProject/qtlogging.ini <<EOF
[Rules]
*.debug=true
qt.*.debug=false
EOF

$ qmake-qt5 .
$ make
$ QT_LOGGING_RULES="*.debug=true" ./helloworld
#else
#include <QtCore/QCoreApplication>
#include <QDebug>
#include <QAudioDeviceInfo>

QAudioDeviceInfo getAudioDevice(QString name) {
  QAudioDeviceInfo device;
  QList<QAudioDeviceInfo> devices =
    QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
  for(int i = 0; i < devices.size(); ++i) {
    qDebug() << "input Device name: " << devices.at(i).deviceName();
    if(devices.at(i).deviceName() == name) {
      device = devices.at(i);
      break;
    }
  }
  return device;
}

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);
  qDebug() << "Hello World!";

  const auto deviceInfos = QAudioDeviceInfo::availableDevices(QAudio::AudioOutput);
  for (const QAudioDeviceInfo &deviceInfo : deviceInfos)
    qDebug() << "output Device name: " << deviceInfo.deviceName();

  QAudioDeviceInfo myDevice = getAudioDevice("default");
  if(myDevice.isNull()) {
    qCritical("Device not found");
  }
  return a.exec(); // .exec starts QApplication and related GUI, this line starts 'event loop'    
}
#endif
