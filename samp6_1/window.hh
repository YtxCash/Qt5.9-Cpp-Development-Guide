#ifndef WINDOW_HH
#define WINDOW_HH

#include <QMainWindow>

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
  void on_btnFile_clicked();

  void on_btnFiles_clicked();

  void on_btnDir_clicked();

  void on_btnSave_clicked();

  void on_btnColor_clicked();

  void on_btnFont_clicked();

 private:
  Ui::Window *ui;
};
#endif  // WINDOW_HH
