/**
 * ICP Project 2022 
 * @file method.cpp
 * @brief implementation of methods in Method class
 * @author Jakub Julius Smykal (xsmyka01)
 * @author Milan Hrabovsky (xhrabo15)
 */

#include "method.h"

void Method::updateName(std::string newName){
    name = newName;
}

std::string Method::getName(){
    return name;
}