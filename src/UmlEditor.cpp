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

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_graphicsView_customContextMenuRequested(const QPoint &pos)
{
    if(ui->graphicsView->itemAt(pos))
        return;
    QMenu menu(this);
    spawnClass = menu.addAction("Create Class Entity");
    connect(spawnClass, &QAction::triggered, scene, &Scene::SpawnClassEntity);
    menu.addAction("Create Connection");
    menu.exec(ui->graphicsView->mapToGlobal(pos));
}
