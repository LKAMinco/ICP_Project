#include "scene.h"
#include <QDebug>

Scene::Scene(QObject *parent) : QGraphicsScene(parent)
{
    entities.clear();
}

void Scene::SpawnClassEntity(bool checked){
    QGraphicsProxyWidget *item = this->addWidget(new ClassEntity());
    entities.push_back(item);
}
