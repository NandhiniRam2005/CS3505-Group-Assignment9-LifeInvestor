/*
The header file for StartScreenView.

This class represents the start screen of the application, including interactive
money bag physics elements using the Box2D engine. It handles user interaction,
physics simulation, and rendering.

By Joel Rodriguez, Jacob Anderson,
Adharsh Ramakrishnan, Nandhini Ramanathan,
Jake Heairld, Joseph Hamilton

Reviewed by Nandhini Ramanathan

April 22, 2025
*/

#ifndef STARTSCREENVIEW_H
#define STARTSCREENVIEW_H

#include <QWidget>
#include <Box2D/Box2D.h>

class StartScreenView : public QWidget {
    Q_OBJECT

public:
    /**
     * Constructs a StartScreenView widget.
     * @param parent - The parent widget
     */
    explicit StartScreenView(QWidget *parent = nullptr);

    /**
     * Destructor for StartScreenView.
     */
    ~StartScreenView();

protected:
    /**
     * Handles paint events to draw the screen.
     * @param event - The paint event triggered by Qt.
     */
    void paintEvent(QPaintEvent *) override;

    /**
     * Handles mouse press events when dragging
     * @param event - The mouse press event.
     */
    void mousePressEvent(QMouseEvent *event) override;

    /**
     * Handles mouse move events to update the position of a dragged money bag.
     * @param event - The mouse move event.
     */
    void mouseMoveEvent(QMouseEvent *event) override;

    /**
     * Handles mouse release events to drop the dragged money bag.
     * @param event - The mouse release event.
     */
    void mouseReleaseEvent(QMouseEvent *event) override;

    /**
     * Called when the widget is shown. Starts the physics simulation.
     * @param event - The show event.
     */
    void showEvent(QShowEvent *) override;

    /**
     * Called when the widget is hidden. Stops the physics simulation.
     * @param event - The hide event.
     */
    void hideEvent(QHideEvent *) override;

    /**
     * Handles resize events and updates physics boundaries accordingly.
     * @param event - The resize event.
     */
    void resizeEvent(QResizeEvent *) override;

private:
    /**
     * Initializes the Box2D physics world and its settings.
     */
    void initializePhysics();

    /**
     * Cleans up and deletes all physics objects and the world.
     */
    void cleanupPhysics();

    /**
     * Creates the boundary walls within the Box2D world to contain objects.
     */
    void createBoundaries();

    /**
     * Creates money bags with Box2D.
     */
    void createMoneyBags();

    b2World *world = nullptr;
    std::vector<b2Body*> moneyBags;
    QTimer *physicsTimer = nullptr;

    bool dragging = false;
    b2Body *draggedBag = nullptr;
    b2Vec2 lastDragPos;
    b2Vec2 prevDragPos;

    const float scale = 30.0f;
};

#endif
