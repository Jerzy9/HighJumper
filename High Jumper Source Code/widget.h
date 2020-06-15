#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include "scene.h"
#include "score.h"
#include "brick.h"
#include "player.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

signals:
    void Close();
    void showMenu();

public slots:

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    int getScore() const;
    void setScore(int value);

private:
    Ui::Widget *ui;

    Scene * scene;
    int score = 0;

};

#endif // WIDGET_H
