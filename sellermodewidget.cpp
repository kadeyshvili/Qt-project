#include "sellermodewidget.h"


SellerModeWidget::SellerModeWidget(QWidget *parent, QStandardItemModel *model) : QWidget(parent)
{

    mainBox = new QVBoxLayout();
    sourceModel = model;
    editVehicleWidget = new EditVehicle();

    connect(editVehicleWidget, SIGNAL(addedNewVehicle(QStringList)), this, SLOT(addVehicle(QStringList)));

    QPushButton *editModeButton = new QPushButton("edit vehicle");
    QPushButton *addModeButton = new QPushButton("add vehicle");

    connect(editModeButton, SIGNAL(clicked()), this, SLOT(editModeSelect()));
    connect(addModeButton, SIGNAL(clicked()), this, SLOT(addModeSelect()));

    mainBox->addWidget(editModeButton);
    mainBox->addWidget(addModeButton);

    setLayout(mainBox);
}

void SellerModeWidget::addModeSelect()
{
    editVehicleWidget->clearFields();
    editVehicleWidget->raise();
    editVehicleWidget->show();
}

void SellerModeWidget::editModeSelect()
{

    QMessageBox box;
    box.setText("You can edit existing vehicle in the buyer mode");
    box.setWindowTitle("Information about futher action");
    box.exec();
}


void SellerModeWidget::addVehicle(QStringList params)
{
    QList<QStandardItem *> standardItemsList;
    for (QString item : params)
    {
        QStandardItem *standartItem = new QStandardItem(item);
        bool ok;
        int number = item.toInt(&ok, 10);
        if (ok)
        {
            standartItem->setData(QVariant::fromValue(number), Qt::DisplayRole);
        }
        standardItemsList.append(standartItem);
    }


    sourceModel->appendRow(standardItemsList);

}

void SellerModeWidget::updateRowParams(QStringList params, int rowIndex)
{
    emit updatedRowParams(params, rowIndex);
}
