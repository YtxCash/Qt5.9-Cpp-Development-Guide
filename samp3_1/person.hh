#ifndef PERSON_HH
#define PERSON_HH

#include <QObject>

class Person : public QObject {
  Q_OBJECT
  Q_CLASSINFO("author", "wang")
  Q_CLASSINFO("company", "UPC")
  Q_CLASSINFO("version", "1.0.0")

  Q_PROPERTY(int Age READ Age WRITE SetAge NOTIFY AgeChanged)
  Q_PROPERTY(int score MEMBER m_score)
  Q_PROPERTY(QString name MEMBER m_name)

 public:
  explicit Person(QString name, QObject *parent = nullptr);

  int Age();
  void SetAge(int value);
  void IncAge();

 signals:
  void AgeChanged(int value);

 private:
  int m_age = 10;
  int m_score = 80;
  QString m_name;
};

#endif  // PERSON_HH
