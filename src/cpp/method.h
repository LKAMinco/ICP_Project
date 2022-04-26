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
 * @brief class for methods in entities
 */ 
class Method {
    private:
        std::string *name;
    public:
        /**
         * @name Constructor for Method class
         */
        Method();
        /**
         * @name Destructor for Method class
         */
        ~Method();
};

#endif