#ifndef BOX_BUTTON_H
#define BOX_BUTTON_H

#include <QtWidgets/QPushButton>
#include <QtCore/QEvent>


class BoxButton : public QPushButton {
   Q_OBJECT

public:
    int position[2];

    BoxButton(int const & iCR_id1, int const & iCR_id2, QWidget *parent=NULL);	// constructor
    ~BoxButton();


public slots:
    void slotOnClick();


signals:
    void sigRelayClick( int row, int col); //

};

#endif
