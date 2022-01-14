#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(1000,800); //set window size to allow more space for the timeline display
    w.show();
    return a.exec();
}
