#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    // Set up the central widget and layout
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    setCentralWidget(centralWidget);

    // 1. Create the button
    m_toggleButton = new QPushButton("Toggle Feature", this);
    layout->addWidget(m_toggleButton, 0, Qt::AlignCenter); // Add button to layout and center it

    // 2. Initialize QGSettings for our schema
    // The schema ID must match the one in org.devv.example.button.gschema.xml
    m_gsettings = new QGSettings("org.devv.example.button");

    // 3. Connect button's clicked signal to a slot
    connect(m_toggleButton, &QPushButton::clicked, this, &MainWindow::onButtonClicked);

    // 4. Connect QGSettings' valueChanged signal to a slot
    // This slot will be called whenever the "is-enabled" key changes,
    // whether by our app or another GSettings client.
    connect(m_gsettings, &QGSettings::changed, this, &MainWindow::onGSettingValueChanged);

    // Initial update of the button text based on the current GSetting value
    updateButtonText();

    setWindowTitle("GSettings Button Example");
    resize(300, 150);
}

MainWindow::~MainWindow() {
    // QGSettings is parented to this, so it will be deleted automatically.
    // m_toggleButton is also parented to this, so it will be deleted automatically.
}

void MainWindow::onButtonClicked() {
    // Read the current value of "is-enabled"
    bool currentEnabled = m_gsettings->get("is-enabled").toBool();
    qDebug() << "Button clicked. Current 'is-enabled':" << currentEnabled;

    // Toggle the value
    m_gsettings->set("is-enabled", !currentEnabled);
    qDebug() << "Set 'is-enabled' to:" << !currentEnabled;

    // The onGSettingValueChanged slot will be automatically called due to the signal connection.
}

void MainWindow::onGSettingValueChanged(const QString &key) {
    // Check if the changed key is the one we are interested in
    if (key == "isEnabled") {
        qDebug() << "GSetting 'is-enabled' value changed.";
        updateButtonText(); // Update the button text to reflect the new state
    }
}

void MainWindow::updateButtonText() {
    bool isEnabled = m_gsettings->get("is-enabled").toBool();
    if (isEnabled) {
        m_toggleButton->setText("Feature: ENABLED (Click to Disable)");
    } else {
        m_toggleButton->setText("Feature: DISABLED (Click to Enable)");
    }
    qDebug() << "Button text updated to reflect: " << (isEnabled ? "ENABLED" : "DISABLED");
}
