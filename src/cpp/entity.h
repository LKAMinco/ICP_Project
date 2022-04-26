/**
 * ICP Project 2022 
 * @file entity.h
 * @brief header file for entity class
 * @author Jakub Julius Smykal (xsmyka01)
 * @author Milan Hrabovsky (xhrabo15)
 */

#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <attribute.h>
#include <method.h>
#include <vector>

/**
 * @class Entity
 * @brief class for entities in ER entities
 */ 
class Entity {
    private:
        std::vector<Attribute*> *attributes;
        std::vector<Method*> *methods;
    public:
        /**
         * @name Constructor
         */
        Entity();
        /**
         * @name Destructor
         */
        ~Entity();
        /**
         * @name Add Attribute
         * @brief adds attribute to attributes (attribute array)
         */
        void addAttribute(Attribute *attrib);
        /**
         * @name Remove Attribute
         * @brief removes attribute from attributes (attribute array)
         */
        void RemoveAttribute(Attribute *attrib);
        /**
         * @name Add Method
         * @brief adds method to methods (method array)
         */
        void addMethod(Method *met);
        /**
         * @name Remove Method
         * @brief removes method from methods (method array)
         */
        void RemoveMethod(Method *met);
};

#endif