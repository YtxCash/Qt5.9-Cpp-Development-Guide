#include "person.hh"

#include "moc_person.cpp"

Person::Person(QString name, QObject *parent) : QObject(parent) {
  m_name = name;
}

int Person::Age() { return m_age; }

void Person::SetAge(int value) {
  m_age = value;
  emit AgeChanged(m_age);
}

void Person::IncAge() {
  m_age++;
  emit AgeChanged(m_age);
}
