//
// Created by Лёха on 09.08.2025.
//

#include "TaskList.h"
#include <iostream>
#include <wx/log.h>
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
bool TaskList::saveToJson(const std::string& path) {
    std::ofstream file(path, std::ios::trunc);
    if (!file) return false;

    nlohmann::json newJArray = nlohmann::json::array();
    for (const auto& [id, task] : tasks) {
        // Сохраняем даты в UTC для избежания проблем с часовыми поясами
        wxDateTime startDate = task.getDateNow();
        wxDateTime finishDate = task.getDateFinish();

        // Преобразуем в UTC перед сохранением
        if (startDate.IsValid()) startDate.MakeUTC();
        if (finishDate.IsValid()) finishDate.MakeUTC();

        std::string startDateStr = startDate.IsValid() ?
            startDate.FormatISOCombined(' ').ToUTF8().data() :
            wxDateTime::Now().MakeUTC().FormatISOCombined(' ').ToUTF8().data();

        std::string finishDateStr = finishDate.IsValid() ?
            finishDate.FormatISOCombined(' ').ToUTF8().data() :
            wxDateTime::Now().MakeUTC().FormatISOCombined(' ').ToUTF8().data();

        newJArray.push_back({
            {"id", task.getId()},
            {"title", task.getTitle()},
            {"description", task.getDescription()},
            {"completed", task.getCompleted()},
            {"startDate", startDateStr},
            {"finishDate", finishDateStr}
        });
    }

    try {
        file << newJArray.dump(4);
        return true;
    } catch (const std::exception& e) {
        wxLogError("Error saving JSON: %s", e.what());
        return false;
    }
}

bool TaskList::loadFromJson(const std::string& path) {
    std::ifstream file(path);
    if (!file) {
        wxLogMessage("File does not exist: %s", path);
        return false;
    }

    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    if (size == 0) {
        wxLogMessage("File is empty: %s", path);
        return false;
    }
    file.seekg(0, std::ios::beg);

    try {
        file >> jArray;
        tasks.clear();

        for (const auto& item : jArray) {
            int id = item["id"];
            std::string title = item["title"];
            std::string description = item["description"];
            bool completed = item["completed"];

            // Парсим даты и преобразуем из UTC в локальное время
            wxDateTime startDate, finishDate;
            std::string startStr = item["startDate"];
            std::string finishStr = item["finishDate"];

            if (startDate.ParseISOCombined(wxString::FromUTF8(startStr))) {
                startDate.MakeFromUTC(); // Преобразуем из UTC в локальное время
            } else {
                startDate = wxDateTime::Now();
            }

            if (finishDate.ParseISOCombined(wxString::FromUTF8(finishStr))) {
                finishDate.MakeFromUTC(); // Преобразуем из UTC в локальное время
            } else {
                finishDate = wxDateTime::Now();
                finishDate.Add(wxDateSpan(0, 0, 0, 1)); // Добавляем 1 день
            }

            Task task(id, title, description, finishDate, startDate, completed);
            tasks.emplace(id, task);
        }
        return true;
    } catch (const std::exception& e) {
        wxLogError("Error loading JSON: %s", e.what());
        return false;
    }
}
// возвращает хэш-таблицу со всеми задачами
const std::unordered_map<int, Task> & TaskList::getTasks() const {
    return tasks;
}

TaskList::~TaskList() = default;
