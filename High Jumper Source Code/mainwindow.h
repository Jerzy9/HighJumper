#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "widget.h"
#include "tutorial.h"
#include <QLabel>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int getScore() const;
    void setScore(int value);

private slots:
    //sloty - akcje przycisków
    void on_StartButton_clicked();
    void on_TutorialPushButton_clicked();
    void on_ExitButton_clicked();

private:
    Ui::MainWindow *ui;

    //liczba punktów
    int score;

    //wskaźniki do okienek
    Widget *WidgetPointer;
    Tutorial *TutorialPointer;
};

#endif // MAINWINDOW_H
