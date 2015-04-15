#include "undoerase.h"
//#include <QMessageBox>
#include <iostream>
using namespace std;
//int numb = -1;
undoErase::undoErase(puzzleWindow *puz, int r, int c, int d, std::list<int> l, QUndoCommand *parent)//(BoxImage *views, QVector<QPixmap> currentChanges, int sNum, int removeAlls, QUndoCommand *parent)
{
     cout << "undo created\n";
     row = r;
     col = c;
     puzzle = puz;
     data = d;
     notesList = l;
}

void undoErase::undo()
{
    cout << "  undo triggered\n";
    if(data != 0)
        puzzle->insertValue(row, col, data);
    else
        puzzle->insertNotes(row, col, notesList);
}

void undoErase::redo()
{
    cout <<" (re)do triggered\n";
    puzzle->eraseBox(row, col);

}


