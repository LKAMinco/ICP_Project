#include "classentity.h"
#include "ui_classentity.h"
#include <QDebug>

ClassEntity::ClassEntity(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ClassEntity)
{
    ui->setupUi(this);
    this->move(QCursor::pos().x(),QCursor::pos().y());
    this->setMouseTracking(true);
}


ClassEntity::~ClassEntity()
{
    delete ui;
}

//Function catches mouse press event -> entity select and mouse offset
void ClassEntity::mousePressEvent(QMouseEvent *event){
    offset = event->pos();
    if(event->buttons() == Qt::RightButton){
        curScene->updateFocusList(ui->line->parentWidget());
    }
}

//Function catches mouse move event -> changes position of entity
void ClassEntity::mouseMoveEvent(QMouseEvent *event){
    if(event->buttons() == Qt::LeftButton)
    {
        this->move(mapToParent(event->pos() - offset));
        curScene->updateConnections(ui->line->parentWidget());
    }
}

//Function updates pointer to current scene
void ClassEntity::updateScene(Scene *scene){
    curScene = scene;
}
