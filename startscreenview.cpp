#include "startscreenview.h"
#include <QPainter>
#include <QMouseEvent>
#include <QTimer>

StartScreenView::StartScreenView(QWidget *parent)
    : QWidget(parent), physicsTimer(new QTimer(this))
{
    setAttribute(Qt::WA_TranslucentBackground);
    setMouseTracking(true);

    connect(physicsTimer, &QTimer::timeout, [this]() {
        if(world) world->Step(1.0f/60.0f, 6, 2);
        update();
    });
}

StartScreenView::~StartScreenView() {
    cleanupPhysics();
}

void StartScreenView::initializePhysics() {
    cleanupPhysics();
    world = new b2World(b2Vec2(0.0f, 9.8f));
    createBoundaries();
    createBall();
    physicsTimer->start(16);
}

void StartScreenView::cleanupPhysics() {
    physicsTimer->stop();
    if(world) {
        delete world;
        world = nullptr;
    }
    ballBody = nullptr;
}

void StartScreenView::createBoundaries() {
    b2BodyDef boundaryDef;
    b2Body* boundaries = world->CreateBody(&boundaryDef);

    b2EdgeShape edge;
    float w = width()/scale;
    float h = height()/scale;

    edge.Set(b2Vec2(0,0), b2Vec2(0,h));  // Left
    boundaries->CreateFixture(&edge, 0);
    edge.Set(b2Vec2(w,0), b2Vec2(w,h));  // Right
    boundaries->CreateFixture(&edge, 0);
    edge.Set(b2Vec2(0,h), b2Vec2(w,h));  // Bottom
    boundaries->CreateFixture(&edge, 0);
}

void StartScreenView::createBall() {
    b2BodyDef ballDef;
    ballDef.type = b2_dynamicBody;
    ballDef.position.Set(width()/2/scale, 50/scale);
    ballBody = world->CreateBody(&ballDef);

    b2CircleShape circle;
    circle.m_radius = 1.0f;

    b2FixtureDef fixture;
    fixture.shape = &circle;
    fixture.density = 0.7f;
    fixture.restitution = 0.6f;
    ballBody->CreateFixture(&fixture);
}

void StartScreenView::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if(ballBody) {
        b2Vec2 pos = ballBody->GetPosition();
        float radius = 1.0f * scale;

        QRadialGradient grad(pos.x*scale, pos.y*scale, radius);
        grad.setColorAt(0, QColor(255, 215, 0));
        grad.setColorAt(1, QColor(184, 134, 11));

        painter.setBrush(grad);
        painter.setPen(Qt::darkYellow);
        painter.drawEllipse(QPointF(pos.x*scale, pos.y*scale), radius, radius);
    }
}

void StartScreenView::mousePressEvent(QMouseEvent *event)
{
    if(!ballBody) return;

    // Convert to physics coordinates
    b2Vec2 mousePos(event->pos().x()/scale, event->pos().y()/scale);

    if(ballBody->GetFixtureList()->TestPoint(mousePos)) {
        // Handle ball drag
        dragging = true;
        ballBody->SetAwake(false);
        dragStart = mousePos;
        event->accept();  // Mark event as handled
    } else {
        // Pass through other clicks
        event->ignore();
    }
}

void StartScreenView::mouseMoveEvent(QMouseEvent *event)
{
    if(dragging && ballBody) {
        b2Vec2 mousePos(event->pos().x()/scale, event->pos().y()/scale);
        ballBody->SetTransform(mousePos, 0);
        event->accept();
    } else {
        event->ignore();
    }
}

void StartScreenView::mouseReleaseEvent(QMouseEvent *event)
{
    if(dragging && ballBody) {
        dragging = false;
        ballBody->SetAwake(true);
        b2Vec2 velocity = ballBody->GetPosition() - dragStart;
        ballBody->SetLinearVelocity(8.0f * velocity);
        event->accept();
    } else {
        event->ignore();
    }
}

// Lifecycle management
void StartScreenView::showEvent(QShowEvent *) { initializePhysics(); }
void StartScreenView::hideEvent(QHideEvent *) { cleanupPhysics(); }
void StartScreenView::resizeEvent(QResizeEvent *) { initializePhysics(); }
