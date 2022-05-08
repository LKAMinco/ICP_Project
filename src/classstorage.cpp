/**
 * ICP Project 2022 
 * @file classstorage.cpp
 * @brief implementation of methods for classes in classstorage.h
 * @author Jakub Julius Smykal (xsmyka01)
 * @author Milan Hrabovsky (xhrabo15)
 */

#include "classstorage.h"
#include <QDebug>
#include "UmlEditor.h"
#include "seqscene.h"
#include "seqentity.h"
#include "seqline.h"

//MethodStorage constructor
MethodStorage::MethodStorage(QString objName){
    objectName = objName;
    content = "";
}

//EntityStorage constructor
EntityStorage::EntityStorage(QString objName){
    methods.clear();
    objectName = objName;
    content = "";
}

//EntityStorage destructor
EntityStorage::~EntityStorage(){
    foreach (MethodStorage *item, methods) {
        delete item;
    }
}

//ClassStorage constructor
ClassStorage::ClassStorage(MainWindow *win){
    entities.clear();
    window = win;
}

//Function creates object to store data about entity
void ClassStorage::CreateEntity(QString objName, QString content){
    EntityStorage *item = new EntityStorage(objName);
    item->content = content;
    entities.push_back(item);
    //updates info for sequence diagrams
    updateSeq();
}

//Fucntion updates data about enities and their methods
void ClassStorage::UpdateEntity(QString objName, QString contentName, QString elemName){
    foreach(EntityStorage *entity, entities){
        if(entity->objectName == objName){
            //only ui element for class name is named title
            if(elemName == "title")
                entity->content = contentName;
            else{
                foreach(MethodStorage *method, entity->methods){
                    if (method->objectName == elemName)
                        method->content = contentName;
                }
            }
        }
    }
    //updates info for sequence diagrams
    updateSeq();
    updateSeqLine();
}

//Function removes entity from data storage
void ClassStorage::RemoveEntity(QString objName){
    for(unsigned int i = 0; i < entities.size(); i++){
        if(entities[i]->objectName == objName){
            EntityStorage *tmp = entities[i];
            entities.erase(entities.begin() + i);
            delete tmp;
        }
    }
    //updates info for sequence diagrams
    updateSeq();
}

//Function creates object to store class's method
void ClassStorage::CreateMethod(QString objName, QString elemName, QString content){
    //searches for correct class entity
    foreach(EntityStorage *entity, entities){
        
        if(entity->objectName == objName){
            MethodStorage *item = new MethodStorage(elemName);
            item->content = content;
            entity->methods.push_back(item);
        }
    }
    //updates info for sequence diagrams
    updateSeqLine();
}

//Function removes method from class's data
void ClassStorage::RemoveMethod(QString objName, QString elemName){
    //searches for correct class entity
    foreach(EntityStorage *entity, entities){
        if(entity->objectName == objName){

            for(unsigned int i = 0; i < entity->methods.size(); i++){

                if (entity->methods[i]->objectName == elemName){
                    MethodStorage *tmp = entity->methods[i];
                    entity->methods.erase(entity->methods.begin() + i);
                    delete tmp;
                }
            }
        }
    }
    //updates info for sequence diagrams
    updateSeqLine();
}

//Function updates info in each entity in sequence diagrams
void ClassStorage::updateSeq(){
    foreach(seqScene *scene , window->seqList){
        foreach (SeqEntity *item, scene->entities) {
            item->updateData(this);
        }
    }
}

//Function updates info in each line in sequence diagrams
void ClassStorage::updateSeqLine(){
    foreach(seqScene *scene , window->seqList){
        foreach (SeqLine *item, scene->connections) {
            item->updateData(this);
        }
    }
}

