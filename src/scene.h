#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsProxyWidget>
#include "line.h"
#include <QGraphicsPolygonItem>

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

    std::vector<ClassEntity*> entities;
    std::vector<Line*> connections;
    Line *lastLine;

public slots:
    void SpawnClassEntity(bool checked);
    void SpawnConnectionLine(bool checked);
    void ChangeConnectionLine(bool checked);
    void RemoveClassEntity(bool checked);
    void RemoveConnectionLine(bool checked);

private:
    std::vector<QWidget*> focusList; //vector of 2 last selected entities

};

#endif // SCENE_H
