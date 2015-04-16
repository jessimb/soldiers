#include "saveload.h"
#include <fstream>
#include <iostream>
#include <QUndoStack>
#include <QFileDialog>
#include <QPushButton>
#include <QGridLayout>

using namespace std;

SaveLoad::SaveLoad(const char * information)
{

    board=information;





}

SaveLoad::~SaveLoad()
{

}

void SaveLoad::saveFile()
{

    QString filename;
    filename = QFileDialog::getSaveFileName(this, "Save Game",QDir::homePath(), tr("SudokuGames (*.sudoku)"));
    if(!filename.isNull())
    {
        ofstream stream(filename.toStdString().c_str(),std::ios::binary | std::ios::out);
            stream.write(board,boardSize);
        stream.close();
    }
}

void SaveLoad::testLoad(char * values)
{

    for(int x=0;x<boardSize;x++)
    {
        cout<<values[x]<<endl;
    }
}

char * SaveLoad::loadFile()
{
    char * data=new char[boardSize];
    QString filename;
    filename = QFileDialog::getOpenFileName(this, "Load Game",QDir::homePath(), tr("SudokuGames (*.sudoku)"));
    if(!filename.isNull())
    {

        ifstream stream(filename.toStdString().c_str());

        stream.read(&data[0],boardSize);
        stream.close();
    }
    else
    {
        return NULL;
    }




    return data;

}





