#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    double firstNum;
    bool typingSecondNumber = false;

private slots:
    void digit_pressed();
    void on_btnPoint_released();
    void on_btnClear_released();
    void on_btnEquals_released();
    void binary_operation_pressed();
    void on_btnPlusMinus_clicked();
};

#endif // MAINWINDOW_H
