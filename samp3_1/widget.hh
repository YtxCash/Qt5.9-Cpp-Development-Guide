#ifndef WIDGET_HH
#define WIDGET_HH

#include <QWidget>
#include <person.hh>

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

 private:
  Ui::Widget *ui;
  Person *boy;
  Person *girl;
  void IniPerson();

 private slots:
  void on_ageChanged(int value);
  void on_spin_valueChanged(int arg1);
  void on_btnBoyAdd_clicked();
  void on_btnGirlAdd_clicked();
  void on_btnShowMeta_clicked();
};
#endif  // WIDGET_HH
