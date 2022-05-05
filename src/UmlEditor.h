/**
 * ICP Project 2022 
 * @file UmlEditor.h
 * @brief header file for app's main window
 * @author Jakub Julius Smykal (xsmyka01)
 * @author Milan Hrabovsky (xhrabo15)
 */

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
#include "classstorage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @class MainWindow
 * @brief class for app's main window
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @name MainWindow
     * @brief constructor
    */
    MainWindow(QWidget *parent = nullptr);
    /**
     * @name MainWindow
     * @brief destructor
    */
    ~MainWindow();

    int seqIndex;
    bool activeSeq;
    ClassStorage *info;
    std::vector <seqScene*> seqList;

private slots:
    /**
     * @name on_graphicsView_customContextMenuRequested
     * @brief Slot to open context open
     * @param pos - position
    */
    void on_graphicsView_customContextMenuRequested(const QPoint &pos);
    /**
     * @name on_actionSave_triggered
     * @brief Slot to save data from diagrams
    */
    void on_actionSave_triggered();
    /**
     * @name on_actionSave_as_triggered
     * @brief Slot to save data to file with path from diagrams
    */
    void on_actionSave_as_triggered();
    /**
     * @name on_actionOpen_triggered
     * @brief Slot to open file and reads its data
    */
    void on_actionOpen_triggered();
    /**
     * @name genJson
     * @brief Slot to generate json output
    */
    QString genJson();
    /**
     * @name on_actionAdd_triggered
     * @brief Slot to add new sequence scene
    */
    void on_actionAdd_triggered();
    /**
     * @name on_actionRemove_triggered
     * @brief Slot to remove opened sequence scene
    */
    void on_actionRemove_triggered();
    /**
     * @name on_actionSeq1_triggered
     * @brief Slot to switches window to sequence scene
    */
    void on_actionSeq1_triggered();
    /**
     * @name on_actionClass_triggered
     * @brief Slot to switches window to class scene
    */
    void on_actionClass_triggered();
    /**
     * @name on_actionNew_triggered
     * @brief Slot to reset all scenes
    */
    void on_actionNew_triggered();
    /**
     * @name on_actionSwitch_Seq_Left_triggered
     * @brief Slot to change active sequence scene to previous
    */
    void on_actionSwitch_Seq_Left_triggered();
    /**
     * @name on_actionSwitch_Seq_Right_triggered
     * @brief Slot to change active sequence scene to next
    */
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

    QMenu *menu;
    QString file_path = "";
};
#endif // MAINWINDOW_H
