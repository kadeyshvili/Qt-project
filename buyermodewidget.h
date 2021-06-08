#ifndef BUYERMODEWIDGET_H
#define BUYERMODEWIDGET_H

#include <QObject>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QTableView>
#include <QFile>
#include <QTextStream>
#include <QWidget>
#include <iostream>
#include <QDebug>
#include <QMessageBox>
#include <QVariant>
#include <QMap>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QListWidgetItem>

#include "filterproxymodel.h"


class BuyerModeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BuyerModeWidget(QWidget *parent = nullptr, QStandardItemModel *model = nullptr);

    QHBoxLayout *centralBox;

    QStandardItemModel *allVehicles;

    FilterProxyModel *proxyModel;

    QMap<QString, QSet<QString>> models;

    QMap<QString, int> sortFields;

    QComboBox *fieldsBox;
    QComboBox *sortOrderBox;

    QStringList paramsList;
    QVector <int> selectableParamsIndexes;
    QMap<QString, QSet<QString>> selectableParamsVariants;
    QMap<QString, QSet<QString>> selectedParamsVariants;
    QList<QListWidget*> paramsWidgets;
    QMap<QString, bool> state;

    QList<Qt::SortOrder> order = {Qt::AscendingOrder, Qt::DescendingOrder};

    QTableView *table;

    void createParamsFilterBox();
    QListWidget *createListWidget(QStringList);
    void readData(QString fileName);

private slots:

    void sortRows();
    void filterRows();
    void addModels(QListWidgetItem *selectedItem);
    void offFilter();
    void minPriceChanged(QString price);
    void maxPriceChanged(QString price);

    void minYearChanged(QString year);
    void maxYearChanged(QString year);

    void updateRowParams(QStringList params, int rowIndex);
};

#endif // BUYERMODEWIDGET_H
