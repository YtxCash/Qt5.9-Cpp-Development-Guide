#include "widget.hh"

#include "./ui_widget.h"
#include "moc_widget.cpp"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);

  IniTimer();
}

Widget::~Widget() { delete ui; }

void Widget::on_btnCurrent_clicked() {
  QDateTime current = QDateTime::currentDateTime();
  ui->timeEdit->setTime(current.time());
  ui->lineEditTime->setText(current.time().toString("hh:mm AP"));
  ui->dateEdit->setDate(current.date());
  ui->lineEditDate->setText(current.date().toString("yyyy-MM-dd"));
  ui->dateTimeEdit->setDateTime(current);
  ui->lineEditDateTime->setText(current.toString("yyyy-MM-dd hh:mm:ss"));
}

void Widget::on_btnTime_clicked() {
  QString str = ui->lineEditTime->text();
  str = str.trimmed();
  if (!str.isEmpty()) {
    QTime t = QTime::fromString(str, "hh:mm AP");
    ui->timeEdit->setTime(t);
  }
}

void Widget::on_btnDate_clicked() {
  QString str = ui->lineEditDate->text();
  str = str.trimmed();
  if (!str.isEmpty()) {
    QDate d = QDate::fromString(str, "yyyy-MM-dd");
    ui->dateEdit->setDate(d);
  }
}

void Widget::on_btnDateTime_clicked() {
  QString str = ui->lineEditDateTime->text();
  str = str.trimmed();
  if (!str.isEmpty()) {
    QDateTime dt = QDateTime::fromString(str, "yyyy-MM-dd hh:mm:ss");
    ui->dateTimeEdit->setDateTime(dt);
  }
}

void Widget::on_calendarWidget_selectionChanged() {
  QDate date = ui->calendarWidget->selectedDate();
  ui->lineEditSeletedDate->setText(date.toString("yyyy-MM-dd"));
}

void Widget::on_timer_timeout() {
  QTime curTime = QTime::currentTime();
  ui->lcdHour->display(curTime.hour());
  ui->lcdMin->display(curTime.minute());
  ui->lcdSec->display(curTime.second());

  int val = ui->progressBar->value();
  ++val;
  if (val > 100) val = 0;
  ui->progressBar->setValue(val);
}

void Widget::IniTimer() {
  timer = new QTimer(this);
  timer->stop();
  timer->setInterval(1000);
  connect(timer, SIGNAL(timeout()), this, SLOT(on_timer_timeout()));
}

void Widget::on_btnStart_clicked() {
  timer->start();
  time_count.start();
  ui->btnStart->setDisabled(true);
  ui->btnStop->setEnabled(true);
  ui->btnPeriod->setDisabled(true);
}

void Widget::on_btnStop_clicked() {
  timer->stop();
  int tmMsec = time_count.elapsed();
  int ms = tmMsec % 1000;
  int sec = tmMsec / 1000;
  QString str = QString::asprintf("%d seconds, %d mseconds", sec, ms);
  ui->labelFlow->setText(str);
  ui->btnStart->setEnabled(true);
  ui->btnStop->setDisabled(true);
  ui->btnPeriod->setEnabled(true);
}

void Widget::on_btnPeriod_clicked() {
  timer->setInterval(ui->spinBox->value());
}
