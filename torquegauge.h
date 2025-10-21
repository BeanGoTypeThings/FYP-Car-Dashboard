#ifndef TORQUEGAUGE_H
#define TORQUEGAUGE_H

#include <QWidget>

class torquegauge : public QWidget
{
    Q_OBJECT
public:
    explicit torquegauge(QWidget *parent = nullptr);
    void setTorque(int torque);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int m_torque;
    int m_minTorque;
    int m_maxTorque;
};
#endif // TORQUEGAUGE_H
