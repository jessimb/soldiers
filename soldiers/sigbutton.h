#ifndef SIGBUTTON_H
#define SIGBUTTON_H
#include <QPushButton>
#include <QObject>

class SigButton : public QPushButton
{
    Q_OBJECT
public:
    explicit SigButton(int i, QWidget *parent = 0);
    ~SigButton();
    int label;

signals:
    void clicked(int);
public slots:
    void onClick();
};

#endif // SIGBUTTON_H
