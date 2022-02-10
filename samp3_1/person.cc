#include "person.hh"

#include "moc_person.cpp"

Person::Person(QString name, QObject *parent) : QObject(parent) {
  m_name = name;
}

int Person::age() { return m_age; }

void Person::setAge(int value) {
  m_age = value;
  emit ageChanged(m_age);
}

void Person::incAge() {
  m_age++;
  emit ageChanged(m_age);
}
