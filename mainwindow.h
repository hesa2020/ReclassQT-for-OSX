#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "reclass.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    ReClass* reclass = nullptr;
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void AddClassMenu(QString className);

private slots:
    void on_ClassesTree_doubleClicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
