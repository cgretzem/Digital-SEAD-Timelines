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

    //add Gun number to be Copied
    ui->CopyGunSelector->addItem("1");
    ui->CopyGunSelector->addItem("2");
    ui->CopyGunSelector->addItem("3");
    ui->CopyGunSelector->addItem("4");
    ui->CopyGunSelector->addItem("5");
    ui->CopyGunSelector->addItem("6");


    //hide all elements initially
    //ui->CalculateTimelineButton->hide();
    ui->AddFiringRangeButton->hide();
    ui->FiringRangesLabel_2->hide();
    ui->FiringRangesDisplay->hide();
    ui->RemoveRangeButton->hide();
    ui->FiringRangesLabel->hide();
    //ui->MarkingTypeLabel->hide();
    ui->MarkingTOFLabel->hide();
    //ui->TimelineDisplay->hide();
    //ui->MarkingSelector->hide();
    ui->FireFreqLabel->hide();
    //ui->clearButton->hide();
    //ui->TOTLabel->hide();
    //ui->TOFLabel->hide();
    //ui->input_1->hide();
    //ui->input_2->hide();
    ui->input_3->hide();
    ui->input_5->hide();
    ui->input_6->hide();
    ui->input_7->hide();


    ui->input_8->hide();
    ui->MarkingRange->hide();
    ui->AddMarkingRangeButton->hide();
    ui->MarkingRangesDisplay->hide();
    ui->RemoveRangeButton_2Mark->hide();

    ui->CopyGun->hide();
    ui->CopyGunButton->hide();
    ui->CopyGunSelector->hide();

    //ui->fireTypeSelector->clear();
    //ui->MarkingSelector->setCurrentIndex(-1);

    //initialize globals
    numFiringRangesAdded = 0;

    //set gun 1 as default gun
    ui->Gun_1_button->setChecked(true);
    currentGun = &gun1;

    //setNewData();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_MarkingSelector_currentIndexChanged(int type){

    switch(type){

     case 0:
        ui->input_5->hide();
        ui->input_5->setText("0");
        ui->MarkingTOFLabel->hide();

        ui->MarkingRange->hide();
        ui->input_8->hide();
        ui->input_8->clear();
        ui->MarkingRangesDisplay->hide();
        ui->RemoveRangeButton_2Mark->hide();
        ui->AddMarkingRangeButton->hide();

        break;

     case 1: case 2:


        ui->input_5->show();
        ui->input_5->setText("0");
        ui->MarkingTOFLabel->show();

        if(ui->fireTypeSelector->currentIndex() == 2){
        ui->MarkingRange->show();
        ui->input_8->show();
        ui->input_8->setText("0");
        ui->AddMarkingRangeButton->show();
        ui->MarkingRangesDisplay->show();
        ui->RemoveRangeButton_2Mark->show();
        }

        break;

    }

    //currentGun->setMarkingRound(type);


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

    currentGun->setFireType(index);


    switch(index){
        //setup continuous and interrupted SEAD layouts
        case 0: case 1:
            //first clear all relevant input fields if they need to be cleared
/*
           if(clearFields){
                ui->TimelineDisplay->clear();
                ui->input_1->clear();
                ui->input_2->clear();
                ui->input_3->clear();
                ui->input_5->clear();
            }
*/
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

            //ui->input_5->hide();
            ui->MarkingTOFLabel->hide();

            //show all standard elements
            ui->MarkingTypeLabel->show();
            //ui->MarkingTOFLabel->show();
            ui->MarkingSelector->show();
            //ui->input_5->show();

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
/*
            if(clearFields){
                ui->TimelineDisplay->clear();
                ui->input_1->clear();
                ui->input_2->clear();
                ui->input_3->clear();
                ui->input_5->clear();
                ui->input_6->clear();
                ui->input_7->clear();
            }
*/
            ui->MarkingTypeLabel->show();
            //ui->MarkingTOFLabel->show();
            ui->MarkingSelector->show();
            //ui->input_5->show();

            //show all non-standard elements
            ui->AddFiringRangeButton->show();
            ui->FiringRangesDisplay->show();
            ui->FiringRangesLabel_2->show();
            ui->RemoveRangeButton->show();
            ui->FiringRangesLabel->show();
            ui->FireFreqLabel->show();
            ui->input_3->show();
            ui->input_3->setText("30");
            ui->input_6->show();
            ui->input_7->show();

            //set intial text for firing range display
            ui->FiringRangesDisplay->setText("Firing Ranges:");

            //set intial text for  range display
            ui->MarkingRangesDisplay->setText("Marking Ranges:");

            //ui->MarkingSelector->setCurrentIndex(-1);

            //reset firing ranges list
            numFiringRangesAdded = 0;

            break;
    }
    //clearFields = true;
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


