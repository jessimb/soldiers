#ifndef INSTRUCTIONSMENU_H
#define INSTRUCTIONSMENU_H
#include "mainwindow.h"
#include <QWidget>

class MainWindow;

class instructionsMenu : public QWidget
{
    Q_OBJECT

public:
    explicit instructionsMenu(MainWindow *mw = 0);
    ~instructionsMenu();

private:
    MainWindow *mainWindow;

private slots:
    void gotoMainMenu();
};

#endif // INSTRUCTIONSMENU_H
