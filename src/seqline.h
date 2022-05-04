#ifndef SEQLINE_H
#define SEQLINE_H

#include <QWidget>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QComboBox>

class SeqEntity;
class ClassStorage;

class SeqLine : public QGraphicsLineItem, public QWidget
{
public:
    /*
     * @name Line constructor
    */
    explicit SeqLine(QWidget *parent = nullptr);
    /*
     * @name Line destructor
    */
    ~SeqLine();
    /*
     * @name setPoints
     * @brief sets pointers to 2 entities, both represent start & end points of line
     * @param first -> start point for line
     * @param last -> end point for line
    */
    void setPoints(SeqEntity *first, SeqEntity *last);
    /*
     * @name setMarkers
     * @brief sets pointers to 3 markers
     * @param ag -> marker for aggregation line
     * @param co -> marker for composition line
     * @param ge -> marker for generalization line /TODO REWORK THIS COMMENT
    */
    void setMarkers(QGraphicsPolygonItem *fu, QGraphicsPolygonItem *ar, QGraphicsPolygonItem *b1, QGraphicsPolygonItem *b2, QComboBox *cbox);
    /*
     * @name setPosition
     * @brief updates position of line and its markers
    */
    void setPosition();
    /*
     * @name changeType
     * @brief changes type of line, displays correct marker and sets offsets
    */
    void changeType();
    /*
     * @name changeColor
     * @brief changes color of the line and its marker
     * @param color
    */
    void changeColor(Qt::GlobalColor color);
    /*
     * @name deleteMarkers
     * @brief deletes all three markers of this line from scene
    */
    void deleteMarkers();
    void updateData(ClassStorage *info);

    SeqEntity *start;
    SeqEntity *end;
    QGraphicsPolygonItem *full, *arrow, *blue1, *blue2;
    //position points for line
    int x1, x2, y1, y2;
    int type; //type of line
    int mouseOffset;
    QComboBox *box;

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

private:
    int startOffset;
    int endOffset;
    int markerOffset;
    int rotate; //rotation for markers
};

#endif // SEQLINE_H
