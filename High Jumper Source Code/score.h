#ifndef SCORE_H
#define SCORE_H

#include <QObject>
#include <QGraphicsTextItem>
#include <QFont>

class Score :public QGraphicsTextItem
{
public:
    //QGraphicsItem* parent = 0
    Score(QGraphicsItem* parent = 0);
    int getScore() const;
    void setScore(int value);
    void increasePoints();

private:
    int score;
};

#endif // SCORE_H
