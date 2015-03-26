#ifndef SAVELOAD_H
#define SAVELOAD_H

#include <QWidget>
class QUndoStack;
class QPushButton;
class QGridLayout;
class SaveLoad : public QWidget
{
    Q_OBJECT
public:
    SaveLoad(const char * d);
private:
    static const int boardSize=81;
    const char * board;
    void addWidgets();
    void initVars();
    void connectButtons();
    QGridLayout *layout;
    QPushButton * saveButton;
    QPushButton * loadButton;
    void testLoad(char *);
    ~SaveLoad();

public slots:
    void saveFile();
    char * loadFile();
};

#endif // SAVELOAD_H
