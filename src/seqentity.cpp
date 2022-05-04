#include "seqentity.h"
#include "ui_seqentity.h"
#include "QDebug"
#include "classstorage.h"

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
    this->box = ui->comboBox;
    setColor(Qt::gray);
    ui->comboBox->addItem("");
    /*
    ui->comboBox->addItem("asd");
    ui->comboBox->setCurrentIndex(1);*/
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
    if(line->height() >= 120){
        line->setFixedHeight(line->height() - 60);
        this->resize(this->width(), this->height() - 60);
        curScene->updateConnections(ui->line->parentWidget());
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
        curScene->updateConnections(ui->line->parentWidget());
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

void SeqEntity::updateData(ClassStorage *info){
    if(ui->comboBox->count() < info->entities.size() + 1){
        ui->comboBox->addItem(info->entities.back()->content);
    }
    else if(ui->comboBox->count() == info->entities.size() + 1){
        for(int i = 0; i < info->entities.size(); i++){
            if(ui->comboBox->itemText(i + 1) != info->entities[i]->content){
                ui->comboBox->setItemText(i + 1, info->entities[i]->content);
                break;
            }
        }
    }
    else{
        for(int i = 0; i < info->entities.size(); i++){
            if(ui->comboBox->itemText(i + 1) != info->entities[i]->content){
                if(ui->comboBox->currentIndex() == i + 1)
                    ui->comboBox->setCurrentIndex(0);
                ui->comboBox->removeItem(i + 1);
            }
        }
        if(ui->comboBox->count() != info->entities.size() + 1){
            if(ui->comboBox->currentIndex() == ui->comboBox->count() - 1)
                ui->comboBox->setCurrentIndex(0);
            ui->comboBox->removeItem(ui->comboBox->count() - 1);
        }
    }
}
