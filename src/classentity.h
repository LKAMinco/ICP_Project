#ifndef CLASSENTITY_H
#define CLASSENTITY_H

#include <QFrame>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include "scene.h"

namespace Ui {
class ClassEntity;
}

class ClassEntity : public QFrame
{
    Q_OBJECT

public:
    explicit ClassEntity(QWidget *parent = nullptr);
    ~ClassEntity();
    void updateScene(Scene *scene);
protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);

private:
    Ui::ClassEntity *ui;
    QPoint offset;
    Scene *curScene;
};

#endif // CLASSENTITY_H
