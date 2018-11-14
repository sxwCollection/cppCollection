#include "boxbutton.h"
#include "battleship_gui.h"
#include <iostream>


// constructor
BoxButton::BoxButton( int const & iCR_id1, int const & iCR_id2, QWidget *parent)  : QPushButton(parent)
{
    position[0] = iCR_id1;
    position[1] = iCR_id2;
	connect(this, SIGNAL(clicked()), this, SLOT(slotOnClick()));
}
BoxButton::~BoxButton()
{
    disconnect(this, SIGNAL(clicked()), this, SLOT(slotOnClick()));
}



void BoxButton::slotOnClick()
{
    //QPalette pal = palette();
    //pal.setColor(QPalette::Button, QColor(Qt::blue));
    //setAutoFillBackground(true);
    //setPalette(pal);

    //repaint();
    emit sigRelayClick(position[0], position[1]);	//TO: battleship.slotClickOnField(pt, row, col)
	return;
}




