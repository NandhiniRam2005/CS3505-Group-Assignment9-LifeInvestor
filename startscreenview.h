#ifndef STARTSCREENVIEW_H
#define STARTSCREENVIEW_H

#include <QWidget>
#include <Box2D/Box2D.h>

class StartScreenView : public QWidget {
    Q_OBJECT
public:
    explicit StartScreenView(QWidget *parent = nullptr);
    ~StartScreenView();

protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void showEvent(QShowEvent *) override;
    void hideEvent(QHideEvent *) override;
    void resizeEvent(QResizeEvent *) override;

private:
    void initializePhysics();
    void cleanupPhysics();
    void createBoundaries();
    void createMoneyBags();

    b2World *world = nullptr;
    std::vector<b2Body*> moneyBags;
    QTimer *physicsTimer = nullptr;

    // For dragging a money bag:
    bool dragging = false;
    b2Body *draggedBag = nullptr;
    b2Vec2 draggedStart;

    // Scale factor for physics to pixels conversion
    const float scale = 30.0f;
};

#endif // STARTSCREENVIEW_H
