#ifndef TASK_H
#define TASK_H

#include <cstdint>
#include <string> // строки
#include <wx/datetime.h> // работа со временнем


class Task {
public:
    Task(const std::string& name, const std::string& description, const wxDateTime& dateFinish, bool completed = false);
    Task(int id, const std::string& name, const std::string& description, const wxDateTime& dateFinish, const wxDateTime& dateStart, bool completed = false);
    bool isValid() const { return start.IsValid() && finish.IsValid(); };
    // геттеры
    const std::string& getTitle() const;
    const std::string& getDescription() const;
    const bool getCompleted() const;
    const wxDateTime &getDateNow() const;
    const wxDateTime &getDateFinish() const;
    const int getId() const;

    // сеттеры
    void setId(int id);
    void setTitle(const std::string& title);
    void setDescription(const std::string& description);
    bool setDateFinish(const wxDateTime &dateFinish);
    bool setDateNow(const wxDateTime &dateStart);
    void setComplete(bool completed);
    /*----------------------------------------------*/
    bool IsOverdue() const;
    wxTimeSpan TimeRemaining() const;

private:
    int id;
    static int nId;
    std::string title{};
    std::string description{};
    bool completed{};
    wxDateTime start;
    wxDateTime finish;
};



#endif //TASK_H
