/**
 * ICP Project 2022 
 * @file scene.p
 * @brief implementation of metods in scene class
 * @author Jakub Julius Smykal (xsmyka01)
 * @author Milan Hrabovsky (xhrabo15)
 */

#include "scene.h"
#include <QDebug>
#include <QLineEdit>
#include "classentity.h"
#include "classstorage.h"

//Scene constructor
Scene::Scene(QObject *parent) : QGraphicsScene(parent)
{
    entities.clear();
    focusList.clear();
    connections.clear();
    lastLine = nullptr;
    spawnCount = 0;
}

//Function creates new entity and stores its pointer in entities vector
void Scene::SpawnEntity(bool checked){
    ClassEntity *element = new ClassEntity();

    //settings for entity ui element
    element->setFrameShape(QFrame::Box);
    element->setFrameShadow(QFrame::Plain);
    element->setLineWidth(4);
    element->updateScene(this);

    //spawns item in scene
    QGraphicsProxyWidget *item = addWidget(element);
    item->setZValue(1);
    item->setParent(this);
    entities.push_back(element);
    element->setObjectName("entity" + QString::number(spawnCount++));
    
    QString text;
    foreach(auto *child, element->children()){
        if(child->objectName() == "title")
            text = qobject_cast<QLineEdit*>(child)->text();
    }
    //Creates object to store data in ClassStorage
    info->CreateEntity(element->objectName(), text);
}

//Function creates new connection and its markers
void Scene::SpawnConnectionLine(bool checked){
    //there must be two entities selected before you can create line
    if (focusList.size() == 2){
        if (focusList[0] == focusList[1])
            return;

        foreach(Line *item, connections){
            if(item->start == dynamic_cast<ClassEntity*>(focusList[0]) && item->end == dynamic_cast<ClassEntity*>(focusList[1]))
                return;
            if(item->start == dynamic_cast<ClassEntity*>(focusList[1]) && item->end == dynamic_cast<ClassEntity*>(focusList[0]))
                return;
        }

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
        item->setPoints(dynamic_cast<ClassEntity*>(focusList[0]), dynamic_cast<ClassEntity*>(focusList[1]));
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
    //also marks last two selected entities by changing their color
    item->setStyleSheet("QFrame { border: 4px solid lightgreen }");
    focusList.push_back(item);

    if (focusList.size() > 2){
        //if more than 2 entities should be selected, deselects first entity
        focusList[0]->setStyleSheet("QFrame { border: 4px solid black }");
        focusList.erase(focusList.begin());
    }
    focusList[0]->setStyleSheet("QFrame { border: 4px solid red }");
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
void Scene::RemoveEntity(bool checked){
    //entity must be selected before removal
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

        //removes entity
        for(int i = 0; i < entities.size(); i++){
            if (entities[i]->pos() == focusList[focusList.size() - 1]->pos()){

                info->RemoveEntity(entities[i]->objectName());
                entities.erase(entities.begin() + i);
            }
        }
        auto *delItem = focusList[focusList.size() - 1];
        focusList.clear();
        delete delItem;
    }
}

void Scene::updateData(QString objName, QString contentName, QString elemName){
    info->UpdateEntity(objName, contentName, elemName);
}

void Scene::createMethodData(QString objName, QString elemName, QString content){
    info->CreateMethod(objName, elemName, content);
}
void Scene::removeMethodData(QString objName, QString elemName){
    info->RemoveMethod(objName, elemName);
}
