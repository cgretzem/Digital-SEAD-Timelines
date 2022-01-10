#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <QDebug>
#include <QString>
#include <string>
#include <iostream>
#include <QColor>
#include <timeline.h>

using namespace std;

std::vector<fireRange> frVec;

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
    ui->CalculateTimelineButton->hide();
    ui->AddFiringRangeButton->hide();
    ui->FiringRangesLabel_2->hide();
    ui->FiringRangesDisplay->hide();
    ui->RemoveRangeButton->hide();
    ui->FiringRangesLabel->hide();
    ui->MarkingTypeLabel->hide();
    ui->MarkingTOFLabel->hide();
    ui->TimelineDisplay->hide();
    ui->MarkingSelector->hide();
    ui->FireFreqLabel->hide();
    ui->clearButton->hide();
    ui->TOTLabel->hide();
    ui->TOFLabel->hide();
    ui->input_1->hide();
    ui->input_2->hide();
    ui->input_3->hide();
    ui->input_5->hide();
    ui->input_6->hide();
    ui->input_7->hide();

    //initialize globals
    numFiringRangesAdded = 0;

    on_fireTypeSelector_currentIndexChanged(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//event handler for when the fire type has been changed
void MainWindow::on_fireTypeSelector_currentIndexChanged(int index)
{
    //show all common items
    ui->CalculateTimelineButton->show();
    ui->TimelineDisplay->show();
    ui->clearButton->show();
    ui->TOTLabel->show();
    ui->TOFLabel->show();
    ui->input_1->show();
    ui->input_2->show();
    ui->input_3->show();

    switch(index){
        //setup continuous and interrupted SEAD layouts
        case 0: case 1:
            //first clear all relevant input fields
            ui->TimelineDisplay->clear();
            ui->input_1->clear();
            ui->input_2->clear();
            ui->input_3->clear();
            ui->input_5->clear();

            //hide all non-standard elements
            ui->AddFiringRangeButton->hide();
            ui->FiringRangesDisplay->hide();
            ui->FiringRangesLabel_2->hide();
            ui->RemoveRangeButton->hide();
            ui->FiringRangesLabel->hide();
            ui->FireFreqLabel->hide();
            ui->input_3->hide();
            ui->input_6->hide();
            ui->input_7->hide();

            //show all standard elements
            ui->MarkingTypeLabel->show();
            ui->MarkingTOFLabel->show();
            ui->MarkingSelector->show();
            ui->input_5->show();

            //reset marking selector
            ui->MarkingSelector->setCurrentIndex(-1);

            break;

        //setup non-standard SEAD layout
        case 2:
            //first clear all relevant input fields
            ui->TimelineDisplay->clear();
            ui->input_1->clear();
            ui->input_2->clear();
            ui->input_3->clear();
            ui->input_5->clear();
            ui->input_6->clear();
            ui->input_7->clear();

            ui->MarkingTypeLabel->show();
            ui->MarkingTOFLabel->show();
            ui->MarkingSelector->show();
            ui->input_5->show();

            //show all non-standard elements
            ui->AddFiringRangeButton->show();
            ui->FiringRangesDisplay->show();
            ui->FiringRangesLabel_2->show();
            ui->RemoveRangeButton->show();
            ui->FiringRangesLabel->show();
            ui->FireFreqLabel->show();
            ui->input_3->show();
            ui->input_6->show();
            ui->input_7->show();

            //set intial text for firing range display
            ui->FiringRangesDisplay->setText("Firing Ranges:");

            ui->MarkingSelector->setCurrentIndex(-1);

            //reset firing ranges list
            numFiringRangesAdded = 0;

            break;
    }
}

//event handler for when the user clicks on the add firing range button
void MainWindow::on_AddFiringRangeButton_clicked()
{

    ui->TimelineDisplay->clear();   //clear timeline display
    string input_6 = ui->input_6->text().toStdString(); //convert text in textbox to string
    string input_7 = ui->input_7->text().toStdString();

    if(isInt(input_6) && isInt(input_7)){ //verify that the value to be inputted is an int

        ui->FiringRangesDisplay->setText(ui->FiringRangesDisplay->toPlainText() + "\n " + ui->input_6->text() + " to " + ui->input_7->text());

        frVec.push_back(fireRange{ stoi(input_6), stoi(input_7) });
        ui->input_6->clear();
        ui->input_7->clear();
        numFiringRangesAdded++;
    }
    else{
        ui->TimelineDisplay->setTextColor(Qt::red);
        ui->TimelineDisplay->setText(ui->TimelineDisplay->toPlainText() + "Firing range is not a whole number\n");
    }
}

//event handler for remove range button, removes the most recent firing range
void MainWindow::on_RemoveRangeButton_clicked()
{
    //remove the line from the firing ranges list, first check to see if the firing ranges is empty
    if(numFiringRangesAdded != 0){
        frVec.pop_back();
        numFiringRangesAdded--;

        string firingRangesText = ui->FiringRangesDisplay->toPlainText().toStdString();
        string newFiringRanges = firingRangesText.substr(0, firingRangesText.find_last_of("\n"));
        ui->FiringRangesDisplay->setText(QString::fromStdString(newFiringRanges));
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

                markingType mt = NEGATIVE;
                if(ui->MarkingSelector->currentIndex() == 1){ mt = ILLUM; }
                else if(ui->MarkingSelector->currentIndex() == 2){ mt = WP; }

                timelineType tt = CONTINUOUS;
                if(ui->fireTypeSelector->currentIndex() == 1){ tt = INTERRUPTED; }

                //cout << "Standard example 1" << endl;
                Standard_Timeline t0 = Standard_Timeline(stoi(input_1), stoi(input_2), mt, stoi(input_5), tt);
                string testLine = t0.print();
                char test[testLine.size()+1];
                testLine.copy(test,testLine.size()+1);
                test[testLine.size()] = '\0';

                QString x = test;

                ui->TimelineDisplay->setText(ui->TimelineDisplay->toPlainText() + x);
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
            if(!isInt(input_3)){
                errorOccured = true;
                ui->TimelineDisplay->setText(ui->TimelineDisplay->toPlainText() + "Firing Freq is not a whole number\n");
            }
            if(!isInt(input_5)){
                errorOccured = true;
                ui->TimelineDisplay->setText(ui->TimelineDisplay->toPlainText() + "Marking TOF is not a whole number\n");
            }
            if(ui->MarkingSelector->currentIndex() == -1){
                errorOccured = true;
                ui->TimelineDisplay->setText(ui->TimelineDisplay->toPlainText() + "Marking shell is not selected\n");
            }

            if(numFiringRangesAdded == 0){
                errorOccured = true;
                ui->TimelineDisplay->setText(ui->TimelineDisplay->toPlainText() + "No firing ranges added\n");
            }
            if(!errorOccured){
                ui->TimelineDisplay->setTextColor(Qt::black);   //errors have been printed, set text color back to black

                markingType mt = NEGATIVE;
                if(ui->MarkingSelector->currentIndex() == 1){ mt = ILLUM; }
                else if(ui->MarkingSelector->currentIndex() == 2){ mt = WP; }


                QString testing = ui->FiringRangesDisplay->toPlainText();

             //cout << "Non-Standard example 3" << endl;
             //std::vector<fireRange> frVec;

             //frVec.push_back(fireRange{ -2, 1 }); // 1 - (-2) = 3 min interval // 2min before TOT 1 min after
             //cout<<"gap"<<endl;               // 3 - 1 = 2 min interval
             //frVec.push_back(fireRange{ 3, 5 }); // 5 - 3 = 2 min interval //



      NonStandard_Timeline nST = NonStandard_Timeline(stoi(input_1), stoi(input_2), mt, stoi(input_5), frVec, stoi(input_3));

                string testLine = nST.print();
                char test[testLine.size()+1];
                testLine.copy(test,testLine.size()+1);
                test[testLine.size()] = '\0';

                QString x = test;

                ui->TimelineDisplay->setText(ui->TimelineDisplay->toPlainText() + x);

                frVec.clear();
            }

            break;
    }
}

//behavior for the clear button, clears all fields
void MainWindow::on_clearButton_clicked(){
    ui->FiringRangesDisplay->clear();
    ui->FiringRangesDisplay->setText("Firing Ranges:");
    ui->MarkingSelector->setCurrentIndex(-1);
    ui->TimelineDisplay->clear();
    ui->input_1->clear();
    ui->input_2->clear();
    ui->input_3->clear();
    ui->input_5->clear();
    ui->input_6->clear();
    ui->input_7->clear();
    frVec.clear();
}

bool MainWindow::isInt(string input){

    //if(input.empty()){  return false; }

    try{ stoi(input); } catch (...) { return false; }

    //for(char const c : input){ if(!isdigit(c)){ return false; } }
    return true;
}
