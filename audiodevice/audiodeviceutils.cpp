#include "audiodeviceutils.h"
#include <QDebug>

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

