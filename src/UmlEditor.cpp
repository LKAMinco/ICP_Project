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

