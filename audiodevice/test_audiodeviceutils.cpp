#include <QtTest>
#include <QCoreApplication>
#include "audiodeviceutils.h"
#include <QAudioDeviceInfo>
#include <QList>

class TestAudioDeviceUtils : public QObject
{
    Q_OBJECT

public:
    TestAudioDeviceUtils();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testGetAudioDevice_existingDevice();
    void testGetAudioDevice_nonExistentDevice();
    void testGetAudioDevice_emptyString();
    void testGetAudioDevice_caseSensitive();
    void testGetAudioDevice_listAvailableDevices();

private:
    QList<QAudioDeviceInfo> availableInputDevices;
};

TestAudioDeviceUtils::TestAudioDeviceUtils()
{
}

void TestAudioDeviceUtils::initTestCase()
{
    // Create QCoreApplication instance (required for Qt multimedia)
    static int argc = 1;
    static char *argv[] = { const_cast<char*>("test_audiodeviceutils") };
    if (!qApp) {
        new QCoreApplication(argc, argv);
    }
    
    // Get list of available input devices for reference in tests
    availableInputDevices = QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
    qDebug() << "Found" << availableInputDevices.size() << "input audio devices";
}

void TestAudioDeviceUtils::cleanupTestCase()
{
}

void TestAudioDeviceUtils::testGetAudioDevice_existingDevice()
{
    if (availableInputDevices.isEmpty()) {
        QSKIP("No audio input devices available for testing");
    }
    
    // Test with the first available device name
    QString firstDeviceName = availableInputDevices.first().deviceName();
    QAudioDeviceInfo result = getAudioDevice(firstDeviceName);
    
    QVERIFY(!result.isNull());
    QCOMPARE(result.deviceName(), firstDeviceName);
}

void TestAudioDeviceUtils::testGetAudioDevice_nonExistentDevice()
{
    // Test with a device name that definitely doesn't exist
    QString nonExistentDevice = "ThisDeviceDefinitelyDoesNotExist12345";
    QAudioDeviceInfo result = getAudioDevice(nonExistentDevice);
    
    // Should return a null/invalid device
    QVERIFY(result.isNull());
}

void TestAudioDeviceUtils::testGetAudioDevice_emptyString()
{
    // Test with empty string
    QAudioDeviceInfo result = getAudioDevice("");
    
    // Should return a null/invalid device (unless there's a device with empty name)
    if (availableInputDevices.isEmpty()) {
        QVERIFY(result.isNull());
    } else {
        // Check if any device has empty name (unlikely but possible)
        bool foundEmptyName = false;
        for (const QAudioDeviceInfo &device : availableInputDevices) {
            if (device.deviceName().isEmpty()) {
                foundEmptyName = true;
                break;
            }
        }
        if (!foundEmptyName) {
            QVERIFY(result.isNull());
        }
    }
}

void TestAudioDeviceUtils::testGetAudioDevice_caseSensitive()
{
    if (availableInputDevices.isEmpty()) {
        QSKIP("No audio input devices available for testing");
    }
    
    // Test that device name matching is case-sensitive
    QString firstDeviceName = availableInputDevices.first().deviceName();
    QString upperCaseName = firstDeviceName.toUpper();
    QString lowerCaseName = firstDeviceName.toLower();
    
    QAudioDeviceInfo originalResult = getAudioDevice(firstDeviceName);
    QAudioDeviceInfo upperResult = getAudioDevice(upperCaseName);
    QAudioDeviceInfo lowerResult = getAudioDevice(lowerCaseName);
    
    // Original should work
    QVERIFY(!originalResult.isNull());
    
    // Upper/lower case versions may or may not work depending on the device name
    // This test documents the current case-sensitive behavior
    if (upperCaseName != firstDeviceName) {
        // If the upper case version is different, it should not match
        QCOMPARE(upperResult.isNull(), upperCaseName != firstDeviceName);
    }
}

void TestAudioDeviceUtils::testGetAudioDevice_listAvailableDevices()
{
    // Test that we can get all available devices by name
    for (const QAudioDeviceInfo &device : availableInputDevices) {
        QAudioDeviceInfo result = getAudioDevice(device.deviceName());
        QVERIFY(!result.isNull());
        QCOMPARE(result.deviceName(), device.deviceName());
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    TestAudioDeviceUtils tc;
    return QTest::qExec(&tc, argc, argv);
}

#include "test_audiodeviceutils.moc"

