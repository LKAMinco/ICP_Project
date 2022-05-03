#ifndef CLASSENTITY_H
#define CLASSENTITY_H

#define PUBLIC "+"
#define PRIVATE "-"
#define PROTECTED "#"
#define PACKAGE "~"

//TODO pozret či treba naozaj všetky knižnice
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

class EntityLine: public QFrame{
    Q_OBJECT
public:
    std::string window_name = "";
    bool is_attrib = false;
    //std::string type = "bool";
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
    std::vector<EntityLine*> entity_lines;
    int index_of_last_attrib = -1;
    QLineEdit* class_title;

protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);

public slots:
    void on_add_method_clicked();

    void on_add_attrib_clicked();

    void updateValue(const QString &text);

    void on_remove_method_clicked();

    void removeLine();

private:
    Ui::ClassEntity *ui;
    QPoint offset;
    unsigned int current_height = 54;
    unsigned int num_of_lines = 0;
    unsigned int current_num_of_lines = 0;
    std::string line_name = "";
    QWidget *last_focus;

    void updateOrder();
};

#endif // CLASSENTITY_H
