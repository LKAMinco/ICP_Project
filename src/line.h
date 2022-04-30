#ifndef LINE_H
#define LINE_H

#include <QObject>
#include <QWidget>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <QDebug>

class Line : public QGraphicsLineItem
{
public:
    explicit Line(QWidget *parent = nullptr);
    void setPoints(QWidget *first, QWidget *last);
    void setPosition();

    QWidget *start;
    QWidget *end;

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);

};

#endif // LINE_H
