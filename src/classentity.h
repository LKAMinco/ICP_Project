#ifndef CLASSENTITY_H
#define CLASSENTITY_H

#include <QFrame>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include "scene.h"

namespace Ui {
class ClassEntity;
}

/*
 * @class ClassEntity
 * @brief class for entities in class diagram
*/
class ClassEntity : public QFrame
{
    Q_OBJECT

public:
    /*
     * @name ClassEntity constructor
    */
    explicit ClassEntity(QWidget *parent = nullptr);
    /*
     * @name ClassEntity destructor
    */
    ~ClassEntity();
    /*
     * @name updateScene
     * @brief sets pointer to active scene
     * @param active class diagram scene
    */
    void updateScene(Scene *scene);
    Scene *curScene;
protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);

private:
    Ui::ClassEntity *ui;
    QPoint offset;
};

#endif // CLASSENTITY_H
