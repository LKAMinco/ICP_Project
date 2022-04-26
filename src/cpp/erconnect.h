/**
 * ICP Project 2022 
 * @file erconnect.h
 * @brief header file for erconnect class
 * @author Jakub Julius Smykal (xsmyka01)
 * @author Milan Hrabovsky (xhrabo15)
 */

#ifndef ERCONNECT_H
#define ERCONNECT_H

#include "entity.h"

/**
 * @class Erconnect
 * @brief class for connection lines in ER diagram
 */ 
class Erconnect {
    private:
        Entity *startPoint;
        Entity *endPoint;
    public:
        /**
         * @name Constructor
         */
        Erconnect(Entity *start, Entity *end);
};

#endif