#ifndef NEWGAMEMENU_H
#define NEWGAMEMENU_H
#include <QGridLayout>
#include <QPushButton>
#include "mainwindow.h"
#include <QWidget>

class MainWindow;

class newGameMenu : public QWidget
{
    Q_OBJECT

public:
    explicit newGameMenu(MainWindow *mw = 0);
    ~newGameMenu();

private:
    MainWindow *mainWindow;

private slots:
    void gotoMainMenu();
    void gotoPuzzleWindow(int l);
};

#endif // NEWGAMEMENU_H
