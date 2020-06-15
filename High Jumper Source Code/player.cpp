#include "player.h"


Player::Player(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    width = 50;                                 //szerekość gracza
    height = 50;                                //wysokość gracza
    minX = -10;                                 //granica z lewej strony planszy
    maxX = 450;                                 //granica z prawej strony planszy
    groundPosition = 645;                       //granica dolna planszy

    //wstawienie obiektu "Player" z grafiką
    setPixmap(QPixmap(":/images/playerImg.png"));

    //tworzenie xAnimation
    xAnimation = new QPropertyAnimation(this, "x", this);
    xAnimation->setStartValue(pixmap());
    xAnimation->setEndValue(1);
    xAnimation->setEasingCurve(QEasingCurve::InQuad);
    xAnimation->setDuration(1000);

    //tworzenie yAnimacje
    yAnimation = new QPropertyAnimation(this, "y", this);
    yAnimation->setStartValue(pixmap());
    yAnimation->setEndValue(groundPosition+this->height);
    yAnimation->setEasingCurve(QEasingCurve::Linear);
    yAnimation->setDuration(10000);

    //gdy skończy się skok, rozpoczyna się opadanie
    connect(yAnimation, &QPropertyAnimation::finished, [=](){
        fallToGroundIfNecessery();
    });

    //rozpoczęcie animacji
    yAnimation->start();
    isFalling = true;                           //zmienna potrzebna do kolizji
    xAnimation->start();

}

//getters
qreal Player::y() const
{
    return m_y;
}

qreal Player::x() const
{
    return m_x;
}

int Player::getHeight() const
{
    return height;
}

int Player::getWidth() const
{
    return width;
}

bool Player::getIsFalling() const
{
    return isFalling;
}

//setters
void Player::setY(qreal y)
{
    m_y = y;
    setPos(QPointF(0,0)+QPointF(x(),y));
    if(y > groundPosition+30)
    {
        emit gameOver();
    }
}

void Player::setX(qreal x)
{
    if(x<maxX && x>minX)
    {
        m_x = x;
        setPos(QPointF(0,0)+QPointF(x,y()));
    }
}

int Player::getPoints() const
{
    return points;
}

bool Player::getCanJump() const
{
    return canJump;
}

void Player::setCanJump(bool value)
{
    canJump = value;
}

//odpowiada za opadanie po skoku
void Player::fallToGroundIfNecessery()
{
   //aż nie dotknie dolnej krawędzi planszy
   if(y() < groundPosition)
   {
       yAnimation->stop();
       yAnimation->setStartValue(y());
       yAnimation->setEndValue(y()+700);                    //gracz zawsze spada 700px w dół, żeby prędkość opadania była na każdej wysokości taka sama
       yAnimation->setEasingCurve(QEasingCurve::Linear);
       yAnimation->setDuration(2500);
       yAnimation->start();
       isFalling = true;

       //canJump musi mieć wartość "false", w przeciwnym wypadku możnaby skakać bez końca
       canJump = false;
   }
}

//odpowiada za skok gracza
void Player::shootUp()
{
    //450px jest trochę nad górną krawędzią planszy, gracz może wylecieć nad granice, żeby wszystko wyglądało naturalnie
    if(y()> -450 && canJump)
    {
        //zatrzymanie opadania
        yAnimation->stop();

        qreal curPosY = y();

        yAnimation->setStartValue(curPosY);
        yAnimation->setEndValue(curPosY - scene()->sceneRect().height()/8);
        yAnimation->setEasingCurve(QEasingCurve::OutQuad);
        yAnimation->setDuration(400);

        yAnimation->start();
        isFalling = false;

        //blokada na nieskończone skoki, ustawiamy tę zmienną na false po jednym skoku
        canJump = false;
    }
}

//odpowiada za ruch w lewą stronę
void Player::goLeft()
{
    //nie dalej, niż lewa granica planszy
    if(x()>minX)
    {
        xAnimation->stop();

        qreal curPosX = this->x();

        xAnimation->setStartValue(curPosX);
        xAnimation->setEndValue(curPosX-500);
        xAnimation->setEasingCurve(QEasingCurve::Linear);
        xAnimation->setDuration(1500);

        xAnimation->start();
    }
}

//odpowiada za ruch w prawą stronę
void Player::goRight()
{
    //nie dalej, niż prawa granica planszy
    if(x()<maxX)
    {
        xAnimation->stop();

        qreal curPosX = this->x();

        xAnimation->setStartValue(curPosX);
        xAnimation->setEndValue(curPosX+500);
        xAnimation->setEasingCurve(QEasingCurve::Linear);
        xAnimation->setDuration(1500);

        xAnimation->start();
    }
}

//zatrzymuje ruch w prawo i lewo
void Player::stopXAnimation()
{
    xAnimation->stop();
}

//zatrzymuje opadanie i skok, wykorzystywane do zatrzymania opadania po kolizji z "Brickiem"
void Player::stopYAnimation()
{
    yAnimation->stop();
}
