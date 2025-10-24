#ifndef INFODISPLAY_H
#define INFODISPLAY_H

#include <QWidget>

class InfoDisplay : public QWidget
{
    Q_OBJECT
public:
    explicit InfoDisplay(QWidget *parent = nullptr);
    void setMileage(double mileage);
    void setTemperature(double temperature);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    double mMileage;
    double mTemperature;
};

#endif // INFODISPLAY_H
