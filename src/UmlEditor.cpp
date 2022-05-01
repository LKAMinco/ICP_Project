#include "UmlEditor.h"
#include "ui_UmlEditor.h"
#include "classentity.h"
#include "scene.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionOpen,&QAction::toggled,this,&MainWindow::on_actionOpen_triggered);
    /*auto *scene = new Scene(ui->graphicsView);
    ui->graphicsView->setScene(scene);*/

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    file_path = QFileDialog::getOpenFileName(this, "Open a file", "directoryToOpen","Uml editor files (*.json)");
    QFileInfo info(file_path);
    file_name = info.fileName();
}

void MainWindow::on_actionSave_as_triggered()
{
    QString file_path = QFileDialog::getSaveFileName(this, tr("Save File"),
                                   "Untitled",
                                   tr("Uml editor files (*.json)"));
    QFileInfo info(file_path);
    file_name = info.fileName();
}

void MainWindow::on_actionSave_triggered()
{
    //TODO pridat save pokial ma nacitanu uz cestu
}
