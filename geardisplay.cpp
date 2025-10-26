#include "geardisplay.h"
#include <QPainter>
#include <QtMath>

GearDisplay::GearDisplay(QWidget *parent)
    : QWidget(parent),
    mCurrentGear('P')
{
    setMinimumSize(200, 250);
    setMaximumSize(200, 250);
}

void GearDisplay::setGear(char gear)
{
    mCurrentGear = gear;
    update();
}

void GearDisplay::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    // Enable Anti-Aliasing
    p.setRenderHint(QPainter::Antialiasing, true);

    // Custom Colours & Font
    QColor lightBlue(84, 215, 219);
    QColor darkBlue(43, 114, 116);
    QColor darkBg(38, 38, 38);
    QFont theFont("Roboto Mono", 20);

    // Lambda function to deduce styling depending on gear
    auto drawGearBox = [&](QRectF rect, char gear, bool isActive) {
        
        // Active Styling
        if (isActive) {
            rect = QRectF(2, rect.y(), 146, 46);
            p.setPen(QPen(lightBlue, 3));
            QLinearGradient linearGrad(rect.topLeft(), QPointF(rect.right(), rect.top()));
            linearGrad.setColorAt(0, lightBlue);
            linearGrad.setColorAt(1, darkBg);
            p.setBrush(linearGrad);
            p.drawRoundedRect(rect, 25, 25);
            QRectF insetRect(rect.x() + 3, rect.y() + 3, rect.width() - 6, rect.height() - 6);
            p.setPen(QPen(darkBg, 2));
            p.setBrush(Qt::NoBrush);
            p.drawRoundedRect(insetRect, 20, 20);
        }

        // Default styling
        else {
            p.setPen(QPen(darkBlue, 3));
            p.setBrush(darkBg);
            p.drawRoundedRect(rect, 25, 25);
        }

        p.setFont(theFont);
        p.setPen(Qt::white);
        p.drawText(rect, Qt::AlignCenter, QString(gear));
    };

    // 1st Rectangle (P)
    drawGearBox(QRectF(2, 4, 46, 46), 'P', mCurrentGear == 'P');

    // 2nd Rectangle (R)
    drawGearBox(QRectF(2, 60, 46, 46), 'R', mCurrentGear == 'R');

    // 3rd Rectangle (N)
    drawGearBox(QRectF(2, 116, 46, 46), 'N', mCurrentGear == 'N');

    // 4th Rectangle (D)
    drawGearBox(QRectF(2, 172, 46, 46), 'D', mCurrentGear == 'D');

}
