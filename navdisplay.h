#ifndef NAVDISPLAY_H
#define NAVDISPLAY_H

#include <QWidget>
#include <QTimer>

class NavDisplay : public QWidget
{
    Q_OBJECT
public:
    explicit NavDisplay(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void updateArrow();

private:
    void drawArrow(QPainter &p, const QPointF &center, double rotation);
    
    int mCurrentArrowDirection; // 0=straight, 1=left, 2=right
    QTimer *mArrowTimer;
    double mDistanceToTurn;
};

#endif // NAVDISPLAY_H
