#include "puzzlewindow.h"
#include <QLabel>
#include <QSplitter>
#include <Qfile>
#include <QTextStream>
#include <clickablelabel.h>
#include "sigbutton.h"
#include <iostream>
#include <sstream>

using namespace std;

puzzleWindow::puzzleWindow(MainWindow *mw)
{

    mainWindow = mw;
    QGridLayout *buttonlayout = new QGridLayout;

    setFocusPolicy(Qt::ClickFocus);

   // this->setLayout(buttonlayout);
    QLabel *label = new QLabel("puzzle");
    buttonlayout->addWidget(label);

    QPushButton *back = new QPushButton("Go Back");
    buttonlayout->addWidget(back);


    connect(back, SIGNAL(clicked()), this, SLOT(gotoMainMenu()));

    QWidget *wid = new QWidget;
    wid->setLayout(lay);
    lay->setHorizontalSpacing(0);
    lay->setVerticalSpacing(0);
    readFile();
    makeGrid();

    QSplitter *splitter = new QSplitter();
    QFrame *leftWidget = new QFrame();
    QGridLayout *leftLayout = new QGridLayout();

    wid->setStyleSheet("QFrame { background-color: rgb(219, 226, 228); }");

    QFrame *innerWidget = new QFrame();
   QGridLayout *innerLayout = new QGridLayout();
   innerWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    innerWidget->setLayout(innerLayout);

    SigButton *button[9];
    for (int i=0;i<9;i++)
      {
        button[i] = new SigButton(i+1);
        button[i]->setMinimumSize(50,50);
        button[i]->setMaximumSize(50,50);
        std::stringstream ss2;
        ss2 << (i+1);
        button[i]->setText(QString::fromStdString(ss2.str()));
        innerLayout->addWidget(button[i],i,0);
        connect(button[i],SIGNAL(clicked(int)), this, SLOT(button_pressed(int)));
      }

    leftLayout->addWidget(innerWidget,0,0, Qt::AlignTop);
    splitter->addWidget(wid);
    splitter->addWidget(innerWidget);

    QList<int> list;
    list.push_back(560);
    list.push_back(70);
    splitter->setSizes(list);
    QGridLayout *n = new QGridLayout();
    n->addWidget(splitter);
    n->addWidget(back);

    this->setLayout(n);



}

void puzzleWindow::gotoMainMenu()
{
    stackedWidget->setCurrentIndex(0);
}
puzzleWindow::~puzzleWindow()
{

}


void puzzleWindow::readFile(){
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
void puzzleWindow::makeGrid() {
    QRect rec2(GridPos,GridPos,GridLength,GridLength);
    lay->setGeometry(rec2);

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {

            ClickableLabel *label = new ClickableLabel(i,j);
            QObject::connect(label, SIGNAL(clicked(int, int)), this, SLOT(press(int, int)));


            if (grid[i][j] != 0) {

                label->setText(QString::number(grid[i][j]));
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


void puzzleWindow::press(int row, int col){
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

void puzzleWindow::button_pressed(int i){
    if (s_row != -1 && s_col != -1) {
        QLayoutItem *item = lay->itemAtPosition(s_row, s_col);
        if (lay) {
           QWidget * wid = item->widget();

           ClickableLabel* labell= static_cast<ClickableLabel*>(wid);
            int index2 = lay->indexOf(labell);
            cout << "before " << endl;
            if (index2 != -1) {
                cout << "index2 " << grid[s_row][s_col] << endl;
                if (grid[s_row][s_col] == 0 && their_solution[s_row][s_col] == i){
                    cout << "second" << endl;
                    labell->setText("");
                    their_solution[s_row][s_col] = 0;
                } else if (grid[s_row][s_col] == 0) {
                    cout << "first" << endl;
                    labell->setText("<font color='blue'>"+ QString::number(i) + "</font>");
                    their_solution[s_row][s_col] = i;
                }
            }
        }
    }
}

void puzzleWindow::keyPressEvent(QKeyEvent *e){
    //Checking for key presses 1-9
    if(e->text().toInt() > 0 && e->text().toInt() < 10){
        button_pressed(e->text().toInt());
    //Checling for key presses: <,^,>,v arrows
    } else if(e->key() == Qt::Key_Up && s_row > 0 && s_row < 9){
        press(s_row-1, s_col);
    } else if(e->key() == Qt::Key_Down && s_row > -1 && s_row < 8){
        press(s_row+1, s_col);
    } else if(e->key() == Qt::Key_Left && s_col > 0 && s_col < 9){
        press(s_row, s_col-1);
    } else if(e->key() == Qt::Key_Right && s_col > -1 && s_col < 8){
        press(s_row, s_col+1);
    }
}
