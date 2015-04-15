#ifndef UNDOADD_H
#define UNDOADD_H
#include <QUndoCommand>
#include "puzzlewindow.h"

class undoAdd : public QUndoCommand
{
public:
    undoAdd(puzzleWindow *puz, int r, int c, int d, std::list<int> list, bool comm, QUndoCommand *parent = 0);//(BoxImage *views, QVector<QPixmap> currentChanges, int sNum, int removeAll, QUndoCommand *parent = 0);
    void undo();
    void redo();

private:
    int row;
    int col;
    int data;
    std::list<int> l;
    bool adds;
    bool isComm;
    puzzleWindow *puzzle;
};

#endif // UNDOADD_H

