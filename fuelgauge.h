#ifndef FUELGAUGE_H
#define FUELGAUGE_H

#include <QWidget>
#include <QQuickWidget>

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
    QQuickWidget *m_fuelIcon;
};

#endif // SPEEDOMETER_H
