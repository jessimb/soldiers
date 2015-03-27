#include "saveload.h"
#include <fstream>
#include <iostream>
#include <QUndoStack>
#include <QFileDialog>
#include <QPushButton>
#include <QGridLayout>

using namespace std;

SaveLoad::SaveLoad(const char * information,int bsize)
{

    board=information;
    boardSize=bsize;

    initVars();
    connectButtons();
    addWidgets();


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
    filename = QFileDialog::getOpenFileName(this, "Save Game",QDir::homePath(), tr("SudokuGames (*.sudoku)"));
    if(!filename.isNull())
    {

        ifstream stream(filename.toStdString().c_str());

        stream.read(&data[0],boardSize);
        stream.close();
    }

    testLoad(data);


    return data;

}

void SaveLoad::addWidgets()
{
    layout->addWidget(saveButton);
    layout->addWidget(loadButton);
}

void SaveLoad::connectButtons()
{
    connect(saveButton,SIGNAL(clicked()),this,SLOT(saveFile()));
    connect(loadButton,SIGNAL(clicked()),this,SLOT(loadFile()));
}

void SaveLoad::initVars()
{
    layout = new QGridLayout(this);
    saveButton=new QPushButton("Save",this);
    loadButton=new QPushButton("Load",this);
}

