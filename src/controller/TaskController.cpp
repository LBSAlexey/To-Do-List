//
// Created by Лёха on 09.08.2025.
//

#include "TaskController.h"

TaskController::TaskController(TaskList &t): taskList() {
    this->taskList = t;
}

void TaskController::addTask(int id, std::string &title, std::string &description, wxDateTime &finisDate, bool complete) const {
    if ((title.empty() || description.empty()) && finisDate.IsEarlierThan(wxDateTime::Now()) && finisDate.IsEqualTo(wxDateTime::Now())) {
        throw std::invalid_argument("Название или описание не могут быть пустыми. Дата выполнения задачи не может быть задано ранее или в точь-точь");
    } else if (finisDate.IsEarlierThan(wxDateTime::Now()) && finisDate.IsEqualTo(wxDateTime::Now())) {
        throw std::invalid_argument("Дата выполнения задачи не может быть задано ранее или в точь-точь");
    } else if (title.empty() || description.empty()) {
        throw std::invalid_argument("Название или описание не могут быть пустыми");
    }
    taskList.addTask(title, description, finisDate, complete);
}

void TaskController::removeTask(int id) const{
    if (id < 0) { throw std::invalid_argument("Id не может быть отрицательным"); }
    taskList.removeTask(id);
}

void TaskController::editTask(int id, std::string &title, std::string &description, wxDateTime &finisDate, bool complete) const {
    if ((title.empty() || description.empty())
        && finisDate.IsEarlierThan(wxDateTime::Now())
        && finisDate.IsEqualTo(wxDateTime::Now())) {
        throw std::invalid_argument("Название или описание не могут быть пустыми. "
                                    "Дата выполнения задачи не может быть задано ранее или в точь-точь. "
                                    "Id не может быть отрицательным");
    } else if (finisDate.IsEarlierThan(wxDateTime::Now()) && finisDate.IsEqualTo(wxDateTime::Now())) {
        throw std::invalid_argument("Дата выполнения задачи не может быть задано ранее или в точь-точь");
    } else if (title.empty() || description.empty()) {
        throw std::invalid_argument("Название или описание не могут быть пустыми");
    } else if (id < 0) { throw std::invalid_argument("Id не может быть отрицательным"); }
    taskList.editTask(id, title,description, finisDate, complete);
}

void TaskController::getTask(int id) const {
    if (id < 0) { throw std::invalid_argument("Id не может быть отрицательным"); }
    taskList.getTask(id);
}

void TaskController::loadTaskFromFile(std::string &filePath) const {
    if (filePath.empty()) {
        throw std::invalid_argument("путь не может быть пустым");
    }
    try {taskList.loadFromJson(filePath);}
    catch (std::exception &e) {throw std::invalid_argument(e.what());}
}

void TaskController::saveTaskToFile(std::string &filePath) const {
    if (filePath.empty()) {
        throw std::invalid_argument("путь не может быть пустым");
    }
    try {taskList.saveToJson(filePath);}
    catch (std::exception &e) {throw std::invalid_argument(e.what());}
}

TaskController::~TaskController() = default;



