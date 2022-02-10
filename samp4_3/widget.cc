#include "widget.hh"

#include "./ui_widget.h"
#include "moc_widget.cpp"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);
}

Widget::~Widget() { delete ui; }

void Widget::on_btnCal_clicked() {
  ui->spinTotal->setValue(ui->spinPrice->value() * ui->spinNumb->value());
}
