#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <iostream>
#include <fstream>
#include <QtWidgets>
#include <QDebug>
#include <QString>
#include <string>
#include <iostream>
#include <QColor>
#include <ctime>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void clearGUIinputs();

    void clearErrorStatus();

    void on_fileNameButton_clicked();

    bool invalidChar2(std::string input3);

    bool check4neg(std::string input1);

    void clearPrintInputs(int b);

    void on_fireTypeSelector_currentIndexChanged(int index);

    void on_MarkingSelector_currentIndexChanged(int type);

    void on_AddFiringRangeButton_clicked();

    void on_AddMarkingRangeButton_clicked();

    bool CalculateTimelineErrors(int timelineType, std::string *inputs);

    void on_CalculateTimelineButton_clicked();

    bool isInt(std::string input);

    bool invalidChar(std::string input2);

    void on_clearButton_clicked();

    void ClearTimeline(int index);

    void on_clearButtonGuns_clicked();

    void on_RemoveRangeButton_clicked();

    void on_RemoveRangeButton_2Mark_clicked();

    void selectGun(int index);

    void on_Gun_1_button_clicked();

    void on_Gun_2_button_clicked();

    void on_Gun_3_button_clicked();

    void on_Gun_4_button_clicked();

    void on_Gun_5_button_clicked();

    void on_Gun_6_button_clicked();

    void on_RemoveSingleRange_clicked();

    void on_RemoveSingleMarking_clicked();

    void on_ClearTimeline1_clicked();

    void on_ClearTimeline2_clicked();

    void on_ClearTimeline3_clicked();

    void on_ClearTimeline4_clicked();

    void on_ClearTimeline5_clicked();

    void on_ClearTimeline6_clicked();

private:
    Ui::MainWindow *ui;

    int numFiringRangesAdded;
    int numMarkingRangesAdded;

};
#endif // MAINWINDOW_H
