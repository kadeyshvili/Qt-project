#ifndef EDITVEHICLE_H
#define EDITVEHICLE_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QStandardItem>
#include <QPushButton>

class EditVehicle : public QWidget
{
    Q_OBJECT
public:
    explicit EditVehicle(QWidget *parent = nullptr);

    QVBoxLayout *mainBox;
    bool startWithEmptyFields;

    QLineEdit *regionEdit;
    QLineEdit *priceEdit;
    QLineEdit *yearEdit;
    QLineEdit *manufacturerEdit;
    QLineEdit *modelEdit;
    QLineEdit *cylindersEdit;
    QLineEdit *fuelEdit;
    QLineEdit *mileageEdit;

    void fillFields(QStringList *items);
    void clearFields();

signals:
    void addedNewVehicle(QStringList params);
    void editedVehicle(QStringList params);

public slots:
    void okButtonSlot();

};

#endif // EDITVEHICLE_H
