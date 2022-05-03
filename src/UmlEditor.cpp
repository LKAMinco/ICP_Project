#include "UmlEditor.h"
#include "ui_UmlEditor.h"
#include "classentity.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionOpen,&QAction::toggled,this,&MainWindow::on_actionOpen_triggered);
    /*auto *scene = new Scene(ui->graphicsView);
    ui->graphicsView->setScene(scene);*/

    //creates new graphics scene and sets its size
    classScene = new Scene(ui->graphicsView);
    ui->graphicsView->setScene(classScene);
    ui->graphicsView->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->graphicsView->setFixedSize(1920,1080);
    classScene->setSceneRect(0,0,1920,1080);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    //creates context menu for class diagram
    menu = new QMenu(this);
    spawnClass = menu->addAction("Create Class Entity");
    connect(spawnClass, &QAction::triggered, classScene, &Scene::SpawnEntity);
    spawnConnect = menu->addAction("Create Connection");
    connect(spawnConnect, &QAction::triggered, classScene, &Scene::SpawnConnectionLine);
    changeLine = menu->addAction("Change Connection");
    connect(changeLine, &QAction::triggered, classScene, &Scene::ChangeConnectionLine);
    removeClass = menu->addAction("Remove Class Entity");
    connect(removeClass, &QAction::triggered, classScene, &Scene::RemoveEntity);
    removeConnect = menu->addAction("Remove Connection");
    connect(removeConnect, &QAction::triggered, classScene, &Scene::RemoveConnectionLine);

    seqList.clear();
    seqIndex = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Spawns context menu on mouse's location
void MainWindow::on_graphicsView_customContextMenuRequested(const QPoint &pos)
{
    if(ui->graphicsView->itemAt(pos)){
        return;
    }
    menu->exec(ui->graphicsView->mapToGlobal(pos));
}

void MainWindow::on_actionSave_triggered()
{
    if(!QString::compare(file_path, "", Qt::CaseSensitive)){
        on_actionSave_as_triggered();
    }
    else
    {
        QFile file(file_path);
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&file);
        out << genJson();
    }


}

void MainWindow::on_actionSave_as_triggered()
{
    std::regex e ("(\\..+)");
    std::string result;
    file_path = QFileDialog::getSaveFileName(this, tr("Save File"),"Untitled",tr("Uml editor files (*.json)"));
    std::string string = file_path.toStdString();
    std::regex_replace (std::back_inserter(result), string.begin(), string.end(), e, "$2");
    result.append(".json");
    file_path = QString::fromStdString(result);
    QFile file(file_path);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << genJson();
}

void MainWindow::on_actionOpen_triggered()
{
    file_path = QFileDialog::getOpenFileName(this, "Open a file", "directoryToOpen","Uml editor files (*.json)");
    QFile file(file_path);
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QByteArray data = file.readAll();
    file.close();
    QJsonParseError errorPtr;
    QJsonDocument doc = QJsonDocument::fromJson(data, &errorPtr);
    if (doc.isNull()) {
        qDebug() << "Parse failed";
    }
    QJsonObject main_obj = doc.object();
    qDebug() << main_obj;
}

