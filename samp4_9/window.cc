#include "window.hh"

#include "./ui_window.h"
#include "moc_window.cpp"

Window::Window(QWidget *parent) : QMainWindow(parent), ui(new Ui::Window) {
  ui->setupUi(this);

  IniUi();
}

Window::~Window() { delete ui; }

void Window::IniUi() {
  lab_cell_index = new QLabel("Current Cell Index", this);
  lab_cell_index->setMinimumWidth(250);

  lab_cell_type = new QLabel("Current Cell Type", this);
  lab_cell_type->setMinimumWidth(250);

  lab_student_ID = new QLabel("Student's ID", this);
  lab_student_ID->setMinimumWidth(250);

  ui->statusbar->addWidget(lab_cell_index);
  ui->statusbar->addWidget(lab_cell_type);
  ui->statusbar->addWidget(lab_student_ID);
}

void Window::on_btnSetColHeaders_clicked() {
  QStringList header_text = {"Name",   "Sex",   "Birth",
                             "Nation", "Party", "Score"};
  ui->tableWidget->setColumnCount(header_text.count());
  ui->tableWidget->setHorizontalHeaderLabels(header_text);
}

void Window::on_btnIniData_clicked() {
  ui->tableWidget->setRowCount(ui->spinBox->value());

  QString name;
  QString sex;
  bool is_party = true;
  QDate birth(1970, 11, 30);
  ui->tableWidget->clearContents();

  int rows = ui->tableWidget->rowCount();
  for (int i = 0; i != rows; ++i) {
    name = QString::asprintf("student %d", i);
    if ((i % 2) == 0)
      sex = "Boy";
    else
      sex = "Girl";

    CreatRowItema(i, name, sex, birth, "Han", is_party, 70);
    birth = birth.addDays(20);
    is_party = !is_party;
  }
}

void Window::CreatRowItema(int row_numb, QString name, QString sex, QDate birth,
                           QString nation, bool is_party, int score) {
  QTableWidgetItem *item;
  QString str;
  uint student_id = 20220202;

  item = new QTableWidgetItem(name, kName);
  item->setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
  student_id += row_numb;
  item->setData(Qt::UserRole, QVariant(student_id));
  ui->tableWidget->setItem(row_numb, kNameNumb, item);

  item = new QTableWidgetItem(sex, kSex);
  item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
  ui->tableWidget->setItem(row_numb, kSecNumb, item);

  str = birth.toString("yyyy-MM-dd");
  item = new QTableWidgetItem(str, kBirthNumb);
  item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
  ui->tableWidget->setItem(row_numb, kBirthNumb, item);

  item = new QTableWidgetItem(nation, kNationNumb);
  ui->tableWidget->setItem(row_numb, kNationNumb, item);

  item = new QTableWidgetItem("Party", kPartyNumb);
  if (is_party)
    item->setCheckState(Qt::Checked);
  else
    item->setCheckState(Qt::Unchecked);
  ui->tableWidget->setItem(row_numb, kPartyNumb, item);

  str.setNum(score);
  item = new QTableWidgetItem(str, kScoreNumb);
  ui->tableWidget->setItem(row_numb, kScoreNumb, item);
}

void Window::on_tableWidget_currentCellChanged(int currentRow,
                                               int currentColumn,
                                               int previousRow,
                                               int previousColumn) {
  Q_UNUSED(previousColumn);
  Q_UNUSED(previousRow);

  auto *item = ui->tableWidget->item(currentRow, currentColumn);

  if (item == NULL) return;
  lab_cell_index->setText(
      QString::asprintf("Current Cell: %d,%d", currentRow, currentColumn));
  int cell_type = item->type();
  lab_cell_type->setText(QString::asprintf("Current Cell Type: %d", cell_type));

  item = ui->tableWidget->item(currentRow, kNameNumb);
  int id = item->data(Qt::UserRole).toInt();
  lab_student_ID->setText(QString::asprintf("%d", id));
}

void Window::on_btnInsertRow_clicked() {
  int cur_item = ui->tableWidget->currentRow();
  ui->tableWidget->insertRow(cur_item);
  CreatRowItema(cur_item, "Man", "man",
                QDate::fromString("2000-08-20", "yyyy-MM-dd"), "HAN", true,
                900);
}

void Window::on_btnAppendRow_clicked() {
  int cur_item = ui->tableWidget->rowCount();
  ui->tableWidget->insertRow(cur_item);
  CreatRowItema(cur_item, "Man", "woman",
                QDate::fromString("2000-08-20", "yyyy-MM-dd"), "HAN", true,
                900);
}

void Window::on_btnDeleteRow_clicked() {
  int cur_row = ui->tableWidget->currentRow();
  ui->tableWidget->removeRow(cur_row);
}

void Window::on_btnAutoHeight_clicked() {
  ui->tableWidget->resizeColumnsToContents();
}

void Window::on_btnAutoWidth_clicked() {
  ui->tableWidget->resizeRowsToContents();
}

void Window::on_btnTableContentsToText_clicked() {
  QTableWidgetItem *item;
  QString string;
  ui->plainTextEdit->clear();

  for (int i = 0; i != ui->tableWidget->rowCount(); ++i) {
    string = QString::asprintf("line %d", i);

    for (int j = 0; j != ui->tableWidget->columnCount(); ++j) {
      item = ui->tableWidget->item(i, j);
      string = string + item->text();
    }
    ui->plainTextEdit->appendPlainText(string);
  }
}

void Window::on_chkBoxEditable_clicked(bool checked) {
  if (checked)
    ui->tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked |
                                     QAbstractItemView::SelectedClicked);
  else
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void Window::on_chkBoxShowRowHeader_clicked(bool checked) {
  ui->tableWidget->verticalHeader()->setVisible(checked);
}

void Window::on_chkBoxShowColHeader_clicked(bool checked) {
  ui->tableWidget->horizontalHeader()->setVisible(checked);
}

void Window::on_chkBoxAlternatingRowColor_clicked(bool checked) {
  ui->tableWidget->setAlternatingRowColors(checked);
}

void Window::on_rBtnSelCell_clicked(bool checked) {
  ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectItems);
}

void Window::on_rBtnSelRow_clicked(bool checked) {
  ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
}
