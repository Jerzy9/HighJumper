#include "brick.h"
#include "player.h"
#include "scene.h"

Brick::Brick()
{
    width = 100;                            //szerekość
    height = 15;                            //wysokość

    //wstawienie obiektu "Brick" z grafiką
    setPixmap(QPixmap(":/images/brickImg.png"));

    //losowy x
    xPos = QRandomGenerator::global()->bounded(490-width);
    int yPos = 10;

    //rozpoczęcie yAnimation dla "Brick", czyli opadanie
    yAnimation = new QPropertyAnimation(this,"y",this);
    yAnimation->setStartValue(yPos);
    yAnimation->setEndValue(700);
    yAnimation->setEasingCurve(QEasingCurve::Linear);
    yAnimation->setDuration(6000);

    //usunięcie elementu po zakończeniu animacji (czyli moment przekroczenia dolnej granicy planszy)
    connect(yAnimation, &QPropertyAnimation::finished, [=]() {
        delete this;
    });

    yAnimation->start();
}

//destruktor wyłowywany gdy "Brick" przekroczy dolną granice planszy
Brick::~Brick() { }

//getters
qreal Brick::y() const
{
    return m_y;
}

int Brick::getHeight() const
{
    return height;
}

int Brick::getWidth() const
{
    return width;
}

//setters
void Brick::setY(qreal y)
{
    m_y = y;

    //jeżeli nastąpiła kolizja, to wysyłany jest sygnał do Sceny
    if(collidesWithPlayer()) {
        emit collideDetected();
    }
    setPos(QPointF(0,0)+QPointF(xPos,y));

}

// funkcja zbiera wszystkie "Bricki" i wkłada je do listy
// sprawdza każdy element w liście czy da sie go "scastować" na obiekt "Player",
// jesli tak, to znaczy, że nastapiła kolizja Gracza z "Brickiem" i zwraca true,
// jeśli nie, zwraca false
bool Brick::collidesWithPlayer()
{
    QList<QGraphicsItem*> collidingItems = this->collidingItems();

    foreach (QGraphicsItem* item, collidingItems) {

        Player * player = dynamic_cast<Player*>(item);
        if(player) {
            return true;
        }
    }
    return false;
}
