#ifndef CLASSENTITY_H
#define CLASSENTITY_H

#include <QFrame>
#include <QGraphicsSceneMouseEvent>

namespace Ui {
class ClassEntity;
}

class ClassEntity : public QFrame
{
    Q_OBJECT

public:
    explicit ClassEntity(QWidget *parent = nullptr);
    ~ClassEntity();

private:
    Ui::ClassEntity *ui;
};

#endif // CLASSENTITY_H
