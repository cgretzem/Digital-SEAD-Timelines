#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <iostream>

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


    void on_fireTypeSelector_currentIndexChanged(int index);

    void on_MarkingSelector_currentIndexChanged(int type);

    void on_AddFiringRangeButton_clicked();

    void on_AddMarkingRangeButton_clicked();

    void on_CalculateTimelineButton_clicked();

    bool isInt(std::string input);

    void on_clearButton_clicked();

    void on_clearButtonGuns_clicked();

    void on_RemoveRangeButton_clicked();

    void on_RemoveRangeButton_2Mark_clicked();

    //void on_CopyGunButton_clicked();

    void on_Gun_1_button_clicked();

    void on_Gun_2_button_clicked();

    void on_Gun_3_button_clicked();

    void on_Gun_4_button_clicked();

    void on_Gun_5_button_clicked();

    void on_Gun_6_button_clicked();

    //void setNewData();

    //void on_input_2_textEdited(const QString &arg1);

    //void on_input_1_textEdited(const QString &arg1);

    //void on_input_5_textEdited(const QString &arg1);

    //void on_input_3_textEdited(const QString &arg1);

    //void on_MarkingSelector_currentIndexChanged(int index);

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
