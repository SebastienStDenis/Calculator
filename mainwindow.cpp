#include <QString>
#include <QGridLayout>
#include <Qt>
#include <QSignalMapper>
#include "mainwindow.h"
#include "ui_mainwindow.h"

// SEE MAINWINDOW.H FOR DOCUMENTATION


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget::setWindowTitle("Calculator");

    setFixedSize(235, 340);

    numpad_setup();
    display_setup();
    op_setup();
    other_setup();
    shortcut_setup();
}


MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::numpad_setup() {
    num_mapper = new QSignalMapper(this);

    for (int i = 0; i < 10; ++i) { // create button, set up the mapping
        numbers[i] = new QPushButton(QString::number(i), this);
        connect(numbers[i], SIGNAL(clicked()), num_mapper, SLOT(map()));
        num_mapper->setMapping(numbers[i], numbers[i]->text());
    }

    int x = 30;
    int y = 225;
    for (int i = 1; i < 10; ++i) {
        numbers[i]->setGeometry(x, y, 40, 40);
        if (i % 3 == 0) {
            x = 30;
            y -= 45;
        } else {
            x += 45;
        }
    }
    numbers[0]->setGeometry(75, 270, 40, 40);

    connect(num_mapper, SIGNAL(mapped(const QString&)), this, SIGNAL(num_clicked(const QString&)));
    connect(this, SIGNAL(num_clicked(const QString&)), this, SLOT(num_press(const QString &)));
}


void MainWindow::display_setup() {
    upper_d = new QLineEdit(this);
    lower_d = new QLineEdit("0", this);

    upper_d->setGeometry(30, 30, 175, 25);
    upper_d->setAlignment(Qt::AlignRight);
    upper_d->setReadOnly(true);
    lower_d->setGeometry(30, 60, 175, 25);
    lower_d->setAlignment(Qt::AlignRight);
    lower_d->setReadOnly(true);
    lower_d->setFrame(false);
}


void MainWindow::op_setup() {
    b_dot = new QPushButton(".", this);
    connect(b_dot, SIGNAL(clicked()), this, SLOT(dot_press()));
    b_dot->setGeometry(120, 270, 40, 40);

    b_neg = new QPushButton("-/+", this);
    connect(b_neg, SIGNAL(clicked()), this, SLOT(neg_press()));
    b_neg->setGeometry(30, 270, 40, 40);

    op_mapper = new QSignalMapper(this);

    plus = new QPushButton("+", this);
    connect(plus, SIGNAL(clicked()), op_mapper, SLOT(map()));
    op_mapper->setMapping(plus, plus->text());

    minus = new QPushButton("-", this);
    connect(minus, SIGNAL(clicked()), op_mapper, SLOT(map()));
    op_mapper->setMapping(minus, minus->text());

    mult = new QPushButton("*", this);
    connect(mult, SIGNAL(clicked()), op_mapper, SLOT(map()));
    op_mapper->setMapping(mult, mult->text());

    div = new QPushButton("/", this);
    connect(div, SIGNAL(clicked()), op_mapper, SLOT(map()));
    op_mapper->setMapping(div, div->text());

    connect(op_mapper, SIGNAL(mapped(const QString&)), this, SIGNAL(op_clicked(const QString&)));
    connect(this, SIGNAL(op_clicked(const QString&)), this, SLOT(op_press(const QString&)));

    plus->setGeometry(165, 90, 40, 40);
    minus->setGeometry(165, 135, 40, 40);
    mult->setGeometry(165, 180, 40, 40);
    div->setGeometry(165, 225, 40, 40);
}


void MainWindow::other_setup() {
    eq = new QPushButton("=", this);
    connect(eq, SIGNAL(clicked()), this, SLOT(eq_press()));
    eq->setGeometry(165, 270, 40, 40);

    CE = new QPushButton("CE", this);
    connect(CE, SIGNAL(clicked()), this, SLOT(ce_press()));
    CE->setGeometry(30, 90, 40, 40);

    C = new QPushButton("C", this);
    connect(C, SIGNAL(clicked()), this, SLOT(c_press()));
    C->setGeometry(75, 90, 40, 40);

    back = new QPushButton("<", this);
    connect(back, SIGNAL(clicked()), this, SLOT(back_press()));
    back->setGeometry(120, 90, 40, 40);
}


