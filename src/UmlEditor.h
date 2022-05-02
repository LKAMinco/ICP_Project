#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "scene.h"
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QFile>
#include <QTextStream>
#include <regex>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_graphicsView_customContextMenuRequested(const QPoint &pos);

    void on_actionSave_triggered();

    void on_actionSave_as_triggered();

    void on_actionOpen_triggered();

    QString genJson();

private:
    Ui::MainWindow *ui;
    QAction *spawnClass;
    QAction *spawnConnect;
    QAction *changeLine;
    QAction *removeClass;
    QAction *removeConnect;
    Scene *scene;
    QMenu *menu;
    QString file_name = "";
    QString file_path = "";
};
#endif // MAINWINDOW_H
