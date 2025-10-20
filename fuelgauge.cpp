#include "fuelgauge.h"
#include <QPainter>
#include <QPainterPath>
#include <QConicalGradient>
#include <QFontDatabase>
#include <QtMath>
#include <QSvgRenderer>

fuelgauge::fuelgauge(QWidget *parent)
    : QWidget(parent),
    m_fuelLevel(100.0)
{
    setMinimumSize(300, 300);
}

void fuelgauge::setFuelLevel(float fuel)
{
    m_fuelLevel = qBound(0.0f, fuel, 100.0f);
    update();
}

void fuelgauge::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    // Enable Anti-Aliasing
    p.setRenderHint(QPainter::Antialiasing, true);

    // Get the SVGs
    QSvgRenderer svgRenderer1(QStringLiteral("/Users/lukebessell/Documents/GitHub/FYP-Car-Dashboard/images/fuel_bg.svg"));
    QSvgRenderer svgRenderer2(QStringLiteral("/Users/lukebessell/Documents/GitHub/FYP-Car-Dashboard/images/fuel_icon.svg"));

    QRectF svgRect1(50, 175, 286, 54); // Sizing for fuel_bg.svg

    double iconX = svgRect1.left() + svgRect1.height() * 0.4;
    double iconY = svgRect1.center().y() - 18;

    QRectF svgRect2(iconX, iconY, 28, 34); // Sizing for fuel_icon.svg

    // Render the SVGs
    svgRenderer1.render(&p, svgRect1);
    svgRenderer2.render(&p, svgRect2);

    // Left circle seperator
    p.setPen(QColor(143, 214, 112));
    p.setBrush(QColor(143, 214, 112));
    p.drawEllipse(QPointF(svgRect1.left() + svgRect2.width() + svgRect1.height() * 0.65,svgRect1.center().y()), 3, 3);

    // Create squares to indicate remaining fuel
    int totalRects = 10;
    double fuelLevel = m_fuelLevel / 100.0;
    double totalWidth = svgRect1.width() * 0.85;
    double rectWidth = totalWidth / totalRects * 0.3;
    double spacing = totalWidth / totalRects * 0.1;
    double barWidth = totalRects * rectWidth + (totalRects - 1) * spacing;
    double rectHeight = svgRect1.height() / 2;
    double bevel = rectHeight / 7.5;
    double startX = svgRect1.left() + (svgRect1.width() - barWidth) / 2.5;
    double y = svgRect1.top() + (svgRect1.height() - rectHeight) / 2.0;


    for (int i = 0; i < totalRects; ++i) {
        double x = startX + i * (rectWidth + spacing);
        QPainterPath path;

        path.addRoundedRect(QRectF(x, y, rectWidth, rectHeight), bevel, bevel);

        QColor colour = (i < totalRects * fuelLevel) ? QColor(71, 224, 7) : QColor(147, 147, 147);
        p.fillPath(path, colour);
    }

    // Right circle seperator
    p.setPen(QColor(143, 214, 112));
    p.setBrush(QColor(143, 214, 112));
    p.drawEllipse(QPointF(svgRect1.right() - svgRect2.width() - svgRect1.height() * 1.4,svgRect1.center().y()), 3, 3);

    // Remaining fuel text
    p.setPen(Qt::green);
    QFont font("Consolas", 24, QFont::Bold);
    p.setFont(font);

    double textX = svgRect1.right() - svgRect1.height() / 0.5;
    double textY = svgRect1.center().y() - 25;

    QString text = QString(QString::number(int(trunc(m_fuelLevel*3))) + "M");
    QRectF textRect(textX, textY, 100, 50);
    p.drawText(textRect, Qt::AlignCenter, text);

}
