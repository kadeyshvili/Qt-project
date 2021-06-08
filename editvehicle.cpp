#include "editvehicle.h"

EditVehicle::EditVehicle(QWidget *parent) : QWidget(parent)
{
    mainBox = new QVBoxLayout();
    QGridLayout *paramsBox = new QGridLayout();

    QLabel *regionLabel = new QLabel("region");
    QLabel *priceLabel = new QLabel("price");
    QLabel *yearLabel = new QLabel("year");
    QLabel *manufacturerLabel = new QLabel("manufacturer");
    QLabel *modelLabel = new QLabel("model");
    QLabel *cylindersLabel = new QLabel("number of cylinders");
    QLabel *fuelLabel = new QLabel("type of fuel");
    QLabel *mileageLabel = new QLabel("odometer");

    regionEdit = new QLineEdit();
    priceEdit = new QLineEdit();
    yearEdit = new QLineEdit();
    manufacturerEdit = new QLineEdit();
    modelEdit = new QLineEdit();
    cylindersEdit = new QLineEdit();
    fuelEdit = new QLineEdit();
    mileageEdit = new QLineEdit();

    paramsBox->addWidget(regionLabel, 0, 0);
    paramsBox->addWidget(priceLabel, 1, 0);
    paramsBox->addWidget(yearLabel, 2, 0);
    paramsBox->addWidget(manufacturerLabel, 3, 0);
    paramsBox->addWidget(modelLabel, 4, 0);
    paramsBox->addWidget(cylindersLabel, 5, 0);
    paramsBox->addWidget(fuelLabel, 6, 0);
    paramsBox->addWidget(mileageLabel, 7, 0);

    paramsBox->addWidget(regionEdit, 0, 1);
    paramsBox->addWidget(priceEdit, 1, 1);
    paramsBox->addWidget(yearEdit, 2, 1);
    paramsBox->addWidget(manufacturerEdit, 3, 1);
    paramsBox->addWidget(modelEdit, 4, 1);
    paramsBox->addWidget(cylindersEdit, 5, 1);
    paramsBox->addWidget(fuelEdit, 6, 1);
    paramsBox->addWidget(mileageEdit, 7, 1);

    mainBox->addLayout(paramsBox);

    QPushButton *btnOk = new QPushButton("Ok");
    QPushButton *btnCancel = new QPushButton("Cancel");

    connect(btnOk, SIGNAL(clicked()), this, SLOT(okButtonSlot()));
    connect(btnCancel, SIGNAL(clicked()), this, SLOT(hide()));

    mainBox->addWidget(btnOk);
    mainBox->addWidget(btnCancel);


    setLayout(mainBox);
}

void EditVehicle::fillFields(QStringList *items)
{
    startWithEmptyFields = false;

    regionEdit->setText(items->at(0));
    priceEdit->setText(items->at(1));
    yearEdit->setText(items->at(2));
    manufacturerEdit->setText(items->at(3));
    modelEdit->setText(items->at(4));
    cylindersEdit->setText(items->at(5));
    fuelEdit->setText(items->at(6));
    mileageEdit->setText(items->at(7));

}

void EditVehicle::okButtonSlot()
{
    QStringList params;

    params.append(regionEdit->text());
    params.append(priceEdit->text());
    params.append(yearEdit->text());
    params.append(manufacturerEdit->text());
    params.append(modelEdit->text());
    params.append(cylindersEdit->text());
    params.append(fuelEdit->text());
    params.append(mileageEdit->text());

    if (startWithEmptyFields)
        emit addedNewVehicle(params);
    else
        emit editedVehicle(params);

    startWithEmptyFields = true;


    hide();
}

void EditVehicle::clearFields()
{
    startWithEmptyFields = true;

    regionEdit->clear();
    priceEdit->clear();
    yearEdit->clear();
    manufacturerEdit->clear();
    modelEdit->clear();
    cylindersEdit->clear();
    fuelEdit->clear();
    mileageEdit->clear();
}
