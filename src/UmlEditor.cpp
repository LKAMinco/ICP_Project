/**
 * ICP Project 2022 
 * @file UmlEditor.cpp
 * @brief implementation of methods in main window class
 * @author Jakub Julius Smykal (xsmyka01)
 * @author Milan Hrabovsky (xhrabo15)
 */

#include "UmlEditor.h"
#include "ui_UmlEditor.h"
#include "classentity.h"
#include "seqentity.h"

//Constructor
MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connect(ui->actionOpen, &QAction::toggled, this, &MainWindow::on_actionOpen_triggered);
    /*auto *scene = new Scene(ui->graphicsView);
    ui->graphicsView->setScene(scene);*/

    //creates new graphics scene and sets its size
    classScene = new Scene(ui->graphicsView);
    ui->graphicsView->setScene(classScene);
    ui->graphicsView->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->graphicsView->setFixedSize(1920, 1080);
    classScene->setSceneRect(0, 0, 1920, 1080);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    //creates context menu for class diagram
    menu = new QMenu(this);
    spawnClass = menu->addAction("Create Entity");
    connect(spawnClass, &QAction::triggered, classScene, &Scene::SpawnEntity);
    spawnConnect = menu->addAction("Create Connection");
    connect(spawnConnect, &QAction::triggered, classScene, &Scene::SpawnConnectionLine);
    changeLine = menu->addAction("Change Connection");
    connect(changeLine, &QAction::triggered, classScene, &Scene::ChangeConnectionLine);
    removeClass = menu->addAction("Remove Entity");
    connect(removeClass, &QAction::triggered, classScene, &Scene::RemoveEntity);
    removeConnect = menu->addAction("Remove Connection");
    connect(removeConnect, &QAction::triggered, classScene, &Scene::RemoveConnectionLine);

    seqList.clear();
    seqIndex = 0;
    activeSeq = false;

    info = new ClassStorage(this);
    classScene->info = info;
}

//Destructor
MainWindow::~MainWindow() {
    delete ui;
}

//Function spawns context menu on mouse's location
void MainWindow::on_graphicsView_customContextMenuRequested(const QPoint &pos) {
    if (ui->graphicsView->itemAt(pos)) {
        return;
    }
    menu->exec(ui->graphicsView->mapToGlobal(pos));
}

//Funcions saves data, if path to savefile exists, otherwise calls 'save as'
void MainWindow::on_actionSave_triggered() {
    if (!QString::compare(file_path, "", Qt::CaseSensitive)) {
        on_actionSave_as_triggered();
    } else {
        QFile file(file_path);
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&file);
        out << genJson();
    }
}

//Function saves data to file
void MainWindow::on_actionSave_as_triggered() {
    std::regex e("(\\..+)");
    std::string result;
    file_path = QFileDialog::getSaveFileName(this, tr("Save File"), "Untitled", tr("Uml editor files (*.json)"));
    std::string string = file_path.toStdString();
    std::regex_replace(std::back_inserter(result), string.begin(), string.end(), e, "$2");
    result.append(".json");
    file_path = QString::fromStdString(result);
    QFile file(file_path);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << genJson();
}

