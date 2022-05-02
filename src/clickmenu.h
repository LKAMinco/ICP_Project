#ifndef CLICKMENU_H
#define CLICKMENU_H

#include <QFrame>

namespace Ui {
class ClickMenu;
}

class ClickMenu : public QFrame
{
    Q_OBJECT

public:
    explicit ClickMenu(QWidget *parent = nullptr);
    ~ClickMenu();

private:
    Ui::ClickMenu *ui;
};

#endif // CLICKMENU_H
