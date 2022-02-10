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
  void on_btnIniSImplify_clicked();

  void on_chkBoxEditable_toggled(bool checked);

  void on_chkBoxReadOnly_toggled(bool checked);

  void on_btnIniCities_clicked();

  void on_btnCleanText_clicked();

  void on_btnAddText_clicked();

 private:
  Ui::Widget *ui;

  QStringList list;
};
#endif  // WIDGET_HH
