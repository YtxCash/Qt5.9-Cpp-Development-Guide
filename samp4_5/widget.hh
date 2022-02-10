#ifndef WIDGET_HH
#define WIDGET_HH

#include <QElapsedTimer>
#include <QTimer>
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
  void on_btnCurrent_clicked();

  void on_btnTime_clicked();

  void on_btnDate_clicked();

  void on_btnDateTime_clicked();

  void on_calendarWidget_selectionChanged();

  void on_timer_timeout();

  void on_btnStart_clicked();

  void on_btnStop_clicked();

  void on_btnPeriod_clicked();

 private:
  Ui::Widget *ui;
  QTimer *timer;
  QElapsedTimer time_count;

  void IniTimer();
};
#endif  // WIDGET_HH
