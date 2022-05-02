#include "clickmenu.h"
#include "ui_clickmenu.h"

ClickMenu::ClickMenu(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ClickMenu)
{
    ui->setupUi(this);
}

ClickMenu::~ClickMenu()
{
    delete ui;
}
