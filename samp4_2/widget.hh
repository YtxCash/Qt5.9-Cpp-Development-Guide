#ifndef WIDGET_HH
#define WIDGET_HH

#include <QCursor>
#include <QHash>
#include <QPoint>
#include <QPushButton>
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
  void on_btn_clicked();

 private:
  Ui::Widget *ui;
  void IniSignalSlots();

  void IniHash();
  QStringList str_list;
  QHash<QString, int> hash;

  QPushButton *btnClicked;

  //  QString str1;
  //  QString str2;
};
#endif  // WIDGET_HH
