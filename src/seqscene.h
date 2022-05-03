#ifndef SEQSCENE_H
#define SEQSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsProxyWidget>
#include <QGraphicsPolygonItem>
#include "seqline.h"
#include <QComboBox>

class SeqEntity;

class seqScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit seqScene(QObject *parent = nullptr);
    /*
     * @name updateFocusList
     * @brief updates vector of 2 last selected entities
     * @param item -> pointer to last selected entity
    */
    void updateFocusList(QWidget *item);
    void updateConnections(QWidget *item);

    std::vector<SeqEntity*> entities;
    std::vector<QWidget*> focusList;
    std::vector<SeqLine*> connections;

    SeqLine *lastLine;

public slots:
    void SpawnEntity(bool checked);
    void SpawnConnectionLine(bool checked);
    void ChangeConnectionLine(bool checked);
    void RemoveEntity(bool checked);
    void RemoveConnectionLine(bool checked);
};

#endif // SEQSCENE_H
