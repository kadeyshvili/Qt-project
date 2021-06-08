#ifndef MODESELECTINGWIDGET_H
#define MODESELECTINGWIDGET_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>

class ModeSelectingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ModeSelectingWidget(QWidget *parent = nullptr);

public slots:
    void sellerModeSelect();
    void buyerModeSelect();

signals:
    void changedMode(int modeIndex);
};

#endif // MODESELECTINGWIDGET_H
