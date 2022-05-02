#include "line.h"
#include "classentity.h"

Line::Line(QWidget *parent)
{
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

Line::~Line(){
}

//Function sets start and end point of line
void Line::setPoints(ClassEntity *first, ClassEntity *last){
    start = first;
    end = last;
}

//Function updates position of line and its markers
void Line::setPosition(){
    //compares on which axis are entities more distant
    if(abs(start->pos().x() - end->pos().x()) > abs(start->pos().y() - end->pos().y())){
       //if x axis distance is greater
       //markers will be either on left or right side of the entity
       //checks if start position is position closer to the beginnig of the scene
       if(start->pos().x() - end->pos().x() < 0){
           x1 = start->pos().x() + start->width();
           x2 = end->pos().x() - lineOffset;
           curOffset = -offset;
           rotate = 0;
       }
       else{
           x1 = start->pos().x();
           x2 = end->pos().x() + end->width() + lineOffset;
           curOffset = offset;
           rotate = 180;
       }
       y1 = start->pos().y() + start->height() / 2;
       y2 = end->pos().y() + end->height() / 2;

       aggreg->setPos(x2 - curOffset,y2);
       compos->setPos(x2 - curOffset,y2);
       gener->setPos(x2 - curOffset,y2);
    }
    //if y axis distance is greater
    //markers will be either on top or bottom of the entity
    else{
        //checks if start entity is higher in the scene
        if(start->pos().y() - end->pos().y() < 0){
            y1 = start->pos().y() + start->height();
            y2 = end->pos().y() - lineOffset;
            curOffset = -offset;
            rotate = 90;
        }
        else{
            y1 = start->pos().y();
            y2 = end->pos().y() + end->height() + lineOffset;
            curOffset = offset;
            rotate = 270;
        }
        x1 = start->pos().x() + start->width() / 2;
        x2 = end->pos().x() + end->width() / 2;

        aggreg->setPos(x2,y2 - curOffset);
        compos->setPos(x2,y2 - curOffset);
        gener->setPos(x2,y2 - curOffset);
    }
    this->setLine(x1, y1, x2, y2);
    this->boundingRect();

    aggreg->setRotation(rotate);
    compos->setRotation(rotate);
    gener->setRotation(rotate);
}

//Function sets pointers to markers
void Line::setMarkers(QGraphicsPolygonItem *ag, QGraphicsPolygonItem *co, QGraphicsPolygonItem *ge){
    aggreg = ag;
    compos = co;
    gener = ge;

    aggreg->setVisible(false);
    compos->setVisible(false);
    gener->setVisible(false);
}

//Function changes type of line, updates visibility of markers and offsets
void Line::changeType(){
    type = (type + 1)%4;
    switch(type){
        case 0:
            compos->setVisible(false);
            aggreg->setVisible(false);
            gener->setVisible(false);
            offset = 0;
            lineOffset = 0;
            break;
        case 1:
            compos->setVisible(true);
            aggreg->setVisible(false);
            gener->setVisible(false);
            offset = 12;
            lineOffset = 25;
            break;
        case 2:
            compos->setVisible(false);
            aggreg->setVisible(true);
            gener->setVisible(false);
            offset = 12;
            lineOffset = 25;
            break;
        case 3:
            compos->setVisible(false);
            aggreg->setVisible(false);
            gener->setVisible(true);
            offset = 0;
            lineOffset = 13;
            break;
        default:
            break;
    }
    setPosition();
}

//Function changes color of the line and its markers
void Line::changeColor(Qt::GlobalColor color){
    this->setPen(QPen(color, 2));
    compos->setPen(QPen(color, 2));
    compos->setBrush(QBrush(color));
    aggreg->setPen(QPen(color, 2));
    gener->setPen(QPen(color, 2));
}

//Function removes all markers
//Cannot be in destructor -> caused segfault upon closing the app
void Line::deleteMarkers(){
    delete compos;
    delete aggreg;
    delete gener;
}

//Function handles mouse press event -> selects entity
void Line::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(event->buttons() == Qt::RightButton){
        if (qobject_cast<ClassEntity*>(start)->curScene->lastLine != nullptr)
            qobject_cast<ClassEntity*>(start)->curScene->lastLine->changeColor(Qt::black);
        this->changeColor(Qt::red);
        qobject_cast<ClassEntity*>(start)->curScene->lastLine = this;
    }
}

