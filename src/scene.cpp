#include "scene.h"
#include <QDebug>
#include <QLineEdit>
#include "classentity.h"

Scene::Scene(QObject *parent) : QGraphicsScene(parent)
{
    entities.clear();
    focusList.clear();
    connections.clear();
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
