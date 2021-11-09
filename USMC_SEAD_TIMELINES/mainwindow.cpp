#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <QDebug>
#include <string>
#include <iostream>
#include <QColor>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //add fire type items into fire selector combo box
    ui->fireTypeSelector->addItem("Continuous");
    ui->fireTypeSelector->addItem("Interruped");
    ui->fireTypeSelector->addItem("Non-Standard");

    //add marking round types into marking round selector
    ui->MarkingSelector->addItem("Negative");
    ui->MarkingSelector->addItem("Illum");
    ui->MarkingSelector->addItem("WP");

    //hide all elements initially
    ui->FireFreqLabel->hide();
    ui->FiringRangesLabel->hide();
    ui->input_4->hide();
    ui->AddFiringRangeButton->hide();
    ui->FiringRangesDisplay->hide();
    ui->TOTLabel->hide();
    ui->TOFLabel->hide();
    ui->CalculateTimelineButton->hide();
    ui->MarkingTypeLabel->hide();
    ui->MarkingTOFLabel->hide();
    ui->input_5->hide();
    ui->input_1->hide();
    ui->input_2->hide();
    ui->input_3->hide();
    ui->input_5->hide();
    ui->MarkingSelector->hide();
    ui->TimelineDisplay->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//event handler for when the fire type has been changed
void MainWindow::on_fireTypeSelector_currentIndexChanged(int index)
{
    //show all common items
    ui->TOTLabel->show();
    ui->TOFLabel->show();
    ui->CalculateTimelineButton->show();
    ui->input_1->show();
    ui->input_2->show();
    ui->input_3->show();
    ui->TimelineDisplay->show();

    //input_4 is used for non-standard, input_5 is a longer text box for standard firing
    switch(index){
        //setup continuous and interrupted SEAD layouts
        case 0: case 1:
            //first clear all relevant input fields
            ui->input_1->clear();
            ui->input_2->clear();
            ui->input_3->clear();
            ui->input_5->clear();
            ui->TimelineDisplay->clear();

            //hide all non-standard elements
            ui->FireFreqLabel->hide();
            ui->FiringRangesLabel->hide();
            ui->input_4->hide();
            ui->AddFiringRangeButton->hide();
            ui->FiringRangesDisplay->hide();

            //show all standard elements
            ui->MarkingTypeLabel->show();
            ui->MarkingTOFLabel->show();
            ui->input_5->show();
            ui->MarkingSelector->show();

            //reset marking selector
            ui->MarkingSelector->setCurrentIndex(-1);

            break;

        //setup non-standard SEAD layout
        case 2:
            //first clear all relevant input fields
            ui->input_1->clear();
            ui->input_2->clear();
            ui->input_3->clear();
            ui->input_4->clear();
            ui->TimelineDisplay->clear();

            //hide all standard elements
            ui->MarkingTypeLabel->hide();
            ui->MarkingTOFLabel->hide();
            ui->input_3->hide();
            ui->input_5->hide();
            ui->MarkingSelector->hide();

            //show all non-standard elements
            ui->FireFreqLabel->show();
            ui->FiringRangesLabel->show();
            ui->input_3->show();
            ui->input_4->show();
            ui->AddFiringRangeButton->show();
            ui->FiringRangesDisplay->show();

            //set intial text for firing range display
            ui->FiringRangesDisplay->setText("Firing Ranges:");
            break;
    }
}

//event handler for when the user clicks on the add firing range button
void MainWindow::on_AddFiringRangeButton_clicked()
{
    ui->TimelineDisplay->clear();   //clear timeline display
    string input_4 = ui->input_4->text().toStdString(); //convert text in textbox to string

    if(isInt(input_4)){ //verify that the value to be inputted is an int
        ui->FiringRangesDisplay->setText(ui->FiringRangesDisplay->toPlainText() + "\n - " + ui->input_4->text());
        ui->input_4->clear();   //firing range inputted, clear the text box
    }
    else{
        ui->TimelineDisplay->setTextColor(Qt::red);
        ui->TimelineDisplay->setText(ui->TimelineDisplay->toPlainText() + "Firing range is not a whole number\n");
    }
}

//event handler for when the calculate timeline button is clicked
//must either display a valid timeline, or return an error message
void MainWindow::on_CalculateTimelineButton_clicked()
{
    //first clear all text
    ui->TimelineDisplay->clear();

    bool errorOccured = false;

    //we must first determine which firing mode is selected, so we can do input verification on the correct input boxes
    switch(ui->fireTypeSelector->currentIndex()){
        //continuous and interrupted (standard)
        //verify <input_1> <input_2> <MarkingSelector> <input_5>
        case 0: case 1:{
            //convert all inputs to strings
            string input_1 = ui->input_1->text().toStdString();
            string input_2 = ui->input_2->text().toStdString();
            string input_5 = ui->input_5->text().toStdString();

            //verify each input for empty value, or non-int value
            ui->TimelineDisplay->setTextColor(Qt::red); //set text color to red in case we need to output errors
            if(!isInt(input_1)){
                errorOccured = true;
                ui->TimelineDisplay->setText(ui->TimelineDisplay->toPlainText() + "TOT is not a whole number\n");
            }
            if(!isInt(input_2)){
                errorOccured = true;
                ui->TimelineDisplay->setText(ui->TimelineDisplay->toPlainText() + "TOF is not a whole number\n");
            }
            if(!isInt(input_5)){
                errorOccured = true;
                ui->TimelineDisplay->setText(ui->TimelineDisplay->toPlainText() + "Marking TOF is not a whole number\n");
            }
            if(ui->MarkingSelector->currentIndex() == -1){
                errorOccured = true;
                ui->TimelineDisplay->setText(ui->TimelineDisplay->toPlainText() + "Marking shell is not selected\n");
            }
            if(!errorOccured){
                ui->TimelineDisplay->setTextColor(Qt::black);   //errors have been printed, set text color back to black
                ui->TimelineDisplay->setText(ui->TimelineDisplay->toPlainText() + "example timeline\n");
            }

            break;
        }

        //non-standard, needs to verify <input_1> <input_2> <input_3>
        //<input_4> is verified as the add button is clicked
        case 2:
            //convert all inputs to strings
            string input_1 = ui->input_1->text().toStdString();
            string input_2 = ui->input_2->text().toStdString();
            string input_3 = ui->input_3->text().toStdString();

            //verify each input for empty value, or non-int value
            ui->TimelineDisplay->setTextColor(Qt::red); //set text color to red in case we need to output errors
            if(!isInt(input_1)){
                errorOccured = true;
                ui->TimelineDisplay->setText(ui->TimelineDisplay->toPlainText() + "TOT is not a whole number\n");
            }
            if(!isInt(input_2)){
                errorOccured = true;
                ui->TimelineDisplay->setText(ui->TimelineDisplay->toPlainText() + "TOF is not a whole number\n");
            }
            if(!isInt(input_3)){
                errorOccured = true;
                ui->TimelineDisplay->setText(ui->TimelineDisplay->toPlainText() + "Firing Freq is not a whole number\n");
            }
            if(!errorOccured){
                ui->TimelineDisplay->setTextColor(Qt::black);   //errors have been printed, set text color back to black
                ui->TimelineDisplay->setText(ui->TimelineDisplay->toPlainText() + "example timeline\n");
            }

            break;
    }
}

bool MainWindow::isInt(string input){
    if(input.empty()){  //check for empty input
        return false;
    }
    for(char const c : input){
        if(!isdigit(c)){   //check if this char is a digit
            return false;
        }
    }
    return true;
}
