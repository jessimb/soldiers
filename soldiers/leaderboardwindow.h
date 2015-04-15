#ifndef LEADERBOARDWINDOW_H
#define LEADERBOARDWINDOW_H
#include "mainwindow.h"
#include <QWidget>
#include <QVector>
#include <QLabel>

class MainWindow;

class leaderboardWindow : public QWidget
{
    Q_OBJECT

public:
    explicit leaderboardWindow(MainWindow *mw = 0);
    ~leaderboardWindow();
    QVector<int> topscores;
    void TP();
    int one=0;
    int two=0;
    int three=0;
    QLabel *first = new QLabel;
    QLabel *second = new QLabel;
    QLabel *third = new QLabel;

private:
    MainWindow *mainWindow;

private slots:
    void gotoMainMenu();
};

#endif // LEADERBOARDWINDOW_H
