#ifndef FILTERPROXYMODEL_H
#define FILTERPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QWidget>
#include <QDebug>


class FilterProxyModel : public QSortFilterProxyModel
{

public:
    FilterProxyModel(QObject *parent = nullptr);

    bool filterOn = false;

    int minPrice = -1;
    int maxPrice = -1;

    int minYear = -1;
    int maxYear = -1;

    int minMileage = -1;
    int maxMileage = -1;

    QStringList acceptedRegions;
    QStringList acceptedManufacturers;
    QStringList acceptedModels;
    QStringList acceptedCylinders;
    QStringList acceptedFuelsType;


protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

public slots:
    void setMinPrice(int price);
    void setMaxPrice(int price);

    void setMinYear(int year);
    void setMaxYear(int year);

    void setAcceptedManufacturers(QStringList manufacturers);
    void setAcceptedModels(QStringList models);
    void setAcceptedFuelsType(QStringList fuelsType);
    void setAcceptedRegions(QStringList regions);
    void setAcceptedCylinders(QStringList cylinders);

    void setMinMileage(int year);
    void setMaxMileage(int year);

    void onFilter();
    void offFilter();
};

#endif // FILTERPROXYMODEL_H
