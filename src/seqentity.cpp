#include "seqentity.h"
#include "ui_seqentity.h"
#include "QDebug"

SeqEntity::SeqEntity(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SeqEntity)
{
    ui->setupUi(this);
    this->move(100,40);
    foreach (auto *child , this->children()){
        if (child->objectName() == "line")
            line = qobject_cast<QFrame*>(child);
    }
    this->move(QCursor::pos().x(),QCursor::pos().y());
    this->setMouseTracking(true);

    setColor(Qt::gray);

}

SeqEntity::~SeqEntity()
{
    delete ui;
}

void SeqEntity::on_plusButton_clicked()
{
    if(line->height() <= 660){
        line->setFixedHeight(line->height() + 60);
        this->resize(this->width(), this->height() + 60);
    }
}

void SeqEntity::on_minusButton_clicked()
{
    if(line->height() >= 60){
        line->setFixedHeight(line->height() - 60);
        this->resize(this->width(), this->height() - 60);
    }
}

//Function catches mouse press event -> entity select and mouse offset
void SeqEntity::mousePressEvent(QMouseEvent *event){
    offset = event->pos();
    if(event->buttons() == Qt::RightButton){
        curScene->updateFocusList(this->line->parentWidget());
    }
}

//Function catches mouse move event -> changes position of entity
void SeqEntity::mouseMoveEvent(QMouseEvent *event){
    if(event->buttons() == Qt::LeftButton)
    {
        this->move(mapToParent(event->pos() - offset));
        //curScene->updateConnections(ui->line->parentWidget());
    }
}

void SeqEntity::setColor(Qt::GlobalColor color){
    if (color == Qt::red)
        line->setStyleSheet("background-color: red");
    else
        line->setStyleSheet("background-color: lightgray");
}

void SeqEntity::updateScene(seqScene *scene){
    this->curScene = scene;
}
