#include "statswindow.h"
#include <QLabel>

statsWindow::statsWindow(MainWindow *mw)
{

    mainWindow = mw;
    QGridLayout *buttonlayout = new QGridLayout;
    QString *style = new QString("QPushButton {font-family: \"Courier New\"; font-size: 20px; border:1px solid #000; border-radius: 15px;background-color: #f6f6f6; color:#0000FF; } QPushButton:pressed{background-color:#fff;}");

    this->setLayout(buttonlayout);
    QLabel *label = new QLabel("stats go here");
    buttonlayout->addWidget(label);

    QPushButton *back = new QPushButton("Main Menu");
    buttonlayout->addWidget(back);
    this->setStyleSheet("background-color:#FAFAD2;");
    back->setFixedSize(150, 45);
    back->setStyleSheet(*style);
    connect(back, SIGNAL(clicked()), this, SLOT(gotoMainMenu()));


}

void statsWindow::gotoMainMenu()
{
    stackedWidget->setCurrentIndex(0);
}
statsWindow::~statsWindow()
{

}

