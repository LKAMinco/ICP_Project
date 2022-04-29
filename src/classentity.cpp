#include "classentity.h"
#include "ui_classentity.h"
#include <QDebug>

ClassEntity::ClassEntity(QWidget *parent) :QFrame(parent),ui(new Ui::ClassEntity){
    ui->setupUi(this);
    this->move(QCursor::pos().x(),QCursor::pos().y());
    qDebug() << "mouse X" << QCursor::pos().x();
    qDebug() << "mouse Y" << QCursor::pos().y();
    qDebug() << "entity X" << this->pos().x();
    qDebug() << "entity Y" << this->pos().y();
}

ClassEntity::~ClassEntity()
{
    delete ui;
    //TODO dorobit destructor na methods
}

void ClassEntity::on_add_method_clicked(){
    current_height += 20;
    if (current_height + 20 - 4 > 222){
        this->resize(208, current_height+24);
    }
    line_name = "line_" + std::to_string(num_of_lines+1);
    QLineEdit *line_edit;
    EntityLine *new_line = new EntityLine;
    line_edit = new QLineEdit(this);
    line_edit->setObjectName(QStringLiteral("line_x"));
    line_edit->setGeometry(QRect(4, current_height, 200, 20));
    line_edit->setFrame(true);
    line_edit->show();
    new_line->line_edit = line_edit;
    entity_lines.push_back(new_line);
}

void ClassEntity::on_add_attrib_clicked()
{
    for(unsigned int i = 0; i < entity_lines.size();i++){
        entity_lines[i]->line_edit->setStyleSheet(QStringLiteral("background-color: rgb(38, 0, 255);"));
    }
}
