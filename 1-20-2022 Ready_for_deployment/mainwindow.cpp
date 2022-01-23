#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <QDebug>
#include <QString>
#include <string>
#include <iostream>
#include <QColor>
#include <timeline.h>
#include <gun.h>

using namespace std;

std::vector<fireRange> frVec;
std::vector<markingType> frVecType;
std::vector<int> frVecMark;

Gun *currentGun;
Gun gun1, gun2, gun3, gun4, gun5, gun6;
bool clearFields;
bool errorOccured;

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

    //have the displays inside the box instead of a text title
    ui->TimelineDisplayGun1->setText("\t     Gun 1 Timeline");
    ui->TimelineDisplayGun2->setText("\t     Gun 2 Timeline");
    ui->TimelineDisplayGun3->setText("\t     Gun 3 Timeline");
    ui->TimelineDisplayGun4->setText("\t     Gun 4 Timeline");
    ui->TimelineDisplayGun5->setText("\t     Gun 5 Timeline");
    ui->TimelineDisplayGun6->setText("\t     Gun 6 Timeline");

    //hide all elements initially
    ui->AddFiringRangeButton->hide();
    ui->FiringRangesLabel_2->hide();
    ui->FiringRangesDisplay->hide();
    ui->RemoveRangeButton->hide();
    ui->FiringRangesLabel->hide();
    ui->MarkingTOFLabel->hide();
    ui->FireFreqLabel->hide();
    ui->MarkingRange->hide();
    ui->AddMarkingRangeButton->hide();
    ui->MarkingRangesDisplay->hide();
    ui->RemoveRangeButton_2Mark->hide();

    ui->input_3->hide();
    ui->input_5->hide();
    ui->input_6->hide();
    ui->input_7->hide();
    ui->input_8->hide();

    //initialize globals
    numFiringRangesAdded = 0;

    //set gun 1 as default gun
    ui->Gun_1_button->setChecked(true);
    currentGun = &gun1;

    ui->errorWindow->clear();
    ui->errorWindow->hide();
    //setNewData();

    //set default firing to continuous
    ui->fireTypeSelector->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_MarkingSelector_currentIndexChanged(int type){
    switch(type){
     case 0:
        ui->input_5->hide();
        ui->MarkingTOFLabel->hide();
        ui->MarkingRange->hide();
        ui->input_8->hide();
        ui->input_8->clear();
        ui->MarkingRangesDisplay->hide();
        ui->RemoveRangeButton_2Mark->hide();
        ui->AddMarkingRangeButton->hide();
        ui->RemoveSingleMarking->hide();
        frVecMark.clear();
        break;

     case 1: case 2:
        ui->input_5->show();
        ui->MarkingTOFLabel->show();

        if(ui->fireTypeSelector->currentIndex() == 2){
            ui->RemoveSingleMarking->show();
            ui->MarkingRange->show();
            ui->input_8->show();
            ui->AddMarkingRangeButton->show();
            ui->MarkingRangesDisplay->show();
            ui->RemoveRangeButton_2Mark->show();
        }
        break;
    }

}
//event handler for when the fire type has been changed
void MainWindow::on_fireTypeSelector_currentIndexChanged(int index)
{
    //show all common items
    ui->CalculateTimelineButton->show();
    ui->clearButton->show();
    ui->TOTLabel->show();
    ui->TOFLabel->show();
    ui->input_1->show();
    ui->input_2->show();
    ui->errorWindow->clear();
    ui->errorWindow->hide();

    //ui->input_3->show();
    currentGun->setFireType(index);

    switch(index){
        //setup continuous and interrupted SEAD layouts
        case 0: case 1:
        //first clear all relevant input fields if they need to be cleared
            frVec.clear();
            frVecMark.clear();

            //hide all non-standard elements
            ui->AddFiringRangeButton->hide();
            ui->FiringRangesDisplay->clear();
            ui->MarkingRangesDisplay->clear();
            ui->FiringRangesDisplay->hide();
            ui->FiringRangesLabel_2->hide();
            ui->RemoveRangeButton->hide();
            ui->FiringRangesLabel->hide();
            ui->FireFreqLabel->hide();
            ui->input_3->hide();
            ui->input_6->hide();
            ui->input_7->hide();
            ui->RemoveSingleMarking->hide();
            ui->RemoveSingleRange->hide();

            //show all standard elements
            ui->MarkingTypeLabel->show();
            ui->MarkingSelector->show();

            //reset marking selector
            //ui->MarkingSelector->setCurrentIndex(-1);

            //reset marking selector
            //ui->CopyGunSelector->setCurrentIndex(-1);

            ui->MarkingRange->hide();
            ui->input_8->hide();
            ui->input_8->clear();
            ui->MarkingRangesDisplay->hide();
            ui->RemoveRangeButton_2Mark->hide();
            ui->AddMarkingRangeButton->hide();

            break;

        //setup non-standard SEAD layout
        case 2:
            //first clear all relevant input fields if they need to be cleared
            //show all non-standard elements
            ui->MarkingTypeLabel->show();
            ui->MarkingSelector->show();
            ui->RemoveSingleRange->show();
            ui->AddFiringRangeButton->show();
            ui->FiringRangesDisplay->show();
            ui->FiringRangesLabel_2->show();
            ui->RemoveRangeButton->show();
            ui->FiringRangesLabel->show();
            ui->FireFreqLabel->show();
            ui->RemoveSingleMarking->hide();

            ui->input_3->show();
            ui->input_6->show();
            ui->input_7->show();

            //set default suppression TOF to 30
            ui->input_3->setText("30");

            //set intial text for firing range display
            ui->FiringRangesDisplay->setText("Suppress From:");

            //set intial text for range display
            ui->MarkingRangesDisplay->setText("Mark With:");

            if(ui->MarkingSelector->currentIndex() <= 0){}
            else{
                ui->RemoveSingleMarking->show();
                ui->MarkingRange->show();
                ui->input_8->show();
                ui->AddMarkingRangeButton->show();
                ui->MarkingRangesDisplay->show();
                ui->RemoveRangeButton_2Mark->show();
              }

            //reset firing ranges list
            numFiringRangesAdded = 0;

            break;
    }
    //clearFields = true;
}

