//
// Created by Лёха on 09.08.2025.
//

#ifndef TASKLIST_H
#define TASKLIST_H

#include <unordered_map>
#include <string>
#include "Task.h"
#include <fstream>  // для сохранения/загрузки
#include <sstream>  // для простого парсинга
#include <nlohmann/json.hpp> // json library


class TaskList {
public:
    TaskList();
    ~TaskList();

    void AddTask(const std::string& title, const std::string& description, const wxDateTime& dueDate, bool completed = false);
    bool removeTask(int id);
    bool editTask(int id, const std::string& newTitle, const std::string newDescription ,const wxDateTime& newFinisDate, bool completed = false);
    Task* getTask(int id) ;
    bool loadFromJson(const std::string& path);
    bool saveToJson(const std::string& path);

private:
    std::unordered_map<int, Task> tasks;
    nlohmann::json jArray;
};



#endif //TASKLIST_H
