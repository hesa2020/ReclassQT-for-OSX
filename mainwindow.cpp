#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTreeWidgetItem>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    reclass = new ReClass(this);

    ui->NodesTree->setModel(reclass->model);
    ui->NodesTree->resizeColumnToContents(0);
    ui->NodesTree->header()->setStretchLastSection(false);
    ui->NodesTree->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    //SpinBoxDelegate* delegate = new SpinBoxDelegate();
    //ui->NodesTree->setItemDelegate(delegate);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::AddClassMenu(QString className)
{
    QTreeWidgetItem *topLevelItem = new QTreeWidgetItem(this->ui->ClassesTree);
    topLevelItem->setText(0, className);
    this->ui->ClassesTree->addTopLevelItem(topLevelItem);
}

void MainWindow::on_ClassesTree_doubleClicked(const QModelIndex &index)
{
    reclass->on_ClassesTree_doubleClicked(index);
    this->ui->NodesTree->reset();
}

void MainWindow::on_NodesTree_doubleClicked(const QModelIndex &index)
{

    this->ui->NodesTree->edit(index);
}
