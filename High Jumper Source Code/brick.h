#ifndef BRICK_H
#define BRICK_H

#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QObject>
#include <QRandomGenerator>
#include <QGraphicsScene>
#include <QDebug>

class Brick : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal y READ y WRITE setY)

public:
    explicit Brick();
    ~Brick();

    qreal y() const;
    int width;
    int height;
    int getWidth() const;
    int getHeight() const;

signals:
    void collideDetected();

public slots:
    void setY(qreal y);

private:
    bool collidesWithPlayer();

    QGraphicsRectItem * rect;
    QPropertyAnimation * yAnimation;
    int xPos;
    qreal m_y;
};

#endif // BRICK_H
