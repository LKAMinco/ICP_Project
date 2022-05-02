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
    scene = new Scene(ui->graphicsView);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->graphicsView->setFixedSize(1920,1080);
    scene->setSceneRect(0,0,1920,1080);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    //creates context menu for class diagram
    menu = new QMenu(this);
    spawnClass = menu->addAction("Create Class Entity");
    connect(spawnClass, &QAction::triggered, scene, &Scene::SpawnClassEntity);
    spawnConnect = menu->addAction("Create Connection");
    connect(spawnConnect, &QAction::triggered, scene, &Scene::SpawnConnectionLine);
    changeLine = menu->addAction("Change Connection");
    connect(changeLine, &QAction::triggered, scene, &Scene::ChangeConnectionLine);
    removeClass = menu->addAction("Remove Class Entity");
    connect(removeClass, &QAction::triggered, scene, &Scene::RemoveClassEntity);
    removeConnect = menu->addAction("Remove Connection");
    connect(removeConnect, &QAction::triggered, scene, &Scene::RemoveConnectionLine);

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

}

void MainWindow::on_actionSave_as_triggered()
{
    std::regex e ("(\\..+)");
    std::string result;
    QString file_path = QFileDialog::getSaveFileName(this, tr("Save File"),"Untitled",tr("Uml editor files (*.json)"));
    std::string string = file_path.toStdString();
    std::regex_replace (std::back_inserter(result), string.begin(), string.end(), e, "$2");
    result.append(".json");
    file_path = QString::fromStdString(result);
    QFileInfo info(file_path);
    file_name = info.fileName();
    qDebug() << file_path << "aaaaaaaaaa" << file_name;
    QFile file(file_path);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << genJson();
}

void MainWindow::on_actionOpen_triggered()
{
    file_path = QFileDialog::getOpenFileName(this, "Open a file", "directoryToOpen","Uml editor files (*.json)");
    QFileInfo info(file_path);
    file_name = info.fileName();
}

QString MainWindow::genJson(){
    QJsonDocument doc;
    QJsonArray arr;

    for(auto* item : scene->entities){
        //qobject_cast<ClassEntity*>(item)->entity_lines;
        arr.append(QJsonObject({
                    {"pos_x", item->pos().x()},
                    {"pos_y",item->pos().y()},
                    {"height",item->geometry().height()},
                    {"width",item->geometry().width()}
                    }));
        QJsonObject obj{{"items",arr}};
        doc.setObject(obj);
    }
    return doc.toJson(QJsonDocument::Indented);
}

void MainWindow::on_actionAdd_triggered()
{
    //TODO add sequence diagram
}

void MainWindow::on_actionRemove_triggered()
{
    //TODO remove sequence diagram
}
