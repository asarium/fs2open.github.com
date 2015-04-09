#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <stdexcept>

#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

#include "editor.h"

namespace fso {
namespace fred {

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setEditor(std::shared_ptr<Editor> editor)
{
    fred = editor;
    ui->centralwidget->setEditor(editor);
}

void MainWindow::loadMission()
{
    qDebug() << "Loading from directory:" << QDir::currentPath();
    QString pathName = QFileDialog::getOpenFileName(this,
                                                    tr("Load mission"),
                                                    QString(),
                                                    tr("FS2 missions (*.fs2)"));

    if (pathName.isEmpty())
        return;

    statusBar()->showMessage(tr("Loading mission %1").arg(pathName));
    try {
        fred->loadMission(pathName.toStdString());
        ui->centralwidget->updateGL();
        statusBar()->showMessage(tr("Units = %1 meters").arg(fred->renderer()->The_grid->square_size));
    }
    catch (const fso::fred::mission_load_error &) {
        QMessageBox::critical(this, tr("Failed loading mission."), tr("Could not parse the mission."));
        statusBar()->clearMessage();
    }
}

} // namespace fred
} // namespace fso
