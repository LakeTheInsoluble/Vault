#include "medal.hh"

Medal::Medal(QObject *parent) : QObject(parent), name_() {}

Medal::Medal(QString name, QObject *parent) : QObject(parent), name_(name) {}

QString Medal::name() const { return name_; }

void Medal::setName(QString newName)
{
    name_ = newName;
    emit nameChanged(newName);
}
