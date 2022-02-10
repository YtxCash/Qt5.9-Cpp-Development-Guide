#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QListWidgetItem>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_listWidget_customContextMenuRequested(const QPoint &pos);

  void on_acttIni_triggered();

  void on_actItemInsert_triggered();

  void on_actItemDelete_triggered();

  void on_actClear_triggered();

  void on_chkBox_stateChanged(int arg1);

  void on_actSelectAll_triggered();

  void on_actSeletcNon_triggered();

  void on_actSelInvs_triggered();

  void on_actItemAppend_triggered();

  void on_listWidget_currentItemChanged(QListWidgetItem *current,
                                        QListWidgetItem *previous);

 private:
  Ui::MainWindow *ui;

  void IniUi();
};
#endif  // MAINWINDOW_HH
