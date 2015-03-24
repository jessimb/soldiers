#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QGridLayout>
#include <QMouseEvent>
#include <QMainWindow>
#include <QChar>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QGridLayout *lay = new QGridLayout;
    void readFile();
    void makeGrid();
    int grid[9][9];
    const int GridLength=540;
    const int GridPos=50;
    int BoxLength=GridLength/9;

private:
    Ui::MainWindow *ui;
public slots:
    void press(int row, int col);
};

#endif // MAINWINDOW_H
