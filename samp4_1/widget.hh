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
  void on_btnCal_clicked();
  void on_convert_clicked();

 private:
  Ui::Widget *ui;

  void IniDynaProperty();
  void IniSignalSlots();
};
#endif  // WIDGET_HH
