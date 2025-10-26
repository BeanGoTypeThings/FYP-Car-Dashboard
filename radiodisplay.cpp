#include "radiodisplay.h"
#include <QPainter>
#include <QtMath>
#include <QTime>
#include <QProgressBar>

RadioDisplay::RadioDisplay(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(200, 250);
    setMaximumSize(200, 250);
    
    // Create progress bar
    mProgressBar = new QProgressBar(this);
    mProgressBar->setGeometry(10, 190, 130, 3);
    mProgressBar->setMinimum(0);
    mProgressBar->setMaximum(200);
    mProgressBar->setValue(100);
}


void RadioDisplay::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    // Enable Anti-Aliasing
    p.setRenderHint(QPainter::Antialiasing, true);

    // Custom Colours & Font
    QColor lightBlue(84, 215, 219);
    QColor darkBg(38, 38, 38);
    QFont infoFont("Roboto Mono", 20);
    QFont smallFont("Roboto Mono", 15);
    QFont microFont("Roboto Mono", 10);

    // Top Rectangle (Mode)
    QRectF modeBox(2, 2, 146, 46);
    p.setPen(QPen(lightBlue, 3));
    p.setBrush(darkBg);
    p.drawRoundedRect(modeBox, 25, 25);

    // Set the Mode
    p.setFont(infoFont);
    p.setPen(Qt::white);
    p.drawText(modeBox, Qt::AlignCenter, "Eco Mode");

    // Middle Rectangle (Time)
    QRectF timeBox(2, 62, 146, 46);
    p.setPen(QPen(lightBlue, 3));
    p.setBrush(darkBg);
    p.drawRoundedRect(timeBox, 25, 25);

    // Set the Time
    p.setPen(Qt::white);
    QTime currentTime = QTime::currentTime();
    p.drawText(timeBox, Qt::AlignCenter, currentTime.toString("hh:mm"));

    // Bottom Rectangle (Radio)
    QRectF radioBox(2, 122, 146, 122);
    p.setPen(QPen(lightBlue, 3));
    p.setBrush(darkBg);
    p.drawRoundedRect(radioBox, 25, 25);

    // Radio Area
    infoFont.setUnderline(true);
    p.setFont(infoFont);
    p.setPen(Qt::white);
    p.drawText(2,82,146,122, Qt::AlignCenter, "PLAYING");
    p.setFont(smallFont);
    p.drawText(2,110,146,122, Qt::AlignCenter, "[INSERT NAME]");
    p.setFont(microFont);
    p.drawText(10,197,146,122, Qt::AlignLeft, "1:00");
    p.drawText(-5,197,146,122, Qt::AlignRight, "-1:00");
    p.drawText(2,172,146,122, Qt::AlignCenter, "----- SPOTIFY -----");
}
