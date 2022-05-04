#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsProxyWidget>
#include "line.h"
#include <QGraphicsPolygonItem>

class ClassStorage;

class ClassEntity;

/*
 * @class Scene
 * @brief class for class diagram scene
*/
class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    /*
     * @name Scene constructor
    */
    explicit Scene(QObject *parent = nullptr);
    /*
     * @name updateFocusList
     * @brief updates vector of 2 last selected entities
     * @param item -> pointer to last selected entity
    */
    void updateFocusList(QWidget *item);
    /*
     * @name updateConnections
     * @brief updates last selected connection pointer, updates selected connection's color
     * @param item -> pointer to last selected connection
    */
    void updateConnections(QWidget *item);

    void updateData(QString objName, QString contentName, QString elemName);
    void createMethodData(QString objName, QString elemName, QString content);
    void removeMethodData(QString objName, QString elemName);

    std::vector<ClassEntity*> entities;
    std::vector<Line*> connections;
    Line *lastLine;
        //vector of 2 last selected entities
    std::vector<QWidget*> focusList;
    ClassStorage *info;

public slots:
    void SpawnEntity(bool checked);
    void SpawnConnectionLine(bool checked);
    void ChangeConnectionLine(bool checked);
    void RemoveEntity(bool checked);
    void RemoveConnectionLine(bool checked);

};

#endif // SCENE_H
