//
// Created by Лёха on 09.08.2025.
//

#ifndef TASKCONTROLLER_H
#define TASKCONTROLLER_H

#include "../model/TaskList.h"   // модель
#include <string>       // работа со строками
#include <wx/datetime.h>// работа с датами
#include <unordered_map>



class TaskController {
public:
    TaskController(TaskList& t);

    ~TaskController();

    void addTask(const std::string& title,const std::string& description,const wxDateTime& finisDate, bool complete) const;
    bool removeTask(int id) const;
    void editTask(int id, const std::string &title, const std::string &description, const wxDateTime &finisDate, bool complete) const;
    Task* getTask(int id) const;
    bool loadTaskFromFile(const std::string& filePath) const;
    bool saveTaskToFile(const std::string& filePath) const;
    std::unordered_map<int,Task> getAllTasks() const;
private:
    TaskList& taskList;


};

#endif //TASKCONTROLLER_H
