/**
 * ICP Project 2022 
 * @file method.h
 * @brief header file for method class
 * @author Jakub Julius Smykal (xsmyka01)
 * @author Milan Hrabovsky (xhrabo15)
 */

#ifndef METHOD_H
#define METHOD_H

#include <string>

/**
 * @class Method
 * @brief class for methods in ER entities
 */ 
class Method {
    private:
        std::string name;
    public:
        /**
         * @name Update Name
         * @brief updates value in name string
         */
        void updateName(std::string newName);
        /**
         * @name Get Name
         * @brief returns name of method
         * @return string
         */
        std::string getName();
};

#endif