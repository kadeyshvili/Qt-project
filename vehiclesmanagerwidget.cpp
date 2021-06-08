#include "vehiclesmanagerwidget.h"

VehiclesManagerWidget::VehiclesManagerWidget(QWidget *parent) : QStackedWidget(parent)
{
    allVehicles = new QStandardItemModel();

    buyerModeWidget = new BuyerModeWidget(nullptr, allVehicles);
    sellerModeWidget = new SellerModeWidget(nullptr, allVehicles);
    modeSelectingWidget = new ModeSelectingWidget();

    addWidget(modeSelectingWidget);
    addWidget(sellerModeWidget);
    addWidget(buyerModeWidget);

    connect(modeSelectingWidget, SIGNAL(changedMode(int)), this, SLOT(changeMode(int)));

}

void VehiclesManagerWidget::changeMode(int modeIndex)
{
    if (modeIndex == 0)
    {
        setCurrentWidget(modeSelectingWidget);
    }
    else if (modeIndex == 1)
    {
        setCurrentWidget(buyerModeWidget);
    }
    else if (modeIndex == 2)
    {
        setCurrentWidget(sellerModeWidget);
    }
}
