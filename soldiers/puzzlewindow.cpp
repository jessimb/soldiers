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
#include <limits.h>
#include "saveload.h"
#include "mainmenu.h"
#include <unordered_map>
#include "undoadd.h"
#include "undodel.h"
using namespace std;
extern QString globalUser;
extern unordered_map<string, statsfunc*> users;

puzzleWindow::puzzleWindow(MainWindow *mw, std::string file,bool loadGame)
{
    for(int x=0;x<9;x++)
    {
        for(int y=0;y<9;y++)
            hints[x][y]=0;
    }
    GridLength = 540;
    GridPos = 50;
    clicked = false;
    BoxLength = GridLength/9;
    lay = new QGridLayout();
    s_row = -1;
    s_col = -1;
    oFile = file;
    time = 0;
    h = 0;
    m = 0;
    s = 0;
    numHints = 0;
    mainWindow = mw;
    QGridLayout *buttonlayout = new QGridLayout;

    undoStack = new QUndoStack(this);
    undoAct = undoStack->createUndoAction(this, tr("&Undo"));
    undoAct->setShortcuts(QKeySequence::Undo);
    undoAct->setStatusTip(tr("Undo the last operation"));
    redoAct = undoStack->createRedoAction(this, tr("&Redo"));
    redoAct->setShortcuts(QKeySequence::Redo);
    redoAct->setStatusTip(tr("Redo the last operation"));

    addAction(undoAct);
    addAction(redoAct);

    style = new QString("QPushButton {font-family: \"Courier New\"; font-size: 20px; border:1px solid #000; border-radius: 15px;background-color: #f6f6f6; color:#0000FF; } QPushButton:pressed{background-color:#fff;}");
    styleDis = new QString("QPushButton {font-family: \"Courier New\"; font-size: 10px; border:1px solid #000; border-radius: 15px;background-color: #f6f6f6; color:#0000FF} QPushButton:pressed{background-color:#fff;}");
    styleDisEn = new QString("QPushButton {font-family: \"Courier New\"; font-size: 20px; border:1px solid #000; border-radius: 15px;background-color: #f6f6f6; color:#d3d3d3} QPushButton:pressed{background-color:#fff;}");
    QString *numStyle = new QString("QPushButton {font-family: \"Courier New\"; font-size: 20px; border:1px solid #000; border-radius: 10px;background-color: #f6f6f6; color:#0000FF; } QPushButton:pressed{background-color:#fff;}");

    setFocusPolicy(Qt::ClickFocus);

    // this->setLayout(buttonlayout);
    QLabel *label = new QLabel("puzzle");
    this->setStyleSheet("background-color:#fafad2;");
    buttonlayout->addWidget(label);

    timeLabel = new QLabel("00:00:00");

    notebutton = new QPushButton("Add Note");
    undoButton = new QPushButton();
    redoButton = new QPushButton();

    QPixmap pixelMapUn = QPixmap(":/images/arrrow-left.png");
    QPixmap tempShrinkUn = pixelMapUn.scaled(QSize(150,30),Qt::KeepAspectRatio);
    QIcon ButtonIcon(tempShrinkUn);
    undoButton->setIcon(ButtonIcon);
    undoButton->setIconSize(tempShrinkUn.rect().size());
    undoButton->setStyleSheet(*numStyle);

    QPixmap pixelMapRe = QPixmap(":/images/arrow-right.png");
    QPixmap tempShrinkRe = pixelMapRe.scaled(QSize(150,30),Qt::KeepAspectRatio);
    QIcon ButtonIcon2(tempShrinkRe);
    redoButton->setIcon(ButtonIcon2);
    redoButton->setIconSize(tempShrinkRe.rect().size());
    redoButton->setStyleSheet(*numStyle);


    hint = new QPushButton("Get Hint\nAdds " + QString::number(60*5*numHints) + " seconds");
    QFont font2 = hint->font();
    font2.setPointSize(15);
    timeLabel->setFont(font2);
    hint->setFont(font2);
    notebutton->setFont(font2);
    hint->setStyleSheet(*styleDis);
    notebutton->setStyleSheet(*style);

    notebutton->setFixedSize(120,45);
    hint->setFixedSize(120,45);
    buttonlayout->addWidget(hint);

    erase = new QPushButton("Erase");
    erase->setFont(font2);
    erase->setStyleSheet(*style);
    erase->setFixedSize(120, 45);
    erase->setEnabled(false);

    QPushButton *pause = new QPushButton("Pause");
    QFont font = pause->font();
    font.setPointSize(15);
    pause->setFont(font);
    pause->setStyleSheet(*style);

    pause->setFixedSize(120, 45);

    connect(pause, SIGNAL(clicked()), this, SLOT(goBackToPuzzle()));
    connect(hint, SIGNAL(clicked()), this, SLOT(showHint()));
    connect(erase, SIGNAL(clicked()), this, SLOT(eraseSlot()));
    connect(undoButton, SIGNAL(clicked()), this, SLOT(undoSlot()));
    connect(redoButton, SIGNAL(clicked()), this, SLOT(redoSlot()));

    QWidget *wid = new QWidget;
    wid->setLayout(lay);
    lay->setHorizontalSpacing(0);
    lay->setVerticalSpacing(0);
    bool broken = false;

    if(loadGame)
    {
        const char * valid = load();
        if(valid==0)
        {
            broken = true;
        }
    }
    else
        readFile();

    if(broken){
        stackedWidget->setCurrentIndex(0);
        stackedWidget->show();
        cout << stackedWidget->currentIndex() << endl;
    } else {
        makeGrid();
        if (loadGame) {
            loadNotes();
            loadHints();
        }

        QSplitter *splitter = new QSplitter();
        QFrame *leftWidget = new QFrame();
        (void)leftWidget;
        QGridLayout *leftLayout = new QGridLayout();

        wid->setStyleSheet("QFrame { background-color: rgb(219, 226, 228); }");



        QFrame *innerWidget = new QFrame();
        QGridLayout *innerLayout = new QGridLayout();
        innerWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        innerWidget->setLayout(innerLayout);
        innerLayout->addWidget(undoButton, 0, 0);
        innerLayout->addWidget(redoButton, 1, 0);
        SigButton *button[9];
        for (int i=0;i<9;i++)
        {
            button[i] = new SigButton(i+1);
            button[i]->setMinimumSize(30,30);
            button[i]->setMaximumSize(30,30);
            button[i]->setStyleSheet(*numStyle);

            std::stringstream ss2;
            ss2 << (i+1);
            QFont font = button[i]->font();
            font.setPointSize(15);
            button[i]->setText(QString::fromStdString(ss2.str()));
            button[i]->setFont(font);
            innerLayout->addWidget(button[i],i+2,0);
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
        n->addWidget(splitter,0,0,1,5);
        n->addWidget(pause, 1,0);
        n->addWidget(hint, 1,1);
        n->addWidget(notebutton,1,2);
        n->addWidget(erase,1,3);
        n->addWidget(timeLabel,1,4);
        connect(notebutton, SIGNAL(clicked()), this, SLOT(note()));
        this->setLayout(n);

        clock = new QTimer();

        clock->start(1000);
        connect(clock, SIGNAL(timeout()), this, SLOT(incrementTime()));

    }
}
void puzzleWindow::undoSlot()
{

    undoAct->trigger();
}

void puzzleWindow::redoSlot()
{
    redoAct->trigger();
}

void puzzleWindow::resetPuzzle()
{
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {


            if (i != -1 && j != -1) {
                QLayoutItem *item = lay->itemAtPosition(i, j);
                if (their_solution[i][j] != 0 && grid[i][j] == 0) {
                    their_solution[i][j] = 0;
                    if (item) {
                        QWidget * wid = item->widget();
                        ClickableLabel* labell= static_cast<ClickableLabel*>(wid);
                        labell->setText("");
                        cout << "reseting\n";
                    }
                }
                if (notes[i][j].size() != 0) {
                    notes[i][j].clear();
                    if (item) {
                        QWidget * wid = item->widget();
                        ClickableLabel* labell= static_cast<ClickableLabel*>(wid);
                        labell->setText("");
                    }
                }
                check_erase(i,j);
                undoStack->clear();
            }
        }
    }
    numHints = 0;
    hint->setText("Get Hint\nAdds " + QString::number(60*5*numHints) + " seconds");

}

