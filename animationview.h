/*
The header file for animationView.

These classes are responsible for rendering and managing
confetti and rain animations using the Box2D physics engine.

By Joel Rodriguez, Jacob Anderson,
Adharsh Ramakrishnan, Nandhini Ramanathan
Jake Heairld & Joseph Hamilton

April 15, 2025
*/

#ifndef ANIMATIONVIEW_H
#define ANIMATIONVIEW_H

#include <QColor>
#include <QSize>
#include <QTimer>
#include <QVector>
#include <QWidget>
#include <Box2D/Box2D.h>


/**
 * This class holds a Box2D body and its visual attributes such as color and size.
 */
class Animation
{
public:
    /**
     * Constructs an Animation object.
     * @param b2Body - Pointer to the Box2D body.
     * @param color - Color of the animation element.
     * @param size - Size of the animation element.
     */
    Animation(b2Body *body, QColor color, QSize size);

    /**
     * Destructor for Animation.
     */
    ~Animation();

    /**
     * The physical body in the Box2D world.
     */
    b2Body *body;

    /**
     * The color used to render the animation.
     */
    QColor color;

    /**
     * The size of teh animation.
     */
    QSize size;
};


/**
 * Uses a Box2D world and a QTimer to animate objects such as confetti and rain.
 */
class AnimationView : public QWidget
{
    Q_OBJECT

public:
    /**
     * Constructs the AnimationView widget.
     * @param parent - the Parent widget.
     */
    explicit AnimationView(QWidget *parent = nullptr);
    void startConfettiAnimation();
    void startRainAnimation();
    void stopConfettiAnimation();
    void stopRainAnimation();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    b2World world;
    QTimer *timer;
    QVector<Animation *> confettiList;
    QVector<Animation *> rainList;
    double scale;

    void clearConfetti();
    void clearRain();
};

#endif
