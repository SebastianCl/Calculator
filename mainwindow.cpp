#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Calculadora");

    //Establecer el mismo metodo (ranura o slot) para los botones 0-9
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

    //Establecer el mismo metodo (ranura o slot) para los botones de operación (+-x/)
    connect(ui->btnMore,SIGNAL(released()),this,SLOT(binary_operation_pressed()));
    connect(ui->btnLess,SIGNAL(released()),this,SLOT(binary_operation_pressed()));
    connect(ui->btnMultiply,SIGNAL(released()),this,SLOT(binary_operation_pressed()));
    connect(ui->btnDivide,SIGNAL(released()),this,SLOT(binary_operation_pressed()));


    //Esta propiedad (setCheckable) permite que los botones sean verificables
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
    //Aqui se construye el objeto button del boton presionado (0-9)
    QPushButton * button = (QPushButton*)sender();

    double lblNumber;
    QString lblNew;

    //NUMERO A MOSTRAR EN PANTALLA:

    //Si es el primer digito presionado
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
    //Si hay más de un digito siempre entra aqui
    else
    {
        //Si se esta escribiendo un número decimal
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

    //Mostrar número escrito
    ui ->lblResult->setText(lblNew);
}


//Agregar punto decimal
void MainWindow::on_btnPoint_released()
{
    //Valida que solo se use un punto
    if (!(ui->lblResult->text().contains('.')))
    {
        ui->lblResult->setText(ui->lblResult->text() + ".");
    }
}


//Guardar operacion a ejecutar y guardar primer número
void MainWindow::binary_operation_pressed()
{
    //Aqui se construye el objeto button del boton presionado (+-x/)
    QPushButton *button = (QPushButton*)sender();
    firstNum = ui->lblResult->text().toDouble();
    button->setChecked(true);
}

//Igual
void MainWindow::on_btnEquals_released()
{
    double lblNumber, secondNum;
    QString lblNew;

    //Obtener segundo número
    secondNum = ui->lblResult->text().toDouble();

    //Validar si es suma
    if(ui->btnMore->isChecked())
    {
        lblNumber = firstNum + secondNum;
        lblNew = QString::number(lblNumber,'g',15);
        ui->lblResult->setText(lblNew);
        ui->btnMore->setChecked(false);
    }
    //Validar si es resta
    else if (ui->btnLess->isChecked())
    {
        lblNumber = firstNum - secondNum;
        lblNew = QString::number(lblNumber,'g',15);
        ui->lblResult->setText(lblNew);
        ui->btnLess->setChecked(false);
    }
    //Validar si es multiplicación
    else if (ui->btnMultiply->isChecked())
    {
        lblNumber = firstNum * secondNum;
        lblNew = QString::number(lblNumber,'g',15);
        ui->lblResult->setText(lblNew);
        ui->btnMultiply->setChecked(false);

    }
    //Valida si es división
    else if (ui->btnDivide->isChecked())
    {
        //Validar división por cero
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


//Concatenar signo negativo
void MainWindow::on_btnPlusMinus_clicked()
{
    double lblNumber;
    QString lblNew;

    lblNumber = ui->lblResult->text().toDouble();
    lblNumber = lblNumber * -1;
    lblNew = QString::number(lblNumber,'g',15);
    ui->lblResult->setText(lblNew);
}

//Reiniciar calculadora
void MainWindow::on_btnClear_released()
{
    ui->btnMore->setChecked(false);
    ui->btnLess->setChecked(false);
    ui->btnMultiply->setChecked(false);
    ui->btnDivide->setChecked(false);

    typingSecondNumber = false;
    ui->lblResult->setText("0");
}

