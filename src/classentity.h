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
class ClassEntity : public QFrame
{
    Q_OBJECT

public:
    explicit ClassEntity(QWidget *parent = nullptr);
    ~ClassEntity();

private slots:
    void on_add_method_clicked();

    void on_add_attrib_clicked();

    void updateValue(const QString &text);

    void on_remove_method_clicked();

    void removeLine();

private:
    Ui::ClassEntity *ui;
    unsigned int current_height = 54;
    unsigned int num_of_lines = 0;
    unsigned int current_num_of_lines = 0;
    std::vector<EntityLine*> entity_lines;
    std::string line_name = "";
    int index_of_last_attrib = -1;
    QWidget *last_focus;

    void updateOrder();
};

#endif // CLASSENTITY_H
