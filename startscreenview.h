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
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void showEvent(QShowEvent *event) override;
    void hideEvent(QHideEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    void initializePhysics();
    void cleanupPhysics();
    void createBoundaries();
    void createBall();

    b2World* world = nullptr;
    b2Body* ballBody = nullptr;
    QTimer* physicsTimer;
    const float scale = 20.0f;
    bool dragging = false;
    b2Vec2 dragStart;
};

#endif // STARTSCREENVIEW_H