void puzzleWindow::goBackToPuzzle()
{
    cout << "In puzzleWindow::goBackToPuzzle (Which is terrible naming conventions cause its going to pausewindow). Is pause always index 5?" << endl;
    clock->stop();
    time = -1;
    incrementTime();
    stackedWidget->setCurrentIndex(5);
}

puzzleWindow::~puzzleWindow()
{

}

void puzzleWindow::loadNotes()
{
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (notes[i][j].size() != 0) {
                QLayoutItem * item = lay->itemAtPosition(i,j);
                if (lay) {
                    QWidget * wid = item->widget();
                    ClickableLabel* labell = static_cast<ClickableLabel*>(wid);
                    QString text = "";
                    notes[i][j].sort();
                    int x = 1;
                    for (std::list<int>::const_iterator iterator = notes[i][j].begin(), end = notes[i][j].end(); iterator != end; ++iterator) {
                        if (*iterator != 0) {
                            text = text + QString::number(*iterator) + " ";
                            if (x%3 == 0 && x!=9) text = text + "<br>";
                            x++;
                        }

                    }
                    labell->setText("<font size=2 color='green'>"+ text + "</font>");                }
            }
        }
    }
}

void puzzleWindow::loadHints()
{
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (hints[i][j]!=0) {
                QLayoutItem * item = lay->itemAtPosition(i,j);
                if (lay) {
                    QWidget * wid = item->widget();
                    ClickableLabel* labell = static_cast<ClickableLabel*>(wid);
                    labell->setText("<b><font size = 15 color = 'black'>" + QString::number(hints[i][j]) + "</font></b>");
                }
            }
        }
    }
}

