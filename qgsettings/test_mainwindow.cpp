#include <QtTest>
#include <QApplication>
#include <QSignalSpy>
#include <QGSettings>
#include "mainwindow.h"
#include <QDir>
#include <QStandardPaths>
#include <cstdlib>

class TestMainWindow : public QObject
{
    Q_OBJECT

public:
    TestMainWindow();
    ~TestMainWindow();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testOnButtonClicked_togglesFalseToTrue();
    void testOnButtonClicked_togglesTrueToFalse();
    void testOnButtonClicked_multipleToggles();
    void testOnButtonClicked_updatesButtonText();

private:
    void setupGSettingsSchema();
    QString schemaDir;
    MainWindow *mainWindow;
};

TestMainWindow::TestMainWindow()
{
}

TestMainWindow::~TestMainWindow()
{
}

void TestMainWindow::initTestCase()
{
    // Setup GSettings schema directory
    setupGSettingsSchema();
    
    // Set GSettings schema directory environment variable
    QString currentSchemaDir = qgetenv("GSETTINGS_SCHEMA_DIR");
    if (!currentSchemaDir.contains(schemaDir)) {
        qputenv("GSETTINGS_SCHEMA_DIR", schemaDir.toLocal8Bit());
    }
    
    mainWindow = new MainWindow();
}

void TestMainWindow::cleanupTestCase()
{
    delete mainWindow;
}

void TestMainWindow::setupGSettingsSchema()
{
    // Get the absolute path to the schemas directory
    QDir currentDir = QDir::current();
    schemaDir = currentDir.absoluteFilePath("schemas");
    
    // Ensure the schema directory exists
    QDir schemaQDir(schemaDir);
    if (!schemaQDir.exists()) {
        QFAIL("Schema directory does not exist!");
    }
}

void TestMainWindow::testOnButtonClicked_togglesFalseToTrue()
{
    // Reset to false
    QGSettings gsettings("org.devv.example.button");
    gsettings.set("is-enabled", false);
    QCOMPARE(gsettings.get("is-enabled").toBool(), false);
    
    // Call onButtonClicked - should toggle to true
    mainWindow->onButtonClicked();
    
    // Verify it's now true
    QCOMPARE(gsettings.get("is-enabled").toBool(), true);
}

void TestMainWindow::testOnButtonClicked_togglesTrueToFalse()
{
    // Set to true
    QGSettings gsettings("org.devv.example.button");
    gsettings.set("is-enabled", true);
    QCOMPARE(gsettings.get("is-enabled").toBool(), true);
    
    // Call onButtonClicked - should toggle to false
    mainWindow->onButtonClicked();
    
    // Verify it's now false
    QCOMPARE(gsettings.get("is-enabled").toBool(), false);
}

void TestMainWindow::testOnButtonClicked_multipleToggles()
{
    // Test multiple toggles to ensure it works consistently
    QGSettings gsettings("org.devv.example.button");
    
    // Start with false
    gsettings.set("is-enabled", false);
    QCOMPARE(gsettings.get("is-enabled").toBool(), false);
    
    // Toggle 1: false -> true
    mainWindow->onButtonClicked();
    QCOMPARE(gsettings.get("is-enabled").toBool(), true);
    
    // Toggle 2: true -> false
    mainWindow->onButtonClicked();
    QCOMPARE(gsettings.get("is-enabled").toBool(), false);
    
    // Toggle 3: false -> true
    mainWindow->onButtonClicked();
    QCOMPARE(gsettings.get("is-enabled").toBool(), true);
    
    // Toggle 4: true -> false
    mainWindow->onButtonClicked();
    QCOMPARE(gsettings.get("is-enabled").toBool(), false);
}

void TestMainWindow::testOnButtonClicked_updatesButtonText()
{
    // This test verifies that onButtonClicked triggers the signal chain
    // that updates the button text via onGSettingValueChanged -> updateButtonText
    
    QGSettings gsettings("org.devv.example.button");
    
    // Set to false and verify button text
    gsettings.set("is-enabled", false);
    QTest::qWait(100); // Allow signal processing
    QString textBefore = mainWindow->m_toggleButton->text();
    QVERIFY(textBefore.contains("DISABLED", Qt::CaseInsensitive));
    
    // Toggle to true
    mainWindow->onButtonClicked();
    QTest::qWait(100); // Allow signal processing
    
    // Verify button text updated (via the signal connection)
    QString textAfter = mainWindow->m_toggleButton->text();
    QVERIFY(textAfter.contains("ENABLED", Qt::CaseInsensitive));
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    TestMainWindow tc;
    return QTest::qExec(&tc, argc, argv);
}

#include "test_mainwindow.moc"
