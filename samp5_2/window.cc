#include "window.hh"

#include "./ui_window.h"
#include "moc_window.cpp"

Window::Window(QWidget *parent) : QMainWindow(parent), ui(new Ui::Window) {
  ui->setupUi(this);
  IniUi();
}

Window::~Window() { delete ui; }

void Window::IniUi() {
  str_list = {"a", "b", "c", "d", "e", "f", "g"};
  mode = new QStringListModel(str_list, this);
  ui->listView->setModel(mode);
  ui->listView->setEditTriggers(QAbstractItemView::DoubleClicked |
                                QAbstractItemView::SelectedClicked);
}

void Window::on_btnResetList_clicked() {
  str_list = {"a", "b", "c", "d", "e", "f", "g"};
  mode->setStringList(str_list);
}

void Window::on_btnAddItem_clicked() {
  mode->insertRow(mode->rowCount());
  QModelIndex index = mode->index(mode->rowCount() - 1, 0);
  mode->setData(index, "add item", Qt::DisplayRole);
  ui->listView->setCurrentIndex(index);
}

void Window::on_btnInsertItem_clicked() {
  QModelIndex index = ui->listView->currentIndex();
  mode->insertRow(index.row());
  mode->setData(index, "Insert item", Qt::DisplayRole);
  ui->listView->setCurrentIndex(index);
}

void Window::on_btnDeleteCurItem_clicked() {
  QModelIndex index = ui->listView->currentIndex();
  mode->removeRow(index.row());
}

void Window::on_btnCleanList_clicked() {
  mode->removeRows(0, mode->rowCount());
}

void Window::on_btnCleanText_clicked() { ui->plainTextEdit->clear(); }

void Window::on_btnShowModeString_clicked() {
  ui->plainTextEdit->clear();
  QStringList str = mode->stringList();
  for (int i = 0; i != str.count(); ++i)
    ui->plainTextEdit->appendPlainText(str.at(i));
}

void Window::on_listView_clicked(const QModelIndex &index) {
  ui->label->setText(QString::asprintf("Current Row: %d, Column: %d",
                                       index.row(), index.column()));
}
