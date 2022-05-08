/**
 * ICP Project 2022 
 * @file classentity.h
 * @brief header file for entity in class diagram
 * @author Jakub Julius Smykal (xsmyka01)
 * @author Milan Hrabovsky (xhrabo15)
 */

#ifndef CLASSENTITY_H
#define CLASSENTITY_H

#define PUBLIC "+"
#define PRIVATE "-"
#define PROTECTED "#"
#define PACKAGE "~"

//TODO pozret či treba naozaj všetky knižnice | lol to si skontroluj sam
#include <QFrame>
#include <string>
#include <iostream>
#include <QLineEdit>
#include <vector>
#include <QDebug>
#include <QString>
#include <QComboBox>
#include <algorithm>
#include <QEvent>
#include <QMouseEvent>
#include <QPushButton>
#include <regex>
#include <QFileDialog>
#include <QGraphicsSceneMouseEvent>
#include "scene.h"


/**
 * @class EntityLine
 * @brief class for one line in entity in class diagram
*/
class EntityLine: public QFrame{
    Q_OBJECT
public:
    std::string window_name = "";
    bool is_attrib = false;
    //std::string type = "bool"; //TODO remove these comments ?
    //std::string visiblity = "+";
    int entity_height = 0;
    //std::string name = "";
    QLineEdit *line_edit;
    QComboBox *box_visiblity;
    QComboBox *box_type;
    QPushButton *btn;
};


namespace Ui {
class ClassEntity;
}

/**
 * @class ClassEntity
 * @brief class for entities in class diagram
*/
class ClassEntity : public QFrame
{
    Q_OBJECT

public:
    /**
     * @name ClassEntity
     * @brief constructor
    */
    explicit ClassEntity(QWidget *parent = nullptr);
    /**
     * @name ClassEntity
     * @brief destructor
    */
    ~ClassEntity();
    /**
     * @name updateScene
     * @brief sets pointer to active scene
     * @param scene - active class diagram scene
    */
    void updateScene(Scene *scene);
    Scene *curScene;
    std::vector<EntityLine*> entity_lines;
    int index_of_last_attrib = -1;
    QLineEdit* class_title;

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

public slots:
    //add method button
    void on_add_method_clicked();
    //add attribute buttom
    void on_add_attrib_clicked();
    //this function is called, when some text in entity changes
    void updateValue(const QString &text);
    //remove attribute or method button
    void removeLine();

private:
    Ui::ClassEntity *ui;
    QPoint offset;
    unsigned int current_height = 54;
    unsigned int num_of_lines = 0;
    unsigned int current_num_of_lines = 0;
    std::string line_name = "";
    QWidget *last_focus;

};

#endif // CLASSENTITY_H
