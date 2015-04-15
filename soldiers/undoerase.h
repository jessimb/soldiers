#ifndef UNDOERASE_H
#define UNDOERASE_H
#include <QUndoCommand>
#include "puzzlewindow.h"

class puzzleWindow;

class undoErase : public QUndoCommand
{
public:
    undoErase(puzzleWindow *puz, int r, int c, int d, QUndoCommand *parent = 0);//(BoxImage *views, QVector<QPixmap> currentChanges, int sNum, int removeAll, QUndoCommand *parent = 0);
    void undo();
    void redo();

private:
    int row;
    int col;
    int data;
    puzzleWindow *puzzle;
};


#endif // UNDOERASE_H
