#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "scene.h"

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

private:
    Ui::MainWindow *ui;
    QAction *spawnClass;
    Scene *scene;
};
#endif // MAINWINDOW_H
