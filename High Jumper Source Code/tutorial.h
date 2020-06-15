#ifndef TUTORIAL_H
#define TUTORIAL_H

#include <QWidget>

namespace Ui {
class Tutorial;
}

class Tutorial : public QWidget
{
    Q_OBJECT

signals:
    void Close();

public:
    explicit Tutorial(QWidget *parent = nullptr);
    ~Tutorial();

private slots:
    void on_MenuButton_clicked();

private:
    Ui::Tutorial *ui;
};

#endif // TUTORIAL_H
