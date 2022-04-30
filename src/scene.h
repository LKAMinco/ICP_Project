#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);
    void updateFocusList(QWidget *item);

    std::vector<QGraphicsProxyWidget*> entities;
    std::vector<QGraphicsProxyWidget*> connections;

public slots:
    void SpawnClassEntity(bool checked);
    void SpawnConnectionLine(bool checked);

private:
    std::vector<QWidget*> focusList;

};

#endif // SCENE_H
