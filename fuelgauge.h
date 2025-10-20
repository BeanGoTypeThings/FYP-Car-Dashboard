#ifndef FUELGAUGE_H
#define FUELGAUGE_H

#include <QWidget>

class fuelgauge : public QWidget
{
    Q_OBJECT
public:
    explicit fuelgauge(QWidget *parent = nullptr);
    void setFuelLevel(float fuel);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    float m_fuelLevel;
};

#endif // SPEEDOMETER_H
