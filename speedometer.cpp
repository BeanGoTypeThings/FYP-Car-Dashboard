#include "speedometer.h"
#include <QPainter>
#include <QPainterPath>
#include <QConicalGradient>
#include <QFontDatabase>
#include <QtMath>

speedometer::speedometer(QWidget *parent)
    : QWidget(parent),
    m_speed(0),
    m_minSpeed(0),
    m_maxSpeed(160)
{
    setMinimumSize(350, 300);
}

void speedometer::setSpeed(int speed)
{
    m_speed = qBound(m_minSpeed, speed, m_maxSpeed);
    update();
}

void speedometer::setFuel(int fuel)
{

}

void speedometer::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    // Enable Anti-Analysing.
    p.setRenderHint(QPainter::Antialiasing, true);

    // Place widget into the center.
    int w = width();
    int h = height();
    p.translate(w / 2.0, h / 2.0);

    // Custom colours.
    QColor lightBlue(84, 215, 219);
    QColor darkBlue(43, 114, 116);
    QColor darkBg(38, 38, 38);
    QFont normalFont("Roboto", 50);
    QFont smallFont("Roboto", 25);

    // Create the main circle.
    QRectF mainRect(-200, -200, 400, 400);
    p.setPen(QPen(lightBlue, 3));
    p.setBrush(darkBg);
    p.drawEllipse(mainRect);

    // Create the tick marks.
    int majorTickCount = 100;
    for (int i = 0; i <= majorTickCount; ++i) {
        double angle = 195 - i * (205.0 / majorTickCount);
        double rad = qDegreesToRadians(angle);
        double x1 = 195 * qCos(rad);
        double y1 = -195 * qSin(rad);
        double x2 = 190 * qCos(rad);
        double y2 = -190 * qSin(rad);

        QColor tickColor = (angle >= 180.0 - 360) ? lightBlue : QColor(114, 219, 84, 60);
        p.setPen(QPen(tickColor, 4, Qt::SolidLine, Qt::RoundCap));
        p.drawLine(QPointF(x1, y1), QPointF(x2, y2));
    }

    // Speed Text.
    p.setPen(Qt::white);
    normalFont.setUnderline(true);
    p.setFont(normalFont);
    QString speedText = QString("%1").arg(m_speed, 3, 10, QLatin1Char('0'));
    QRectF speedTextRect(-75, -150, 150, 60);
    p.drawText(speedTextRect, Qt::AlignCenter, speedText);

    // MPH Text.
    QString measurementText = QString("MPH");
    QRectF measurementTextRect(-75, -97.5, 150, 30);
    p.setFont(smallFont);
    p.drawText(measurementTextRect, Qt::AlignCenter, measurementText);

    // Numerical Speed Values.
    p.setPen(lightBlue);
    p.setFont(smallFont);
    struct Label { int val; double ang; };
    QVector<Label> labels = {
        {0, 105}, {40, 60}, {80, 0}, {120, -60}, {160, -105}
    };
    for (const auto &l : labels) {
        double rad = qDegreesToRadians(l.ang + 90);
        double r = 165;
        QPointF pos(r * qCos(rad), -r * qSin(rad));
        QRectF numericalSpeedRect(pos.x() - 25, pos.y() - 15, 50, 30);
        p.drawText(numericalSpeedRect, Qt::AlignCenter, QString::number(l.val));
    }
}
