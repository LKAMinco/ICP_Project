/**
 * ICP Project 2022 
 * @file method.cpp
 * @brief implementation of methods in Method class
 * @author Jakub Julius Smykal (xsmyka01)
 * @author Milan Hrabovsky (xhrabo15)
 */

#include <method.h>

Method::Method(){
    name = new std::string;
}

Method::~Method(){
    delete name;
}