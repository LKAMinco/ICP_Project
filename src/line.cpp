#include "line.h"
#include "classentity.h"

Line::Line(QWidget *parent)
{

}

void Line::setPoints(QWidget *first, QWidget *last){
    start = first;
    end = last;
}

void Line::setPosition(){
    /*auto x1 = start->pos().x() + start->width() / 2;
    auto y1 = start->pos().y() + start->height() / 2;
    auto x2 = end->pos().x() + end->width() / 2;
    auto y2 = end->pos().y() + end->height() / 2;*/
    int x1, x2, y1, y2;
    if(abs(start->pos().x() - end->pos().x()) > abs(start->pos().y() - end->pos().y())){
       if(start->pos().x() - end->pos().x() < 0){
           x1 = start->pos().x() + start->width();
           x2 = end->pos().x();
       }
       else{
           x1 = start->pos().x();
           x2 = end->pos().x() + end->width();
       }
       y1 = start->pos().y() + start->height() / 2;
       y2 = end->pos().y() + end->height() / 2;
    }
    else{
        if(start->pos().y() - end->pos().y() < 0){
            y1 = start->pos().y() + start->height();
            y2 = end->pos().y();
        }
        else{
            y1 = start->pos().y();
            y2 = end->pos().y() + end->height();
        }
        x1 = start->pos().x() + start->width() / 2;
        x2 = end->pos().x() + end->width() / 2;
    }
    this->setLine(x1, y1, x2, y2);
    this->boundingRect();
}

void Line::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(event->buttons() == Qt::RightButton){
        qobject_cast<ClassEntity*>(start)->curScene->lastLine = this;
        //QPen pens(Qt::DashLine);
        //this->setPen(pens);
    }
}
