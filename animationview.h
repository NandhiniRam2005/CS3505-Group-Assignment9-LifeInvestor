#ifndef ANIMATIONVIEW_H
#define ANIMATIONVIEW_H

#include <QWidget>
#include <QTimer>
#include <QColor>
#include <QSize>
#include <QVector>
#include <Box2D/Box2D.h>

class Animation {
public:
    Animation(b2Body* body, QColor color, QSize size);
    ~Animation();
    b2Body* body;
    QColor color;
    QSize size;
};

class AnimationView : public QWidget
{
    Q_OBJECT

public:
    explicit AnimationView(QWidget *parent = nullptr);
    void startConfettiAnimation();
    void startRainAnimation();
    void stopConfettiAnimation();
    void stopRainAnimation();

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    b2World world;
    QTimer* timer;
    QVector<Animation*> confettiList;
    QVector<Animation*> rainList;
    double scale;

    void clearConfetti();
    void clearRain();
};

#endif // ANIMATIONVIEW_H