QString MainWindow::genJson(){
    QJsonDocument doc;
    QJsonArray arr,arr3;
    QJsonObject windows;
    QJsonObject connections;
    for(auto* item : classScene->entities){
        QJsonArray arr2;
        for(auto * item2 : item->entity_lines){
            if(item2->box_type != nullptr){
                arr2.append((QJsonObject({
                    {"visBox_value",item2->box_visiblity->currentText()},
                    {"lineEdit_value",item2->line_edit->text()},
                    {"boxType_value",item2->box_type->currentText()}
                                         })));
            }
            else
            {
                arr2.append((QJsonObject({
                    {"visBox_value",item2->box_visiblity->currentText()},
                    {"lineEdit_value",item2->line_edit->text()},
                                          })));
            }
        }
        arr.append(QJsonObject({
                    {"class_name",item->class_title->text()},
                    {"g_x", item->pos().x()},
                    {"g_y",item->pos().y()},
                    {"g_h",item->geometry().height()},
                    {"g_w",item->geometry().width()},
                    {"index_of_last_attrib", item->index_of_last_attrib},
                    {"lines", arr2}
                    }));
    }
    for(auto* item:classScene->connections){
        arr3.append((QJsonObject({
                    {"start_name",item->start->class_title->text()},
                    {"end_name",item->end->class_title->text()},
                    {"line_type", item->type}
                                  })));
    }

    QJsonObject main_obj;
    main_obj.insert("windows", arr);
    main_obj.insert("connectionsns",arr3);
    doc.setObject(main_obj);
    return doc.toJson(QJsonDocument::Indented);
}

void MainWindow::on_actionAdd_triggered()
{
    //TODO add sequence diagram
    seqScene *diagram = new seqScene(ui->graphicsView);
    diagram->setSceneRect(0,0,1920,1080);
    seqList.push_back(diagram);
}

void MainWindow::on_actionRemove_triggered()
{
    //TODO remove sequence diagram
    if(seqList.size() != 0){
        if (ui->graphicsView->scene() == seqList[seqIndex])
            on_actionClass_triggered();
        seqScene *tmp = seqList[seqIndex];
        seqList.erase(seqList.begin());
        delete tmp;
    }
}

void MainWindow::on_actionSeq1_triggered()
{
    //TODO switch to seq1
    if(seqList.size() != 0)
        ui->graphicsView->setScene(seqList[seqIndex]);

    disconnect(spawnClass, &QAction::triggered, classScene, &Scene::SpawnEntity);
    disconnect(spawnConnect, &QAction::triggered, classScene, &Scene::SpawnConnectionLine);
    disconnect(changeLine, &QAction::triggered, classScene, &Scene::ChangeConnectionLine);
    disconnect(removeClass, &QAction::triggered, classScene, &Scene::RemoveEntity);
    disconnect(removeConnect, &QAction::triggered, classScene, &Scene::RemoveConnectionLine);

    connect(spawnClass, &QAction::triggered, seqList[seqIndex], &seqScene::SpawnEntity);
    connect(spawnConnect, &QAction::triggered, seqList[seqIndex], &seqScene::SpawnConnectionLine);
    connect(changeLine, &QAction::triggered, seqList[seqIndex], &seqScene::ChangeConnectionLine);
    connect(removeClass, &QAction::triggered, seqList[seqIndex], &seqScene::RemoveEntity);
    connect(removeConnect, &QAction::triggered, seqList[seqIndex], &seqScene::RemoveConnectionLine);
}

void MainWindow::on_actionClass_triggered()
{
    //TODO switch to class
    ui->graphicsView->setScene(classScene);

    disconnect(spawnClass, &QAction::triggered, seqList[seqIndex], &seqScene::SpawnEntity);
    disconnect(spawnConnect, &QAction::triggered, seqList[seqIndex], &seqScene::SpawnConnectionLine);
    disconnect(changeLine, &QAction::triggered, seqList[seqIndex], &seqScene::ChangeConnectionLine);
    disconnect(removeClass, &QAction::triggered, seqList[seqIndex], &seqScene::RemoveEntity);
    disconnect(removeConnect, &QAction::triggered, seqList[seqIndex], &seqScene::RemoveConnectionLine);

    connect(spawnClass, &QAction::triggered, classScene, &Scene::SpawnEntity);
    connect(spawnConnect, &QAction::triggered, classScene, &Scene::SpawnConnectionLine);
    connect(changeLine, &QAction::triggered, classScene, &Scene::ChangeConnectionLine);
    connect(removeClass, &QAction::triggered, classScene, &Scene::RemoveEntity);
    connect(removeConnect, &QAction::triggered, classScene, &Scene::RemoveConnectionLine);
}
