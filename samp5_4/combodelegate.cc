#include "combodelegate.hh"

#include <QComboBox>

ComboDelegate::ComboDelegate(QObject *parent) : QStyledItemDelegate(parent) {}

QWidget *ComboDelegate::createEditor(QWidget *parent,
                                     const QStyleOptionViewItem &option,
                                     const QModelIndex &index) const {
  auto *editor = new QComboBox(parent);
  editor->setFrame(false);
  editor->addItem("One");
  editor->addItem("Two");
  editor->addItem("Three");
  editor->setCurrentIndex(0);
  return editor;
}

void ComboDelegate::setEditorData(QWidget *editor,
                                  const QModelIndex &index) const {
  int value = index.model()->data(index, Qt::DisplayRole).toInt();
  auto *combo_box = static_cast<QComboBox *>(editor);
  int ind = combo_box->findData(value);
  combo_box->setCurrentIndex(ind);
}

void ComboDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                 const QModelIndex &index) const {
  auto *combo_box = static_cast<QComboBox *>(editor);
  QString str = combo_box->currentText();
  model->setData(index, str, Qt::EditRole);
}

void ComboDelegate::updateEditorGeometry(QWidget *editor,
                                         const QStyleOptionViewItem &option,
                                         const QModelIndex &index) const {
  editor->setGeometry(option.rect);
}
