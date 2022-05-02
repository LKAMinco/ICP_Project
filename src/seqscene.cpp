#include "seqscene.h"
#include <QDebug>

seqScene::seqScene(QObject *parent) : QGraphicsScene(parent)
{

}

void seqScene::SpawnClassEntity(bool checked){
    qDebug() << "spawn entity";
}

void seqScene::SpawnConnectionLine(bool checked){
    qDebug() << "spawn connection";
}

void seqScene::ChangeConnectionLine(bool checked){
    qDebug() << "update connection";
}

void seqScene::RemoveConnectionLine(bool checked){
    qDebug() << "remove connection";
}

void seqScene::RemoveClassEntity(bool checked){
    qDebug() << "remove entity";
}
