#ifndef SEQSCENE_H
#define SEQSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsProxyWidget>
#include <QGraphicsPolygonItem>

class seqScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit seqScene(QObject *parent = nullptr);

public slots:
    void SpawnClassEntity(bool checked);
    void SpawnConnectionLine(bool checked);
    void ChangeConnectionLine(bool checked);
    void RemoveClassEntity(bool checked);
    void RemoveConnectionLine(bool checked);
};

#endif // SEQSCENE_H
