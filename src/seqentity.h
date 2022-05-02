#ifndef SEQENTITY_H
#define SEQENTITY_H

#include <QFrame>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <seqscene.h>

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
