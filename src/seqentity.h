/**
 * ICP Project 2022 
 * @file seqentity.h
 * @brief header file for sequence diagram's entity
 * @author Jakub Julius Smykal (xsmyka01)
 * @author Milan Hrabovsky (xhrabo15)
 */

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

/**
 * @class SeqEntity
 * @brief class for entity in sequence diagram
*/
class SeqEntity : public QFrame
{
    Q_OBJECT

public:
    /**
     * @name SeqEntity
     * @brief constructor
     * @param parent
    */
    explicit SeqEntity(QWidget *parent = nullptr);
    /**
     * @name SeqEntity
     * @brief destructor
    */
    ~SeqEntity();
    /**
     * @name setColor
     * @brief changes color of line in entity
     * @param color
    */
    void setColor(Qt::GlobalColor color);
    /**
     * @name updateScene
     * @brief notifies scene about change in entity's combobox
     * @param scene
    */
    void updateScene(seqScene *scene);
    /**
     * @name updateData
     * @brief updates data in combobox
     * @param info - pointer to ClassStorage
    */
    void updateData(ClassStorage *info);
    /**
     * @name insertAllDaata
     * @brief insterts data to combobox from ClassStorage
     * @param info - pointer to ClassStorage
    */
    void insertAllData(ClassStorage *info);

    seqScene *curScene;
    QFrame *line; //size 60-720 px
    Ui::SeqEntity *ui;
    QComboBox *box;


private slots:
    /**
     * @name on_plusButton_clicked
     * @brief increases line's length
    */
    void on_plusButton_clicked();
    /**
     * @name on_minusButton_clicked
     * @brief decreases line's length
    */
    void on_minusButton_clicked();

protected:
    /**
     * @name mousePressEvent
     * @param event
    */
    virtual void mousePressEvent(QMouseEvent *event);
    /**
     * @name mouseMoveEvent
     * @param event
    */
    virtual void mouseMoveEvent(QMouseEvent *event);

private:
    QPoint offset;
};

#endif // SEQENTITY_H
