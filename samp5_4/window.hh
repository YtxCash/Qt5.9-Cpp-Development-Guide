#ifndef WINDOW_HH
#define WINDOW_HH

#include <QItemSelectionModel>
#include <QLabel>
#include <QMainWindow>
#include <QStandardItemModel>
#include <combodelegate.hh>
#include <doublespindelegate.hh>
#include <intspindelegate.hh>

QT_BEGIN_NAMESPACE
namespace Ui {
class Window;
}
QT_END_NAMESPACE

class Window : public QMainWindow {
  Q_OBJECT

 public:
  Window(QWidget *parent = nullptr);
  ~Window();

 private:
  Ui::Window *ui;

  IntSpinDelegate int_delegate;
  DoubleSpinDelegate double_delegate;
  ComboDelegate combo_delegate;

  QLabel *lab_cur_file;
  QLabel *lab_cell_pos;
  QLabel *lab_cell_text;

  QStandardItemModel *model_data;
  QItemSelectionModel *model_select;

  void IniModel(QStringList &list);
  void IniUi();

  const int kFixedColumnCount = 6;

  QModelIndex index;
  QStandardItem *item;
  QModelIndexList index_list;

 private slots:
  void onCurrentChanged(const QModelIndex &current,
                        const QModelIndex &previous);
  void on_actOpen_triggered();
  void on_actAppend_triggered();
  void on_actInsert_triggered();
  void on_actDelete_triggered();
  void on_actAlignRight_triggered();
  void on_actAlignLeft_triggered();
  void on_actAlignCenter_triggered();
  void on_actFontBlod_triggered(bool checked);
  void on_actSave_triggered();
};
#endif  // WINDOW_HH
