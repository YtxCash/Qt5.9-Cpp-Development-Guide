#ifndef WIDGET_HH
#define WIDGET_HH

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget {
  Q_OBJECT

 public:
  Widget(QWidget *parent = nullptr);
  ~Widget();

 private slots:
  void on_sliderColor_valueChanged(int value);

  void on_dial_valueChanged(int value);

  void on_rBtnBin_clicked();

 private:
  Ui::Widget *ui;
  void IniSignalSlots();
  void IniDynaProp();
};
#endif  // WIDGET_HH
