#ifndef CLASSSTORAGE_H
#define CLASSSTORAGE_H

#include "classentity.h"
#include <QString>

class MainWindow;

class MethodStorage
{
public:
    MethodStorage(QString objName);

    QString objectName;
    QString content;
};

class EntityStorage
{
public:
    EntityStorage(QString objName);
    ~EntityStorage();

    QString objectName;
    QString content;
    std::vector<MethodStorage*> methods;
};

class ClassStorage
{
public:
    ClassStorage(MainWindow *win);
    ~ClassStorage();

    void CreateEntity(QString objName);
    void UpdateEntity(QString objName, QString contentName, QString elemName);
    void RemoveEntity(QString objName);
    void CreateMethod(QString objName, QString elemName);
    void RemoveMethod(QString objName, QString elemName);
    void updateSeq();
    void updateSeqLine();

    std::vector<EntityStorage*> entities;
    MainWindow *window;
};

#endif // CLASSSTORAGE_H
