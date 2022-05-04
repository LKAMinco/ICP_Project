#include "seqscene.h"
#include <QDebug>
#include "seqentity.h"


seqScene::seqScene(QObject *parent) : QGraphicsScene(parent)
{
    entities.clear();
    focusList.clear();
    connections.clear();
}

void seqScene::SpawnEntity(bool checked){
    static int num = 0;
    SeqEntity *item = new SeqEntity();
    this->addWidget(item);
    item->updateScene(this);
    entities.push_back(item);
    item->setObjectName("seq_entity" + QString::number(num++));
    item->insertAllData(info);
}

void seqScene::SpawnConnectionLine(bool checked){
    //there must be two entities selected before you can create line
    if (focusList.size() == 2){
        if (focusList[0] == focusList[1])
            return;

        //creates three markers from polygons
        QPolygonF full, arrow, blue;
        full << QPoint(12, 0) << QPoint(0, 12) << QPoint(0, -12);
        QGraphicsPolygonItem *fullP = addPolygon(full, QPen(Qt::black, 2), QBrush(Qt::black));
        arrow << QPoint(12, 0) << QPoint(0, 12) << QPoint(12, 0) << QPoint(0, -12);
        QGraphicsPolygonItem *arrowP = addPolygon(arrow, QPen(Qt::black, 2), QBrush(Qt::black));
        blue << QPoint(-6, 24) << QPoint(6, 24) << QPoint(6, -24) << QPoint(-6, -24);
        QGraphicsPolygonItem *blue1P = addPolygon(blue, QPen(Qt::blue, 2), QBrush(Qt::blue));
        QGraphicsPolygonItem *blue2P = addPolygon(blue, QPen(Qt::blue, 2), QBrush(Qt::blue));

        fullP->setZValue(2);
        arrowP->setZValue(2);
        blue1P->setZValue(1);
        blue2P->setZValue(1);

        QComboBox *box = new QComboBox();
        auto *newBox = this->addWidget(box);
        box->addItem("");
        newBox->setZValue(2);

        SeqLine *item = new SeqLine();
        //sets all pointers in line object
        item->setPoints(dynamic_cast<SeqEntity*>(focusList[0]), dynamic_cast<SeqEntity*>(focusList[1]));
        item->setMarkers(fullP, arrowP, blue1P, blue2P, box);
        this->addItem(item);
        item->setPosition();
        item->insertAllData(info);

        //stores line in connections vector
        connections.push_back(item);
    }
}

void seqScene::ChangeConnectionLine(bool checked){
    if(lastLine != nullptr)
        lastLine->changeType();
}

void seqScene::RemoveConnectionLine(bool checked){
    if (lastLine != nullptr){
        for(int i = 0; i < connections.size(); i++){
            if (connections[i] == lastLine)
                connections.erase(connections.begin() + i);
        }
        lastLine->deleteMarkers();
        delete lastLine;
    }
    lastLine = nullptr;
}

void seqScene::RemoveEntity(bool checked){
    //entity must be selected before removal
    qDebug() << focusList.size();
    if(focusList.size() != 0){
        //function also removes all lines, that are connected to the entity, which is being removed
        for(int i = 0; i < connections.size(); i++){
            if (connections[i]->start == focusList[focusList.size() - 1] || connections[i]->end == focusList[focusList.size() - 1]){
                if(lastLine == connections[i])
                    lastLine = nullptr;
                auto *delItem = connections[i];
                connections[i]->deleteMarkers();
                connections.erase(connections.begin() + i);
                delete delItem;
                i--;
            }
        }
        for(int i = 0; i < entities.size(); i++){
            if (entities[i]->pos() == focusList[focusList.size() - 1]->pos()){
                entities.erase(entities.begin() + i);
            }
        }
        auto *delItem = focusList[focusList.size() - 1];
        focusList.clear();
        delete delItem;
    }
}

//Function updates last selected entities
void seqScene::updateFocusList(QWidget *item){
    qobject_cast<SeqEntity*>(item)->setColor(Qt::red);
    focusList.push_back(item);
    if (focusList.size() > 2){
        qobject_cast<SeqEntity*>(focusList[0])->setColor(Qt::black);
        focusList.erase(focusList.begin());
    }
    qobject_cast<SeqEntity*>(focusList[0])->setColor(Qt::red);
}

//Function updates last selected connection line
void seqScene::updateConnections(QWidget *item){
    for(int i = 0; i < connections.size(); i++){
        if (connections[i]->start == item || connections[i]->end == item)
            connections[i]->setPosition();
    }
}

void seqScene::updateDataLines(const QString &text){
    QObject* obj = sender();
    foreach(SeqLine *line, connections){
        if(line->start->objectName() == obj->parent()->parent()->objectName())
            line->insertAllData(info);
    }
}
