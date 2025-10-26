#include "cardashboard.h"
#include "speedometer.h"
#include "ui_cardashboard.h"
#include <QKeyEvent>

CarDashboard::CarDashboard(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CarDashboard)
    , upArrowPressed(false)
    , downArrowPressed(false)
    , currentSpeed(0.0)
    , currentFuel(100)
    , totalMileage(0.0)
    , currentTemperature(20.0)
{
    ui->setupUi(this);
    
    // Timer (updates every 0.001s)
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
    else if (event->key() == Qt::Key_N) {
        // Toggle the navigation
        bool showNav = !ui->navDisplayWidget->isVisible();
        ui->navDisplayWidget->setVisible(showNav);
        ui->infoDisplayWidget->setVisible(!showNav);
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
    // Set the default gear (P)
    char newGear = 'P';
    
    // If UP ARROW pressed:
    if (upArrowPressed && (currentFuel != 0)) {
        // Increase Speed
        currentSpeed += 1;
        if (currentSpeed > 160) {
            currentSpeed = 160;
        }

        // Slowly Decrease Fuel
        currentFuel -= 0.05;
        if (currentFuel < 0) {
            currentFuel = 0;
        }

        // Slowly Increase Temperature
        currentTemperature += 0.02;
        if (currentTemperature > 110.0) {
            currentTemperature = 110.0;
        }
        
        // Set the accelerating gear (D)
        newGear = 'D';
    }
    // If DOWN ARROW pressed:
    else if (downArrowPressed && (currentFuel != 0)) {
        // Decrease Speed Rapidly (BRAKING)
        currentSpeed -= 2;
        if (currentSpeed < 0) {
            currentSpeed = 0;
        }
        
        // If not moving (R)
        // If moving, but not doing anything (N)
        newGear = (currentSpeed > 0.5) ? 'N' : 'R';
    }
    // If nothing is pressed:
    else {
        // Slowly Decrease Speed
        currentSpeed -= 0.25;
        if (currentSpeed < 0) {
            currentSpeed = 0;
        }

        // Decrease Temperature
        currentTemperature -= 0.01;
        if (currentTemperature < 20.0) {
            currentTemperature = 20.0;
        }
        
        // If not moving (P)
        // If moving, but not doing anything (N)
        newGear = (currentSpeed > 0.5) ? 'N' : 'P';
    }

    // Update Mileage (speed dependent)
    totalMileage += (currentSpeed * 0.01) / 3600.0;

    ui->speedometerWidget->setSpeed(currentSpeed);
    ui->infoDisplayWidget->setMileage(totalMileage);
    ui->infoDisplayWidget->setTemperature(currentTemperature);
    ui->fuelmeterWidget->setFuelLevel(currentFuel);
    ui->gearDisplayWidget->setGear(newGear);
}

