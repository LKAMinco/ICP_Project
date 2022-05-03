#include "classstorage.h"
#include <QDebug>
#include "UmlEditor.h"
#include "seqscene.h"
#include "seqentity.h"

MethodStorage::MethodStorage(QString objName){
    objectName = objName;
    content = "";
}

EntityStorage::EntityStorage(QString objName){
    methods.clear();
    objectName = objName;
    content = "";
}

EntityStorage::~EntityStorage(){
    foreach (MethodStorage *item, methods) {
        delete item;
    }
}

ClassStorage::ClassStorage(MainWindow *win){
    entities.clear();
    window = win;
}

void ClassStorage::CreateEntity(QString objName){
    EntityStorage *item = new EntityStorage(objName);
    entities.push_back(item);

    updateSeq();
}

void ClassStorage::UpdateEntity(QString objName, QString contentName, QString elemName){
    for(int i = 0; i < entities.size(); i++){
        if(entities[i]->objectName == objName)
            if(elemName == "title")
                entities[i]->content = contentName;
    }

    qDebug() << entities[0]->content << " <- title";
    updateSeq();
}

void ClassStorage::RemoveEntity(QString objName){
    for(int i = 0; i < entities.size(); i++){
        if(entities[i]->objectName == objName){
            EntityStorage *tmp = entities[i];
            entities.erase(entities.begin() + i);
            delete tmp;
        }
    }

    updateSeq();
}

void ClassStorage::updateSeq(){
    foreach(seqScene *scene , window->seqList){
        foreach (SeqEntity *item, scene->entities) {
            item->updateData(this);
        }
    }
}

