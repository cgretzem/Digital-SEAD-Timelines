#include "timelinegui.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TimelineGUI w;
    w.show();
    return a.exec();
}
