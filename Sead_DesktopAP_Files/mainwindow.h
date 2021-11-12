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

    void on_AddFiringRangeButton_clicked();

    void on_CalculateTimelineButton_clicked();

    bool isInt(std::string input);

private:
    Ui::MainWindow *ui;

    int numFiringRangesAdded;
};
#endif // MAINWINDOW_H
