#include "buyermodewidget.h"

QStringList setToList(QSet<QString> set)
{
    QStringList list;
    QSet<QString>::const_iterator i = set.constBegin();
    while (i != set.constEnd())
    {
        if (i->size() > 0)
            list << *i;
        ++i;
    }
    return list;
}

BuyerModeWidget::BuyerModeWidget(QWidget *parent, QStandardItemModel *model)
    : QWidget(parent)
{
    QVBoxLayout *mainBox = new QVBoxLayout();
    centralBox = new QHBoxLayout();

    paramsList << "region"
               << "price"
               << "year"
               << "manufacturer"
               << "model"
               << "number of cylinders"
               << "type of fuel"
               << "odometer";

    selectableParamsIndexes << 0
                            << 3
                            << 4
                            << 5
                            << 6;

    allVehicles = model;
    proxyModel = new FilterProxyModel();
    proxyModel->setSourceModel(allVehicles);
    allVehicles->setColumnCount(8);

    allVehicles->setHorizontalHeaderLabels(paramsList);

    table = new QTableView();
    table->setModel(proxyModel);


    table->setColumnHidden(8, true);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);

    sortFields["price"] = 1;
    sortFields["year"] = 2;
    sortFields["manufacturer"] = 3;

    QHBoxLayout *sortSettingsBox = new QHBoxLayout();
    QLabel *sortLabel = new QLabel("Sort: ");

    fieldsBox = new QComboBox();
    sortOrderBox = new QComboBox();

    sortOrderBox->addItem("ascending order");
    sortOrderBox->addItem("descending order");

    QPushButton *applyButton = new QPushButton("sort!");
    connect(applyButton, SIGNAL(clicked()), this, SLOT(sortRows()));

    sortSettingsBox->addWidget(sortLabel);
    sortSettingsBox->addWidget(fieldsBox);
    sortSettingsBox->addWidget(sortOrderBox);
    sortSettingsBox->addWidget(applyButton);
    mainBox->addLayout(sortSettingsBox);

    QMap<QString, int>::const_iterator i = sortFields.constBegin();
    while (i != sortFields.constEnd())
    {
        fieldsBox->insertItem(i.value(), i.key());
        ++i;
    }

    mainBox->addWidget(table);
    centralBox->addLayout(mainBox);
    setLayout(centralBox);
}

void BuyerModeWidget::readData(QString fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "file error" << file.errorString();
    }

    int rowCount = 500;

    int index = 0;
    QTextStream in(&file);
    while (!in.atEnd() && index < rowCount + 1)
    {
        QString line = in.readLine();
        int pos = line.indexOf(QChar(';'));
        line = line.left(pos);
        if (index == 0)
        {
            index++;
            continue;
        }
        QList<QStandardItem *> standardItemsList;
        for (QString item : line.split(","))
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
        for (int i = 0; i < selectableParamsIndexes.size(); ++i)
        {
            QString paramName = paramsList[selectableParamsIndexes[i]];
            QSet<QString> *variants = &selectableParamsVariants[paramName];
            QStandardItem *item = standardItemsList[selectableParamsIndexes[i]];
            variants->insert(item->text());
        }

        int manufacturerIndex = 3;
        int modelIndex = 4;

        QString modelName = standardItemsList[modelIndex]->text();
        QString manufacturerName = standardItemsList[manufacturerIndex]->text();
        QSet<QString> *modelVariants = &models[manufacturerName];
        modelVariants->insert(modelName);

        allVehicles->appendRow(standardItemsList);
        index++;
    }
    file.close();

    createParamsFilterBox();
}

void BuyerModeWidget::sortRows()
{
    int colIndex = sortFields[fieldsBox->currentText()];
    allVehicles->sort(colIndex, order[sortOrderBox->currentIndex()]);
    int rowsWithEmptyValueInColSort = 0;
    for (int i = 0; i < allVehicles->rowCount(); ++i)
    {
        QStandardItem *item = allVehicles->takeItem(i, colIndex);
        if (item->text().size() == 0)
            rowsWithEmptyValueInColSort++;
        allVehicles->setItem(i, colIndex, item);
    }
    if (order[sortOrderBox->currentIndex()] == Qt::AscendingOrder)
    {
        for (int i = 0; i < rowsWithEmptyValueInColSort; ++i)
            allVehicles->appendRow(allVehicles->takeRow(0));
    }
}

void BuyerModeWidget::filterRows()
{
    selectedParamsVariants.clear();
    for (int i = 0; i < selectableParamsIndexes.size(); ++i)
    {
        QString paramName = paramsList[selectableParamsIndexes[i]];
        QListWidget *listWidget = paramsWidgets[i];
        QSet<QString> variants;
        int countItems = listWidget->count();
        for (int j = 0; j < countItems; ++j)
        {
            QListWidgetItem *item = listWidget->item(j);
            if (item->checkState() == Qt::Checked)
            {
                variants.insert(item->text());
            }
        }
        selectedParamsVariants[paramName] = variants;
    }

    proxyModel->setAcceptedRegions(setToList(selectedParamsVariants["region"]));
    proxyModel->setAcceptedManufacturers(setToList(selectedParamsVariants["manufacturer"]));
    proxyModel->setAcceptedCylinders(setToList(selectedParamsVariants["number of cylinders"]));
    proxyModel->setAcceptedFuelsType(setToList(selectedParamsVariants["type of fuel"]));

    proxyModel->onFilter();
}

