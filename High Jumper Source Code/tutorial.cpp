#include "tutorial.h"
#include "ui_tutorial.h"

Tutorial::Tutorial(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tutorial)
{
    ui->setupUi(this);

    //nazwa okna
    this->setWindowTitle("High Jumper: Jak Grać?");
}

Tutorial::~Tutorial()
{
    delete ui;
}

//akcja przycisku - powrót do menu
void Tutorial::on_MenuButton_clicked()
{
    this->close();
    emit Close();
}
