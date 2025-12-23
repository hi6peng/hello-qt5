#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

#include <QProcessEnvironment>
#include <QDebug>
#include <QX11Info>

int main(int argc, char *argv[]) {
    // Create the QApplication object
    QApplication app(argc, argv);

    qDebug() << "Qt version:" << QT_VERSION_STR;

    qDebug() << "DISPLAY:" << QProcessEnvironment::systemEnvironment().value("DISPLAY");

    // APIs common to Qt 4 and Qt 5.1
    int screen = QX11Info::appScreen();
    qDebug() << "Screen:" << QX11Info::appScreen();
    qDebug() << "DPI X:" << QX11Info::appDpiX(screen);
    qDebug() << "DPI Y:" << QX11Info::appDpiY(screen);
    qDebug() << "Root window handle:" << QX11Info::appRootWindow(screen);
    qDebug() << "Time:" << QX11Info::appTime();
    qDebug() << "User time:" << QX11Info::appUserTime();
    qDebug() << "Display:" << QX11Info::display();

    // Qt 5.1 APIs
    #if QT_VERSION >= 0x050100
        qDebug() << "XCB connection:" << QX11Info::connection();
    #endif

    // Qt 4 APIs
    #if QT_VERSION < 0x050000
        qDebug() << "Cells:" << QX11Info::appCells(screen);
        qDebug() << "Class:" << QX11Info::appClass();
        qDebug() << "Color map:" << QX11Info::appColormap(screen);
        qDebug() << "Default color map:" << QX11Info::appDefaultColormap(screen);
        qDebug() << "Default visual:" << QX11Info::appDefaultVisual(screen);
        qDebug() << "Depth:" << QX11Info::appDepth(screen);
        qDebug() << "Visual:" << QX11Info::appVisual(screen);
        qDebug() << "Is composite manager running?"
            << QX11Info::isCompositingManagerRunning();
    #endif

    // Create a main window widget
    QWidget window;
    window.setWindowTitle("QtApplication Demo");

    // Create a vertical layout
    QVBoxLayout *layout = new QVBoxLayout;

    // Add a label
    QLabel *label = new QLabel("Hello, CMake and Qt5!", &window);
    layout->addWidget(label);

    // Add a button
    QPushButton *button = new QPushButton("Click Me", &window);
    // Connect the button's clicked signal to the application's quit slot
    QObject::connect(button, &QPushButton::clicked, &app, &QApplication::quit);
    layout->addWidget(button);

    // Set the layout for the window
    window.setLayout(layout);

    // Resize and show the window
    window.resize(300, 150);
    window.show();

    // Start the application event loop
    return app.exec();
}
