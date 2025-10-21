#ifndef FUELMETER_H
#define FUELMETER_H

#include <QWidget>
#include <QQuickWidget>

class fuelmeter : public QWidget
{
    Q_OBJECT
public:
    explicit fuelmeter(QWidget *parent = nullptr);
    void setFuelLevel(float fuel);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    float m_fuelLevel;
    QQuickWidget *m_fuelIcon;
};

#endif // FUELMETER_H
