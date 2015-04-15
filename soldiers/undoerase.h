#ifndef UNDOERASE_H
#define UNDOERASE_H
#include <QUndoCommand>
#include "puzzlewindow.h"

using namespace std;
class puzzleWindow;

class undoErase : public QUndoCommand
{
public:
    undoErase(puzzleWindow *puz, int r, int c, int d, list<int> l, QUndoCommand *parent = 0);//(BoxImage *views, QVector<QPixmap> currentChanges, int sNum, int removeAll, QUndoCommand *parent = 0);
    void undo();
    void redo();

private:
    int row;
    int col;
    int data;
    puzzleWindow *puzzle;
    list<int> notesList;
};


#endif // UNDOERASE_H
