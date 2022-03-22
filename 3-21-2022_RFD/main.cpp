#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(1337, 950); //set window size to allow more space for the timeline display
    w.show();
    return a.exec();
}
