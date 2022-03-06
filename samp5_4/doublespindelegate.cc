#include "doublespindelegate.hh"

#include <QDoubleSpinBox>

DoubleSpinDelegate::DoubleSpinDelegate(QObject *parent)
    : QStyledItemDelegate(parent) {}

QWidget *DoubleSpinDelegate::createEditor(QWidget *parent,
                                          const QStyleOptionViewItem &option,
                                          const QModelIndex &index) const {
  auto *editor = new QDoubleSpinBox(parent);
  editor->setFrame(false);
  editor->setMinimum(0);
  editor->setMaximum(1000);
  editor->setButtonSymbols(QAbstractSpinBox::NoButtons);
  return editor;
}

void DoubleSpinDelegate::setEditorData(QWidget *editor,
                                       const QModelIndex &index) const {
  int value = index.model()->data(index, Qt::EditRole).toInt();
  auto *double_spin_box = static_cast<QDoubleSpinBox *>(editor);
  double_spin_box->setValue(value);
}

void DoubleSpinDelegate::setModelData(QWidget *editor,
                                      QAbstractItemModel *model,
                                      const QModelIndex &index) const {
  auto *double_spin_box = static_cast<QDoubleSpinBox *>(editor);
  double_spin_box->interpretText();
  int value = double_spin_box->value();
  model->setData(index, value, Qt::EditRole);
}

void DoubleSpinDelegate::updateEditorGeometry(
    QWidget *editor, const QStyleOptionViewItem &option,
    const QModelIndex &index) const {
  editor->setGeometry(option.rect);
}
