#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <QStatusBar>
#include <QDebug>
#include <QFileDialog>

#include "vehiclesmanagerwidget.h"
#include "aboutwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    AboutWidget *aboutWidget = new AboutWidget();
    VehiclesManagerWidget *manager;
    QStandardItemModel *allVehicles;

public slots:
    void modeSelectingOn();
    void loadFile();
    void changeModeStatus(int modeIndex);
    void aboutSlot();
    void save();

private:
    Ui::MainWindow *ui;
    QString _fileName;
};
#endif // MAINWINDOW_H
