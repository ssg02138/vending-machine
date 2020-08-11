#include "widget.h"
#include "ui_widget.h"
#include "qmessagebox.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->pbCoffee->setEnabled(false);
    ui->pbTea->setEnabled(false);
    ui->pbMilk->setEnabled(false);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::changeMoney(int diff)
{
    money += diff;

    if (10000 >= money)
    {
        ui->lcdNumber->display(money);

        checkProduct();
    }
    else
    {
        changeOut(diff);
        customMessageBox("Information", "You cannot insert money over than 10,000");
    }
}

void Widget::checkProduct()
{
    if (100 <= money) ui->pbCoffee->setEnabled(true);
    else ui->pbCoffee->setEnabled(false);

    if (150 <= money) ui->pbTea->setEnabled(true);
    else ui->pbTea->setEnabled(false);

    if (200 <= money) ui->pbMilk->setEnabled(true);
    else ui->pbMilk->setEnabled(false);
}

void Widget::productOut(int price, const char *productName)
{
    changeMoney(-price);

    customMessageBox("Product Out", productName);
}

void Widget::changeOut(int value)
{
    char *charValue  = (char*)malloc(sizeof(char) * 30);
    int t, f, h, fh {0};

    fh = value/500;
    h = (value-500*fh)/100;
    f = (value-500*fh-100*h)/50;
    t = (value-500*fh-100*h-50*f)/10;

    sprintf(charValue, "10: %dea\n50: %dea\n100: %dea\n500: %dea", t, f, h, fh);

    changeMoney(-value);

    customMessageBox("Change Out", charValue);
}

void Widget::customMessageBox(const char *title, const char *contents)
{
    QMessageBox m;
    m.information(nullptr, title, contents);
}

void Widget::on_pb10_clicked()
{
    changeMoney(10);
}

void Widget::on_pb50_clicked()
{
    changeMoney(50);
}

void Widget::on_pb100_clicked()
{
    changeMoney(100);
}

void Widget::on_pb500_clicked()
{
    changeMoney(500);
}

void Widget::on_pbCoffee_clicked()
{
    productOut(100, "Coffee");
}

void Widget::on_pbTea_clicked()
{
    productOut(150, "Tea");
}

void Widget::on_pbMilk_clicked()
{
    productOut(200, "Milk");
}

void Widget::on_pbReset_clicked()
{
    changeOut(money);
}
