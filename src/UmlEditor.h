#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "scene.h"
#include "seqscene.h"
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

/*
 * @class MainWindow
 * @brief class for app's main window
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /*
     * @name MainWindow constructor
    */
    MainWindow(QWidget *parent = nullptr);
    /*
     * @name MainWindow destructor
    */
    ~MainWindow();

    int seqIndex;
    bool activeSeq;

private slots:
    void on_graphicsView_customContextMenuRequested(const QPoint &pos);

    void on_actionSave_triggered();

    void on_actionSave_as_triggered();

    void on_actionOpen_triggered();

    QString genJson();

    void on_actionAdd_triggered();

    void on_actionRemove_triggered();

    void on_actionSeq1_triggered();

    void on_actionClass_triggered();

    void on_actionNew_triggered();

    void on_actionSwitch_Seq_Left_triggered();

    void on_actionSwitch_Seq_Right_triggered();

private:
    Ui::MainWindow *ui;
    //buttons in context menu for class diagram
    QAction *spawnClass;
    QAction *spawnConnect;
    QAction *changeLine;
    QAction *removeClass;
    QAction *removeConnect;

    Scene *classScene;
    std::vector <seqScene*> seqList;

    QMenu *menu;
    QString file_path = "";
};
#endif // MAINWINDOW_H
