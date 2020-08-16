#include "widget.h"
#include "ui_widget.h"
#include "qmessagebox.h"

#define COFFEE_PRICE 100
#define TEA_PRICE    150
#define MILK_PRICE   200

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    checkProduct();
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
    ui->pbReset  ->setEnabled(0             < money);
    ui->pbCoffee ->setEnabled(COFFEE_PRICE <= money);
    ui->pbTea    ->setEnabled(TEA_PRICE    <= money);
    ui->pbMilk   ->setEnabled(MILK_PRICE   <= money);
}

void Widget::productOut(int price, const char *productName)
{
    changeMoney(-price);

    customMessageBox("Product Out", productName);
}

void Widget::changeOut(int value)
{
    char charValue[4];
    sprintf(charValue, "%d", value);

    changeMoney(-value);

    customMessageBox("Change Out", charValue);
}

void Widget::resetMoney()
{
    while(500 <= money) changeOut(500);
    while(100 <= money) changeOut(100);
    while(50 <= money)  changeOut(50);
    while(10 <= money)  changeOut(10);
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
    productOut(COFFEE_PRICE, "Coffee");
}

void Widget::on_pbTea_clicked()
{
    productOut(TEA_PRICE,    "Tea");
}

void Widget::on_pbMilk_clicked()
{
    productOut(MILK_PRICE,   "Milk");
}

void Widget::on_pbReset_clicked()
{
    resetMoney();
}
