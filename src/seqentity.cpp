/**
 * ICP Project 2022 
 * @file seqentity.cpp
 * @brief implementation of methods in SeqEntity class
 * @author Jakub Julius Smykal (xsmyka01)
 * @author Milan Hrabovsky (xhrabo15)
 */

#include "seqentity.h"
#include "ui_seqentity.h"
#include "QDebug"
#include "classstorage.h"

//Constructor
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

    //sets position to cursor's location
    this->move(QCursor::pos().x(),QCursor::pos().y());
    this->setMouseTracking(true);
    this->box = ui->comboBox;
    setColor(Qt::gray);
    ui->comboBox->addItem("");
}

//Destructor
SeqEntity::~SeqEntity()
{
    delete ui;
}

//Function increases length of line
void SeqEntity::on_plusButton_clicked()
{
    if(line->height() < 720){
        line->setFixedHeight(line->height() + 60);
        this->resize(this->width(), this->height() + 60);
    }
}

//Function decreases length of line
void SeqEntity::on_minusButton_clicked()
{
    if(line->height() > 60){
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

//Function changes color of line
void SeqEntity::setColor(Qt::GlobalColor color){
    if (color == Qt::red)
        line->setStyleSheet("background-color: red");
    else if (color == Qt::green)
        line->setStyleSheet("background-color: lightgreen");
    else
        line->setStyleSheet("background-color: lightgray");
}

//Function updates curScene pointer and sets connection for signal
void SeqEntity::updateScene(seqScene *scene){
    this->curScene = scene;
    connect(this->box, &QComboBox::currentTextChanged , curScene, &seqScene::updateDataLines);
}

//Function updates data in entity from ClassStorage
void SeqEntity::updateData(ClassStorage *info){
    //new class was added
    if((unsigned int)ui->comboBox->count() < info->entities.size() + 1){
        ui->comboBox->addItem(info->entities.back()->content);
    }
    //class name was changed
    else if((unsigned int)ui->comboBox->count() == info->entities.size() + 1){
        for(unsigned int i = 0; i < info->entities.size(); i++){
            if(ui->comboBox->itemText(i + 1) != info->entities[i]->content){
                ui->comboBox->setItemText(i + 1, info->entities[i]->content);
                break;
            }
        }
    }
    //class was removed
    else{
        for(unsigned int i = 0; i < info->entities.size(); i++){
            if(ui->comboBox->itemText(i + 1) != info->entities[i]->content){
                //if class that is being removed was currently selected, remove selection
                if((unsigned int)ui->comboBox->currentIndex() == i + 1)
                    ui->comboBox->setCurrentIndex(0);
                ui->comboBox->removeItem(i + 1);
            }
        }
        //last class was removed
        if((unsigned int)ui->comboBox->count() != info->entities.size() + 1){
            //if class that is being removed was currently selected, remove selection
            if(ui->comboBox->currentIndex() == ui->comboBox->count() - 1)
                ui->comboBox->setCurrentIndex(0);
            ui->comboBox->removeItem(ui->comboBox->count() - 1);
        }
    }
}

//Function insert all data from ClassStorage
void SeqEntity::insertAllData(ClassStorage *info){
    foreach(EntityStorage *item, info->entities){
        ui->comboBox->addItem(item->content);
    }
}
