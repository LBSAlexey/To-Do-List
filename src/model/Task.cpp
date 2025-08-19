//
// Created by Лёха on 09.08.2025.
//

#include "Task.h"

#include <iostream>

int Task::nId = 0;
// конструктор который создаёт задачу
Task::Task(const std::string& name, const std::string& description, const wxDateTime& dateFinish, bool completed) {
    this->title = name;
    this->description = description;
    this->finish = dateFinish;
    this->start = wxDateTime::Now();
    this->completed = completed;
    this->id = ++nId;
}

Task::Task(int id, const std::string& name, const std::string& description, const wxDateTime& dateFinish, const wxDateTime& dateStart, bool completed) {
    this->id = id;
    this->title = name;
    this->description = description;
    this->finish = dateFinish;
    this->start = dateStart;
    this->completed = completed;

    // Обновляем статический счетчик ID
    if (id >= nId) {
        nId = id + 1;
    }
}

void Task::setId(int id) {
    this->id = id;
    // Обновляем статический счетчик ID
    if (id >= nId) {
        nId = id + 1;
    }
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

const bool Task::getCompleted() const {
    return this->completed;
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

bool Task::setDateNow(const wxDateTime &dateStart) {
    this->start = dateStart;
}

void Task::setComplete(const bool completed) {
    this->completed = completed;
}

void Task::setTitle(const std::string &title) {
    this->title = title;
}

void Task::setDescription(const std::string &description) {
    this->description = description;
}

// проверка на просорчку задания
bool Task::IsOverdue() const {
    return !completed && (finish.IsEarlierThan(wxDateTime::Now()) || finish.IsEqualTo(wxDateTime::Now()));
}
// сколько осталось до выполнения задачи
wxTimeSpan Task::TimeRemaining() const {
    return finish.Subtract(wxDateTime::Now());
}