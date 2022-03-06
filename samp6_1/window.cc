#include "window.hh"

#include <QColorDialog>
#include <QCoreApplication>
#include <QFileDialog>
#include <QFontDialog>

#include "./ui_window.h"
#include "moc_window.cpp"

Window::Window(QWidget *parent) : QMainWindow(parent), ui(new Ui::Window) {
  ui->setupUi(this);
}

Window::~Window() { delete ui; }

void Window::on_btnFile_clicked() {
  QString cur_path = QCoreApplication::applicationDirPath();
  QString title = "Select a file";
  QString filter = "*.txt;;*.jpg *.png;;*.*";
  QString file_name =
      QFileDialog::getOpenFileName(this, title, cur_path, filter);
  if (!file_name.isEmpty()) {
    ui->plainTextEdit->appendPlainText(file_name);
  }
}

void Window::on_btnFiles_clicked() {
  QString cur_path = QCoreApplication::applicationDirPath();
  QString title = "Select files";
  QString filter = "*.txt;; *.jpg *.png;;*.*";
  QStringList file_names =
      QFileDialog::getOpenFileNames(this, title, cur_path, filter);
  if (!file_names.isEmpty()) {
    foreach (QString str, file_names)
      ui->plainTextEdit->appendPlainText(str);
  }
}

void Window::on_btnDir_clicked() {
  QString cur_path = QCoreApplication::applicationDirPath();
  QString title = "Select a directory";
  QString dir_name = QFileDialog::getExistingDirectory(
      this, title, cur_path, QFileDialog::ShowDirsOnly);
  if (!dir_name.isEmpty()) ui->plainTextEdit->appendPlainText(dir_name);
}

void Window::on_btnSave_clicked() {
  QString cur_path = QApplication::applicationDirPath();
  QString title = "Save a file";
  QString filter = "*.txt;; *.jpg *.png;;*.*";
  QString file_name =
      QFileDialog::getSaveFileName(this, title, cur_path, filter);
  if (!file_name.isEmpty()) ui->plainTextEdit->appendPlainText(file_name);
}

void Window::on_btnColor_clicked() {
  QPalette pale = ui->plainTextEdit->palette();
  QColor ini_color = pale.color(QPalette::Text);
  QColor color = QColorDialog::getColor(ini_color, this, "Select a color");
  if (color.isValid()) {
    pale.setColor(QPalette::Text, color);
    ui->plainTextEdit->setPalette(pale);
  }
}

void Window::on_btnFont_clicked() {
  QFont ini_font = ui->plainTextEdit->font();
  bool ok = false;
  auto font = QFontDialog::getFont(&ok, this);
  if (ok) ui->plainTextEdit->setFont(font);
}
