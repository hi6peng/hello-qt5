#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGSettings>
#include <QVBoxLayout>
#include <QWidget>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onButtonClicked();
    void onGSettingValueChanged(const QString &key);
    void updateButtonText();

private:
    QPushButton *m_toggleButton;
    QGSettings *m_gsettings;

    // Expose m_toggleButton for testing
    friend class TestMainWindow;
};

#endif // MAINWINDOW_H