QListWidget* BuyerModeWidget::createListWidget(QStringList itemLabels)
{
    QListWidget *listWidget = new QListWidget();
    listWidget->addItems(itemLabels);

    QListWidgetItem* item = 0;
    for(int i = 0; i < listWidget->count(); ++i)
    {
        item = listWidget->item(i);
        item->setCheckState(Qt::Unchecked);
    }
    return listWidget;
}

void BuyerModeWidget::createParamsFilterBox()
{
    QVBoxLayout *box = new QVBoxLayout();

    QHBoxLayout *priceLayout = new QHBoxLayout();

    QLabel *priceLabel = new QLabel("Price");
    QLabel *minLabel = new QLabel("min");
    QLabel *maxLabel = new QLabel("max");
    QLineEdit *minPriceEdit = new QLineEdit();
    QLineEdit *maxPriceEdit = new QLineEdit();

    connect(minPriceEdit, SIGNAL(textChanged(QString)), this, SLOT(minPriceChanged(QString)));
    connect(maxPriceEdit, SIGNAL(textChanged(QString)), this, SLOT(maxPriceChanged(QString)));

    priceLayout->addWidget(priceLabel);
    priceLayout->addWidget(minLabel);
    priceLayout->addWidget(minPriceEdit);
    priceLayout->addWidget(maxLabel);
    priceLayout->addWidget(maxPriceEdit);

    box->addLayout(priceLayout);

    QHBoxLayout *yearLayout = new QHBoxLayout();

    QLabel *yearLabel = new QLabel("Year");
    QLabel *minYearLabel = new QLabel("min");
    QLabel *maxYearLabel = new QLabel("max");
    QLineEdit *minYearEdit = new QLineEdit();
    QLineEdit *maxYearEdit = new QLineEdit();

    connect(minYearEdit, SIGNAL(textChanged(QString)), this, SLOT(minYearChanged(QString)));
    connect(maxYearEdit, SIGNAL(textChanged(QString)), this, SLOT(maxYearChanged(QString)));

    yearLayout->addWidget(yearLabel);
    yearLayout->addWidget(minYearLabel);
    yearLayout->addWidget(minYearEdit);
    yearLayout->addWidget(maxYearLabel);
    yearLayout->addWidget(maxYearEdit);

    box->addLayout(yearLayout);

    QSet<QString> regions = selectableParamsVariants["region"];
    QListWidget *regionListWidget = createListWidget(setToList(regions));
    box->addWidget(regionListWidget);
    paramsWidgets.append(regionListWidget);

    QSet<QString> manufacturers = selectableParamsVariants["manufacturer"];
    QListWidget *manufacturerListWidget = createListWidget(setToList(manufacturers));
    connect(manufacturerListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(addModels(QListWidgetItem*)));
    box->addWidget(manufacturerListWidget);
    paramsWidgets.append(manufacturerListWidget);

    QListWidget *modelsListWidget = createListWidget(QStringList());
    box->addWidget(modelsListWidget);
    paramsWidgets.append(modelsListWidget);

    QSet<QString> cylinders = selectableParamsVariants["number of cylinders"];
    QListWidget *cylindersListWidget = createListWidget(setToList(cylinders));
    box->addWidget(cylindersListWidget);
    paramsWidgets.append(cylindersListWidget);

    QSet<QString> fuels = selectableParamsVariants["type of fuel"];
    QListWidget *fuelsListWidget = createListWidget(setToList(fuels));
    box->addWidget(fuelsListWidget);
    paramsWidgets.append(fuelsListWidget);

    QPushButton *filterButton = new QPushButton("Filter");
    connect(filterButton, SIGNAL(clicked()), this, SLOT(filterRows()));
    box->addWidget(filterButton);

    QPushButton *cancelButton = new QPushButton("Cancel");
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(offFilter()));
    box->addWidget(cancelButton);

    centralBox->addLayout(box);
}

