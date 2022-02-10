#include "widget.hh"

#include <QTextBlock>
#include <QTextDocument>

#include "./ui_widget.h"
#include "moc_widget.cpp"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);
}

Widget::~Widget() { delete ui; }

void Widget::on_btnIniSImplify_clicked() {
  ui->comboSimplify->clear();
  for (int i = 0; i != 20; ++i) {
    ui->comboSimplify->addItem(QString::asprintf("Item %d", i));
  }
}

void Widget::on_chkBoxEditable_toggled(bool checked) {
  ui->comboSimplify->setEditable(checked);
}

void Widget::on_chkBoxReadOnly_toggled(bool checked) {
  ui->plainTextEdit->setReadOnly(checked);
}

void Widget::on_btnIniCities_clicked() {
  for (int i = 0; i != 20; ++i) {
    ui->comboCities->addItem(QString::asprintf("Item %d", i), i);
  }
}

void Widget::on_btnCleanText_clicked() { ui->plainTextEdit->clear(); }

void Widget::on_btnAddText_clicked() {
  QTextDocument *doc = ui->plainTextEdit->document();
  int count = doc->blockCount();
  for (int i = 0; i != count; ++i) {
    QTextBlock text = doc->findBlockByNumber(i);
    QString str = text.text();
    ui->comboSimplify->addItem(str);
  }
}
