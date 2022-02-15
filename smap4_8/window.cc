#include "window.hh"

#include <QFileDialog>

#include "./ui_window.h"
#include "moc_window.cpp"

Window::Window(QWidget *parent) : QMainWindow(parent), ui(new Ui::Window) {
  ui->setupUi(this);

  IniTree();
}

Window::~Window() { delete ui; }

void Window::IniTree() {
  lab_file_name = new QLabel("");
  ui->statusbar->addWidget(lab_file_name);
  QString data_str = ("");

  ui->actDockFloat->setCheckable(true);
  ui->actDockVisible->setCheckable(true);

  ui->treeWidget->clear();
  ui->treeWidget->setColumnCount(2);

  QTreeWidgetItem *item = new QTreeWidgetItem(Window::kRowTop);
  item->setText(kColItem, "Image");
  item->setText(kColItemType, "Top");
  item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable |
                 Qt::ItemIsEnabled | Qt::ItemIsAutoTristate);
  item->setCheckState(kColItem, Qt::Checked);
  item->setData(kColItem, Qt::UserRole, QVariant(data_str));
  ui->treeWidget->addTopLevelItem(item);
}

void Window::on_actAddGroup_triggered() {
  if (ui->treeWidget->currentItem() == NULL) return;

  QString dir = QFileDialog::getExistingDirectory();

  if (!dir.isEmpty()) {
    QTreeWidgetItem *par_item = ui->treeWidget->currentItem();
    AddGroupItem(par_item, dir);
  }
}

void Window::AddGroupItem(QTreeWidgetItem *par_item, QString dir_name) {
  QString node_text = GetGroupName(dir_name);

  QTreeWidgetItem *item = new QTreeWidgetItem(kRowGroup);
  item->setText(kColItem, node_text);
  item->setText(kColItemType, "Group");
  item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable |
                 Qt::ItemIsEnabled | Qt::ItemIsAutoTristate);
  item->setData(kColItem, Qt::UserRole, QVariant(dir_name));
  par_item->addChild(item);
}

QString Window::GetGroupName(const QString &full_path_name) {
  int cnt = full_path_name.length();
  int i = full_path_name.lastIndexOf("/");
  QString str = full_path_name.right(cnt - i - 1);
  return str;
}

void Window::on_actAddImages_triggered() {
  QStringList list_images = QFileDialog::getOpenFileNames(
      this, "Select Images", "", "Images(*.jpg)  Images(*.png)");
  if (list_images.isEmpty()) return;

  QTreeWidgetItem *par_item;
  QTreeWidgetItem *item = ui->treeWidget->currentItem();

  if (item->type() == kRowImage)
    par_item = item->parent();
  else
    par_item = item;

  for (int i = 0; i != list_images.size(); ++i) {
    QString image_name = list_images.at(i);
    AddImageItem(par_item, image_name);
  }
}

void Window::AddImageItem(QTreeWidgetItem *par_item, QString file_name) {
  QString note_text = GetGroupName(file_name);
  QTreeWidgetItem *item = new QTreeWidgetItem(kRowImage);

  item->setText(kColItem, note_text);
  item->setText(kColItemType, "Image");
  item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable |
                 Qt::ItemIsEnabled | Qt::ItemIsAutoTristate);
  item->setCheckState(kColItem, Qt::Checked);
  item->setData(kColItem, Qt::UserRole, QVariant(file_name));
  par_item->addChild(item);
}

void Window::DisplayImage(QTreeWidgetItem *item) {
  QString image_name = item->data(kColItem, Qt::UserRole).toString();
  lab_file_name->setText(image_name);
  cur_pixmap.load(image_name);
  on_actZoomFitH_triggered();
}

void Window::on_treeWidget_currentItemChanged(QTreeWidgetItem *current,
                                              QTreeWidgetItem *previous) {
  Q_UNUSED(previous);
  if (current == NULL) return;

  int var = current->type();
  switch (var) {
    case kRowTop:
      ui->actAddGroup->setEnabled(true);
      ui->actAddImages->setEnabled(true);
      ui->actDeleteImage->setDisabled(true);
      break;

    case kRowGroup:
      ui->actAddGroup->setEnabled(true);
      ui->actAddImages->setEnabled(true);
      ui->actDeleteImage->setEnabled(true);
      break;

    case kRowImage:
      ui->actAddGroup->setDisabled(true);
      ui->actAddImages->setEnabled(true);
      ui->actDeleteImage->setEnabled(true);
      DisplayImage(current);
      break;
  }
}

void Window::on_actDeleteImage_triggered() {
  QTreeWidgetItem *item = ui->treeWidget->currentItem();
  QTreeWidgetItem *par_item = item->parent();
  par_item->removeChild(item);
  delete item;
}

void Window::on_actScanImages_triggered() {
  for (int i = 0; i != ui->treeWidget->topLevelItemCount(); ++i) {
    QTreeWidgetItem *item = ui->treeWidget->topLevelItem(i);
    ChangeItemCaption(item);
  }
}

void Window::ChangeItemCaption(QTreeWidgetItem *item) {
  QString str = "*" + item->text(kColItem);
  item->setText(kColItem, str);

  if (item->childCount() > 0)
    for (int i = 0; i != item->childCount(); ++i) {
      ChangeItemCaption(item->child(i));
    }
}

void Window::on_actZoomFitH_triggered() {
  int h = ui->scrollArea->height();
  int real_h = cur_pixmap.height();
  pix_ratio = float(h) / real_h;
  QPixmap pix = cur_pixmap.scaledToHeight(h / 2);
  ui->label->setPixmap(pix);
}

void Window::on_actZoomFitW_triggered() {
  int w = ui->scrollArea->width();
  int real_w = cur_pixmap.width();
  pix_ratio = float(w) / real_w;
  QPixmap pix = cur_pixmap.scaledToWidth(w / 2);
  ui->label->setPixmap(pix);
}

void Window::on_actZoomRealSize_triggered() {
  pix_ratio = 1;
  ui->label->setPixmap(cur_pixmap);
}

void Window::on_actZoomIn_triggered() {
  pix_ratio = pix_ratio * 1.2;
  int w = pix_ratio * cur_pixmap.width();
  int h = pix_ratio * cur_pixmap.height();
  QPixmap pix = cur_pixmap.scaled(w, h);
  ui->label->setPixmap(pix);
}

void Window::on_dockWidget_visibilityChanged(bool visible) {
  ui->actDockVisible->setChecked(visible);
}

void Window::on_dockWidget_topLevelChanged(bool topLevel) {
  ui->actDockFloat->setChecked(topLevel);
}

void Window::on_actDockVisible_toggled(bool arg1) {
  ui->dockWidget->setVisible(arg1);
}

void Window::on_actZoomOut_triggered() {
  pix_ratio = pix_ratio / 1.2;
  int w = cur_pixmap.width() * pix_ratio;
  int h = cur_pixmap.height() * pix_ratio;
  QPixmap pix = cur_pixmap.scaled(w, h);
  ui->label->setPixmap(pix);
}

void Window::on_actDockFloat_toggled(bool arg1) {
  ui->dockWidget->setFloating(arg1);
}