void BuyerModeWidget::addModels(QListWidgetItem *selectedItem)
{
    QString paramName = selectedItem->text();

    if (state.contains(paramName))
    {
        state[paramName] = !state[paramName];
    }
    else {
        state[paramName] = true;
    }

    int modelsWidgetIndex = 2;
    QListWidget *modelsListWidget = paramsWidgets[modelsWidgetIndex];
    modelsListWidget->clear();

    if (state[paramName] == true)
    {
        selectedParamsVariants["manufacturer"].insert(selectedItem->text());
        selectedItem->setCheckState(Qt::Checked);
    }
    else
    {
        selectedParamsVariants["manufacturer"].remove(paramName);
        selectedItem->setCheckState(Qt::Unchecked);
    }
    QSet<QString> manufacturers = selectedParamsVariants["manufacturer"];

    QStringList allModels;
    QSet<QString>::const_iterator i = manufacturers.constBegin();
    while (i != manufacturers.constEnd())
    {
        QSet<QString> manufacturerModels = models[*i];
        QStringList manufacturerModelsList = setToList(manufacturerModels);
        for (int j = 0; j < manufacturerModelsList.size(); ++j)
        {
            allModels.append(manufacturerModelsList[j]);
        }
        ++i;
    }

    modelsListWidget->addItems(allModels);

    QListWidgetItem* item = 0;
    for(int i = 0; i < modelsListWidget->count(); ++i)
    {
        item = modelsListWidget->item(i);
        item->setCheckState(Qt::Unchecked);
    }
    modelsListWidget->update();
}

void BuyerModeWidget::offFilter()
{
    for (int i = 0; i < paramsWidgets.size(); ++i)
    {
        QListWidget *listWidget = paramsWidgets[i];
        int countItems = listWidget->count();
        for (int j = 0; j < countItems; ++j)
        {
            QListWidgetItem *item = listWidget->item(j);
            item->setCheckState(Qt::Unchecked);
        }
    }
    proxyModel->offFilter();
}

void BuyerModeWidget::minPriceChanged(QString price)
{
    bool ok;
    int tmp = price.toInt(&ok);
    if (ok)
    {
        proxyModel->setMinPrice(tmp);
    }
    else if (price.size() == 0)
    {
        proxyModel->setMinPrice(-1);
    }
}

void BuyerModeWidget::maxPriceChanged(QString price)
{
    bool ok;
    int tmp = price.toInt(&ok);
    if (ok)
        proxyModel->setMaxPrice(tmp);
    else if (price.size() == 0)
    {
        proxyModel->setMaxPrice(-1);
    }
}

void BuyerModeWidget::minYearChanged(QString year)
{
    bool ok;
    int tmp = year.toInt(&ok);
    if (ok)
        proxyModel->setMinYear(tmp);
    else if (year.size() == 0) {
        proxyModel->setMinYear(-1);
    }
}

void BuyerModeWidget::maxYearChanged(QString year)
{
    bool ok;
    int tmp = year.toInt(&ok);
    if (ok)
    {
        proxyModel->setMaxYear(tmp);
    }
    else if (year.size() == 0)
    {
        proxyModel->setMaxYear(-1);
    }
}

void BuyerModeWidget::updateRowParams(QStringList params, int rowIndex)
{
    selectableParamsVariants.clear();
    selectedParamsVariants.clear();
    models.clear();

    QSet<QString> manufacturers = selectedParamsVariants["manufacturer"];
    for (int i = 0; i < allVehicles->rowCount(); ++i) {
        for (int j = 0; j < selectableParamsIndexes.size(); ++j)
        {
            if (selectableParamsIndexes[j] == 4)
            {
                QStandardItem *item = allVehicles->takeItem(i, 4);
                QString modelName = item->text();
                allVehicles->setItem(i, 4, item);

                item = allVehicles->takeItem(i, 3);
                QString manufacturerName = item->text();
                allVehicles->setItem(i, 3, item);
                models[manufacturerName].insert(modelName);
                continue;
            }
            QString paramName = paramsList[selectableParamsIndexes[j]];
            QSet<QString> *variants = &selectableParamsVariants[paramName];
            QStandardItem *item = allVehicles->takeItem(i, selectableParamsIndexes[j]);
            variants->insert(item->text());
            allVehicles->setItem(i, selectableParamsIndexes[j], item);
        }
    }
    qDebug() << allVehicles->rowCount();

    for (int i = 0; i < paramsWidgets.size(); ++i)
    {
        QListWidget *listWidget = paramsWidgets[i];
        listWidget->clear();
    }

    qDebug() << selectableParamsVariants["manufacturer"];


    paramsWidgets[0]->addItems(setToList(selectableParamsVariants["region"]));
    paramsWidgets[1]->addItems(setToList(selectableParamsVariants["manufacturer"]));
    paramsWidgets[3]->addItems(setToList(selectableParamsVariants["number of cylinders"]));
    paramsWidgets[4]->addItems(setToList(selectableParamsVariants["type of fuel"]));

    for (int i = 0; i < paramsWidgets.size(); ++i)
    {
        QListWidget *listWidget = paramsWidgets[i];
        int countItems = listWidget->count();
        for (int j = 0; j < countItems; ++j)
        {
            QListWidgetItem *item = listWidget->item(j);
            item->setCheckState(Qt::Unchecked);
        }
        listWidget->update();
    }

    paramsWidgets[2]->update();
    update();
}


