/**
 * ICP Project 2022 
 * @file seqscene.h
 * @brief header file for sequence diagram's scene
 * @author Jakub Julius Smykal (xsmyka01)
 * @author Milan Hrabovsky (xhrabo15)
 */

#ifndef SEQSCENE_H
#define SEQSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsProxyWidget>
#include <QGraphicsPolygonItem>
#include "seqline.h"
#include <QComboBox>
#include "classstorage.h"

class SeqEntity;

/**
 * @class seqScene
 * @brief class for sequence diagram scene
*/
class seqScene : public QGraphicsScene
{
    Q_OBJECT
public:
    /**
     * @name seqScene
     * @brief constructor
     * @param parent
    */
    explicit seqScene(QObject *parent = nullptr);
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

    std::vector<SeqEntity*> entities;
    std::vector<QWidget*> focusList;
    std::vector<SeqLine*> connections;

    SeqLine *lastLine;
    ClassStorage *info;
    int spawnSeqCount;

public slots:
    /**
     * @name SpawnEntity
     * @brief Slot to spawn entity in sequence diagram
     * @param checked
    */
    void SpawnEntity();
    /**
     * @name SpawnConnectionLine
     * @brief Slot to spawn connectin in sequence diagram
     * @param checked
    */
    void SpawnConnectionLine();
    /**
     * @name ChangeConnectionLine
     * @brief Slot to change type of connection in sequence diagram
     * @param checked
    */
    void ChangeConnectionLine();
    /**
     * @name RemoveEntity
     * @brief Slot to remove entity in sequence diagram
     * @param checked
    */
    void RemoveEntity();
    /**
     * @name RemoveConnectionLine
     * @brief Slot to remove connection in sequence diagram
     * @param checked
    */
    void RemoveConnectionLine();
    /**
     * @name updateDataLines
     * @brief Slot to update data in connectinos, where entity's class is changed
     * @param text
    */
    void updateDataLines();
};

#endif // SEQSCENE_H
