#include "UmlEditor.h"
#include "ui_UmlEditor.h"
#include "classentity.h"
#include "scene.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*auto *scene = new Scene(ui->graphicsView);
    ui->graphicsView->setScene(scene);*/

}

MainWindow::~MainWindow()
{
    delete ui;
}
