//
// Created by Лёха on 09.08.2025.
//

#include "TaskController.h"

TaskController::TaskController(TaskList &t): taskList(t) {};

void TaskController::addTask(const std::string &title,const std::string &description,const wxDateTime &finisDate, bool complete) const {
    if ((title.empty() || description.empty()) && (finisDate.IsEarlierThan(wxDateTime::Now()) || finisDate.IsEqualTo(wxDateTime::Now()))) {
        throw std::invalid_argument("Название или описание не могут быть пустыми. Дата выполнения задачи не может быть задано ранее или в точь-точь");
    } else if (finisDate.IsEarlierThan(wxDateTime::Now()) || finisDate.IsEqualTo(wxDateTime::Now())) {
        throw std::invalid_argument("Дата выполнения задачи не может быть задано ранее или в точь-точь");
    } else if (title.empty() || description.empty()) {
        throw std::invalid_argument("Название или описание не могут быть пустыми");
    }
    taskList.addTask(title, description, finisDate, complete);
}

bool TaskController::removeTask(int id) const{
    if (id < 0) { throw std::invalid_argument("Id не может быть отрицательным"); }
    taskList.removeTask(id);
    return true;
}

void TaskController::editTask(int id, const std::string &title, const std::string &description, const wxDateTime &finisDate,  bool complete) const {
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

Task* TaskController::getTask(int id) const {
    if (id < 0) { throw std::invalid_argument("Id не может быть отрицательным"); }
    return this->taskList.getTask(id);
}

bool TaskController::loadTaskFromFile(const std::string &filePath) const {
    if (filePath.empty()) {
        throw std::invalid_argument("путь не может быть пустым");
    }
    try {
        taskList.loadFromJson(filePath);
        return true;
    }
    catch (std::exception &e) {throw std::invalid_argument(e.what());}
}

bool TaskController::saveTaskToFile(const std::string &filePath) const {
    if (filePath.empty()) {
        throw std::invalid_argument("путь не может быть пустым");
    }
    try {
        taskList.saveToJson(filePath);
        return true;
    }
    catch (std::exception &e) {throw std::invalid_argument(e.what());}
}

std::unordered_map<int, Task> TaskController::getAllTasks() const {
    return !taskList.getTasks().empty() ?  taskList.getTasks() : throw std::invalid_argument("пустой объект");

}

TaskController::~TaskController() = default;



