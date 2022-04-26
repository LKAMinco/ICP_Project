/**
 * ICP Project 2022 
 * @file er.cpp
 * @brief implementation of methods in ER class
 * @author Jakub Julius Smykal (xsmyka01)
 * @author Milan Hrabovsky (xhrabo15)
 */

#include <er.h>

ER::ER(){
    entities = new std::vector<Entity*>();
    connections = new std::vector<Erconnect*>();
}

ER::~ER(){
    delete[] entities;
    delete[] connections;
}

void ER::addEntity(Entity *en){
    entities->push_back(en);
}

void ER::RemoveEntity(Entity *en){
    int index = -1;
    std::string name = en->getName();
    for(int i = 0; i < entities->size(); i++){
        //compares name of attribute in vector with attrib
        if ((*entities)[i]->getName() == name){
            index = i;
            break;
        }
    }
    //if finds attribute, calls its destructor and removes it from vector
    if(index != -1){
        delete (*entities)[index];
        entities->erase(entities->begin() + index);
    }
}

void ER::addConnection(Erconnect *connection){
    connections->push_back(connection);
}
