//
// Created by Лёха on 09.08.2025.
//

#ifndef TASKCONTROLLER_H
#define TASKCONTROLLER_H

#include "../model/TaskList.h"   // модель
#include <string>       // работа со строками
#include <wx/datetime.h>// работа с датами
#include <vector>       // если нужно будет отдавать списки задач


class TaskController {
public:
    TaskController(TaskList& t);
    ~TaskController();

    void addTask(int id, std::string& title, std::string& description, wxDateTime& finisDate, bool complete) const;
    void removeTask(int id) const;
    void editTask(int id, std::string& title, std::string& description, wxDateTime& finisDate, bool complete) const;
    void getTask(int id) const;
    void loadTaskFromFile(std::string& filePath) const;
    void saveTaskToFile(std::string& filePath) const;
private:
    TaskList& taskList;


};



#endif //TASKCONTROLLER_H
