#include "scene.h"

Scene::Scene(QObject *parent) : QGraphicsScene(parent)
{
    entities.clear();
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event){

    if (event->button() == Qt::RightButton){
        spawnItem();
    }

    //QGraphicsScene::mousePressEvent(event);
}

void Scene::spawnItem(){
    QGraphicsProxyWidget *item = this->addWidget(new ClassEntity());
    entities.push_back(item);
}
