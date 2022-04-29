#include "classentity.h"
#include "ui_classentity.h"
#include <QDebug>

ClassEntity::ClassEntity(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ClassEntity)
{
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
}
