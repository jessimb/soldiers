#include "undodel.h"
#include <iostream>
using namespace std;
undoDel::undoDel(puzzleWindow *puz, int r, int c, int d, std::list<int> list, bool comm, QUndoCommand *parent)//(BoxImage *views, QVector<QPixmap> currentChanges, int sNum, int removeAlls, QUndoCommand *parent)
{

    cout << "undo created\n";
    row = r;
    col = c;
    puzzle = puz;
    data = d;
    l = list;
    isComm = comm;
}


void undoDel::undo()
{
    cout << "  undo triggered\n";
cout<<row<<" test1 "<<col<<endl;
        if (!isComm) {

            puzzle->addNum(row, col, data);

        } else {
            puzzle->addCom(row, col, data);
        }

}

void undoDel::redo()
{
cout<<row<<" test2 "<<col<<endl;
        if (!isComm) {
            puzzle->delNum(row, col, data);
            cout<<row<<" "<<col<<" "<<data<<endl;
        } else {
            puzzle->delCom(row, col, data);
        }



}


