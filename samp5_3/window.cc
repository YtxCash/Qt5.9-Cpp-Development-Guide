#include "window.hh"

#include <QFileDialog>

#include "./ui_window.h"
#include "moc_window.cpp"

Window::Window(QWidget *parent) : QMainWindow(parent), ui(new Ui::Window) {
  ui->setupUi(this);

  IniUi();
}

Window::~Window() { delete ui; }

void Window::IniModel(QStringList &list) {
  int row_count = list.count() - 1;
  model_data->setRowCount(row_count);

  auto str = list.at(0);
  auto str_list = str.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
  model_data->setHorizontalHeaderLabels(str_list);

  int j = 0;

  for (int i = 1; i != list.count(); ++i) {
    str = list.at(i);
    str_list = str.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);

    for (j = 0; j != kFixedColumnCount - 1; ++j) {
      item = new QStandardItem(str_list.at(j));
      model_data->setItem(i - 1, j, item);
    }

    item = new QStandardItem(str_list.at(j));
    item->setCheckable(true);
    if (str_list.at(j) == "0")
      item->setCheckState(Qt::Checked);
    else
      item->setCheckState(Qt::Unchecked);
    model_data->setItem(i - 1, j, item);
  }
}

void Window::IniUi() {
  model_data = new QStandardItemModel(2, kFixedColumnCount, this);
  model_select = new QItemSelectionModel(model_data);

  ui->tableView->setModel(model_data);
  ui->tableView->setSelectionModel(model_select);
  ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
  ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);

  connect(model_select, &QItemSelectionModel::currentChanged, this,
          &Window::onCurrentChanged);

  lab_cur_file = new QLabel;
  lab_cell_pos = new QLabel;
  lab_cell_text = new QLabel;

  lab_cur_file->setMinimumWidth(150);
  lab_cell_pos->setMinimumWidth(150);
  lab_cell_pos->setMinimumWidth(150);

  ui->statusbar->addWidget(lab_cur_file);
  ui->statusbar->addWidget(lab_cell_pos);
  ui->statusbar->addWidget(lab_cell_text);
}

void Window::onCurrentChanged(const QModelIndex &current,
                              const QModelIndex &previous) {
  Q_UNUSED(previous);

  if (current.isValid())
    lab_cell_pos->setText(QString::asprintf(
        "current cell: %d %d", current.row() + 1, current.column() + 1));
  item = model_data->itemFromIndex(current);
  lab_cell_text->setText("cell content " + item->text());
}

void Window::on_actOpen_triggered() {
  auto cur_path = QCoreApplication::applicationDirPath();
  auto file_name =
      QFileDialog::getOpenFileName(this, "Open a file", cur_path, "*.txt");

  if (file_name.isEmpty()) return;

  QStringList file_content;
  QFile file(file_name);

  if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QTextStream stream(&file);
    ui->plainTextEdit->clear();
    while (!stream.atEnd()) {
      auto str = stream.readLine();
      ui->plainTextEdit->appendPlainText(str);
      file_content.append(str);
    }
  }
  lab_cell_text->setText(file_name);
  IniModel(file_content);
}

void Window::on_actAppend_triggered() {
  QList<QStandardItem *> item_list;

  for (int i = 0; i != kFixedColumnCount - 1; ++i) {
    item = new QStandardItem(QString::asprintf("append %d", i + 1));
    item_list.append(item);
  }

  auto str = model_data
                 ->headerData(model_data->columnCount() - 1, Qt::Horizontal,
                              Qt::DisplayRole)
                 .toString();

  item = new QStandardItem(str);
  item->setCheckable(true);
  item_list.append(item);
  model_data->appendRow(item_list);

  auto cur_index = model_data->index(model_data->rowCount() - 1, 0);
  model_select->clearSelection();
  model_select->setCurrentIndex(cur_index, QItemSelectionModel::Select);
}

void Window::on_actInsert_triggered() {
  QList<QStandardItem *> item_list;

  for (int i = 0; i != kFixedColumnCount - 1; ++i) {
    item = new QStandardItem(QString::asprintf("insert %d", i + 1));
    item_list.append(item);
  }

  auto str = model_data
                 ->headerData(model_data->columnCount() - 1, Qt::Horizontal,
                              Qt::DisplayRole)
                 .toString();

  item = new QStandardItem(str);
  item->setCheckable(true);
  item_list.append(item);
  index = model_select->currentIndex();

  model_data->insertRow(index.row(), item_list);

  model_select->clearSelection();
  model_select->setCurrentIndex(index, QItemSelectionModel::Select);
}

void Window::on_actDelete_triggered() {
  auto cur_index = model_select->currentIndex();
  if (cur_index.row() == model_data->rowCount() - 1)
    model_data->removeRow(cur_index.row());
  else {
    model_data->removeRow(cur_index.row());
    model_select->setCurrentIndex(cur_index, QItemSelectionModel::Select);
  }
}

void Window::on_actAlignRight_triggered() {
  if (!model_select->hasSelection()) return;

  index_list = model_select->selectedIndexes();

  foreach (index, index_list) {
    item = model_data->itemFromIndex(index);
    item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
  }
}

void Window::on_actAlignLeft_triggered() {
  if (!model_select->hasSelection()) return;

  index_list = model_select->selectedIndexes();

  foreach (index, index_list) {
    item = model_data->itemFromIndex(index);
    item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
  }
}

void Window::on_actAlignCenter_triggered() {
  if (!model_select->hasSelection()) return;

  index_list = model_select->selectedIndexes();

  foreach (index, index_list) {
    item = model_data->itemFromIndex(index);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
  }
}

#if 0
void Window::on_actFontBlod_triggered(bool checked) {
  if (!model_select->hasSelection()) return;

  index_list = model_select->selectedIndexes();
  QFont font;

  foreach (index, index_list) {
    item = model_data->itemFromIndex(index);
    font = item->font();
    font.setBold(checked);
    item->setFont(font);
  }
}
#endif
