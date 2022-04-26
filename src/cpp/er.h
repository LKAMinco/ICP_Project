/**
 * ICP Project 2022 
 * @file er.h
 * @brief header file for er class
 * @author Jakub Julius Smykal (xsmyka01)
 * @author Milan Hrabovsky (xhrabo15)
 */

#ifndef ERDIAGRAM_H
#define ERDIAGRAM_H

#include <erconnect.h>

/**
 * @class ER
 * @brief class for connection lines in ER diagram
 */ 
class ER {
    private:
        std::vector<Entity*> *entities;
        std::vector<Erconnect*> *connections;
    public:
        /**
         * @name Constructor
         */
        ER();
        /**
         * @name Destructor
         */
        ~ER();
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