#ifndef CARDASHBOARD_H
#define CARDASHBOARD_H

#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class CarDashboard;
}
QT_END_NAMESPACE

class CarDashboard : public QMainWindow
{
    Q_OBJECT

public:
    CarDashboard(QWidget *parent = nullptr);
    ~CarDashboard();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private slots:
    void updateProgressBar();

private:
    Ui::CarDashboard *ui;
    QTimer *timer;
    bool upArrowPressed;
    bool downArrowPressed;
    float currentSpeed;
    float currentFuel;
    int currentTorque;
};
#endif // CARDASHBOARD_H
