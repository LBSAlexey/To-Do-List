//
// Created by Лёха on 09.08.2025.
//

#include "TaskList.h"

#include <iostream>

TaskList::TaskList() {
    if (jArray.empty()) {
         try {
             loadFromJson("tasks.json");
         } catch (std::exception &e) {
             std::cout << e.what() << '\n';
         }
    }
}

void TaskList::AddTask(const std::string &newTitle, const std::string &newDescription, const wxDateTime & newFinishDate, bool completed) {
    Task t(newTitle, newDescription, newFinishDate, completed);
    tasks[t.getId()] = t; // добавляем хэш-таблицу по ключу id
}

bool TaskList::removeTask(int id) {
    auto key = tasks.find(id);
    if (key != tasks.end()) {
        tasks.erase(key->first);
        return true;
    }
    return false;
}

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

Task *TaskList::getTask(int id)  {
    auto key = tasks.find(id);
    if (key != tasks.end()) {
        return &(key->second);
    }
    return nullptr;
}

bool TaskList::loadFromJson(const std::string& path) {
    std::fstream file(path);
    if (!file.is_open() || !file.good()) {
        return false;
    }
    file >> jArray;
    for (const auto& item : jArray) {
        std::string title = item["title"];
        std::string description = item["description"];
        bool completed = item["completed"];
        wxDateTime startDate;
        wxDateTime finishDate;
        startDate.ParseISOCombined(item["startDate"].get<std::string>());
        finishDate.ParseISOCombined(item["finishDate"].get<std::string>());
        Task t(title, description, finishDate, completed);
        tasks.emplace(t.getId(), t);
    }
    return true;
}

bool TaskList::saveToJson(const std::string& path) {
    std::fstream file(path);
    if (!file.is_open() || !file.good()) {
        return false;
    }
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
