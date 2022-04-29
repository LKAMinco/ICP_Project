#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "classentity.h"
#include <QDebug>

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);

    std::vector<QGraphicsProxyWidget*> entities;

public slots:
    void SpawnClassEntity(bool checked);

signals:

};

#endif // SCENE_H
