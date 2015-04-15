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
#include "undoerase.h"
#include <QUndoStack>
#include <QAction>
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
    void resetPuzzle();
    char* load();
    int grid[9][9];
    bool clicked;
    int their_solution[9][9];
    int answer[9][9];
    int GridLength;
    int GridPos;
    int BoxLength;
    std::string oFile = "";
    std::list<int> notes[9][9];
    int hints[9][9];
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
    QPushButton * hint;
    void writeStats();
    QUndoStack *undoStack;
    QAction *undoAct;
    QAction *redoAct;

private:
    MainWindow *mainWindow;
    int s_row;
    int s_col;
    QGridLayout * lay;
    QString *styleDis;
    QString *styleDisEn;
    QString *style;
    void loadNotes();
    void loadHints();

private slots:
    void goBackToPuzzle();

public slots:
    void press(int row, int col);
    void button_pressed(int i);
    void showHint();
    void note();
    void eraseBox(int row, int col);
    void incrementTime();
    void eraseSlot();
    void insertValue(int r, int c, int d);
    void insertNotes(int r, int c, std::list<int> notes);
};


#endif // PUZZLEWINDOW_H
