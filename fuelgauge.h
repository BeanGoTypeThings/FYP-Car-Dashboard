#ifndef FUELGAUGE_H
#define FUELGAUGE_H

#include <QWidget>

class fuelgauge : public QWidget
{
    Q_OBJECT
public:
    explicit fuelgauge(QWidget *parent = nullptr);
    void setSpeed(int speed);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int m_speed;
    int m_minSpeed;
    int m_maxSpeed;
};

#endif // SPEEDOMETER_H
