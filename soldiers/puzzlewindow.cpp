#include "puzzlewindow.h"
#include <QLabel>
#include <QSplitter>
#include <Qfile>
#include <QTextStream>
#include "clickablelabel.h"
#include "sigbutton.h"
#include <iostream>
#include <QCoreApplication>
#include <sstream>
#include <qdir>
#include <algorithm>
#include <list>
#include "saveload.h"

using namespace std;
bool clicked = false;

puzzleWindow::puzzleWindow(MainWindow *mw, bool loadGame)
{

    mainWindow = mw;
    QGridLayout *buttonlayout = new QGridLayout;

    setFocusPolicy(Qt::ClickFocus);

   // this->setLayout(buttonlayout);
    QLabel *label = new QLabel("puzzle");
    this->setStyleSheet("background-color:#fafad2;");
    buttonlayout->addWidget(label);

    QPushButton *note = new QPushButton("Make a Note");

    QPushButton *hint = new QPushButton("Get Hint");
    QFont font2 = hint->font();
    font2.setPointSize(15);
    hint->setFont(font2);
    note->setFont(font2);
   // buttonlayout->addWidget(pause,0,1);
   hint->setStyleSheet("QPushButton {border:1px solid #000; border-radius: 15px;background-color: #f6f6f6;} QPushButton:pressed{background-color:#fff;}");
   note->setStyleSheet("QPushButton {border:1px solid #000; border-radius: 15px;background-color: #f6f6f6;} QPushButton:pressed{background-color:#fff;}");

note->setFixedSize(100,45);
    hint->setFixedSize(100,45);
    buttonlayout->addWidget(hint);

    QPushButton *pause = new QPushButton("Pause");
    QFont font = pause->font();
    font.setPointSize(15);
    pause->setFont(font);
   // buttonlayout->addWidget(pause,0,1);
    pause->setStyleSheet("QPushButton {border:1px solid #000; border-radius: 15px;background-color: #f6f6f6;} QPushButton:pressed{background-color:#fff;}");


    pause->setFixedSize(100, 45);

    connect(pause, SIGNAL(clicked()), this, SLOT(goBackToPuzzle()));
    connect(hint, SIGNAL(clicked()), this, SLOT(showHint()));

    QWidget *wid = new QWidget;
    wid->setLayout(lay);
    lay->setHorizontalSpacing(0);
    lay->setVerticalSpacing(0);
    if(!loadGame)
        readFile();
    else
        load();

    makeGrid();

    QSplitter *splitter = new QSplitter();
    QFrame *leftWidget = new QFrame();
    (void)leftWidget;
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
        button[i]->setMinimumSize(30,30);
        button[i]->setMaximumSize(30,30);
        button[i]->setStyleSheet("QPushButton {border:1px solid #000; border-radius: 10px;background-color: #f6f6f6;} QPushButton:pressed{background-color:#fff;}");

        std::stringstream ss2;
        ss2 << (i+1);
        QFont font = button[i]->font();
        font.setPointSize(15);
        button[i]->setText(QString::fromStdString(ss2.str()));
        button[i]->setFont(font);
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
    n->addWidget(splitter,0,0,1,3);
    n->addWidget(pause, 1,0);
    n->addWidget(hint, 1,1);
    n->addWidget(note,1,2);
    connect(note, SIGNAL(clicked()), this, SLOT(note()));
    this->setLayout(n);



}

void puzzleWindow::goBackToPuzzle()
{
    stackedWidget->setCurrentIndex(5);
}
puzzleWindow::~puzzleWindow()
{

}

void puzzleWindow::save(){
    char * file= new char [81*3];

    for(int x=0;x<9;x++)
    {
        for(int y=0;y<9;y++)
        {
            file[x*9+y]=(char)('0'+grid[x][y]);
            file[x*9+y+81]=(char)('0'+their_solution[x][y]);
            file[x*9+y+81*2]=(char)('0'+answer[x][y]);
        }
    }
    (*new SaveLoad(file,81*3)).saveFile();
}

void puzzleWindow::load(){
    char * file= (*new SaveLoad("Used only for Saving",0)).loadFile();

    for(int x=0;x<9;x++)
    {
        for(int y=0;y<9;y++)
        {
            grid[x][y]=file[x*9+y]-'0';
            their_solution[x][y]=file[x*9+y+81]-'0';
            answer[x][y]=file[x*9+y+81*2]-'0';
        }
    }

}

