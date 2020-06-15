#include "score.h"

Score::Score(QGraphicsItem* parent):QGraphicsTextItem(parent)
{
    //Ustawienie początkowej wartości punktów oraz wyświetlenie jej na ekranie
    score = 0;    

    setPlainText(QString("Wynik: ") + QString::number(score)); // Score: 0
    setDefaultTextColor(Qt::blue);
    setFont(QFont("times", 16));
}

int Score::getScore() const
{
    return score;
}

void Score::setScore(int value)
{
    score = value;
}

//Pokazywanie wyniku na ekranie oraz liczenie punktów
void Score::increasePoints()
{
    score++;
    setPlainText(QString("Wynik: ") + QString::number(score));
}
