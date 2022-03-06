#ifndef INTSPINDELEGATE_HH
#define INTSPINDELEGATE_HH

#include <QStyledItemDelegate>

class IntSpinDelegate : public QStyledItemDelegate {
 public:
  IntSpinDelegate();

  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                        const QModelIndex &index) const override;
  void setEditorData(QWidget *editor, const QModelIndex &index) const override;
  void setModelData(QWidget *editor, QAbstractItemModel *model,
                    const QModelIndex &index) const override;
  void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                            const QModelIndex &index) const override;
};

#endif  // INTSPINDELEGATE_HH