void puzzleWindow::eraseSlot()
{
    undoStack->push(new undoErase(this, s_row, s_col, their_solution[s_row][s_col], notes[s_row][s_col]));

}


void puzzleWindow::addNum(int row, int col, int i){
    if (notes[row][col].size() != 0) {
        notes[row][col].clear();
    }
    QLayoutItem *item = lay->itemAtPosition(row, col);
    if (lay) {
        QWidget * wid = item->widget();

        ClickableLabel* labell= static_cast<ClickableLabel*>(wid);
        labell->setText("<font size=15 color='blue'>"+ QString::number(i) + "</font>");
    }
    their_solution[row][col] = i;
    check_erase(row,col);
}


void puzzleWindow::delNum(int row, int col, int i){
    QLayoutItem *item = lay->itemAtPosition(row, col);

    if (lay) {

        QWidget * wid = item->widget();

        ClickableLabel* labell= static_cast<ClickableLabel*>(wid);
        labell->setText("");
    }
    their_solution[row][col] = 0;
    check_erase(row,col);

}

void puzzleWindow::addCom(int row, int col, int i){
    if (their_solution[row][col] != 0) {
        their_solution[row][col] = 0;
    }
    notes[row][col].push_back(i);
    QString text = "";
    notes[row][col].sort();
    int x = 1;
    for (std::list<int>::const_iterator iterator = notes[row][col].begin(), end = notes[row][col].end(); iterator != end; ++iterator) {
        if (*iterator != 0) {
            text = text + QString::number(*iterator) + " ";
            if (x%3 == 0 && x!=9) text = text + "<br>";
            x++;
        }

    }
    QLayoutItem *item = lay->itemAtPosition(row, col);
    if (lay) {
        QWidget * wid = item->widget();

        ClickableLabel* labell= static_cast<ClickableLabel*>(wid);
        labell->setText("<font size=2 color='green'>"+ text + "</font>");
    }
    check_erase(row,col);
}

