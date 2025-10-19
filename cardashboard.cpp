#include "cardashboard.h"
#include "speedometer.h"
#include "ui_cardashboard.h"
#include <QKeyEvent>

CarDashboard::CarDashboard(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CarDashboard)
    , upArrowPressed(false)
    , downArrowPressed(false)
    , currentSpeed(0)
    , currentFuel(100)
{
    ui->setupUi(this);
    
    // Timer (updates every 10ms)
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &CarDashboard::updateProgressBar);
    timer->start(10);
}

CarDashboard::~CarDashboard()
{
    delete ui;
}

void CarDashboard::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Up) {
        upArrowPressed = true;
    }
    else if (event->key() == Qt::Key_Down) {
        downArrowPressed = true;
    }
    QMainWindow::keyPressEvent(event);
}

void CarDashboard::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Up) {
        upArrowPressed = false;
    }
    else if (event->key() == Qt::Key_Down) {
        downArrowPressed = false;
    }
    QMainWindow::keyReleaseEvent(event);
}

// This functionality will be updated when pedals are introduced
void CarDashboard::updateProgressBar()
{
    // If UP ARROW pressed, increase speed
    if (upArrowPressed) {
        currentSpeed += 1;
        if (currentSpeed > 160) {
            currentSpeed = 160;
        }

        // Slowly decrease fuel if driving
        currentFuel -= 0.005;
    }
    // If DOWN ARROW pressed, decrease speed
    else if (downArrowPressed) {
        currentSpeed -= 2;
        if (currentSpeed < 0) {
            currentSpeed = 0;
        }
    }
    // If nothing pressed, slowly decrease speed
    else {
        currentSpeed -= 1;
        if (currentSpeed < 0) {
            currentSpeed = 0;
        }
    }

    ui->fuelBar->setValue(currentFuel);
    ui->fuelValue->setText(QString::number(currentFuel) + " %");
    ui->speedometerWidget->setSpeed(currentSpeed);
}