//event handler for when the user clicks on the add firing range button
void MainWindow::on_AddFiringRangeButton_clicked()
{

    string input_6 = ui->input_6->text().toStdString(); //convert text in textbox to string
    string input_7 = ui->input_7->text().toStdString();

    if(isInt(input_6) && isInt(input_7)){ //verify that the value to be inputted is an int

        ui->errorWindow->clear();
        ui->errorWindow->hide();

        ui->FiringRangesDisplay->setText(ui->FiringRangesDisplay->toPlainText() + "\n " + ui->input_6->text() + " to " + ui->input_7->text());

        frVec.push_back(fireRange{ stoi(input_6), stoi(input_7) });

        ui->input_6->clear();
        ui->input_7->clear();

        numFiringRangesAdded++;
    }
    else{
        ui->errorWindow->show();
        ui->errorWindow->setTextColor(Qt::red);
        ui->errorWindow->setText(ui->errorWindow->toPlainText() + "Firing ranges are not whole numbers\n");
    }
}


//event handler for when the user clicks on the add firing range button
void MainWindow::on_AddMarkingRangeButton_clicked()
{

    string input_8 = ui->input_8->text().toStdString(); //convert text in textbox to string
    string displayType = "";
    char disArray[10];

    switch(ui->MarkingSelector->currentIndex()){

    case 0:
        break;
    case 1:
        displayType = "ILLUM at ";
        break;
    case 2:
        displayType = "WP at ";
        break;
    }

    displayType.copy(disArray,displayType.size()+1);
    disArray[displayType.size()] = '\0';

    if(isInt(input_8)){ //verify that the value to be inputted is an int

        ui->errorWindow->clear();
        ui->errorWindow->hide();

        ui->MarkingRangesDisplay->setText(ui->MarkingRangesDisplay->toPlainText() + "\n " + disArray + ui->input_8->text());

        frVecMark.push_back(int{ stoi(input_8) });

        ui->input_8->clear();

        numMarkingRangesAdded++;
    }
    else{
        ui->errorWindow->show();
        ui->errorWindow->setTextColor(Qt::red);
        ui->errorWindow->setText(ui->errorWindow->toPlainText() + "Marking range is not a whole number\n");
    }
}

