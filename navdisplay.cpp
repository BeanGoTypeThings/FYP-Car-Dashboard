#include "navdisplay.h"
#include <QPainter>
#include <QPainterPath>
#include <QtMath>
#include <QSvgRenderer>
#include <QRandomGenerator>

NavDisplay::NavDisplay(QWidget *parent)
    : QWidget(parent),
    mCurrentArrowDirection(0),
    mDistanceToTurn(500.0)
{
    setMinimumSize(500, 220);
    setMaximumSize(500, 220);

    // Randomly change the arrow (3 seconds).
    mArrowTimer = new QTimer(this);
    connect(mArrowTimer, &QTimer::timeout, this, &NavDisplay::updateArrow);
    mArrowTimer->start(3000);
}

void NavDisplay::updateArrow()
{
    // Select random arrow direction.
    mCurrentArrowDirection = QRandomGenerator::global()->bounded(3);

    // Random distance between 100-1000
    mDistanceToTurn = QRandomGenerator::global()->bounded(100, 1001);

    update();
}

void NavDisplay::drawArrow(QPainter &p, const QPointF &center, double rotation)
{
    p.save();
    p.translate(center);
    p.rotate(rotation);

    QColor white(255, 255, 255);
    p.setPen(QPen(white, 3));
    p.setBrush(Qt::NoBrush);

    // Draw the arrow
    QPainterPath arrow;
    arrow.moveTo(0, -28);
    arrow.lineTo(24.75, 0);
    arrow.lineTo(8, 0);
    arrow.lineTo(8, 30);
    arrow.lineTo(-8, 30);
    arrow.lineTo(-8, 0);
    arrow.lineTo(-24.75, 0);
    arrow.closeSubpath();

    p.drawPath(arrow);
    p.restore();
}

void NavDisplay::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    // Enable Anti-Aliasing
    p.setRenderHint(QPainter::Antialiasing, true);

    // Custom Colours & Font
    QColor lightBlue(84, 215, 219);
    QColor darkBg(38, 38, 38);
    QFont navFont("Roboto", 25);

    // Main Rect
    int centerX = width() / 2 - 100;
    int centerY = height() / 2 - 100;
    QRectF navBox(centerX, centerY, 200, 95);
    p.setPen(QPen(lightBlue, 3));
    p.setBrush(darkBg);

    // Distance Text
    p.setFont(navFont);
    p.setPen(Qt::white);
    QString navText = QString("%1").arg(mDistanceToTurn, 0, 'f', 0);
    QRectF distanceBox(centerX, centerY - 25, 200, 95);
    p.drawText(distanceBox, Qt::AlignCenter, navText);

    // Metres Measurement
    QString measurementText = QString("METRES");
    QRectF measurementBox(centerX, centerY, 200, 95);
    p.drawText(measurementBox, Qt::AlignCenter, measurementText);

    // Navigation arrow placement
    double arrowY = centerY + 110;
    double arrowX = centerX + 100;

    // Choose rotation (UP/LEFT/RIGHT)
    double arrowRotation = 0;
    switch(mCurrentArrowDirection) {
        case 0: arrowRotation = 0; break;
        case 1: arrowRotation = -90; break;
        case 2: arrowRotation = 90; break;
    }

    drawArrow(p, QPointF(arrowX, arrowY), arrowRotation);

    // Load Dashed Line SVG
    QSvgRenderer svgRenderer(QStringLiteral(":/images/dashed_line.svg"));

    // Left Line
    p.save();
    p.translate(navBox.left() - 10, navBox.center().y());
    p.rotate(190);
    QRectF leftLineRect(-30, -110, 2, 200);
    svgRenderer.render(&p, leftLineRect);
    p.restore();

    // Right Line
    p.save();
    p.translate(navBox.right() + 10, navBox.center().y());
    p.rotate(-190);
    QRectF rightLineRect(30, -110, 2, 200);
    svgRenderer.render(&p, rightLineRect);
    p.restore();
}