void MainWindow::on_actionOpen_triggered() {
    on_actionNew_triggered();
    file_path = QFileDialog::getOpenFileName(this, "Open a file", "directoryToOpen", "Uml editor files (*.json)");
    QFile file(file_path);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray data = file.readAll();
    file.close();
    QJsonParseError errorPtr;
    QJsonDocument doc = QJsonDocument::fromJson(data, &errorPtr);
    if (doc.isNull()) {
        qDebug() << "Parse failed";
        return;
    }
    QJsonObject main_obj = doc.object();
    QJsonArray windows = main_obj.value("windows").toArray();
    foreach(
    const QJsonValue &val, windows){
        classScene->SpawnEntity(false);
        auto *entity = classScene->entities.back();
        int x = val.toObject().value("g_x").toInt();
        int y = val.toObject().value("g_y").toInt();
        entity->class_title->setText(val.toObject().value("class_name").toString());
        info->UpdateEntity(entity->objectName(), entity->class_title->text(), "title");
        entity->move(x, y);
        QJsonArray lines = val.toObject().value("lines").toArray();
        int i = -1;
        foreach(
        const QJsonValue &val2, lines){
            i++;
            if (i <= val.toObject().value("index_of_last_attrib").toInt()) {
                entity->on_add_attrib_clicked();
                entity->entity_lines.back()->box_visiblity->setCurrentIndex(
                        val2.toObject().value("visBox_value").toInt());
                entity->entity_lines.back()->line_edit->setText(val2.toObject().value("lineEdit_value").toString());
                entity->entity_lines.back()->box_type->setCurrentIndex(val2.toObject().value("boxType_value").toInt());
            } else {
                entity->on_add_method_clicked();
                entity->entity_lines.back()->box_visiblity->setCurrentIndex(
                        val2.toObject().value("visBox_value").toInt());
                entity->entity_lines.back()->line_edit->setText(
                        val2.toObject().value("lineEdit_value").toString()); //TODO
                info->UpdateEntity(entity->objectName(), entity->entity_lines.back()->line_edit->text(),
                                   entity->entity_lines.back()->line_edit->objectName());
            }
        }
    }
    QJsonArray connections = main_obj.value("connections").toArray();
    foreach(
    const QJsonValue &val, connections){
        for (auto *item: classScene->entities) {
            auto item_name = item->class_title->text();
            auto find_name = val.toObject().value("start_name").toString();
            if (!QString::compare(item_name, find_name, Qt::CaseSensitive)) {
                classScene->updateFocusList(item);
                break;
            } //else
            //qDebug() << "aaaaa hladam";
        }
        for (auto *item: classScene->entities) {
            auto item_name = item->class_title->text();
            auto find_name = val.toObject().value("end_name").toString();
            if (!QString::compare(item_name, find_name, Qt::CaseSensitive)) {
                classScene->updateFocusList(item);
                break;
            } //else
            //qDebug() << "aaaaa hladam";
        }
        classScene->SpawnConnectionLine(false);
        if (val.toObject().value("line_type").toInt() == 0)
            classScene->connections.back()->type = 3;
        else
            classScene->connections.back()->type = val.toObject().value("line_type").toInt() - 1;
        classScene->lastLine = classScene->connections.back();
        classScene->ChangeConnectionLine(false);
        for (auto *item2: classScene->focusList) {
            item2->setStyleSheet("QFrame { border: 4px solid black }");
        }
        classScene->focusList.clear();
        classScene->lastLine = nullptr;
    }
    QJsonArray seq_scenes = main_obj.value("seq_scenes").toArray();
    foreach(
    const QJsonValue &val, seq_scenes){
        QJsonArray entities = val.toObject().value("entities").toArray();
        on_actionAdd_triggered();
        foreach(
        const QJsonValue &val2, entities){
            seqList.back()->SpawnEntity(false);
            seqList.back()->entities.back()->setObjectName(val2.toObject().value("window_name").toString());
            int x = val2.toObject().value("g_x").toInt();
            int y = val2.toObject().value("g_y").toInt();
            seqList.back()->entities.back()->move(x, y);
            auto text = val2.toObject().value("box_value").toString();
            int index = seqList.back()->entities.back()->box->findText(text);
            seqList.back()->entities.back()->box->setCurrentIndex(index);
            int height = val2.toObject().value("height").toInt();
            int width = seqList.back()->entities.back()->width();
            seqList.back()->entities.back()->resize(width, seqList.back()->entities.back()->height() + height - 120);
            seqList.back()->entities.back()->line->setFixedHeight(height);
            qDebug() << seqList.back()->entities.back()->objectName();
        }
        QJsonArray connections = val.toObject().value("connections").toArray();
        foreach(
        const QJsonValue &val2, connections){
            for (auto *item: seqList.back()->entities) {
                auto item_name = item->objectName();
                auto find_name = val2.toObject().value("start_name").toString();
                if (!QString::compare(item_name, find_name, Qt::CaseSensitive)) {
                    seqList.back()->updateFocusList(item);
                    break;
                } else
                    qDebug() << "bbbbb hladam";
            }
            for (auto *item: seqList.back()->entities) {
                auto item_name = item->objectName();
                auto find_name = val2.toObject().value("end_name").toString();
                if (!QString::compare(item_name, find_name, Qt::CaseSensitive)) {
                    seqList.back()->updateFocusList(item);
                    break;
                } else
                    qDebug() << "bbbbb hladam";
            }
            seqList.back()->SpawnConnectionLine(false);
            auto text = val2.toObject().value("box_value").toString();
            int index = seqList.back()->connections.back()->box->findText(text);
            seqList.back()->connections.back()->box->setCurrentIndex(index);
            if (val2.toObject().value("type").toInt() == 0)
                seqList.back()->connections.back()->type = 3;
            else
                seqList.back()->connections.back()->type = val2.toObject().value("type").toInt() - 1;
            seqList.back()->lastLine = seqList.back()->connections.back();
            qDebug() << seqList.back()->connections.back()->type;
            seqList.back()->ChangeConnectionLine(false);
            seqList.back()->connections.back()->mouseOffset = val2.toObject().value("mouse_offset").toInt();
            seqList.back()->connections.back()->setPosition();
            seqList.back()->connections.back()->changeColor(Qt::black);
        }
    }
}