void puzzleWindow::delCom(int row, int col, int i){
    QString text = "";
    notes[row][col].erase((std::find(notes[row][col].begin(), notes[row][col].end(), i)));
    notes[row][col].sort();
    int x = 1;
    for (std::list<int>::const_iterator iterator = notes[row][col].begin(), end = notes[row][col].end(); iterator != end; ++iterator) {
        if (*iterator != 0) {
            text = text + QString::number(*iterator) + " ";
            if (x%3 == 0 && x!=9) text = text + "<br>";
            x++;
        }

    }
    QLayoutItem *item = lay->itemAtPosition(row, col);
    if (lay) {
        QWidget * wid = item->widget();

        ClickableLabel* labell= static_cast<ClickableLabel*>(wid);
        labell->setText("<font size=2 color='green'>"+ text + "</font>");
    }
    check_erase(row,col);
}

void puzzleWindow::insertValue(int r, int c, int d)
{
    their_solution[r][c] = d;
    QLayoutItem *item = lay->itemAtPosition(r, c);

    if (item) {
        QWidget * wid = item->widget();
        ClickableLabel* labell= static_cast<ClickableLabel*>(wid);
        labell->setText("<font size = 15 color = 'blue'>" + QString::number(d) + "</font>");
    }

}

void puzzleWindow::insertNotes(int r, int c, list<int> noteList)
{
    notes[r][c] = noteList;
    QLayoutItem *item = lay->itemAtPosition(r, c);

    if (item) {
        QWidget * wid = item->widget();
        ClickableLabel* labell= static_cast<ClickableLabel*>(wid);

        //int index2 = lay->indexOf(labell);

        /* if (grid[r][c] == 0 && hints[r][c] == 0 && std::find(notes[r][c].begin(), notes[r][c].end(), i) != notes[r][c].end()) { //going to delete note
            QString text = "";
            notes[r][c].erase((std::find(notes[r][c].begin(), notes[r][c].end(), i)));
            notes[r][c].sort();
            int x = 1;
            for (std::list<int>::const_iterator iterator = notes[r][c].begin(), end = notes[r][c].end(); iterator != end; ++iterator) {
                if (*iterator != 0) {
                    text = text + QString::number(*iterator) + " ";
                    if (x%3 == 0 && x!=9) text = text + "<br>";
                    x++;
                }

            }
            labell->setText("<font size=2 color='green'>"+ text + "</font>");
        } else */if (grid[r][c] == 0 && hints[r][c] == 0) {
            if (their_solution[r][c] != 0) {
                their_solution[r][c] = 0;
            }
            //notes[r][c].push_back(i);
            QString text = "";
            notes[r][c].sort();
            int x = 1;
            for (std::list<int>::const_iterator iterator = notes[r][c].begin(), end = notes[r][c].end(); iterator != end; ++iterator) {
                if (*iterator != 0) {
                    text = text + QString::number(*iterator) + " ";
                    if (x%3 == 0 && x!=9) text = text + "<br>";
                    x++;
                }

            }
            labell->setText("<font size=2 color='green'>"+ text + "</font>");

        }

    }

}

void puzzleWindow::eraseBox(int row, int col) {
    if (row != -1 && col != -1) {
        QLayoutItem *item = lay->itemAtPosition(row, col);
        if (their_solution[row][col] != 0) {
            their_solution[row][col] = 0;
            if (item) {
                QWidget * wid = item->widget();
                ClickableLabel* labell= static_cast<ClickableLabel*>(wid);
                labell->setText("");
            }
        }
        if (notes[row][col].size() != 0) {
            notes[row][col].clear();
            if (item) {
                QWidget * wid = item->widget();
                ClickableLabel* labell= static_cast<ClickableLabel*>(wid);
                labell->setText("");
            }
        }
        check_erase(row,col);
    }
}

void puzzleWindow::save(){
    char * file= new char [SaveLoad::boardSize];

    for(int x=0;x<9;x++)
    {
        for(int y=0;y<9;y++)
        {

            file[x*9+y]=(char)('0'+grid[x][y]);
            file[x*9+y+81]=(char)('0'+their_solution[x][y]);
            cout<<their_solution[x][y]<<endl;
            file[x*9+y+81*2]=(char)('0'+answer[x][y]);
            file[x*9+y+81*3]=(char)('0'+hints[x][y]);
            for(int i=0;i<9;i++)
            {
                int storedvalue=0;
                for(list<int>::iterator it =notes[x][y].begin();it!=notes[x][y].end();it++)
                {

                    if(i==*it)
                    {
                        storedvalue=1;
                    }
                }
                file[(x*9+y)*9+81*4+i]=(char)('0'+storedvalue);
            }
        }
    }
    (*new SaveLoad(file)).saveFile();
}

