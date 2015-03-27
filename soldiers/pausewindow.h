#ifndef PAUSEWINDOW_H
#define PAUSEWINDOW_H
#include "mainwindow.h"
#include <QWidget>

class MainWindow;

class pauseWindow : public QWidget
{
    Q_OBJECT

public:
    explicit pauseWindow(MainWindow *mw = 0);
    ~pauseWindow();

private:
    MainWindow *mainWindow;

private slots:
    void goBackToPuzzle();
};

#endif // PAUSEWINDOW_H


