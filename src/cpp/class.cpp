/**
 * ICP Project 2022 
 * @file er.cpp
 * @brief implementation of methods in class diagram class
 * @author Jakub Julius Smykal (xsmyka01)
 * @author Milan Hrabovsky (xhrabo15)
 */

#include "class.h"

void CD::addEntity(Entity *en){
    entities.push_back(en);
}

void CD::RemoveEntity(Entity *en){
    int index = -1;
    std::string name = en->getName();
    for(int i = 0; i < entities.size(); i++){
        //compares name of attribute in vector with attrib
        if (entities[i]->getName() == name){
            index = i;
            break;
        }
    }
    //if finds attribute, calls its destructor and removes it from vector
    if(index != -1){
        delete entities[index];
        entities.erase(entities.begin() + index);
    }
}

void CD::addConnection(Erconnect *connection){
    connections.push_back(connection);
}
