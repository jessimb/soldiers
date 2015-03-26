#include "clickablelabel.h"
#include <iostream>
ClickableLabel::ClickableLabel( int row2, int col2, QWidget * parent ) :
    QLabel(parent)
{
 row = row2;
 col = col2;

}

ClickableLabel::~ClickableLabel()
{

}

void ClickableLabel::mousePressEvent ( QMouseEvent * event )
{
    (void) event;
    emit clicked(row, col);
}
