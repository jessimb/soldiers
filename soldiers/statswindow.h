#ifndef STATSWINDOW_H
#define STATSWINDOW_H
#include "mainwindow.h"
#include <QWidget>

class MainWindow;

class statsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit statsWindow(MainWindow *mw = 0);
    ~statsWindow();

private:
    MainWindow *mainWindow;

private slots:
    void gotoMainMenu();
};

#endif // STATSWINDOW_H
