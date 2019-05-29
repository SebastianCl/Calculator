#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Calculadora");

    connect(ui->btn0,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->btn1,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->btn2,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->btn3,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->btn4,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->btn5,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->btn6,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->btn7,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->btn8,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->btn9,SIGNAL(released()),this,SLOT(digit_pressed()));

    connect(ui->btnPlusMinus,SIGNAL(released()),this,SLOT(unary_operation_pressed()));
    connect(ui->btnPercentage,SIGNAL(released()),this,SLOT(unary_operation_pressed()));

    connect(ui->btnMore,SIGNAL(released()),this,SLOT(binary_operation_pressed()));
    connect(ui->btnLess,SIGNAL(released()),this,SLOT(binary_operation_pressed()));
    connect(ui->btnMultiply,SIGNAL(released()),this,SLOT(binary_operation_pressed()));
    connect(ui->btnDivide,SIGNAL(released()),this,SLOT(binary_operation_pressed()));

    ui->btnMore->setCheckable(true);
    ui->btnLess->setCheckable(true);
    ui->btnMultiply->setCheckable(true);
    ui->btnDivide->setCheckable(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

//Un numero es presionado
void MainWindow::digit_pressed()
{
    QPushButton * button = (QPushButton*)sender();

    double lblNumber;
    QString lblNew;

    if(
        (ui->btnMore->isChecked() ||
        ui->btnLess->isChecked() ||
        ui->btnMultiply->isChecked() ||
        ui->btnDivide->isChecked())
        && (!typingSecondNumber))
    {
        lblNumber = button->text().toDouble();
        typingSecondNumber = true;
        lblNew = QString::number(lblNumber,'g',15);
    }
    else
    {
        if(
            ui->lblResult->text().contains('.')
            && button->text() == "0")
        {
            lblNew = ui->lblResult->text() + button->text();

        }
        else
        {
            lblNumber = (ui->lblResult->text() + button->text()).toDouble();
            lblNew = QString::number(lblNumber,'g',15);
        }
    }

    ui ->lblResult->setText(lblNew);
}

void MainWindow::on_btnPoint_released()
{
    if (!(ui->lblResult->text().contains('.')))
    {
        ui->lblResult->setText(ui->lblResult->text() + ".");
    }
}

void MainWindow::unary_operation_pressed()
{
    QPushButton * button = (QPushButton*) sender();
    double lblNumber;
    QString lblNew;

    if(button->text() == "+/-")
    {
        lblNumber = ui->lblResult->text().toDouble();
        lblNumber = lblNumber * -1;
        lblNew = QString::number(lblNumber,'g',15);
        ui->lblResult->setText(lblNew);
    }

    if(button->text() == "%")
    {
        lblNumber = ui->lblResult->text().toDouble();
        lblNumber = lblNumber * 0.01;
        lblNew = QString::number(lblNumber,'g',15);
        ui->lblResult->setText(lblNew);
    }
}


void MainWindow::on_btnClear_released()
{
    ui->btnMore->setChecked(false);
    ui->btnLess->setChecked(false);
    ui->btnMultiply->setChecked(false);
    ui->btnDivide->setChecked(false);

    typingSecondNumber = false;
    ui->lblResult->setText("0");
}


void MainWindow::on_btnEquals_released()
{
    double lblNumber, secondNum;
    QString lblNew,n2;
    n2 = ui->lblResult->text();

    secondNum = n2.toDouble();

    if(ui->btnMore->isChecked())
    {
        lblNumber = firstNum + secondNum;
        lblNew = QString::number(lblNumber,'g',15);
        ui->lblResult->setText(lblNew);
        ui->btnMore->setChecked(false);
    }
    else if (ui->btnLess->isChecked())
    {
        lblNumber = firstNum - secondNum;
        lblNew = QString::number(lblNumber,'g',15);
        ui->lblResult->setText(lblNew);
        ui->btnLess->setChecked(false);
    }
    else if (ui->btnMultiply->isChecked())
    {
        lblNumber = firstNum * secondNum;
        lblNew = QString::number(lblNumber,'g',15);
        ui->lblResult->setText(lblNew);
        ui->btnMultiply->setChecked(false);

    }
    else if (ui->btnDivide->isChecked())
    {
        if(secondNum == 0)
        {
            ui->lblResult->setText("Math ERROR");
        }
        else
        {
            lblNumber = firstNum / secondNum;
            lblNew = QString::number(lblNumber,'g',15);
            ui->lblResult->setText(lblNew);
            ui->btnDivide->setChecked(false);
        }

    }
    typingSecondNumber = false;

}


//Guardar operacion a ejecutar y primer numero
void MainWindow::binary_operation_pressed()
{
    QString n1;
    n1 = ui->lblResult->text();
    QPushButton *button = (QPushButton*)sender();
    firstNum = n1.toDouble();
    button->setChecked(true);
}