//event handler for remove ran ge button, removes the most recent firing range
void MainWindow::on_RemoveRangeButton_clicked()
{
    //remove the line from the firing ranges list, first check to see if the firing ranges is empty
    ui->FiringRangesDisplay->clear(); 
    ui->FiringRangesDisplay->setText("Suppress From:");
    frVec.clear();
}

//event handler for remove ran ge button, removes the most recent firing range
void MainWindow::on_RemoveRangeButton_2Mark_clicked()
{
    //remove the line from the firing ranges list, first check to see if the firing ranges is empty
     ui->MarkingRangesDisplay->clear();
     frVecMark.clear();
     ui->MarkingRangesDisplay->setText("Mark With:");
}

//event handler for when the calculate timeline button is clicked
//must either display a valid timeline, or return an error message
void MainWindow::on_CalculateTimelineButton_clicked()
{
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
            ui->errorWindow->setTextColor(Qt::red); //set text color to red in case we need to output errors
            ui->errorWindow->clear();
            ui->errorWindow->hide();
            errorOccured = false;

            if(!isInt(input_1)){
                errorOccured = true;
                ui->errorWindow->show();
                ui->errorWindow->setText(ui->errorWindow->toPlainText() + "TOT is not a whole number\n");
            }
            if(!isInt(input_2)){
                errorOccured = true;
                ui->errorWindow->show();
                ui->errorWindow->setText(ui->errorWindow->toPlainText() + "TOF is not a whole number\n");
            }
            if(!isInt(input_5) && ui->MarkingSelector->currentIndex() > 0){
                errorOccured = true;
                ui->errorWindow->show();
                ui->errorWindow->setText(ui->errorWindow->toPlainText() + "Marking TOF is not a whole number\n");
            }
            if(ui->MarkingSelector->currentIndex() == -1){
                errorOccured = true;
                ui->errorWindow->show();
                ui->errorWindow->setText(ui->errorWindow->toPlainText() + "Marking shell is not selected\n");
            }
            if(!errorOccured){

                ui->errorWindow->setTextColor(Qt::black);   //errors have been printed, set text color back to black
                ui->errorWindow->clear();
                ui->errorWindow->hide();

                errorOccured = false;

                markingType mt = NEGATIVE;
                if(ui->MarkingSelector->currentIndex() == 1){ mt = ILLUM; }
                else if(ui->MarkingSelector->currentIndex() == 2){ mt = WP; }

                timelineType tt = CONTINUOUS;
                if(ui->fireTypeSelector->currentIndex() == 1){ tt = INTERRUPTED; }

                if(mt == NEGATIVE){ input_5 = "0"; }
                //cout << "Standard example 1" << endl;
                Standard_Timeline t0 = Standard_Timeline(stoi(input_1), stoi(input_2), mt, stoi(input_5), tt);

                string testLine = t0.print();
                char test[testLine.size()+1];
                testLine.copy(test,testLine.size()+1);
                test[testLine.size()] = '\0';
                QString x = test;

                if(currentGun == &gun1){ui->TimelineDisplayGun1->clear(); ui->TimelineDisplayGun1->setText("             Gun 1 Timeline\n\n"); ui->TimelineDisplayGun1->setText(ui->TimelineDisplayGun1->toPlainText() + x); }
                else if (currentGun == &gun2){ ui->TimelineDisplayGun2->clear(); ui->TimelineDisplayGun2->setText("          Gun 2 Timeline\n\n"); ui->TimelineDisplayGun2->setText(ui->TimelineDisplayGun2->toPlainText() + x); }
                else if (currentGun == &gun3){ ui->TimelineDisplayGun3->clear(); ui->TimelineDisplayGun3->setText("          Gun 3 Timeline\n\n"); ui->TimelineDisplayGun3->setText(ui->TimelineDisplayGun3->toPlainText() + x); }
                else if (currentGun == &gun4){ ui->TimelineDisplayGun4->clear(); ui->TimelineDisplayGun4->setText("          Gun 4 Timeline\n\n"); ui->TimelineDisplayGun4->setText(ui->TimelineDisplayGun4->toPlainText() + x); }
                else if (currentGun == &gun5){ ui->TimelineDisplayGun5->clear(); ui->TimelineDisplayGun5->setText("          Gun 5 Timeline\n\n"); ui->TimelineDisplayGun5->setText(ui->TimelineDisplayGun5->toPlainText() + x); }
                else { ui->TimelineDisplayGun6->clear(); ui->TimelineDisplayGun6->setText("          Gun 6 Timeline\n\n"); ui->TimelineDisplayGun6->setText(ui->TimelineDisplayGun6->toPlainText() + x); }
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

            ui->errorWindow->clear();
            ui->errorWindow->hide();
            errorOccured = false;

            //verify each input for empty value, or non-int value
            ui->errorWindow->setTextColor(Qt::red); //set text color to red in case we need to output errors
            if(!isInt(input_1)){
                errorOccured = true;
                ui->errorWindow->show();
                ui->errorWindow->setText(ui->errorWindow->toPlainText() + "TOT is not a whole number\n");
            }
            if(!isInt(input_2)){
                errorOccured = true;
                ui->errorWindow->show();
                ui->errorWindow->setText(ui->errorWindow->toPlainText() + "TOF is not a whole number\n");
            }
            if(!isInt(input_3)){
                errorOccured = true;
                ui->errorWindow->show();
                ui->errorWindow->setText(ui->errorWindow->toPlainText() + "Fire Frequency is not a whole number\n");
            }
            if(!isInt(input_5) && ui->MarkingSelector->currentIndex() > 0){
                errorOccured = true;
                ui->errorWindow->show();
                ui->errorWindow->setText(ui->errorWindow->toPlainText() + "Marking TOF is not a whole number\n");
            }

            if(ui->MarkingSelector->currentIndex() == -1){
                errorOccured = true;
                ui->errorWindow->show();
                ui->errorWindow->setText(ui->errorWindow->toPlainText() + "Marking shell is not selected\n");
            }
            if(frVec.empty()){
                errorOccured = true;
                ui->errorWindow->show();
                ui->errorWindow->setText(ui->errorWindow->toPlainText() + "Add Suppress Range\n");
            }
            if(frVecMark.empty() && ui->MarkingSelector->currentIndex() != 0){
                errorOccured = true;
                ui->errorWindow->show();
                ui->errorWindow->setText(ui->errorWindow->toPlainText() + "Add Marking Range\n");
            }
            if(!errorOccured){
                ui->errorWindow->setTextColor(Qt::black);   //errors have been printed, set text color back to black
                ui->errorWindow->clear();
                ui->errorWindow->hide();

                errorOccured = false;

                markingType mt = NEGATIVE;
                if(ui->MarkingSelector->currentIndex() == 1){ mt = ILLUM; }
                else if(ui->MarkingSelector->currentIndex() == 2){ mt = WP; }

                if(mt == NEGATIVE){ input_5 = "0"; }
                
                NonStandard_Timeline nST = NonStandard_Timeline(stoi(input_1), stoi(input_2), stoi(input_5), frVec, stoi(input_3));

                for(int num : frVecMark){ nST.addMarkingRound(mt, num); }

                string testLine = nST.print();
                char test[testLine.size()+1];
                testLine.copy(test,testLine.size()+1);
                test[testLine.size()] = '\0';
                QString x = test;

                if(currentGun == &gun1){ui->TimelineDisplayGun1->clear(); ui->TimelineDisplayGun1->setText("             Gun 1 Timeline\n\n"); ui->TimelineDisplayGun1->setText(ui->TimelineDisplayGun1->toPlainText() + x); }
                else if (currentGun == &gun2){ ui->TimelineDisplayGun2->clear(); ui->TimelineDisplayGun2->setText("          Gun 2 Timeline\n\n"); ui->TimelineDisplayGun2->setText(ui->TimelineDisplayGun2->toPlainText() + x); }
                else if (currentGun == &gun3){ ui->TimelineDisplayGun3->clear(); ui->TimelineDisplayGun3->setText("          Gun 3 Timeline\n\n"); ui->TimelineDisplayGun3->setText(ui->TimelineDisplayGun3->toPlainText() + x); }
                else if (currentGun == &gun4){ ui->TimelineDisplayGun4->clear(); ui->TimelineDisplayGun4->setText("          Gun 4 Timeline\n\n"); ui->TimelineDisplayGun4->setText(ui->TimelineDisplayGun4->toPlainText() + x); }
                else if (currentGun == &gun5){ ui->TimelineDisplayGun5->clear(); ui->TimelineDisplayGun5->setText("          Gun 5 Timeline\n\n"); ui->TimelineDisplayGun5->setText(ui->TimelineDisplayGun5->toPlainText() + x); }
                else { ui->TimelineDisplayGun6->clear(); ui->TimelineDisplayGun6->setText("          Gun 6 Timeline\n\n"); ui->TimelineDisplayGun6->setText(ui->TimelineDisplayGun6->toPlainText() + x); }
            }
            qInfo() << ui->input_1->text();
            break;
    }
}


