#ifndef TIMELINEGUI_H
#define TIMELINEGUI_H

#include "timeline.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class TimelineGUI; }
QT_END_NAMESPACE

class TimelineGUI : public QMainWindow
{
    Q_OBJECT

public:
    TimelineGUI(QWidget *parent = nullptr);
    ~TimelineGUI();

private:
    Ui::TimelineGUI *ui;
};
#endif // TIMELINEGUI_H
