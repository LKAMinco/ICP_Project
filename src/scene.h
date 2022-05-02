#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsProxyWidget>
#include "line.h"
#include <QGraphicsPolygonItem>

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);
    void updateFocusList(QWidget *item);
    void updateConnections(QWidget *item);

    std::vector<QGraphicsProxyWidget*> entities;
    std::vector<Line*> connections;
    Line *lastLine;

public slots:
    void SpawnClassEntity(bool checked);
    void SpawnConnectionLine(bool checked);
    void ChangeConnectionLine(bool checked);
    void RemoveClassEntity(bool checked);
    void RemoveConnectionLine(bool checked);

private:
    std::vector<QWidget*> focusList;

};

#endif // SCENE_H
