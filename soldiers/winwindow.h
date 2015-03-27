#ifndef WINWINDOW_H
#define WINWINDOW_H
#include "mainwindow.h"
#include <QWidget>

class MainWindow;

class winWindow : public QWidget
{
    Q_OBJECT

public:
    explicit winWindow(MainWindow *mw = 0);
    ~winWindow();

private:
    MainWindow *mainWindow;

private slots:
    void gotoMainMenu();
};


#endif // WINWINDOW_H
