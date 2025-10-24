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
    float mFuelLevel;
    QQuickWidget *mFuelIcon;
};

#endif // FUELMETER_H
