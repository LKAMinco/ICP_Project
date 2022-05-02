#include "UmlEditor.h"
#include "ui_UmlEditor.h"
#include "classentity.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new Scene(ui->graphicsView);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->graphicsView->setFixedSize(1920,1080);
    scene->setSceneRect(0,0,1920,1080);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    menu = new QMenu(this);
    spawnClass = menu->addAction("Create Class Entity");
    connect(spawnClass, &QAction::triggered, scene, &Scene::SpawnClassEntity);
    spawnConnect = menu->addAction("Create Connection");
    connect(spawnConnect, &QAction::triggered, scene, &Scene::SpawnConnectionLine);
    removeClass = menu->addAction("Remove Class Entity");
    connect(removeClass, &QAction::triggered, scene, &Scene::RemoveClassEntity);
    removeConnect = menu->addAction("Remove Connection");
    connect(removeConnect, &QAction::triggered, scene, &Scene::RemoveConnectionLine);

}

MainWindow::~MainWindow()
{
    delete ui;
}

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
    QString file_path = QFileDialog::getSaveFileName(this, tr("Save File"),"Untitled",tr("Uml editor files (*.json)"));
        QFileInfo info(file_path);
        file_name = info.fileName();
}

void MainWindow::on_actionOpen_triggered()
{
    file_path = QFileDialog::getOpenFileName(this, "Open a file", "directoryToOpen","Uml editor files (*.json)");
    QFileInfo info(file_path);
    file_name = info.fileName();
}
