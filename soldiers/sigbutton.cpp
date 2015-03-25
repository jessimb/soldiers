#include "sigbutton.h"

SigButton::SigButton(int i, QWidget *parent) : QPushButton(parent)
{
label = i;
QObject::connect(this, SIGNAL(clicked()), this, SLOT( onClick()));
}

SigButton::~SigButton()
{

}

void SigButton::onClick(){
    emit clicked(label);
}

