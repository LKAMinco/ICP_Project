#include "seqline.h"
#include <QDebug>
#include "seqentity.h"

SeqLine::SeqLine(QWidget *parent){
    x1 = 0;
    x2 = 0;
    y1 = 0;
    y2 = 0;
    this->setPen(QPen(Qt::black, 2));
    type = 0;
    offset = 14;
    curOffset = 0;
    lineOffset = 0;
    rotate = 0;
}

void SeqLine::changeType(){
    qDebug() << "test";
}

void SeqLine::setPoints(SeqEntity *first, SeqEntity *last){
    if(first->pos().x() < last->pos().x()){
        start = first;
        end = last;
    }
    else{
        start = last;
        end = first;
    }
}

void SeqLine::setMarkers(QGraphicsPolygonItem *fu, QGraphicsPolygonItem *ar, QGraphicsPolygonItem *b1, QGraphicsPolygonItem *b2){
    full = fu;
    arrow = ar;
    blue1 = b1;
    blue2 = b2;
}

void SeqLine::setPosition(){
    x1 = start->pos().x();
    y1 = start->pos().y();
    x2 = end->pos().x();
    y2 = end->pos().y();
    this->setLine(x1, y1, x2, y2);
}
