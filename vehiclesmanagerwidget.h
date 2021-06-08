#ifndef VEHICLESMANAGERWIDGET_H
#define VEHICLESMANAGERWIDGET_H

#include <QStackedWidget>
#include <QObject>
#include <QWidget>
#include <QStandardItemModel>
#include <QStandardItem>

#include "buyermodewidget.h"
#include "sellermodewidget.h"
#include "modeselectingwidget.h"


class VehiclesManagerWidget : public QStackedWidget
{
    Q_OBJECT
public:
    VehiclesManagerWidget(QWidget *parent = nullptr);

    QStandardItemModel *allVehicles;

    BuyerModeWidget *buyerModeWidget;
    SellerModeWidget *sellerModeWidget;
    ModeSelectingWidget *modeSelectingWidget;

public slots:
    void changeMode(int modeIndex);

};

#endif // VEHICLESMANAGERWIDGET_H
