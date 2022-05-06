/**
 * ICP Project 2022 
 * @file seqline.cpp
 * @brief implementation of methods in SeqLine class
 * @author Jakub Julius Smykal (xsmyka01)
 * @author Milan Hrabovsky (xhrabo15)
 */

#include "seqline.h"
#include <QDebug>
#include "seqentity.h"
#include "classstorage.h"

//Constructor
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

//Destructor
SeqLine::~SeqLine(){

}

//Function sets start and end points of line
void SeqLine::setPoints(SeqEntity *first, SeqEntity *last){
    //start point is always the one on the left side
    if(first->pos().x() < last->pos().x()){
        start = first;
        end = last;
    }
    else{
        start = last;
        end = first;
    }
}

//Function sets pointers to markers and sets their visibility
void SeqLine::setMarkers(QGraphicsPolygonItem *fu, QGraphicsPolygonItem *ar, QGraphicsPolygonItem *b1, QGraphicsPolygonItem *b2, QComboBox *cbox){
    full = fu;
    arrow = ar;
    blue1 = b1;
    blue2 = b2;

    full->setVisible(true);
    arrow->setVisible(false);
    box = cbox;
}

//Function updates position of line and its markers
void SeqLine::setPosition(){
    setPoints(start, end);
    //sets offset from moving the line with mouse
    y1 = start->pos().y() + mouseOffset;
    if(type == 3)
        y1 += 48;

    y2 = y1;

    //caps mouse offset
    if(y2 < end->pos().y())
        y2 = end->pos().y();
    if(y2 > end->pos().y() + end->height() - 10)
        y2 = end->pos().y() + end->height() - 10;

    if(y1 > start->pos().y() + 85)
        startOffset = -87;
    else
        startOffset = 0;

    //different y positoion cap if line is of type return line(3)
    if(type == 3 && y2 < end->pos().y() + 85 + 48)
        y2 = end->pos().y() + 85 + 48;

    //check if line points to widget or line of entity
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

    //sets x positions of line
    x1 = start->pos().x() + start->width() + startOffset;
    x2 = end->pos().x() + endOffset;
    this->setLine(x1, y1, x2, y2);

    //sets position of markers
    full->setPos(x2 - 16 + markerOffset, y2);
    //sets position of arrow and blue markers based on type of line
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
    //changes position of combobox, that belongs to the line
    box->move((x2 + x1)/2 - box->width()/2, (y1 + y2)/2 - 35);

}

//Function handles mouse press event -> selects entity
void SeqLine::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(event->buttons() == Qt::RightButton){
        if (qobject_cast<SeqEntity*>(start)->curScene->lastLine != nullptr)
            qobject_cast<SeqEntity*>(start)->curScene->lastLine->changeColor(Qt::black);

        //marks selected line by changing its color
        this->changeColor(Qt::red);
        qobject_cast<SeqEntity*>(start)->curScene->lastLine = this;
    }
}

//Function handles mouse press event -> selects entity
void SeqLine::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if(event->buttons() == Qt::LeftButton)
    {
        ///cap for moving the line on y axis
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

//Function changes type of line, updates visibility of markers and offsets
void SeqLine::changeType(){
    type = (type + 1) % 4;
    switch(type){
        case 0: //solid line with full triange
            full->setVisible(true);
            arrow->setVisible(false);
            this->setPen(QPen(Qt::red, 3, Qt::SolidLine));
            box->setVisible(true);
            break;

        case 1: //solid line with arrow
            full->setVisible(false);
            arrow->setVisible(true);
            this->setPen(QPen(Qt::red, 3, Qt::SolidLine));
            box->setVisible(true);
            break;

        case 2: //dashed line with arrow
            full->setVisible(false);
            arrow->setVisible(true);
            this->setPen(QPen(Qt::red, 3, Qt::DashLine));
            box->setVisible(true);
            break;

        case 3: //return line
            full->setVisible(false);
            arrow->setVisible(true);
            this->setPen(QPen(Qt::red, 3, Qt::DashLine));
            box->setVisible(false);
            break;

        default:
            break;
    }
    //updates position of line and its markers
    setPosition();
}

//Function removes all markers
//Cannot be in destructor -> caused segfault upon closing the app
void SeqLine::deleteMarkers(){
    delete full;
    delete arrow;
    delete blue1;
    delete blue2;
    delete box;
}

//Function updates data in entity from ClassStorage
void SeqLine::updateData(ClassStorage *info){
    foreach (EntityStorage *entity, info->entities) { //finds selecte class
        if(entity->content == end->box->itemText(end->box->currentIndex())){

            //new method was added
            if(box->count() < entity->methods.size() + 1){
                box->addItem(entity->methods.back()->content);
            }
            //method name was changed
            else if(box->count() == entity->methods.size() + 1){
                for(int i = 0; i < entity->methods.size(); i++){
                    if(box->itemText(i + 1) != entity->methods[i]->content){
                        box->setItemText(i + 1, entity->methods[i]->content);
                        break;
                    }
                }
            }
            //method was removed
            else{
                for(int i = 0; i < entity->methods.size(); i++){
                    //if method that is being removed was currently selected, remove selection
                    if(box->currentIndex() == i + 1)
                        box->setCurrentIndex(0);
                    box->removeItem(i + 1);
                }
                //last method was removed
                if(box->count() != entity->methods.size() + 1){
                    //if class that is being removed was currently selected, remove selection
                    if(box->currentIndex() == box->count() - 1)
                        box->setCurrentIndex(0);
                    box->removeItem(box->count() - 1);
                }
            }
        }
    }
}

//Function insert all data for selected class from ClassStorage
void SeqLine::insertAllData(ClassStorage *info){
    //removes data in combobox if there were any
    box->setCurrentIndex(0);
    for(int i = 1; i < box->count(); i++)
        box->removeItem(i--);

    foreach(EntityStorage *item, info->entities){
        if(item->content == end->box->currentText()){
            foreach(MethodStorage *elem, item->methods){
                box->addItem(elem->content);
            }
            break;
        }
    }
}
