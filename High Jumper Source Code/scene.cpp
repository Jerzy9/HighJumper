#include "scene.h"
#include "mainwindow.h"

Scene::Scene(QObject *parent) : QGraphicsScene(parent)
{
    time = 900;                         //czas pomiedzy tworzeniem bricków

    //Gracz
    player = new Player();
    addItem(player);

    //Punkty
    score = new Score();
    addItem(score);

    //Koniec gry
    connect(player, &Player::gameOver, [=]()
    {
        // blokada ruchu
        gameON = false;
        player->stopYAnimation();

        setScoreFromScoreObject(score->getScore());     //przekazanie wyniku do widgetu
        emit (closeSceneWindow());
    });

    setUpBrickTimer();
}

//po upływie czasu timera,tworzy się nowy "Brick",
//Tutaj też jest umieszczony system kolizji
void Scene::setUpBrickTimer()
{
    brickTimer = new QTimer(this);
    //to się wywołuje po upływie czasu
    connect(brickTimer, &QTimer::timeout, [=]()
    {
        if(gameON)
        {
            Brick * brick = new Brick();

            connect(brick, &Brick::collideDetected, [=]()
            {
                //jeżli gracz spada
                if(player->getIsFalling())
                {
                    //i udeży w "Brick" swoją dolną częścią, to wtedy się na nim utrzymuje
                    if(player->y()+player->getHeight() < brick->y()+brick->getHeight())
                    {
                        player->fallToGroundIfNecessery();

                        //na "Bricku" można skakać
                        player->setCanJump(true);
                    }
                    //jeżeli udeży np. górną częścią to nic sie nie dzieje
                }
            });

        //dodajemy "Brick" do sceny
        addItem(brick);

        //dodawanie punktów
        score->increasePoints();
         }
    });

    brickTimer->start(time);
}

int Scene::getScoreFromScoreObject() const
{
    return scoreFromScoreObject;
}

void Scene::setScoreFromScoreObject(int value)
{
    scoreFromScoreObject = value;
}

// nasiśnięcie przycisku
void Scene::keyPressEvent(QKeyEvent *event)
{
    // skok, strzałka do góry
    if(event->key() == Qt::Key_Up)
    {
        player->shootUp();
    }

    //odświeżenie keyPressEvent
    QGraphicsScene::keyPressEvent(event);

    // strzałka w lewo
    if(gameON)
    {
        if(event->key() == Qt::Key_Left)
        {
            player->goLeft();
        }

        //strzałka w prawo
        QGraphicsScene::keyPressEvent(event);

        if(event->key() == Qt::Key_Right)
        {
            player->goRight();
        }
    }

    //odświeżenie keyPressEvent
    QGraphicsScene::keyPressEvent(event);
}

// opuszczenie przycisku
void Scene::keyReleaseEvent(QKeyEvent *event)
{
    //kończy animację jeżeli gracz przestanie przytrzymywać strzałki

    if(event->key() == Qt::Key_Left && event->key() != Qt::Key_Right)
    {
        player->stopXAnimation();
    }

    QGraphicsScene::keyReleaseEvent(event);

    if(event->key() == Qt::Key_Right && event->key() != Qt::Key_Left)
    {
        player->stopXAnimation();
    }

    QGraphicsScene::keyReleaseEvent(event);
}
