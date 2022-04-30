#include "scene.h"
#include <QDebug>
#include <QLineEdit>
#include "classentity.h"
#include "classline.h"

Scene::Scene(QObject *parent) : QGraphicsScene(parent)
{
    entities.clear();
    focusList.clear();
    connections.clear();
}

void Scene::SpawnClassEntity(bool checked){
    ClassEntity *element = new ClassEntity();
    element->updateScene(this);;
    QGraphicsProxyWidget *item = this->addWidget(element);
    entities.push_back(item);
}

void Scene::SpawnConnectionLine(bool checked){
    if (focusList.size() == 2){
        ClassLine *element = new ClassLine();
        element->setPoints(focusList[0], focusList[1]);
        QGraphicsProxyWidget *item = this->addWidget(element);
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
