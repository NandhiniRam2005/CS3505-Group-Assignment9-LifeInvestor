#include "confettiview.h"
#include <QPainter>
#include <QRandomGenerator>
#include <QTimer>

Confetti::Confetti(b2Body* body, QColor color, QSize size)
    : body(body), color(color), size(size) {}

Confetti::~Confetti() {
}

ConfettiView::ConfettiView(QWidget *parent)
    : QWidget(parent), world(b2Vec2(0.3f, 9.8f)), timer(new QTimer(this)), scale(20.0)
{
    setGeometry(parent->rect());

    connect(timer, &QTimer::timeout, this, [this]() {
        world.Step(1.0f / 60.0f, 4, 2);
        update();
    });

    hide();
}

void ConfettiView::startConfettiAnimation()
{
    stopConfettiAnimation();

    for (int i = 0; i < 50; ++i) {
        // Define the ground body.
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(QRandomGenerator::global()->bounded(width()) / scale, 0);

        // Call the body factory which allocates memory for the ground body from a pool and creates the ground box shape (also from a pool).
        b2Body *body = world.CreateBody(&bodyDef);

        float vx = -1.5f + QRandomGenerator::global()->generateDouble() * 3.0f; // Horizontal speed
        float vy = QRandomGenerator::global()->generateDouble();  // Small downward speed
        body->SetLinearVelocity(b2Vec2(vx, vy));

        // Define the ground box shape.
        b2PolygonShape shape;
        shape.SetAsBox(0.03f, 0.03f);

        // Define the dynamic body fixture.
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.3f;
        fixtureDef.restitution = 0.9f;

        body->CreateFixture(&fixtureDef);

        // Random color chooser for the confetti
        QRandomGenerator *generator = QRandomGenerator::global();
        int red = generator->bounded(256);
        int green = generator->bounded(256);
        int blue = generator->bounded(256);

        QColor color = QColor(red, green, blue);
        QSize size(5, 5);
        confettiList.push_back(new Confetti(body, color, size));
    }

    show();
    timer->start(16);

    QTimer::singleShot(3000, this, &ConfettiView::stopConfettiAnimation);
}

void ConfettiView::startRainAnimation()
{
    stopRainAnimation();

    for (int i = 0; i < 150; ++i) {
        // Define the ground body.
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(QRandomGenerator::global()->bounded(width()) / scale, 0);

        // Call the body factory which allocates memory for the ground body from a pool and creates the ground box shape (also from a pool).
        b2Body *body = world.CreateBody(&bodyDef);

        float vy = QRandomGenerator::global()->generateDouble() * 75;  // downward speed
        body->SetLinearVelocity(b2Vec2(0, vy));

        // Define the ground box shape.
        b2PolygonShape shape;
        shape.SetAsBox(0.0025f, 0.08f);

        // Define the dynamic body fixture.
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.05f;
        fixtureDef.restitution = 0.0f;

        body->CreateFixture(&fixtureDef);

        QColor color(0, 0, 255);  // Blue color for rain
        QSize size(1, 10);
        rainList.push_back(new Confetti(body, color, size));
    }

    show();
    timer->start(16);

    QTimer::singleShot(3000, this, &ConfettiView::stopRainAnimation);
}

void ConfettiView::stopConfettiAnimation()
{
    timer->stop();
    clearConfetti();
    hide();
}

void ConfettiView::stopRainAnimation()
{
    timer->stop();
    clearRain();
    hide();
}

void ConfettiView::clearConfetti()
{
    for (Confetti* confetti : confettiList) {
        world.DestroyBody(confetti->body);
        delete confetti;
    }
    confettiList.clear();
}

void ConfettiView::clearRain()
{
    for (Confetti* rainDrop : rainList) {
        world.DestroyBody(rainDrop->body);
        delete rainDrop;
    }
    rainList.clear();
}

void ConfettiView::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    for (Confetti* confetti : confettiList) {
        b2Vec2 pos = confetti->body->GetPosition();
        QPoint center(pos.x * scale, pos.y * scale);
        QRect rect(center.x(), center.y(), confetti->size.width(), confetti->size.height());
        painter.setBrush(confetti->color);
        painter.setPen(Qt::NoPen);
        painter.drawRect(rect);
    }

    for (Confetti* rain : rainList) {
        b2Vec2 pos = rain->body->GetPosition();
        QPoint center(pos.x * scale, pos.y * scale);
        QRect rect(center.x(), center.y(), rain->size.width(), rain->size.height());
        painter.setBrush(rain->color);
        painter.setPen(Qt::NoPen);
        painter.drawRect(rect);
    }
}


