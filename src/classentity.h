#ifndef CLASSENTITY_H
#define CLASSENTITY_H

#include <QFrame>
#include <string>
#include <iostream>
#include <QLineEdit>
#include <vector>
#include <QGraphicsSceneMouseEvent>

class EntityLine{
public:
    bool is_argument = false;
    int type = -1;
    int operands = -1;
    std::string name = "";
    QLineEdit *line_edit;
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

private:
    Ui::ClassEntity *ui;
    unsigned int current_height = 74;
    unsigned int num_of_lines = 0;
    std::vector<EntityLine*> entity_lines;
    std::string line_name = "";
    int index_of_first_attrib = -1;
};

#endif // CLASSENTITY_H
