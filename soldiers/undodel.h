#ifndef UNDODEL_H
#define UNDODEL_H
#include <QUndoCommand>
#include "puzzlewindow.h"

class undoDel : public QUndoCommand
{
public:
    undoDel(puzzleWindow *puz, int r, int c, int d, std::list<int> list, bool comm, QUndoCommand *parent = 0);//(BoxImage *views, QVector<QPixmap> currentChanges, int sNum, int removeAll, QUndoCommand *parent = 0);
    void undo();
    void redo();

private:
    int row;
    int col;
    int data;
    std::list<int> l;
    bool isComm;
    puzzleWindow *puzzle;
};

#endif // UNDODEL_H