//event handler for when the user clicks on the add firing range button
void MainWindow::on_AddMarkingRangeButton_clicked()
{
    ui->TimelineDisplay->clear();   //clear timeline display
    string input_8 = ui->input_8->text().toStdString(); //convert text in textbox to string

    if(isInt(input_8)){ //verify that the value to be inputted is an int

        ui->MarkingRangesDisplay->setText(ui->MarkingRangesDisplay->toPlainText() + "\n " + ui->input_8->text());

        frVecMark.push_back(int{ stoi(input_8) });
        ui->input_8->clear();
        numMarkingRangesAdded++;
    }
    else{
        ui->TimelineDisplay->setTextColor(Qt::red);
        ui->TimelineDisplay->setText(ui->TimelineDisplay->toPlainText() + "Marking range is not a whole number\n");
    }
}



//event handler for remove ran ge button, removes the most recent firing range
void MainWindow::on_RemoveRangeButton_clicked()
{
    //remove the line from the firing ranges list, first check to see if the firing ranges is empty
    /*
    if(numFiringRangesAdded != 0){
        frVec.pop_back();
        numFiringRangesAdded--;

        string firingRangesText = ui->FiringRangesDisplay->toPlainText().toStdString();
        string newFiringRanges = firingRangesText.substr(0, firingRangesText.find_last_of("\n"));
        ui->FiringRangesDisplay->setText(QString::fromStdString(newFiringRanges));
    }
*/
    ui->FiringRangesDisplay->clear();
    frVec.clear();
}

//event handler for remove ran ge button, removes the most recent firing range
void MainWindow::on_RemoveRangeButton_2Mark_clicked()
{
    //remove the line from the firing ranges list, first check to see if the firing ranges is empty
   /*
    if(numMarkingRangesAdded != 0){
        frVecMark.pop_back();
        numMarkingRangesAdded--;

        string MarkingRangesText = ui->MarkingRangesDisplay->toPlainText().toStdString();
        string newMarkingRanges = MarkingRangesText.substr(0, MarkingRangesText.find_last_of("\n"));
        ui->MarkingRangesDisplay->setText(QString::fromStdString(newMarkingRanges));
    }
*/
     ui->MarkingRangesDisplay->clear();
     frVecMark.clear();
}


