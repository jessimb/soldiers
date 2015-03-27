#include "pausewindow.h"
#include <QLabel>

pauseWindow::pauseWindow(MainWindow *mw)
{
    mainWindow = mw;
    QGridLayout *buttonlayout = new QGridLayout;

    this->setLayout(buttonlayout);
    QLabel *label = new QLabel("game is paused");
    buttonlayout->addWidget(label);

    QPushButton *back = new QPushButton("Continue");
    buttonlayout->addWidget(back);
    this->setStyleSheet("background-color:#fff;");
    back->setFixedSize(150, 45);
    back->setStyleSheet("QPushButton {border:1px solid #000; border-radius: 15px;background-color: #f6f6f6;} QPushButton:pressed{background-color:#fff;}");

    QPushButton *end = new QPushButton("End");
    buttonlayout->addWidget(end);
    end->setFixedSize(150, 45);
    end->setStyleSheet("QPushButton {border:1px solid #000; border-radius: 15px;background-color: #f6f6f6;} QPushButton:pressed{background-color:#fff;}");

    QPushButton *save = new QPushButton("Save");
    buttonlayout->addWidget(save);
    save->setFixedSize(150, 45);
    save->setStyleSheet("QPushButton {border:1px solid #000; border-radius: 15px;background-color: #f6f6f6;} QPushButton:pressed{background-color:#fff;}");

    QPushButton *reset = new QPushButton("Reset Board");
    buttonlayout->addWidget(reset);
    reset->setFixedSize(150, 45);
    reset->setStyleSheet("QPushButton {border:1px solid #000; border-radius: 15px;background-color: #f6f6f6;} QPushButton:pressed{background-color:#fff;}");

    QPushButton *mainMenu = new QPushButton("Main Menu");
    buttonlayout->addWidget(mainMenu);
    mainMenu->setFixedSize(150, 45);
    mainMenu->setStyleSheet("QPushButton {border:1px solid #000; border-radius: 15px;background-color: #f6f6f6;} QPushButton:pressed{background-color:#fff;}");

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

