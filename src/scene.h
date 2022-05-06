/**
 * ICP Project 2022 
 * @file scene.h
 * @brief header file for class diagram's scene
 * @author Jakub Julius Smykal (xsmyka01)
 * @author Milan Hrabovsky (xhrabo15)
 */

#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsProxyWidget>
#include "line.h"
#include <QGraphicsPolygonItem>

class ClassStorage;

class ClassEntity;

/**
 * @class Scene
 * @brief class for class diagram scene
*/
class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    /**
     * @name Scene
     * @brief constructor
     * @param parent
    */
    explicit Scene(QObject *parent = nullptr);
    /**
     * @name updateFocusList
     * @brief updates vector of 2 last selected entities
     * @param item - pointer to last selected entity
    */
    void updateFocusList(QWidget *item);
    /**
     * @name updateConnections
     * @brief updates last selected connection pointer, updates selected connection's color
     * @param item - pointer to last selected connection
    */
    void updateConnections(QWidget *item);
    /**
     * @name updateData
     * @brief function connect entity with ClassStorage's method UpdateEntity
     * @param objName - entity's object name
     * @param content - name of class/method
     * @param elemName - name of ui element, from where data is copied
    */
    void updateData(QString objName, QString contentName, QString elemName);
    /**
     * @name updateMethodData
     * @brief function connect entity with ClassStorage's method UpdateEntity
     * @param objName - entity's object name
     * @param content - name of class/method
     * @param elemName - name of ui element, from where data is copied
    */
    void createMethodData(QString objName, QString elemName, QString content);
    /**
     * @name removeMethodData
     * @brief function connect entity with ClassStorage's method
     * @param objName - entity's object name
     * @param content - name of class/method
     * @param elemName - name of ui element, from where data is copied RemoveMethod
    */
    void removeMethodData(QString objName, QString elemName);

    std::vector<ClassEntity*> entities;
    std::vector<Line*> connections;
    //last selected line
    Line *lastLine;
    //vector of 2 last selected entities
    std::vector<QWidget*> focusList;
    //pointer to data storage
    ClassStorage *info;
    int spawnCount;

public slots:
    /**
     * @name SpawnEntity
     * @brief Slot to spawn entity in class diagram
     * @param checked
    */
    void SpawnEntity(bool checked);
    /**
     * @name SpawnConnectionLine
     * @brief Slot to spawn connectin in class diagram
     * @param checked
    */
    void SpawnConnectionLine(bool checked);
    /**
     * @name ChangeConnectionLine
     * @brief Slot to change type of connection in class diagram
     * @param checked
    */
    void ChangeConnectionLine(bool checked);
    /**
     * @name RemoveEntity
     * @brief Slot to remove entity in class diagram
     * @param checked
    */
    void RemoveEntity(bool checked);
    /**
     * @name RemoveConnectionLine
     * @brief Slot to remove connection in class diagram
     * @param checked
    */
    void RemoveConnectionLine(bool checked);

};

#endif // SCENE_H
