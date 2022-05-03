#ifndef SEQENTITY_H
#define SEQENTITY_H

#include <QFrame>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <seqscene.h>

class ClassStorage;

namespace Ui {
class SeqEntity;
}

class SeqEntity : public QFrame
{
    Q_OBJECT

public:
    explicit SeqEntity(QWidget *parent = nullptr);
    ~SeqEntity();

    void setColor(Qt::GlobalColor color);
    void updateScene(seqScene *scene);
    void updateData(ClassStorage *info);

    seqScene *curScene;
    QFrame *line;

private slots:
    void on_plusButton_clicked();
    void on_minusButton_clicked();

protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);

private:
    Ui::SeqEntity *ui;
    QPoint offset;
};

#endif // SEQENTITY_H
