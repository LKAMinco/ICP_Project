/**
 * ICP Project 2022 
 * @file attribute.cpp
 * @brief implementation of methods in Attribute class
 * @author Jakub Julius Smykal (xsmyka01)
 * @author Milan Hrabovsky (xhrabo15)
 */

#include "attribute.h"

void Attribute::updateModifier(std::string newMod){
    modifier = newMod;
}

void Attribute::updateName(std::string newName){
    name = newName;
}

void Attribute::updateType(std::string newType){
    name = newType;
}

std::string Attribute::getName(){
    return name;
}