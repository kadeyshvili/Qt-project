#ifndef ABOUTWIDGET_H
#define ABOUTWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QFont>
#include <QGradient>

class AboutWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AboutWidget(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent* event);

signals:

};

#endif // ABOUTWIDGET_H
