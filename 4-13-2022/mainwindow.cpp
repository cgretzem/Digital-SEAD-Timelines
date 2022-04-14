#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <timeline.h>
#include <gun.h>

using namespace std;

std::vector<fireRange> frVec;
std::vector<markingType> frVecType;
std::vector<int> frVecMark;

Gun *currentGun;
Gun gun1, gun2, gun3, gun4, gun5, gun6;
bool clearFields, errorOccured;
int gunIndex;

string tLineArry[6];
string fiName;

QTextBrowser* TimelineDisplayGuns[6];//array of pointers to QTextBrowser objects

struct tLineParam{
    string tLineNum;
    string tLineType;
    string casTOT;
    string supTOF;
    string supFF;
    string supFR;
    string mType;
    string mTOF;
    string mAt;
};

tLineParam printInput[6];

void MainWindow::clearPrintInputs(int b){
    printInput[b].tLineNum = "NA";
    printInput[b].tLineType = "NA";
    printInput[b].casTOT = "NA";
    printInput[b].supTOF = "NA";
    printInput[b].supFF = "NA";
    printInput[b].supFR = "NA";
    printInput[b].mType = "NA";
    printInput[b].mTOF = "NA";
    printInput[b].mAt = "NA";
}


void MainWindow::clearGUIinputs(){
    ui->input_1->clear();
    ui->input_2->clear();
    ui->input_3->clear();
    ui->input_5->clear();
    ui->input_6->clear();
    ui->input_7->clear();
    ui->input_8->clear();
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //add fire type items into fire selector combo box
    ui->fireTypeSelector->addItem("Continuous");
    ui->fireTypeSelector->addItem("Interrupted");
    ui->fireTypeSelector->addItem("Non-Standard");

    //add marking round types into marking round selector
    ui->MarkingSelector->addItem("Negative");
    ui->MarkingSelector->addItem("Illum");
    ui->MarkingSelector->addItem("WP");

    //have the displays inside the box instead of a text title
    TimelineDisplayGuns[0] = ui->TimelineDisplayGun1;
    TimelineDisplayGuns[1] = ui->TimelineDisplayGun2;
    TimelineDisplayGuns[2] = ui->TimelineDisplayGun3;
    TimelineDisplayGuns[3] = ui->TimelineDisplayGun4;
    TimelineDisplayGuns[4] = ui->TimelineDisplayGun5;
    TimelineDisplayGuns[5] = ui->TimelineDisplayGun6;

    for(int i = 1; i < 7; i++){
        string text = "Gun " + to_string(i) + " Timeline\n\n";
        TimelineDisplayGuns[i-1]->setText(QString(text.c_str()));
        TimelineDisplayGuns[i-1]->setAlignment(Qt::AlignCenter);
    }

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

    //set default firing to continuous
    ui->fireTypeSelector->setCurrentIndex(0);

    //clear all timelines
    for(int i = 0; i < 6; i++){
        clearPrintInputs(i);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_MarkingSelector_currentIndexChanged(int type){
    switch(type){
     case 0:
        ui->input_5->hide();
        ui->input_5->clear();
        ui->MarkingTOFLabel->hide();
        ui->MarkingRange->hide();
        ui->input_8->hide();
        ui->input_8->clear();
        ui->MarkingRangesDisplay->hide();
        ui->RemoveRangeButton_2Mark->hide();
        ui->AddMarkingRangeButton->hide();
        ui->RemoveSingleMarking->hide();
        ui->MarkingRangesDisplay->clear();
        frVecMark.clear();
        break;

     case 1: case 2:
        ui->input_5->show();
        ui->input_5->clear();
        ui->MarkingTOFLabel->show();

        if(ui->fireTypeSelector->currentIndex() == 2){
            ui->RemoveSingleMarking->show();
            ui->MarkingRange->show();
            ui->input_8->show();
            ui->input_8->clear();
            ui->AddMarkingRangeButton->show();
            ui->MarkingRangesDisplay->clear();
            ui->MarkingRangesDisplay->setText("Mark With:");
            frVecMark.clear();
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
            ui->input_3->clear();
            ui->input_6->hide();
            ui->input_6->clear();
            ui->input_7->hide();
            ui->input_7->clear();
            ui->RemoveSingleMarking->hide();
            ui->RemoveSingleRange->hide();

            //show all standard elements
            ui->MarkingTypeLabel->show();
            ui->MarkingSelector->show();
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
}

//event handler for when the user clicks the save file button
void MainWindow::on_fileNameButton_clicked()
{
    ui->errorWindow->setTextColor(Qt::red); //set text color to red in case we need to output errors
    ui->errorWindow->clear();
    ui->errorWindow->hide();
    errorOccured = false;

    ofstream myfile;

    fiName = ui->fileNameInput->text().toStdString();

    if(fiName.length() <= 0 || invalidChar(fiName)){
        errorOccured = true;
        ui->errorWindow->show();
        ui->errorWindow->setText(ui->errorWindow->toPlainText() + "ERROR: Add File Name\n");
    }

    else if(!invalidChar2(fiName)){
        errorOccured = true;
        ui->errorWindow->show();
        ui->errorWindow->setText(ui->errorWindow->toPlainText() + "ERROR: File Name has Invalid Characters");
    }

    if(!errorOccured){
        ui->errorWindow->setTextColor(Qt::black);   //errors have been printed, set text color back to black
        ui->errorWindow->clear();
        ui->errorWindow->hide();
        errorOccured = false;

        string path = "C:\\Users\\";
        path += getenv("USERNAME");
        path += "\\Desktop\\";
        path += fiName;
        path += ".txt";
        ofstream { path };
        myfile.open(path);

        //format date and time for GMT
        time_t currentTime = time(0); //get current date/time
        tm *gmtm = gmtime(&currentTime); //format date/time for zulu (GMT) time
        char* dt = asctime(gmtm);
        dt[strlen(dt) - 1] = 0; //remove newline char at the end

        myfile << "File:[" << fiName << "]   Date:[" << dt << "]" << endl << endl << endl;

        for(int i = 0; i < 6; i++){
            if(printInput[i].casTOT != "NA"){   //only print timelines with data
                string pRam = "\n";

                pRam += "[CAS TOT = ";
                pRam += printInput[i].casTOT;
                pRam += "] ";

                pRam += "[Sup TOF = ";
                pRam += printInput[i].supTOF;
                pRam += "] ";

                pRam += "[Mark Type = ";
                pRam += printInput[i].mType;
                pRam += "] ";

                if(printInput[i].mType == "NEGATIVE"){ printInput[i].mTOF = "NA"; }
                pRam += "[Mark TOF = ";
                pRam += printInput[i].mTOF;
                pRam += "] ";

                if(printInput[i].tLineType == " Non-Standard  =================================="){
                    pRam += "[Sup FF = ";
                    pRam += printInput[i].supFF;
                    pRam += "]\n";

                    pRam += "[Sup FR = ";
                    pRam += printInput[i].supFR;
                    pRam += "]\n";

                    if(printInput[i].mType == "NEGATIVE"){ printInput[i].mAt = "NA"; }
                    pRam += "[Mark At = ";
                    pRam += printInput[i].mAt;
                    pRam += "] ";
                }

                myfile << printInput[i].tLineNum << endl;
                myfile << pRam << endl << endl;
                myfile << tLineArry[i] << endl << endl;
            }
        }
        myfile.close();
        ui->fileNameInput->clear();
        fiName = "NA";
    }
}

//event handler for when the user clicks on the add firing range button
void MainWindow::on_AddFiringRangeButton_clicked()
{
    //verify each input for empty value, or non-int value
    ui->errorWindow->setTextColor(Qt::red); //set text color to red in case we need to output errors
    ui->errorWindow->clear();
    ui->errorWindow->hide();
    errorOccured = false;

    string input_6 = ui->input_6->text().toStdString(); //convert text in textbox to string
    string input_7 = ui->input_7->text().toStdString();

    if(!invalidChar(input_6)){
        errorOccured = true;
        ui->errorWindow->show();
        ui->errorWindow->setText(ui->errorWindow->toPlainText() + "ERROR: Suppression Range 1st entry has invalid characters\n");
    }
    if(!invalidChar(input_7)){
        errorOccured = true;
        ui->errorWindow->show();
        ui->errorWindow->setText(ui->errorWindow->toPlainText() + "ERROR: Suppression Range 2nd entry has invalid characters\n");
    }
    else if(isInt(input_6) && isInt(input_7)){ //verify that the value to be inputted is an int

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
        ui->errorWindow->setText(ui->errorWindow->toPlainText() + "ERROR: Firing ranges are not whole numbers\n");
    }
}

//event handler for when the user clicks on the add firing range button
void MainWindow::on_AddMarkingRangeButton_clicked()
{
    //verify each input for empty value, or non-int value
    ui->errorWindow->setTextColor(Qt::red); //set text color to red in case we need to output errors
    ui->errorWindow->clear();
    ui->errorWindow->hide();
    errorOccured = false;

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

    if(!invalidChar(input_8)){
        errorOccured = true;
        ui->errorWindow->show();
        ui->errorWindow->setText(ui->errorWindow->toPlainText() + "ERROR: Mark At has invalid characters\n");
    }

    else if(isInt(input_8)){ //verify that the value to be inputted is an int

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
        ui->errorWindow->setText(ui->errorWindow->toPlainText() + "ERROR: Marking range is not a whole number\n");
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

//check if any errors exist before we attempt to calculate timeline.
bool MainWindow::CalculateTimelineErrors(int timelineType, string *inputs){
    //timeline types: 0 == continuous, 1 == interrupted(standard), 2 == non-standard
    bool errorOccurred = false;//if we encounter an error, this will later be set to true

    string CAS_TOT = inputs[0];//CAS TOT value
    string Supp_TOF = inputs[1];//Supp TOF value
    string Supp_Fire_Freq = inputs[2];//Supp Fire Freq value
    string Marking_TOF = inputs[3];//Marking TOF value
    string Supp_Firing_Range_lower = inputs[4];//Supp Firing range (lower value)
    string Supp_Firing_Range_upper = inputs[5];//Supp Firing range (upper value)
    string Mark_At = inputs[6];//'Mark at' value

    //verify each input for empty value, or non-int value
    ui->errorWindow->setTextColor(Qt::red); //set text color to red in case we need to output errors
    ui->errorWindow->clear();
    ui->errorWindow->hide();

    //checks for CAS TOT
    if(!isInt(CAS_TOT)){//is CAS_TOT an integer?
        errorOccurred = true;
        ui->errorWindow->setText(ui->errorWindow->toPlainText() + "ERROR: TOT is not a whole number\n");
    }
    if(!invalidChar(CAS_TOT)){//does CAS_TOT contain an invalid character?
        errorOccurred = true;
        ui->errorWindow->setText(ui->errorWindow->toPlainText() + "ERROR: TOT contains invalid characters\n");
    }
    if(!check4neg(CAS_TOT)){//is CAS_TOT a negative number?
        errorOccurred = true;
        ui->errorWindow->setText(ui->errorWindow->toPlainText() + "ERROR: TOT must be a postive number\n");
    }

    //checks for Sup TOF
    if(!isInt(Supp_TOF)){//is Supp_TOF an integer?
        errorOccurred = true;
        ui->errorWindow->setText(ui->errorWindow->toPlainText() + "ERROR: SUP TOF is not a whole number\n");
    }
    if(!invalidChar(Supp_TOF)){//does Supp_TOF contain an invalid character?
        errorOccurred = true;
        ui->errorWindow->setText(ui->errorWindow->toPlainText() + "ERROR: SUP TOF contains invalid characters\n");
    }
    if(!check4neg(Supp_TOF)){//is SUP_TOF a negative number?
        errorOccurred = true;
        ui->errorWindow->setText(ui->errorWindow->toPlainText() + "ERROR: SUP TOT must be a postive number\n");
    }

    //checks for FF
    if(!isInt(Supp_Fire_Freq) && (timelineType == 2)){//non-standard only
        errorOccurred = true;
        ui->errorWindow->setText(ui->errorWindow->toPlainText() + "ERROR: Fire Frequency is not a whole number\n");
    }
    if(!invalidChar(Supp_Fire_Freq) && (timelineType == 2)){//non-standard only
        errorOccurred = true;
        ui->errorWindow->setText(ui->errorWindow->toPlainText() + "ERROR: Fire Frequency contains invalid characters\n");
    }
    if(!check4neg(Supp_Fire_Freq)){//is FF a negative number?
        errorOccurred = true;
        ui->errorWindow->setText(ui->errorWindow->toPlainText() + "ERROR: Fire Frequency must be a postive number\n");
    }

    //checks for Mark TOF
    if(ui->MarkingSelector->currentIndex() != 0 && !isInt(Marking_TOF)){
        errorOccurred = true;
        ui->errorWindow->setText(ui->errorWindow->toPlainText() + "ERROR: Marking TOF is not a whole number\n");
    }
    if(!invalidChar(Marking_TOF)){
        errorOccurred = true;
        ui->errorWindow->setText(ui->errorWindow->toPlainText() + "ERROR: Marking TOF contains invalid characters\n");
    }
    if(!check4neg(Marking_TOF)){//is CAS_TOT a negative number?
        errorOccurred = true;
        ui->errorWindow->setText(ui->errorWindow->toPlainText() + "ERROR: Marking TOF must be a postive number\n");
    }

    //check selctor for Marking Type
    if(ui->MarkingSelector->currentIndex() == -1){//is marking shell selected?
        errorOccurred = true;
        ui->errorWindow->setText(ui->errorWindow->toPlainText() + "ERROR: Marking shell is not selected\n");
    }

    if(frVec.empty() && (timelineType == 2)){//non-standard only
        errorOccurred = true;
        ui->errorWindow->setText(ui->errorWindow->toPlainText() + "ERROR: Add Suppress Range\n");
    }
    if(frVecMark.empty() && (ui->MarkingSelector->currentIndex() != 0) && (timelineType == 2)){//non-standard only
        errorOccurred = true;
        ui->errorWindow->setText(ui->errorWindow->toPlainText() + "ERROR: Add Marking Range\n");
    }

    //if an error occurred, make error window visible to show messages
    if(errorOccurred)
        ui->errorWindow->show();
    return errorOccurred;
}

//event handler for when the calculate timeline button is clicked
//must either display a valid timeline, or return an error message
void MainWindow::on_CalculateTimelineButton_clicked()
{
    //gunIndex tells us which timeline window we should write into
    //clear timeline for the current gun
    ClearTimeline(gunIndex);

    //we must first determine which firing mode is selected, so we can do input verification on the correct input boxes
    string inputs[7];//these will hold the inputs to pass them as parameter more easily
    inputs[0] = ui->input_1->text().toStdString();//CAS TOT
    inputs[1] = ui->input_2->text().toStdString();//Supp TOF
    inputs[2] = ui->input_3->text().toStdString();//Supp Fire Freq
    inputs[3] = ui->input_5->text().toStdString();//Marking TOF
    inputs[4] = ui->input_6->text().toStdString();//Supp Firing range (lower)
    inputs[5] = ui->input_7->text().toStdString();//Supp firing range (upper)
    inputs[6] = ui->input_8->text().toStdString();//'Mark at'

    errorOccured = CalculateTimelineErrors(ui->fireTypeSelector->currentIndex(), inputs);

    //calculations for continuous and interrupted
    ui->errorWindow->setTextColor(Qt::black);   //errors have been printed, set text color back to black
    ui->errorWindow->clear();
    ui->errorWindow->hide();

    errorOccured = false;

    markingType mt = NEGATIVE;
    if(ui->MarkingSelector->currentIndex() == 1){ mt = ILLUM; }
    else if(ui->MarkingSelector->currentIndex() == 2){ mt = WP; }

    string testLine;
    if(!errorOccured){
        //handle continuous and interrupted timelines
        if(ui->fireTypeSelector->currentIndex() == 1 || ui->fireTypeSelector->currentIndex() == 2){

            timelineType tt;
            if(ui->fireTypeSelector->currentIndex() == 1){ tt = INTERRUPTED; }
            else{tt = CONTINUOUS; }

            if(tt == CONTINUOUS){printInput[gunIndex].tLineType = " Continuous  ==================================";}
            else if(tt == INTERRUPTED){printInput[gunIndex].tLineType = " Interrupted  ==================================";}
            else{printInput[gunIndex].tLineType = " NEGATIVE  ==================================";}

            if(mt == NEGATIVE){ inputs[3] = "0"; }//set Supp_Fire_Freq to 0
            Standard_Timeline timeline = Standard_Timeline(stoi(inputs[0]), stoi(inputs[1]), mt, stoi(inputs[3]), tt);//CAS_TOT, Supp_TOF, Marking_TOF
            testLine = timeline.print();
        }

        //handle non-standard timelines
        else if(ui->fireTypeSelector->currentIndex() == 2){
            if(mt == NEGATIVE){ inputs[3] = "0"; }//Marking_TOF
            NonStandard_Timeline timeline = NonStandard_Timeline(stoi(inputs[0]), stoi(inputs[1]), stoi(inputs[3]), frVec, stoi(inputs[2]));//CAS_TOT, Supp_TOF, Marking_TOF, Supp_Fire_Freq
            for(int num : frVecMark){ timeline.addMarkingRound(mt, num); }
            testLine = timeline.print();

            printInput[gunIndex].tLineType = " Non-Standard  ==================================";
            printInput[gunIndex].supFF = ui->input_3->text().toStdString();
            printInput[gunIndex].supFR = "";
            for(fireRange i : frVec){
                printInput[gunIndex].supFR += "(" + to_string(i.startMin);
                printInput[gunIndex].supFR += "," + to_string(i.endMin) + ") ";
            }

            //remove extra space at the end
            printInput[gunIndex].supFR.pop_back();
            printInput[gunIndex].mAt = "";

            for(int i : frVecMark){ printInput[gunIndex].mAt += to_string(i); printInput[gunIndex].mAt += ", "; }

            //remove extra space and comma at the end
            printInput[gunIndex].mAt.pop_back();
            printInput[gunIndex].mAt.pop_back();
        }

        char test[testLine.size()+1];
        testLine.copy(test,testLine.size()+1);
        test[testLine.size()] = '\0';
        QString x = test;

        TimelineDisplayGuns[gunIndex]->clear();//clear any previous output
        string text = "Gun " + to_string(gunIndex+1) + " Timeline\n\n";
        TimelineDisplayGuns[gunIndex]->setText(text.c_str() + x);//write our content to the QTextBrowser
        TimelineDisplayGuns[gunIndex]->setAlignment(Qt::AlignCenter);

        printInput[gunIndex].casTOT = ui->input_1->text().toStdString();
        printInput[gunIndex].supTOF = ui->input_2->text().toStdString();

        if(mt == WP){printInput[gunIndex].mType = "WP";}
        else if(mt == ILLUM){printInput[gunIndex].mType = "ILLUM";}
        else{printInput[gunIndex].mType = "NEGATIVE";}

        printInput[gunIndex].mTOF = ui->input_5->text().toStdString();
        printInput[gunIndex].tLineNum = "==================================  Gun " + to_string(gunIndex+1) + " Timeline";
        printInput[gunIndex].tLineNum += printInput[gunIndex].tLineType;

        tLineArry[gunIndex] += x.toStdString();
    }
}

void MainWindow::selectGun(int index){
    switch(index){
        case 1:
            currentGun = &gun1;
            gunIndex = 0;
            break;
        case 2:
            currentGun = &gun2;
            gunIndex = 1;
            break;
        case 3:
            currentGun = &gun3;
            gunIndex = 2;
            break;
        case 4:
            currentGun = &gun4;
            gunIndex = 3;
            break;
        case 5:
            currentGun = &gun5;
            gunIndex = 4;
            break;
        case 6:
            currentGun = &gun6;
            gunIndex = 5;
            break;
    }
    ui->errorWindow->clear();
    ui->errorWindow->hide();
}

//gun 1 is selected, load all gun 1 data into the displays
void MainWindow::on_Gun_1_button_clicked(){
    selectGun(1);
}

//gun 2 is selected, load all gun 2 data into the displays
void MainWindow::on_Gun_2_button_clicked(){
    selectGun(2);
}

//gun 3 is selected, load all gun 3 data into the displays
void MainWindow::on_Gun_3_button_clicked(){
    selectGun(3);
}

//gun 4 is selected, load all gun 4 data into the displays
void MainWindow::on_Gun_4_button_clicked(){
    selectGun(4);
}

//gun 5 is selected, load all gun 5 data into the displays
void MainWindow::on_Gun_5_button_clicked(){
    selectGun(5);
}

//gun 6 is selected, load all gun 6 data into the displays
void MainWindow::on_Gun_6_button_clicked(){
    selectGun(6);
}

//behavior for the clear button, clears all fields
void MainWindow::on_clearButton_clicked(){
    ui->errorWindow->clear();
    ui->errorWindow->hide();

    ui->FiringRangesDisplay->clear();
    ui->FiringRangesDisplay->setText("Suppress From:");

    ui->MarkingRangesDisplay->clear();
    ui->MarkingRangesDisplay->setText("Mark With:");

    ui->input_1->clear();
    ui->input_2->clear();
    ui->input_3->clear();
    ui->input_5->clear();
    ui->input_6->clear();
    ui->input_7->clear();
    ui->input_8->clear();

    ui->fileNameInput->clear();

    frVec.clear();
    frVecMark.clear();
}

//handles clearing a singular timeline window and its associated data
void MainWindow::ClearTimeline(int index){
    TimelineDisplayGuns[index]->clear();
    string text = "Gun " + to_string(index+1) + " Timeline\n\n";
    TimelineDisplayGuns[index]->setText(text.c_str());
    TimelineDisplayGuns[index]->setAlignment(Qt::AlignCenter);
    tLineArry[index] = "";
    clearPrintInputs(index);
}

void MainWindow::on_clearButtonGuns_clicked(){
    ui->errorWindow->clear();
    ui->errorWindow->hide();

    ui->fileNameInput->clear();
    fiName = "NA";

    for(int i = 0; i < 6; i++){
        ClearTimeline(i);
    }
}

bool MainWindow::isInt(string input){ try{ stoi(input); } catch (...) { return false; } return true; }

bool MainWindow::invalidChar(string input2){
    string test;

    int s1 = input2.length();

    for(int i = 0; i < s1; i++){
        test = "";

        if((input2[0] == '-' || input2[0] == '+') && i == 0){ i++; }

        test += input2[i];

        if(!isInt(test)){ return false; }
    }
    return true;
}

bool MainWindow::invalidChar2(string input3){
    int s2 = input3.length();

    for(int i = 0; i < s2; i++){
        if(input3[i] == '\\'
        || input3[i] == '/'
        || input3[i] == ':'
        || input3[i] == '<'
        || input3[i] == '>'
        || input3[i] == '"'
        || input3[i] == '<'){ return false; }
    }
    return true;
}

bool MainWindow::check4neg(string input1){
    if(input1[0] == '-'){ return false; }
    return true;
}

void MainWindow::on_RemoveSingleRange_clicked(){
    //remove the line from the firing ranges list, first check to see if the firing ranges is empty
    if(frVec.size() != 0){
        frVec.pop_back();

        string firingRangesText = ui->FiringRangesDisplay->toPlainText().toStdString();
        string newFiringRanges = firingRangesText.substr(0, firingRangesText.find_last_of("\n"));
        ui->FiringRangesDisplay->setText(QString::fromStdString(newFiringRanges));
    }
}


void MainWindow::on_RemoveSingleMarking_clicked(){
    //remove the line from the marking ranges list, first check to see if the firing ranges is empty
    if(frVecMark.size() != 0){
        frVecMark.pop_back();

        string markingRangesText = ui->MarkingRangesDisplay->toPlainText().toStdString();
        string newMarkingRanges = markingRangesText.substr(0, markingRangesText.find_last_of("\n"));
        ui->MarkingRangesDisplay->setText(QString::fromStdString(newMarkingRanges));
    }
}

void MainWindow::on_ClearTimeline1_clicked(){
    ClearTimeline(0);
}


void MainWindow::on_ClearTimeline2_clicked(){
    ClearTimeline(1);
}


void MainWindow::on_ClearTimeline3_clicked(){
    ClearTimeline(2);
}


void MainWindow::on_ClearTimeline4_clicked(){
    ClearTimeline(3);
}


void MainWindow::on_ClearTimeline5_clicked(){
    ClearTimeline(4);
}


void MainWindow::on_ClearTimeline6_clicked(){
    ClearTimeline(5);
}
