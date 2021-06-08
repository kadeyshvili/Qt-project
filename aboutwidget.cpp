#include "aboutwidget.h"

#include <QPainterPath>
#include <QTextDocument>

AboutWidget::AboutWidget(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("About");
}

void AboutWidget::paintEvent(QPaintEvent* event)
{


    QRectF rectangle1(200.0, 100.0, 250.0, 250.0);
    QRectF rectangle2(225, 125.0, 200.0, 200.0);
    QRectF rectangle3(285, 185.0, 80.0, 80.0);

    QPen myPen, myPen2, myPen3;

    QPainterPath myPath1, myPath2, myPath3, myPath4;
    myPath1.addEllipse(rectangle1);
    myPath2.addEllipse(rectangle2);
    myPath3.addEllipse(rectangle3);

    QPainter painter(this);


    painter.setPen(myPen);
    painter.fillPath(myPath1, Qt::darkGray);
    painter.fillPath(myPath2, Qt::white);
    painter.drawPath(myPath1);
    painter.drawPath(myPath2);


    myPen2.setWidth(5);
    painter.setPen(myPen2);
    QLineF line1(325, 230, 420, 200);
    QLineF line2(325, 230, 416, 270);
    QLineF line3(325, 230, 365, 316);
    QLineF line4(325, 230, 290, 315);
    QLineF line5(325, 230, 240, 270);
    QLineF line6(325, 230, 230, 200);
    QLineF line7(325, 230, 280, 140);
    QLineF line8(325, 230, 370, 140);

    painter.drawLine(line1);
    painter.drawLine(line2);
    painter.drawLine(line3);
    painter.drawLine(line4);
    painter.drawLine(line5);
    painter.drawLine(line6);
    painter.drawLine(line7);
    painter.drawLine(line8);

    painter.setPen(myPen);
    painter.fillPath(myPath3, Qt::gray);


    QPainter painter2(this);
    QFont myFont;
    myFont.setPointSize(myFont.pointSize() * 2);
    QPointF point(293, 235);
    myPath4.addText(point, myFont, tr("Car$"));
    painter2.setPen(myPen3);

    painter2.drawPath(myPath4);
    painter.drawPath(myPath3);



    QRectF rect3(60.0, 70.0, 110.0, 100.0);
    QRectF rect4(100, 250, 500, 300);
    QPainter painter3(this);
    painter3.setPen(Qt::blue);
    painter3.drawText(rect3, Qt::AlignCenter, tr("Student №160"));
    painter3.drawText(rect4, Qt::AlignCenter, tr("Programme for buying and selling used cars with 2 modes:\n'buyer' and 'seller'"));

}
