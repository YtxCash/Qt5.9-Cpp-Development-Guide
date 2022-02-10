#include "widget.hh"

#include "./ui_widget.h"
#include "moc_widget.cpp"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);

  IniDynaProperty();
  IniSignalSlots();
}

Widget::~Widget() { delete ui; }

void Widget::on_btnCal_clicked() {
  QString str = ui->editNum->text();
  int num = str.toInt();
  str = ui->editPrice->text();
  float price = str.toFloat();
  float total = num * price;
  str = str.asprintf("%.2f", total);
  ui->editTotal->setText(str);
}

void Widget::on_convert_clicked() {
  QPushButton *sendBtn = qobject_cast<QPushButton *>(sender());

  int input_int = 0;
  QString str;
  bool ok;

  int i = sendBtn->property("Binary").toInt();
  switch (i) {
    case 10:
      input_int = ui->editDec->text().toInt(&ok, 10);
      break;
    case 2:
      input_int = ui->editBin->text().toInt(&ok, 2);
      break;
    case 16:
      input_int = ui->editHex->text().toInt(&ok, 16);
      break;
    default:
      break;
  }

  str = str.setNum(input_int, 10);
  ui->editDec->setText(str);

  str = str.setNum(input_int, 16);
  str = str.toUpper();
  ui->editHex->setText(str);

  str = str.setNum(input_int, 2);
  ui->editBin->setText(str);
}

void Widget::IniDynaProperty() {
  ui->btnHex->setProperty("Binary", 16);
  ui->btnDec->setProperty("Binary", 10);
  ui->btnBin->setProperty("Binary", 2);
}

void Widget::IniSignalSlots() {
  connect(ui->btnDec, &QPushButton::clicked, this, &Widget::on_convert_clicked);
  connect(ui->btnBin, &QPushButton::clicked, this, &Widget::on_convert_clicked);
  connect(ui->btnHex, &QPushButton::clicked, this, &Widget::on_convert_clicked);
}
