////////////////////////////////////////////////////
//Twórcy:                                         //
//Szczepanik Maciej                               //
//Zbylut Konrad                                   //
//                                                //
//Data:                                           //
//rozpoczęcia: 25.05.2020                         //
//końca: 15.06.2020                               //
////////////////////////////////////////////////////


#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow * mainWindow = new MainWindow();
    mainWindow->show();
    return a.exec();
}
