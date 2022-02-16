#include "qwdialog.hh"

#include "./ui_qwdialog.h"
#include "moc_qwdialog.cpp"

QWDialog::QWDialog(QWidget *parent) : QDialog(parent), ui(new Ui::QWDialog) {
  ui->setupUi(this);
  IniSignalSlots();
}

QWDialog::~QWDialog() { delete ui; }

void QWDialog::on_chkBoxUnder_clicked(bool checked) {
  auto font = ui->textEdit->font();
  font.setUnderline(checked);
  ui->textEdit->setFont(font);
}

void QWDialog::on_chkBoxItalic_clicked(bool checked) {
  auto font = ui->textEdit->font();
  font.setItalic(checked);
  ui->textEdit->setFont(font);
}

void QWDialog::on_chkBoxBold_clicked(bool checked) {
  auto font = ui->textEdit->font();
  font.setBold(checked);
  ui->textEdit->setFont(font);
}

void QWDialog::SetTextFontColor() {
  auto palette = ui->textEdit->palette();
  if (ui->rBtnBlack->isChecked()) {
    palette.setColor(QPalette::Text, Qt::black);
  } else if (ui->rBtnBlue->isChecked()) {
    palette.setColor(QPalette::Text, Qt::blue);
  } else if (ui->rBtnRed->isChecked()) {
    palette.setColor(QPalette::Text, Qt::red);
  }
  ui->textEdit->setPalette(palette);
}

void QWDialog::IniSignalSlots() {
  connect(ui->rBtnBlack, &QRadioButton::clicked, this,
          &QWDialog::SetTextFontColor);
  connect(ui->rBtnRed, &QRadioButton::clicked, this,
          &QWDialog::SetTextFontColor);
  connect(ui->rBtnBlue, &QRadioButton::clicked, this,
          &QWDialog::SetTextFontColor);
}
