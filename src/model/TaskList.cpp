//
// Created by Лёха on 09.08.2025.
//

#include "TaskList.h"

TaskList::TaskList() {
    // loadFromJson("TaskList.json");
}

void TaskList::AddTask(const std::string &newTitle, const std::string &newDescription, const wxDateTime & newFinishDate, bool completed) {
    Task t(newTitle, newDescription, newFinishDate, completed);
    tasks[t.getId()] = t; // добавляем хэш-таблицу по ключу id
}

bool TaskList::removeTask(int id) {
}
