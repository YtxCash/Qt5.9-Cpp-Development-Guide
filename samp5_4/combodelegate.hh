#ifndef COMBODELEGATE_HH
#define COMBODELEGATE_HH

#include <QStyledItemDelegate>

class ComboDelegate : public QStyledItemDelegate {
 public:
  explicit ComboDelegate(QObject *parent = nullptr);

  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                        const QModelIndex &index) const override;
  void setEditorData(QWidget *editor, const QModelIndex &index) const override;
  void setModelData(QWidget *editor, QAbstractItemModel *model,
                    const QModelIndex &index) const override;
  void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                            const QModelIndex &index) const override;
};

#endif  // COMBODELEGATE_HH
