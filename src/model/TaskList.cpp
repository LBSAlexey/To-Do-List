//
// Created by Лёха on 09.08.2025.
//

#include "TaskList.h"
#include <iostream>

TaskList::TaskList() {

}
// добавляем задачу в хэш-таблицу
void TaskList::addTask(const std::string &newTitle, const std::string &newDescription, const wxDateTime & newFinishDate, bool completed) {
    Task t(newTitle, newDescription, newFinishDate, completed);
    tasks.try_emplace(t.getId(), std::move(t)); // добавляем хэш-таблицу по ключу id
}
// удаляет задачу из таблицы по id
bool TaskList::removeTask(int id) {
    auto key = tasks.find(id);
    if (key != tasks.end()) {
        tasks.erase(key->first);
        return true;
    }
    return false;
}
// изменяет задачу по id
bool TaskList::editTask(int id, const std::string &newTitle, const std::string& newDescription, const wxDateTime &newFinisDate, bool completed) {
    auto key = tasks.find(id);
    if (key != tasks.end()) {
        key->second.setTitle(newTitle);
        key->second.setDescription(newDescription);
        key->second.setDateFinish(newFinisDate);
        key->second.setComplete(completed);
        return true;
    }
    return false;
}
// возвращает задачу по id
Task *TaskList::getTask(int id)  {
    auto key = tasks.find(id);
    if (key != tasks.end()) {
        return &(key->second);
    }
    return nullptr;
}
// загружает задачи из json
bool TaskList::loadFromJson(const std::string& path) {
    std::ifstream file(path);
    if (!file) return false;

    file >> jArray;
    for (const auto& item : jArray) {
        int id = item["id"].get<int>();
        std::string title = item["title"];
        std::string description = item["description"];
        bool completed = item["completed"];
        wxDateTime startDate, finishDate;
        startDate.ParseISOCombined(item["startDate"].get<std::string>());
        finishDate.ParseISOCombined(item["finishDate"].get<std::string>());
        Task t(id,title, description, finishDate, startDate,completed);
        tasks.emplace(t.getId(), t);
    }
    return true;
}
// сохраняет задачи в json
bool TaskList::saveToJson(const std::string& path) {
    std::ofstream file(path, std::ios::trunc);
    if (!file)  return false;

    nlohmann::json newJArray = nlohmann::json::array();
    for (const auto& [id, task] : tasks) {
        newJArray.push_back({
            {"id", task.getId()},
            {"title", task.getTitle()},
            {"description", task.getDescription()},
            {"completed", task.getCompleted()},
            {"startDate", task.getDateNow().FormatISOCombined(' ')},
            {"finishDate", task.getDateFinish().FormatISOCombined(' ')}
        });
    }
    file << newJArray.dump(4);
    return true;
}
// возвращает хэш-таблицу со всеми задачами
const std::unordered_map<int, Task> & TaskList::getTasks() const {
    return tasks;
}

TaskList::~TaskList() = default;
