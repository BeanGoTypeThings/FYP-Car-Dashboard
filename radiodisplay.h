#ifndef RADIODISPLAY_H
#define RADIODISPLAY_H

#include <QWidget>
#include <QProgressBar>

class RadioDisplay : public QWidget
{
    Q_OBJECT
public:
    explicit RadioDisplay(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QProgressBar *mProgressBar;
};

#endif // RADIODISPLAY_H
