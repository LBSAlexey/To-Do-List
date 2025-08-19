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

bool TaskController::loadTaskFromFile(const std::string& filePath) const {
    if (filePath.empty()) {
        wxLogWarning("Empty file path");
        return false;
    }

    // Проверяем существование файла
    if (!wxFileExists(filePath)) {
        wxLogMessage("File does not exist: %s", filePath);
        return false;
    }

    // Проверяем, не пустой ли файл
    wxFile file(filePath);
    if (file.Length() == 0) {
        wxLogMessage("File is empty: %s", filePath);
        return false;
    }
    file.Close();

    try {
        return taskList.loadFromJson(filePath);
    } catch (const std::exception& e) {
        wxLogError("Error loading tasks: %s", e.what());
        return false;
    }
}

bool TaskController::saveTaskToFile(const std::string& filePath) const {
    if (filePath.empty()) {
        wxLogWarning("Empty file path");
        return false;
    }

    // Создаем директорию, если она не существует
    wxFileName fn(filePath);
    if (!fn.DirExists()) {
        if (!fn.Mkdir(wxS_DIR_DEFAULT, wxPATH_MKDIR_FULL)) {
            wxLogError("Cannot create directory: %s", fn.GetPath());
            return false;
        }
    }

    try {
        return taskList.saveToJson(filePath);
    } catch (const std::exception& e) {
        wxLogError("Error saving tasks: %s", e.what());
        return false;
    }
}

std::unordered_map<int, Task> TaskController::getAllTasks() const {
    try {
        auto tasks = taskList.getTasks();
        if (tasks.empty()) {
            wxLogMessage("Task list is empty");
        }
        return tasks;
    } catch (const std::exception& e) {
        wxLogError("Error getting tasks: %s", e.what());
        return std::unordered_map<int, Task>();
    }
}

TaskController::~TaskController() = default;



