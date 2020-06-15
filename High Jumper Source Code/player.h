#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QPropertyAnimation>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>

class Player : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal y READ y WRITE setY)
    Q_PROPERTY(qreal x READ x WRITE setX)

    qreal m_y;
    qreal m_x;


public:
    Player(QGraphicsItem *parent=0);
    qreal y() const;
    qreal x() const;
    void shootUp();
    void goLeft();
    void goRight();
    void stopXAnimation();
    void stopYAnimation();

    bool getIsFalling() const;
    bool getIsJumping() const;

    int getWidth() const;
    int getHeight() const;
    bool getCanJump() const;
    void setCanJump(bool value);
    void addPoint();

    int getPoints() const;

public slots:
    void setY(qreal y);
    void fallToGroundIfNecessery();
    void setX(qreal x);

private:
    int width;
    int height;
    int maxX;
    int minX;
    bool isFalling = false;
    bool canJump = true;
    int points;

    bool collideDetection();

    QGraphicsPixmapItem * player;

    QPropertyAnimation * yAnimation;
    QPropertyAnimation * xAnimation;

    qreal groundPosition;

signals:
    void gameOver();
};

#endif // PLAYER_H
