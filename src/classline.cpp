#include "classline.h"

ClassLine::ClassLine(QWidget *parent) : QWidget(parent)
{

}

void ClassLine::setPoints(QWidget *first, QWidget *last){
    start = first;
    end = last;
    qDebug() << start->pos();
    qDebug() << end->pos();

}
