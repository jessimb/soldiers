#ifndef PUZZLEWINDOW_H
#define PUZZLEWINDOW_H
#include <QGridLayout>
#include <QPushButton>
#include "mainwindow.h"
#include <QWidget>
#include <QKeyEvent>
#include <string>
#include <QTimer>
#include <QLabel>
class MainWindow;

class puzzleWindow : public QWidget
{
    Q_OBJECT

public:
    explicit puzzleWindow(MainWindow *mw = 0,std::string file="",bool loadgame=false);
    ~puzzleWindow();
    void readFile();
    void makeGrid();
    void save();
    void checkVictory();
    char* load();
    int grid[9][9];
    int their_solution[9][9];
    int answer[9][9];
    int GridLength;
    int GridPos;
    int BoxLength;
    std::string oFile = "";
    std::list<int> notes[9][9];
    int hints[9][9] = {{0}};
    int numHints;
    void keyPressEvent(QKeyEvent* e);
    QPushButton *notebutton;
    QPushButton *erase;
    void check_erase(int row, int col);
    QTimer * clock;
    QLabel * timeLabel;
    int time;
    int h;
    int m;
    int s;

private:
    MainWindow *mainWindow;
    int s_row;
    int s_col;
    QGridLayout * lay;
    QString *styleDis;
    QString *style;

private slots:
    void goBackToPuzzle();

public slots:
    void press(int row, int col);
    void button_pressed(int i);
    void showHint();
    void note();
    void eraseBox();
    void incrementTime();
};


#endif // PUZZLEWINDOW_H
