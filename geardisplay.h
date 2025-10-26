#ifndef GEARDISPLAY_H
#define GEARDISPLAY_H

#include <QWidget>

class GearDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit GearDisplay(QWidget *parent = nullptr);
    void setGear(char gear);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    char mCurrentGear = 'P';
};

#endif // GEARDISPLAY_H
