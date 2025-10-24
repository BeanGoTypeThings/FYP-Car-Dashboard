#ifndef SPEEDOMETER_H
#define SPEEDOMETER_H

#include <QWidget>

class speedometer : public QWidget
{
    Q_OBJECT
public:
    explicit speedometer(QWidget *parent = nullptr);
    void setSpeed(int speed);
    void setFuel(int fuel);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int mSpeed;
    int mMinSpeed;
    int mMaxSpeed;
};

#endif // SPEEDOMETER_H
