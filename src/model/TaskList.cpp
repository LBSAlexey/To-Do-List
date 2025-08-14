//
// Created by Лёха on 09.08.2025.
//

#include "TaskList.h"

TaskList::TaskList() {
    // loadFromJson("TaskList.json");
}

void TaskList::AddTask(const std::string &newTitle, const std::string &newDescription, const wxDateTime & newFinishDate, bool completed) {
    Task task(newTitle, newDescription, newFinishDate, completed);
}
