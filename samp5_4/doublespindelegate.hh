#ifndef DOUBLESPINDELEGATE_HH
#define DOUBLESPINDELEGATE_HH

#include <QStyledItemDelegate>

class DoubleSpinDelegate : public QStyledItemDelegate {
 public:
  explicit DoubleSpinDelegate(QObject *parent = nullptr);

  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                        const QModelIndex &index) const override;
  void setEditorData(QWidget *editor, const QModelIndex &index) const override;
  void setModelData(QWidget *editor, QAbstractItemModel *model,
                    const QModelIndex &index) const override;
  void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                            const QModelIndex &index) const override;
};

#endif  // DOUBLESPINDELEGATE_HH
