/**
 * ICP Project 2022 
 * @file classentity.cpp
 * @brief implementation of methods in ClassEntity class
 * @author Jakub Julius Smykal (xsmyka01)
 * @author Milan Hrabovsky (xhrabo15)
 */

#include "classentity.h"
#include "ui_classentity.h"
#include "UmlEditor.h"

ClassEntity::ClassEntity(QWidget *parent) : QFrame(parent), ui(new Ui::ClassEntity) {
    ui->setupUi(this);
    this->move(QCursor::pos().x(), QCursor::pos().y());
    this->setMouseTracking(true);
    class_title = ui->title;
    connect(class_title, &QLineEdit::textEdited, this, &ClassEntity::updateValue);
}


ClassEntity::~ClassEntity() {
    delete ui;
    //TODO dorobit destructor na vector
}

//Function catches mouse press event -> entity select and mouse offset
void ClassEntity::mousePressEvent(QMouseEvent *event) {
    offset = event->pos();
    if (event->buttons() == Qt::RightButton) {
        curScene->updateFocusList(ui->line->parentWidget());
    }
}

//Function catches mouse move event -> changes position of entity
void ClassEntity::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() == Qt::LeftButton) {
        this->move(mapToParent(event->pos() - offset));
        curScene->updateConnections(ui->line->parentWidget());
    }
}

//Function updates pointer to current scene
void ClassEntity::updateScene(Scene *scene) {
    curScene = scene;
}

void ClassEntity::on_add_method_clicked() {
    current_height += 20;
    //resize current frame for correct height
    if (current_height + 20 - 4 > 222) {
        this->resize(278, current_height + 24);
    }
    num_of_lines++;
    line_name = "line" + std::to_string(num_of_lines);
    QLineEdit *line_edit;
    QComboBox *vis_box;
    QPushButton *push_button;
    EntityLine *new_line = new EntityLine;

    //spawns combo box for visiblity
    vis_box = new QComboBox(this);
    vis_box->addItem(QString());
    vis_box->addItem(QString());
    vis_box->addItem(QString());
    vis_box->addItem(QString());
    vis_box->setObjectName(QString::fromStdString("visBox_" + line_name));
    vis_box->setGeometry(QRect(4, current_height, 40, 20));
    vis_box->setStyleSheet("QFrame { border: 1px solid black }");
    //set values to visiblity box
    vis_box->setItemText(0, QApplication::translate("MainWindow", "+", nullptr));
    vis_box->setItemText(1, QApplication::translate("MainWindow", "-", nullptr));
    vis_box->setItemText(2, QApplication::translate("MainWindow", "#", nullptr));
    vis_box->setItemText(3, QApplication::translate("MainWindow", "~", nullptr));
    vis_box->show();
    //spanws line for method name
    line_edit = new QLineEdit(this);
    line_edit->setObjectName(QString::fromStdString(line_name));
    line_edit->setGeometry(QRect(44, current_height, 210, 20));
    line_edit->setFrame(true);
    line_edit->show();
    //spawns button for remove current method
    push_button = new QPushButton(this);
    push_button->setObjectName(QString::fromStdString("btn_" + line_name));
    push_button->setGeometry(QRect(254, current_height, 20, 20));
    push_button->setStyleSheet(QStringLiteral("background-color: rgb(176, 28, 31);"));
    push_button->setText(QApplication::translate("ClassEntity", "X", nullptr));
    push_button->show();

    new_line->box_visiblity = vis_box;
    new_line->line_edit = line_edit;
    new_line->window_name = line_name;
    new_line->btn = push_button;
    new_line->is_attrib = false;
    new_line->entity_height = current_height;

    connect(line_edit, &QLineEdit::textEdited, this, &ClassEntity::updateValue);
    connect(vis_box, &QComboBox::currentTextChanged, this, &ClassEntity::updateValue);
    connect(push_button, &QPushButton::clicked, this, &ClassEntity::removeLine);
    entity_lines.push_back(new_line);
    current_num_of_lines++;

    curScene->createMethodData(this->objectName(), line_edit->objectName(), line_edit->text());
}


