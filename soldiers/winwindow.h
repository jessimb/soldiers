#ifndef WINWINDOW_H
#define WINWINDOW_H
#include "mainwindow.h"
#include <QWidget>
#include <QLabel>

class MainWindow;

class winWindow : public QWidget
{
    Q_OBJECT

public:
    explicit winWindow(MainWindow *mw = 0);
    ~winWindow();
    QLabel * scoreLabel;
    QGridLayout * buttonLayout;
    void updateScore();

private:
    MainWindow *mainWindow;

private slots:
    void gotoMainMenu();
};


#endif // WINWINDOW_H
