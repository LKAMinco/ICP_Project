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

//Creates new entity and stores its pointer in entities vector
void Scene::SpawnClassEntity(bool checked){
    ClassEntity *element = new ClassEntity();
    element->updateScene(this);;
    QGraphicsProxyWidget *item = addWidget(element);
    item->setZValue(1);
    entities.push_back(item);
}

//Creates new connection and its markers
void Scene::SpawnConnectionLine(bool checked){
    //there must be two entities selected before you can create line
    if (focusList.size() == 2){
        if (focusList[0] == focusList[1])
            return;

        //brush for marker's fill
        QBrush brush;
        brush.setColor(Qt::white);

        Line *item = new Line();
        //creates three markers from polygons
        QPolygonF aggreg, compos, gener;
        aggreg << QPoint(12, 0) << QPoint(0, 12) << QPoint(-12, 0) << QPoint(0, -12);
        QGraphicsPolygonItem *aggregP = addPolygon(aggreg, QPen(Qt::black, 2), brush);
        compos << QPoint(12, 0) << QPoint(0, 12) << QPoint(-12, 0) << QPoint(0, -12);
        QGraphicsPolygonItem *composP = addPolygon(compos, QPen(Qt::black, 2), QBrush(Qt::black));
        gener << QPoint(12, 0) << QPoint(0, 12) << QPoint(0, -12);
        QGraphicsPolygonItem *generP = addPolygon(gener, QPen(Qt::black, 2), brush);

        //sets all pointers in line object
        item->setPoints(focusList[0], focusList[1]);
        item->setMarkers(aggregP, composP, generP);
        this->addItem(item);
        item->setPosition();
        //stores line in connections vector
        connections.push_back(item);
    }
    else{
        qDebug() << "This does not work!";
    }
}

//Function updates last selected entities
void Scene::updateFocusList(QWidget *item){
    focusList.push_back(item);
    if (focusList.size() > 2)
        focusList.erase(focusList.begin());
}

//Function updates last selected connection line
void Scene::updateConnections(QWidget *item){
    for(int i = 0; i < connections.size(); i++){
        if (connections[i]->start == item || connections[i]->end == item)
            connections[i]->setPosition();
    }
}

//Function changes type of connection line
void Scene::ChangeConnectionLine(bool checked){
    if (lastLine != nullptr){
        lastLine->changeType();
    }
}

//Function removes connection line from scene
void Scene::RemoveConnectionLine(bool checked){
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

//Function removes entity from scene
void Scene::RemoveClassEntity(bool checked){
    //entity must be selected before removal
    if(focusList.size() != 0){
        //function also removes all lines, that are connected to the entity, which is being removed
        for(int i = 0; i < connections.size(); i++){
            if (connections[i]->start == focusList[focusList.size() - 1] || connections[i]->end == focusList[focusList.size() - 1]){
                if(lastLine == connections[i])
                    lastLine = nullptr;
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
