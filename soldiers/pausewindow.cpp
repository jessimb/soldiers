#include "pausewindow.h"
#include <QLabel>

pauseWindow::pauseWindow(MainWindow *mw)
{
    mainWindow = mw;
    QGridLayout *buttonlayout = new QGridLayout;
    QString *style = new QString("QPushButton {font-family: \"Courier New\"; font-size: 20px; border:1px solid #000; border-radius: 15px;background-color: #f6f6f6; color:#0000FF; } QPushButton:pressed{background-color:#fff;}");

    this->setLayout(buttonlayout);
    QLabel *label = new QLabel("Game is Paused.");
    label->setAlignment(Qt::AlignCenter);
    buttonlayout->addWidget(label);

    QPushButton *back = new QPushButton("Continue");
    buttonlayout->addWidget(back);
    this->setStyleSheet("background-color:#FAFAD2;");
    back->setFixedSize(150, 45);
    back->setStyleSheet(*style);

    QPushButton *end = new QPushButton("End");
    buttonlayout->addWidget(end);
    end->setFixedSize(150, 45);
    end->setStyleSheet(*style);

    QPushButton *save = new QPushButton("Save");
    buttonlayout->addWidget(save);
    save->setFixedSize(150, 45);
    save->setStyleSheet(*style);

    QPushButton *reset = new QPushButton("Reset Board");
    buttonlayout->addWidget(reset);
    reset->setFixedSize(150, 45);
    reset->setStyleSheet(*style);

    QPushButton *mainMenu = new QPushButton("Main Menu");
    buttonlayout->addWidget(mainMenu);
    mainMenu->setFixedSize(150, 45);
    mainMenu->setStyleSheet(*style);

    connect(back, SIGNAL(clicked()), this, SLOT(goBackToPuzzle()));
    connect(end, SIGNAL(clicked()), this, SLOT(endToMainMenu()));
    connect(save, SIGNAL(clicked()), this, SLOT(saveStay()));
    connect(reset, SIGNAL(clicked()), this, SLOT(resetToPuzzle()));
    connect(mainMenu, SIGNAL(clicked()), this, SLOT(goBackToMainMenu()));


}

void pauseWindow::goBackToPuzzle()
{
    stackedWidget->setCurrentIndex(7);
}

void pauseWindow::goBackToMainMenu()
{
    //should ask if you want to save changes
    stackedWidget->setCurrentIndex(0);
}
void pauseWindow::endToMainMenu()
{
    //should probably ask if you want to save or that things will be discarded
    //i'm thinking a QDialoge - JB
    stackedWidget->setCurrentIndex(0);
}
void pauseWindow::saveStay()
{
    mainWindow->puzzleWindowObj->save();
    //do whatever we need to do save then dont change screens??
}
void pauseWindow::resetToPuzzle()
{
    //reload the puzzle. probably should ask if wants to save
    stackedWidget->setCurrentIndex(7);
}

pauseWindow::~pauseWindow()
{

}

