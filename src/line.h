#ifndef LINE_H
#define LINE_H

#include <QObject>
#include <QWidget>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <QDebug>
#include <QPainter>
#include <QGraphicsPolygonItem>


class ClassEntity;
/*
 * @class Line
 * @brief class for lines in class diagram
*/
class Line : public QGraphicsLineItem, public QWidget
{
    //Q_OBJECT
public:
    /*
     * @name Line constructor
    */
    explicit Line(QWidget *parent = nullptr);
    /*
     * @name Line destructor
    */
    ~Line();
    /*
     * @name setPoints
     * @brief sets pointers to 2 entities, both represent start & end points of line
     * @param first -> start point for line
     * @param last -> end point for line
    */
    void setPoints(ClassEntity *first, ClassEntity *last);
    /*
     * @name setMarkers
     * @brief sets pointers to 3 markers
     * @param ag -> marker for aggregation line
     * @param co -> marker for composition line
     * @param ge -> marker for generalization line
    */
    void setMarkers(QGraphicsPolygonItem *ag, QGraphicsPolygonItem *co, QGraphicsPolygonItem *ge);
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

    ClassEntity *start;
    ClassEntity *end;
    QGraphicsPolygonItem *aggreg, *compos, *gener;
    //position points for line
    int x1, x2, y1, y2;
    int type; //type of line

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    int offset;
    int curOffset;
    int lineOffset;
    int rotate; //rotation for markers

};

#endif // LINE_H
