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
    std::ofstream file(path, std::ios::trunc | std::ios::binary);
    if (!file) return false;

    nlohmann::json newJArray = nlohmann::json::array();
    for (const auto& [id, task] : tasks) {
        // Для дат: форматируем и преобразуем в std::string
        wxString startDateWxStr = task.getDateNow().IsValid() ?
            task.getDateNow().FormatISOCombined(' ') :
            wxDateTime::Now().FormatISOCombined(' ');
        std::string startDateStr = std::string(startDateWxStr.ToUTF8());

        wxString finishDateWxStr = task.getDateFinish().IsValid() ?
            task.getDateFinish().FormatISOCombined(' ') :
            wxDateTime::Now().FormatISOCombined(' ');
        std::string finishDateStr = std::string(finishDateWxStr.ToUTF8());

        // Для title и description: преобразуем через wxString для обеспечения UTF-8
        wxString titleWxStr = wxString::FromUTF8(task.getTitle());
        if (!titleWxStr.IsValid()) {
            titleWxStr = wxString::FromUTF8(task.getTitle(), wxConvUTF8, wxREPLACE_INVALID);
        }
        std::string titleStr = std::string(titleWxStr.ToUTF8());

        wxString descriptionWxStr = wxString::FromUTF8(task.getDescription());
        if (!descriptionWxStr.IsValid()) {
            descriptionWxStr = wxString::FromUTF8(task.getDescription(), wxConvUTF8, wxREPLACE_INVALID);
        }
        std::string descriptionStr = std::string(descriptionWxStr.ToUTF8());

        newJArray.push_back({
            {"id", task.getId()},
            {"title", titleStr},
            {"description", descriptionStr},
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
    std::ifstream file(path, std::ios::binary);
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

            // Парсим даты с временем
            wxDateTime startDate, finishDate;
            std::string startStr = item["startDate"];
            std::string finishStr = item["finishDate"];

            // Преобразуем в wxString для корректной обработки UTF-8
            wxString startWxStr = wxString::FromUTF8(startStr);
            wxString finishWxStr = wxString::FromUTF8(finishStr);

            if (!startDate.ParseISOCombined(startWxStr)) {
                startDate = wxDateTime::Now();
            }

            if (!finishDate.ParseISOCombined(finishWxStr)) {
                finishDate = wxDateTime::Now();
                finishDate.Add(wxDateSpan(0, 0, 0, 1));
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
