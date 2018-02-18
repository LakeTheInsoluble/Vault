#include "passengertrain.hh"

PassengerTrain::PassengerTrain(int number, QString type)
    : Train("Passenger", 100), // HACK
      number_ (number), type_ (type)
{}

void PassengerTrain::addTimetableRow(const QDateTime& time, 
                                     const QString& type, 
                                     Station* station)
{
    Q_ASSERT(time.isValid() && station != nullptr);
    PassengerTrain::TimeTableRow row;
    if (type.toLower() == "departure")
    {
        row.type = TimeTableRow::Type::departure;
    }
    else if (type.toLower() == "arrival")
    {
        row.type = TimeTableRow::Type::arrival;
    }
    else
    {
        return;
    }
    row.station = station;
    row.time = time;
    timeTable_.insert(time, row);
}

int PassengerTrain::number() const { return number_; }

QString PassengerTrain::type() const { return type_; }

QDateTime PassengerTrain::startTime() const { return timeTable_.firstKey(); }

QDateTime PassengerTrain::endTime() const { return timeTable_.lastKey(); }

bool PassengerTrain::hasTimeTable() const { return !timeTable_.isEmpty(); }

void PassengerTrain::validateTimetable()
{
    while (!timeTable_.empty() && timeTable_.first().type == TimeTableRow::Type::arrival)
    {
        timeTable_.remove(timeTable_.firstKey());
    }

    while (!timeTable_.empty() && timeTable_.last().type == TimeTableRow::Type::departure)
    {
        timeTable_.remove(timeTable_.lastKey());
    }
}

PassengerTrain::TimeTableRow PassengerTrain::latestRow(QDateTime time)
{
    Q_ASSERT(hasTimeTable() && time >= startTime());
    auto iter = timeTable_.lowerBound(time);
    if (iter != timeTable_.begin())
    {
        iter--;
    }
    return iter.value();
}

PassengerTrain::TimeTableRow PassengerTrain::nextRow(QDateTime time)
{
    Q_ASSERT(hasTimeTable() && time <= endTime());
    return timeTable_.upperBound(time).value();
}
