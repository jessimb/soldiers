#ifndef PUZZLEWINDOW_H
#define PUZZLEWINDOW_H
#include <QGridLayout>
#include <QPushButton>
#include "mainwindow.h"
#include <QWidget>
#include <QKeyEvent>

class MainWindow;

class puzzleWindow : public QWidget
{
    Q_OBJECT

public:
    explicit puzzleWindow(MainWindow *mw = 0,bool loadGame=false);
    ~puzzleWindow();
    void readFile();
    void makeGrid();
    void save();
    void checkVictory();
    void load();
    int grid[9][9];
    int their_solution[9][9];
    int answer[9][9];
    const int GridLength=540;
    const int GridPos=50;
    int BoxLength=GridLength/9;
    void keyPressEvent(QKeyEvent* e);

private:
    MainWindow *mainWindow;
    int s_row = -1;
    int s_col = -1;
    QGridLayout *lay = new QGridLayout();

private slots:
    void goBackToPuzzle();
public slots:
    void press(int row, int col);
    void button_pressed(int i);
};


#endif // PUZZLEWINDOW_H
