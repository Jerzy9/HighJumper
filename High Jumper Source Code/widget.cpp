#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget)
{
    //ui to jest kreator widoku (view)
    ui->setupUi(this);

    //scene
    scene = new Scene(this);
    scene->setSceneRect(0,0,490,690);

    //nazwa okna
    this->setWindowTitle("High Jumper");

    //połaczenie widoku ze sceną (to znaczy że mają takie same wymiary)
    ui->graphicsView->setScene(scene);

    this->close();

    connect(scene, &Scene::closeSceneWindow, [=]()
    {
        setScore(scene->getScoreFromScoreObject());
        emit showMenu();
        this->close();
    });
}

Widget::~Widget()
{
    delete ui;
}

int Widget::getScore() const
{
    return score;
}

void Widget::setScore(int value)
{
    score = value;
}
