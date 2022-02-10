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
  QMenu *menu_list = new QMenu;
  menu_list->addAction(ui->actSelectAll);
  menu_list->addAction(ui->actSeletcNon);
  menu_list->addAction(ui->actSelInvs);

  // tool button select item
  ui->tBtnSelItem->setPopupMode(QToolButton::MenuButtonPopup);
  ui->tBtnSelItem->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextOnly);
  ui->tBtnSelItem->setDefaultAction(ui->actSelPopMenu);
  ui->tBtnSelItem->setMenu(menu_list);

  QToolButton *tBtn = new QToolButton;
  tBtn->setPopupMode(QToolButton::InstantPopup);
  tBtn->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);
  tBtn->setMenu(menu_list);
  tBtn->setDefaultAction(ui->actSelPopMenu);  // this line do nothing
  ui->toolBar->addWidget(tBtn);

  ui->toolBar->addSeparator();
  ui->toolBar->addAction(ui->actQuit);

  ui->tBtnIni->setDefaultAction(ui->acttIni);
  ui->tBtnClear->setDefaultAction(ui->actClear);
  ui->tBtnItemAppend->setDefaultAction(ui->actItemAppend);
  ui->tBtnItemDelete->setDefaultAction(ui->actItemDelete);
  ui->tBtnItemInsert->setDefaultAction(ui->actItemInsert);
  ui->tBtnSelAll->setDefaultAction(ui->actSelectAll);
  ui->tBtnSelNon->setDefaultAction(ui->actSeletcNon);
  ui->tBtnSelInvs->setDefaultAction(ui->actSelInvs);

  ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
}

void MainWindow::on_listWidget_customContextMenuRequested(const QPoint &pos) {
  Q_UNUSED(pos);
  QMenu *menu = new QMenu(this);
  menu->addAction(ui->acttIni);
  menu->addAction(ui->actClear);
  menu->addAction(ui->actItemInsert);
  menu->addAction(ui->actItemAppend);
  menu->addAction(ui->actItemAppend);
  menu->addAction(ui->actSelectAll);
  menu->addAction(ui->actSeletcNon);
  menu->addAction(ui->actSelInvs);
  menu->exec(QCursor::pos());
  delete menu;
}

void MainWindow::on_acttIni_triggered() {
  bool check = ui->chkBox->isChecked();

  if (check) {
    ui->listWidget->clear();
    QString str;
    QListWidgetItem *item;

    for (int i = 0; i != 20; ++i) {
      str = QString::asprintf("Item %d", i);
      item = new QListWidgetItem;
      item->setText(str);
      item->setCheckState(Qt::Checked);
      item->setFlags(Qt::ItemIsEditable | Qt::ItemIsSelectable |
                     Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
      ui->listWidget->addItem(item);
    }
  }
}

void MainWindow::on_actItemInsert_triggered() {
  bool check = ui->chkBox->isChecked();
  if (check) {
    QListWidgetItem *item = new QListWidgetItem("New Item");
    item->setCheckState(Qt::Checked);
    item->setFlags(Qt::ItemIsEditable | Qt::ItemIsSelectable |
                   Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
    ui->listWidget->insertItem(ui->listWidget->currentRow(), item);
  }
}

void MainWindow::on_actItemDelete_triggered() {
  bool check = ui->chkBox->isChecked();
  if (check) {
    int row = ui->listWidget->currentRow();
    QListWidgetItem *item = ui->listWidget->takeItem(row);
    delete item;
  }
}

void MainWindow::on_actClear_triggered() {
  bool check = ui->chkBox->isChecked();
  if (check) {
    ui->listWidget->clear();
  }
}

void MainWindow::on_chkBox_stateChanged(int arg1) {
  Q_UNUSED(arg1);

  bool check = ui->chkBox->isChecked();
  if (check) {
    for (int i = 0; i != ui->listWidget->count(); ++i) {
      ui->listWidget->item(i)->setFlags(
          Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled |
          Qt::ItemIsUserCheckable);
    }
  } else
    for (int i = 0; i != ui->listWidget->count(); ++i) {
      ui->listWidget->item(i)->setFlags(
          Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
    }
}

void MainWindow::on_actSelectAll_triggered() {
  bool check = ui->chkBox->isChecked();
  if (check) {
    for (int i = 0; i != ui->listWidget->count(); ++i)
      ui->listWidget->item(i)->setCheckState(Qt::Checked);
  }
}

void MainWindow::on_actSeletcNon_triggered() {
  bool check = ui->chkBox->isChecked();
  if (check) {
    for (int i = 0; i != ui->listWidget->count(); ++i)
      ui->listWidget->item(i)->setCheckState(Qt::Unchecked);
  }
}

void MainWindow::on_actSelInvs_triggered() { QString str = "do not how to do"; }

void MainWindow::on_actItemAppend_triggered() {
  bool check = ui->chkBox->isChecked();
  if (check) {
    QListWidgetItem *item = new QListWidgetItem("New Item");
    item->setCheckState(Qt::Checked);
    item->setFlags(Qt::ItemIsEditable | Qt::ItemIsSelectable |
                   Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
    ui->listWidget->addItem(item);
  }
}

void MainWindow::on_listWidget_currentItemChanged(QListWidgetItem *current,
                                                  QListWidgetItem *previous) {
  QString str;
  if (current != NULL) {
    if (previous == NULL)
      str = "Current " + current->text();
    else
      str = "Previous " + previous->text() + " " + "current " + current->text();
  }
  ui->lineEdit->setText(str);
}
