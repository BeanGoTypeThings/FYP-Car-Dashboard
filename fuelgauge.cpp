#include "fuelgauge.h"
#include <QPainter>
#include <QPainterPath>
#include <QConicalGradient>
#include <QFontDatabase>
#include <QtMath>
#include <QSvgRenderer>

fuelgauge::fuelgauge(QWidget *parent)
    : QWidget(parent),
    m_speed(100),
    m_minSpeed(0),
    m_maxSpeed(100)
{
    setMinimumSize(300, 300);
}

void fuelgauge::setSpeed(int speed)
{
    m_speed = qBound(m_minSpeed, speed, m_maxSpeed);
    update();
}

void fuelgauge::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    QSvgRenderer svgRenderer1(QStringLiteral("/Users/lukebessell/Documents/GitHub/FYP-Car-Dashboard/images/fuel_bg.svg"));
    QSvgRenderer svgRenderer2(QStringLiteral("/Users/lukebessell/Documents/GitHub/FYP-Car-Dashboard/images/fuel_icon.svg"));

    // Render the SVG onto the painter
    svgRenderer1.render(&p, QRectF(50, 175, 250, 50));
    svgRenderer2.render(&p, QRectF(0, 175, 40, 50));

    // Enable Anti-Aliasing.
    p.setRenderHint(QPainter::Antialiasing, true);

    int w = width();
    int h = height();
    int side = qMin(w, h);

    p.translate(w / 2.0, h * 0.75);
    p.scale(side / 500.0, side / 500.0);

}
