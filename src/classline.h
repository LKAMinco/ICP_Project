#ifndef CLASSLINE_H
#define CLASSLINE_H

#include <QObject>
#include <QWidget>
#include <QDebug>

#include "classentity.h"

class ClassLine : public QWidget
{
    Q_OBJECT
public:
    explicit ClassLine(QWidget *parent = nullptr);
    void setPoints(QWidget *first, QWidget *last);

    QWidget *start;
    QWidget *end;

signals:

};

#endif // CLASSLINE_H
