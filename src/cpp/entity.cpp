/**
 * ICP Project 2022 
 * @file entity.cpp
 * @brief implementation of methods in Entity class
 * @author Jakub Julius Smykal (xsmyka01)
 * @author Milan Hrabovsky (xhrabo15)
 */

#include <entity.h>

Entity::Entity(){
    name = new std::string;
    attributes = new std::vector<Attribute*>();
    methods = new std::vector<Method*>();
}

Entity::~Entity(){
    delete name;
    delete[] attributes;
    delete[] methods;
}

void Entity::addAttribute(Attribute *attrib){
    attributes->push_back(attrib);
}

void Entity::RemoveAttribute(Attribute *attrib){
    int index = -1;
    std::string name = attrib->getName();
    for(int i = 0; i < attributes->size(); i++){
        //compares name of attribute in vector with attrib
        if ((*attributes)[i]->getName() == name){
            index = i;
            break;
        }
    }
    //if finds attribute, calls its destructor and removes it from vector
    if(index != -1){
        delete (*attributes)[index];
        attributes->erase(attributes->begin() + index);
    }
}

void Entity::addMethod(Method *met){
    methods->push_back(met);
}

void Entity::RemoveMethod(Method *met){
    int index = -1;
    std::string name = met->getName();
    for(int i = 0; i < methods->size(); i++){
        //compares name of method in vector with met
        if ((*methods)[i]->getName() == name){
            index = i;
            break;
        }
    }
    //if finds method, calls its destructor and removes it from vector
    if(index != -1){
        delete (*methods)[index];
        methods->erase(methods->begin() + index);
    }
}

std::string Entity::getName(){
    return *name;
}