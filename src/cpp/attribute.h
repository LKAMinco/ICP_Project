/**
 * ICP Project 2022 
 * @file attribute.h
 * @brief header file for attribute class
 * @author Jakub Julius Smykal (xsmyka01)
 * @author Milan Hrabovsky (xhrabo15)
 */

#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <string>

/**
 * @class Attribute
 * @brief class for attributes in ER entities
 */ 
class Attribute {
    private:
        std::string modifier; // +, -, #, ~
        std::string name;
        std::string type;
    public:
        /**
         * @name Update Modifier
         * @brief updates value in modifier string
         */
        void updateModifier(std::string newMod);
        /**
         * @name Update Name
         * @brief updates value in name string
         */
        void updateName(std::string newName);
        /**
         * @name Update Type
         * @brief updates value in type string
         */
        void updateType(std::string newType);
        /**
         * @name Get Name
         * @brief returns name of attribute
         * @return string
         */
        std::string getName();
};

#endif