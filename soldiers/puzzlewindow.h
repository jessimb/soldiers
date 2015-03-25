#ifndef PUZZLEWINDOW_H
#define PUZZLEWINDOW_H
#include <QGridLayout>
#include <QPushButton>
#include "mainwindow.h"
#include <QWidget>

class MainWindow;

class puzzleWindow : public QWidget
{
    Q_OBJECT

public:
    explicit puzzleWindow(MainWindow *mw = 0);
    ~puzzleWindow();

private:
    MainWindow *mainWindow;

private slots:
    void gotoMainMenu();
};


#endif // PUZZLEWINDOW_H
