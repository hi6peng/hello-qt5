# hello-qt5

## audiodevice


sudo apt-get install qtmultimedia5-dev

qmake .
make

## qgsettings

~~~
$ sudo apt-get install libgsettings-qt-dev
$ dpkg -l libgsettings-qt-dev
ii  libgsettings-qt-dev:arm64 0.2-1
~~~


Run glib-compile-schemas . (or glib-compile-schemas schemas if the XML is in a schemas subdirectory).


~~~
$ qmake -project "QT += widgets" "CONFIG += c++11 link_pkgconfig" "PKGCONFIG += gsettings-qt"
$ qmake
$ make
#$ XDG_DATA_DIRS=$PWD/schemas:$XDG_DATA_DIRS ./GSettingsButtonExample
$ GSETTINGS_SCHEMA_DIR=$PWD/schemas:$GSETTINGS_SCHEMA_DIR ./GSettingsButtonExample
~~~

The behavior you are observing is intentional in QGSettings. The QGSettings::changed(const QString &key) signal converts the schema's kebab-case (hyphen-separated) key names into camelCase (e.g., is-enabled becomes isEnabled) when emitted. 
This is by design to follow standard Qt naming conventions for signals and properties, which generally use camelCase. When connecting to the changed signal, you should expect to receive the key name in camelCase.

### Solution

When handling the changed(const QString &key) signal in your code, you must use the camelCase version of the key name.
For example, if your GSettings schema has the key is-enabled, you should connect to the signal and check for isEnabled in your slot:


~~~
connect(gSettings, &QGSettings::changed, this, &MyObject::handleSettingChanged);

// ...

void MyObject::handleSettingChanged(const QString &key)
{
    if (key == "isEnabled") { // Check for the camelCase key name
        // Handle the change for the "is-enabled" setting
        bool enabled = gSettings->value("is-enabled").toBool(); // Access using schema name
        // ...
    }
}
~~~

You can still use the original kebab-case name ("is-enabled") when calling other QGSettings methods like value(), setValue(), etc., as the class handles the internal mapping between the schema's format and Qt's format. 
