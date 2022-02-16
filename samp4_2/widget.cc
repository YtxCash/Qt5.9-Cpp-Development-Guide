#include "widget.hh"

#include "./ui_widget.h"
#include "moc_widget.cpp"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);

  IniHash();
  IniSignalSlots();
}

Widget::~Widget() { delete ui; }

void Widget::on_btn_clicked() {
  btnClicked = qobject_cast<QPushButton *>(sender());

  QString str3;
  auto str1 = ui->comboBox->currentText();
  auto str2 = ui->comboBox_2->currentText();

  switch (hash[btnClicked->text()]) {
    case 0:
      str3 = str1;
      str3.append(str2);
      break;
    case 1:
      str3 = str1;
      str3.prepend(str2);
      break;
    case 2:
      ui->comboBox->setCurrentText(str1.toUpper());
      ui->comboBox_2->setCurrentText(str2.toUpper());
      break;
    case 3:
      ui->comboBox->setCurrentText(str1.toLower());
      ui->comboBox_2->setCurrentText(str2.toLower());
      break;
    case 4:
      str3 = str2.left(5);
      break;
    case 5:
      str3 = str2.right(5);
      break;
    case 6:
      str3 = str2.section(",", 0, 1);
      break;
    case 7:
      str3 = str2.simplified();
      break;
    case 8:
      str3 = str2.trimmed();
      break;
    case 9:
      ui->spinBox->setValue(str2.count());
      break;
    case 10:
      ui->spinBox->setValue(str2.size());
      break;
    case 11:
      str3.setNum(str2.indexOf(str1, Qt::CaseInsensitive));
      break;
    case 12:
      str3.setNum(str2.lastIndexOf(str1, Qt::CaseInsensitive));
      break;
    case 13:
      str3.setNum(str2.endsWith(str1, Qt::CaseInsensitive));
      break;
    case 14:
      str3.setNum(str2.startsWith(str1, Qt::CaseInsensitive));
      break;
    case 15:
      str3.setNum(str2.contains(str1, Qt::CaseInsensitive));
      break;
    case 16:
      if (str2.isNull())
        ui->spinBox->setValue(1);
      else {
        ui->spinBox->setValue(0);
      }
      break;
    case 17:
      if (str3.isEmpty())
        ui->spinBox->setValue(1);
      else {
        ui->spinBox->setValue(0);
      }
  }
  ui->lineEdit->setText(str3);
}

void Widget::IniSignalSlots() {
  connect(ui->btnApend, SIGNAL(clicked()), this, SLOT(on_btn_clicked()));
  connect(ui->btnPrepend, SIGNAL(clicked()), this, SLOT(on_btn_clicked()));
  connect(ui->btnToUpper, SIGNAL(clicked()), this, SLOT(on_btn_clicked()));
  connect(ui->btnToLower, SIGNAL(clicked()), this, SLOT(on_btn_clicked()));
  connect(ui->btnLeft, SIGNAL(clicked()), this, SLOT(on_btn_clicked()));
  connect(ui->btnRight, SIGNAL(clicked()), this, SLOT(on_btn_clicked()));
  connect(ui->btnSection, SIGNAL(clicked()), this, SLOT(on_btn_clicked()));
  connect(ui->btnSimplified, SIGNAL(clicked()), this, SLOT(on_btn_clicked()));
  connect(ui->btnTrimmed, SIGNAL(clicked()), this, SLOT(on_btn_clicked()));
  connect(ui->btnCount, SIGNAL(clicked()), this, SLOT(on_btn_clicked()));
  connect(ui->btnSize, SIGNAL(clicked()), this, SLOT(on_btn_clicked()));
  connect(ui->btnIndex, SIGNAL(clicked()), this, SLOT(on_btn_clicked()));
  connect(ui->btnLastIndex, SIGNAL(clicked()), this, SLOT(on_btn_clicked()));
  connect(ui->btnEnds, SIGNAL(clicked()), this, SLOT(on_btn_clicked()));
  connect(ui->btnStarts, SIGNAL(clicked()), this, SLOT(on_btn_clicked()));
  connect(ui->btnContains, SIGNAL(clicked()), this, SLOT(on_btn_clicked()));
  connect(ui->btnIsNull, SIGNAL(clicked()), this, SLOT(on_btn_clicked()));
  connect(ui->btnIsEmpty, SIGNAL(clicked()), this, SLOT(on_btn_clicked()));
}

void Widget::IniHash() {
  str_list = {"apend",    "prepend", "toUpper",     "toLower",  "left",
              "right",    "section", "simplified",  "trimmed",  "count",
              "size",     "indexOf", "lastIndexOf", "endsWith", "startsWith",
              "contains", "isNull",  "isEmpty"};

  for (int i = 0; i != str_list.count(); ++i) hash.insert(str_list.at(i), i);
}
