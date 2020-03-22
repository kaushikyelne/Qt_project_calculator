#include "calculator.h"
#include "ui_calculator.h"

double calcVal = 0.0;
bool divTrigger = false;
bool mulTrigger = false;
bool addTrigger = false;
bool subTrigger = false;

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);

    ui->Display->setText(QString::number(calcVal));
    QPushButton *numButtons[10];
    for(int i = 0; i < 10;++i)
    {
        QString butName = "Button" + QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton *>(butName);
        connect(numButtons[i], SIGNAL(released()), this,
                SLOT(NumPressed()));
    }
    connect(ui->zeroes ,SIGNAL(released()), this,
            SLOT(zerozeroButtonPressed()));
    connect(ui->Add, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Subtract, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Multiply, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Divide, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Equals, SIGNAL(released()), this,
            SLOT(EqualButtonPressed()));
    connect(ui->Signchange, SIGNAL(released()), this,
            SLOT(ChangeNumberSign()));
    connect(ui->Allclear, SIGNAL(released()), this,
            SLOT(ClearButtonPressed()));
    connect(ui->Decimal, SIGNAL(released()), this,
            SLOT(Deci()));
    connect(ui->Delet, SIGNAL(released()), this,
            SLOT(Delete()));
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::NumPressed()
{
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    QString displayVal = ui->Display->text();
    if((displayVal.toDouble() == 0) || (displayVal.toDouble() == 0.0))
    {
            ui->Display->setText(butVal);
    }
     else {
            QString newVal = displayVal + butVal;
            double dblnewVal = newVal.toDouble();
            ui->Display->setText(QString::number(dblnewVal));
            }

}



void Calculator::MathButtonPressed()
{
    divTrigger = false;
    mulTrigger = false;
    addTrigger = false;
    subTrigger = false;
    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    if(QString::compare(butVal, "/",Qt::CaseInsensitive) == 0)
    {
        divTrigger = true;
    }
    else if(QString ::compare(butVal, "*",Qt::CaseInsensitive) == 0)
    {
        mulTrigger = true;
    }
    else if(QString::compare(butVal, "+",Qt::CaseInsensitive) == 0)
    {
        addTrigger = true;
    }
    else
    {
        subTrigger = true;
    }

    ui->Display->setText("");
}

void Calculator::EqualButtonPressed()
{
    double solution = 0.0;
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    if(addTrigger || subTrigger || mulTrigger || divTrigger)
    {
        if(addTrigger)
        {
            solution = calcVal + dblDisplayVal;
        } else if(subTrigger)
        {
            solution = calcVal - dblDisplayVal;
        } else if(mulTrigger)
        {
            solution = calcVal * dblDisplayVal;
        } else
        {
            solution = calcVal / dblDisplayVal;
        }

    }
    ui->Display->setText(QString::number(solution));
}

void Calculator::zerozeroButtonPressed()
{

    double butVal = 0.0;
    QString displayVal = ui->Display->text();
    butVal = displayVal.toDouble();
////    if((displayVal.toDouble() == 0) || (displayVal.toDouble() == 0.0))
////    {
////            ui->Display->setText("00");
////    }
////     else {

//            double dblnewVal = displayVal.toDouble();
            displayVal= displayVal+"00";
            butVal= butVal * 100;
            double newdisplVal = displayVal.toDouble();
            ui->Display->setText(QString::number(newdisplVal));


}
void Calculator::ChangeNumberSign()
{
    QString displayVal = ui->Display->text();
    QRegExp reg("[-]?[0-9.]*");
    if(reg.exactMatch(displayVal)){
        double dblDisplayVal = displayVal.toDouble();
        double dblDisplayValSign = -1 * dblDisplayVal;
        ui->Display->setText(QString::number(dblDisplayValSign));

    }

}

void Calculator:: ClearButtonPressed()
{
    ui->Display->setText("");
}

void Calculator:: Deci()
{
    QString displayVal = ui->Display->text();
    displayVal = displayVal + ".";
    ui->Display->setText(displayVal);
}

void Calculator::Delete()
{
    QString displayVal = ui->Display->text();
//    int pos = displayVal.lastIndexOf(QChar(*));
//    displayVal.left(pos);
    displayVal.chop(1);
    ui->Display->setText(displayVal);
}
