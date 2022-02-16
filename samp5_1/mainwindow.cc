#include "mainwindow.hh"

#include "./ui_mainwindow.h"
#include "moc_mainwindow.cpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  IniUi();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::IniUi() {
  mode = new QFileSystemModel(this);
  mode->setRootPath(QDir::currentPath());

  ui->treeView->setModel(mode);
  ui->listView->setModel(mode);
  ui->tableView->setModel(mode);

  connect(ui->treeView, &QAbstractItemView::clicked, ui->tableView,
          &QAbstractItemView::setRootIndex);
  connect(ui->treeView, &QAbstractItemView::clicked, ui->listView,
          &QAbstractItemView::setRootIndex);

  ui->chkkIsDir->setText("");
}

void MainWindow::on_treeView_clicked(const QModelIndex &index) {
  ui->chkkIsDir->setChecked(mode->isDir(index));
  ui->labPath->setText(mode->filePath(index));
  ui->labFileType->setText(mode->type(index));
  ui->labFileName->setText(mode->fileName(index));

  int sz = mode->size(index) / 1000;

  if (sz < 1024)
    ui->labFileSize->setText(QString("%1 KB").arg(sz));
  else
    ui->labFileSize->setText(QString::asprintf("%d MB", sz / 1000));
}