void ClassEntity::on_add_attrib_clicked() {
    int height;
    current_height += 20;
    //resize current frame for correct height
    if (current_height + 20 - 4 > 222) {
        this->resize(278, current_height + 24);
    }
    num_of_lines++;
    line_name = "line" + std::to_string(num_of_lines);
    QLineEdit *line_edit;
    QComboBox *vis_box;
    QComboBox *type_box;
    QPushButton *push_button;
    EntityLine *new_line = new EntityLine;
    EntityLine *tmp = new EntityLine;
    entity_lines.push_back(tmp);
    //moves all methods one line down, so the attribute can be spawned in correct position
    for (int i = entity_lines.size() - 2; i > index_of_last_attrib; i--) {
        entity_lines[i]->entity_height += 20;
        entity_lines[i]->line_edit->move(44, entity_lines[i]->entity_height);
        entity_lines[i]->box_visiblity->move(4, entity_lines[i]->entity_height);
        entity_lines[i]->btn->move(254, entity_lines[i]->entity_height);
        entity_lines[i + 1] = entity_lines[i];
    }
    index_of_last_attrib == -1 ? height = 74 : height = entity_lines[index_of_last_attrib]->entity_height + 20;
    index_of_last_attrib++;
    //spanws box for visiblity
    vis_box = new QComboBox(this);
    vis_box->addItem(QString());
    vis_box->addItem(QString());
    vis_box->addItem(QString());
    vis_box->addItem(QString());
    vis_box->setObjectName(QString::fromStdString("visBox_" + line_name));
    vis_box->setGeometry(QRect(4, height, 40, 20));

    vis_box->setItemText(0, QApplication::translate("MainWindow", PUBLIC, nullptr));
    vis_box->setItemText(1, QApplication::translate("MainWindow", PRIVATE, nullptr));
    vis_box->setItemText(2, QApplication::translate("MainWindow", PROTECTED, nullptr));
    vis_box->setItemText(3, QApplication::translate("MainWindow", PACKAGE, nullptr));
    vis_box->setStyleSheet("QFrame { border: 1px solid black }");
    vis_box->show();
    //spanws line for attribute name
    line_edit = new QLineEdit(this);
    line_edit->setObjectName(QString::fromStdString(line_name));
    line_edit->setGeometry(QRect(44, height, 140, 20));
    line_edit->setFrame(true);
    line_edit->show();
    //spanws box for type of attribute
    type_box = new QComboBox(this);
    type_box->addItem(QString());
    type_box->addItem(QString());
    type_box->addItem(QString());
    type_box->addItem(QString());
    type_box->addItem(QString());
    type_box->setObjectName(QString::fromStdString("typeBox_" + line_name));
    type_box->setGeometry(QRect(184, height, 70, 20));

    type_box->setItemText(0, QApplication::translate("MainWindow", "bool", nullptr));
    type_box->setItemText(1, QApplication::translate("MainWindow", "int", nullptr));
    type_box->setItemText(2, QApplication::translate("MainWindow", "float", nullptr));
    type_box->setItemText(3, QApplication::translate("MainWindow", "char", nullptr));
    type_box->setItemText(4, QApplication::translate("MainWindow", "string", nullptr));
    type_box->setStyleSheet("QFrame { border: 1px solid black }");
    type_box->show();
    //spawns button for remove current attribute
    push_button = new QPushButton(this);
    push_button->setObjectName(QString::fromStdString("btn_" + line_name));
    push_button->setGeometry(QRect(254, height, 20, 20));
    push_button->setStyleSheet(QStringLiteral("background-color: rgb(176, 28, 31);"));
    push_button->setText(QApplication::translate("ClassEntity", "X", nullptr));
    push_button->show();

    new_line->box_visiblity = vis_box;
    new_line->line_edit = line_edit;
    new_line->box_type = type_box;
    new_line->window_name = line_name;
    new_line->btn = push_button;
    new_line->is_attrib = true;
    new_line->entity_height = height;

    connect(line_edit, &QLineEdit::textChanged, this, &ClassEntity::updateValue);
    connect(vis_box, &QComboBox::currentTextChanged, this, &ClassEntity::updateValue);
    connect(type_box, &QComboBox::currentTextChanged, this, &ClassEntity::updateValue);
    connect(push_button, &QPushButton::clicked, this, &ClassEntity::removeLine);
    entity_lines[index_of_last_attrib] = new_line;
    current_num_of_lines++;
}

void
ClassEntity::updateValue(const QString &text) {
    QObject *obj = sender();

    curScene->updateData(this->objectName(), text, obj->objectName());
}

//remove current line of method or attribute
void ClassEntity::removeLine() {
    EntityLine *tmp = new EntityLine;
    int index = -1;
    QObject *obj = sender();
    std::string name = obj->objectName().toStdString();
    std::string result;
    std::regex e("(?:btn_)");
    std::regex_replace(std::back_inserter(result), name.begin(), name.end(), e, "$2");
    //finds index of line which has to be deleted
    for (unsigned int i = 0; i < entity_lines.size(); i++) {
        if (result == entity_lines[i]->window_name) {
            index = i;
            tmp = entity_lines[index];
            for (unsigned int i = index; i < entity_lines.size() - 1; i++) {
                entity_lines[i] = entity_lines[i + 1];
            }
            break;
        }
    }
    if (current_num_of_lines != 0) {
        entity_lines.back() = tmp;
        delete entity_lines.back()->line_edit;
        delete entity_lines.back()->box_visiblity;
        if (entity_lines.back()->is_attrib) {
            delete entity_lines.back()->box_type;
            index_of_last_attrib--;
        }
        entity_lines.pop_back();
        //updates positions of lines so there is no space after deleting line
        for (unsigned int i = index; i < entity_lines.size(); i++) {
            entity_lines[i]->entity_height -= 20;
            entity_lines[i]->line_edit->move(44, entity_lines[i]->entity_height);
            entity_lines[i]->box_visiblity->move(4, entity_lines[i]->entity_height);
            if (entity_lines[i]->is_attrib) {
                entity_lines[i]->box_type->move(184, entity_lines[i]->entity_height);
            }
            if (entity_lines[i]->btn != nullptr)
                entity_lines[i]->btn->move(254, entity_lines[i]->entity_height);
        }
        current_num_of_lines--;
        current_height == 54 ? current_height = 54 : current_height -= 20;
        current_height > 202 ? this->resize(278, current_height + 24) : this->resize(278, 222);
    }
    curScene->removeMethodData(this->objectName(), QString::fromStdString(result));
    delete tmp;
    delete obj;
}


