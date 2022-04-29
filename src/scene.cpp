#include "scene.h"
#include <QDebug>

Scene::Scene(QObject *parent) : QGraphicsScene(parent)
{
    entities.clear();
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event){

    if (event->button() == Qt::RightButton){
        spawnItem();
    }
    else{
        QGraphicsScene::mousePressEvent(event);
    }
}

void Scene::spawnItem(){
    QGraphicsProxyWidget *item = this->addWidget(new ClassEntity());
    entities.push_back(item);
}

