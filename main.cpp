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

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);
  qDebug() << "Hello World!";
  return a.exec(); // .exec starts QApplication and related GUI, this line starts 'event loop'    
}
#endif
