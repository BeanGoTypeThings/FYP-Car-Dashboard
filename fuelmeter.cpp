#include "fuelmeter.h"
#include <QPainter>
#include <QPainterPath>
#include <QConicalGradient>
#include <QFontDatabase>
#include <QtMath>
#include <QQmlContext>
#include <QObject>
#include <QSvgRenderer>
#include <QQuickItem>
#include <QQuickWidget>

fuelmeter::fuelmeter(QWidget *parent)
    : QWidget(parent),
    m_fuelLevel(100.0),
    m_fuelIcon(nullptr)
{
    setMinimumSize(300, 300);

    // Create QML fuel icon widget
    m_fuelIcon = new QQuickWidget(this);
    
    // Render in a better quality (performance cost)
    QSurfaceFormat format;
    format.setSamples(4);
    m_fuelIcon->setFormat(format);
    
    m_fuelIcon->setSource(QUrl::fromLocalFile("/Users/lukebessell/Documents/GitHub/FYP-Car-Dashboard/images/fuel_icon.qml"));
    m_fuelIcon->setResizeMode(QQuickWidget::SizeRootObjectToView);
    m_fuelIcon->setAttribute(Qt::WA_AlwaysStackOnTop);
    m_fuelIcon->setAttribute(Qt::WA_TranslucentBackground);
    m_fuelIcon->setClearColor(Qt::transparent);
}

void fuelmeter::setFuelLevel(float fuel)
{
    m_fuelLevel = qBound(0.0f, fuel, 100.0f);

    // Update QML fuel icon if low fuel
    if (m_fuelIcon && m_fuelIcon->rootObject()) {
        m_fuelIcon->rootObject()->setProperty("fuelLevel", m_fuelLevel);
    }

    update();
}

void fuelmeter::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    // Enable Anti-Aliasing
    p.setRenderHint(QPainter::Antialiasing, true);

    // Get the background SVG
    QSvgRenderer svgRenderer1(QStringLiteral("/Users/lukebessell/Documents/GitHub/FYP-Car-Dashboard/images/fuel_bg.svg"));

    QRectF svgBgRect(0, 220, 300, 57); // Sizing for fuel_bg.svg

    double iconX = svgBgRect.left() + svgBgRect.height() * 0.4;
    double iconY = svgBgRect.center().y() - 18;

    // Size and position for QML fuel icon
    QRectF iconRect(iconX, iconY, 28, 34);

    // Render the background SVG
    svgRenderer1.render(&p, svgBgRect);

    // Show the QML fuel icon
    if (m_fuelIcon) {
        m_fuelIcon->setGeometry(iconRect.toRect());
        m_fuelIcon->show();
    }

    // Left circle seperator
    if (m_fuelLevel < 20.0) {
        p.setPen(QColor(210, 48, 48));
        p.setBrush(QColor(154, 10, 10));
    }
    else {
        p.setPen(QColor(143, 214, 112));
        p.setBrush(QColor(143, 214, 112));
    }
    p.drawEllipse(QPointF(svgBgRect.left() + iconRect.width() + svgBgRect.height() * 0.65,svgBgRect.center().y()), 3, 3);

    // Create squares to indicate remaining fuel
    int totalRects = 10;
    double fuelLevel = m_fuelLevel / 100.0;
    double totalWidth = svgBgRect.width() * 0.85;
    double rectWidth = totalWidth / totalRects * 0.3;
    double spacing = totalWidth / totalRects * 0.1;
    double barWidth = totalRects * rectWidth + (totalRects - 1) * spacing;
    double rectHeight = svgBgRect.height() / 2;
    double bevel = rectHeight / 7.5;
    double startX = svgBgRect.left() + (svgBgRect.width() - barWidth) / 2.5;
    double y = svgBgRect.top() + (svgBgRect.height() - rectHeight) / 2.0;


    for (int i = 0; i < totalRects; ++i) {
        double x = startX + i * (rectWidth + spacing);
        QPainterPath path;

        path.addRoundedRect(QRectF(x, y, rectWidth, rectHeight), bevel, bevel);

        bool colour = (i < totalRects * fuelLevel) ? true : false;

        if (colour == true) {
            if (m_fuelLevel < 20.0) {
                p.fillPath(path, QColor(154, 10, 10));
            }
            else {
                p.fillPath(path, QColor(71, 224, 7));
            }
        }
        else {
            p.fillPath(path, QColor(147, 147, 147));
        }
    }

    // Right circle seperator
    if (m_fuelLevel < 20.0) {
        p.setPen(QColor(210, 48, 48));
        p.setBrush(QColor(154, 10, 10));
    }
    else {
        p.setPen(QColor(143, 214, 112));
        p.setBrush(QColor(143, 214, 112));
    }
    p.drawEllipse(QPointF(svgBgRect.right() - iconRect.width() - svgBgRect.height() * 1.4,svgBgRect.center().y()), 3, 3);

    // Remaining fuel text
    if (m_fuelLevel < 20.0) {
        p.setPen(QColor(210, 48, 48));
    }
    else {
        p.setPen(QColor(71, 224, 7));
    }
    QFont font("Roboto", 24, QFont::Bold);
    p.setFont(font);

    double textX = svgBgRect.right() - svgBgRect.height() / 0.5;
    double textY = svgBgRect.center().y() - 25;

    QString text = QString(QString::number(int(trunc(m_fuelLevel*3))) + "M");
    QRectF textRect(textX, textY, 100, 50);
    p.drawText(textRect, Qt::AlignCenter, text);

}
