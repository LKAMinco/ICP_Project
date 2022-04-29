#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "classentity.h"

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);

    std::vector<QGraphicsProxyWidget*> entities;

    void spawnItem();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

signals:

};

#endif // SCENE_H
