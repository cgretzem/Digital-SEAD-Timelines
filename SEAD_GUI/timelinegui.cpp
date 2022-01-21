#include "timelinegui.h"
#include "ui_timelinegui.h"

TimelineGUI::TimelineGUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TimelineGUI)
{
    ui->setupUi(this);
}

TimelineGUI::~TimelineGUI()
{
    delete ui;
}

