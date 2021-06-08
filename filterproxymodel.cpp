#include "filterproxymodel.h"

FilterProxyModel::FilterProxyModel(QObject *parent) : QSortFilterProxyModel(parent)
{
    setDynamicSortFilter(true);
}

void FilterProxyModel::setMaxPrice(int price)
{
    maxPrice = price;
    invalidateFilter();
}

void FilterProxyModel::setMinPrice(int price)
{
    minPrice = price;
    invalidateFilter();
}

void FilterProxyModel::setMaxYear(int year)
{
    maxYear = year;
    invalidateFilter();
}

void FilterProxyModel::setMinYear(int year)
{
    minYear = year;
    invalidateFilter();
}

void FilterProxyModel::setAcceptedRegions(QStringList regions)
{
    acceptedRegions = regions;
    invalidateFilter();
}

void FilterProxyModel::setAcceptedManufacturers(QStringList manufacturers)
{
    acceptedManufacturers = manufacturers;
    invalidateFilter();
}

void FilterProxyModel::setAcceptedModels(QStringList models)
{
    acceptedModels = models;
    invalidateFilter();
}

void FilterProxyModel::setAcceptedFuelsType(QStringList fuelsType)
{
    acceptedFuelsType = fuelsType;
    invalidateFilter();
}

void FilterProxyModel::setAcceptedCylinders(QStringList cylinders)
{
    acceptedCylinders = cylinders;
    invalidateFilter();
}


bool FilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    if (!filterOn)
    {
        return true;
    }

    QModelIndex indRegions = sourceModel()->index(sourceRow, 0, sourceParent);
    QModelIndex indPrice = sourceModel()->index(sourceRow, 1, sourceParent);
    QModelIndex indYear = sourceModel()->index(sourceRow, 2, sourceParent);
    QModelIndex indManufacturers = sourceModel()->index(sourceRow, 3, sourceParent);
    QModelIndex indModels = sourceModel()->index(sourceRow, 4, sourceParent);
    QModelIndex indCylinders = sourceModel()->index(sourceRow, 5, sourceParent);
    QModelIndex indFuels = sourceModel()->index(sourceRow, 6, sourceParent);
    QModelIndex indMileage = sourceModel()->index(sourceRow, 7, sourceParent);

    bool validRegions = false;
    bool validPrice = false;
    bool validYear = false;
    bool validManufacturers = false;
    bool validModels = false;
    bool validFuels = false;
    bool validCylinders = false;
    bool validMileage = false;

    if (acceptedRegions.size() == 0)
    {
        validRegions = true;
    }
    else if(acceptedRegions.contains(sourceModel()->data(indRegions).toString()))
    {
         validRegions = true;
    }

    int rowPrice = sourceModel()->data(indPrice).toInt();
    if (rowPrice > minPrice)
    {
        validPrice = true;
    }
    if (maxPrice == -1 || rowPrice < maxPrice)
    {
        validPrice = true && validPrice;
    }
    else
    {
        validPrice = false;
    }

    bool ok;
    double rowYear = sourceModel()->data(indYear).toDouble(&ok);
    if (rowYear > minYear)
    {
        validYear = true;
    }
    if (maxYear == -1 || rowYear < maxYear)
    {
        validYear = true && validYear;
    }
    else
    {
        validYear = false;
    }

    if (acceptedManufacturers.size() == 0)
    {
        validManufacturers = true;
    }
    else if(acceptedManufacturers.contains(sourceModel()->data(indManufacturers).toString()))
         validManufacturers = true;

    if (acceptedModels.size() == 0)
    {
        validModels = true;
    }
    else if (acceptedModels.contains(sourceModel()->data(indModels).toString()))
    {
         validModels = true;
    }

    if (acceptedCylinders.size() == 0)
    {
        validCylinders = true;
    }
    else if(acceptedCylinders.contains(sourceModel()->data(indCylinders).toString()))
    {
         validCylinders = true;
    }

    if (acceptedFuelsType.size() == 0)
    {
        validFuels = true;
    }
    else if(acceptedFuelsType.contains(sourceModel()->data(indFuels).toString()))
    {
         validFuels = true;
    }

     return validPrice && validYear && validCylinders && validManufacturers && validModels && validFuels &&
            validRegions;
}

void FilterProxyModel::onFilter()
{
    filterOn = true;
    invalidateFilter();
}

void FilterProxyModel::offFilter()
{
    filterOn = false;
    invalidateFilter();
}
