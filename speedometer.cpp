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
    setMinimumSize(300, 300);
}

void speedometer::setSpeed(int speed)
{
    m_speed = qBound(m_minSpeed, speed, m_maxSpeed);
    update();
}

void speedometer::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    // Enable Anti-Analysing.
    p.setRenderHint(QPainter::Antialiasing, true);

    int w = width();
    int h = height();
    int side = qMin(w, h);

    p.translate(w / 2.0, h * 0.9);
    p.scale(side / 300.0, side / 300.0);

    QColor green(114, 219, 84);
    QColor darkBg(56, 56, 56);

    // Inner Semicircle
    QRectF innerSemi(-60, -60, 120, 120);
    QPainterPath innerArc;
    innerArc.moveTo(innerSemi.center().x(), innerSemi.center().y());
    innerArc.arcTo(innerSemi, 180, -180);
    innerArc.closeSubpath();

    p.setBrush(darkBg);
    p.setPen(QPen(green, 3));
    p.drawPath(innerArc);

    // Outer Radial Semicircle
    QRectF outerRect(-120, -120, 240, 240);
    QRectF innerRect(-80, -80, 160, 160);
    QPainterPath baseArc;

    baseArc.moveTo(outerRect.center().x() - outerRect.width()/2, outerRect.center().y());
    baseArc.arcTo(outerRect, 180, -180);
    baseArc.arcTo(innerRect, 0, 180);
    baseArc.closeSubpath();

    p.setBrush(darkBg);
    p.setPen(QPen(green, 3));
    p.drawPath(baseArc);

    // Gradient Progress Arc
    double spanAngle = (double)m_speed / m_maxSpeed * 180.0;
    if (spanAngle > 0) {
        QConicalGradient grad(0, 0, 90);
        grad.setColorAt(0.0, QColor(132, 201, 113, 190));
        grad.setColorAt(0.75, QColor(40, 61, 34, 190));
        grad.setColorAt(1.0, QColor(132, 201, 113, 190));

        QPainterPath fillArc;
        fillArc.moveTo(innerRect.center().x(), innerRect.center().y());
        fillArc.arcTo(outerRect, 180, -spanAngle);
        fillArc.arcTo(innerRect, 180 - spanAngle, spanAngle);
        fillArc.closeSubpath();

        p.setBrush(grad);
        p.setPen(Qt::NoPen);
        p.drawPath(fillArc);
    }

    // Tick marks
    int majorTickCount = 24;
    for (int i = 0; i <= majorTickCount; ++i) {
        double angle = 180 - i * (180.0 / majorTickCount);
        double rad = qDegreesToRadians(angle);
        double x1 = 130 * qCos(rad);
        double y1 = -130 * qSin(rad);
        double x2 = 140 * qCos(rad);
        double y2 = -140 * qSin(rad);

        QColor tickColor = (angle >= 180.0 - spanAngle) ? green : QColor(114, 219, 84, 60);
        p.setPen(QPen(tickColor, 4, Qt::SolidLine, Qt::RoundCap));
        p.drawLine(QPointF(x1, y1), QPointF(x2, y2));
    }

    // Speed Text
    p.setPen(green);
    QFont font("Consolas", 24, QFont::Bold);
    p.setFont(font);

    QString text = QString("%1").arg(m_speed, 3, 10, QLatin1Char('0'));
    QRectF textRect(-40, -40, 80, 30);
    p.drawText(textRect, Qt::AlignCenter, text);

    // Numerical Values
    QFont smallFont("Digital-7 Mono", 14);
    p.setFont(smallFont);
    struct Label { int val; double ang; };
    QVector<Label> labels = {
        {0, 90}, {40, 45}, {80, 0}, {120, -45}, {160, -90}
    };
    for (const auto &l : labels) {
        double rad = qDegreesToRadians(l.ang + 90);
        double r = 160;
        QPointF pos(r * qCos(rad), -r * qSin(rad));
        QRectF rct(pos.x() - 15, pos.y() - 10, 30, 20);
        p.drawText(rct, Qt::AlignCenter, QString::number(l.val));
    }
}
