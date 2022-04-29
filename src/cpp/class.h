/**
 * ICP Project 2022 
 * @file er.h
 * @brief header file for class diagram class
 * @author Jakub Julius Smykal (xsmyka01)
 * @author Milan Hrabovsky (xhrabo15)
 */

#ifndef CDIAGRAM_H
#define CDIAGRAM_H

#include "erconnect.h"

/**
 * @class CD
 * @brief class for connection lines in ER diagram
 */ 
class CD {
    private:
        std::vector<Entity*> entities;
        std::vector<Erconnect*> connections;
    public:
        /**
         * @name Add Attribute
         * @brief adds attribute to attributes (attribute array)
         */
        void addEntity(Entity *en);
        /**
         * @name Remove Attribute
         * @brief removes attribute from attributes (attribute array)
         */
        void RemoveEntity(Entity *en);
        /**
         * @name Add Method
         * @brief adds method to methods (method array)
         */
        void addConnection(Erconnect *connection);
};

#endif