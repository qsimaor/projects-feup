//
// Created by gonzallito on 15-10-2022.
//

#include "Classes.h"

Classes::Classes() {}

Classes::Classes(const string &classCode, const string &ucCode, const string &weekday, float startHour, float duration,
                 const string &type) : classCode(classCode), ucCode(ucCode), startHour(startHour),
                                       duration(duration), type(type)
                                            {
                                            if (weekday == "Monday")
                                                this->weekday = Monday;
                                            if (weekday == "Tuesday")
                                                this->weekday = Tuesday;
                                            if (weekday == "Wednesday")
                                                this->weekday = Wednesday;
                                            if (weekday == "Thursday")
                                                this->weekday = Thursday;
                                            if (weekday == "Friday")
                                                this->weekday = Friday;
                                            }

const string &Classes::getClassCode() const {
    return classCode;
}

const string &Classes::getUcCode() const {
    return ucCode;
}

const DaysOfWeek &Classes::getWeekday() const {
    return weekday;
}

float Classes::getStartHour() const {
    return startHour;
}

float Classes::getDuration() const {
    return duration;
}

const string &Classes::getType() const {
    return type;
}

void Classes::setClassCode(const string &classCode) {
    Classes::classCode = classCode;
}

void Classes::setUcCode(const string &ucCode) {
    Classes::ucCode = ucCode;
}

void Classes::setWeekday(const DaysOfWeek &weekday) {
    Classes::weekday = weekday;
}

void Classes::setStartHour(float startHour) {
    Classes::startHour = startHour;
}

void Classes::setDuration(float duration) {
    Classes::duration = duration;
}

void Classes::setType(const string &type) {
    Classes::type = type;
}

ostream &operator<<(ostream &os, const Classes &classes) {
    os << "classCode: " << classes.classCode << " ucCode: " << classes.ucCode << " weekday: " << classes.weekday
       << " startHour: " << classes.startHour << " duration: " << classes.duration << " type: " << classes.type;
    return os;
}
