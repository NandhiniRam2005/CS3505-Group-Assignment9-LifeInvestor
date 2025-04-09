#include "startscreenview.h"
#include <QPainter>
#include <QMouseEvent>
#include <QTimer>
#include <QPixmap>

StartScreenView::StartScreenView(QWidget *parent)
    : QWidget(parent), physicsTimer(new QTimer(this)), draggedBag(nullptr)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setMouseTracking(true);

    connect(physicsTimer, &QTimer::timeout, [this]() {
        if (world)
            world->Step(1.0f/60.0f, 6, 2);
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
    createMoneyBags();
    physicsTimer->start(16);
}

void StartScreenView::cleanupPhysics() {
    physicsTimer->stop();
    if (world) {
        for (b2Body* bag : moneyBags) {
            world->DestroyBody(bag);
        }
        moneyBags.clear();
        delete world;
        world = nullptr;
    }
    draggedBag = nullptr;
}

void StartScreenView::createBoundaries() {
    b2BodyDef boundaryDef;
    b2Body* boundaries = world->CreateBody(&boundaryDef);

    b2EdgeShape edge;
    float w = width() / scale;
    float h = height() / scale;

    // Left boundary
    edge.Set(b2Vec2(0,0), b2Vec2(0, h));
    boundaries->CreateFixture(&edge, 0);

    // Right boundary
    edge.Set(b2Vec2(w,0), b2Vec2(w, h));
    boundaries->CreateFixture(&edge, 0);

    // Bottom boundary
    edge.Set(b2Vec2(0, h), b2Vec2(w, h));
    boundaries->CreateFixture(&edge, 0);

    // Top boundary
    edge.Set(b2Vec2(0,0), b2Vec2(w, 0));
    boundaries->CreateFixture(&edge, 0);
}

void StartScreenView::createMoneyBags() {
    float centerX = width() / (2.0f * scale);
    float centerY = height() / (4.0f * scale);

    // Create three money bags and space them out horizontally.
    for (int i = 0; i < 3; ++i) {
        b2BodyDef bagDef;
        bagDef.type = b2_dynamicBody;
        bagDef.position.Set(centerX + (i - 1) * 2.5f, centerY);
        b2Body* bag = world->CreateBody(&bagDef);

        b2CircleShape circle;
        circle.m_radius = 1.0f;

        b2FixtureDef fixture;
        fixture.shape = &circle;
        fixture.density = 0.7f;
        fixture.restitution = 0.6f;
        bag->CreateFixture(&fixture);

        moneyBags.push_back(bag);
    }
}

void StartScreenView::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPixmap moneyBagPixmap(":/icons/icons/test.png");  // Ensure this image is listed in your .qrc file

    if (moneyBagPixmap.isNull()) {
        // Fallback: draw a simple ellipse if pixmap not found
        painter.setBrush(Qt::yellow);
        painter.setPen(Qt::darkYellow);
        for (b2Body* bag : moneyBags) {
            b2Vec2 pos = bag->GetPosition();
            float radius = 1.0f * scale;
            painter.drawEllipse(QPointF(pos.x * scale, pos.y * scale), radius, radius);
        }
    } else {
        // For each money bag, apply the rotation corresponding to the physics body's angle.
        for (b2Body* bag : moneyBags) {
            b2Vec2 pos = bag->GetPosition();
            float size = 2.0f * scale;
            float angle = bag->GetAngle() * (180.0f / b2_pi); // Convert radians to degrees

            // Save the current painter state
            painter.save();

            // Translate to the center of the money bag
            painter.translate(pos.x * scale, pos.y * scale);
            // Rotate the painter by the body's angle
            painter.rotate(angle);

            // Draw the money bag pixmap centered at the origin.
            QRect rect(-size/2, -size/2, size, size);
            painter.drawPixmap(rect, moneyBagPixmap);

            // Restore the painter's state for the next drawing operation.
            painter.restore();
        }
    }
}


void StartScreenView::mousePressEvent(QMouseEvent *event)
{
    // Convert the mouse position to physics coordinates.
    b2Vec2 mousePos(event->pos().x() / scale, event->pos().y() / scale);

    // Check each money bag to see if it was clicked.
    for (b2Body* bag : moneyBags) {
        if (bag->GetFixtureList() && bag->GetFixtureList()->TestPoint(mousePos)) {
            dragging = true;
            draggedBag = bag;
            draggedStart = mousePos;  // Record the drag start position.
            draggedBag->SetAwake(false);
            event->accept();
            return;
        }
    }
    event->ignore();
}

void StartScreenView::mouseMoveEvent(QMouseEvent *event)
{
    if (dragging && draggedBag) {
        b2Vec2 mousePos(event->pos().x() / scale, event->pos().y() / scale);
        draggedBag->SetTransform(mousePos, 0);
        event->accept();
    } else {
        event->ignore();
    }
}

void StartScreenView::mouseReleaseEvent(QMouseEvent *event)
{
    if (dragging && draggedBag) {
        dragging = false;
        draggedBag->SetAwake(true);
        b2Vec2 velocity = draggedBag->GetPosition() - draggedStart;
        draggedBag->SetLinearVelocity(8.0f * velocity);
        draggedBag = nullptr;
        event->accept();
    } else {
        event->ignore();
    }
}

// Lifecycle management: When shown, hidden, or resized, update the physics world.
void StartScreenView::showEvent(QShowEvent *) { initializePhysics(); }
void StartScreenView::hideEvent(QHideEvent *) { cleanupPhysics(); }
void StartScreenView::resizeEvent(QResizeEvent *) { initializePhysics(); }
