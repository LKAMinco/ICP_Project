#include "scene.h"
#include <QDebug>
#include <QLineEdit>
#include "classentity.h"

Scene::Scene(QObject *parent) : QGraphicsScene(parent)
{
    entities.clear();
    focusList.clear();
    connections.clear();
    lastLine = nullptr;
}

void Scene::SpawnClassEntity(bool checked){
    ClassEntity *element = new ClassEntity();
    element->updateScene(this);;
    QGraphicsProxyWidget *item = addWidget(element);
    item->setZValue(1);
    entities.push_back(item);
}

void Scene::SpawnConnectionLine(bool checked){
    if (focusList.size() == 2){
        if (focusList[0] == focusList[1])
            return;

        Line *item = new Line();
        item->setPoints(focusList[0], focusList[1]);
        this->addItem(item);
        item->setPosition();
        connections.push_back(item);
    }
    else{
        qDebug() << "This does not work!";
    }
}

void Scene::updateFocusList(QWidget *item){
    focusList.push_back(item);
    if (focusList.size() > 2)
        focusList.erase(focusList.begin());
}

void Scene::updateConnections(QWidget *item){
    for(int i = 0; i < connections.size(); i++){
        if (connections[i]->start == item || connections[i]->end == item)
            connections[i]->setPosition();
    }
}

void Scene::RemoveConnectionLine(bool checked){
    if (lastLine != nullptr){
        for(int i = 0; i < connections.size(); i++){
            if (connections[i] == lastLine)
                connections.erase(connections.begin() + i);
        }
        delete lastLine;
    }
    lastLine = nullptr;
}

void Scene::RemoveClassEntity(bool checked){
    if(focusList.size() != 0){
        for(int i = 0; i < connections.size(); i++){
            if (connections[i]->start == focusList[focusList.size() - 1] || connections[i]->end == focusList[focusList.size() - 1]){
                auto *delItem = connections[i];
                connections.erase(connections.begin() + i);
                delete delItem;
                i--;
            }
        }

        for(int i = 0; i < entities.size(); i++){
            if (entities[i]->pos() == focusList[focusList.size() - 1]->pos()){
                entities.erase(entities.begin() + i);
                auto *delItem = focusList[focusList.size() - 1];
                focusList.erase(focusList.begin() + focusList.size() - 1);
                delete delItem;
            }
        }
    }
}
