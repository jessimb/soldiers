#ifndef PUZZLEWINDOW_H
#define PUZZLEWINDOW_H
#include <QGridLayout>
#include <QPushButton>
#include "mainwindow.h"
#include <QWidget>
#include <QKeyEvent>
#include <string>
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
    void keyPressEvent(QKeyEvent* e);
    QPushButton *notebutton;


private:
    MainWindow *mainWindow;
    int s_row;
    int s_col;
    QGridLayout * lay;

private slots:
    void goBackToPuzzle();
public slots:
    void press(int row, int col);
    void button_pressed(int i);
    void showHint();
    void note();
};


#endif // PUZZLEWINDOW_H
