#include "leaderboardwindow.h"
#include <QLabel>

leaderboardWindow::leaderboardWindow(MainWindow *mw)
{

    mainWindow = mw;
    QGridLayout *buttonlayout = new QGridLayout;

    this->setLayout(buttonlayout);
    QLabel *label = new QLabel("leaderboard will be here");
    buttonlayout->addWidget(label);

    QPushButton *back = new QPushButton("Main Menu");
    buttonlayout->addWidget(back);
    this->setStyleSheet("background-color:#FAFAD2;");
    back->setFixedSize(150, 45);
    back->setStyleSheet("QPushButton {border:1px solid #000; border-radius: 15px;background-color: #f6f6f6; color:#0000FF; } QPushButton:pressed{background-color:#fff;}");


    connect(back, SIGNAL(clicked()), this, SLOT(gotoMainMenu()));


}

void leaderboardWindow::gotoMainMenu()
{
    stackedWidget->setCurrentIndex(0);
}
leaderboardWindow::~leaderboardWindow()
{

}

