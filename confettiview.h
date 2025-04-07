#ifndef CONFETTIVIEW_H
#define CONFETTIVIEW_H

#include <QWidget>
#include <QTimer>
#include <QColor>
#include <QSize>
#include <QVector>
#include <Box2D/Box2D.h>

class Confetti {
public:
    Confetti(b2Body* body, QColor color, QSize size);
    ~Confetti();
    b2Body *body;
    QColor color;
    QSize size;
};

class ConfettiView : public QWidget
{
    Q_OBJECT

public:
    explicit ConfettiView(QWidget *parent = nullptr);
    void startAnimation();
    void stopAnimation();

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    b2World world;
    QTimer* timer;
    QVector<Confetti*> confettiList;
    double scale;

    void clearConfetti();
};

#endif // CONFETTIVIEW_H
