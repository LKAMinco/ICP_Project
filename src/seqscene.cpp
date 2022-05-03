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
    SeqEntity *item = new SeqEntity();
    this->addWidget(item);
    item->updateScene(this);
    entities.push_back(item);
}

void seqScene::SpawnConnectionLine(bool checked){
    //there must be two entities selected before you can create line
    if (focusList.size() == 2){
        if (focusList[0] == focusList[1])
            return;
        SeqLine *item = new SeqLine();
        //sets all pointers in line object
        item->setPoints(dynamic_cast<SeqEntity*>(focusList[0]), dynamic_cast<SeqEntity*>(focusList[1]));
        //item->setMarkers(aggregP, composP, generP);
        this->addItem(item);
        item->setPosition(false);
        //stores line in connections vector
        connections.push_back(item);
    }
}

void seqScene::ChangeConnectionLine(bool checked){
    qDebug() << "update connection";
}

void seqScene::RemoveConnectionLine(bool checked){
    qDebug() << "remove connection";
}

void seqScene::RemoveEntity(bool checked){
    //entity must be selected before removal
    qDebug() << focusList.size();
    if(focusList.size() != 0){
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
    if(focusList.size() != 0)
        qobject_cast<SeqEntity*>(focusList.back())->setColor(Qt::gray);
    qobject_cast<SeqEntity*>(item)->setColor(Qt::red);
    focusList.push_back(item);
    if (focusList.size() > 2)
        focusList.erase(focusList.begin());
}

//Function updates last selected connection line
void seqScene::updateConnections(QWidget *item){
    for(int i = 0; i < connections.size(); i++){
        if (connections[i]->start == item || connections[i]->end == item)
            connections[i]->setPosition(true);
    }
}
