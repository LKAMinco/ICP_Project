#include "line.h"

Line::Line(QWidget *parent)
{

}

void Line::setPoints(QWidget *first, QWidget *last){
    start = first;
    end = last;
}

void Line::setPosition(){
    auto x1 = start->pos().x() + start->width() / 2;
    auto y1 = start->pos().y() + start->height() / 2;
    auto x2 = end->pos().x() + end->width() / 2;
    auto y2 = end->pos().y() + end->height() / 2;
    this->setLine(x1, y1, x2, y2);
    this->boundingRect();
}

void Line::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(event->buttons() == Qt::RightButton){
        qDebug() << "line";
    }
}
