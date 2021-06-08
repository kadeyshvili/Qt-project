#ifndef SELLERMODEWIDGET_H
#define SELLERMODEWIDGET_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QFile>
#include <QMessageBox>
#include "editvehicle.h"

class SellerModeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SellerModeWidget(QWidget *parent = nullptr, QStandardItemModel *model = nullptr);

    QVBoxLayout *mainBox;
    QStandardItemModel *sourceModel;

    EditVehicle *editVehicleWidget;
    void readData(QString fileName);
    QStandardItemModel *allVehicles;

public slots:
    void editModeSelect();
    void addModeSelect();

    void addVehicle(QStringList params);
    void updateRowParams(QStringList params, int rowIndex);

signals:
    void changedMode(int modeIndex);
    void updatedRowParams(QStringList params, int rowIndex);
};

#endif // SELLERMODEWIDGET_H
