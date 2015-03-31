#include "instructionsmenu.h"
#include <QLabel>
#include <QScrollArea>

instructionsMenu::instructionsMenu(MainWindow *mw)
{

    QString *style = new QString("QPushButton {font-family: \"Courier New\"; font-size: 20px; border:1px solid #000; border-radius: 15px;background-color: #f6f6f6; color:#0000FF; } QPushButton:pressed{background-color:#fff;}");

    mainWindow = mw;
    QGridLayout *buttonlayout = new QGridLayout();
    this->setLayout(buttonlayout);
    QLabel *label = new QLabel("A sudoku puzzle is a grid of nine by nine squares or cells, \nthat has been subdivided into nine subgrids or \"regions\" of three by three cells. \n");
    QLabel *label2 = new QLabel("\nThe objective of sudoku is to enter a digit from 1 through 9 in each cell, in such a way that: \nEach horizontal row (shown in pink) contains each digit exactly once \nEach vertical column (shown in yellow) contains each digit exactly once \nEach subgrid or region (shown in green) contains each digit exactly once \nIn each sudoku puzzle, several digits have already been entered -- these may not be changed.\nThe puzzler\'s job is to fill the remainder of the grid with digits, respecting the three constraints mentioned earlier.");

    label->setWordWrap(true);
    label->setAlignment(Qt::AlignCenter);
    label2->setWordWrap(true);
    label2->setAlignment(Qt::AlignCenter);
    buttonlayout->addWidget(label, 0, 0);

    QLabel *img = new QLabel();
    QPixmap pixelMap = QPixmap(":/images/instrboard.png");
    QPixmap tempShrink = pixelMap.scaled(QSize(200,200),Qt::KeepAspectRatio);
    img->setPixmap(tempShrink);
    img->setAlignment(Qt::AlignCenter);
    buttonlayout->addWidget(img, 1, 0);
    buttonlayout->addWidget(label2, 2, 0);


    //layout = QVBoxLayout(scrollarea)
    //realmScroll.setWidget(layout.widget())


    QPushButton *back = new QPushButton("Main Menu");
    buttonlayout->addWidget(back, 3, 0, Qt::AlignCenter);
    this->setStyleSheet("background-color:#FAFAD2;");
    back->setFixedSize(150, 45);
    back->setStyleSheet(*style);

    connect(back, SIGNAL(clicked()), this, SLOT(gotoMainMenu()));


}

void instructionsMenu::gotoMainMenu()
{
    stackedWidget->setCurrentIndex(0);
}
instructionsMenu::~instructionsMenu()
{

}

