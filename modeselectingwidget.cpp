#include "modeselectingwidget.h"

ModeSelectingWidget::ModeSelectingWidget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainBox = new QVBoxLayout();

    QPushButton *sellerModeButton = new QPushButton("seller mode");
    QPushButton *buyerModeButton = new QPushButton("buyer mode");

    connect(sellerModeButton, SIGNAL(clicked()), this, SLOT(sellerModeSelect()));
    connect(buyerModeButton, SIGNAL(clicked()), this, SLOT(buyerModeSelect()));

    mainBox->addWidget(sellerModeButton);
    mainBox->addWidget(buyerModeButton);

    setLayout(mainBox);

    setWindowTitle("Select mode");
}

void ModeSelectingWidget::buyerModeSelect()
{
    emit changedMode(1);
}

void ModeSelectingWidget::sellerModeSelect()
{
    emit changedMode(2);
}
