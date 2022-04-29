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

void ClassEntity::mousePressEvent(QMouseEvent *event){
    offset = event->pos();
}

void ClassEntity::mouseMoveEvent(QMouseEvent *event){
    if(event->buttons() == Qt::LeftButton)
    {
        this->move(mapToParent(event->pos() - offset));
    }
}
