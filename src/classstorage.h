/**
 * ICP Project 2022 
 * @file classstorage.h
 * @brief header file for ClassStorage, where data from class diagram are stored
 * @author Jakub Julius Smykal (xsmyka01)
 * @author Milan Hrabovsky (xhrabo15)
 */

#ifndef CLASSSTORAGE_H
#define CLASSSTORAGE_H

#include "classentity.h"
#include <QString>

class MainWindow;

/**
 * @class MethodStorage
 * @brief class for storing data from entity's method
*/
class MethodStorage
{
public:
    /**
     * @name MethodStorage
     * @brief constructor
     * @param objName - object name
    */
    MethodStorage(QString objName);

    QString objectName;
    QString content;
};

/**
 * @class EntityStorage
 * @brief class for storing data from class diagram's entity
*/
class EntityStorage
{
public:
    /**
     * @name EntityStorage
     * @brief constructor
     * @param objName - object name
    */
    EntityStorage(QString objName);
    /**
     * @name EntityStorage destructor
    */
    ~EntityStorage();

    QString objectName;
    QString content;
    std::vector<MethodStorage*> methods;
};

/**
 * @class ClassStorage
 * @brief class for storing entities from class diagram
*/
class ClassStorage
{
public:
    /**
     * @name ClassStorage
     * @brief constructor
     * @param win - pointer to main window
    */
    ClassStorage(MainWindow *win);
    //~ClassStorage();

    /**
     * @name CreateEntity
     * @brief creates object to store data from class diagram's entity
     * @param objName - entity's object name
     * @param content - name of class
    */
    void CreateEntity(QString objName, QString content);
    /**
     * @name UpdateEntity
     * @brief updates data stored about entity and its methods
     * @param objName - entity's object name
     * @param content - name of class/method
     * @param elemName - name of ui element, from where data is copied
    */
    void UpdateEntity(QString objName, QString contentName, QString elemName);
    /**
     * @name RemoveEntity
     * @brief removes entity from ClassStorage
     * @param objName - entity'sobject name
    */
    void RemoveEntity(QString objName);
    /**
     * @name CreateMethod
     * @brief creates object to store data from entity's method
     * @param objName - entity's object name
     * @param elemName - name of ui element, from where data is copied
     * @param content - name of method in entity
    */
    void CreateMethod(QString objName, QString elemName, QString content);
    /**
     * @name RemoveMethod
     * @brief removes method from entity's data
     * @param objName - entity'sobject name
     * @param elemName - name of ui element, from where data is copied
    */
    void RemoveMethod(QString objName, QString elemName);
    /**
     * @name updateSeq
     * @brief updates data in sequence diagram's entities
    */
    void updateSeq();
    /**
     * @name updateSeqLine
     * @brief updates data in sequence diagram's lines
    */
    void updateSeqLine();

    std::vector<EntityStorage*> entities;
    MainWindow *window;
};

#endif // CLASSSTORAGE_H
