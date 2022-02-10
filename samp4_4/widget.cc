#include "widget.hh"

#include "./ui_widget.h"
#include "moc_widget.cpp"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);
  IniDynaProp();
  IniSignalSlots();
}

Widget::~Widget() { delete ui; }

void Widget::on_sliderColor_valueChanged(int value) {
  Q_UNUSED(value);
  QColor color(ui->sliderRed->value(), ui->sliderGreen->value(),
               ui->sliderBLue->value(), ui->sliderAlpha->value());

  QPalette pale = ui->textEdit->palette();
  pale.setColor(QPalette::Base, color);
  ui->textEdit->setPalette(pale);
}

void Widget::IniSignalSlots() {
  connect(ui->sliderRed, SIGNAL(valueChanged(int)), this,
          SLOT(on_sliderColor_valueChanged(int)));
  connect(ui->sliderGreen, SIGNAL(valueChanged(int)), this,
          SLOT(on_sliderColor_valueChanged(int)));
  connect(ui->sliderBLue, SIGNAL(valueChanged(int)), this,
          SLOT(on_sliderColor_valueChanged(int)));
  connect(ui->sliderAlpha, SIGNAL(valueChanged(int)), this,
          SLOT(on_sliderColor_valueChanged(int)));

  connect(ui->rBtnBin, SIGNAL(clicked()), this, SLOT(on_rBtnBin_clicked()));
  connect(ui->rBtnDec, SIGNAL(clicked()), this, SLOT(on_rBtnBin_clicked()));
  connect(ui->rBtnHex, SIGNAL(clicked()), this, SLOT(on_rBtnBin_clicked()));
  connect(ui->rBtnOct, SIGNAL(clicked()), this, SLOT(on_rBtnBin_clicked()));
}

void Widget::IniDynaProp() {
  ui->rBtnBin->setProperty("Binary", 2);
  ui->rBtnDec->setProperty("Binary", 10);
  ui->rBtnHex->setProperty("Binary", 16);
  ui->rBtnOct->setProperty("Binary", 8);
}

void Widget::on_dial_valueChanged(int value) { ui->lcdNumber->display(value); }

void Widget::on_rBtnBin_clicked() {
  QRadioButton *btn = qobject_cast<QRadioButton *>(sender());
  ui->lcdNumber->setDigitCount(10);
  switch (btn->property("Binary").toInt()) {
    case 2:
      ui->lcdNumber->setBinMode();
      break;
    case 8:
      ui->lcdNumber->setOctMode();
      break;
    case 10:
      ui->lcdNumber->setDecMode();
      break;
    case 16:
      ui->lcdNumber->setHexMode();
      break;
    default:
      ui->lcdNumber->setDecMode();
  }
}
