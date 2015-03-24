#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QObject>
#include <QLabel>
#include <QMouseEvent>
class ClickableLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ClickableLabel( int row2, int col2, QWidget * parent = 0 );
    ~ClickableLabel();
    int row;
    int col;

signals:
   void clicked(int row3, int col3);
public slots:
    void mousePressEvent(QMouseEvent *event);
};

#endif // CLICKABLELABEL_H