void puzzleWindow::readFile(){



    QFile file(":/maps/puzzleDatabase/e01.txt");
    if (file.open(QIODevice::ReadOnly))
    {

        QTextStream in(&file);
        for(int i = 0; i < 9; i++){
            QString line = in.readLine();

            for (int j = 0; j < 9; j++) {
                grid[i][j] = line.at(j).digitValue();
                their_solution[i][j] = line.at(j).digitValue();
            }
        }
        in.readLine();
        for(int i = 0; i < 9; i++){
            QString line = in.readLine();

            for(int j = 0; j < 9; j++){
                answer[i][j] = line.at(j).digitValue();
            }
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

                label->setText("<b><font size = 15>" + QString::number(grid[i][j]) + "</font></b>");
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
        if (clicked == false) {
            QLayoutItem *item = lay->itemAtPosition(s_row, s_col);
            if (lay) {
               QWidget * wid = item->widget();

               ClickableLabel* labell= static_cast<ClickableLabel*>(wid);
                int index2 = lay->indexOf(labell);
                if (index2 != -1) {
                    if (grid[s_row][s_col] == 0 && their_solution[s_row][s_col] == i){
                        labell->setText("");
                        their_solution[s_row][s_col] = 0;
                    } else if (grid[s_row][s_col] == 0) {
                        labell->setText("<font size=15 color='blue'>"+ QString::number(i) + "</font>");
                        their_solution[s_row][s_col] = i;
                    }
                }
            }
            checkVictory();
        } else { //tryna make a note
            QLayoutItem *item = lay->itemAtPosition(s_row, s_col);
            if (lay) {
               QWidget * wid = item->widget();
               ClickableLabel* labell= static_cast<ClickableLabel*>(wid);
                int index2 = lay->indexOf(labell);
                if (index2 != -1) {
                    if (grid[s_row][s_col] == 0 && std::find(notes[s_row][s_col].begin(), notes[s_row][s_col].end(), i) != notes[s_row][s_col].end()) {
                        QString text = "";
                        *(std::find(notes[s_row][s_col].begin(), notes[s_row][s_col].end(), i)) = 0;
                        int x = 1;
                        for (std::list<int>::const_iterator iterator = notes[s_row][s_col].begin(), end = notes[s_row][s_col].end(); iterator != end; ++iterator) {
                           if (*iterator != 0) {
                            text = text + QString::number(*iterator) + " ";
                           }
                           if (x%3 == 0 && x!=9) text = text + "<br>";
                           x++;
                        }
                        labell->setText("<font size=2 color='green'>"+ text + "</font>");
                    } else if (grid[s_row][s_col] == 0) {
                        notes[s_row][s_col].push_back(i);
                        QString text = "";
                        notes[s_row][s_col].sort();
                        int x = 1;
                        for (std::list<int>::const_iterator iterator = notes[s_row][s_col].begin(), end = notes[s_row][s_col].end(); iterator != end; ++iterator) {
                           if (*iterator != 0) {
                            text = text + QString::number(*iterator) + " ";
                           }
                           if (x%3 == 0 && x!=9) text = text + "<br>";
                           x++;
                        }
                        labell->setText("<font size=2 color='green'>"+ text + "</font>");

                    }
                }
            }
        }
    }
}

void puzzleWindow::checkVictory(){
    bool won = true;
//    cout << "Checking victory." << endl;
    for(int i = 0; i < 9 && won; i++){
        for(int j = 0; j < 9 && won; j++){
            if(answer[i][j] != their_solution[i][j]){
//                cout << "Failed on: row-" << i << " col-" << j << endl;
                won = false;
            }
        }
    }
    if(won){
        cout << "Congrats! You've won!" << endl;
    }
}

void puzzleWindow::keyPressEvent(QKeyEvent *e){
    //Checking for key presses: 1-9
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

    //Checking for key press: delete
    } else if(e->key() == Qt::Key_Delete){
        QLayoutItem * item = lay->itemAtPosition(s_row, s_col);
        if (lay) {
            QWidget * wid = item->widget();
            ClickableLabel* labell = static_cast<ClickableLabel*>(wid);
            int index2 = lay->indexOf(labell);
            if (index2 != -1) {
                if (grid[s_row][s_col] == 0 && their_solution[s_row][s_col] != 0){
                    labell->setText("");
                    their_solution[s_row][s_col] = 0;
                }
            }
        }
    }
}


void puzzleWindow::showHint(){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if (their_solution[i][j] == 0 && grid[i][j] == 0) {
                QLayoutItem * item = lay->itemAtPosition(i,j);
                if (lay) {
                    QWidget * wid = item->widget();
                    ClickableLabel* labell = static_cast<ClickableLabel*>(wid);
                    int index2 = lay->indexOf(labell);
                    if (index2 != -1) {
                        labell->setText("<b><font size = 15>" + QString::number(answer[i][j]) + "</font></b>");
                        their_solution[i][j] = answer[i][j];
                    }
                 return;
            }
        }
    }
    }
}

void puzzleWindow::note() {
    if (clicked == true) {
        clicked = false;
    } else {
        clicked = true;
    }
}
