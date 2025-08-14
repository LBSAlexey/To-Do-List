//
// Created by Лёха on 09.08.2025.
//

#include "Task.h"

int Task::nId = 0;

Task::Task(const std::string& name, const std::string& description, const wxDateTime& dateFinish, bool completed) {
    this->title = name;
    this->description = description;
    this->finish = dateFinish;
    this->start = wxDateTime::Now();
    this->completed = completed;
    this->id = ++nId;
}

// геттеры
const wxDateTime& Task::getDateFinish() const {
    return finish;
}

const wxDateTime& Task::getDateNow() const{
    return start;
}


const std::string& Task::getTitle() const{
    return this->title;
}

const std::string& Task::getDescription() const{
    return this->description;
}

const int Task::getId() const {
    return this->id;
}
// сеттеры

bool Task::setDateFinish(const wxDateTime &dateFinish) {
    if (dateFinish.IsEarlierThan(wxDateTime::Now())) {
        return false; // нельзя ставить дату в прошлом
    }
    this->finish = dateFinish;
    return true;
}

void Task::setTitle(const std::string &title) {
    this->title = title;
}

void Task::setDescription(const std::string &description) {
    this->description = description;
}

//
bool Task::IsOverdue() const {
    return !completed && (finish.IsEarlierThan(wxDateTime::Now()) || finish.IsEqualTo(wxDateTime::Now()));
}

wxTimeSpan Task::TimeRemaining() const {
    return finish.Subtract(wxDateTime::Now());
}