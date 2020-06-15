#ifndef SCENE_H
#define SCENE_H

#include <brick.h>
#include <QTimer>
#include <QObject>
#include <QKeyEvent>
#include <QDebug>
#include "player.h"
#include "score.h"
#include "brick.h"


class Scene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit Scene(QObject *parent = nullptr);
    int getScoreFromScoreObject() const;
    void setScoreFromScoreObject(int value);

signals:
    void closeSceneWindow();

public slots:

private:
    bool gameON = true;
    void setUpBrickTimer();
    //void collisionDetection();
    //QList<QGraphicsItem*> brickList;
    QTimer * brickTimer;
    //QTimer * collisionTimer;
    Player * player;
    Score * score;
    int time=900;

    int scoreFromScoreObject;

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

};

#endif // SCENE_H
