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

SeqLine::~SeqLine(){

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

void SeqLine::setPosition(bool move){
    setPoints(start, end);
    x1 = start->pos().x();
    x2 = end->pos().x();
    if(!move){
        y1 = start->pos().y();
        y2 = end->pos().y();
    }
    this->setLine(x1, y1, x2, y2);
}

//Function handles mouse press event -> selects entity
void SeqLine::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(event->buttons() == Qt::RightButton){
        if (qobject_cast<SeqEntity*>(start)->curScene->lastLine != nullptr)
            qobject_cast<SeqEntity*>(start)->curScene->lastLine->changeColor(Qt::black);
        this->changeColor(Qt::red);
        qobject_cast<SeqEntity*>(start)->curScene->lastLine = this;
    }
}

void SeqLine::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if(event->buttons() == Qt::LeftButton)
    {
        int diff = y2-y1; //rework so it does work when moving objects
        //needs to calculate relative position of mouse to start and end of higher located entity
        y1 = event->pos().y();
        y2 = event->pos().y() + diff;
        setPosition(true);
    }
}

//Function changes color of the line and its markers
void SeqLine::changeColor(Qt::GlobalColor color){
    this->setPen(QPen(color, 2));
    //compos->setPen(QPen(color, 2));
    //compos->setBrush(QBrush(color));
    //aggreg->setPen(QPen(color, 2));
    //gener->setPen(QPen(color, 2));
}
