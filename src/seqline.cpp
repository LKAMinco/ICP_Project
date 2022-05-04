#include "seqline.h"
#include <QDebug>
#include "seqentity.h"

SeqLine::SeqLine(QWidget *parent){
    x1 = 0;
    x2 = 0;
    y1 = 0;
    y2 = 0;
    this->setPen(QPen(Qt::black, 3));
    type = 0;
    startOffset = 0;
    endOffset = 0;
    rotate = 0;
    mouseOffset = 100;
    markerOffset = 0;
    this->setZValue(1);
    box = nullptr;
}

SeqLine::~SeqLine(){

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

void SeqLine::setMarkers(QGraphicsPolygonItem *fu, QGraphicsPolygonItem *ar, QGraphicsPolygonItem *b1, QGraphicsPolygonItem *b2, QComboBox *cbox){
    full = fu;
    arrow = ar;
    blue1 = b1;
    blue2 = b2;

    full->setVisible(true);
    arrow->setVisible(false);
    box = cbox;
}

void SeqLine::setPosition(){
    setPoints(start, end);
    y1 = start->pos().y() + mouseOffset;
    if(type == 3)
        y1 += 48;

    y2 = y1;


    if(y2 < end->pos().y())
        y2 = end->pos().y();
    if(y2 > end->pos().y() + end->height() - 10)
        y2 = end->pos().y() + end->height() - 10;

    if(y1 > start->pos().y() + 85)
        startOffset = -87;
    else
        startOffset = 0;

    if(type == 3 && y2 < end->pos().y() + 85 + 48)
        y2 = end->pos().y() + 85 + 48;

    if(y2 > end->pos().y() + 85){
        endOffset = 87;
        blue2->setVisible(true);
        markerOffset = 0;
    }
    else{
        endOffset = 0;
        blue2->setVisible(false);
        markerOffset = 5;
    }

    x1 = start->pos().x() + start->width() + startOffset;
    x2 = end->pos().x() + endOffset;
    this->setLine(x1, y1, x2, y2);

    full->setPos(x2 - 16 + markerOffset, y2);

    if(type == 3){
        arrow->setPos(x1 + 16, y1);
        arrow->setRotation(180);
        blue1->setPos(x1 - 3,y1 - 24);
        blue2->setPos(x2 + 3,y2 - 24);
    }
    else{
        arrow->setPos(x2 - 16 + markerOffset, y2);
        arrow->setRotation(0);
        blue1->setPos(x1 - 3,y1 + 24);
        blue2->setPos(x2 + 3,y2 + 24);
    }
    box->move((x2 + x1)/2 - box->width()/2, (y1 + y2)/2 - 35);

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
        if ((event->pos().y() > start->pos().y() + 85) && (event->pos().y() < start->pos().y() + start->height() - 58)){
            mouseOffset = event->pos().y() - start->pos().y();
            setPosition();
        }
    }
}

//Function changes color of the line and its markers
void SeqLine::changeColor(Qt::GlobalColor color){
    this->setPen(QPen(color, 3));
    full->setPen(QPen(color, 3));
    full->setBrush(QBrush(color));
    arrow->setPen(QPen(color, 3));
}

void SeqLine::changeType(){
    type = (type + 1) % 4;
    switch(type){
        case 0:
            full->setVisible(true);
            arrow->setVisible(false);
            this->setPen(QPen(Qt::red, 3, Qt::SolidLine));
            break;
        case 1:
            full->setVisible(false);
            arrow->setVisible(true);
            this->setPen(QPen(Qt::red, 3, Qt::SolidLine));
            break;
        case 2:
            full->setVisible(false);
            arrow->setVisible(true);
            this->setPen(QPen(Qt::red, 3, Qt::DashLine));
            break;
        case 3:
            full->setVisible(false);
            arrow->setVisible(true);
            this->setPen(QPen(Qt::red, 3, Qt::DashLine));
            break;
        default:
            break;
    }
    setPosition();
}

void SeqLine::deleteMarkers(){
    delete full;
    delete arrow;
    delete blue1;
    delete blue2;
}

void SeqLine::updateData(ClassStorage *info){
    //start
}