QString MainWindow::genJson() {
    QJsonDocument doc;
    QJsonArray arr, arr3, arr5;
    QJsonObject windows;
    QJsonObject connections;
    for (auto *item: classScene->entities) {
        QJsonArray arr2;
        int i = -1;
        for (auto *item2: item->entity_lines) {
            i++;
            if (i <= item->index_of_last_attrib) {
                arr2.append((QJsonObject({
                                                 {"visBox_value",   item2->box_visiblity->currentIndex()},
                                                 {"lineEdit_value", item2->line_edit->text()},
                                                 {"boxType_value",  item2->box_type->currentIndex()}
                                         })));
            } else {
                arr2.append((QJsonObject({
                                                 {"visBox_value",   item2->box_visiblity->currentIndex()},
                                                 {"lineEdit_value", item2->line_edit->text()},
                                         })));
            }
        }
        arr.append(QJsonObject({
                                       {"class_name",           item->class_title->text()},
                                       {"g_x",                  item->pos().x()},
                                       {"g_y",                  item->pos().y()},
                                       //{"g_h",item->geometry().height()},
                                       //{"g_w",item->geometry().width()},
                                       {"index_of_last_attrib", item->index_of_last_attrib},
                                       {"lines",                arr2}
                               }));
    }
    for (auto *item: classScene->connections) {
        arr3.append((QJsonObject({
                                         {"start_name", item->start->class_title->text()},
                                         {"end_name",   item->end->class_title->text()},
                                         {"line_type",  item->type}
                                 })));
    }
    for (auto *scene: seqList) {
        QJsonArray arr2, arr4;
        for (auto *item: scene->entities) {
            arr2.append((QJsonObject({
                                             {"window_name", item->objectName()},
                                             {"g_x",         item->pos().x()},
                                             {"g_y",         item->pos().y()},
                                             {"box_value",   item->box->currentText()},
                                             {"height",      item->line->height()}
                                     })));
        }
        for (auto *item: scene->connections) {
            arr4.append((QJsonObject({
                                             {"start_name",   item->start->objectName()},
                                             {"end_name",     item->end->objectName()},
                                             {"box_value",    item->box->currentText()},
                                             {"type",         item->type},
                                             {"mouse_offset", item->mouseOffset}
                                     })));
        }
        arr5.append((QJsonObject({
                                         {"entities",    arr2},
                                         {"connections", arr4}
                                 })));
    }
    QJsonObject main_obj;
    main_obj.insert("windows", arr);
    main_obj.insert("connections", arr3);
    main_obj.insert("seq_scenes", arr5);
    doc.setObject(main_obj);
    return doc.toJson(QJsonDocument::Indented);
}

//Function creates new sequence scene
void MainWindow::on_actionAdd_triggered() {
    seqScene *diagram = new seqScene(ui->graphicsView);
    diagram->setSceneRect(0, 0, 1920, 1080); //sets size
    seqList.push_back(diagram);
    diagram->info = info;
}

//Function removes active sequence scene
void MainWindow::on_actionRemove_triggered() {
    //TODO remove sequence diagram
    if (seqList.size() != 0) {
        seqScene *tmp = seqList[seqIndex];
        seqList.erase(seqList.begin() + seqIndex);
        delete tmp;
        //switches to different sequence scene
        //switches to class scene if there are not any sequence scenes
        if (seqList.size() == 0) {
            on_actionClass_triggered();
        } else {
            seqIndex = 0;
            on_actionSeq1_triggered();
        }
    }
}

//Function switches window to sequence scene
void MainWindow::on_actionSeq1_triggered() {
    //checks if any sequence scene exist
    if (seqList.size() == 0)
        return;
    ui->graphicsView->setScene(seqList[seqIndex]);

    //disconnects context menu from class scene
    disconnect(spawnClass, &QAction::triggered, classScene, &Scene::SpawnEntity);
    disconnect(spawnConnect, &QAction::triggered, classScene, &Scene::SpawnConnectionLine);
    disconnect(changeLine, &QAction::triggered, classScene, &Scene::ChangeConnectionLine);
    disconnect(removeClass, &QAction::triggered, classScene, &Scene::RemoveEntity);
    disconnect(removeConnect, &QAction::triggered, classScene, &Scene::RemoveConnectionLine);

    //connects context menu to sequence scene
    connect(spawnClass, &QAction::triggered, seqList[seqIndex], &seqScene::SpawnEntity);
    connect(spawnConnect, &QAction::triggered, seqList[seqIndex], &seqScene::SpawnConnectionLine);
    connect(changeLine, &QAction::triggered, seqList[seqIndex], &seqScene::ChangeConnectionLine);
    connect(removeClass, &QAction::triggered, seqList[seqIndex], &seqScene::RemoveEntity);
    connect(removeConnect, &QAction::triggered, seqList[seqIndex], &seqScene::RemoveConnectionLine);

    activeSeq = true;
}

