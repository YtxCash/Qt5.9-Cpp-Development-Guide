#include "widget.hh"

#include <QMetaProperty>

#include "./ui_widget.h"
#include "moc_widget.cpp"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);
  IniPerson();
}

Widget::~Widget() { delete ui; }

void Widget::IniPerson() {
  boy = new Person("Xiao Ming");
  boy->setProperty("score", 97);
  boy->setProperty("age", 20);
  boy->setProperty("sex", "boy");
  connect(boy, &Person::ageChanged, this, &Widget::on_ageChanged);

  girl = new Person("Li Li");
  girl->setProperty("age", 18);
  girl->setProperty("score", 60);
  girl->setProperty("sex", "girl");
  connect(girl, &Person::ageChanged, this, &Widget::on_ageChanged);

  ui->spinBoyAge->setProperty("isBoy", true);
  ui->spinGirlAge->setProperty("isBoy", false);

  connect(ui->spinBoyAge, SIGNAL(valueChanged(int)), this,
          SLOT(on_spin_valueChanged(int)));
  connect(ui->spinGirlAge, SIGNAL(valueChanged(int)), this,
          SLOT(on_spin_valueChanged(int)));
}

void Widget::on_ageChanged(int value) {
  Q_UNUSED(value);

  Person *aPerson = qobject_cast<Person *>(sender());
  QString hisName = aPerson->property("name").toString();
  QString hisSex = aPerson->property("sex").toString();
  int hisAge = aPerson->age();
  ui->textEdit->append(hisName + "," + hisSex +
                       QString::asprintf(",Age %d", hisAge));
}

void Widget::on_spin_valueChanged(int arg1) {
  Q_UNUSED(arg1);
  QSpinBox *spinBox = qobject_cast<QSpinBox *>(sender());
  if (spinBox->property("isBoy").toBool())
    boy->setAge(spinBox->value());
  else
    girl->setAge(spinBox->value());
}

void Widget::on_btnBoyAdd_clicked() { boy->incAge(); }

void Widget::on_btnGirlAdd_clicked() { girl->incAge(); }

void Widget::on_btnShowMeta_clicked() {
  const QMetaObject *meta = boy->metaObject();
  ui->textEdit->clear();
  ui->textEdit->append("==Meta Information");
  ui->textEdit->append(QString("Class Name: %1\n").arg(meta->className()));
  ui->textEdit->append("Property");
  for (int i = meta->propertyOffset(); i != meta->propertyCount(); ++i) {
    QMetaProperty prop = meta->property(i);
    const char *propName = prop.name();
    QString propValue = boy->property(propName).toString();
    ui->textEdit->append(QString("%1, %2").arg(propName, propValue));
  }

  ui->textEdit->append("");
  ui->textEdit->append("class info");
  for (int i = meta->classInfoOffset(); i != meta->classInfoCount(); ++i) {
    QMetaClassInfo classInfo = meta->classInfo(i);
    ui->textEdit->append(QString("Name: %1, Value: %2")
                             .arg(classInfo.name(), classInfo.value()));
  }
}
