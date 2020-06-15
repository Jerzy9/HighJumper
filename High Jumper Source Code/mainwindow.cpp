#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "score.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->scoreLabel->setText("0");

    //nazwa okna
    this->setWindowTitle("High Jumper");
}

MainWindow::~MainWindow()
{
    delete ui;
}

//akcja przycisku - rozpoczyna rozgrywkę
void MainWindow::on_StartButton_clicked()
{
    WidgetPointer = new Widget;
    connect(WidgetPointer, &Widget::Close, this, &MainWindow::show);
    this->hide();
    WidgetPointer->show();

    connect(WidgetPointer, &Widget::showMenu, [=]() {
        setScore(WidgetPointer->getScore());
        ui->scoreLabel->setText(QString::number(score));
        WidgetPointer = new Widget;
        this->show();
    });
}

//akcja przycisku - pokazuje okno "Jak grać?"
void MainWindow::on_TutorialPushButton_clicked()
{
    TutorialPointer = new Tutorial;
    connect(TutorialPointer, &Tutorial::Close, this, &MainWindow::show);
    this->hide();
    TutorialPointer->show();
}

//akcja przycisku - zamyka aplikację
void MainWindow::on_ExitButton_clicked()
{
    MainWindow::close();
}

int MainWindow::getScore() const
{
    return score;
}

void MainWindow::setScore(int value)
{
    score = value;
}
