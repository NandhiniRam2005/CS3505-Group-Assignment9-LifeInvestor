/*
The header file for animationView.

These classes are responsible for rendering and managing
confetti and rain animations using the Box2D physics engine.

By Joel Rodriguez, Jacob Anderson,
Adharsh Ramakrishnan, Nandhini Ramanathan
Jake Heairld & Joseph Hamilton

April 22, 2025
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

    /**
     * Starts confetti animation with confetti with Box 2D and initiating the timer.
     */
    void startConfettiAnimation();

    /**
     * Starts confetti animation with rain with Box 2D and initiating the timer.
     */
    void startRainAnimation();

    /**
     * Stops confetti animation with confetti with Box 2D and initiating the timer.
     */
    void stopConfettiAnimation();

    /**
     * Stops confetti animation with rain with Box 2D and initiating the timer.
     */
    void stopRainAnimation();

protected:
    /**
     * Handles the paint event and renders all current animation objects.
     * @param event - The paint event triggered by Qt.
     */
    void paintEvent(QPaintEvent *event) override;

private:
    b2World world;
    QTimer *timer;
    QVector<Animation *> confettiList;
    QVector<Animation *> rainList;
    double scale;

    /**
     * Clears all confetti elements from the Box2D view.
     */
    void clearConfetti();

    /**
     * Clears all rain elements from the Box2D view.
     */
    void clearRain();
};

#endif
