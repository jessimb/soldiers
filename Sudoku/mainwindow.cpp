#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <Qfile>
#include <QTextStream>
#include <iostream>
#include <QPainter>
#include <QLabel>
#include <QRect>
#include <QFrame>
#include <clickablelabel.h>

int s_row = -1;
int s_col = -1;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget *wid = new QWidget;
    wid->setLayout(lay);
    lay->setHorizontalSpacing(0);
    lay->setVerticalSpacing(0);
    this->setCentralWidget(wid);
    readFile();
    makeGrid();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readFile(){
    QFile file("/Users/phoebemirman/Desktop/Sudoku/map.txt");
    if (file.open(QIODevice::ReadOnly))
    {

        QTextStream in(&file);
        int z = 0;
        while(!in.atEnd()) {
            QString line = in.readLine();

            for (int i = 0; i < 9; i++) {
                grid[z][i] = line.at(i).digitValue();
            }
            z++;
        }

    }

    file.close();
}
void MainWindow::makeGrid() {
    QRect rec2(GridPos,GridPos,GridLength,GridLength);
    lay->setGeometry(rec2);

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {

            QLabel *label;

            if (grid[i][j] != 0) {
                label = new QLabel();
                label->setText(QString::number(grid[i][j]));
            } else {
                label = new ClickableLabel(i,j);
                QObject::connect(label, SIGNAL(clicked(int, int)), this, SLOT(press(int, int)));
            }

            QRect rec(i*BoxLength+GridPos,j*BoxLength+GridPos,BoxLength, BoxLength);
            label->setAlignment(Qt::AlignCenter);

            label->setStyleSheet("border: 1px solid");
            if (i%3 == 0 && i != 0) {
                label->setStyleSheet("border: 1px solid; border-top: 2px solid; border-top-color: #00246B");
            }
            if (j%3 == 0 && j != 0) {
                label->setStyleSheet("border: 1px solid; border-left: 2px solid; border-left-color: #00246B");
            }
            if (j%3 == 0 && j != 0 && i%3 == 0 && i != 0) {
                label->setStyleSheet("border: 1px solid; border-top: 2px solid; border-left: 2px solid; border-top-color: #00246B; border-left-color: #00246B");
            }

            label->setGeometry(rec);
            lay->addWidget(label, i, j);

        }
    }
}

void MainWindow::press(int row, int col){
    QLayoutItem *item = lay->itemAtPosition(row, col);
    if (lay) {
       QWidget * wid = item->widget();

       ClickableLabel* labell= static_cast<ClickableLabel*>(wid);
        int index2 = lay->indexOf(labell);
        if (index2 != -1) {
        labell->setStyleSheet("border: 3px solid yellow");

        }

    }

    if (s_row != -1 && s_col != -1) {
        QLayoutItem *lay2 = lay->itemAtPosition(s_row, s_col);
        QWidget * wid = lay2->widget();
        ClickableLabel* label= static_cast<ClickableLabel*>(wid);
        int index = lay->indexOf(label);



        if (index != -1) {
            int i = s_row;
            int j = s_col;
            label->setStyleSheet("border: 1px solid");
            if (i%3 == 0 && i != 0) {
                label->setStyleSheet("border: 1px solid; border-top: 2px solid; border-top-color: #00246B");
            }
            if (j%3 == 0 && j != 0) {
                label->setStyleSheet("border: 1px solid; border-left: 2px solid; border-left-color: #00246B");
            }
            if (j%3 == 0 && j != 0 && i%3 == 0 && i != 0) {
                label->setStyleSheet("border: 1px solid; border-top: 2px solid; border-left: 2px solid; border-top-color: #00246B; border-left-color: #00246B");
            }

        }
    }
    s_row = row;
    s_col = col;

}