void MainWindow::on_CopyGunButton_clicked()
{

    switch(ui->CopyGunSelector->currentIndex()){

    case(0):
        if(currentGun == &gun1){ ui->TimelineDisplayGun1->setText(ui->TimelineDisplayGun1->toPlainText()); }
        else if (currentGun == &gun2){ ui->TimelineDisplayGun2->setText(ui->TimelineDisplayGun1->toPlainText()); }
        else if (currentGun == &gun3){ ui->TimelineDisplayGun3->setText(ui->TimelineDisplayGun1->toPlainText()); }
        else if (currentGun == &gun4){ ui->TimelineDisplayGun4->setText(ui->TimelineDisplayGun1->toPlainText()); }
        else if (currentGun == &gun5){ ui->TimelineDisplayGun5->setText(ui->TimelineDisplayGun1->toPlainText()); }
        else { ui->TimelineDisplayGun6->setText(ui->TimelineDisplayGun1->toPlainText()); }
        break;
    case(1):
        if(currentGun == &gun1){ ui->TimelineDisplayGun1->setText(ui->TimelineDisplayGun2->toPlainText()); }
        else if (currentGun == &gun2){ ui->TimelineDisplayGun2->setText(ui->TimelineDisplayGun2->toPlainText()); }
        else if (currentGun == &gun3){ ui->TimelineDisplayGun3->setText(ui->TimelineDisplayGun2->toPlainText()); }
        else if (currentGun == &gun4){ ui->TimelineDisplayGun4->setText(ui->TimelineDisplayGun2->toPlainText()); }
        else if (currentGun == &gun5){ ui->TimelineDisplayGun5->setText(ui->TimelineDisplayGun2->toPlainText()); }
        else { ui->TimelineDisplayGun6->setText(ui->TimelineDisplayGun2->toPlainText()); }
        break;
    case(2):
        if(currentGun == &gun1){ ui->TimelineDisplayGun1->setText(ui->TimelineDisplayGun3->toPlainText()); }
        else if (currentGun == &gun2){ ui->TimelineDisplayGun2->setText(ui->TimelineDisplayGun3->toPlainText()); }
        else if (currentGun == &gun3){ ui->TimelineDisplayGun3->setText(ui->TimelineDisplayGun3->toPlainText()); }
        else if (currentGun == &gun4){ ui->TimelineDisplayGun4->setText(ui->TimelineDisplayGun3->toPlainText()); }
        else if (currentGun == &gun5){ ui->TimelineDisplayGun5->setText(ui->TimelineDisplayGun3->toPlainText()); }
        else { ui->TimelineDisplayGun6->setText(ui->TimelineDisplayGun3->toPlainText()); }
        break;
    case(3):
        if(currentGun == &gun1){ ui->TimelineDisplayGun1->setText(ui->TimelineDisplayGun4->toPlainText()); }
        else if (currentGun == &gun2){ ui->TimelineDisplayGun2->setText(ui->TimelineDisplayGun4->toPlainText()); }
        else if (currentGun == &gun3){ ui->TimelineDisplayGun3->setText(ui->TimelineDisplayGun4->toPlainText()); }
        else if (currentGun == &gun4){ ui->TimelineDisplayGun4->setText(ui->TimelineDisplayGun4->toPlainText()); }
        else if (currentGun == &gun5){ ui->TimelineDisplayGun5->setText(ui->TimelineDisplayGun4->toPlainText()); }
        else { ui->TimelineDisplayGun6->setText(ui->TimelineDisplayGun4->toPlainText()); }
        break;
    case(4):
        if(currentGun == &gun1){ ui->TimelineDisplayGun1->setText(ui->TimelineDisplayGun5->toPlainText()); }
        else if (currentGun == &gun2){ ui->TimelineDisplayGun2->setText(ui->TimelineDisplayGun5->toPlainText()); }
        else if (currentGun == &gun3){ ui->TimelineDisplayGun3->setText(ui->TimelineDisplayGun5->toPlainText()); }
        else if (currentGun == &gun4){ ui->TimelineDisplayGun4->setText(ui->TimelineDisplayGun5->toPlainText()); }
        else if (currentGun == &gun5){ ui->TimelineDisplayGun5->setText(ui->TimelineDisplayGun5->toPlainText()); }
        else { ui->TimelineDisplayGun6->setText(ui->TimelineDisplayGun5->toPlainText()); }
        break;
    case(5):
        if(currentGun == &gun1){ ui->TimelineDisplayGun1->setText(ui->TimelineDisplayGun6->toPlainText()); }
        else if (currentGun == &gun2){ ui->TimelineDisplayGun2->setText(ui->TimelineDisplayGun6->toPlainText()); }
        else if (currentGun == &gun3){ ui->TimelineDisplayGun3->setText(ui->TimelineDisplayGun6->toPlainText()); }
        else if (currentGun == &gun4){ ui->TimelineDisplayGun4->setText(ui->TimelineDisplayGun6->toPlainText()); }
        else if (currentGun == &gun5){ ui->TimelineDisplayGun5->setText(ui->TimelineDisplayGun6->toPlainText()); }
        else { ui->TimelineDisplayGun6->setText(ui->TimelineDisplayGun6->toPlainText()); }
        break;

    };

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
                //currentGun->setTimeline(ui->TimelineDisplay->toPlainText());

                if(currentGun == &gun1){ui->TimelineDisplayGun1->clear(); ui->TimelineDisplayGun1->setText(ui->TimelineDisplayGun1->toPlainText() + x); }
                else if (currentGun == &gun2){ ui->TimelineDisplayGun2->clear(); ui->TimelineDisplayGun2->setText(ui->TimelineDisplayGun2->toPlainText() + x); }
                else if (currentGun == &gun3){ ui->TimelineDisplayGun3->clear(); ui->TimelineDisplayGun3->setText(ui->TimelineDisplayGun3->toPlainText() + x); }
                else if (currentGun == &gun4){ ui->TimelineDisplayGun4->clear(); ui->TimelineDisplayGun4->setText(ui->TimelineDisplayGun4->toPlainText() + x); }
                else if (currentGun == &gun5){ ui->TimelineDisplayGun5->clear(); ui->TimelineDisplayGun5->setText(ui->TimelineDisplayGun5->toPlainText() + x); }
                else { ui->TimelineDisplayGun6->clear(); ui->TimelineDisplayGun6->setText(ui->TimelineDisplayGun6->toPlainText() + x); }

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
            string input_8 = ui->input_8->text().toStdString();


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


                //NonStandard_Timeline nST = NonStandard_Timeline(stoi(input_1), stoi(input_2), mt, stoi(input_5), frVec, stoi(input_3));
                NonStandard_Timeline nST = NonStandard_Timeline(stoi(input_1), stoi(input_2), stoi(input_5), frVec, stoi(input_3));

                for(int num : frVecMark){ nST.addMarkingRound(mt, num); }

                string testLine = nST.print();
                char test[testLine.size()+1];
                testLine.copy(test,testLine.size()+1);
                test[testLine.size()] = '\0';

                QString x = test;

                ui->TimelineDisplay->setText(ui->TimelineDisplay->toPlainText() + x);
                //currentGun->setTimeline(ui->TimelineDisplay->toPlainText());

                if(currentGun == &gun1){ ui->TimelineDisplayGun1->clear(); ui->TimelineDisplayGun1->setText(ui->TimelineDisplayGun1->toPlainText() + x); }
                else if (currentGun == &gun2){ ui->TimelineDisplayGun2->clear(); ui->TimelineDisplayGun2->setText(ui->TimelineDisplayGun2->toPlainText() + x); }
                else if (currentGun == &gun3){ ui->TimelineDisplayGun3->clear(); ui->TimelineDisplayGun3->setText(ui->TimelineDisplayGun3->toPlainText() + x); }
                else if (currentGun == &gun4){ ui->TimelineDisplayGun4->clear(); ui->TimelineDisplayGun4->setText(ui->TimelineDisplayGun4->toPlainText() + x); }
                else if (currentGun == &gun5){ ui->TimelineDisplayGun5->clear(); ui->TimelineDisplayGun5->setText(ui->TimelineDisplayGun5->toPlainText() + x); }
                else { ui->TimelineDisplayGun6->clear(); ui->TimelineDisplayGun6->setText(ui->TimelineDisplayGun6->toPlainText() + x); }

                //frVec.clear();
                //frVecMark.clear();
            }
            break;
    }
}


