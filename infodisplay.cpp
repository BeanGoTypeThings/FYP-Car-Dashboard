#include "infodisplay.h"
#include <QPainter>
#include <QtMath>

InfoDisplay::InfoDisplay(QWidget *parent)
    : QWidget(parent),
    mMileage(0.0),
    mTemperature(20.0)
{
    setMinimumSize(200, 110);
    setMaximumSize(200, 110);
}

void InfoDisplay::setMileage(double mileage)
{
    mMileage = mileage;
    update();
}

void InfoDisplay::setTemperature(double temperature)
{
    mTemperature = temperature;
    update();
}

void InfoDisplay::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    // Enable Anti-Aliasing
    p.setRenderHint(QPainter::Antialiasing, true);

    // Custom Colours & Font
    QColor lightBlue(84, 215, 219);
    QColor darkBg(38, 38, 38);
    QFont infoFont("Roboto", 20);

    // Add padding (otherwise cutoff occurs)
    int padding = 2;

    // Top Rectangle (Mileage)
    QRectF mileageBox(padding, padding, 200 - 2*padding, 50 - 2*padding);
    p.setPen(QPen(lightBlue, 3));
    p.setBrush(darkBg);
    p.drawRoundedRect(mileageBox, 25, 25);

    // Draw Mileage Text
    p.setFont(infoFont);
    p.setPen(Qt::white);
    QString mileageText = QString("%1 mi").arg(mMileage, 0, 'f', 1);
    p.drawText(mileageBox, Qt::AlignCenter, mileageText);

    // Bottom Rectangle (Temperature)
    QRectF tempBox(padding, 60 + padding, 200 - 2*padding, 50 - 2*padding);
    p.setPen(QPen(lightBlue, 3));
    p.setBrush(darkBg);
    p.drawRoundedRect(tempBox, 25, 25);

    // Draw Temperature Text
    p.setPen(Qt::white);
    QString tempText = QString("%1°C").arg(mTemperature, 0, 'f', 0);
    p.drawText(tempBox, Qt::AlignCenter, tempText);
}