//gun 1 is selected, load all gun 1 data into the displays
void MainWindow::on_Gun_1_button_clicked()
{
    currentGun = &gun1;
    ui->errorWindow->clear();
    ui->errorWindow->hide();
    //setNewData();
}

//gun 2 is selected, load all gun 2 data into the displays
void MainWindow::on_Gun_2_button_clicked()
{
    currentGun = &gun2;
    ui->errorWindow->clear();
    ui->errorWindow->hide();
    //setNewData();
}

//gun 3 is selected, load all gun 3 data into the displays
void MainWindow::on_Gun_3_button_clicked()
{
    currentGun = &gun3;
    ui->errorWindow->clear();
    ui->errorWindow->hide();
    //setNewData();
}

//gun 4 is selected, load all gun 4 data into the displays
void MainWindow::on_Gun_4_button_clicked()
{
    currentGun = &gun4;
    ui->errorWindow->clear();
    ui->errorWindow->hide();
    //setNewData();
}

//gun 5 is selected, load all gun 5 data into the displays
void MainWindow::on_Gun_5_button_clicked()
{
    currentGun = &gun5;
    ui->errorWindow->clear();
    ui->errorWindow->hide();
    //setNewData();
}

//gun 6 is selected, load all gun 6 data into the displays
void MainWindow::on_Gun_6_button_clicked()
{
    currentGun = &gun6;
    ui->errorWindow->clear();
    ui->errorWindow->hide();
    //setNewData();
}

