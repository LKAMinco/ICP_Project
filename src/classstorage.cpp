#include "classstorage.h"
#include <QDebug>
#include "UmlEditor.h"
#include "seqscene.h"
#include "seqentity.h"
#include "seqline.h"

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

void ClassStorage::CreateEntity(QString objName, QString content){
    EntityStorage *item = new EntityStorage(objName);
    item->content = content;
    entities.push_back(item);

    updateSeq();
}

void ClassStorage::UpdateEntity(QString objName, QString contentName, QString elemName){
    foreach(EntityStorage *entity, entities){
        if(entity->objectName == objName)
            if(elemName == "title")
                entity->content = contentName;
            else{
                foreach(MethodStorage *method, entity->methods){
                    if (method->objectName == elemName)
                        method->content = contentName;
                }
            }
    }

    updateSeq();
    updateSeqLine();
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

void ClassStorage::CreateMethod(QString objName, QString elemName, QString content){
    foreach(EntityStorage *entity, entities){
        if(entity->objectName == objName){
            MethodStorage *item = new MethodStorage(elemName);
            item->content = content;
            entity->methods.push_back(item);
        }
    }
    updateSeqLine();
}
void ClassStorage::RemoveMethod(QString objName, QString elemName){
    foreach(EntityStorage *entity, entities){
        if(entity->objectName == objName){
            for(int i = 0; i < entity->methods.size(); i++){
                if (entity->methods[i]->objectName == elemName){
                    MethodStorage *tmp = entity->methods[i];
                    entity->methods.erase(entity->methods.begin() + i);
                    delete tmp;
                }
            }
        }
    }
    updateSeqLine();
}

void ClassStorage::updateSeq(){
    foreach(seqScene *scene , window->seqList){
        foreach (SeqEntity *item, scene->entities) {
            item->updateData(this);
        }
    }
}

void ClassStorage::updateSeqLine(){
    foreach(seqScene *scene , window->seqList){
        foreach (SeqLine *item, scene->connections) {
            item->updateData(this);
        }
    }
}*/

