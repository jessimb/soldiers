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
    SaveLoad(const char *);
    static const int boardSize=81*4+9*9*9;//+9*81;
private:

    const char * board;

    void initVars();

    int size;
    void testLoad(char *);
    ~SaveLoad();

public slots:
    void saveFile();
    char * loadFile();
};

#endif // SAVELOAD_H
