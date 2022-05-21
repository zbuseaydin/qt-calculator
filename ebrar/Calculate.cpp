#include "Calculate.h"
#include "ui_Calculate.h"

long result = 0;                // stores the result of the operation in decimal

bool addPressed = false;
bool subPressed = false;
bool endOfNum = false;
bool ok;  // a dumb variable to use toLong method of QString for hexadecimal numbers
bool firstOperation = true;     // when the first operator (+ or -) is pressed, the first number given will be transferred to result

Calculate::Calculate(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::Calculate)
{
    ui->setupUi(this);

    ui->Display->setText(QString::number(result));

    QPushButton *numButtons[16];
    for(int i = 0; i < 10; i++){
        QString butName = "button" + QString::number(i);            // button names should be like button0, ... button15 in .ui
        numButtons[i] = Calculate::findChild<QPushButton *>(butName);
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumberPressed()));
    }

    int ch = 65;
    for(int i = 10; i < 16; i++, ch++){
        QString butName = "button" + QString(QChar(ch));
        numButtons[i] = Calculate::findChild<QPushButton *>(butName);
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumberPressed()));
    }

    connect(ui->addition, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->subtraction, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->equals, SIGNAL(released()), this, SLOT(EqualButtonPressed()));
    connect(ui->clear, SIGNAL(released()), this, SLOT(ClearPressed()));
}


Calculate::~Calculate()
{
    delete ui;
}


void Calculate::NumberPressed(){
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();                // button being pressed
    QString displayVal = ui->Display->text();       // current displayed value in String
//    long displayValue = displayVal.toLong(&ok, 16);

    // if the previous number is finished or the current display is 0, only the current number is displayed:
    if(endOfNum || (displayVal == "0")){
        ui->Display->setText(butVal);
    }
    // else: the new number is concatenated to previous display:
    else{
        QString newVal = displayVal + butVal;
        ui->Display->setText(newVal);
    }

    endOfNum = false;
}


void Calculate::MathButtonPressed(){

    // Get value from display
    QString displayVal = ui->Display->text();
    long displayValue = displayVal.toLong(&ok, 16);

    if(firstOperation){
        result = displayValue;
        firstOperation = false;
    }
    // First check whether a button is pressed before:
    if(addPressed){
        // result stores the previous value
        result = result + displayValue;
        QString newDisplay = QString::number(result, 16).toUpper();
        // display the result of the last operation:
        ui->Display->setText(newDisplay);
    } else if(subPressed){
        // result stores the previous value
        result = result - displayValue;
        QString newDisplay = QString::number(result, 16).toUpper();
        // display the result of the last operation:
        ui->Display->setText(newDisplay);
    }

    // Cancel out previous math button clicks
    addPressed = false;
    subPressed = false;

    // Sender returns a pointer to the button pressed
    QPushButton *button = (QPushButton *)sender();

    // Get math symbol on the button
    QString butVal = button->text();

    if(QString::compare(butVal, "+", Qt::CaseInsensitive) == 0){
        addPressed = true;
    } else {
        subPressed = true;
    }

    // end of number:
    endOfNum = true;

}



void Calculate::EqualButtonPressed(){

    // Get value in display
    QString displayVal = ui->Display->text();
    long dblDisplayVal = displayVal.toLong(&ok, 16);    // displayed value in decimal

    // process the last operation pressed:
    if(addPressed){
        result = result + dblDisplayVal;
    } else if(subPressed){
        result = result - dblDisplayVal;
    }

    // Put result in display
    ui->Display->setText(QString::number(result, 16).toUpper());

}


void Calculate::ClearPressed(){
    ui->Display->setText("");
    result = 0;
}
