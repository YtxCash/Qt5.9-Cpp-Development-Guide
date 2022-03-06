#include "intspindelegate.hh"

#include <QSpinBox>

IntSpinDelegate::IntSpinDelegate() {}

QWidget *IntSpinDelegate::createEditor(QWidget *parent,
                                       const QStyleOptionViewItem &option,
                                       const QModelIndex &index) const {
  auto *editor = new QSpinBox(parent);
  editor->setFrame(false);
  editor->setMinimum(0);
  editor->setMaximum(1000);
  editor->setButtonSymbols(QAbstractSpinBox::NoButtons);
  return editor;
}

void IntSpinDelegate::setEditorData(QWidget *editor,
                                    const QModelIndex &index) const {
  int value = index.model()->data(index, Qt::EditRole).toInt();
  auto *spin_box = static_cast<QSpinBox *>(editor);
  spin_box->setValue(value);
}

void IntSpinDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                   const QModelIndex &index) const {
  auto *spin_box = static_cast<QSpinBox *>(editor);
  spin_box->interpretText();
  int value = spin_box->value();
  model->setData(index, value, Qt::EditRole);
}

void IntSpinDelegate::updateEditorGeometry(QWidget *editor,
                                           const QStyleOptionViewItem &option,
                                           const QModelIndex &index) const {
  editor->setGeometry(option.rect);
}
