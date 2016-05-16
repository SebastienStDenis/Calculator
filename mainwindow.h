#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QGridLayout>
#include <QSignalMapper>
#include <QShortcut>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void num_clicked(const QString&);
    void op_clicked(const QString&);

private slots:

    // num_press(text) adds text to the lower display, where text is
    //    the number of the button that was pressed
    void num_press(const QString&);

    // op_press() adds the current lower display number to the upper
    //    display and adds the operator op aftwerwards
    void op_press(const QString&);

    // dot_press() adds a decimal point to the number in the lower display
    void dot_press();

    // neg_press() toggles the number in the lower display
    //    between negative and positive
    void neg_press();

    // eq_press() shows the final answer in the lower display, clears the upper display
    void eq_press();

    // ce_press() sets the lower display to 0
    void ce_press();

    // c_press sets the lower siplay to 0 and clears the upper display

    void c_press();

    // back_press() removes the last character on the lower display
    void back_press();

private:
    Ui::MainWindow *ui;

    // result stores the current value of the equation
    double result = 0;

    // pre_op stores the value of the current last operator
    //    selected (from +, -, *, /), or empty if there is none
    QString pre_op = "";

    // new_num is true when no number is being inputted
    //    into the lower display, false otherwise
    bool new_num = true;

    // dot_pressed is true when the current number being
    //    inputted contains a decimal point, false otherwise
    bool dot_pressed = false;

    // numpad_setup() creates and positions the buttons from 0 to 9
    void numpad_setup();

    // display_setup() creates and positions both displays
    void display_setup();

    // op_setup() creates and positions the operator (and decimal) buttons
    void op_setup();

    // other_setup() creates and positions the equal, C, CE, and backspace buttons
    void other_setup();

    // shortcut_setup() creates the shortcuts for all the buttons
    void shortcut_setup();

    // calculate() returns the current total value, including
    //    the number in the lower display
    double calculate();

    // set_text(val) sets the text of the lower display to
    //    val, with 6 decimal places max
    void set_text(double);

    // set_new_num(new_n) changes the value of the new_num member to newN and
    //    modifies the appearance of the lower display border accordingly
    void set_new_num(bool);

    // ui elements:

    // upper_d is the upper display, which shows the
    //    current equstion
    QLineEdit *upper_d;

    // lower_d is the lower display, which shows the
    //    current number being entered
    QLineEdit *lower_d;

    // numbers from 0 to 9
    QPushButton *numbers[10];

    // signal mapper for numbers
    QSignalMapper *num_mapper;

    // decimal point button
    QPushButton *b_dot;

    // negative/positive toggle button
    QPushButton *b_neg;

    // buttons for the four binary ops
    QPushButton *plus;
    QPushButton *minus;
    QPushButton *mult;
    QPushButton *div;

    // signal mapper for the four binary ops
    QSignalMapper *op_mapper;

    // equal button
    QPushButton *eq;

    // CE button (clear current number)
    QPushButton *CE;

    // C button (clears everything)
    QPushButton *C;

    // backspace button
    QPushButton *back;

    //shortcuts for each button:
    QShortcut *s0;
    QShortcut *s1;
    QShortcut *s2;
    QShortcut *s3;
    QShortcut *s4;
    QShortcut *s5;
    QShortcut *s6;
    QShortcut *s7;
    QShortcut *s8;
    QShortcut *s9;
    QShortcut *sDot;
    QShortcut *sNeg;
    QShortcut *sPlus;
    QShortcut *sPlus2;
    QShortcut *sMinus;
    QShortcut *sMult;
    QShortcut *sMult2;
    QShortcut *sDiv;
    QShortcut *sEq;
    QShortcut *sEq2;
    QShortcut *sEq3;
    QShortcut *sCE;
    QShortcut *sC;
    QShortcut *sBack;
};

#endif // MAINWINDOW_H
