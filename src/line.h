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

class Line : public QGraphicsLineItem, public QWidget
{
public:
    explicit Line(QWidget *parent = nullptr);
    ~Line();
    void setPoints(QWidget *first, QWidget *last);
    void setMarkers(QGraphicsPolygonItem *ag, QGraphicsPolygonItem *co, QGraphicsPolygonItem *ge);
    void setPosition();
    void changeType();

    QWidget *start;
    QWidget *end;
    QGraphicsPolygonItem *aggreg, *compos, *gener;

    int x1, x2, y1, y2;

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    int type;
    int offset;
    int curOffset;
    int lineOffset;
    int rotate;

};

#endif // LINE_H
