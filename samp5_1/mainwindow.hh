#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QFileSystemModel>
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
  void on_treeView_clicked(const QModelIndex &index);

 private:
  Ui::MainWindow *ui;

  QFileSystemModel *mode;

  void IniUi();
};
#endif  // MAINWINDOW_HH