//Function switches window to class scene
void MainWindow::on_actionClass_triggered() {
    ui->graphicsView->setScene(classScene);

    //disconnects context menu from sequence scene
    disconnect(spawnClass, &QAction::triggered, seqList[seqIndex], &seqScene::SpawnEntity);
    disconnect(spawnConnect, &QAction::triggered, seqList[seqIndex], &seqScene::SpawnConnectionLine);
    disconnect(changeLine, &QAction::triggered, seqList[seqIndex], &seqScene::ChangeConnectionLine);
    disconnect(removeClass, &QAction::triggered, seqList[seqIndex], &seqScene::RemoveEntity);
    disconnect(removeConnect, &QAction::triggered, seqList[seqIndex], &seqScene::RemoveConnectionLine);

    //connects context menu to class scene
    connect(spawnClass, &QAction::triggered, classScene, &Scene::SpawnEntity);
    connect(spawnConnect, &QAction::triggered, classScene, &Scene::SpawnConnectionLine);
    connect(changeLine, &QAction::triggered, classScene, &Scene::ChangeConnectionLine);
    connect(removeClass, &QAction::triggered, classScene, &Scene::RemoveEntity);
    connect(removeConnect, &QAction::triggered, classScene, &Scene::RemoveConnectionLine);

    activeSeq = false;
}

//Function resets all scenes
void MainWindow::on_actionNew_triggered() {
    //deletes all existing data
    delete classScene;
    delete info;
    //creates new scene
    classScene = new Scene(ui->graphicsView);
    ui->graphicsView->setScene(classScene);
    ui->graphicsView->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->graphicsView->setFixedSize(1920, 1080);
    classScene->setSceneRect(0, 0, 1920, 1080);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    while (seqList.size() > 0)
        on_actionRemove_triggered();

    //connects new class scene to context menu
    connect(spawnClass, &QAction::triggered, classScene, &Scene::SpawnEntity);
    connect(spawnConnect, &QAction::triggered, classScene, &Scene::SpawnConnectionLine);
    connect(changeLine, &QAction::triggered, classScene, &Scene::ChangeConnectionLine);
    connect(removeClass, &QAction::triggered, classScene, &Scene::RemoveEntity);
    connect(removeConnect, &QAction::triggered, classScene, &Scene::RemoveConnectionLine);
    file_path = "";

    info = new ClassStorage(this);
    classScene->info = info;
    ui->graphicsView->setScene(classScene);
}

//Function changes active sequence scene to previous
void MainWindow::on_actionSwitch_Seq_Left_triggered() {
    //does nothing if there is only one existing scene or class scene is active
    if ((seqList.size() <= 1) || (!activeSeq))
        return;
    //disconnects context menu from current sequence scene
    disconnect(spawnClass, &QAction::triggered, seqList[seqIndex], &seqScene::SpawnEntity);
    disconnect(spawnConnect, &QAction::triggered, seqList[seqIndex], &seqScene::SpawnConnectionLine);
    disconnect(changeLine, &QAction::triggered, seqList[seqIndex], &seqScene::ChangeConnectionLine);
    disconnect(removeClass, &QAction::triggered, seqList[seqIndex], &seqScene::RemoveEntity);
    disconnect(removeConnect, &QAction::triggered, seqList[seqIndex], &seqScene::RemoveConnectionLine);

    //changes current sequence scene index
    seqIndex--;
    if (seqIndex < 0)
        seqIndex = seqList.size() - 1;

    on_actionSeq1_triggered();
}

//Function changes active sequence scene to next
void MainWindow::on_actionSwitch_Seq_Right_triggered() {
    //does nothing if there is only one existing scene or class scene is active
    if ((seqList.size() <= 1) || (!activeSeq))
        return;
    //disconnects context menu from current sequence scene
    disconnect(spawnClass, &QAction::triggered, seqList[seqIndex], &seqScene::SpawnEntity);
    disconnect(spawnConnect, &QAction::triggered, seqList[seqIndex], &seqScene::SpawnConnectionLine);
    disconnect(changeLine, &QAction::triggered, seqList[seqIndex], &seqScene::ChangeConnectionLine);
    disconnect(removeClass, &QAction::triggered, seqList[seqIndex], &seqScene::RemoveEntity);
    disconnect(removeConnect, &QAction::triggered, seqList[seqIndex], &seqScene::RemoveConnectionLine);

    //changes current sequence scene index
    seqIndex++;
    seqIndex = seqIndex % seqList.size();

    on_actionSeq1_triggered();
}