/*
//reloads all data in display boxes using the current gun data set
void MainWindow::setNewData(){
    clearFields = false;
    ui->fireTypeSelector->setCurrentIndex(currentGun->getFireType());
    //ui->TimelineDisplay->setText(currentGun->getTimeline());
    ui->input_1->setText(QString::number(currentGun->getTOF()));
    ui->input_2->setText(QString::number(currentGun->getTOT()));
    ui->input_3->setText(QString::number(currentGun->getFireFreq()));
    ui->input_5->setText(QString::number(currentGun->getMarkingTOF()));
    //qInfo() << "gun " << currentGun << " has marking round " << currentGun->getMarkingRound();
    ui->MarkingSelector->setCurrentIndex(currentGun->getMarkingRound());
}
*/

//behavior for the clear button, clears all fields
void MainWindow::on_clearButton_clicked(){

    ui->errorWindow->clear();
    ui->errorWindow->hide();

    ui->FiringRangesDisplay->clear();
    ui->FiringRangesDisplay->setText("Suppress From:");

    ui->MarkingRangesDisplay->clear();
    ui->MarkingRangesDisplay->setText("Mark With:");

    //ui->MarkingSelector->setCurrentIndex(-1);

    //ui->fireTypeSelector->setCurrentIndex(-1);

    ui->input_1->clear();
    ui->input_2->clear();
    ui->input_3->clear();
    ui->input_5->clear();
    ui->input_6->clear();
    ui->input_7->clear();
    ui->input_8->clear();

    frVec.clear();
    frVecMark.clear();
}

