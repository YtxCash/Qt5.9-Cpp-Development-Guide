#ifndef WINDOW_HH
#define WINDOW_HH

#include <QMainWindow>
#include <QStringListModel>

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

 private slots:

  void on_btnResetList_clicked();

  void on_btnAddItem_clicked();

  void on_btnInsertItem_clicked();

  void on_btnDeleteCurItem_clicked();

  void on_btnCleanList_clicked();

  void on_btnCleanText_clicked();

  void on_btnShowModeString_clicked();

  void on_listView_clicked(const QModelIndex &index);

 private:
  Ui::Window *ui;
  QStringListModel *mode;
  QStringList str_list;

  void IniUi();
};
#endif  // WINDOW_HH
