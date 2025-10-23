#ifndef FUELEFFICIENCYMETER_H
#define FUELEFFICIENCYMETER_H

#include <QWidget>

class fuelefficiencymeter : public QWidget
{
    Q_OBJECT
public:
    explicit fuelefficiencymeter(QWidget *parent = nullptr);
    void setEfficiency(int efficiency);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int m_efficiency;
    int m_minEfficiency;
    int m_maxEfficiency;
};

#endif // FUELEFFICIENCYMETER_H
