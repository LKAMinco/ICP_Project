#include "classentity.h"
#include "ui_classentity.h"

ClassEntity::ClassEntity(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ClassEntity)
{
    ui->setupUi(this);
}

ClassEntity::~ClassEntity()
{
    delete ui;
}
