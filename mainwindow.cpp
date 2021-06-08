#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    manager = new VehiclesManagerWidget(this);

    QToolBar *toolBar = addToolBar("Select mode");
    QAction *selectModeAction = toolBar->addAction("Select mode");
    QAction *loadFileAction = toolBar->addAction("Load file");
    QAction *aboutAction = toolBar->addAction("About");
    QAction *quitAction = toolBar->addAction("Quit");
    QAction *saveAction = toolBar->addAction("Save");

    connect(selectModeAction, SIGNAL(triggered()), this, SLOT(modeSelectingOn()));
    connect(loadFileAction, SIGNAL(triggered()), this, SLOT(loadFile()));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(aboutSlot()));
    connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));
    connect(manager->modeSelectingWidget, SIGNAL(changedMode(int)), this, SLOT(changeModeStatus(int)));

    setCentralWidget(manager);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::modeSelectingOn()
{
    manager->changeMode(0);
    ui->statusbar->showMessage("Select mode");
}

void MainWindow::changeModeStatus(int modeIndex)
{
    if (modeIndex == 0)
        ui->statusbar->showMessage("Select mode");
    else if (modeIndex == 1)
        ui->statusbar->showMessage("Buyer mode");
    else if (modeIndex == 2)
        ui->statusbar->showMessage("Seller mode");
}

void MainWindow::aboutSlot()
{
    aboutWidget->show();
}

void MainWindow::loadFile()
{
    _fileName = QFileDialog::getOpenFileName(this, "Load file");
    manager->buyerModeWidget->readData(_fileName);
}

void MainWindow::save()
{
    QString fileName = QFileDialog::getSaveFileName(this,"Save","*.csv");
    QFile outFile(fileName);
    if (!outFile.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::information(this, tr("Unable to open file"),
                    outFile.errorString());
        return;
    }
    outFile.open(QIODevice::WriteOnly);

    QTextStream out(&outFile);

    for (int i = 0; i < allVehicles->rowCount(); ++i)
    {
        for (int j = 0; j < allVehicles->columnCount(); ++j)
        {
            QModelIndex idx = allVehicles->index(i, j);
            out << allVehicles->data(idx).toString();
            if (j != allVehicles->columnCount() - 1)
            {
                out << ",";
            }
        }
        out << "\n";
    }
    outFile.close();
}