//gun 1 is selected, load all gun 1 data into the displays
void MainWindow::on_Gun_1_button_clicked()
{
    currentGun = &gun1;
    //setNewData();
}

//gun 2 is selected, load all gun 2 data into the displays
void MainWindow::on_Gun_2_button_clicked()
{
    currentGun = &gun2;
    //setNewData();
}

//gun 3 is selected, load all gun 3 data into the displays
void MainWindow::on_Gun_3_button_clicked()
{
    currentGun = &gun3;
    //setNewData();
}

//gun 4 is selected, load all gun 4 data into the displays
void MainWindow::on_Gun_4_button_clicked()
{
    currentGun = &gun4;
    //setNewData();
}

//gun 5 is selected, load all gun 5 data into the displays
void MainWindow::on_Gun_5_button_clicked()
{
    currentGun = &gun5;
    //setNewData();
}

//gun 6 is selected, load all gun 6 data into the displays
void MainWindow::on_Gun_6_button_clicked()
{
    currentGun = &gun6;
    //setNewData();
}

//reloads all data in display boxes using the current gun data set
void MainWindow::setNewData(){
    clearFields = false;
    ui->fireTypeSelector->setCurrentIndex(currentGun->getFireType());
    ui->TimelineDisplay->setText(currentGun->getTimeline());
    ui->input_1->setText(QString::number(currentGun->getTOF()));
    ui->input_2->setText(QString::number(currentGun->getTOT()));
    ui->input_3->setText(QString::number(currentGun->getFireFreq()));
    ui->input_5->setText(QString::number(currentGun->getMarkingTOF()));
    //qInfo() << "gun " << currentGun << " has marking round " << currentGun->getMarkingRound();
    ui->MarkingSelector->setCurrentIndex(currentGun->getMarkingRound());
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
    frVecMark.clear();
}

bool MainWindow::isInt(string input){

    //if(input.empty()){  return false; }

    try{ stoi(input); } catch (...) { return false; }

    //for(char const c : input){ if(!isdigit(c)){ return false; } }
    return true;
}

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

/*
void MainWindow::on_MarkingSelector_currentIndexChanged(int index)
{
    //qInfo() << "marking round changed to " << index << " for gun " << currentGun;
    if(index != -1){
        currentGun->setMarkingRound(index);
    }
}
*/