char * puzzleWindow::load(){
    char * file= (*new SaveLoad("Used only for Saving")).loadFile();
    if(file==0)
        return 0;
    for(int x=0;x<9;x++)
    {
        for(int y=0;y<9;y++)
        {

            grid[x][y]=file[x*9+y]-'0';
            their_solution[x][y]=file[x*9+y+81]-'0';
            answer[x][y]=file[x*9+y+81*2]-'0';
            hints[x][y]=file[x*9+y+81*3]-'0';
            for(int i=0;i<9;i++)
            {
                int a= file[(x*9+y)*9+81*4+i]-'0';
                if(a>0)
                    notes[x][y].push_back(i);

            }
        }
    }

    return file;

}

void puzzleWindow::readFile(){


    string s = ":/maps/puzzleDatabase/" + oFile;
    std::cout<<s<<std::endl;
    QFile file(QString::fromStdString(s));
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
            else if (their_solution[i][j] != 0) {

                label->setText("<b><font size = 15 color = 'blue'>" + QString::number(their_solution[i][j]) + "</font></b>");
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
void puzzleWindow::check_erase(int row, int col){
    if (grid[row][col] == 0 && hints[row][col] == 0 && their_solution[row][col] == 0 && notes[row][col].size() == 0 ) {

        erase->setEnabled(false);
        erase->setStyleSheet(*styleDisEn);

    } else if (grid[row][col] != 0 ) {
        erase->setEnabled(false);
        erase->setStyleSheet(*styleDisEn);

    } else if (hints[row][col] != 0){
        erase->setEnabled(false);
        erase->setStyleSheet(*styleDisEn);

    } else {
        erase->setEnabled(true);
        erase->setStyleSheet(*style);

    }
}

void puzzleWindow::press(int row, int col){
    check_erase(row, col);
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
    std::list<int> list;
    if (s_row != -1 && s_col != -1) {
        if (clicked == false) {
            QLayoutItem *item = lay->itemAtPosition(s_row, s_col);
            if (lay) {
                QWidget * wid = item->widget();

                ClickableLabel* labell= static_cast<ClickableLabel*>(wid);
                int index2 = lay->indexOf(labell);
                if (index2 != -1) {
                    list.clear();
                    if (grid[s_row][s_col] == 0 && hints[s_row][s_col] == 0 && their_solution[s_row][s_col] == i){ //trying to remove
                        undoStack->push(new undoDel(this, s_row, s_col, i, list, false));
                    } else if (grid[s_row][s_col] == 0 && hints[s_row][s_col] == 0) { //trying to add number
                        undoStack->push(new undoAdd(this, s_row, s_col, i, list, false)); //bool at end 1 means they are adding
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
                    if (grid[s_row][s_col] == 0 && hints[s_row][s_col] == 0 && std::find(notes[s_row][s_col].begin(), notes[s_row][s_col].end(), i) != notes[s_row][s_col].end()) { //going to delete note
                        undoStack->push(new undoDel(this, s_row, s_col, i, notes[s_row][s_col], true));
                    } else if (grid[s_row][s_col] == 0 && hints[s_row][s_col] == 0) {
                        undoStack->push(new undoAdd(this, s_row, s_col, i, notes[s_row][s_col], true)); //bool at end 1 means they are adding
                    }
                }
            }

        }
        check_erase(s_row,s_col);
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
        clock->stop();
        cout << "Congrats! You've won! Your score was - " << INT_MAX/time << "!" << endl;
        stackedWidget->setCurrentIndex(6);
        cout<<"Global "<<globalUser.toStdString()<<" user"<<endl;
        if(globalUser.toStdString()!="")
        {

            auto winner = users.find(globalUser.toStdString());
            if(winner == users.end())
            {
                statsfunc * newprof= new statsfunc(globalUser);
                newprof->bestTime=time;
                newprof->highScore=INT_MAX/time;
                cout<<"prepre "<<newprof->bestTime<<endl;
                newprof->statsfunction(INT_MAX/time,time);
                cout<<"prebestTime "<<newprof->bestTime<<endl;
                users.insert(pair<string,statsfunc*>(globalUser.toStdString(),newprof));

            }
            else
            {

                winner->second->statsfunction(INT_MAX/time,time);
            }
            cout<<"calling write stats\n";
            writeStats();
            mainWindow->statsWindowObj->updatestats(globalUser);
            mainWindow->leaderboardWindowObj->TP();
        }


        cout << "Ctrl+f 'NEEDS TO BE FIXED'" << endl;
        //        Janky and needs to be fixed.
        static_cast<winWindow*>(stackedWidget->currentWidget())->scoreLabel = new QLabel("<font size = 30 color = blue> You win! Your score was " + QString::number(INT_MAX/time) + "!</font>");
        static_cast<winWindow*>(stackedWidget->currentWidget())->updateScore();
    }

}

void puzzleWindow::keyPressEvent(QKeyEvent *e){
    //Checking for key presses: 1-9
    if(e->text().toInt() > 0 && e->text().toInt() < 10){
        button_pressed(e->text().toInt());

        //Checking for key presses: <,^,>,v arrows
    } else if(e->key() == Qt::Key_Up && s_row > 0 && s_row < 9){
        press(s_row-1, s_col);
    } else if(e->key() == Qt::Key_Down && s_row > -1 && s_row < 8){
        press(s_row+1, s_col);
    } else if(e->key() == Qt::Key_Left && s_col > 0 && s_col < 9){
        press(s_row, s_col-1);
    } else if(e->key() == Qt::Key_Right && s_col > -1 && s_col < 8){
        press(s_row, s_col+1);

        //Checking for key press: delete
    } else if(e->key() == Qt::Key_Backspace || e->key() == Qt::Key_Delete){
        if (hints[s_row][s_col] == 0 && grid[s_row][s_col] == 0) eraseBox(s_row,s_col);
    }
}


void puzzleWindow::showHint(){
    int i = rand()%9;
    int j = rand()%9;
    int x = 0;
    while ((their_solution[i][j] != 0 || grid[i][j] != 0) && x < 163) {
        i = rand()%9;
        j = rand()%9;
        x++;
    }
    if (their_solution[i][j] == 0 && grid[i][j] == 0) {
        QLayoutItem * item = lay->itemAtPosition(i,j);
        if (lay) {
            QWidget * wid = item->widget();
            ClickableLabel* labell = static_cast<ClickableLabel*>(wid);
            int index2 = lay->indexOf(labell);
            if (index2 != -1) {
                labell->setText("<b><font size = 15>" + QString::number(answer[i][j]) + "</font></b>");
                their_solution[i][j] = answer[i][j];

                hints[i][j] = answer[i][j];
                notes[i][j].clear();
                time += 60*5*numHints++;
                hint->setText("Get Hint\nAdds " + QString::number(60*5*numHints) + " seconds");
                checkVictory();
            }
            return;
        }
    }
}

void puzzleWindow::note() {

    QString *newstyle = new QString("QPushButton {font-family: \"Courier New\"; font-size: 20px; border:1px solid #000; border-radius: 15px;background-color: #ADD8E6; color:#0000FF; } QPushButton:pressed{background-color:#fff;}");

    if (clicked == true) {
        clicked = false;
        notebutton->setStyleSheet(*style);
    } else {
        notebutton->setStyleSheet(*newstyle);
        clicked = true;
    }
}

void puzzleWindow::writeStats()
{
    statsWindow::writeStats();
}

void puzzleWindow::incrementTime(){
    time++;
    s = time % 60;
    m = time / 60 % 60;
    h = time / (60*60);
    QString hStr = QString("%1").arg(h,2,10,QChar('0'));
    QString mStr = QString("%1").arg(m,2,10,QChar('0'));
    QString sStr = QString("%1").arg(s,2,10,QChar('0'));
    //    cout << time << endl;
    timeLabel->setText(hStr + ":" + mStr + ":" + sStr);
    if(time < 0){
        cout << "Wraparound error." << endl;
    }
}