void MainWindow::on_clearButtonGuns_clicked(){
    ui->errorWindow->clear();
    ui->errorWindow->hide();

    ui->TimelineDisplayGun1->clear();
    ui->TimelineDisplayGun1->setText("              Gun 1 Timeline");

    ui->TimelineDisplayGun2->clear();
    ui->TimelineDisplayGun2->setText("              Gun 2 Timeline");

    ui->TimelineDisplayGun3->clear();
    ui->TimelineDisplayGun3->setText("              Gun 3 Timeline");

    ui->TimelineDisplayGun4->clear();
    ui->TimelineDisplayGun4->setText("              Gun 4 Timeline");

    ui->TimelineDisplayGun5->clear();
     ui->TimelineDisplayGun5->setText("              Gun 5 Timeline");

    ui->TimelineDisplayGun6->clear();
    ui->TimelineDisplayGun6->setText("              Gun 6 Timeline");
}

bool MainWindow::isInt(string input){ try{ stoi(input); } catch (...) { return false; } return true; }


/*
void MainWindow::on_input_2_textEdited(const QString &arg1)
{
    currentGun->setTOT(arg1.toInt());
}


void MainWindow::on_input_1_textEdited(const QString &arg1)
{
    currentGun->setTOF(arg1.toInt());
}


void MainWindow::on_input_5_textEdited(const QString &arg1)
{
    currentGun->setMarkingTOF(arg1.toInt());
}


void MainWindow::on_input_3_textEdited(const QString &arg1)
{
    currentGun->setFireFreq(arg1.toInt());
}
*/

void MainWindow::on_RemoveSingleRange_clicked()
{
    //remove the line from the firing ranges list, first check to see if the firing ranges is empty
    if(frVec.size() != 0){
        frVec.pop_back();

        string firingRangesText = ui->FiringRangesDisplay->toPlainText().toStdString();
        string newFiringRanges = firingRangesText.substr(0, firingRangesText.find_last_of("\n"));
        ui->FiringRangesDisplay->setText(QString::fromStdString(newFiringRanges));
    }
}


void MainWindow::on_RemoveSingleMarking_clicked()
{
    //remove the line from the marking ranges list, first check to see if the firing ranges is empty
    if(frVecMark.size() != 0){
        frVecMark.pop_back();

        string markingRangesText = ui->MarkingRangesDisplay->toPlainText().toStdString();
        string newMarkingRanges = markingRangesText.substr(0, markingRangesText.find_last_of("\n"));
        ui->MarkingRangesDisplay->setText(QString::fromStdString(newMarkingRanges));
    }
}


void MainWindow::on_ClearTimeline1_clicked()
{
    ui->TimelineDisplayGun1->clear();
    ui->TimelineDisplayGun1->setText("              Gun 1 Timeline");
}


void MainWindow::on_ClearTimeline2_clicked()
{
    ui->TimelineDisplayGun2->clear();
    ui->TimelineDisplayGun2->setText("              Gun 2 Timeline");
}


void MainWindow::on_ClearTimeline3_clicked()
{
    ui->TimelineDisplayGun3->clear();
    ui->TimelineDisplayGun3->setText("              Gun 3 Timeline");
}


void MainWindow::on_ClearTimeline4_clicked()
{
    ui->TimelineDisplayGun4->clear();
    ui->TimelineDisplayGun4->setText("              Gun 4 Timeline");
}


void MainWindow::on_ClearTimeline5_clicked()
{
    ui->TimelineDisplayGun5->clear();
    ui->TimelineDisplayGun5->setText("              Gun 5 Timeline");
}


void MainWindow::on_ClearTimeline6_clicked()
{
    ui->TimelineDisplayGun6->clear();
    ui->TimelineDisplayGun6->setText("              Gun 6 Timeline");
}