void MainWindow::shortcut_setup() {
    s0 = new QShortcut(Qt::Key_0, numbers[0], SIGNAL(clicked()));
    s1 = new QShortcut(Qt::Key_1, numbers[1], SIGNAL(clicked()));
    s2 = new QShortcut(Qt::Key_2, numbers[2], SIGNAL(clicked()));
    s3 = new QShortcut(Qt::Key_3, numbers[3], SIGNAL(clicked()));
    s4 = new QShortcut(Qt::Key_4, numbers[4], SIGNAL(clicked()));
    s5 = new QShortcut(Qt::Key_5, numbers[5], SIGNAL(clicked()));
    s6 = new QShortcut(Qt::Key_6, numbers[6], SIGNAL(clicked()));
    s7 = new QShortcut(Qt::Key_7, numbers[7], SIGNAL(clicked()));
    s8 = new QShortcut(Qt::Key_8, numbers[8], SIGNAL(clicked()));
    s9 = new QShortcut(Qt::Key_9, numbers[9], SIGNAL(clicked()));

    sDot = new QShortcut(Qt::Key_Period, b_dot, SIGNAL(clicked()));
    sNeg = new QShortcut(Qt::SHIFT + Qt::Key_Minus, b_neg, SIGNAL(clicked()));
    sPlus = new QShortcut(Qt::Key_Plus, plus, SIGNAL(clicked()));
    sMinus = new QShortcut(Qt::Key_Minus, minus, SIGNAL(clicked()));
    sMult = new QShortcut(Qt::Key_Asterisk, mult, SIGNAL(clicked()));
    sDiv = new QShortcut(Qt::Key_Slash, div, SIGNAL(clicked()));

    sEq = new QShortcut(Qt::Key_Return, eq, SIGNAL(clicked()));
    sEq2 = new QShortcut(Qt::Key_Enter, eq, SIGNAL(clicked()));
    sEq3 = new QShortcut(Qt::Key_Equal, eq, SIGNAL(clicked()));
    sCE = new QShortcut(Qt::Key_Delete, CE, SIGNAL(clicked()));
    sC = new QShortcut(Qt::Key_Escape, C, SIGNAL(clicked()));
    sBack = new QShortcut(Qt::Key_Backspace, back, SIGNAL(clicked()));
}


void MainWindow::num_press(const QString& text) {
    if (new_num || lower_d->text() == "0") { // clear display if entering new number
        lower_d->clear();
    }
    lower_d->setText(lower_d->text() + text);
    set_new_num(false);
}


void MainWindow::dot_press() {
    if (!dot_pressed) {
        if (new_num) { // if empty, add 0 before dot
            lower_d->setText("0");
        }
        lower_d->setText(lower_d->text() + ".");
        set_new_num(false);
        dot_pressed = true;
    }
}


void MainWindow::neg_press() {
    if (!new_num) {
        set_text(lower_d->text().toDouble() * -1);
    }
}


void MainWindow::op_press(const QString& op) {
   if (!new_num || upper_d->text().isEmpty()) { // add number then operator
       if (!new_num
               && lower_d->text().at(lower_d->text().length() - 1) == '.') {
           // remove the dot at the end of the number if there are no following digits
           back_press();
       }
       upper_d->setText(upper_d->text() + lower_d->text() + " " + op + " ");
       set_text(calculate());
       set_new_num(true);
   } else { // remove operator, add new one
       upper_d->end(false);
       upper_d->backspace();
       upper_d->backspace();
       upper_d->setText(upper_d->text() + op + " ");
   }
   pre_op = op;
   dot_pressed = false;
}


void MainWindow::eq_press() {
    if (!new_num) {
        set_text(calculate());
    } else {
        set_text(result);
    }
    upper_d->clear();
    pre_op = "";
    dot_pressed = false;
    set_new_num(true);
}


void MainWindow::ce_press() {
    lower_d->setText("0");
    set_new_num(true);
    dot_pressed = false;
}


void MainWindow::c_press() {
    upper_d->clear();
    lower_d->setText("0");
    pre_op = "";
    set_new_num(true);
    dot_pressed = false;
    result = 0;
}


void MainWindow::back_press() {
    if (new_num || lower_d->text().length() == 1) {
        lower_d->setText("0");
        set_new_num(true);
        dot_pressed = false;
    } else {
        if (lower_d->text().length() != 0 // if a dot is going to be deleted
                && lower_d->text().at(lower_d->text().length() - 1) == '.') {
            dot_pressed = false;
        }
        lower_d->end(false);
        lower_d->backspace();
        if (lower_d->text() == "-") {
            lower_d->setText("0");
            set_new_num(true);
            dot_pressed = false;
        }
    }
}


double MainWindow::calculate() {
    if (pre_op == "+") {
        return result += lower_d->text().toDouble();
    } else if (pre_op == "-") {
        return result -= lower_d->text().toDouble();
    } else if (pre_op == "*") {
        return result *= lower_d->text().toDouble();
    } else if (pre_op == "/") {
        return result /= lower_d->text().toDouble();
    }
    return result = lower_d->text().toDouble();

}


void MainWindow::set_text(double val) {
    int ival = val;
    int pre_len = QString::number(ival).length();
    if (ival < 0) {
        --pre_len;
    }

    lower_d->setText(QString::number(val, 'g', pre_len + 6));
}


void MainWindow::set_new_num(bool new_n) {
    new_num = new_n;
    if (new_n) {
        lower_d->setFrame(false);
    } else {
        lower_d->setFrame(true);
    }
}
