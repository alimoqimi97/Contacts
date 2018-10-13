#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.resize(500,250);


    //          Debugging           //

//    Contact  c("eden","hazard","9");
//    QString  gn = w.editwindow->GetContactGroupName(c);


//    w.editwindow->EditingMission();
    //          ----------          //

    w.show();

    return a.exec();
}
