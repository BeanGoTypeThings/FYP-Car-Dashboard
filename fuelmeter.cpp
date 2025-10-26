#include "fuelmeter.h"
#include <QPainter>
#include <QPainterPath>
#include <QConicalGradient>
#include <QFontDatabase>
#include <QtMath>

fuelmeter::fuelmeter(QWidget *parent)
    : QWidget(parent),
    mFuelLevel(100.0)
{
    setMinimumSize(400, 150);
    setMaximumSize(400, 150);
}

void fuelmeter::setFuelLevel(float fuel)
{
    mFuelLevel = qBound(0.0f, fuel, 100.0f);
    update();
}

void fuelmeter::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);

    // Custom Colours & Font
    QColor lightBlue(84, 215, 219);
    QColor darkBlue(43, 114, 116);
    QColor lightRed(219, 84, 86);
    QColor darkRed(82, 30, 31);
    QFont normalFont("Roboto", 20);

    // Fuel meter curve
    QPainterPath curvePath;
    curvePath.moveTo(65.0, 5.0);
    curvePath.quadTo(QPointF(200.0, 120.0), QPointF(335.0, 5.0));

    // Colour based on Fuel Level remaining
    QColor curveColourMain = (mFuelLevel < 20.0) ? lightRed : lightBlue;
    QColor curveColourBG = (mFuelLevel < 20.0) ? darkRed : darkBlue;
    QColor fuelTextColour = (mFuelLevel < 20.0) ? lightRed : lightBlue;
    double fuelPercent = mFuelLevel / 100.0;

    // Draw background curve
    p.setPen(QPen(curveColourBG, 10, Qt::SolidLine, Qt::RoundCap));
    p.drawPath(curvePath);

    // Draw remaining fuel curve
    if (fuelPercent > 0) {
        QPainterPath filledPath;

        int steps = 250;
        for (int i = 0; i <= steps * fuelPercent; ++i) {
            double t = i / (double)steps;
            QPointF point = curvePath.pointAtPercent(t);
            if (i == 0) {
                filledPath.moveTo(point);
            } else {
                filledPath.lineTo(point);
            }
        }

        p.setPen(QPen(curveColourMain, 10, Qt::SolidLine, Qt::RoundCap));
        p.drawPath(filledPath);
    }

    // Fuel Text.
    p.setPen(fuelTextColour);
    p.setFont(normalFont);
    QString fuelText = QString("%1%").arg(mFuelLevel, 0, 'f', 0);
    QRectF fuelTextRect(0, 10, width(), 60);
    p.drawText(fuelTextRect, Qt::AlignCenter, fuelText);
}
